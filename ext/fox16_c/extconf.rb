#!/bin/env ruby

require 'fileutils'
require 'mkmf'

gem 'mini_portile2', '~>2.1'
require 'mini_portile2'

$autodetected_fxscintilla = false

def is_fxscintilla_build?
  # No means no
  return false if fxscintilla_support_suppressed?

  # Check arguments
  with_config("fxscintilla", false) || $autodetected_fxscintilla
end

def fxscintilla_support_suppressed?
  !with_config("fxscintilla", true)
end

# Stick at zlib-1.2.7 for compatibility to MSYS1 based RubyInstaller.
LIBZ_VERSION = ENV['LIBZ_VERSION'] || '1.2.7.3'
LIBZ_SOURCE_URI = "http://zlib.net/fossils/zlib-#{LIBZ_VERSION}.tar.gz"

LIBPNG_VERSION = ENV['LIBPNG_VERSION'] || '1.6.29'
LIBPNG_SOURCE_URI = "http://prdownloads.sourceforge.net/libpng/libpng-#{LIBPNG_VERSION}.tar.gz"

# LIBJPEG_VERSION = ENV['LIBJPEG_VERSION'] || '9b'
# LIBJPEG_SOURCE_URI = "http://www.ijg.org/files/jpegsrc.v#{LIBJPEG_VERSION}.tar.gz"

LIBJPEG_VERSION = ENV['LIBJPEG_VERSION'] || '1.5.2'
LIBJPEG_SOURCE_URI = "https://downloads.sourceforge.net/libjpeg-turbo/libjpeg-turbo-#{LIBJPEG_VERSION}.tar.gz"

LIBTIFF_VERSION = ENV['LIBTIFF_VERSION'] || '4.0.8'
LIBTIFF_SOURCE_URI = "http://download.osgeo.org/libtiff/tiff-#{LIBTIFF_VERSION}.tar.gz"

LIBFOX_VERSION            = ENV['LIBFOX_VERSION'] || '1.6.55'
LIBFOX_SOURCE_URI         = "http://ftp.fox-toolkit.org/pub/fox-#{LIBFOX_VERSION}.tar.gz"

LIBFXSCINTILLA_VERSION            = ENV['LIBFXSCINTILLA_VERSION'] || '2.28.0'
LIBFXSCINTILLA_SOURCE_URI         = "http://download.savannah.gnu.org/releases/fxscintilla/fxscintilla-#{LIBFXSCINTILLA_VERSION}.tar.gz"
# LIBFXSCINTILLA_VERSION            = ENV['LIBFXSCINTILLA_VERSION'] || '3.5.2'
# LIBFXSCINTILLA_SOURCE_URI         = "https://github.com/yetanothergeek/fxscintilla/archive/FXSCINTILLA-#{LIBFXSCINTILLA_VERSION.gsub(".","_")}.tar.gz"


class BuildRecipe < MiniPortile
  def initialize(name, version, files)
    super(name, version)
    self.files = files
    rootdir = File.expand_path('../../..', __FILE__)
    self.target = File.join(rootdir, "ports")
    # Prefer host_alias over host in order to use i586-mingw32msvc as
    # correct compiler prefix for cross build, but use host if not set.
    self.host = consolidated_host(RbConfig::CONFIG["host_alias"].empty? ? RbConfig::CONFIG["host"] : RbConfig::CONFIG["host_alias"])
    self.patch_files = Dir[File.join(rootdir, "patches", self.name, self.version, "*.diff")].sort
  end

  def consolidated_host(name)
    name.gsub('i686-pc-mingw32', 'i586-mingw32msvc')
  end

  def configure_defaults
    [
      "--host=#{host}",    # build for specific target (host)
      "--disable-static",
      "--enable-shared",
    ]
  end

  def port_path
    "#{target}/#{host}"
  end

  # When using rake-compiler-dock on Windows, the underlying Virtualbox shared
  # folders don't support symlinks, but libiconv expects it for a build on
  # Linux. We work around this limitation by using the temp dir for cooking.
  def chdir_for_build
    build_dir = ENV['RCD_HOST_RUBY_PLATFORM'].to_s =~ /mingw|mswin|cygwin/ ? '/tmp' : '.'
    Dir.chdir(build_dir) do
      yield
    end
  end

  def cook_and_activate
    checkpoint = File.join(self.target, "#{self.name}-#{self.version}-#{self.host}.installed")
    unless File.exist?(checkpoint)
      chdir_for_build do
        self.cook
      end
      FileUtils.touch checkpoint
    end
    self.activate
    self
  end
end

