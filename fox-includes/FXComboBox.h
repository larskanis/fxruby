/********************************************************************************
*                                                                               *
*                       C o m b o   B o x   W i d g e t                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXComboBox.h 2342 2006-02-10 14:24:44Z lyle $                        *
********************************************************************************/
#ifndef FXCOMBOBOX_H
#define FXCOMBOBOX_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/// ComboBox styles
enum {
  COMBOBOX_NO_REPLACE     = 0,                  /// Leave the list the same
  COMBOBOX_REPLACE        = 0x00020000,         /// Replace current item with typed text
  COMBOBOX_INSERT_BEFORE  = 0x00040000,         /// Typed text inserted before current
  COMBOBOX_INSERT_AFTER   = 0x00060000,         /// Typed text inserted after current
  COMBOBOX_INSERT_FIRST   = 0x00080000,         /// Typed text inserted at begin of list
  COMBOBOX_INSERT_LAST    = 0x00090000,         /// Typed text inserted at end of list
  COMBOBOX_STATIC         = 0x00100000,         /// Unchangable text box
  COMBOBOX_NORMAL         = 0                   /// Can type text but list is not changed
  };


class FXTextField;
class FXMenuButton;
class FXList;
class FXPopup;


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
class FXAPI FXComboBox : public FXPacker {
  FXDECLARE(FXComboBox)
protected:
  FXTextField   *field;
  FXMenuButton  *button;
  FXList        *list;
  FXPopup       *pane;
protected:
  FXComboBox(){}
private:
  FXComboBox(const FXComboBox&);
  FXComboBox &operator=(const FXComboBox&);
public:
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusSelf(FXObject*,FXSelector,void*);
  long onMouseWheel(FXObject*,FXSelector,void*);
  long onTextButton(FXObject*,FXSelector,void*);
  long onTextChanged(FXObject*,FXSelector,void*);
  long onTextCommand(FXObject*,FXSelector,void*);
  long onListClicked(FXObject*,FXSelector,void*);
  long onFwdToText(FXObject*,FXSelector,void*);
  long onUpdFmText(FXObject*,FXSelector,void*);
public:
  enum {
    ID_LIST=FXPacker::ID_LAST,
    ID_TEXT,
    ID_LAST
    };
public:

  /// Construct a Combo Box widget with room to display cols columns of text
  FXComboBox(FXComposite *p,FXint cols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=COMBOBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Enable combo box
  virtual void enable();

  /// Disable combo box
  virtual void disable();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

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

  /// Set the number of visible items in the drop down list
  void setNumVisible(FXint nvis);

  /// Return true if current item
  FXbool isItemCurrent(FXint index) const;

  /// Set the current item (index is zero-based)
  void setCurrentItem(FXint index,FXbool notify=FALSE);

  /// Get the current item's index
  FXint getCurrentItem() const;

  /// Return the item at the given index
  FXString getItem(FXint index) const;

  /// Replace the item at index
  FXint setItem(FXint index,const FXString& text,void* ptr=NULL);

  /// Fill combo box by appending items from array of strings
  FXint fillItems(const FXchar** strings);

  /// Fill combo box by appending items from newline separated strings
  FXint fillItems(const FXString& strings);

  /// Insert a new item at index
  FXint insertItem(FXint index,const FXString& text,void* ptr=NULL);

  /// Append an item to the list
  FXint appendItem(const FXString& text,void* ptr=NULL);

  /// Prepend an item to the list
  FXint prependItem(const FXString& text,void* ptr=NULL);

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
  */
  FXint findItemByData(const void *ptr,FXint start=-1,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Set text for specified item
  void setItemText(FXint index,const FXString& text);

  /// Get text for specified item
  FXString getItemText(FXint index) const;

  /// Set data pointer for specified item
  void setItemData(FXint index,void* ptr) const;

  /// Get data pointer for specified item
  void* getItemData(FXint index) const;

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

  /// Set window background color
  virtual void setBackColor(FXColor clr);

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

  /// Return sort function
  FXListSortFunc getSortFunc() const;

  /// Change sort function
  void setSortFunc(FXListSortFunc func);

  /// Set the combobox help text
  void setHelpText(const FXString& txt);

  /// Get the combobox help text
  const FXString& getHelpText() const;

  /// Set the tool tip message for this combobox
  void setTipText(const FXString& txt);

  /// Get the tool tip message for this combobox
  const FXString& getTipText() const;

  /// Save combobox to a stream
  virtual void save(FXStream& store) const;

  /// Load combobox from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXComboBox();
  };

}

#endif
