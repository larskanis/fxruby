begin
  require 'fox16_c'
rescue LoadError
  # If it's a Windows binary gem, try the <major>.<minor> subdirectory
  if RUBY_PLATFORM =~/(mswin|mingw)/i
    major_minor = RUBY_VERSION[ /^(\d+\.\d+)/ ] or
      raise "Oops, can't extract the major/minor version from #{RUBY_VERSION.dump}"

    add_dll_path = proc do |path, &block|
      begin
        require 'ruby_installer/runtime'
        RubyInstaller::Runtime.add_dll_directory(path, &block)
      rescue LoadError
        old_path = ENV['PATH']
        ENV['PATH'] = "#{path};#{old_path}"
        block.call
        ENV['PATH'] = old_path
      end
    end

    # Temporary add this directory for DLL search, so that bundled DLLs can be found.
    ports_dir = RbConfig::CONFIG["host"].gsub('i686-pc-mingw32') do
      major_minor < '2.0' ? 'i586-mingw32msvc' : 'i686-w64-mingw32'
    end
    ports_bin = File.expand_path("../../ports/#{ports_dir}/bin", __FILE__)
    add_dll_path.call(ports_bin) do
      require "#{major_minor}/fox16_c"
    end
  else
    raise
  end
end

require "fox16/core"
require "fox16/dict"
require "fox16/settings"
require "fox16/iterators"
require "fox16/keys"
require "fox16/aliases"
require "fox16/responder2"
require "fox16/glgroup"
require "fox16/execute_nonmodal"
require "fox16/version"
require "fox16/kwargs"
require "fox16/exceptions_for_fxerror"
require "fox16/thread"
