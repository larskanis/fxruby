begin
  require 'fox16_c'
rescue LoadError
  # If it's a Windows binary gem, try the <major>.<minor> subdirectory
  if RUBY_PLATFORM =~/(mswin|mingw)/i
    major_minor = RUBY_VERSION[ /^(\d+\.\d+)/ ] or
      raise "Oops, can't extract the major/minor version from #{RUBY_VERSION.dump}"

    # Set the PATH environment variable, so that the DLLs can be found.
    old_path = ENV['PATH']
    begin
      ports_dir = RbConfig::CONFIG["host"].gsub('i686-pc-mingw32') do
        major_minor < '2.0' ? 'i586-mingw32msvc' : 'i686-w64-mingw32'
      end
      ENV['PATH'] = "#{File.expand_path("../../ports/#{ports_dir}/bin", __FILE__)};#{old_path}"
      require "#{major_minor}/fox16_c"
    ensure
      ENV['PATH'] = old_path
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
