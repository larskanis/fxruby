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

def do_rake_compiler_setup
  if enable_config("win32-static-build")
    dir_config("installed")
    have_library( 'gdi32', 'CreateDC' ) && append_library( $libs, 'gdi32' )
    have_library( 'opengl32' ) && append_library( $libs, 'opengl32' )
    have_library( 'winspool', 'EnumPrintersA') && append_library( $libs, 'winspool' )

    CONFIG['CC'] += "\nCXX=#{RbConfig::CONFIG["host"]}-g++" # Hack CXX into Makefile for cross compilation
    CONFIG['LDSHARED'].gsub!('gcc', 'g++') # ensure C++ linker is used, so that libstdc++ is linked static
    $LDFLAGS += " -s -static-libgcc -static-libstdc++" # mingw-w64 v4.7 defaults to dynamic linking
  elsif RUBY_PLATFORM =~ /mingw/
    $CFLAGS = $CFLAGS + " -I/usr/local/include"
    $LDFLAGS = $LDFLAGS + " -I/usr/local/lib"
    %w{stdc++ glu32 opengl32 wsock32 comctl32 mpr gdi32 winspool}.each {|lib| $libs = append_library($libs, lib) }
  elsif RUBY_PLATFORM =~ /darwin/
    $CFLAGS = $CFLAGS + " -I/usr/X11/include" # for built-in libpng
    $LDFLAGS = $LDFLAGS + " -L/usr/X11/lib"   # for built-in libpng
    $CFLAGS = $CFLAGS + " -I/usr/local/include" # for libjpeg and libtiff
    $LDFLAGS = $LDFLAGS + " -L/usr/local/lib"   # for libjpeg and libtiff
    %w{Xft}.each {|lib| $libs = append_library($libs, lib) }
  end
  $libs = append_library($libs, "stdc++") unless RUBY_PLATFORM =~ /mingw/ || enable_config("win32-static-build")
  have_header("sys/time.h") unless RUBY_PLATFORM =~ /mingw/ || enable_config("win32-static-build")
  have_header("signal.h")
  if have_library("z", "deflate")
    have_library("png", "png_create_read_struct")
  end
  have_library("jpeg", "jpeg_mem_init")
  have_library("tiff", "TIFFSetErrorHandler")
  have_library("Xft", "XftInit")
  find_library("Xext", "XShmQueryVersion", "/usr/X11R6/lib")
  find_library("X11", "XFindContext", "/usr/X11R6/lib")
  find_library("GL", "glXCreateContext", "/usr/X11R6/lib")
  find_library("GLU", "gluNewQuadric", "/usr/X11R6/lib")
  $libs = append_library($libs, "FOX-1.6")
  $libs = append_library($libs, "Xrandr") unless RUBY_PLATFORM =~ /mingw/ || enable_config("win32-static-build")
  $libs = append_library($libs, "Xcursor") unless RUBY_PLATFORM =~ /mingw/ || enable_config("win32-static-build")
  $libs = append_library($libs, "png")
  find_header('FXRbCommon.h', File.join(File.dirname(__FILE__), 'include'))
  if is_fxscintilla_build?
    FileUtils.move('scintilla_wrap.cpp.bak', 'scintilla_wrap.cpp') if FileTest.exist?('scintilla_wrap.cpp.bak')
    $CPPFLAGS = $CPPFLAGS + " -DWITH_FXSCINTILLA -DHAVE_FOX_1_6"
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
do_rake_compiler_setup

$CFLAGS += " -DRUBY_1_8" if RUBY_VERSION =~ /1\.8\./
$CFLAGS += " -DRUBY_1_9" if RUBY_VERSION =~ /1\.9\./
$CFLAGS += " -DRUBY_2_0" if RUBY_VERSION =~ /2\.0\./

# Last step: build the makefile
create_makefile("fox16_c")
