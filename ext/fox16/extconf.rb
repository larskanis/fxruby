#!/bin/env ruby

require 'fileutils'
require 'mkmf'

def find_installed_fox_version
  stddirs = ["/usr/include/fox-1.6",
             "/usr/local/include/fox-1.6",
             "/sw/include/fox-1.6",
	     "/opt/local/include/fox-1.6"]
  usrdirs = []
  ARGV.each do |arg|
    if arg =~ /--with-fox-include/
      option, value = arg.split('=')
      usrdirs = [ value ] + usrdirs
    end
  end
  incdirs = usrdirs + stddirs
  incdirs.uniq! # remove duplicates
  
  incdirs.each do |incdir|
    filename = File.join(incdir, "fxver.h")
    if FileTest.exist?(filename)
      idircflag = "-I" + incdir
      $CPPFLAGS += " " + idircflag unless $CPPFLAGS.split.include?(idircflag)
      return
    end
  end
  
  # Couldn't find it; this should have been caught by the pre-config script
  raise RuntimeError, "couldn't find FOX header files"
end

$autodetected_fxscintilla = false

def find_installed_fxscintilla_version
  stddirs = ["/usr/include/fxscintilla",
             "/usr/local/include/fxscintilla",
             "/sw/include/fxscintilla",
	     "/opt/local/include/fxscintilla"]
  usrdirs = []
  ARGV.each do |arg|
    if arg =~ /--with-fxscintilla-include/
      option, value = arg.split('=')
      usrdirs = [ value ] + usrdirs
    end
  end
  incdirs = usrdirs + stddirs
  incdirs.uniq! # remove duplicates
  
  incdirs.each do |incdir|
    filename = File.join(incdir, "FXScintilla.h")
    if FileTest.exist?(filename)
      $autodetected_fxscintilla = true
      idircflag = "-I" + incdir
      $CPPFLAGS += " " + idircflag unless $CPPFLAGS.split.include?(idircflag)
      return
    end
  end
end

def is_fxscintilla_build?
  # No means no
  return false if fxscintilla_support_suppressed?
  
  # Check arguments
  args = ARGV.delete_if { |e| !(e =~ /--with-fxscintilla/) }
  (args.length > 0) || $autodetected_fxscintilla
end

def fxscintilla_support_suppressed?
  ARGV.include? "--without-fxscintilla"
end

def do_cygwin_setup
  extra_libs = %w{stdc++ glu32 opengl32 wsock32 comctl32 mpr gdi32 winspool}
  extra_libs.each do |lib|
    $libs = append_library($libs, lib)
  end
  have_header("sys/time.h")
  have_header("signal.h")
  if have_library("z", "deflate")
    have_library("png", "png_create_read_struct")
  end
  have_library("jpeg", "jpeg_mem_init")
  have_library("tiff", "TIFFSetErrorHandler")
  $libs = append_library($libs, "FOX-1.6")
  $CFLAGS = $CFLAGS + " -fpermissive -DWIN32 -Iinclude"
  if is_fxscintilla_build?
    FileUtils.move('scintilla_wrap.cpp.bak', 'scintilla_wrap.cpp') if FileTest.exist?('scintilla_wrap.cpp.bak')
    $CFLAGS = $CFLAGS + " -DWITH_FXSCINTILLA -DHAVE_FOX_1_6"
    $libs = append_library($libs, "fxscintilla")
  else
    FileUtils.move('scintilla_wrap.cpp', 'scintilla_wrap.cpp.bak') if FileTest.exist?('scintilla_wrap.cpp')
  end
end

def do_mswin32_setup
  extra_libs = %w{glu32 opengl32 mpr wsock32 comctl32 winspool shell32 advapi32 shell32 gdi32 user32}
  extra_libs.each do |lib|
    $libs = append_library($libs, lib)
  end
  have_header("sys/time.h")
  have_header("signal.h")
  have_library("zlib", "deflate")
  have_library("libpng", "png_create_read_struct")
  have_library("libjpeg", "jpeg_mem_init")
  have_library("libtiff", "TIFFSetErrorHandler")
# $CFLAGS = $CFLAGS + " /DWIN32 /GR /GX /DFOXDLL /Iinclude"
# $LOCAL_LIBS = $LOCAL_LIBS + "foxdll.lib"
  $CFLAGS = $CFLAGS + " /DWIN32 /DUNICODE /GR /GX /Iinclude"
  $LOCAL_LIBS = $LOCAL_LIBS + "FOX-1.6.lib"
  if is_fxscintilla_build?
    FileUtils.move('scintilla_wrap.cpp.bak', 'scintilla_wrap.cpp') if FileTest.exist?('scintilla_wrap.cpp.bak')
    $CFLAGS = $CFLAGS + " /DWITH_FXSCINTILLA /DHAVE_FOX_1_6"
    $libs = append_library($libs, "fxscintilla")
  else
    FileUtils.move('scintilla_wrap.cpp', 'scintilla_wrap.cpp.bak') if FileTest.exist?('scintilla_wrap.cpp')
  end
