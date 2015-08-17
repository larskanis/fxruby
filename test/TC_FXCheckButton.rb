require 'test/unit'
require 'testcase'
require 'fox16'

class TC_FXCheckButton < Fox::TestCase
  include Fox

  def setup
    super("TC_FXCheckButton")
    @checkButton = FXCheckButton.new(mainWindow, "cbText")
  end

  def test_setCheck_TRUE
    @checkButton.check = Fox::TRUE
    assert_equal(Fox::TRUE, @checkButton.checkState)
    assert(@checkButton.checked?)
    assert(!@checkButton.unchecked?)
    assert(!@checkButton.maybe?)
  end

  def test_setCheck_FALSE
    @checkButton.check = Fox::FALSE
    assert_equal(Fox::FALSE, @checkButton.checkState)
    assert(!@checkButton.checked?)
    assert(@checkButton.unchecked?)
    assert(!@checkButton.maybe?)
  end

  def test_setCheck_MAYBE
    @checkButton.check = Fox::MAYBE
    assert_equal(Fox::MAYBE, @checkButton.checkState)
    assert(!@checkButton.checked?)
    assert(!@checkButton.unchecked?)
    assert(@checkButton.maybe?)
  end

  def test_setCheck_true
    @checkButton.check = true
    assert_equal(Fox::TRUE, @checkButton.checkState)
    assert(@checkButton.checked?)
    assert(!@checkButton.unchecked?)
    assert(!@checkButton.maybe?)
  end

  def test_setCheck_false
    @checkButton.check = false
    assert_equal(Fox::FALSE, @checkButton.checkState)
    assert(!@checkButton.checked?)
    assert(@checkButton.unchecked?)
    assert(!@checkButton.maybe?)
  end
end
