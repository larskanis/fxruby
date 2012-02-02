require 'test/unit'

require 'fox16'

class TC_FXAccelTable < Test::Unit::TestCase
  include Fox

  def setup
    @accelTable = FXAccelTable.new
    @hotKey = fxparseHotKey('&q')
  end

  def test_add_accel_with_nil_target
    @accelTable.addAccel(@hotKey)
    assert @accelTable.hasAccel?(@hotKey)
    assert_nil @accelTable.targetOfAccel(@hotKey)
  end

  def test_add_accel_with_default_seldn_selup
    target = FXObject.new
    @accelTable.addAccel(@hotKey, target)
    assert_same target, @accelTable.targetOfAccel(@hotKey)
  end

  def test_add_accel_with_default_selup
    @accelTable.addAccel(@hotKey, FXObject.new, FXSEL(SEL_COMMAND, FXWindow::ID_SHOW))
  end

  def test_add_accel_with_no_defaults
    @accelTable.addAccel(@hotKey, FXObject.new, FXSEL(SEL_COMMAND, FXWindow::ID_SHOW), FXSEL(SEL_COMMAND, FXWindow::ID_HIDE))
  end

  def test_add_accel_with_lambda_for_seldn
    @accelTable.addAccel(@hotKey, lambda { puts "hello" })
  end

  def test_add_accel_with_lambda_for_selup
    @accelTable.addAccel(@hotKey, nil, lambda { puts "goodbye" })
  end

  def test_add_accel_with_lambda_for_selup_and_seldn
    @accelTable.addAccel(@hotKey, lambda { puts "hello" }, lambda { puts "goodbye" })
  end

  def test_has_accel
    assert(!@accelTable.hasAccel?(@hotKey))
    @accelTable.addAccel(@hotKey)
    assert(@accelTable.hasAccel?(@hotKey))
  end

  def test_remove_accel
    @accelTable.addAccel(@hotKey)
    assert(@accelTable.hasAccel?(@hotKey))
    @accelTable.removeAccel(@hotKey)
    assert(!@accelTable.hasAccel?(@hotKey))
  end
end
