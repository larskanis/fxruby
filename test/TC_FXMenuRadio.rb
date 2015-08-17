require 'test/unit'
require 'testcase'
require 'fox16'

class TC_FXMenuRadio < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    @menuRadio = FXMenuRadio.new(mainWindow, "menuRadio")
  end

  def test_setCheck_TRUE
    @menuRadio.check = Fox::TRUE
    assert_equal(Fox::TRUE, @menuRadio.checkState)
    assert(@menuRadio.checked?)
    assert(!@menuRadio.unchecked?)
    assert(!@menuRadio.maybe?)
  end

  def test_setCheck_FALSE
    @menuRadio.check = Fox::FALSE
    assert_equal(Fox::FALSE, @menuRadio.checkState)
    assert(!@menuRadio.checked?)
    assert(@menuRadio.unchecked?)
    assert(!@menuRadio.maybe?)
  end

  def test_setCheck_MAYBE
    @menuRadio.check = Fox::MAYBE
    assert_equal(Fox::MAYBE, @menuRadio.checkState)
    assert(!@menuRadio.checked?)
    assert(!@menuRadio.unchecked?)
    assert(@menuRadio.maybe?)
  end

  def test_setCheck_true
    @menuRadio.check = true
    assert_equal(Fox::TRUE, @menuRadio.checkState)
    assert(@menuRadio.checked?)
    assert(!@menuRadio.unchecked?)
    assert(!@menuRadio.maybe?)
  end

  def test_setCheck_false
    @menuRadio.check = false
    assert_equal(Fox::FALSE, @menuRadio.checkState)
    assert(!@menuRadio.checked?)
    assert(@menuRadio.unchecked?)
    assert(!@menuRadio.maybe?)
  end
end
