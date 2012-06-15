if RUBY_PLATFORM =~ /(mswin|mingw)/i
  require "#{RUBY_VERSION.sub(/\.\d+$/, '')}/fox16.so"
elsif RUBY_PLATFORM =~ /darwin/
  require "fox16.bundle"
else
  require "fox16.so"
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
