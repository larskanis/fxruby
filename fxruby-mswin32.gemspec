# Source gem spec file

require 'rubygems'

# These library files aren't ready for distribution yet.
COOKER_LIBS = %w{acceltable.rb bitmapview.rb canvas.rb html.rb tkcompat.rb}

# These example programs aren't ready for distribution yet.
COOKER_EXAMPLES = %w{canvasdemo.rb WhatAQuietStiff.rb examples.rb gdchart.rb gembrowser.rb rapt-gui.rb}

PKG_FILES = [
  "ANNOUNCE",
  "ChangeLog",
  "LICENSE",
  "README",
  "index.html",
  "doc/*.html",
  "doc/images/*.png",
  "examples/README",
  "examples/*.rb",
  "examples/*.xml",
  "examples/icons/*.png",
  "examples/icons/*.ico",
  "examples/textedit/*.rb",
  "lib/fox16/*.rb",
  "ext/fox16/fox14.so",
  "tests/README",
  "tests/*.rb",
  "tests/*.ps",
  "web/*.html",
  "web/*.css",
  "web/art/*.png",
  "web/art/*.gif",
  "rdoc-sources/*.rb",
  "rdoc-sources/README.rdoc"
]

spec = Gem::Specification.new do |s|
  s.name = 'fxruby'
  s.version = "1.6.0"
  s.platform = Gem::Platform::WIN32
  s.description = "FXRuby is the Ruby binding to the FOX GUI toolkit."
  s.requirements << "FOX library version 1.6.0 or higher"
  s.summary = "FXRuby is the Ruby binding to the FOX GUI toolkit."

  s.files = []
  PKG_FILES.each do |pat|
    s.files += Dir.glob(pat).delete_if { |item|
      COOKER_LIBS.include?(File.basename(item)) || COOKER_EXAMPLES.include?(File.basename(item))
    }
  end

  s.require_paths = ['ext/fox16', 'lib']
  s.autorequire = 'fox16'

  s.has_rdoc = true
  s.rdoc_options = [
                    '--main', File.join('rdoc-sources', 'README.rdoc'),
                    '--exclude', 'ext/fox16'
                   ]
  s.extra_rdoc_files = [
                        'rdoc-sources',
                        File.join('rdoc-sources', 'README.rdoc')
                       ]

  s.test_suite_file = "tests/TS_All.rb"

  s.author = "Lyle Johnson"
  s.email = "lyle@knology.net"
  s.homepage = "http://www.fxruby.org"
end

