require 'rubygems'
require 'erb'
require 'date'
require 'rake/extensiontask'
require 'bundler'
require 'bundler/gem_helper'
require './lib/fox16/version.rb'


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
LIBFXSCINTILLA_VERSION            = ENV['LIBFXSCINTILLA_VERSION'] || '3.5.2'
LIBFXSCINTILLA_SOURCE_URI         = "https://github.com/yetanothergeek/fxscintilla/archive/FXSCINTILLA-#{LIBFXSCINTILLA_VERSION.gsub(".","_")}.tar.gz"

SWIG = (RUBY_PLATFORM =~ /mingw/) ? "swig.exe" : "swig"
SWIGFLAGS = "-c++ -ruby -nodefaultdtor -nodefaultctor -w302 -features compactdefaultargs -I../fox-includes"

CLEAN.include( ".config", "ext/fox16_c/Makefile", "ext/fox16_c/*.o", "ext/fox16_c/*.bundle", "ext/fox16_c/mkmf.log", "ext/fox16_c/conftest.dSYM", "ext/fox16_c/swigruby.h*", "ext/fox16_c/librb.c", "ext/fox16_c/include/inlinestubs.h", "ext/fox16_c/*_wrap.cpp", "tmp", "ports/*.installed", "ports/*mingw*" )

CLOBBER.include( "pkg" )
CLOBBER.include( "ports/archives" )

# Tests need to run with binary gems, so that the task doesn't depend on compile
task :test do
  sh "ruby -w -W2 -Ilib test/TS_All.rb -v"
end

task :gem => ["ext/fox16_c/extconf.rb", "fxruby:configure", :build]


gem_spec = Bundler.load_gemspec('fxruby.gemspec')

ext_task = Rake::ExtensionTask.new("fox16_c", gem_spec) do |ext|
  ext.cross_compile = true
  ext.cross_platform = ['x86-mingw32', 'x64-mingw-ucrt', 'x64-mingw32', 'aarch64-mingw-ucrt']
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
      'x64-mingw-ucrt' => ['x86_64-w64-mingw32'],
      'x64-mingw32' => ['x86_64-w64-mingw32'],
      'aarch64-mingw-ucrt' => ['aarch64-w64-mingw32'],
    }

    gemplat = spec.platform.to_s
    platform_host_map[gemplat].each do |host|

      gcc_shared_dlls = %w[libwinpthread-1.dll libgcc_s_dw2-1.dll libgcc_s_sjlj-1.dll libgcc_s_seh-1.dll libstdc++-6.dll]

      dlls = gcc_shared_dlls.select{|dll| File.exist?("ports/#{gemplat}/bin/#{dll}") }
      dlls += [
          "libfxscintilla-25.dll",
          "libFOX-1.6-0.dll",
          "libjpeg-62.dll",
          "libpng16-16.dll",
          "libtiff-6.dll",
          "zlib1.dll",
      ]

      spec.files += dlls.map{|dll| "ports/#{gemplat}/bin/#{dll}" }

      # Bind the external DLLs per manifest to our fox16_c.so ,
      # so that they aren't used by any other extension.
      # Otherwise version dependent incompatibilities can break other gems.
      manif_fname = "ports/#{gemplat}/bin/fxruby-assembly.manifest"
      File.binwrite manif_fname, <<~EOT
        <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
        <assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
        <assemblyIdentity type="win32" name="fxruby-assembly" version="1.0.0.0"></assemblyIdentity>

        #{ dlls.map{|dll| %Q{<file name="#{dll}"/>} }.join }
        </assembly>
      EOT
      spec.files += [manif_fname]

      # Windows manifest files don't allow file paths but only file names.
      # Therefore move our fox16_c.so into the bin directory
      # and change to a ruby version dependent file name like "4_0_fox16_c.so".
      exts, spec.files = spec.files.partition{|f| File.fnmatch("lib/?.?/fox16_c.so", f) }
      spec.files += exts.map do |f|
        new = "ports/#{gemplat}/bin/#{File.basename(File.dirname(f)).gsub(".","_")}_#{File.basename(f)}"
        mv("tmp/#{gemplat}/stage/#{f}", new)
        new
      end

      unless ENV['FXRUBY_MINGW_DEBUG']
        dlls.each do |dll|
          task "ports/#{gemplat}/bin/#{dll}" do |t|
            sh "#{host}-strip", t.name
          end
        end
      end
    end
  end

  FoxGemHelper.install_tasks
  Bundler::GemHelper.instance.cross_platforms = ext.cross_platform
