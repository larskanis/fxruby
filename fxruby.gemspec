# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'fox16/version'

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

Gem::Specification.new do |spec|
  spec.name          = "fxruby"
  spec.version       = Fox.fxrubyversion
  spec.authors       = ["Lyle Johnson", "Lars Kanis"]
  spec.email         = ["lyle@lylejohnson.name", "lars@greiz-reinsdorf.de"]

  spec.summary       = %q{FXRuby is the Ruby binding to the FOX GUI toolkit.}
  spec.homepage      = "http://fxruby.org/"
  spec.license       = 'LGPL-2.1'

  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f=~/^fox-includes|^web/
  end
  spec.files += SWIG_MODULES.values.map{|f| File.join("ext/fox16_c", f) }
  spec.files << 'ext/fox16_c/include/inlinestubs.h'
  spec.files << 'ext/fox16_c/swigruby.h'
  spec.files << 'doap.rdf'
  spec.files << 'lib/fox16/kwargs.rb'

  spec.bindir = "exe"
  spec.executables = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/fox16_c/extconf.rb"]
  spec.metadata['msys2_mingw_dependencies'] = 'fox'

  spec.add_runtime_dependency 'mini_portile2', '~> 2.1'
end
