require 'test/unit'
require 'fox16'
require 'testcase'

include Fox

class TC_FXApp < TestCase
  def setup
    super(self.class.name)
  end
  def test_initialized
    assert(app.initialized?)
  end
end

