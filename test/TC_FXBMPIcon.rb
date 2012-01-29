require 'fox16'
require 'test/unit'
require 'testcase'

class TC_FXBMPIcon < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end

  def test_fileExt
    assert_equal("bmp", FXBMPIcon.fileExt)
  end
end
