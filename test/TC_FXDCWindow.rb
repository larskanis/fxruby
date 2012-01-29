require 'test/unit'
require 'testcase'
require 'fox16'

class TC_FXDCWindow < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    app.create
    mainWindow.create
  end

  def test_new
    dc = FXDCWindow.new(mainWindow)
    dc.drawPoint(0, 0)
    dc.end
  end

  def test_new_with_block
    FXDCWindow.new(mainWindow) do |dc|
      dc.drawPoint(0, 0)
    end
  end
end
