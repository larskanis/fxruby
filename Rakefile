require 'date'
require 'rake/gempackagetask'
require 'rake/rdoctask'
require 'rake/testtask'

# FXRuby version number
PKG_VERSION = "1.6.19"

# Minimum version of FOX required for compatibility
FOX_VERSION = "1.6.0"

# Path to local installation of FOX (Windows only)
FOX_INSTALL_DIR = "e:\\src\\fox-1.6.33"

# Path to local installation of FXScintilla (Windows only)
FXSCINTILLA_INSTALL_DIR = "c:\\src\\fxscintilla"

# Path to local installation of InnoSetup command-line compiler
ISCC = "C:\\Progra~1\\InnoSe~1\\ISCC.exe"

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

desc "Run the test battery."
task :check do
  cd "tests"
  ruby %{-I../ext/fox16 -I../lib TS_All.rb}
end

desc "Run SWIG to generate the wrapper files."
task :swig do
  cd "swig-interfaces"
  system %{touch dependencies}
  system %{make depend; make}
  cd ".."
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

desc "Upload the RDocs"
task :upload_rdoc do
# system %{scp -Cqr doc/api lyle@rubyforge.org:/var/www/gforge-projects/fxruby/1.6/doc}
  host = "lyle@rubyforge.org"
  remote_dir = "/var/www/gforge-projects/fxruby/doc/api"
  local_dir = 'doc/api'
  sh %{rsync -av --delete #{local_dir}/ #{host}:#{remote_dir}}
end

desc "Upload release files to RubyForge"
task :rubyforge do
  require 'rubyforge'
  rubyforge = RubyForge.new
  rubyforge.login
  if PLATFORM =~ /mswin32/
    rubyforge.userconfig['processor_id'] = 'i386'
    rubyforge.add_file    "fxruby", "FXRuby 1.6", PKG_VERSION, "fxruby-#{PKG_VERSION}-mswin32.gem"
    rubyforge.add_file    "fxruby", "FXRuby 1.6", PKG_VERSION, "FXRuby-#{PKG_VERSION}-ruby186.exe"
  else
    rubyforge.add_release "fxruby", "FXRuby 1.6", PKG_VERSION, "FXRuby-#{PKG_VERSION}.tar.gz"
    rubyforge.add_file    "fxruby", "FXRuby 1.6", PKG_VERSION, "fxruby-#{PKG_VERSION}.gem"
  end
# rubyforge add_release      fxruby "FXRuby 1.6" "1.6.9" FXRuby-1.6.9.tar.gz
# rubyforge add_file         fxruby "FXRuby 1.6" "1.6.9" fxruby-1.6.9.gem
# rubyforge add_file -o i386 fxruby "FXRuby 1.6" "1.6.9" fxruby-1.6.9-mswin32.gem
# rubyforge add_file -o i386 fxruby "FXRuby 1.6" "1.6.9" FXRuby-1.6.9-ruby186.exe
end

desc "Tag this release in Subversion"
task :tag do
  require 'rexml/document'
  doc = REXML::Document.new(`svn info --xml`)
  branch = doc.get_elements("/info/entry/url").first.text
  root   = doc.get_elements("/info/entry/repository/root").first.text
  tag = root + "/tags/REL-#{PKG_VERSION}"
  sh %{svn copy -m "Created tag for version #{PKG_VERSION}" #{branch} #{tag}}
end

desc "Generate all of the documentation files."
task :doc do
  cd "doc"
  system %{make}
  cd ".."
end

#
# This task (:rdoc) provides its own description and
# also creates the clobber_rdoc and rerdoc tasks.
#
Rake::RDocTask.new do |rdoc|
  rdoc.rdoc_dir = "doc/api"
  rdoc.main = "rdoc-sources/README.rdoc"
  rdoc.rdoc_files.add("rdoc-sources/README.rdoc")
  rdoc.rdoc_files.add("rdoc-sources/*.rb")
  rdoc.rdoc_files.add("lib/fox16/accel_table.rb",
                      "lib/fox16/calendar.rb",
                      "lib/fox16/chore.rb",
                      "lib/fox16/core.rb",
                      "lib/fox16/execute_nonmodal.rb",
                      "lib/fox16/glgroup.rb",
                      "lib/fox16/glshapes.rb",
                      "lib/fox16/input.rb",
                      "lib/fox16/iterators.rb",
                      "lib/fox16/keys.rb",
                      "lib/fox16/responder2.rb",
                      "lib/fox16/scintilla.rb",
                      "lib/fox16/signal.rb",
                      "lib/fox16/splashscreen.rb",
                      "lib/fox16/timeout.rb",
                      "lib/fox16/undolist.rb",
                      "lib/fox16/version.rb"
                     )
end

task :docs => [:doc, :rdoc] do
end

desc "Install it."
task :install => [:build] do
  ruby "install.rb install"
end

desc "Clean"
task :clean do
  rm_rf "ext/fox16/Makefile"
  rm_rf FileList["ext/fox16/*.o"]
  rm_rf FileList["ext/fox16/*.bundle"]
  rm_rf "ext/fox16/mkmf.log"
  rm_rf "ext/fox16/conftest.dSYM"
  ruby "install.rb clean"
end

def make_impl
  cd "ext/fox16"
  ruby "make_impl.rb"
  cd "../.."
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

task :scintilla do
  ruby "scripts/iface.rb -i ~/src/fxscintilla/scintilla/include/Scintilla.iface -o lib/fox16/scintilla.rb"
end

def setversions(filename)
  substitutions = {
    "@@DATE@@" => "#{Date.today}",
    "@@FOX_VERSION@@" => FOX_VERSION,
    "@@FXRUBY_VERSION@@" => PKG_VERSION,
    "@@FXRUBY_HOME_URL@@" => "http://www.fxruby.org",
    "@@FOX_HOME_URL@@" => "http://www.fox-toolkit.com",
  }
  text = nil
  File.open(filename + ".in", "rb") do |inp|
    text = inp.read
  end
  substitutions.each { |pattern, replacement|
    text.gsub!(pattern, replacement)
  }
  File.open(filename, "wb") do |out|
    out.write(text)
  end
end

desc "Set versions"
task :setversions => [ :create_installer_scripts ] do
  setversions("Makefile")
  setversions("pre-config.rb")
  setversions("ext/fox16/extconf.rb")
  setversions("FXRuby-ruby1.8.6-i386-msvcrt.iss")
  setversions("lib/fox16/version.rb")
  setversions("doap.rdf")
  setversions("scripts/make-installers.rb")
end

desc "Create INNO Setup Installer Scripts from Template"
task :create_installer_scripts do
  output_filenames = {
    "FXRuby-ruby1.8.6-i386-msvcrt.iss.in" =>  ["1.8", "ruby186", "i386-msvcrt"]
  }

  output_filenames.each do |output_filename, info|
    File.open("scripts/FXRuby.iss.in", "rb") do |input_file|
      contents = input_file.read
      contents.gsub!(/@@RUBY_VERSION@@/, info[0])
      contents.gsub!(/@@RUBYVER@@/, info[1])
      contents.gsub!(/@@TARGET@@/, info[2])
      File.open(output_filename, "wb") do |output_file|
        output_file.write(contents)
      end
    end
  end
end

# These library files aren't ready for distribution yet.
COOKER_LIBS = %w{acceltable.rb bitmapview.rb canvas.rb html.rb tkcompat.rb}

# These example programs aren't ready for distribution yet.
COOKER_EXAMPLES = %w{canvasdemo.rb WhatAQuietStiff.rb examples.rb gdchart.rb gembrowser.rb rapt-gui.rb rmagick.rb tablenew.rb}

# Return the Gem specification for the source Gem
def create_gemspec
  pkg_files = [
  "ANNOUNCE",
	"LICENSE",
	"README",
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

  Gem::Specification.new do |s|
    s.name = 'fxruby'
    s.version = PKG_VERSION
    s.description = "FXRuby is the Ruby binding to the FOX GUI toolkit."
    s.requirements << "FOX library version 1.6.0 or higher"
    s.summary = "FXRuby is the Ruby binding to the FOX GUI toolkit."

    s.files = []
    pkg_files.each do |pat|
      s.files += Dir.glob(pat).delete_if { |item|
        COOKER_LIBS.include?(File.basename(item)) || COOKER_EXAMPLES.include?(File.basename(item))
      }
    end
    
    s.require_paths = ['ext/fox16', 'lib']

    s.has_rdoc = true
    s.rdoc_options = [
                    '--main', File.join('rdoc-sources', 'README.rdoc'),
                    '--exclude', 'ext/fox16',
                    '--exclude', %r{acceltable|aliases|bitmapview|canvas|html|kwargs|missingdep|responder|tkcompat}
                   ]
    s.extra_rdoc_files = [
                        'rdoc-sources',
                        File.join('rdoc-sources', 'README.rdoc')
                       ]

    s.test_suite_file = "tests/TS_All.rb"

    s.author = "Lyle Johnson"
    s.email = "lyle.johnson@gmail.com"
    s.homepage = "http://www.fxruby.org"
  end
end

desc "Build source Gem"
task :build_src_gem do
  spec = create_gemspec
  spec.platform = Gem::Platform::RUBY
  spec.files += [
    "ext/fox16/MANIFEST",
    "ext/fox16/extconf.rb"
    ] +
    Dir.glob("ext/fox16/*.c") +
    Dir.glob("ext/fox16/*.cpp") +
    Dir.glob("ext/fox16/include/*.h")
  spec.extensions = ["ext/fox16/extconf.rb"]
  Gem::Builder.new(spec).build
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

Rake::TestTask.new do |t|
  t.libs << "tests"
  t.test_files = FileList["tests/TC_*.rb"]
  t.verbose = true
end

# Default task is build
task :default => [:build] do
end

