require 'test/unit'
require 'fox16'

class TC_FXMainWindow < Test::Unit::TestCase
  include Fox

  def test_nil_app_raises_argument_error
    err = assert_raise do
      FXMainWindow.new(nil, "title")
    end
    assert_match(/NULL pointer/, err.to_s)
  end

  def test_non_created_app_raises_runtime_error
    pend "two FXApp are not allowed"
    app = FXApp.new
    assert_raise RuntimeError do
      FXMainWindow.new(app, "title").create
    end
  end
end
