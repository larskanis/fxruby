require 'rubygems'
require 'hoe'
require 'erb'
require 'rake/extensiontask'
require './lib/fox16/version.rb'

Hoe.plugin :bundler

# Use forked process for chdir'ed environment, to allow parallel execution with drake
module FileUtils
  alias unforked_fileutils_cd cd
  def cd(dir, options={}, &block)
    raise "chdir called without block" unless block_given?
    Process.waitpid(fork{ unforked_fileutils_cd(dir, options, &block) })
  end
  module_function :cd
  alias chdir cd
  module_function :chdir
end

# Some constants we'll need
PKG_VERSION = Fox.fxrubyversion

LIBFXSCINTILLA_VERSION            = ENV['LIBFXSCINTILLA_VERSION'] || '2.28.0'
LIBFXSCINTILLA_SOURCE_URI         = "http://download.savannah.gnu.org/releases/fxscintilla/fxscintilla-#{LIBFXSCINTILLA_VERSION}.tar.gz"

SWIG = (RUBY_PLATFORM =~ /mingw/) ? "swig.exe" : "swig"
SWIGFLAGS = "-c++ -ruby -nodefaultdtor -nodefaultctor -w302 -features compactdefaultargs -I../fox-includes"
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


hoe = Hoe.spec "fxruby" do
  # ... project specific data ...
  self.blog_categories = %w{FXRuby}
  self.clean_globs = [".config", "ext/fox16_c/Makefile", "ext/fox16_c/*.o", "ext/fox16_c/*.bundle", "ext/fox16_c/mkmf.log", "ext/fox16_c/conftest.dSYM", "ext/fox16_c/include/swigrubyrun.h", "ext/fox16_c/librb.c", "ext/fox16_c/include/inlinestubs.h", "ext/fox16_c/*_wrap.cpp", "tmp", "ports/*.installed", "ports/*mingw32*"]
  developer("Lyle Johnson", "lyle@lylejohnson.name")
  developer("Lars Kanis", "kanis@comcard.de")
  self.extra_rdoc_files = ["rdoc-sources", File.join("rdoc-sources", "README.rdoc")]
  self.remote_rdoc_dir = "doc/api"
  self.spec_extras = {
    :description => "FXRuby is the Ruby binding to the FOX GUI toolkit.",
    :extensions => ["ext/fox16_c/extconf.rb"],
    :rdoc_options => ['--main', File.join('rdoc-sources', 'README.rdoc'), '--exclude', 'ext/fox16_c', '--exclude', %r{aliases|kwargs|missingdep|responder}.inspect],
    :require_paths => ['lib'],
    :summary => "FXRuby is the Ruby binding to the FOX GUI toolkit."
  }
  self.test_globs = ["test/**/TC_*.rb"]
  self.testlib = :testunit
  self.version = PKG_VERSION
  self.readme_file = 'README.rdoc'
  self.extra_rdoc_files << self.readme_file
  self.extra_deps << ['mini_portile', '~> 0.6']
  self.extra_dev_deps << ['hoe-bundler', '~> 1.2']
  self.extra_dev_deps << ['rake-compiler', '~> 0.9']
  self.extra_dev_deps << ['rake-compiler-dock', '~> 0.5.0']
  self.extra_dev_deps << ['opengl', '~> 0.8']
  self.extra_dev_deps << ['glu', '~> 8.0']
  self.extra_dev_deps << ['test-unit', '~> 3.1']
  self.license 'LGPL'

  spec_extras[:files] = File.read_utf("Manifest.txt").split(/\r?\n\r?/).reject{|f| f=~/^fox-includes|^web/ }
  spec_extras[:files] += SWIG_MODULES.values.map{|f| File.join("ext/fox16_c", f) }
  spec_extras[:files] << 'ext/fox16_c/include/inlinestubs.h'
  spec_extras[:files] << 'ext/fox16_c/swigruby.h'
  spec_extras[:files] << 'doap.rdf'
  spec_extras[:files] << 'lib/fox16/kwargs.rb'
end

# Make sure extension is built before tests are run
task :test => [:compile]

# The "docs" task created by Hoe assumes that we want to run RDoc
# over everything under the "lib" and "ext" subdirectories.
# We need to go back and tell it to skip the stuff under ext.
# rdoc_target = Rake::Task['docs'].prerequisites.first
# rdoc_files = Rake::Task[rdoc_target].prerequisites
# rdoc_files.reject! {|x| x == "ext/fox16_c" }

# Make sure that all of the package contents exist before we try to build the package
#Rake::Task['package'].prerequisites.unshift("swig:swig", "fxruby:setversions", "fxruby:generate_kwargs_lib")

# ... project specific tasks ...

Rake::ExtensionTask.new("fox16_c", hoe.spec) do |ext|
  ext.cross_compile = true
  ext.cross_platform = ['x86-mingw32', 'x64-mingw32']
  # Enable FXTRACE and FXASSERT for 'rake compile'
  ext.config_options << "--enable-debug"

  ext.cross_config_options += [
      "--enable-win32-cross",
      "--with-fxscintilla",
    ]

  # Add dependent DLLs to the cross gems
  ext.cross_compiling do |spec|
    platform_host_map =  {
      'x86-mingw32' => ['i586-mingw32msvc', 'i686-w64-mingw32'],
      'x64-mingw32' => ['x86_64-w64-mingw32'],
    }

    gemplat = spec.platform.to_s
    platform_host_map[gemplat].each do |host|

      gcc_shared_dlls = %w[libwinpthread-1.dll libgcc_s_dw2-1.dll libgcc_s_sjlj-1.dll libgcc_s_seh-1.dll libstdc++-6.dll]

      dlls = gcc_shared_dlls.select{|dll| File.exist?("ports/#{host}/bin/#{dll}") }
      dlls += [
          "libfxscintilla-20.dll",
          "libFOX-1.6-0.dll",
          "libjpeg-8.dll",
          "libpng15-15.dll",
          "libtiff-5.dll",
          "zlib1.dll",
      ]

      spec.files += dlls.map{|dll| "ports/#{host}/bin/#{dll}" }

      dlls.each do |dll|
        task "ports/#{host}/bin/#{dll}" do |t|
          sh "x86_64-w64-mingw32-strip", t.name
        end
      end
    end
  end
