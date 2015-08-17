require 'test/unit'
require 'fox16'

class TC_FXMainWindow < Test::Unit::TestCase
  include Fox

  def test_nil_app_raises_argument_error
    assert_raise ArgumentError do
      FXMainWindow.new(nil, "title")
    end
  end

  def test_non_created_app_raises_runtime_error
    pend "two FXApp are not allowed"
    app = FXApp.new
    assert_raise RuntimeError do
      FXMainWindow.new(app, "title").create
    end
  end
end
