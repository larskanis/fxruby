require 'fox16'
require 'test/unit'

if __FILE__ == $0
  $: << File.dirname(__FILE__)
  Dir.glob("TC_*.rb").each do |testcase|
    require "#{testcase}"
  end
end
