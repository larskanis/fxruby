require 'rubygems'
require 'hoe'
require 'erb'
require './lib/fox16/version.rb'

# Some constants we'll need
PKG_VERSION = Fox.fxrubyversion
FXRUBY_HOME_URL = "http://www.fxruby.org"
FOX_VERSION = "1.6.0"
FOX_HOME_URL = "http://www.fox-toolkit.com"
FOX_INSTALL_DIR = "e:\\src\\fox-1.6.35"
FXSCINTILLA_INSTALL_DIR = "c:\\src\\fxscintilla"
ISCC = "C:\\Progra~1\\InnoSe~1\\ISCC.exe"

Hoe.new("FXRuby", PKG_VERSION) do |p|
  # ... project specific data ...
  p.blog_categories = %w{FXRuby}
  p.clean_globs = [".config", "ext/fox16/Makefile", "ext/fox16/*.o", "ext/fox16/*.bundle", "ext/fox16/mkmf.log", "ext/fox16/conftest.dSYM"]
  p.developer("Lyle Johnson", "lyle@lylejohnson.name")
  p.extra_rdoc_files = ["rdoc-sources", File.join("rdoc-sources", "README.rdoc")]
  p.remote_rdoc_dir = "doc/api"
  p.spec_extras = {
    :description => "FXRuby is the Ruby binding to the FOX GUI toolkit.",
    :extensions => ["ext/fox16/extconf.rb"],
    :rdoc_options => ['--main', File.join('rdoc-sources', 'README.rdoc'), '--exclude', 'ext/fox16', '--exclude', %r{aliases|kwargs|missingdep|responder}],
    :require_paths => ['ext/fox16', 'lib'],
    :summary => "FXRuby is the Ruby binding to the FOX GUI toolkit."
  }
end

# Make sure extension is built before tests are run
task :test => [:build]

# ... project specific tasks ...

def setversions(filename)
  File.open(filename, "wb") do |out|
    template = ERB.new(File.open(filename + ".erb", "rb").read)
    out.write(template.result)
  end
end

desc "Create INNO Setup installer scripts from templates"
task :create_installer_scripts do
  output_filenames = {
    "FXRuby-ruby1.8.6-i386-msvcrt.iss" =>  ["1.8", "ruby186", "i386-msvcrt"]
  }
  template = ERB.new(File.open("scripts/FXRuby.iss.erb", "rb").read)
  output_filenames.each do |output_filename, info|
    File.open(output_filename, "wb") do |output_file|
      output_file.write(template.result(binding))
    end
  end
end

