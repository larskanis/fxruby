require 'test/unit'
require 'testcase'
require 'fox16'

class TC_FXMenuCommand < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    @menuCommand = FXMenuCommand.new(mainWindow, "menuCommand")
  end
end