def do_rake_compiler_setup
  if enable_config("win32-cross")
    dir_config("installed")

    libz_recipe = BuildRecipe.new("libz", LIBZ_VERSION, [LIBZ_SOURCE_URI]).tap do |recipe|
      class << recipe
        def configure
          Dir.chdir work_path do
            mk = File.read 'win32/Makefile.gcc'
            File.open 'win32/Makefile.gcc', 'wb' do |f|
              f.puts "BINARY_PATH = #{path}/bin"
              f.puts "LIBRARY_PATH = #{path}/lib"
              f.puts "INCLUDE_PATH = #{path}/include"
              mk.sub!(/^PREFIX\s*=\s*$/, "PREFIX = #{host}-")
              f.puts mk
            end
          end
        end

        def configured?
          Dir.chdir work_path do
            !! (File.read('win32/Makefile.gcc') =~ /^BINARY_PATH/)
          end
        end

        def compile
          execute "compile", "make -f win32/Makefile.gcc SHARED_MODE=1"
        end

        def install
          execute "install", "make -f win32/Makefile.gcc install SHARED_MODE=1"
        end
      end

      recipe.cook_and_activate
    end

    libpng_recipe = BuildRecipe.new("libpng", LIBPNG_VERSION, [LIBPNG_SOURCE_URI]).tap do |recipe|
      recipe.configure_options += [
        "CPPFLAGS=-I#{libz_recipe.path}/include",
        "LDFLAGS=-L#{libz_recipe.path}/lib",
      ]
      recipe.cook_and_activate
    end

    libjpeg_recipe = BuildRecipe.new("libjpeg", LIBJPEG_VERSION, [LIBJPEG_SOURCE_URI]).tap do |recipe|
      recipe.cook_and_activate
    end

    libtiff_recipe = BuildRecipe.new("libtiff", LIBTIFF_VERSION, [LIBTIFF_SOURCE_URI]).tap do |recipe|
      recipe.cook_and_activate
    end

    libfox_recipe = BuildRecipe.new("libfox", LIBFOX_VERSION, [LIBFOX_SOURCE_URI]).tap do |recipe|
      debug = enable_config("debug")
      recipe.configure_options += [
        "--without-xft",
        "--without-x",
        debug ? "--enable-debug" : "--enable-release",
        "CPPFLAGS=-I#{libjpeg_recipe.path}/include -I#{libpng_recipe.path}/include -I#{libtiff_recipe.path}/include -I#{libz_recipe.path}/include -DUNICODE=1 #{debug ? "-ggdb" : ""}",
        "LDFLAGS=-L#{libjpeg_recipe.path}/lib -L#{libpng_recipe.path}/lib -L#{libtiff_recipe.path}/lib -L#{libz_recipe.path}/lib #{debug ? "-ggdb" : ""}",
      ]
      class << recipe
        def compile
          # Add param -no-undefined to libtool to build a win32 shared lib
          execute "compile", "#{ENV['MAKE'] || "make"} libFOX_1_6_la_LDFLAGS='-version-info 0:49:0 -export-dynamic -no-undefined'"
        end
      end

      recipe.cook_and_activate
    end

    libfxscintills_recipe = BuildRecipe.new("libfxscintilla", LIBFXSCINTILLA_VERSION, [LIBFXSCINTILLA_SOURCE_URI]).tap do |recipe|
      class << recipe
        attr_accessor :libfox_path
        def mk
          "#{ENV['MAKE'] || "make"}"
        end

