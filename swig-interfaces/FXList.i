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

/// List styles
enum {
  LIST_EXTENDEDSELECT    = 0,             /// Extended selection mode allows for drag-selection of ranges of items
  LIST_SINGLESELECT      = 0x00100000,    /// Single selection mode allows up to one item to be selected
  LIST_BROWSESELECT      = 0x00200000,    /// Browse selection mode enforces one single item to be selected at all times
  LIST_MULTIPLESELECT    = 0x00300000,    /// Multiple selection mode is used for selection of individual items
  LIST_AUTOSELECT        = 0x00400000,    /// Automatically select under cursor
  LIST_NORMAL            = LIST_EXTENDEDSELECT
  };


class FXIcon;
class FXFont;
class FXList;



/// List item
class FXListItem : public FXObject {
protected:
  FXString  label;
  FXIcon   *icon; 
  void     *data; 
  FXuint    state;
  FXint     x,y;
protected:
  FXListItem();
  virtual void draw(const FXList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual FXint hitItem(const FXList* list,FXint x,FXint y) const;
public:
  enum {
    SELECTED  = 1,
    FOCUS     = 2,
    DISABLED  = 4,
    DRAGGABLE = 8,
    ICONOWNED = 16
    };
public:
  %extend {
    FXListItem(const FXString& text,FXIcon* ic=NULL,void* ITEMDATA=NULL){
      return new FXRbListItem(text,ic,ITEMDATA);
      }
    }

  const FXString& getText() const;
  FXIcon* getIcon() const;

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

  virtual ~FXListItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXListItem)
DECLARE_FXLISTITEM_VIRTUALS(FXListItem)

%{
static swig_type_info *FXListItem_dynamic_cast(void **ptr) {
    FXListItem **ppListItem = reinterpret_cast<FXListItem **>(ptr);
    FXColorItem *pColorItem=dynamic_cast<FXColorItem*>(*ppListItem);
    if(pColorItem){
      *ptr=reinterpret_cast<void*>(pColorItem);
      return SWIG_TypeQuery("FXColorItem *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXListItem, FXListItem_dynamic_cast);

%typemap(check) FXint LISTITEM_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumItems()) {
    rb_raise(rb_eIndexError, "list item index out of bounds");
  }
}

%apply FXint LISTITEM_INDEX { FXint index, FXint newindex, FXint oldindex };

%alias FXList::appendItem "<<";

/**
* A List Widget displays a list of items, each with a text and
* optional icon.  When an item's selected state changes, the list sends
* a SEL_SELECTED or SEL_DESELECTED message.  A change of the current
* item is signified by the SEL_CHANGED message.
* The list sends SEL_COMMAND messages when the user clicks on an item,
* and SEL_CLICKED, SEL_DOUBLECLICKED, and SEL_TRIPLECLICKED when the user
* clicks once, twice, or thrice, respectively.
* When items are added, replaced, or removed, the list sends messages of
* the type SEL_INSERTED, SEL_REPLACED, or SEL_DELETED.
* In each of these cases, the index to the item, if any, is passed in the
* 3rd argument of the message.
*/
class FXList : public FXScrollArea {
protected:
  FXListItemList items;             // Item list
  FXint          anchor;            // Anchor item
  FXint          current;           // Current item
  FXint          extent;            // Extent item
  FXint          cursor;            // Cursor item
  FXint          viewable;          // Viewable item
  FXFont        *font;              // Font
  FXColor        textColor;         // Text color
  FXColor        selbackColor;      // Selected back color
  FXColor        seltextColor;      // Selected text color
  FXint          listWidth;         // List width
  FXint          listHeight;        // List height
  FXint          visible;           // Number of rows high
  FXString       help;              // Help text
  FXint          grabx;             // Grab point x
  FXint          graby;             // Grab point y
  FXString       lookup;            // Lookup string
  FXbool         state;             // State of item
protected:
  FXList();
  void recompute();
  virtual FXListItem *createItem(const FXString& text,FXIcon* icon,void* ptr);
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
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_EVENT);
  long onClicked(FXObject*,FXSelector,void* PTR_INT);
  long onDoubleClicked(FXObject*,FXSelector,void* PTR_INT);
  long onTripleClicked(FXObject*,FXSelector,void* PTR_INT);
  long onCommand(FXObject*,FXSelector,void* PTR_INT);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onTipTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onLookupTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
public:
  static FXint ascending(const FXListItem* a,const FXListItem* b);
  static FXint descending(const FXListItem* a,const FXListItem* b);
  static FXint ascendingCase(const FXListItem* a,const FXListItem* b);
  static FXint descendingCase(const FXListItem* a,const FXListItem* b);
public:
  enum {
    ID_LOOKUPTIMER=FXScrollArea::ID_LAST,
    ID_LAST
    };
public:
  %extend {
    /// Construct a list with initially no items in it
    FXList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=LIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbList(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return the number of items in the list
  FXint getNumItems() const;

  /// Return number of visible items
  FXint getNumVisible() const;

  /// Change the number of visible items
  void setNumVisible(FXint nvis);
  
  /// Return the item at the given index
  FXListItem *getItem(FXint index) const;
  
  %extend {
    /// Replace the item with a [possibly subclassed] item
    FXint setItem(FXint index,FXListItem* item,FXbool notify=false){
      // Save pointer to the soon-to-be-destroyed item
      FXListItem* oldItem=self->getItem(index);

      // Do the deed
      if(item->isMemberOf(FXMETACLASS(FXRbListItem)))
        dynamic_cast<FXRbListItem*>(item)->owned=TRUE;
      FXint result=self->setItem(index,item,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(oldItem);

      // Done
      return result;
      }

    /// Replace item's text, icon, and user-data pointer
    FXint setItem(FXint index,const FXString& text,FXIcon *icon=NULL,void* ITEMDATA=NULL,FXbool notify=false){
      // Save pointer to the soon-to-be-destroyed item
      FXListItem* oldItem=self->getItem(index);

      // Do the deed
      FXint result=self->setItem(index,text,icon,ITEMDATA,notify);
      
      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(oldItem);

      // Done
      return result;
      }
  }

  /// Fill list by appending items from array of strings
  FXint fillItems(const FXchar** strings,FXIcon *icon=NULL,void* ptr=NULL,FXbool notify=false);

  %extend {
    /// Insert a new [possibly subclassed] item at the given index
    FXint insertItem(FXint index,FXListItem* item,FXbool notify=false){
      if(item->isMemberOf(FXMETACLASS(FXRbListItem)))
        dynamic_cast<FXRbListItem*>(item)->owned=TRUE;
      return self->insertItem(index,item,notify);
      }
  }

  /// Insert item at index with given text, icon, and user-data pointer
  FXint insertItem(FXint index,const FXString& text,FXIcon *icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  %extend {
    /// Append a [possibly subclassed] item to the list
    FXint appendItem(FXListItem* item,FXbool notify=false){
      if(item->isMemberOf(FXMETACLASS(FXRbListItem)))
        dynamic_cast<FXRbListItem*>(item)->owned=TRUE;
      return self->appendItem(item,notify);
      }
  }
  
  /// Append new item with given text and optional icon, and user-data pointer
  FXint appendItem(const FXString& text,FXIcon *icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  %extend {
    /// Prepend a [possibly subclassed] item to the list
    FXint prependItem(FXListItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbListItem)))
        dynamic_cast<FXRbListItem*>(item)->owned=TRUE;
      return self->prependItem(item,notify);
      }
  }
  
  /// Prepend new item with given text and optional icon, and user-data pointer
  FXint prependItem(const FXString& text,FXIcon *icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  /// Move item from oldindex to newindex
  FXint moveItem(FXint newindex,FXint oldindex,FXbool notify=false);

  /// Extract item from list
  FXListItem* extractItem(FXint index,FXbool notify=false);

  %extend {
    /// Remove item from list
    void removeItem(FXint index,FXbool notify=false){
      // Save pointer to the soon-to-be-destroyed item
      FXListItem* item=self->getItem(index);

      // Do the deed
      self->removeItem(index,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(item);
      }
  
    /// Remove all items from list
    void clearItems(FXbool notify=false){
      // Save pointers to the soon-to-be-destroyed items
      FXObjectListOf<FXListItem> items;
      for(FXint i=0; i<self->getNumItems(); i++) items.append(self->getItem(i));

      // Do the deed
      self->clearItems(notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint j=0; j<items.no(); j++) FXRbUnregisterRubyObj(items[j]);
      }
  }
  
  /// Return item width
  FXint getItemWidth(FXint index) const;

  /// Return item height
  FXint getItemHeight(FXint index) const;

  /// Return item hit code: 0 no hit; 1 hit the icon; 2 hit the text
  FXint hitItem(FXint index,FXint x,FXint y) const;
  
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
    void makeItemVisible(FXListItem* item){
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
  
  /// Change item icon
  void setItemIcon(FXint index,FXIcon* icon,FXbool owned=false);
  
  /// Return item icon, if any
  FXIcon* getItemIcon(FXint index) const;
  
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
  
  /// Return TRUE if item is selected
  FXbool isItemSelected(FXint index) const;
  
  /// Return TRUE if item is current
  FXbool isItemCurrent(FXint index) const;
  
  /// Return TRUE if item is visible
  FXbool isItemVisible(FXint index) const;
  
  /// Return TRUE if item is enabled
  FXbool isItemEnabled(FXint index) const;
  
  /// Repaint item
  void updateItem(FXint index) const;
  
  /// Return current item, if any
  FXint getCurrentItem() const;

  /// Change anchor item
  void setAnchorItem(FXint index);
  
  /// Return anchor item, if any
  FXint getAnchorItem() const;

  /// Sort items using current sort function
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
  
  /// Return list style
  FXuint getListStyle() const;
  
  /// Change list style
  void setListStyle(FXuint style);
  
  /// Set the status line help text for this list
  void setHelpText(const FXString& text);
  
  /// Get the status line help text for this list
  const FXString& getHelpText() const;

  /// Destructor
  virtual ~FXList();
  };
  
%clear FXint index;
%clear FXint newindex;
%clear FXint oldindex;

DECLARE_FXOBJECT_VIRTUALS(FXList)
DECLARE_FXID_VIRTUALS(FXList)
DECLARE_FXDRAWABLE_VIRTUALS(FXList)
DECLARE_FXWINDOW_VIRTUALS(FXList)
DECLARE_FXSCROLLAREA_VIRTUALS(FXList)
DECLARE_FXLIST_VIRTUALS(FXList)

%{
static swig_type_info *FXList_dynamic_cast(void **ptr) {
    FXList **ppList = reinterpret_cast<FXList **>(ptr);
    FXColorList *pColorList=dynamic_cast<FXColorList*>(*ppList);
    if(pColorList){
      *ptr=reinterpret_cast<void*>(pColorList);
      return SWIG_TypeQuery("FXColorList *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXListItem, FXListItem_dynamic_cast);

