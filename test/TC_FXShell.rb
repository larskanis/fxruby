require 'test/unit'

require 'fox16'

class TC_FXShell < Test::Unit::TestCase
  include Fox

  def setup
    if FXApp.instance.nil?
      @app = FXApp.new('TC_FXShell', 'FXRuby')
      @app.init([])
    else
      @app = FXApp.instance
    end
    @mainWin = FXMainWindow.new(@app, 'TC_FXShell')
  end

  def test_nil_parent_raises_argument_error
    assert_raise(ArgumentError){ FXShell.new(nil, 0, 0, 0, 0, 0) }
  end

  def test_new
    # Free-floating
    shell1 = FXShell.new(@app, 0, 0, 0, 0, 0)
    assert_nil(shell1.owner)

    # Owned
    shell2 = FXShell.new(@mainWin, 0, 0, 0, 0, 0)
    assert_same(@mainWin, shell2.owner)
  end
end
