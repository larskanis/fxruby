require 'rubygems'
require 'hoe'
require 'erb'
require './lib/fox16/version.rb'

# Some constants we'll need
PKG_VERSION = Fox.fxrubyversion
FXRUBY_HOME_URL = "http://www.fxruby.org"
FOX_HOME_URL    = "http://www.fox-toolkit.com"

Hoe.new("FXRuby", PKG_VERSION) do |p|
  # ... project specific data ...
  p.blog_categories = %w{FXRuby}
  p.clean_globs = ["ext/fox16/Makefile", "ext/fox16/*.o", "ext/fox16/*.bundle", "ext/fox16/mkmf.log", "ext/fox16/conftest.dSYM"]
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
  cd "swig-interfaces"
  system %{touch dependencies}
  system %{make depend; make}
  cd ".."
end
