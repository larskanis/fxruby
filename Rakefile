require 'rubygems'
require 'hoe'

# FXRuby version number
PKG_VERSION = "1.6.19"

Hoe.new("FXRuby", PKG_VERSION) do |p|
  # ... project specific data ...
  p.rubyforge_name = "fxruby"
  p.developer("Lyle Johnson", "lyle@lylejohnson.name")
  p.blog_categories = %w{FXRuby}
  p.extra_rdoc_files = ["rdoc-sources", File.join("rdoc-sources", "README.rdoc")]
end

# ... project specific tasks ...
desc "Run SWIG to generate the wrapper files."
task :swig do
  cd "swig-interfaces"
  system %{touch dependencies}
  system %{make depend; make}
  cd ".."
end
