require 'test/unit'
require 'fox16'
require 'testcase'

class TC_FXWindow < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    @window = FXWindow.new(mainWindow)
  end

  def test_width_accessor
    pos = @window.width
    assert_kind_of(Integer, pos)
    @window.width = pos + 1
    assert_equal(pos + 1, @window.width)
    @window.width = pos + 2.7
    assert_equal(pos + 2, @window.width)
    assert_kind_of(Integer, @window.width)
  end

  def test_width_invalid
    assert_raise(TypeError){ @window.width = nil }
  end
end
