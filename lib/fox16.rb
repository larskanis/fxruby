if RUBY_PLATFORM =~ /(mswin|mingw)/i
  require "#{RUBY_VERSION.sub(/\.\d+$/, '')}/fox16.so"
elsif RUBY_PLATFORM =~ /darwin/
  require "fox16.bundle"
else
  require "fox16.so"
end

