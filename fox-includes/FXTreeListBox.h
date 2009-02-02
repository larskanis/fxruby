/********************************************************************************
*                                                                               *
*                      T r e e   L i s t   B o x   W i d g e t                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2008 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXTreeListBox.h 2867 2008-05-29 21:50:28Z lyle $                     *
********************************************************************************/
#ifndef FXTREELISTBOX_H
#define FXTREELISTBOX_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/// Tree List Box styles
enum {
  TREELISTBOX_NORMAL         = 0          /// Normal style
  };


class FXButton;
class FXMenuButton;
class FXTreeList;
class FXPopup;


/**
* The Tree List Box behaves very much like a List Box, except that
* it supports a hierarchical, tree structured display of the items.
* When an item is selected it issues a SEL_COMMAND message with the
* pointer to the item.  While manipulating the tree list, it may send
* SEL_CHANGED messages to indicate which item the cursor is hovering over.
* When items are added, replaced, or removed, the list sends messages of
* the type SEL_INSERTED, SEL_REPLACED, or SEL_DELETED, with the pointer to
* the affected item as argument.
*/
class FXAPI FXTreeListBox : public FXPacker {
  FXDECLARE(FXTreeListBox)
protected:
  FXButton      *field;
  FXMenuButton  *button;
  FXTreeList    *tree;
  FXPopup       *pane;
protected:
  FXTreeListBox(){}
private:
  FXTreeListBox(const FXTreeListBox&);
  FXTreeListBox& operator=(const FXTreeListBox&);
public:
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusSelf(FXObject*,FXSelector,void*);
  long onMouseWheel(FXObject*,FXSelector,void*);
  long onFieldButton(FXObject*,FXSelector,void*);
  long onTreeUpdate(FXObject*,FXSelector,void*);
  long onTreeForward(FXObject*,FXSelector,void*);
  long onTreeClicked(FXObject*,FXSelector,void*);
  long onTreeCommand(FXObject*,FXSelector,void*);
public:
  enum{
    ID_TREE=FXPacker::ID_LAST,
    ID_FIELD,
    ID_LAST
    };
public:

  /// Construct tree list box
  FXTreeListBox(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|TREELISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Perform layout
  virtual void layout();

  /// Enable widget
  virtual void enable();

  /// Disable widget
  virtual void disable();

  /// Return default with
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Return number of items
  FXint getNumItems() const;

  /// Return number of visible items
  FXint getNumVisible() const;

  /// Set number of visible items to determine default height
  void setNumVisible(FXint nvis);

  /// Return first top-level item
  FXTreeItem* getFirstItem() const;

  /// Return last top-level item
  FXTreeItem* getLastItem() const;

  /// Return true if item is the current item
  FXbool isItemCurrent(const FXTreeItem* item) const;

  /// Change current item
  virtual void setCurrentItem(FXTreeItem* item,FXbool notify=false);

  /// Return current item
  FXTreeItem* getCurrentItem() const;

  /// Fill tree list box by appending items from array of strings
  FXint fillItems(FXTreeItem* father,const FXchar** strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=false);

  /// Fill tree list box by appending items from newline separated strings
  FXint fillItems(FXTreeItem* father,const FXString& strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=false);

  /// Insert [possibly subclassed] item under father before other item
  FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item,FXbool notify=false);

  /// Insert item with given text and optional icons, and user-data pointer under father before other item
  FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=false);

  /// Append [possibly subclassed] item as last child of father
  FXTreeItem* appendItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=false);

  /// Append item with given text and optional icons, and user-data pointer as last child of father
  FXTreeItem* appendItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=false);

  /// Prepend [possibly subclassed] item as first child of father
  FXTreeItem* prependItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=false);

  /// Prepend item with given text and optional icons, and user-data pointer as first child of father
  FXTreeItem* prependItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=false);

  /// Move item under father before other item
  FXTreeItem *moveItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item);

  /// Extract item
  FXTreeItem* extractItem(FXTreeItem* item,FXbool notify=false);

  /// Remove item
  void removeItem(FXTreeItem* item,FXbool notify=false);

  /// Remove all items in range [fm...to]
  void removeItems(FXTreeItem* fm,FXTreeItem* to,FXbool notify=false);

  /// Remove all items from list
  void clearItems(FXbool notify=false);

  /**
  * Search items by name, beginning from item start.  If the
  * start item is NULL the search will start at the first, top-most item
  * in the list.  Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control
  * the search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  * The option SEARCH_IGNORECASE causes a case-insensitive match.  Finally,
  * passing SEARCH_PREFIX causes searching for a prefix of the item name.
  * Return NULL if no matching item is found.
  */
  FXTreeItem* findItem(const FXString& text,FXTreeItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /**
  * Search items by associated user data, beginning from item start. If the
  * start item is NULL the search will start at the first, top-most item
  * in the list.  Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control
  * the search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  */
  FXTreeItem* findItemByData(const void *ptr,FXTreeItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Return true if item is leaf-item, i.e. has no children
  FXbool isItemLeaf(const FXTreeItem* item) const;

  /// Sort the toplevel items with the sort function
  void sortRootItems();

  /// Sort all items recursively
  void sortItems();

  /// Sort child items of item
  void sortChildItems(FXTreeItem* item);

  /// Change item label
  void setItemText(FXTreeItem* item,const FXString& text);

  /// Return item label
  FXString getItemText(const FXTreeItem* item) const;

  /// Change item's open icon, delete old one if it was owned
  void setItemOpenIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=false);

  /// Return item's open icon
  FXIcon* getItemOpenIcon(const FXTreeItem* item) const;

  /// Change item's closed icon, delete old one if it was owned
  void setItemClosedIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=false);

  /// Return item's closed icon
  FXIcon* getItemClosedIcon(const FXTreeItem* item) const;

  /// Change item's user data
  void setItemData(FXTreeItem* item,void* ptr) const;

  /// Return item's user data
  void* getItemData(const FXTreeItem* item) const;

  /// Return item sort function
  FXTreeListSortFunc getSortFunc() const;

  /// Change item sort function
  void setSortFunc(FXTreeListSortFunc func);

  /// Show or hide menu
  void showMenu(FXbool shw);

  /// Is the menu pane shown
  FXbool isMenuShown() const;

  /// Change font
  void setFont(FXFont* fnt);

  /// Return font
  FXFont* getFont() const;

  /// Change list style
  void setListStyle(FXuint style);

  /// Return list style
  FXuint getListStyle() const;

  /// Change popup pane shrinkwrap mode
  void setShrinkWrap(FXbool flag);

  /// Return popup pane shrinkwrap mode
  FXbool getShrinkWrap() const;

  /// Change help text
  void setHelpText(const FXString& txt);

  /// Return help text
  const FXString& getHelpText() const;

  /// Change tip text
  void setTipText(const FXString& txt);

  /// Return tip text
  const FXString& getTipText() const;

  /// Save object to a stream
  virtual void save(FXStream& store) const;

  /// Load object from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXTreeListBox();
  };

}

#endif