desc "Update the web site."
task :website => [:doap] do
  system %{scp -Cq doc/*.css lyle@rubyforge.org:/var/www/gforge-projects/fxruby/1.6/doc}
  system %{scp -Cq doc/*.html lyle@rubyforge.org:/var/www/gforge-projects/fxruby/1.6/doc}
  system %{scp -Cq doc/images/*.png lyle@rubyforge.org:/var/www/gforge-projects/fxruby/1.6/doc/images}
  system %{scp -Cq examples/*.rb lyle@rubyforge.org:/var/www/gforge-projects/fxruby/1.6/examples}
  system %{scp -Cq web/index.html lyle@rubyforge.org:/var/www/gforge-projects/fxruby}
  system %{scp -Cq web/community.html lyle@rubyforge.org:/var/www/gforge-projects/fxruby}
  system %{scp -Cq web/documentation.html lyle@rubyforge.org:/var/www/gforge-projects/fxruby}
  system %{scp -Cq web/downloads.html lyle@rubyforge.org:/var/www/gforge-projects/fxruby}
  system %{scp -Cq web/images/* lyle@rubyforge.org:/var/www/gforge-projects/fxruby/images}
  system %{scp -Cq web/css/*.css lyle@rubyforge.org:/var/www/gforge-projects/fxruby/css}
end

desc "Upload the DOAP file to the Web site"
task :doap => [:setversions] do
  system %{scp -Cq doap.rdf lyle@rubyforge.org:/var/www/gforge-projects/fxruby}
end

desc "Set versions"
task :setversions => [ :create_installer_scripts ] do
  setversions("pre-config.rb")
  setversions("doap.rdf")
  setversions("scripts/make-installers.rb")
end

desc "Run SWIG to generate the wrapper files."
task :swig do
  Dir.chdir "swig-interfaces" do
    system %{touch dependencies}
    system %{make depend; make}
  end
end

DISTFILES = [
  "ANNOUNCE",
  "LICENSE",
  "README",
  "README.win32.txt",
  "pre-config.rb",
  "install.rb",
  "doap.rdf",
  "FXRuby-ruby1.8.6-i386-msvcrt.iss",
  "Rakefile",
  "index.html",
  "doc/*.css",
  "doc/*.html",
  "doc/images/*.png",
  "examples/README",
  "examples/*.rb",
  "examples/*.xml",
  "examples/icons/*.png",
  "examples/icons/*.ico",
  "examples/textedit/*.rb",
  "lib/fox16/*.rb",
  "ext/fox16/MANIFEST",
  "ext/fox16/extconf.rb",
  "ext/fox16/*.c",
  "ext/fox16/*.cpp",
  "ext/fox16/include/*.h",
  "swig-interfaces/README",
  "swig-interfaces/Makefile",
  "swig-interfaces/swig.sed",
  "swig-interfaces/*.i",
  "tests/README",
  "tests/*.rb",
  "tests/*.ps",
  "rdoc-sources/*.rb",
  "rdoc-sources/README.rdoc",
  "scripts/make-installers.rb"
]

def distdir
  "FXRuby-#{PKG_VERSION}"
end

task :distdir => [:swig, :docs, :setversions, :generate_kwargs_lib] do
  rm_rf "#{distdir}"
  mkdir "#{distdir}"
  chmod(0777, distdir)
  DISTFILES.each do |filespec|
    Dir.glob(filespec) { |filename|
      mkdir_p "#{distdir}/#{File.dirname(filename)}"
      File.syscopy(filename, "#{distdir}/#{File.dirname(filename)}")
    }
  end
  rm_f "#{distdir}/lib/fox16/acceltable.rb"
  rm_f "#{distdir}/lib/fox16/canvas.rb"
  rm_f "#{distdir}/lib/fox16/html.rb"
  rm_f "#{distdir}/lib/fox16/sugar.rb"
  rm_f "#{distdir}/lib/fox16/tkcompat.rb"
  rm_f "#{distdir}/examples/canvasdemo.rb"
  rm_f "#{distdir}/examples/examples.rb"
  rm_f "#{distdir}/examples/gdchart.rb"
  rm_f "#{distdir}/examples/rapt-gui.rb"
  rm_f "#{distdir}/examples/WhatAQuietStiff.rb"
  rm_f "#{distdir}/examples/gembrowser.rb"
  rm_f "#{distdir}/examples/rmagick.rb"
  rm_f "#{distdir}/examples/tablenew.rb"
end

desc "Build the source tarball."
task :dist => [:distdir] do
  system "chmod -R a+r #{distdir}"
  system "tar czf #{distdir}.tar.gz #{distdir}"
  system "rm -rf #{distdir}"
end

desc "Generate all of the documentation files."
task :doc do
  Dir.chdir "doc" do
    system %{make}
  end
end

def make_impl
  Dir.chdir "ext/fox16" do
    ruby "make_impl.rb"
  end
end

task :configure => [:scintilla, :setversions, :generate_kwargs_lib] do
  unless File.exist?(".config")
#   ruby "install.rb config -- --with-fxscintilla-include=/usr/include/fxscintilla --with-fxscintilla-lib=/usr/lib"
#   ruby "install.rb config -- --without-fxscintilla"
#   ruby "install.rb config -- --with-fox-include=/opt/local/include/fox-1.6 --with-fox-lib=/opt/local/lib --with-fxscintilla-include=/opt/local/include/fxscintilla --with-fxscintilla-lib=/opt/local/lib"
    ruby "install.rb config -- --with-fox-include=/usr/local/include/fox-1.6 --with-fox-lib=/usr/local/lib --with-fxscintilla-include=/usr/local/include/fxscintilla --with-fxscintilla-lib=/usr/local/lib"
    make_impl
  end
end

desc "Build it."
task :build => [:configure] do
  ruby "install.rb setup"
end

desc "Install it."
task :install => [:build] do
  ruby "install.rb install"
end

task :scintilla do
  ruby "scripts/iface.rb -i ~/src/fxscintilla/scintilla/include/Scintilla.iface -o lib/fox16/scintilla.rb"
end

# Given the distribution tarball, build the installer for Win32
desc "Build Win32 installer"
task :build_win32 do
  if File.exist? ".config"
    ruby "install.rb clean"
  end
  ruby "install.rb config --make-prog=nmake -- --with-fox-include=#{FOX_INSTALL_DIR}\\include --with-fox-lib=#{FOX_INSTALL_DIR}\\lib --with-fxscintilla-include=#{FXSCINTILLA_INSTALL_DIR}\\include --with-fxscintilla-lib=#{FXSCINTILLA_INSTALL_DIR}\\lib"
# ruby "install.rb config --make-prog=nmake -- --with-fox-include=#{FOX_INSTALL_DIR}\\include --with-fox-lib=#{FOX_INSTALL_DIR}\\lib"
  ruby "install.rb setup"
end

desc "Build Win32 installer using INNO Setup"
task :build_win32_installer => [:build_win32] do
  iss_script_name = nil
  case VERSION
    when /1.8.2/
      iss_script_name = "FXRuby-ruby1.8.2-i386-msvcrt.iss"
    when /1.8.4/
      iss_script_name = "FXRuby-ruby1.8.4-i386-msvcrt.iss"
    when /1.8.5/
      iss_script_name = "FXRuby-ruby1.8.5-i386-msvcrt.iss"
    when /1.8.6/
      iss_script_name = "FXRuby-ruby1.8.6-i386-msvcrt.iss"
  end
  system(ISCC, iss_script_name)
end

desc "Build Win32 binary Gem"
task :build_win32_gem => [:build_win32] do
  spec = create_gemspec
  spec.platform = Gem::Platform::CURRENT
  spec.files += ["ext/fox16/fox16.so"]
  Gem::Builder.new(spec).build
end

desc "Build Win32 binary installer and Gem"
task :release_win32 => [:build_win32_installer, :build_win32_gem] do
end

desc "Build Mac OS X binary Gem"
task :build_macosx_gem do
  raise RuntimeError, "remove libFOX*.dylib and recompile before building gem" unless Dir.glob("/usr/local/lib/libFOX*.dylib").empty?
  spec = create_gemspec
  spec.platform = Gem::Platform::CURRENT
  spec.files += ["ext/fox16/fox16.bundle"]
  Gem::Builder.new(spec).build
end

task :generate_kwargs_lib do
  ruby 'scripts/generate_kwargs_lib.rb'
end
