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

/// Folding list styles
enum {
  FOLDINGLIST_EXTENDEDSELECT = 0,            /// Extended selection mode allows for drag-selection of ranges of items
  FOLDINGLIST_SINGLESELECT   = 0x00100000,   /// Single selection mode allows up to one item to be selected
  FOLDINGLIST_BROWSESELECT   = 0x00200000,   /// Browse selection mode enforces one single item to be selected at all times
  FOLDINGLIST_MULTIPLESELECT = 0x00300000,   /// Multiple selection mode is used for selection of individual items
  FOLDINGLIST_AUTOSELECT     = 0x00400000,   /// Automatically select under cursor
  FOLDINGLIST_SHOWS_LINES    = 0x00800000,   /// Lines shown
  FOLDINGLIST_SHOWS_BOXES    = 0x01000000,   /// Boxes to expand shown
  FOLDINGLIST_ROOT_BOXES     = 0x02000000,   /// Display root boxes also
  FOLDINGLIST_NORMAL         = FOLDINGLIST_EXTENDEDSELECT
  };

%rename("hasItems?") FXFoldingItem::hasItems() const;
%rename("hasItems=") FXFoldingItem::setHasItems(FXbool);

/// Tree list Item
class FXFoldingItem : public FXObject {
public:
  enum{
    SELECTED        = 1,
    FOCUS           = 2,
    DISABLED        = 4,
    OPENED          = 8,
    EXPANDED        = 16,
    HASITEMS        = 32,
    DRAGGABLE       = 64,
    OPENICONOWNED   = 128,
    CLOSEDICONOWNED = 256
    };
public:

  %extend {
    /// Constructor
    FXFoldingItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL){
      return new FXRbFoldingItem(text,oi,ci,ITEMDATA);
      }
  }

  /// Get parent item
  FXFoldingItem* getParent() const;

  /// Get next sibling item
  FXFoldingItem* getNext() const;

  /// Get previous sibling item
  FXFoldingItem* getPrev() const;

  /// Get first child item
  FXFoldingItem* getFirst() const;

  /// Get las child item
  FXFoldingItem* getLast() const;

  /// Get item below this one in list
  FXFoldingItem* getBelow() const;

  /// Get item above this one in list
  FXFoldingItem* getAbove() const;

  /// Get number of children of item
  FXint getNumChildren() const;

  /// Get item label
  const FXString& getText() const;

  /// Get open icon
  FXIcon* getOpenIcon() const;

  /// Get closed icon
  FXIcon* getClosedIcon() const;

  /// Set or get user data for this item
  %extend {
    void setData(VALUE ptr){
      self->setData(reinterpret_cast<void*>(ptr));
      }

    VALUE getData() const {
      return self->getData() ? reinterpret_cast<VALUE>(self->getData()) : Qnil;
      }
  }

  /// Return true if item has focus
  FXbool hasFocus() const;

  /// Return true if this item is selected
  FXbool isSelected() const;

  /// Return true if this item is open
  FXbool isOpened() const;

  /// Return true if this item is expanded into sub items
  FXbool isExpanded() const;

  /// Return true if this item is enabled
  FXbool isEnabled() const;

  /// Return true if this item is draggable
  FXbool isDraggable() const;

  /// Return TRUE if subitems, real or imagined
  FXbool hasItems() const;

  /// Change has items flag
  void setHasItems(FXbool flag);

  /// Return true if descendent of parent item
  FXbool isChildOf(const FXFoldingItem* item) const;

  /// Return true if ancestor of child item
  FXbool isParentOf(const FXFoldingItem* item) const;

  /// Destroy item and free icons if owned
  virtual ~FXFoldingItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFoldingItem)
DECLARE_FXFOLDINGITEM_VIRTUALS(FXFoldingItem)


