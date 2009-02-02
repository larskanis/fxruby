/********************************************************************************
*                                                                               *
*                        L i s t   B o x   W i d g e t                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXListBox.h 2255 2005-11-30 13:55:50Z lyle $                         *
********************************************************************************/
#ifndef FXLISTBOX_H
#define FXLISTBOX_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/// List Box styles
enum {
  LISTBOX_NORMAL         = 0          // Normal style
  };


class FXButton;
class FXMenuButton;
class FXList;
class FXPopup;


/**
* The List Box is a control to select one of a list of options.  It looks
* similar to a Combo Box except that List Box yields integer numbers only.
* When an option is selected, List Box will send an SEL_COMMAND with the
* index of the opton.  While manipulating the list, it may send SEL_CHANGED
* messages to indicate which option the cursor is hovering over.
* The List Box is able to receive ID_GETINTVALUE and ID_SETINTVALUE which
* will retrieve the current option or change the selected option.
*/
class FXAPI FXListBox : public FXPacker {
  FXDECLARE(FXListBox)
protected:
  FXButton      *field;
  FXMenuButton  *button;
  FXList        *list;
  FXPopup       *pane;
protected:
  FXListBox(){}
private:
  FXListBox(const FXListBox&);
  FXListBox &operator=(const FXListBox&);
public:
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusSelf(FXObject*,FXSelector,void*);
  long onMouseWheel(FXObject*,FXSelector,void*);
  long onFieldButton(FXObject*,FXSelector,void*);
  long onListUpdate(FXObject*,FXSelector,void*);
  long onListClicked(FXObject*,FXSelector,void*);
  long onListChanged(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
public:
  enum {
    ID_LIST=FXPacker::ID_LAST,
    ID_FIELD,
    ID_LAST
    };
public:

  /// Constructor
  FXListBox(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|LISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Perform layout
  virtual void layout();

  /// Enable drive box
  virtual void enable();

  /// Disable drive box
  virtual void disable();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Return the number of items in the list
  FXint getNumItems() const;

  /// Return the number of visible items
  FXint getNumVisible() const;

  /// Set the number of visible items
  void setNumVisible(FXint nvis);

  /// Return true if current item
  FXbool isItemCurrent(FXint index) const;

  /// Set the current item (index is zero-based)
  virtual void setCurrentItem(FXint index,FXbool notify=FALSE);

  /// Get the current item's index
  FXint getCurrentItem() const;

  /// Return the item at the given index
  FXString getItem(FXint index) const;

  /// Replace the item at index
  FXint setItem(FXint index,const FXString& text,FXIcon* icon=NULL,void* ptr=NULL);

  /// Fill list box by appending items from array of strings
  FXint fillItems(const FXchar** strings,FXIcon* icon=NULL,void* ptr=NULL);

  /// Fill list box by appending items from newline separated strings
  FXint fillItems(const FXString& strings,FXIcon* icon=NULL,void* ptr=NULL);

  /// Insert a new item at index
  FXint insertItem(FXint index,const FXString& text,FXIcon* icon=NULL,void* ptr=NULL);

  /// Add an item to the end of the list
  FXint appendItem(const FXString& text,FXIcon* icon=NULL,void* ptr=NULL);

  /// Prepend an item to the list
  FXint prependItem(const FXString& text,FXIcon* icon=NULL,void* ptr=NULL);

  /// Move item from oldindex to newindex
  FXint moveItem(FXint newindex,FXint oldindex);

  /// Extract item from list
  FXListItem* extractItem(FXint index);

  /// Remove this item from the list
  void removeItem(FXint index);

  /// Remove all items from the list
  void clearItems();

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
  FXint findItemByData(const void *ptr,FXint start=-1,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Set text for specified item
  void setItemText(FXint index,const FXString& text);

  /// Get text for specified item
  FXString getItemText(FXint index) const;

  /// Change item icon, deleting old one if it was owned
  void setItemIcon(FXint index,FXIcon* icon,FXbool owned=FALSE);

  /// Return icon of item at index
  FXIcon* getItemIcon(FXint index) const;

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
  virtual ~FXListBox();
  };

}

#endif
