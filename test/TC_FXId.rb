require 'test/unit'
require 'fox16'
require 'testcase'

class TC_FXId < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end

  def test_created?
    assert !mainWindow.created?
    mainWindow.create
    assert mainWindow.created?, "main window should be created after call to FXApp#create"
    mainWindow.destroy
    assert !mainWindow.created?
  end
end
