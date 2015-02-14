/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

/// Tree list styles
enum {
  TREELIST_EXTENDEDSELECT = 0,            /// Extended selection mode allows for drag-selection of ranges of items
  TREELIST_SINGLESELECT   = 0x00100000,   /// Single selection mode allows up to one item to be selected
  TREELIST_BROWSESELECT   = 0x00200000,   /// Browse selection mode enforces one single item to be selected at all times
  TREELIST_MULTIPLESELECT = 0x00300000,   /// Multiple selection mode is used for selection of individual items
  TREELIST_AUTOSELECT     = 0x00400000,   /// Automatically select under cursor
  TREELIST_SHOWS_LINES    = 0x00800000,   /// Lines shown
  TREELIST_SHOWS_BOXES    = 0x01000000,   /// Boxes to expand shown
  TREELIST_ROOT_BOXES     = 0x02000000,   /// Display root boxes also
  TREELIST_NORMAL         = TREELIST_EXTENDEDLIST
  };


class FXIcon;
class FXFont;
class FXTreeList;

%rename("hasItems?") FXTreeItem::hasItems() const;
%rename("hasItems=") FXTreeItem::setHasItems(FXbool);

class FXTreeItem : public FXObject {
public:
  enum{
    SELECTED        = 1,        /// Selected
    FOCUS           = 2,        /// Focus
    DISABLED        = 4,        /// Disabled
    OPENED          = 8,        /// Opened
    EXPANDED        = 16,       /// Expanded
    HASITEMS        = 32,       /// Has virtual subitems
    DRAGGABLE       = 64,       /// Draggable
    OPENICONOWNED   = 128,      /// Open icon owned by item
    CLOSEDICONOWNED = 256       /// Close icon owned by item
    };
public:
  %extend {
    FXTreeItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL){
      return new FXRbTreeItem(text,oi,ci,ITEMDATA);
      }
    }

  /// Get item label
  const FXString& getText() const;

  /// Get open icon
  FXIcon* getOpenIcon() const;

  /// Get closed icon
  FXIcon* getClosedIcon() const;

  FXTreeItem* getParent() const;
  FXTreeItem* getNext() const;
  FXTreeItem* getPrev() const;
  FXTreeItem* getFirst() const;
  FXTreeItem* getLast() const;
  FXTreeItem* getBelow() const;
  FXTreeItem* getAbove() const;
  FXint getNumChildren() const;

  %extend {
    void setData(VALUE ptr){
      self->setData((void*) ptr);
      }

    VALUE getData() const {
      return self->getData() ? (VALUE) self->getData() : Qnil;
      }
  }

  FXbool hasFocus() const;
  FXbool isSelected() const;
  FXbool isOpened() const;
  FXbool isExpanded() const;
  FXbool isEnabled() const;
  FXbool isDraggable() const;

  /// Return TRUE if subitems, real or imagined
  FXbool hasItems() const;

  /// Change has items flag
  void setHasItems(FXbool flag);

  /// Return true if descendent of parent item
  FXbool isChildOf(const FXTreeItem* item) const;

  /// Return true if ancestor of child item
  FXbool isParentOf(const FXTreeItem* item) const;

  virtual ~FXTreeItem(){}
  };


DECLARE_FXOBJECT_VIRTUALS(FXTreeItem)
DECLARE_FXTREEITEM_VIRTUALS(FXTreeItem)

