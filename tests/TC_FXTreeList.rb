require 'test/unit'
require 'testcase'
require 'fox16'

include Fox

class TC_FXTreeList < TestCase
  def setup
    super(self.class.name)
    @treeList = FXTreeList.new(mainWindow, nil, 0,
      (TREELIST_BROWSESELECT|TREELIST_SHOWS_LINES|TREELIST_SHOWS_BOXES|
       TREELIST_ROOT_BOXES|LAYOUT_FILL_X|LAYOUT_FILL_Y))
  end
  
  def test_firstItem
    assert_nil(@treeList.firstItem)
    item = @treeList.addItemFirst(nil, "first")
    assert_same(item, @treeList.firstItem)
  end

  def test_lastItem
    assert_nil(@treeList.lastItem)
    item = @treeList.addItemFirst(nil, "first")
    assert_same(item, @treeList.lastItem)
  end

  def test_reparentItem
    rootItem = @treeList.addItemFirst(nil, "Root Item")
    childItem = @treeList.addItemFirst(@treeList.firstItem, "Child Item")
    @treeList.reparentItem(childItem, nil)
    assert_same(rootItem, @treeList.firstItem)
    assert_same(childItem, @treeList.lastItem)
  end

  def test_moveItemBefore
    first  = @treeList.addItemLast(nil, "first")
    second = @treeList.addItemLast(nil, "second")
    assert_same(second, first.next)
    assert_same(first,  second.prev)
    assert_same(second, @treeList.moveItemBefore(first, second))
    assert_same(second, first.prev)
    assert_same(first,  second.next)
  end

  def test_moveItemAfter
    first  = @treeList.addItemLast(nil, "first")
    second = @treeList.addItemLast(nil, "second")
    assert_same(second, first.next)
    assert_same(first,  second.prev)
    assert_same(first, @treeList.moveItemAfter(second, first))
    assert_same(second, first.prev)
    assert_same(first,  second.next)
  end

  def test_sortRootItems
    @treeList.addItemLast(nil, "B")
    @treeList.addItemLast(nil, "A")
    @treeList.addItemLast(nil, "C")
    @treeList.sortRootItems
    assert_equal("A", @treeList.firstItem.text)
    assert_equal("B", @treeList.firstItem.next.text)
    assert_equal("C", @treeList.lastItem.text)
  end

  def test_SEL_INSERTED
    anItem = nil
    @treeList.connect(SEL_INSERTED) { |sender, sel, ptr|
      anItem = ptr
    }
    theItem = @treeList.addItemLast(nil, "", nil, nil, nil, true)
    assert_same(theItem, anItem)
  end
  
  def test_SEL_DELETED
    theItem = @treeList.addItemLast(nil, "")
    anItem = nil
    @treeList.connect(SEL_DELETED) { |sender, sel, ptr|
      anItem = ptr
    }
    @treeList.removeItem(theItem, true)
    assert_same(theItem, anItem)
  end
end