end

namespace :gem do
  ext_task.cross_platform.each do |plat|
    desc "Build the windows binary gems"
    multitask 'windows' => plat

    task 'prepare' do
      require 'rake_compiler_dock'
      sh "bundle package"
    end

    desc "Build a binary gem for platform #{plat}"
    task plat => ['gem', 'prepare'] do
      debug = "FXRUBY_MINGW_DEBUG=#{ENV['FXRUBY_MINGW_DEBUG'].inspect}" if ENV['FXRUBY_MINGW_DEBUG']
      RakeCompilerDock.sh <<-EOT, platform: plat
        sudo apt-get update &&
        sudo apt-get install -y yasm libtool m4 automake &&
        sudo chmod go+w /usr/local/rbenv/versions/4.0.0/lib/ruby/gems/4.0.0/plugins -R &&
        bundle config set without test &&
        bundle install --local &&
        rake native:#{plat} pkg/#{ext_task.gem_spec.full_name}-#{plat}.gem MAKE=\"nice make V=1 VERBOSE=1 -j `nproc`\" #{debug}  RUBY_CC_VERSION=#{RakeCompilerDock.ruby_cc_version("~>4.0", "~>3.0")}
      EOT
    end
  end
end

$matched_gsubs = Hash.new { |h,e| h[e] = [] }
def checked_gsub!(str, from, to)
  old = str.dup
  n = str.gsub!(from, to)

  $matched_gsubs[[from, to]] << (old != str)

  n
end

namespace :swig do
  def patch_swigruby(line)

    # Allow Truffleruby-22.1.0 to compile the sources without fxscintilla.
    # Unfortunately Truffleruby still fails with various runtime errors.
    if RUBY_ENGINE == "truffleruby"
      checked_gsub! line,  '#include <ruby.h>', <<-EOT
        #include <ruby.h>
        #define rb_define_virtual_variable(x,y,z)
      EOT

      checked_gsub! line, 'rb_define_readonly_variable("$swig_runtime_data_type_pointer" SWIG_RUNTIME_VERSION SWIG_TYPE_TABLE_NAME, &swig_runtime_data_type_pointer);', <<-EOT
        if (rb_gv_get("$swig_runtime_data_type_pointer" SWIG_RUNTIME_VERSION SWIG_TYPE_TABLE_NAME) == RUBY_Qnil) {
          rb_gv_set("$swig_runtime_data_type_pointer" SWIG_RUNTIME_VERSION SWIG_TYPE_TABLE_NAME, swig_runtime_data_type_pointer);
        }
      EOT
    end

    line
  end

  def sed(wrapper_src_file_name)
    puts "Update #{wrapper_src_file_name}"

    line = File.read(wrapper_src_file_name)
    checked_gsub!(line, /static VALUE mCore;/, "VALUE mCore;")
    checked_gsub!(line, /mCore = rb_define_module\("Core"\)/, "mFox = rb_define_module(\"Fox\")")
    checked_gsub!(line, /mCore/, "mFox")
    # checked_gsub!(line, /static VALUE m(Dc|Dialogs|Frames|Iconlist|Icons|Image|Label|Layout|List|Mdi|Menu|Fx3d|Scintilla|Table|Text|Treelist|Ui);/, '')
    checked_gsub!(line, /m(Dc|Dialogs|Frames|Iconlist|Icons|Image|Label|Layout|List|Mdi|Menu|Fx3d|Scintilla|Table|Text|Treelist|Ui) = rb_define_module.*/, '')
    checked_gsub!(line, /rb_require.*/, '')
    checked_gsub!(line, /m(Dc|Dialogs|Frames|Iconlist|Icons|Image|Label|Layout|List|Mdi|Menu|Fx3d|Scintilla|Table|Text|Treelist|Ui),/, "mFox,")

    line = patch_swigruby(line)

    File.write(wrapper_src_file_name, line)
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
  file "ext/fox16_c/swigruby.h.orig" do |task|
    puts "generate #{task.name}"
    system "#{SWIG} -ruby -external-runtime #{task.name}"
  end

  file "ext/fox16_c/swigruby.h"=>["ext/fox16_c/swigruby.h.orig"] do |task|
    puts "generate #{task.name}"
    text = File.read(task.prerequisites[0])
    text = patch_swigruby(text)
    File.write(task.name, text)
  end

  desc "Run SWIG to generate the wrapper files."
  multitask :swig => [:swigruby_h] + SWIG_MODULES.map{|ifile, cppfile| File.join("ext/fox16_c", cppfile) }
