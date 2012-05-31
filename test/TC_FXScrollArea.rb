require 'test/unit'
require 'fox16'
require 'testcase'

class TC_FXScrollArea < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    @scrollArea = FXScrollArea.new(mainWindow)
  end

  def test_nil_parent_raises_argument_error
    assert_raise(ArgumentError){ FXScrollArea.new(nil) }
  end

  def test_position_get
    pos = @scrollArea.position
    assert_instance_of(Array, pos)
    assert_equal(2, pos.size)
    assert_kind_of(Integer, pos[0])
    assert_kind_of(Integer, pos[1])
  end

  def test_setPosition
    @scrollArea.setPosition(0, 0)
  end

  def test_position_move_and_resize
    @scrollArea.position(0, 0, 1, 1)
  end
end
