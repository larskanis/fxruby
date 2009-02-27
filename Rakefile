require 'rubygems'
require 'hoe'

# FXRuby version number
PKG_VERSION = "1.6.19"

Hoe.new("FXRuby", PKG_VERSION) do |p|
  # ... project specific data ...
  p.blog_categories = %w{FXRuby}
  p.clean_globs = ["ext/fox16/Makefile", "ext/fox16/*.o", "ext/fox16/*.bundle", "ext/fox16/mkmf.log", "ext/fox16/conftest.dSYM"]
  p.developer("Lyle Johnson", "lyle@lylejohnson.name")
  p.extra_rdoc_files = ["rdoc-sources", File.join("rdoc-sources", "README.rdoc")]
  p.rubyforge_name = "fxruby"
end

# ... project specific tasks ...
desc "Run SWIG to generate the wrapper files."
task :swig do
  cd "swig-interfaces"
  system %{touch dependencies}
  system %{make depend; make}
  cd ".."
end
