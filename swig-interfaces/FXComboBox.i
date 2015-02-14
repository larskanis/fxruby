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

// ComboBox styles
enum {
  COMBOBOX_NO_REPLACE     = 0,                  // Leave the list the same
  COMBOBOX_REPLACE        = 0x00020000,         // Replace current item with typed text
  COMBOBOX_INSERT_BEFORE  = 0x00040000,         // Typed text inserted before current
  COMBOBOX_INSERT_AFTER   = 0x00060000,         // Typed text inserted after current
  COMBOBOX_INSERT_FIRST   = 0x00080000,         // Typed text inserted at begin of list
  COMBOBOX_INSERT_LAST    = 0x00090000,         // Typed text inserted at end of list
  COMBOBOX_STATIC         = 0x00100000,         // Unchangable text box
  COMBOBOX_NORMAL         = 0
  };


class FXTextField;
class FXMenuButton;
class FXList;
class FXPopup;

%typemap(check) FXint COMBOBOX_ITEM_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumItems()) {
    rb_raise(rb_eIndexError, "combobox item index out of bounds");
  }
}

%typemap(check) FXint COMBOBOX_ITEM_INDEX_OR_NONE {
  if ($1 < -1 || $1 >= arg1->getNumItems()) {
    rb_raise(rb_eIndexError, "combobox item index out of bounds");
  }
}

%apply FXint COMBOBOX_ITEM_INDEX { FXint index, FXint newindex, FXint oldindex };
%apply FXint COMBOBOX_ITEM_INDEX_OR_NONE { FXint indexz };

%rename("justify=") FXComboBox::setJustify(FXuint);
%rename("justify")  FXComboBox::getJustify() const;

/**
* A Combo Box provides a way to select a string from a list of strings.
* Unless COMBOBOX_STATIC is passed, it also allows the user to enter a new
* string into the text field, for example if the desired entry is not in the
* list of strings.  Passing COMBOBOX_REPLACE, COMBOBOX_INSERT_BEFORE, COMBOBOX_INSERT_AFTER,
* COMBOBOX_INSERT_FIRST, or COMBOBOX_INSERT_LAST causes a newly entered text to replace the
* current one in the list, or be added before or after the current entry, or to be added at
* the beginning or end of the list.
* Combo Box is intended to enter text; if you need to enter a choice from a list of
* options, it is recommended that the List Box widget is used instead.
* When the text in the field is changed, a SEL_COMMAND will be send to the target.
* The Combo Box can also receive ID_GETSTRINGVALUE and ID_SETSTRINGVALUE and so
* on, which will behave similar to Text Field in that they will retrieve or update
* the value of the field.
*/
class FXComboBox : public FXPacker {
public:
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onTextButton(FXObject*,FXSelector,void* PTR_IGNORE);
  long onTextChanged(FXObject*,FXSelector,void* PTR_CSTRING);
  long onTextCommand(FXObject*,FXSelector,void* PTR_CSTRING);
  long onListClicked(FXObject*,FXSelector,void* PTR_INT);
  long onFwdToText(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onUpdFmText(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_LIST=FXPacker::ID_LAST,
    ID_TEXT,
    ID_LAST
    };
public:
  %extend {
    /// Constructor
    FXComboBox(FXComposite *p,FXint cols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=COMBOBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbComboBox(p,cols,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Return true if combobox is editable
  FXbool isEditable() const;

  /// Set editable state
  void setEditable(FXbool edit=TRUE);

  /// Set the text
  void setText(const FXString& text);

  /// Get the text
  FXString getText() const;

  /// Set the number of columns
  void setNumColumns(FXint cols);

  /// Get the number of columns
  FXint getNumColumns() const;

  /// Change text justification mode; default is JUSTIFY_LEFT
  void setJustify(FXuint mode);

  /// Return text justification mode
  FXuint getJustify() const;

  /// Return the number of items in the list
  FXint getNumItems() const;

  /// Return the number of visible items
  FXint getNumVisible() const;

  /// Set the number of visible items
  void setNumVisible(FXint nvis);

  /// Return true if current item
  FXbool isItemCurrent(FXint index) const;

  /// Set the current item (index is zero-based)
  void setCurrentItem(FXint indexz,FXbool notify=FALSE);

  /// Get the current item's index
  FXint getCurrentItem() const;

  /// Return the item at the given index
  FXString getItem(FXint index) const;

  /// Replace the item at index
  FXint setItem(FXint index,const FXString& text,void* ITEMDATA=NULL);

  /// Fill combo box by appending items from array of strings
  FXint fillItems(const FXchar** strings);

  /// Insert a new item at index
  FXint insertItem(FXint index,const FXString& text,void* ITEMDATA=NULL);

  /// Append an item to the list
  FXint appendItem(const FXString& text,void* ITEMDATA=NULL);

  /// Prepend an item to the list
  FXint prependItem(const FXString& text,void* ITEMDATA=NULL);

  /// Move item from oldindex to newindex
  FXint moveItem(FXint newindex,FXint oldindex);

  /// Remove this item from the list
  void removeItem(FXint index);

  /// Remove all items from the list
  void clearItems();

  /**
   * Search items by name, beginning from item start.  If the start item
   * is -1 the search will start at the first item in the list.  Flags
   * may be SEARCH_FORWARD or SEARCH_BACKWARD to control the search
   * direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
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
  * Return -1 if no matching item is found.
  */
  FXint findItemByData(const void *ITEMDATA,FXint start=-1,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Set text for specified item
  void setItemText(FXint index,const FXString& text);

  /// Get text for specified item
  FXString getItemText(FXint index) const;

  %extend {
    /// Set data pointer for specified item
    void setItemData(FXint index, VALUE ptr) {
      self->setItemData(index, (void*) ptr);
      }

    /// Get data pointer for specified item
    VALUE getItemData(FXint index) const {
      return self->getItemData(index) ? (VALUE) self->getItemData(index) : Qnil;
      }
  }

  /// Is the pane shown
  FXbool isPaneShown() const;

  /// Sort items using current sort function
  void sortItems();

  /// Set text font
  void setFont(FXFont* fnt);

  /// Get text font
  FXFont* getFont() const;

  /// Set the combobox style.
  void setComboStyle(FXuint mode);

  /// Get the combobox style.
  FXuint getComboStyle() const;

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
  virtual ~FXComboBox();
  };

%clear FXint index;
%clear FXint indexz;
%clear FXint newindex;
%clear FXint oldindex;

DECLARE_FXOBJECT_VIRTUALS(FXComboBox)
DECLARE_FXID_VIRTUALS(FXComboBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXComboBox)
DECLARE_FXWINDOW_VIRTUALS(FXComboBox)

