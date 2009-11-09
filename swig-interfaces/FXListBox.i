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

/// List Box styles
enum {
  LISTBOX_NORMAL         = 0          // Normal style
  };

class FXButton;
class FXMenuButton;
class FXList;
class FXPopup;

%alias FXListBox::appendItem(const FXString& text,FXIcon* icon,void* ITEMDATA,FXbool notify) "<<";

%typemap(check) FXint LISTBOX_ITEM_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumItems()) {
    rb_raise(rb_eIndexError, "list box item index out of bounds");
  }
}

%apply FXint LISTBOX_ITEM_INDEX { FXint index, FXint newindex, FXint oldindex };

%rename("shrinkWrap=")      FXListBox::setShrinkWrap(FXbool);
%rename("shrinkWrap")       FXListBox::getShrinkWrap() const;
%rename("menuShown?")				FXListBox::isMenuShown() const;
%rename("menuShown=")				FXListBox::showMenu(FXbool);

// Add alias for backwards compatibility with FXRuby 1.6
%alias FXListBox::isMenuShown() const "paneShown?";

/**
* The List Box is a control to select one of a list of options.  It looks
* similar to a Combo Box except that List Box yields integer numbers only.
* When an option is selected, List Box will send an SEL_COMMAND with the
* index of the opton.  While manipulating the list, it may send SEL_CHANGED
* messages to indicate which option the cursor is hovering over.
* The List Box is able to receive ID_GETINTVALUE and ID_SETINTVALUE which
* will retrieve the current option or change the selected option.
* When items are added, replaced, or removed, the list sends messages of
* the type SEL_INSERTED, SEL_REPLACED, or SEL_DELETED, with the index of
* the affected item as argument.
*/
class FXListBox : public FXPacker {
protected:
  FXButton      *field;
  FXMenuButton  *button;
  FXList        *list;
  FXPopup       *pane;
protected:
  FXListBox(){}
public:
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onFieldButton(FXObject*,FXSelector,void* PTR_IGNORE);
  long onListUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
  long onListClicked(FXObject*,FXSelector,void* PTR_INT);
  long onListCommand(FXObject*,FXSelector,void* PTR_IVAL);
  long onListForward(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
public:
  enum {
    ID_LIST=FXPacker::ID_LAST,
    ID_FIELD,
    ID_LAST
    };
public:
  %extend {
    /// Constructor
    FXListBox(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|LISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbListBox(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Return the number of items in the list
  FXint getNumItems() const;

  /// Return the number of visible items
  FXint getNumVisible() const;

  /// Set the number of visible items
  void setNumVisible(FXint nvis);

  /// Return true if current item
  FXbool isItemCurrent(FXint index) const;

  /// Get the current item's index
  FXint getCurrentItem() const;

  /// Return the item at the given index
  FXString getItem(FXint index) const;

  /// Replace the item at index
  FXint setItem(FXint index,const FXString& text,FXIcon* icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  /// Fill list box by appending items from array of strings
  FXint fillItems(const FXchar** strings,FXIcon* icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  /// Insert a new item at index
  FXint insertItem(FXint index,const FXString& text,FXIcon* icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  /// Add an item to the end of the list
  FXint appendItem(const FXString& text,FXIcon* icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  /// Prepend an item to the list
  FXint prependItem(const FXString& text,FXIcon* icon=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  /// Move item from oldindex to newindex
  FXint moveItem(FXint newindex,FXint oldindex,FXbool notify=false);

  /// Extract item from list
  FXListItem* extractItem(FXint index,FXbool notify=false);

  /// Remove this item from the list
  void removeItem(FXint index,FXbool notify=false);

  /// Remove all items from the list
  void clearItems(FXbool notify=false);

  /**
  * Search items for item by name, starting from start item; the
  * flags argument controls the search direction, and case sensitivity.
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

  /// Set text for specified item
  void setItemText(FXint index,const FXString& text);

  /// Get text for specified item
  FXString getItemText(FXint index) const;

  /// Change item icon
  void setItemIcon(FXint index,FXIcon* icon,FXbool owned=false);
  
  /// Return icon of item at index
  FXIcon* getItemIcon(FXint index) const;
  
  %extend {
    /// Set data pointer for specified item
    void setItemData(FXint index,VALUE ptr) {
      self->setItemData(index, (void*) ptr);
      }

    /// Get data pointer for specified item
    VALUE getItemData(FXint index) const {
      return self->getItemData(index) ? (VALUE) self->getItemData(index) : Qnil;
      }
  }

	/// Show or hide menu
	void showMenu(FXbool shw);
	
	/// Is the menu pane shown
	FXbool isMenuShown() const;

  /// Sort items using current sort function
  void sortItems();

  /// Set text font
  void setFont(FXFont* fnt);

  /// Get text font
  FXFont* getFont() const;

  /// Change popup pane shrinkwrap mode
  void setShrinkWrap(FXbool flag);
  
  /// Return popup pane shrinkwrap mode
  FXbool getShrinkWrap() const;
  
  /// Get background color
  FXColor getBackColor() const;

  /// Change text color
  void setTextColor(FXColor clr);
  
  /// Return text color
  FXColor getTextColor() const;

  /// Change selected background color
  void setSelBackColor(FXColor clr);
  
  /// Return selected background color
  FXColor getSelBackColor() const;

  /// Change selected text color
  void setSelTextColor(FXColor clr);
  
  /// Return selected text color
  FXColor getSelTextColor() const;

  /// Set the combobox help text
  void setHelpText(const FXString& txt);

  /// Get the combobox help text
  const FXString& getHelpText() const;

  /// Set the tool tip message for this combobox
  void setTipText(const FXString& txt);

  /// Get the tool tip message for this combobox
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXListBox();
  };

%clear FXint index;
%clear FXint newindex;
%clear FXint oldindex;

DECLARE_FXOBJECT_VIRTUALS(FXListBox)
DECLARE_FXID_VIRTUALS(FXListBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXListBox)
DECLARE_FXWINDOW_VIRTUALS(FXListBox)
DECLARE_FXLISTBOX_VIRTUALS(FXListBox)

%{
static swig_type_info *FXListBox_dynamic_cast(void **ptr) {
    FXListBox **ppListBox = reinterpret_cast<FXListBox **>(ptr);
    FXDriveBox *pDriveBox=dynamic_cast<FXDriveBox*>(*ppListBox);
    if(pDriveBox){
      *ptr=reinterpret_cast<void*>(pDriveBox);
      return SWIG_TypeQuery("FXDriveBox *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXListBox, FXListBox_dynamic_cast);