/**
* A Folding List Widget resembles a Tree list except that it supports a
* header control to provide each item with multiple columns of text.
* Subtrees can be collapsed or expanded by double-clicking on an item
* or by clicking on the optional plus button in front of the item.
* Each item may have a text and optional open-icon as well as a closed-icon.
* The items may be connected by optional lines to show the hierarchical
* relationship.
* When an item's selected state changes, the folding list emits a SEL_SELECTED
* or SEL_DESELECTED message.  If an item is opened or closed, a message
* of type SEL_OPENED or SEL_CLOSED is sent.  When the subtree under an
* item is expanded, a SEL_EXPANDED or SEL_COLLAPSED message is issued.
* A change of the current item is signified by the SEL_CHANGED message.
* In addition, the folding list sends SEL_COMMAND messages when the user
* clicks on an item, and SEL_CLICKED, SEL_DOUBLECLICKED, and SEL_TRIPLECLICKED
* when the user clicks once, twice, or thrice, respectively.
* When items are added or removed, the folding list sends messages of the
* type SEL_INSERTED or SEL_DELETED.
* In each of these cases, a pointer to the item, if any, is passed in the
* 3rd argument of the message.
*/
class FXFoldingList : public FXScrollArea {
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onRightBtnPress(FXObject*,FXSelector,void*);
  long onRightBtnRelease(FXObject*,FXSelector,void*);
  long onHeaderChanged(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onTipTimer(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onAutoScroll(FXObject*,FXSelector,void*);
  long onClicked(FXObject*,FXSelector,void*);
  long onDoubleClicked(FXObject*,FXSelector,void*);
  long onTripleClicked(FXObject*,FXSelector,void*);
  long onCommand(FXObject*,FXSelector,void*);
  long onLookupTimer(FXObject*,FXSelector,void*);
public:
  static FXint ascending(const FXFoldingItem*,const FXFoldingItem*);
  static FXint descending(const FXFoldingItem*,const FXFoldingItem*);
  static FXint ascendingCase(const FXFoldingItem*,const FXFoldingItem*);
  static FXint descendingCase(const FXFoldingItem*,const FXFoldingItem*);
public:
  enum {
    ID_LOOKUPTIMER=FXScrollArea::ID_LAST,
    ID_HEADER_CHANGE,
    ID_LAST
    };
public:

  %extend {
    /// Construct a folding list with nvis visible items; the folding list is initially empty
    FXFoldingList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FOLDINGLIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbFoldingList(p,tgt,sel,opts,x,y,w,h);
      }
  }

  /// Return header control
  FXHeader* getHeader() const;

  %extend {
    /// Set headers from array of strings
    void setHeaders(VALUE stringArray,FXint size=1){
      Check_Type(stringArray,T_ARRAY);
      long len=RARRAY_LEN(stringArray);
      const FXchar **strings;
      if(FXMALLOC(&strings,FXchar*,len+1)){
        for(long i=0;i<len;i++){
          VALUE s=rb_ary_entry(stringArray,i);
          strings[i]=StringValuePtr(s);
          }
        strings[len]=0;
        self->setHeaders(strings,size);
        FXFREE(&strings);
        }
      }
  }

  /// Append header with given text and optional icon
  void appendHeader(const FXString& text,FXIcon *icon=NULL,FXint size=1);

  /// Remove header at index
  void removeHeader(FXint index);

  /// Change text of header at index
  void setHeaderText(FXint index,const FXString& text);

  /// Return text of header at index
  FXString getHeaderText(FXint index) const;

  /// Change icon of header at index
  void setHeaderIcon(FXint index,FXIcon *icon);

  /// Return icon of header at index
  FXIcon* getHeaderIcon(FXint index) const;

  /// Change size of header at index
  void setHeaderSize(FXint index,FXint size);

  /// Return width of header at index
  FXint getHeaderSize(FXint index) const;

  /// Return number of headers
  FXint getNumHeaders() const;

  /// Return number of items
  FXint getNumItems() const;

  /// Return number of visible items
  FXint getNumVisible() const;

  /// Change number of visible items
  void setNumVisible(FXint nvis);

  /// Return first root item
  FXFoldingItem* getFirstItem() const;

  /// Return last root item
  FXFoldingItem* getLastItem() const;

  %extend {
    /// Fill list by appending items from array of strings
    FXint fillItems(FXFoldingItem* father,const FXchar** strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE){
      return self->fillItems(father,strings,oi,ci,ITEMDATA,notify);
      }
  }

  %extend {
    /// Insert [possibly subclassed] item under father before other item
    FXFoldingItem* insertItem(FXFoldingItem* other,FXFoldingItem* father,FXFoldingItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbFoldingItem))){
        dynamic_cast<FXRbFoldingItem*>(item)->owned=TRUE;
        }
      return self->insertItem(other,father,item,notify);
      }
  }

  /// Insert item with given text and optional icons, and user-data pointer under father before other item
  FXFoldingItem* insertItem(FXFoldingItem* other,FXFoldingItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Append new [possibly subclassed] item after to other item
    FXFoldingItem* appendItem(FXFoldingItem* father,FXFoldingItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbFoldingItem))){
        dynamic_cast<FXRbFoldingItem*>(item)->owned=TRUE;
        }
      return self->appendItem(father,item,notify);
      }
  }

  /// Append item with given text and optional icons, and user-data pointer as last child of father
  FXFoldingItem* appendItem(FXFoldingItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Prepend [possibly subclassed] item as first child of father
    FXFoldingItem* prependItem(FXFoldingItem* father,FXFoldingItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbFoldingItem))){
        dynamic_cast<FXRbFoldingItem*>(item)->owned=TRUE;
        }
      return self->prependItem(father,item,notify);
      }
  }

  /// Prepend new item with given text and optional icon, and user-data pointer prior to other item
  FXFoldingItem* prependItem(FXFoldingItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Move item under father before other item
  FXFoldingItem *moveItem(FXFoldingItem* other,FXFoldingItem* father,FXFoldingItem* item);

  /// Extract item
  FXFoldingItem* extractItem(FXFoldingItem* item,FXbool notify=FALSE);

  %extend {
    /// Remove item
    void removeItem(FXFoldingItem* item,FXbool notify=FALSE){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXFoldingItem> items;
      FXRbFoldingList::enumerateItem(item,items);

      // Do the deed
      self->removeItem(item,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }

    /// Remove items in range [fm, to] inclusively
    void removeItems(FXFoldingItem* fm,FXFoldingItem* to,FXbool notify=FALSE){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXFoldingItem> items;
      FXRbFoldingList::enumerateItems(fm,to,items);

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
      FXObjectListOf<FXFoldingItem> items;
      FXRbFoldingList::enumerateItems(self->getFirstItem(),self->getLastItem(),items);

      // Do the deed
      self->clearItems(notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }
  }

  /// Return item width
  FXint getItemWidth(const FXFoldingItem* item) const;

  /// Return item height
  FXint getItemHeight(const FXFoldingItem* item) const;

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
  FXFoldingItem* findItem(const FXString& text,FXFoldingItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /**
  * Search items by associated user data, beginning from item start. If the
  * start item is NULL the search will start at the first, top-most item
  * in the list.  Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control
  * the search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  */
  FXFoldingItem* findItemByData(const void *ITEMDATA,FXFoldingItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Change item's text
  void setItemText(FXFoldingItem* item,const FXString& text);

  /// Return item's text
  FXString getItemText(const FXFoldingItem* item) const;

  /// Change item's open icon
  void setItemOpenIcon(FXFoldingItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's open icon
  FXIcon* getItemOpenIcon(const FXFoldingItem* item) const;

  /// Chance item's closed icon
  void setItemClosedIcon(FXFoldingItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's closed icon
  FXIcon* getItemClosedIcon(const FXFoldingItem* item) const;

  %extend {
    /// Change item user-data pointer
    void setItemData(FXFoldingItem* item,VALUE ptr){
      self->setItemData(item,reinterpret_cast<void*>(ptr));
      }

    /// Return item user-data pointer
    VALUE getItemData(const FXFoldingItem* item) const {
      return self->getItemData(item) ? reinterpret_cast<VALUE>(self->getItemData(item)) : Qnil;
      }
  }

  /// Return TRUE if item is selected
  FXbool isItemSelected(const FXFoldingItem* item) const;

  /// Return TRUE if item is current
  FXbool isItemCurrent(const FXFoldingItem* item) const;

  /// Return TRUE if item is visible
  FXbool isItemVisible(const FXFoldingItem* item) const;

  /// Return TRUE if item opened
  FXbool isItemOpened(const FXFoldingItem* item) const;

  /// Return TRUE if item expanded
  FXbool isItemExpanded(const FXFoldingItem* item) const;

  /// Return TRUE if item is a leaf-item, i.e. has no children
  FXbool isItemLeaf(const FXFoldingItem* item) const;

  /// Return TRUE if item is enabled
  FXbool isItemEnabled(const FXFoldingItem* item) const;

  /// Return item hit code: 0 outside, 1 icon, 2 text, 3 box
  FXint hitItem(const FXFoldingItem* item,FXint x,FXint y) const;

  /// Repaint item
  void updateItem(FXFoldingItem* item);

  /// Return current item, if any
  FXFoldingItem* getCurrentItem() const;

  /// Change anchor item
  void setAnchorItem(FXFoldingItem* item);

  /// Return anchor item, if any
  FXFoldingItem* getAnchorItem() const;

  /// Return item under cursor, if any
  FXFoldingItem* getCursorItem() const;

  /// Sort all items recursively
  void sortItems();

  /// Sort root items
  void sortRootItems();

  /// Sort children of item
  void sortChildItems(FXFoldingItem* item);

  /// Return sort function
  FXFoldingListSortFunc getSortFunc() const;

  /// Change sort function
  void setSortFunc(FXFoldingListSortFunc func);

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
  virtual ~FXFoldingList();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFoldingList)
DECLARE_FXID_VIRTUALS(FXFoldingList)
DECLARE_FXDRAWABLE_VIRTUALS(FXFoldingList)
DECLARE_FXWINDOW_VIRTUALS(FXFoldingList)
DECLARE_FXSCROLLAREA_VIRTUALS(FXFoldingList)
DECLARE_FXFOLDINGLIST_VIRTUALS(FXFoldingList)

