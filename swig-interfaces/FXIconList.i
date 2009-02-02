/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

/// Icon list styles
enum {
  ICONLIST_EXTENDEDSELECT = 0,                /// Extended selection mode
  ICONLIST_SINGLESELECT   = 0x00100000,       /// At most one selected item
  ICONLIST_BROWSESELECT   = 0x00200000,       /// Always exactly one selected item
  ICONLIST_MULTIPLESELECT = 0x00300000,       /// Multiple selection mode
  ICONLIST_AUTOSIZE       = 0x00400000,       /// Automatically size item spacing
  ICONLIST_DETAILED       = 0,                /// List mode
  ICONLIST_MINI_ICONS     = 0x00800000,       /// Mini Icon mode
  ICONLIST_BIG_ICONS      = 0x01000000,       /// Big Icon mode
  ICONLIST_ROWS           = 0,                /// Row-wise mode
  ICONLIST_COLUMNS        = 0x02000000,       /// Column-wise mode
  ICONLIST_NORMAL         = ICONLIST_EXTENDEDSELECT
  };


class FXIcon;
class FXHeader;
class FXFont;
class FXIconList;



/// Icon item
class FXIconItem : public FXObject {
protected:
  FXString  label;
  FXIcon   *bigIcon;
  FXIcon   *miniIcon;
  void     *data;
  FXuint    state;
protected:
  FXIconItem():bigIcon(NULL),miniIcon(NULL),data(NULL),state(0){}
  virtual void draw(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual FXint hitItem(const FXIconList* list,FXint rx,FXint ry,FXint rw=1,FXint rh=1) const;
protected:
  virtual void drawBigIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawMiniIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawDetails(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
public:
  enum {
    SELECTED      = 1,  /// Selected
    FOCUS         = 2,  /// Focus
    DISABLED      = 4,  /// Disabled
    DRAGGABLE     = 8,  /// Draggable
    BIGICONOWNED  = 16, /// Big icon owned by item
    MINIICONOWNED = 32  /// Mini icon owned by item
    };
public:
  %extend {
    // Constructor
    FXIconItem(const FXString& text,FXIcon* bi=NULL,FXIcon* mi=NULL,void* ITEMDATA=NULL){
      return new FXRbIconItem(text,bi,mi,ITEMDATA);
      }
    }

   const FXString& getText() const;
   FXIcon* getBigIcon() const;
   FXIcon* getMiniIcon() const;

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
  FXbool isEnabled() const;
  FXbool isDraggable() const;
  
  virtual ~FXIconItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXIconItem)
DECLARE_FXICONITEM_VIRTUALS(FXIconItem)

%{
static swig_type_info *FXIconItem_dynamic_cast(void **ptr) {
    FXIconItem **ppIconItem = reinterpret_cast<FXIconItem **>(ptr);
    FXFileItem *pFileItem=dynamic_cast<FXFileItem*>(*ppIconItem);
    if(pFileItem){
      *ptr=reinterpret_cast<void*>(pFileItem);
      return SWIG_TypeQuery("FXFileItem *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXIconItem, FXIconItem_dynamic_cast);

%alias FXIconList::appendItem "<<";

%typemap(check) FXint ICONLIST_ITEM_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumItems()) {
    rb_raise(rb_eIndexError, "icon list item index out of bounds");
  }
}

%apply FXint ICONLIST_ITEM_INDEX { FXint index, FXint newindex, FXint oldindex };

%typemap(check) FXint ICONLIST_HEADER_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumHeaders()) {
    rb_raise(rb_eIndexError, "icon list header index out of bounds");
  }
}

%apply FXint ICONLIST_HEADER_INDEX { FXint headerIndex };

%ignore FXIconList::setHeaders(const FXString& strings,FXint size);


/**
* A Icon List Widget displays a list of items, each with a text and
* optional icon.  Icon List can display its items in essentially three
* different ways; in big-icon mode, the bigger of the two icons is used
* for each item, and the text is placed underneath the icon. In mini-
* icon mode, the icons are listed in rows and columns, with the smaller
* icon preceding the text.  Finally, in detail mode the icons are listed
* in a single column, and all fields of the text are shown under a
* header control with one button for each subfield.
* When an item's selected state changes, the icon list sends
* a SEL_SELECTED or SEL_DESELECTED message.  A change of the current
* item is signified by the SEL_CHANGED message.
* The icon list sends SEL_COMMAND messages when the user clicks on an item,
* and SEL_CLICKED, SEL_DOUBLECLICKED, and SEL_TRIPLECLICKED when the user
* clicks once, twice, or thrice, respectively.
* When items are added, replaced, or removed, the icon list sends messages
* of the type SEL_INSERTED, SEL_REPLACED, or SEL_DELETED.
* In each of these cases, the index to the item, if any, is passed in the
* 3rd argument of the message.
*/
class FXIconList : public FXScrollArea {
protected:
  FXHeader          *header;            // Header control
  FXIconItem       **items;             // Item list
  FXint              nitems;            // Number of items
  FXint              nrows;             // Number of rows
  FXint              ncols;             // Number of columns
  FXint              anchor;            // Anchor item
  FXint              current;           // Current item
  FXint              extent;            // Extent item
  FXint              cursor;            // Cursor item
  FXint              viewable;          // Visible item
  FXFont            *font;              // Font
  FXColor            textColor;         // Text color
  FXColor            selbackColor;      // Selected back color
  FXColor            seltextColor;      // Selected text color
  FXint              itemWidth;         // Item width
  FXint              itemHeight;        // Item height
  FXint              itemSpace;         // Space for item label
  FXint              anchorx;           // Rectangular selection
  FXint              anchory;
  FXint              currentx;
  FXint              currenty;
  FXint              grabx;             // Grab point x
  FXint              graby;             // Grab point y
  FXString           lookup;            // Lookup string
  FXString           help;              // Help text
  FXbool             state;             // State of item
protected:
  FXIconList();
  void recompute();
  void getrowscols(FXint& nr,FXint& nc,FXint w,FXint h) const;
  void drawLasso(FXint x0,FXint y0,FXint x1,FXint y1);
  void lassoChanged(FXint ox,FXint oy,FXint ow,FXint oh,FXint nx,FXint ny,FXint nw,FXint nh,FXbool notify);
  virtual void moveContents(FXint x,FXint y);
  virtual FXIconItem *createItem(const FXString& text,FXIcon *big,FXIcon* mini,void* ptr);
  static FXint compareSection(const FXchar *p,const FXchar* q,FXint s);
  static FXint compareSectionCase(const FXchar *p,const FXchar* q,FXint s);
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onTipTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeselectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectInverse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdArrangeByRows(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdArrangeByRows(FXObject*,FXSelector,void* PTR_NULL);
  long onCmdArrangeByColumns(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdArrangeByColumns(FXObject*,FXSelector,void* PTR_NULL);
  long onCmdShowDetails(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdShowDetails(FXObject*,FXSelector,void* PTR_NULL);
  long onCmdShowBigIcons(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdShowBigIcons(FXObject*,FXSelector,void* PTR_NULL);
  long onCmdShowMiniIcons(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdShowMiniIcons(FXObject*,FXSelector,void* PTR_NULL);
  long onHeaderChanged(FXObject*,FXSelector,void* PTR_IGNORE);
  long onHeaderResize(FXObject*,FXSelector,void* PTR_INT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onClicked(FXObject*,FXSelector,void* PTR_INT);
  long onDoubleClicked(FXObject*,FXSelector,void* PTR_INT);
  long onTripleClicked(FXObject*,FXSelector,void* PTR_INT);
  long onCommand(FXObject*,FXSelector,void* PTR_INT);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_EVENT);
  long onLookupTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
public:
  static FXint ascending(const FXIconItem* a,const FXIconItem* b);
  static FXint descending(const FXIconItem* a,const FXIconItem* b);
  static FXint ascendingCase(const FXIconItem* a,const FXIconItem* b);
  static FXint descendingCase(const FXIconItem* a,const FXIconItem* b);
public:
  enum {
    ID_SHOW_DETAILS=FXScrollArea::ID_LAST,
    ID_SHOW_MINI_ICONS,
    ID_SHOW_BIG_ICONS,
    ID_ARRANGE_BY_ROWS,
    ID_ARRANGE_BY_COLUMNS,
    ID_HEADER_CHANGE,
    ID_LOOKUPTIMER,
    ID_SELECT_ALL,
    ID_DESELECT_ALL,
    ID_SELECT_INVERSE,
    ID_LAST
    };
public:
  %extend {
    /// Construct icon list with no items in it initially
    FXIconList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=ICONLIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbIconList(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return number of items
  FXint getNumItems() const;
  
  /// Return number of rows
  FXint getNumRows() const;
  
  /// Return number of columns
  FXint getNumCols() const;

  /// Return header control
  FXHeader* getHeader() const;

  /// Set headers from array of strings
  void setHeaders(const FXchar** strings,FXint size=1);

  /// Set headers from newline separated strings
  void setHeaders(const FXString& strings,FXint size=1);

  /// Append header with given text and optional icon
  void appendHeader(const FXString& text,FXIcon *icon=NULL,FXint size=1);
  
  /// Remove header at index
  void removeHeader(FXint headerIndex);
  
  /// Change text of header at index
  void setHeaderText(FXint headerIndex,const FXString& text);
  
  /// Return text of header at index
  FXString getHeaderText(FXint headerIndex) const;
  
  /// Change icon of header at index
  void setHeaderIcon(FXint headerIndex,FXIcon *icon);
  
  /// Return icon of header at index
  FXIcon* getHeaderIcon(FXint headerIndex) const;
  
  /// Change size of header at index
  void setHeaderSize(FXint headerIndex,FXint size);
  
  /// Return width of header at index
  FXint getHeaderSize(FXint headerIndex) const;
  
  /// Return number of headers
  FXint getNumHeaders() const;
  
  /// Return the item at the given index
  FXIconItem *getItem(FXint index) const;
  
  %extend {
    /// Replace the item with a [possibly subclassed] item
    FXint setItem(FXint index,FXIconItem* item,FXbool notify=FALSE){
      // Save pointer to the soon-to-be-destroyed item
      FXIconItem* oldItem=self->getItem(index);

      // Do the deed
      if(item->isMemberOf(FXMETACLASS(FXRbIconItem)))
        dynamic_cast<FXRbIconItem*>(item)->owned=TRUE;
      FXint result=self->setItem(index,item,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(oldItem);

      // Done
      return result;
      }

    /// Replace items text, icons, and user-data pointer
    FXint setItem(FXint index,const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE){
      // Save pointer to the soon-to-be-destroyed item
      FXIconItem* oldItem=self->getItem(index);

      // Do the deed
      FXint result=self->setItem(index,text,big,mini,ITEMDATA,notify);
      
      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(oldItem);

      // Done
      return result;
      }
  }
  

  /// Fill list by appending items from array of strings
  FXint fillItems(const FXchar** strings,FXIcon *big=NULL,FXIcon* mini=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Insert a new [possibly subclassed] item at the give index
    FXint insertItem(FXint index,FXIconItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbIconItem)))
        dynamic_cast<FXRbIconItem*>(item)->owned=TRUE;
      return self->insertItem(index,item,notify);
      }
  }
  
  /// Insert item at index with given text, icons, and user-data pointer
  FXint insertItem(FXint index,const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);
  
  %extend {
    /// Append a [possibly subclassed] item to the end of the list
    FXint appendItem(FXIconItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbIconItem)))
        dynamic_cast<FXRbIconItem*>(item)->owned=TRUE;
      return self->appendItem(item,notify);
      }
  }
  
  /// Append new item with given text and optional icons, and user-data pointer
  FXint appendItem(const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Append a [possibly subclassed] item to the end of the list
    FXint prependItem(FXIconItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbIconItem)))
        dynamic_cast<FXRbIconItem*>(item)->owned=TRUE;
      return self->prependItem(item,notify);
      }
  }
  
  /// Append new item with given text and optional icons, and user-data pointer
  FXint prependItem(const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Move item from oldindex to newindex
  FXint moveItem(FXint newindex,FXint oldindex,FXbool notify=FALSE);

  /// Extract item from list
  FXIconItem* extractItem(FXint index,FXbool notify=FALSE);

  %extend {
    /// Remove item from list
    void removeItem(FXint index,FXbool notify=FALSE){
      // Save pointer to the soon-to-be-destroyed item
      FXIconItem* item=self->getItem(index);

      // Do the deed
      self->removeItem(index,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(item);
      }
  
    /// Remove all items from list
    void clearItems(FXbool notify=FALSE){
      // Save pointers to the soon-to-be-destroyed items
      FXObjectListOf<FXIconItem> items;
      FXint numItems = self->getNumItems();
      for (FXint i = 0; i< numItems; i++) items.append(self->getItem(i));

      // Do the deed
      self->clearItems(notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for (FXint j = 0; j < items.no(); j++) FXRbUnregisterRubyObj(items[j]);
      }
  }
  
  /// Return item width
  FXint getItemWidth() const;

  /// Return item height
  FXint getItemHeight() const;

  /** 
  * Search items by name, beginning from item start.  If the start
  * item is -1 the search will start at the first item in the list.
  * Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control the
  * search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  * The option SEARCH_IGNORECASE causes a case-insensitive match.  Finally,
  * passing SEARCH_PREFIX causes searching for a prefix of the item name.
  * Return -1 if no matching item is found.
  */
  FXint findItem(const FXString& text,FXint start=-1,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;
  
  /**
  * Search items by associated user data, beginning from item start. If the
  * start item is -1 the search will start at the first item in the list.
  * Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control the
  * search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  */
  FXint findItemByData(const void *ITEMDATA,FXint start=-1,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  %extend {
    /// Scroll to make item visible
    void makeItemVisible(FXIconItem* item){
      FXint numItems=self->getNumItems();
      for(FXint i=0; i<numItems; i++){
        if(self->getItem(i)==item){
          self->makeItemVisible(i);
	  break;
	  }
	}
      }
  }
  
  /// Change item text
  void setItemText(FXint index,const FXString& text);
  
  /// Return item text
  FXString getItemText(FXint index) const;
  
  /// Change item big icon
  void setItemBigIcon(FXint index,FXIcon* icon,FXbool owned=FALSE);
  
  /// Return big icon of item at index
  FXIcon* getItemBigIcon(FXint index) const;
  
  /// Change item mini icon
  void setItemMiniIcon(FXint index,FXIcon* icon,FXbool owned=FALSE);
  
  /// Return mini icon of item at index
  FXIcon* getItemMiniIcon(FXint index) const;
  
  %extend {
    /// Change item user-data pointer
    void setItemData(FXint index, VALUE ptr){
      self->setItemData(index, (void*) ptr);
      }
  
    /// Return item user-data pointer
    VALUE getItemData(FXint index) const {
      return self->getItemData(index) ? (VALUE) self->getItemData(index) : Qnil;
      }
  }
  
  /// Return TRUE if item at index is selected
  FXbool isItemSelected(FXint index) const;
  
  /// Return TRUE if item at index is current
  FXbool isItemCurrent(FXint index) const;
  
  /// Return TRUE if item at index is visible
  FXbool isItemVisible(FXint index) const;
  
  /// Return TRUE if item at index is enabled
  FXbool isItemEnabled(FXint index) const;
  
  /// Return item hit code: 0 outside, 1 icon, 2 text
  FXint hitItem(FXint index,FXint x,FXint y,FXint ww=1,FXint hh=1) const;
  
  /// Repaint item at index
  void updateItem(FXint index) const;
  
  /// Return current item index, or -1 if none
  FXint getCurrentItem() const;

  /// Change anchor item index
  void setAnchorItem(FXint index);
  
  /// Return anchor item index, or -1 if none
  FXint getAnchorItem() const { return anchor; }

  /// Return index of item under cursor, or -1 if none
  FXint getCursorItem() const;

  /// Sort items
  void sortItems();
  
  /// Change text font
  void setFont(FXFont* fnt);
  
  /// Return text font
  FXFont* getFont() const;

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
  
  /// Change maximum item space for each item
  void setItemSpace(FXint s);
  
  /// Return maximum item space
  FXint getItemSpace() const;

  /// Get the current icon list style
  FXuint getListStyle() const;

  /// Set the current icon list style.
  void setListStyle(FXuint style);

  /// Set the status line help text for this widget
  void setHelpText(const FXString& text);

  /// Get the status line help text for this widget
  const FXString& getHelpText() const;

  /// Destructor
  virtual ~FXIconList();
  };

%clear FXint index;
%clear FXint newindex;
%clear FXint oldindex;
%clear FXint headerIndex;

DECLARE_FXOBJECT_VIRTUALS(FXIconList)
DECLARE_FXID_VIRTUALS(FXIconList)
DECLARE_FXDRAWABLE_VIRTUALS(FXIconList)
DECLARE_FXWINDOW_VIRTUALS(FXIconList)
DECLARE_FXSCROLLAREA_VIRTUALS(FXIconList)
DECLARE_FXICONLIST_VIRTUALS(FXIconList)

%{
static swig_type_info *FXIconList_dynamic_cast(void **ptr) {
    FXIconList **ppIconList = reinterpret_cast<FXIconList **>(ptr);
    FXFileList *pFileList=dynamic_cast<FXFileList*>(*ppIconList);
    if(pFileList){
      *ptr=reinterpret_cast<void*>(pFileList);
      return SWIG_TypeQuery("FXFileList *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXIconList, FXIconList_dynamic_cast);