end

# add dependencies for compile *.i to *_wrap.cpp
SWIG_MODULES.each do |ifile, cppfile|
  cppfile_path = File.join("ext/fox16_c", cppfile)

  file cppfile_path => [ifile, 'macros.i', 'common.i', 'fxdefs.i', 'ruby-typemaps.i',
                        'markfuncs.i', 'exceptions.i', 'freefuncs.i', 'macros.i', 'handlers.i'
                       ].map{|f| File.join("swig-interfaces", f) } do |task|
    swig(File.join("swig-interfaces", ifile), cppfile_path)
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
  file "ports/archives/FXSCINTILLA-3_5_2.tar.gz" => ["ports/archives"] do |t|
    sh "wget #{LIBFXSCINTILLA_SOURCE_URI} -O #{t.name}"
  end

  directory "tmp/fxscintilla"
  task "tmp/fxscintilla/fxscintilla-FXSCINTILLA-3_5_2/include/Scintilla.iface" => ["tmp/fxscintilla", "ports/archives/FXSCINTILLA-3_5_2.tar.gz"] do
    chdir "tmp/fxscintilla" do
      sh "tar xzf ../../ports/archives/FXSCINTILLA-3_5_2.tar.gz"
    end
  end

  task :scintilla => 'lib/fox16/scintilla.rb'
  file 'lib/fox16/scintilla.rb' => ["tmp/fxscintilla/fxscintilla-FXSCINTILLA-3_5_2/include/Scintilla.iface", 'scripts/iface.rb'] do
    ruby "scripts/iface.rb -i tmp/fxscintilla/fxscintilla-FXSCINTILLA-3_5_2/include/Scintilla.iface -o lib/fox16/scintilla.rb"
  end

  task :generate_kwargs_lib => 'lib/fox16/kwargs.rb'
  file 'lib/fox16/kwargs.rb' => ['scripts/generate_kwargs_lib.rb'] + Dir.glob('rdoc-sources/*.rb') do
    ruby 'scripts/generate_kwargs_lib.rb'
  end
end

namespace :docs do
  desc "Update the docs in git for github pages"
  task :update do
    rm_rf 'docs'
    sh 'git', 'rm', '-rfq', 'docs' do end
    sh 'yardoc', '--output-dir', 'docs'
    sh 'git', 'add', 'docs'
  end
end

task :compile do
  never_matched = $matched_gsubs.select { |_key, matches| matches.all?(false) }

  never_matched.each do |(from, to), |
    warn "gsub didn't match on\n  from: #{from}\n  to: #{to}"
  end
end
