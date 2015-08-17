require 'test/unit'
require 'testcase'
require 'fox16'

class TC_FXMenuCheck < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    @menuCheck = FXMenuCheck.new(mainWindow, "menuCheck")
  end

  def test_setCheck_TRUE
    @menuCheck.check = Fox::TRUE
    assert_equal(Fox::TRUE, @menuCheck.checkState)
    assert(@menuCheck.checked?)
    assert(!@menuCheck.unchecked?)
    assert(!@menuCheck.maybe?)
  end

  def test_setCheck_FALSE
    @menuCheck.check = Fox::FALSE
    assert_equal(Fox::FALSE, @menuCheck.checkState)
    assert(!@menuCheck.checked?)
    assert(@menuCheck.unchecked?)
    assert(!@menuCheck.maybe?)
  end

  def test_setCheck_MAYBE
    @menuCheck.check = Fox::MAYBE
    assert_equal(Fox::MAYBE, @menuCheck.checkState)
    assert(!@menuCheck.checked?)
    assert(!@menuCheck.unchecked?)
    assert(@menuCheck.maybe?)
  end

  def test_setCheck_true
    @menuCheck.check = true
    assert_equal(Fox::TRUE, @menuCheck.checkState)
    assert(@menuCheck.checked?)
    assert(!@menuCheck.unchecked?)
    assert(!@menuCheck.maybe?)
  end

  def test_setCheck_false
    @menuCheck.check = false
    assert_equal(Fox::FALSE, @menuCheck.checkState)
    assert(!@menuCheck.checked?)
    assert(@menuCheck.unchecked?)
    assert(!@menuCheck.maybe?)
  end
end
