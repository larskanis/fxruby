require 'fox16'
require 'test/unit'
require 'testcase'

class TC_FXXBMImage < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end

  def test_fileExt
    assert_equal("xbm", FXXBMImage.fileExt)
  end
end
