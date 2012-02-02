require 'test/unit'
require 'fox16'

class TC_FXDialogBox < Test::Unit::TestCase
  include Fox

  def test_nil_app_raises_argument_error
    assert_raise ArgumentError do
      FXDialogBox.new(nil, "title")
    end
  end
end