end

def do_unix_setup
  $libs = append_library($libs, "stdc++")
# $libs = append_library($libs, "supc++")
  have_header("sys/time.h")
  have_header("signal.h")
  have_library("png", "png_create_read_struct")
  have_library("z", "deflate")
  have_library("jpeg", "jpeg_mem_init")
  have_library("tiff", "TIFFSetErrorHandler")
  find_library("Xext", "XShmQueryVersion", "/usr/X11R6/lib")
  find_library("X11", "XFindContext", "/usr/X11R6/lib")
  find_library("GL", "glXCreateContext", "/usr/X11R6/lib")
  find_library("GLU", "gluNewQuadric", "/usr/X11R6/lib")
  $libs = append_library($libs, "FOX-1.6")
  $libs = append_library($libs, "Xrandr")
  $CFLAGS = $CFLAGS + " -O0 -Iinclude"
  if is_fxscintilla_build?
    FileUtils.move('scintilla_wrap.cpp.bak', 'scintilla_wrap.cpp') if FileTest.exist?('scintilla_wrap.cpp.bak')
    $CFLAGS = $CFLAGS + " -DWITH_FXSCINTILLA -DHAVE_FOX_1_6"
    $libs = append_library($libs, "fxscintilla")
  else
    FileUtils.move('scintilla_wrap.cpp', 'scintilla_wrap.cpp.bak') if FileTest.exist?('scintilla_wrap.cpp')
  end
end

def do_darwin_setup
  $libs = append_library($libs, "stdc++")
  have_header("sys/time.h")
  have_header("signal.h")
  have_library("png", "png_create_read_struct")
  have_library("z", "deflate")
  have_library("jpeg", "jpeg_mem_init")
  have_library("tiff", "TIFFSetErrorHandler")
  find_library("Xext", "XShmQueryVersion", "/usr/X11R6/lib")
  find_library("X11", "XFindContext", "/usr/X11R6/lib")
  find_library("GL", "glXCreateContext", "/usr/X11R6/lib")
  find_library("GLU", "gluNewQuadric", "/usr/X11R6/lib")
  $libs = append_library($libs, "FOX-1.6")
  $libs = append_library($libs, "Xrandr")
  $libs = append_library($libs, "Xcursor")
  $libs = append_library($libs, "png")
  $CFLAGS = $CFLAGS + " -O0 -Iinclude"
  if is_fxscintilla_build?
    FileUtils.move('scintilla_wrap.cpp.bak', 'scintilla_wrap.cpp') if FileTest.exist?('scintilla_wrap.cpp.bak')
    $CFLAGS = $CFLAGS + " -DWITH_FXSCINTILLA -DHAVE_FOX_1_6"
    $libs = append_library($libs, "fxscintilla")
  else
    FileUtils.move('scintilla_wrap.cpp', 'scintilla_wrap.cpp.bak') if FileTest.exist?('scintilla_wrap.cpp')
  end
end

# This directive processes the "--with-fox-include" and "--with-fox-lib"
# command line switches and modifies the CFLAGS and LDFLAGS accordingly.

dir_config('fox', '/usr/local/include/fox-1.6', '/usr/local/lib')

# This directive processes the "--with-fxscintilla-include" and
# "--with-fxscintilla-lib" command line switches and modifies the CFLAGS
# and LDFLAGS accordingly.

dir_config('fxscintilla', '/usr/local/include/fxscintilla', '/usr/local/lib')

find_installed_fox_version

#
# Check for FXScintilla header files, unless FXScintilla support has
# been explicitly suppressed with the '--without-fxscintilla' flag.
#

unless fxscintilla_support_suppressed?
  find_installed_fxscintilla_version
end

# Platform-specific modifications
if RUBY_PLATFORM =~ /cygwin/ || RUBY_PLATFORM =~ /mingw/
  do_cygwin_setup
elsif RUBY_PLATFORM =~ /mswin32/
  do_mswin32_setup
elsif RUBY_PLATFORM =~ /darwin/
  do_darwin_setup
else
  do_unix_setup
end

# Check for Ruby 1.9
$CFLAGS += " -DRUBY_1_9" if RUBY_VERSION =~ /1\.9\./

# Last step: build the makefile
create_makefile("fox16")
