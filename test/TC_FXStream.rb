require 'test/unit'
require 'fox16'
require 'testcase'

class TC_FXStream < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end
end