end

# To reduce the gem file size strip mingw32 dlls before packaging
ENV['RUBY_CC_VERSION'].to_s.split(':').each do |ruby_version|
  task "tmp/x86-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so" do |t|
    sh "i686-w64-mingw32-strip -S tmp/x86-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so"
  end

  task "tmp/x64-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so" do |t|
    sh "x86_64-w64-mingw32-strip -S tmp/x64-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so"
  end
end

desc "Build the windows binary gems"
task 'gem:windows' => 'gem' do
  require 'rake_compiler_dock'
  RakeCompilerDock.sh "rake cross native gem RUBYOPT=--disable-rubygems MAKE=\"nice make V=1 -j `nproc`\" "
end

# Set environment variable SWIG_LIB to
# c:/ruby-1.8.6-p383-preview2/devkit/msys/1.0.11/usr/local/share/swig/1.3.22
# before running swig on MinGW.
namespace :swig do
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
    cmd = "#{SWIG} #{SWIGFLAGS} -o #{wrapper_src_file_name} #{swig_interface_file_name}"
    puts cmd
    system cmd
    sed wrapper_src_file_name
  end

  task :swigruby_h => ["ext/fox16_c/swigruby.h"]
  file "ext/fox16_c/swigruby.h" do |task|
    puts "generate #{task.name}"
    system "#{SWIG} -ruby -external-runtime #{task.name}"
  end

  desc "Run SWIG to generate the wrapper files."
  task :swig => [:swigruby_h] + SWIG_MODULES.map{|ifile, cppfile| File.join("ext/fox16_c", cppfile) }

  # add dependencies for compile *.i to *_wrap.cpp
  SWIG_MODULES.each do |ifile, cppfile|
    cppfile_path = File.join("ext/fox16_c", cppfile)

    file cppfile_path => [ifile, 'macros.i', 'common.i', 'fxdefs.i', 'ruby-typemaps.i',
                          'markfuncs.i', 'exceptions.i', 'freefuncs.i', 'macros.i', 'handlers.i'
                         ].map{|f| File.join("swig-interfaces", f) } do |task|
      swig(File.join("swig-interfaces", ifile), cppfile_path)
    end
  end
end


namespace :fxruby do

  desc "Update the web site."
  task :website => [:doap] do
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

  def setversions(filename)
    File.open(filename, "wb") do |out|
      template = ERB.new(File.open(filename + ".erb", "rb").read)
      out.write(template.result)
    end
  end

  desc "Set versions"
  task :setversions => "doap.rdf"
  file "doap.rdf" => ["doap.rdf.erb"] do
    setversions("doap.rdf")
  end

  def make_impl
    ruby '-Cext/fox16_c', "make_impl.rb"
  end

  task :configure => [:scintilla, :setversions, :generate_kwargs_lib]

  rb_header_files = Dir['ext/include/*.h']
  file 'ext/fox16_c/include/inlinestubs.h' => rb_header_files do
    make_impl
  end
  file 'ext/fox16_c/impl.cpp' => rb_header_files do
    make_impl
  end

  file "ext/fox16_c/extconf.rb" => ['ext/fox16_c/swigruby.h', 'ext/fox16_c/impl.cpp', 'ext/fox16_c/include/inlinestubs.h'] +
      SWIG_MODULES.map{|ifile, cppfile| File.join("ext/fox16_c", cppfile) }


  directory "ports/archives"
  file "ports/archives/fxscintilla-2.28.0.tar.gz" => ["ports/archives"] do |t|
    sh "wget #{LIBFXSCINTILLA_SOURCE_URI} -O #{t.name}"
  end

  directory "tmp/fxscintilla"
  task "tmp/fxscintilla/fxscintilla-2.28.0/include/Scintilla.iface" => ["tmp/fxscintilla", "ports/archives/fxscintilla-2.28.0.tar.gz"] do
    chdir "tmp/fxscintilla" do
      sh "tar xzf ../../ports/archives/fxscintilla-2.28.0.tar.gz"
    end
  end

  task :scintilla => 'lib/fox16/scintilla.rb'
  file 'lib/fox16/scintilla.rb' => ["tmp/fxscintilla/fxscintilla-2.28.0/include/Scintilla.iface", 'scripts/iface.rb'] do
    ruby "scripts/iface.rb -i tmp/fxscintilla/fxscintilla-2.28.0/include/Scintilla.iface -o lib/fox16/scintilla.rb"
  end

  task :generate_kwargs_lib => 'lib/fox16/kwargs.rb'
  file 'lib/fox16/kwargs.rb' => ['scripts/generate_kwargs_lib.rb'] + Dir.glob('rdoc-sources/*.rb') do
    ruby 'scripts/generate_kwargs_lib.rb'
  end
end
