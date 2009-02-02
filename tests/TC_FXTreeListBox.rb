require 'test/unit'
require 'testcase'
require 'fox16'

include Fox

class TC_FXTreeListBox < TestCase
  def setup
    super(self.class.name)
    @treeListBox = FXTreeListBox.new(mainWindow)
  end

  def test_sortRootItems
    @treeListBox.addItemLast(nil, "B")
    @treeListBox.addItemLast(nil, "A")
    @treeListBox.addItemLast(nil, "C")
    @treeListBox.sortRootItems
    assert_equal("A", @treeListBox.firstItem.text)
    assert_equal("B", @treeListBox.firstItem.next.text)
    assert_equal("C", @treeListBox.lastItem.text)
  end
end