%{
static swig_type_info *FXTreeItem_dynamic_cast(void **ptr) {
    FXTreeItem **ppTreeItem = reinterpret_cast<FXTreeItem **>(ptr);
    FXDirItem *pDirItem=dynamic_cast<FXDirItem*>(*ppTreeItem);
    if(pDirItem){
      *ptr=reinterpret_cast<void*>(pDirItem);
      return SWIG_TypeQuery("FXDirItem *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXTreeItem, FXTreeItem_dynamic_cast);

%ignore FXTreeList::getSortFunc() const;
%ignore FXTreeList::setSortFunc(FXTreeListSortFunc);

/**
* A Tree List Widget organizes items in a hierarchical, tree-like fashion.
* Subtrees can be collapsed or expanded by double-clicking on an item
* or by clicking on the optional plus button in front of the item.
* Each item may have a text and optional open-icon as well as a closed-icon.
* The items may be connected by optional lines to show the hierarchical
* relationship.
* When an item's selected state changes, the treelist emits a SEL_SELECTED
* or SEL_DESELECTED message.  If an item is opened or closed, a message
* of type SEL_OPENED or SEL_CLOSED is sent.  When the subtree under an
* item is expanded, a SEL_EXPANDED or SEL_COLLAPSED message is issued.
* A change of the current item is signified by the SEL_CHANGED message.
* In addition, the tree list sends SEL_COMMAND messages when the user
* clicks on an item, and SEL_CLICKED, SEL_DOUBLECLICKED, and SEL_TRIPLECLICKED
* when the user clicks once, twice, or thrice, respectively.
* When items are added or removed, the tree list sends messages of the
* type SEL_INSERTED or SEL_DELETED.
* In each of these cases, a pointer to the item, if any, is passed in the
* 3rd argument of the message.
*/
class FXTreeList : public FXScrollArea {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onTipTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_EVENT);
  long onClicked(FXObject*,FXSelector,void* PTR_TREEITEM);
  long onDoubleClicked(FXObject*,FXSelector,void* PTR_TREEITEM);
  long onTripleClicked(FXObject*,FXSelector,void* PTR_TREEITEM);
  long onCommand(FXObject*,FXSelector,void* PTR_TREEITEM);
  long onLookupTimer(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  static FXint ascending(const FXTreeItem* a,const FXTreeItem* b);
  static FXint descending(const FXTreeItem* a,const FXTreeItem* b);
  static FXint ascendingCase(const FXTreeItem* a,const FXTreeItem* b);
  static FXint descendingCase(const FXTreeItem* pa,const FXTreeItem* pb);
public:
  enum {
    ID_LOOKUPTIMER=FXScrollArea::ID_LAST,
    ID_LAST
    };
public:

  /// Construct a new, initially empty tree list
  %extend {
    FXTreeList(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TREELIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbTreeList(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return number of items
  FXint getNumItems() const;

  /// Return number of visible items
  FXint getNumVisible() const;

  /// Change number of visible items
  void setNumVisible(FXint nvis);

  /// Return first root item
  FXTreeItem* getFirstItem() const;

  /// Return last root item
  FXTreeItem* getLastItem() const;

  /// Fill tree list by appending items from array of strings
  FXint fillItems(FXTreeItem* father,const FXchar** strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Insert [possibly subclassed] item under father before other item
    FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owned=TRUE;
        }
      return self->insertItem(other,father,item,notify);
      }
  }

  /// Insert item with given text and optional icons, and user-data pointer under father before other item
  FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Append [possibly subclassed] item as last child of father
    FXTreeItem* appendItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owned=TRUE;
        }
      return self->appendItem(father,item,notify);
      }
  }

  /// Append item with given text and optional icons, and user-data pointer as last child of father
  FXTreeItem* appendItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Prepend [possibly subclassed] item as first child of father
    FXTreeItem* prependItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owned=TRUE;
        }
      return self->prependItem(father,item,notify);
      }
  }

  /// Prepend item with given text and optional icons, and user-data pointer as first child of father
  FXTreeItem* prependItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Move item under father before other item
  FXTreeItem *moveItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item);

  /// Extract item
  FXTreeItem* extractItem(FXTreeItem* item,FXbool notify=FALSE);

  %extend {
    /// Remove item
    void removeItem(FXTreeItem* item,FXbool notify=FALSE){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXTreeItem> items;
      FXRbTreeList::enumerateItem(item,items);

      // Do the deed
      self->removeItem(item,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }

    /// Remove items in range [fm, to] inclusively
    void removeItems(FXTreeItem* fm,FXTreeItem* to,FXbool notify=FALSE){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXTreeItem> items;
      FXRbTreeList::enumerateItems(fm,to,items);

      // Do the deed
      self->removeItems(fm,to,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }

    /// Remove all items from list
    void clearItems(FXbool notify=FALSE){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXTreeItem> items;
      FXRbTreeList::enumerateItems(self->getFirstItem(),self->getLastItem(),items);

      // Do the deed
      self->clearItems(notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }
    }

  /// Return item width
  FXint getItemWidth(const FXTreeItem* item) const;

  /// Return item height
  FXint getItemHeight(const FXTreeItem* item) const;

  /**
  * Search items by name, beginning from item start.  If the start item
  * is NULL the search will start at the first, top-most item in the list.
  * Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control the search
  * direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  * The option SEARCH_IGNORECASE causes a case-insensitive match.  Finally,
  * passing SEARCH_PREFIX causes searching for a prefix of the item name.
  * Return NULL if no matching item is found.
  */
  FXTreeItem* findItem(const FXString& name,FXTreeItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /**
  * Search items by associated user data, beginning from item start. If the
  * start item is NULL the search will start at the first, top-most item
  * in the list.  Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control
  * the search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  */
  FXTreeItem* findItemByData(const void *ITEMDATA,FXTreeItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Change item's text
  void setItemText(FXTreeItem* item,const FXString& text);

  /// Return item's text
  FXString getItemText(const FXTreeItem* item) const;

  /// Change item's open icon, deleting the old icon if it was owned
  void setItemOpenIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's open icon
  FXIcon* getItemOpenIcon(const FXTreeItem* item) const;

  /// Chance item's closed icon, deleting the old icon if it was owned
  void setItemClosedIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's closed icon
  FXIcon* getItemClosedIcon(const FXTreeItem* item) const;

  %extend {
    /// Change item user-data pointer
    void setItemData(FXTreeItem* item,VALUE ptr){
      self->setItemData(item,(void*) ptr);
      }

    /// Return item user-data pointer
    VALUE getItemData(const FXTreeItem* item) const {
      return self->getItemData(item) ? (VALUE) self->getItemData(item) : Qnil;
      }
  }

  /// Return TRUE if item is selected
  FXbool isItemSelected(const FXTreeItem* item) const;

  /// Return TRUE if item is current
  FXbool isItemCurrent(const FXTreeItem* item) const;

  /// Return TRUE if item is visible
  FXbool isItemVisible(const FXTreeItem* item) const;

  /// Return TRUE if item opened
  FXbool isItemOpened(const FXTreeItem* item) const;

  /// Return TRUE if item expanded
  FXbool isItemExpanded(const FXTreeItem* item) const;

  /// Return TRUE if item is a leaf-item, i.e. has no children
  FXbool isItemLeaf(const FXTreeItem* item) const;

  /// Return TRUE if item is enabled
  FXbool isItemEnabled(const FXTreeItem* item) const;

  /// Return item hit code: 0 outside, 1 icon, 2 text, 3 box
  FXint hitItem(const FXTreeItem* item,FXint x,FXint y) const;

  /// Repaint item
  void updateItem(FXTreeItem* item) const;

  /// Return current item, if any
  FXTreeItem* getCurrentItem() const;

  /// Change anchor item
  void setAnchorItem(FXTreeItem* item);

  /// Return anchor item, if any
  FXTreeItem* getAnchorItem() const;

  /// Return item under cursor, if any
  FXTreeItem* getCursorItem() const;

  /// Sort root items
  void sortRootItems();

  /// Sort all items recursively
  void sortItems();

  /// Sort children of item
  void sortChildItems(FXTreeItem* item);

  /// Return sort function
  FXTreeListSortFunc getSortFunc() const;

  /// Change sort function
  void setSortFunc(FXTreeListSortFunc func);

  /// Change text font
  void setFont(FXFont* fnt);

  /// Return text font
  FXFont* getFont() const;

  /// Change parent-child indent amount
  void setIndent(FXint in);

  /// Return parent-child indent amount
  FXint getIndent() const;

  /// Return normal text color
  FXColor getTextColor() const;

  /// Change normal text color
  void setTextColor(FXColor clr);

  /// Return selected text background
  FXColor getSelBackColor() const;

  /// Change selected text background
  void setSelBackColor(FXColor clr);

  /// Return selected text color
  FXColor getSelTextColor() const;

  /// Change selected text color
  void setSelTextColor(FXColor clr);

  /// Return line color
  FXColor getLineColor() const;

  /// Change line color
  void setLineColor(FXColor clr);

  /// Return list style
  FXuint getListStyle() const;

  /// Change list style
  void setListStyle(FXuint style);

  /// Set the status line help text for this list
  void setHelpText(const FXString& text);

  /// Get the status line help text for this list
  const FXString& getHelpText() const;

  /// Destructor
  virtual ~FXTreeList();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTreeList)
DECLARE_FXID_VIRTUALS(FXTreeList)
DECLARE_FXDRAWABLE_VIRTUALS(FXTreeList)
DECLARE_FXWINDOW_VIRTUALS(FXTreeList)
DECLARE_FXSCROLLAREA_VIRTUALS(FXTreeList)
DECLARE_FXTREELIST_VIRTUALS(FXTreeList)

%{
static swig_type_info *FXTreeList_dynamic_cast(void **ptr) {
    FXTreeList **ppTreeList = reinterpret_cast<FXTreeList **>(ptr);
    FXDirList *pDirList=dynamic_cast<FXDirList*>(*ppTreeList);
    if(pDirList){
      *ptr=reinterpret_cast<void*>(pDirList);
      return SWIG_TypeQuery("FXDirList *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXTreeList, FXTreeList_dynamic_cast);

