require 'fox16'
require 'test/unit'

if (l=ENV["fxTraceLevel"].to_i) > 0
  Fox.fxTraceLevel = l
end

if __FILE__ == $0
  testdir = File.expand_path("..", __FILE__)
  $: << testdir
  Dir.chdir(testdir) do
    Dir.glob("TC_*.rb").each do |testcase|
      require "#{testcase}"
    end
  end
end
