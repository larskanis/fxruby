require 'test/unit'
require 'fox16'

class TC_FXDialogBox < Test::Unit::TestCase
  include Fox

  def test_nil_app_raises_argument_error
    err = assert_raise do
      FXDialogBox.new(nil, "title")
    end
    assert_match(/NULL pointer/, err.to_s)
  end
end
