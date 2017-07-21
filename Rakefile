require 'rubygems'
require 'erb'
require 'date'
require 'rake/extensiontask'
require 'bundler'
require 'bundler/gem_helper'
require './lib/fox16/version.rb'

# Use forked process for chdir'ed environment, to allow parallel execution with rake -m
module FileUtils
  alias unforked_fileutils_cd cd
  def cd(dir, options={}, &block)
    raise "chdir called without block" unless block_given?
    begin
      pid = Process.waitpid(fork{ unforked_fileutils_cd(dir, options, &block) })
      raise "Error in subprocess" if $?.exitstatus != 0
    rescue NotImplementedError
      unforked_fileutils_cd(dir, options, &block)
    end
  end
  module_function :cd
  alias chdir cd
  module_function :chdir
end


class FoxGemHelper < Bundler::GemHelper
  attr_accessor :cross_platforms

  def install
    super

    task "release:guard_clean" => ["release:update_history"]

    task "release:update_history" do
      update_history
    end

    task "release:rubygem_push" => ["gem:windows"]
  end

  def hfile
    "History.md"
  end

  def headline
    '([^\w]*)(\d+\.\d+\.\d+(?:\.\w+)?)([^\w]+)([2Y][0Y][0-9Y][0-9Y]-[0-1M][0-9M]-[0-3D][0-9D])([^\w]*|$)'
  end

  def reldate
    Time.now.strftime("%Y-%m-%d")
  end

  def update_history
    hin = File.read(hfile)
    hout = hin.sub(/#{headline}/) do
      raise "#{hfile} isn't up-to-date for version #{version}" unless $2==version.to_s
      $1 + $2 + $3 + reldate + $5
    end
    if hout != hin
      Bundler.ui.confirm "Updating #{hfile} for release."
      File.write(hfile, hout)
      Rake::FileUtilsExt.sh "git", "commit", hfile, "-m", "Update release date in #{hfile}"
    end
  end

  def tag_version
    Bundler.ui.confirm "Tag release with annotation:"
    m = File.read(hfile).match(/(?<annotation>#{headline}.*?)#{headline}/m) || raise("Unable to find release notes in #{hfile}")
    Bundler.ui.info(m[:annotation].gsub(/^/, "    "))
    IO.popen(["git", "tag", "--file=-", version_tag], "w") do |fd|
      fd.write m[:annotation]
    end
    yield if block_given?
  rescue
    Bundler.ui.error "Untagging #{version_tag} due to error."
    sh_with_code "git tag -d #{version_tag}"
    raise
  end

  def rubygem_push(path)
    cross_platforms.each do |ruby_platform|
      super(path.gsub(/\.gem\z/, "-#{ruby_platform}.gem"))
    end
    super(path)
  end
end

# Some constants we'll need
LIBFXSCINTILLA_VERSION            = ENV['LIBFXSCINTILLA_VERSION'] || '2.28.0'
LIBFXSCINTILLA_SOURCE_URI         = "http://download.savannah.gnu.org/releases/fxscintilla/fxscintilla-#{LIBFXSCINTILLA_VERSION}.tar.gz"

SWIG = (RUBY_PLATFORM =~ /mingw/) ? "swig.exe" : "swig"
SWIGFLAGS = "-c++ -ruby -nodefaultdtor -nodefaultctor -w302 -features compactdefaultargs -I../fox-includes"

CLEAN.include( ".config", "ext/fox16_c/Makefile", "ext/fox16_c/*.o", "ext/fox16_c/*.bundle", "ext/fox16_c/mkmf.log", "ext/fox16_c/conftest.dSYM", "ext/fox16_c/swigruby.h", "ext/fox16_c/librb.c", "ext/fox16_c/include/inlinestubs.h", "ext/fox16_c/*_wrap.cpp", "tmp", "ports/*.installed", "ports/*mingw32*" )

CLOBBER.include( "pkg" )

# Make sure extension is built before tests are run
task :test => [:compile] do
  sh "ruby -w -W2 -Ilib test/TS_All.rb -v"
end

task :gem => [:compile, :build]


gem_spec = Bundler.load_gemspec('fxruby.gemspec')

Rake::ExtensionTask.new("fox16_c", gem_spec) do |ext|
  ext.cross_compile = true
  ext.cross_platform = ['x86-mingw32', 'x64-mingw32']
  # Enable FXTRACE and FXASSERT for 'rake compile'
  ext.config_options << "--enable-debug"

  ext.cross_config_options += [
      "--enable-win32-cross",
      "--with-fxscintilla",
    ]
  ext.cross_config_options << "--enable-debug" if ENV['FXRUBY_MINGW_DEBUG']

  # Add dependent DLLs to the cross gems
  ext.cross_compiling do |spec|
    # The fat binary gem doesn't depend on the fox package, since it bundles the libraries.
    spec.metadata.delete('msys2_mingw_dependencies')

    platform_host_map =  {
      'x86-mingw32' => ['i686-w64-mingw32'],
      'x64-mingw32' => ['x86_64-w64-mingw32'],
    }

    gemplat = spec.platform.to_s
    platform_host_map[gemplat].each do |host|

      gcc_shared_dlls = %w[libwinpthread-1.dll libgcc_s_dw2-1.dll libgcc_s_sjlj-1.dll libgcc_s_seh-1.dll libstdc++-6.dll]

      dlls = gcc_shared_dlls.select{|dll| File.exist?("ports/#{host}/bin/#{dll}") }
      dlls += [
          "libfxscintilla-20.dll",
          "libFOX-1.6-0.dll",
          "libjpeg-62.dll",
          "libpng16-16.dll",
          "libtiff-5.dll",
          "zlib1.dll",
      ]

      spec.files += dlls.map{|dll| "ports/#{host}/bin/#{dll}" }

      unless ENV['FXRUBY_MINGW_DEBUG']
        dlls.each do |dll|
          task "ports/#{host}/bin/#{dll}" do |t|
            sh "x86_64-w64-mingw32-strip", t.name
          end
        end
      end
    end
  end

  FoxGemHelper.install_tasks
  Bundler::GemHelper.instance.cross_platforms = ext.cross_platform
end

# To reduce the gem file size strip mingw32 dlls before packaging
unless ENV['FXRUBY_MINGW_DEBUG']
  ENV['RUBY_CC_VERSION'].to_s.split(':').each do |ruby_version|
    task "tmp/x86-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so" do |t|
      sh "i686-w64-mingw32-strip -S tmp/x86-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so"
    end

    task "tmp/x64-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so" do |t|
      sh "x86_64-w64-mingw32-strip -S tmp/x64-mingw32/stage/lib/#{ruby_version[/^\d+\.\d+/]}/fox16_c.so"
    end
  end
end

desc "Build the windows binary gems"
task 'gem:windows' => 'gem' do
  require 'rake_compiler_dock'

  sh "bundle package"
  debug = "FXRUBY_MINGW_DEBUG=#{ENV['FXRUBY_MINGW_DEBUG'].inspect}" if ENV['FXRUBY_MINGW_DEBUG']
  RakeCompilerDock.sh <<-EOT
    sudo apt update &&
    sudo apt install yasm &&
    bundle --local --without=test &&
    rake cross native gem MAKE=\"nice make V=1 -j `nproc`\" #{debug}
  EOT
end

# Set environment variable SWIG_LIB to
# c:/ruby-1.8.6-p383-preview2/devkit/msys/1.0.11/usr/local/share/swig/1.3.22
# before running swig on MinGW.
namespace :swig do
  def sed(wrapper_src_file_name)
    puts "Update #{wrapper_src_file_name}"
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

  def add_with_fxscintilla_cond(file)
    puts "Update #{file} for fxscintilla"
    content = File.binread(file)
    content = "#ifdef WITH_FXSCINTILLA\n" + content + "#endif /* WITH_FXSCINTILLA */\n"
    File.binwrite(file, content)
  end

  def swig(swig_interface_file_name, wrapper_src_file_name)
    cmd = "#{SWIG} #{SWIGFLAGS} -o #{wrapper_src_file_name} #{swig_interface_file_name}"
    puts cmd
    system cmd

    # Do our own wrapper file modifications:
    sed wrapper_src_file_name
    add_with_fxscintilla_cond(wrapper_src_file_name) if ["scintilla_wrap.cpp"].include?(File.basename(wrapper_src_file_name))
  end

  task :swigruby_h => ["ext/fox16_c/swigruby.h"]
  file "ext/fox16_c/swigruby.h" do |task|
    puts "generate #{task.name}"
    system "#{SWIG} -ruby -external-runtime #{task.name}"
  end

  desc "Run SWIG to generate the wrapper files."
  multitask :swig => [:swigruby_h] + SWIG_MODULES.map{|ifile, cppfile| File.join("ext/fox16_c", cppfile) }

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

  file "ext/fox16_c/extconf.rb" => ['ext/fox16_c/impl.cpp', 'ext/fox16_c/include/inlinestubs.h', 'swig:swig']


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
