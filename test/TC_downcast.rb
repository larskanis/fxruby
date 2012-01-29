require 'test/unit'
require 'fox16'
require 'testcase'

class TC_downcast < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end
  def test_downcast
    fs = FXFileSelector.new(mainWindow)
    assert_kind_of(FXHorizontalFrame, fs.first)
  end
end
