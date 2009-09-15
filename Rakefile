require 'rubygems'
require 'hoe'
require 'erb'
require 'rake/extensiontask'

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
  p.test_globs = "test/**/TC_*.rb"
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
  make_impl
end

task :scintilla do
# ruby "scripts/iface.rb -i ~/src/fxscintilla/scintilla/include/Scintilla.iface -o lib/fox16/scintilla.rb"
  ruby "scripts/iface.rb -i c:/src/fxscintilla-1.71/scintilla/include/Scintilla.iface -o lib/fox16/scintilla.rb"
end

desc "Build Win32 installer using INNO Setup"
task :build_win32_installer => [:compile] do
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
task :build_win32_gem => [:compile] do
  spec = create_gemspec
  spec.platform = Gem::Platform::CURRENT
  spec.files += ["ext/fox16/fox16.so"]
  Gem::Builder.new(spec).build
end

desc "Build Win32 binary installer and Gem"
task :release_win32 => [:build_win32_installer, :build_win32_gem] do
end

task :generate_kwargs_lib do
  ruby 'scripts/generate_kwargs_lib.rb'
end

Rake::ExtensionTask.new("fox16") do |ext|
# ext.config_options << "--with-fox-include=/usr/local/include/fox-1.6"
# ext.config_options << "--with-fox-lib=/usr/local/lib"
  ext.config_options << "--with-fox-include=c:/ruby-1.8.6-p383-preview2/devkit/msys/1.0.11/usr/local/include/fox-1.6"
  ext.config_options << "--with-fox-lib=c:/ruby-1.8.6-p383-preview2/devkit/msys/1.0.11/usr/local/lib"
  ext.config_options << "--with-fxscintilla-include=c:/ruby-1.8.6-p383-preview2/devkit/msys/1.0.11/usr/local/include/fxscintilla"
  ext.config_options << "--with-fxscintilla-lib=c:/ruby-1.8.6-p383-preview2/devkit/msys/1.0.11/usr/local/lib"
end

# Set environment variable SWIG_LIB to
# c:/ruby-1.8.6-p383-preview2/devkit/msys/1.0.11/usr/local/share/swig/1.3.22
# before running swig on MinGW.
namespace :swig do
  SWIG = "swig"
  SWIGFLAGS = "-fcompact -noruntime -c++ -ruby -no_default -I../fox-includes"
  SWIG_LIB = `#{SWIG} -swiglib`.chomp
  SWIG_MODULES = {
    "core.i" => "core_wrap.cpp",
    "dcmodule.i" => "dc_wrap.cpp",
    "dialogs.i" => "dialogs_wrap.cpp",
    "framesmodule.i" => "frames_wrap.cpp",
    "iconlistmodule.i" => "iconlist_wrap.cpp",
    "icons.i" => "icons_wrap.cpp",
    "image.i" => "image_wrap.cpp",
    "labelmodule.i" => "label_wrap.cpp",
    "layout.i" => "layout_wrap.cpp",
    "listmodule.i" => "list_wrap.cpp",
    "mdi.i" => "mdi_wrap.cpp",
    "menumodule.i" => "menu_wrap.cpp",
    "fx3d.i" => "fx3d_wrap.cpp",
    "scintilla.i" => "scintilla_wrap.cpp",
    "table-module.i" => "table_wrap.cpp",
    "text-module.i" => "text_wrap.cpp",
    "treelist-module.i" => "treelist_wrap.cpp",
    "ui.i" => "ui_wrap.cpp"
  }

  def wrapper_src_file_path(wrapper_src_file_name)
    File.join("..", "ext", "fox16", wrapper_src_file_name)
  end
  
  def swig_generate_dependencies(swig_interface_file_name, wrapper_src_file_name)
    system "#{SWIG} #{SWIGFLAGS} -MM -o #{wrapper_src_file_path(wrapper_src_file_name)} #{swig_interface_file_name} >> dependencies"
  end
  
  def sed(wrapper_src_file_name)
    results = []
    IO.readlines(wrapper_src_file_name).each do |line|
      line.gsub!(/static VALUE mCore;/, "VALUE mCore;")
      line.gsub!(/mCore = rb_define_module\("Core"\)/, "mFox = rb_define_module(\"Fox\")")
      line.gsub!(/mCore/, "mFox")
      next if line =~ /static VALUE m(Dc|Dialogs|Frames|Iconlist|Icons|Image|Label|Layout|List|Mdi|Menu|Fx3d|Scintilla|Table|Text|Treelist|Ui);/
      next if line =~ /m(Dc|Dialogs|Frames|Iconlist|Icons|Image|Label|Layout|List|Mdi|Menu|Fx3d|Scintilla|Table|Text|Treelist|Ui) = rb_define_module/
      next if line =~ /rb_require/
      line.gsub!(/m(Dc|Dialogs|Frames|Iconlist|Icons|Image|Label|Layout|List|Mdi|Menu|Fx3d|Scintilla|Table|Text|Treelist|Ui),/, "mFox,")
      results << line
    end
    File.open(wrapper_src_file_name, "w") do |io|
      io.write(results.join)
    end
  end
  
  def swig(swig_interface_file_name, wrapper_src_file_name)
    system "#{SWIG} #{SWIGFLAGS} -o #{wrapper_src_file_path(wrapper_src_file_name)} #{swig_interface_file_name}"
    sed wrapper_src_file_path(wrapper_src_file_name)
  end

  task :swig_dependencies do
    Dir.chdir "swig-interfaces" do
      FileUtils.rm_f "dependencies"
      FileUtils.touch "dependencies"
      SWIG_MODULES.each do |key, value|
        swig_generate_dependencies(key, value)
      end
    end
  end
  
  task :swig_librb do
    Dir.chdir "swig-interfaces" do
      File.open(wrapper_src_file_path("librb.c"), "w") do |io|
        io.puts "#define SWIG_GLOBAL 1"
        io.write(IO.read(File.join(SWIG_LIB, "ruby", "precommon.swg")))
        io.write(IO.read(File.join(SWIG_LIB, "common.swg")))
        io.write(IO.read(File.join(SWIG_LIB, "ruby", "rubyhead.swg")))
        io.write(IO.read(File.join(SWIG_LIB, "ruby", "rubydef.swg")))
      end
    end
  end

  desc "Run SWIG to generate the wrapper files."
  task :swig => [:swig_dependencies, :swig_librb] do
    Dir.chdir "swig-interfaces" do
      SWIG_MODULES.each do |key, value|
        swig(key, value)
      end
    end
  end
end

task :build => [:configure, :compile]
