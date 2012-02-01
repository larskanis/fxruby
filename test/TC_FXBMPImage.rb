require 'fox16'
require 'test/unit'
require 'testcase'

class TC_FXBMPImage < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end

  def test_fileExt
    assert_equal("bmp", FXBMPImage.fileExt)
  end
end