#         # This can be uncommented when fxscintilla is used from the source repository.
#         def configure
#           execute "bootstrap", "./bootstrap.sh"
#           super
#         end

        def compile
          execute "compile_lexers", "cd lexers && #{mk}"
          execute "compile_lexlib", "cd lexlib && #{mk}"
          execute "compile_src", "cd src && #{mk}"
          execute "compile_fox", "cd fox && #{mk} libfxscintilla_la_LDFLAGS='-version-info 23:0:3 -export-dynamic -no-undefined -L#{libfox_path}/lib -lFOX-1.6'"
        end

        def install
          execute "install", "cd fox && #{mk} install && cd ../include && #{mk} install"
        end
      end
      recipe.libfox_path = libfox_recipe.path

      recipe.configure_options += [
        "PKG_CONFIG_PATH=#{libfox_recipe.path}/lib/pkgconfig",
      ]
      recipe.cook_and_activate
    end

    dir_config('libfox', "#{libfox_recipe.path}/include/fox-1.6", "#{libfox_recipe.path}/lib")
    dir_config('libfxscintilla', "#{libfxscintills_recipe.path}/include/fxscintilla", "#{libfxscintills_recipe.path}/lib")

    gcc_shared_dlls = %w[libwinpthread-1.dll libgcc_s_dw2-1.dll libgcc_s_sjlj-1.dll libgcc_s_seh-1.dll libstdc++-6.dll]
    gcc_shared_dlls.each do |dll|
      cmd = "#{CONFIG['CC']} -print-file-name=\"#{dll}\""
      res = `#{cmd}`.chomp
      next if dll == res
      puts "#{cmd} => #{res}"
      FileUtils.cp `#{cmd}`.chomp, "#{libfox_recipe.path}/bin/", verbose: true
    end

    CONFIG['CXX'] = "#{libfox_recipe.host}-g++" # CXX setting must be prefixed for cross build
    CONFIG['CC'] += "\nCXX=#{CONFIG['CXX']}" # Hack CXX into Makefile for cross compilation
    CONFIG['LDSHARED'].gsub!('gcc', 'g++') # ensure C++ linker is used, so that libstdc++ is linked static
    $LDFLAGS += " -s" # remove symbol table informations from shared lib
    $libs = append_library($libs, "fxscintilla")

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
  have_library("z", "deflate")
  have_library("png", "png_create_read_struct")
  have_library("jpeg", "jpeg_mem_init")
  have_library("tiff", "TIFFSetErrorHandler")
  have_library("Xft", "XftInit")
  find_library("Xext", "XShmQueryVersion", "/usr/X11R6/lib")
  find_library("X11", "XFindContext", "/usr/X11R6/lib")
  find_library("GL", "glXCreateContext", "/usr/X11R6/lib")
  find_library("GLU", "gluNewQuadric", "/usr/X11R6/lib")
  $libs = append_library($libs, "Xrandr") unless RUBY_PLATFORM =~ /mingw/ || enable_config("win32-static-build")
  $libs = append_library($libs, "Xcursor") unless RUBY_PLATFORM =~ /mingw/ || enable_config("win32-static-build")
  $libs = append_library($libs, "FOX-1.6")
  $INCFLAGS << " -I#{File.join(File.dirname(__FILE__), 'include')}"
  if is_fxscintilla_build?
    $CPPFLAGS = $CPPFLAGS + " -DWITH_FXSCINTILLA -DHAVE_FOX_1_6"
  end

  checking_for("thread local variables") do
    $defs.push( "-DHAVE___THREAD" ) if try_compile <<-EOT
      __thread int x=1;
      #if defined(__MINGW32__)
        #include <windows.h>
        #if !defined(__MINGW64_VERSION_MAJOR)
          #error "Old mingw32 compiler doesn't implement thread local variables properly."
        #endif
      #endif
    EOT
  end &&
      have_func('rb_thread_call_without_gvl') &&
      have_func('rb_thread_call_with_gvl')

  have_func('rb_during_gc')
end

# This directive processes the "--with-fox-include" and "--with-fox-lib"
# command line switches and modifies the CFLAGS and LDFLAGS accordingly.

dir_config('fox', '/usr/local/include/fox-1.6', '/usr/local/lib')

# This directive processes the "--with-fxscintilla-include" and
# "--with-fxscintilla-lib" command line switches and modifies the CFLAGS
# and LDFLAGS accordingly.

dir_config('fxscintilla', '/usr/local/include/fxscintilla', '/usr/local/lib')

unless enable_config("win32-cross")
  checking_for "fox per pkg-config" do
    pkg_config("fox")
  end

  #
  # Check for FXScintilla header files, unless FXScintilla support has
  # been explicitly suppressed with the '--without-fxscintilla' flag.
  #

  unless fxscintilla_support_suppressed?
    checking_for "fxscintilla per pkg-config" do
      $autodetected_fxscintilla = pkg_config("fxscintilla")
    end

    unless $autodetected_fxscintilla
      checking_for "fxscintilla on Ubuntu with missing libfxscintilla.so link" do
        if find_library(":libfxscintilla.so.19", nil) && (cflags = RUBY_VERSION>="2.1" ? pkg_config("fxscintilla", "cflags") : `pkg-config --cflags fxscintilla`)
          $CXXFLAGS += " " + cflags
          $autodetected_fxscintilla = true
        end
      end
    end
  end
  checking_for "fxscintilla build" do
    is_fxscintilla_build?
  end
end

if enable_config("debug")
  $CPPFLAGS += " -ggdb"
  $LDFLAGS += " -ggdb"
else
  $CPPFLAGS += " -DNDEBUG"
end
$CPPFLAGS += " -Wno-unused-function"

# Platform-specific modifications
do_rake_compiler_setup

$CFLAGS += " -DRUBY_1_8" if RUBY_VERSION =~ /1\.8\./
$CFLAGS += " -DRUBY_1_9" if RUBY_VERSION =~ /1\.9\./
$CFLAGS += " -DRUBY_2_0" if RUBY_VERSION =~ /2\.0\./

# Last step: build the makefile
create_header
create_makefile("fox16_c")
