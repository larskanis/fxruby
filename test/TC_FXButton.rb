require 'test/unit'
require 'fox16'
require 'testcase'

class TC_FXButton < Fox::TestCase
  include Fox

  def setup
    super("TC_FXButton")
    @button = FXButton.new(mainWindow, "buttonText")
  end

  def test_nil_parent_raises_argument_error
    assert_raise(ArgumentError){ FXButton.new(nil, "buttonText") }
  end

  def testText
    assert(@button.text)
    assert_instance_of(String, @button.text)
    assert_equal("buttonText", @button.text)
    assert_not_equal("googly-moogly", @button.text)
    @button.text = nil
    assert(@button.text)
    assert_instance_of(String, @button.text)
  end

  def testStyle
    assert(@button.buttonStyle)
    assert_kind_of(Integer, @button.buttonStyle)

    @button.buttonStyle |= BUTTON_AUTOGRAY
    assert((@button.buttonStyle & BUTTON_AUTOGRAY) != 0)
    @button.buttonStyle &= ~BUTTON_AUTOGRAY
    assert((@button.buttonStyle & BUTTON_AUTOGRAY) == 0)

    @button.buttonStyle |= BUTTON_AUTOHIDE
    assert((@button.buttonStyle & BUTTON_AUTOHIDE) != 0)
    @button.buttonStyle &= ~BUTTON_AUTOHIDE
    assert((@button.buttonStyle & BUTTON_AUTOHIDE) == 0)

    @button.buttonStyle |= BUTTON_TOOLBAR
    assert((@button.buttonStyle & BUTTON_TOOLBAR) != 0)
    @button.buttonStyle &= ~BUTTON_TOOLBAR
    assert((@button.buttonStyle & BUTTON_TOOLBAR) == 0)

    @button.buttonStyle |= BUTTON_DEFAULT
    assert((@button.buttonStyle & BUTTON_DEFAULT) != 0)
    @button.buttonStyle &= ~BUTTON_DEFAULT
    assert((@button.buttonStyle & BUTTON_DEFAULT) == 0)

    @button.buttonStyle |= BUTTON_INITIAL
    assert((@button.buttonStyle & BUTTON_INITIAL) != 0)
    @button.buttonStyle &= ~BUTTON_INITIAL
    assert((@button.buttonStyle & BUTTON_INITIAL) == 0)
  end

  def testState
    assert(@button.state)
    assert_kind_of(Integer, @button.state)

    @button.state = STATE_UP
    assert_equal(STATE_UP, @button.state)

    @button.state = STATE_DOWN
    assert_equal(STATE_DOWN, @button.state)

    @button.state = STATE_ENGAGED
    assert_equal(STATE_ENGAGED, @button.state)

    @button.state = STATE_CHECKED
    assert_equal(STATE_CHECKED, @button.state)

    @button.state = STATE_UNCHECKED
    assert_equal(STATE_UNCHECKED, @button.state)
  end

  def test_create_for_non_created_parent_window_raises_runtime_error
    assert_raise RuntimeError do
      @button.create
    end
  end
end
