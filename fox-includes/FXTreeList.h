/********************************************************************************
*                                                                               *
*                         T r e e   L i s t   W i d g e t                       *
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
* $Id: FXTreeList.h 2343 2006-02-12 20:26:26Z lyle $                       *
********************************************************************************/
#ifndef FXTREELIST_H
#define FXTREELIST_H

#ifndef FXSCROLLAREA_H
#include "FXScrollArea.h"
#endif

namespace FX {


class FXIcon;
class FXFont;
class FXTreeList;
class FXDirList;


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
  TREELIST_NORMAL         = TREELIST_EXTENDEDSELECT
  };


/// Tree list Item
class FXAPI FXTreeItem : public FXObject {
  FXDECLARE(FXTreeItem)
  friend class FXTreeList;
  friend class FXDirList;
protected:
  FXTreeItem *parent;           // Parent item
  FXTreeItem *prev;             // Previous item
  FXTreeItem *next;             // Next item
  FXTreeItem *first;            // First child item
  FXTreeItem *last;             // Last child item
  FXString    label;            // Text of item
  FXIcon     *openIcon;         // Icon of item
  FXIcon     *closedIcon;       // Icon of item
  void       *data;             // Item user data pointer
  FXuint      state;            // Item state flags
  FXint       x,y;
private:
  FXTreeItem(const FXTreeItem&);
  FXTreeItem& operator=(const FXTreeItem&);
protected:
  FXTreeItem():parent(NULL),prev(NULL),next(NULL),first(NULL),last(NULL),openIcon(NULL),closedIcon(NULL),data(NULL),state(0),x(0),y(0){}
  virtual void draw(const FXTreeList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual FXint hitItem(const FXTreeList* list,FXint x,FXint y) const;
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

  /// Constructor
  FXTreeItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL):parent(NULL),prev(NULL),next(NULL),first(NULL),last(NULL),label(text),openIcon(oi),closedIcon(ci),data(ptr),state(0),x(0),y(0){}

  /// Get parent item
  FXTreeItem* getParent() const { return parent; }

  /// Get next sibling item
  FXTreeItem* getNext() const { return next; }

  /// Get previous sibling item
  FXTreeItem* getPrev() const { return prev; }

  /// Get first child item
  FXTreeItem* getFirst() const { return first; }

  /// Get las child item
  FXTreeItem* getLast() const { return last; }

  /// Get item below this one in list
  FXTreeItem* getBelow() const;

  /// Get item above this one in list
  FXTreeItem* getAbove() const;

  /// Get number of children of item
  FXint getNumChildren() const;

  /// Change item label
  virtual void setText(const FXString& txt);

  /// Get item label
  const FXString& getText() const { return label; }

  /// Change open icon, deleting the old icon if it was owned
  virtual void setOpenIcon(FXIcon* icn,FXbool owned=FALSE);

  /// Get open icon
  FXIcon* getOpenIcon() const { return openIcon; }

  /// Change closed icon, deleting the old icon if it was owned
  virtual void setClosedIcon(FXIcon* icn,FXbool owned=FALSE);

  /// Get closed icon
  FXIcon* getClosedIcon() const { return closedIcon; }

  /// Change item user data
  void setData(void* ptr){ data=ptr; }

  /// Get item user data
  void* getData() const { return data; }

  /// Make item draw as focused
  virtual void setFocus(FXbool focus);

  /// Return true if item has focus
  FXbool hasFocus() const { return (state&FOCUS)!=0; }

  /// Select item
  virtual void setSelected(FXbool selected);

  /// Return true if this item is selected
  FXbool isSelected() const { return (state&SELECTED)!=0; }

  /// Make item show as open
  virtual void setOpened(FXbool opened);

  /// Return true if this item is open
  FXbool isOpened() const { return (state&OPENED)!=0; }

  /// Expand or collapse item
  virtual void setExpanded(FXbool expanded);

  /// Return true if this item is expanded into sub items
  FXbool isExpanded() const { return (state&EXPANDED)!=0; }

  /// Enable or disable item
  virtual void setEnabled(FXbool enabled);

  /// Return true if this item is enabled
  FXbool isEnabled() const { return (state&DISABLED)==0; }

  /// Make item draggable
  virtual void setDraggable(FXbool draggable);

  /// Return true if this item is draggable
  FXbool isDraggable() const { return (state&DRAGGABLE)!=0; }

  /// Return TRUE if subitems, real or imagined
  FXbool hasItems() const { return (state&HASITEMS)!=0; }

  /// Change has items flag
  void setHasItems(FXbool flag);

  /// Return true if descendent of parent item
  FXbool isChildOf(const FXTreeItem* item) const;

  /// Return true if ancestor of child item
  FXbool isParentOf(const FXTreeItem* item) const;

  /// Return width of item as drawn in list
  virtual FXint getWidth(const FXTreeList* list) const;

  /// Return height of item as drawn in list
  virtual FXint getHeight(const FXTreeList* list) const;

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy item and free icons if owned
  virtual ~FXTreeItem();
  };



/// Tree item collate function
typedef FXint (*FXTreeListSortFunc)(const FXTreeItem*,const FXTreeItem*);



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
class FXAPI FXTreeList : public FXScrollArea {
  FXDECLARE(FXTreeList)
protected:
  FXTreeItem        *firstitem;         // First root item
  FXTreeItem        *lastitem;          // Last root item
  FXTreeItem        *anchoritem;        // Selection anchor item
  FXTreeItem        *currentitem;       // Current item
  FXTreeItem        *extentitem;        // Selection extent
  FXTreeItem        *cursoritem;        // Item under cursor
  FXTreeItem        *viewableitem;      // Visible item
  FXFont            *font;              // Font
  FXTreeListSortFunc sortfunc;          // Item sort function
  FXColor            textColor;         // Text color
  FXColor            selbackColor;      // Selected background color
  FXColor            seltextColor;      // Selected text color
  FXColor            lineColor;         // Line color
  FXint              treeWidth;         // Tree width
  FXint              treeHeight;        // Tree height
  FXint              visible;           // Number of visible items
  FXint              indent;            // Parent to child indentation
  FXint              grabx;             // Grab point x
  FXint              graby;             // Grab point y
  FXString           lookup;            // Lookup string
  FXString           tip;
  FXString           help;              // Help string
  FXbool             state;             // State of item
protected:
  FXTreeList();
  virtual FXTreeItem* createItem(const FXString& text,FXIcon* oi,FXIcon* ci,void* ptr);
  void sort(FXTreeItem*& f1,FXTreeItem*& t1,FXTreeItem*& f2,FXTreeItem*& t2,int n);
  void recompute();
private:
  FXTreeList(const FXTreeList&);
  FXTreeList& operator=(const FXTreeList&);
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
  static FXint ascending(const FXTreeItem*,const FXTreeItem*);
  static FXint descending(const FXTreeItem*,const FXTreeItem*);
  static FXint ascendingCase(const FXTreeItem*,const FXTreeItem*);
  static FXint descendingCase(const FXTreeItem*,const FXTreeItem*);
public:
  enum {
    ID_LOOKUPTIMER=FXScrollArea::ID_LAST,
    ID_LAST
    };
public:

  /// Construct a new, initially empty tree list
  FXTreeList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TREELIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Compute and return content width
  virtual FXint getContentWidth();

  /// Return content height
  virtual FXint getContentHeight();

  /// Recalculate layout
  virtual void recalc();

  /// Tree list can receive focus
  virtual bool canFocus() const;

  /// Move the focus to this window
  virtual void setFocus();

  /// Remove the focus from this window
  virtual void killFocus();

  /// Return number of items
  FXint getNumItems() const;

  /// Return number of visible items
  FXint getNumVisible() const { return visible; }

  /// Change number of visible items
  void setNumVisible(FXint nvis);

  /// Return first root item
  FXTreeItem* getFirstItem() const { return firstitem; }

  /// Return last root item
  FXTreeItem* getLastItem() const { return lastitem; }

  /// Fill tree list by appending items from array of strings
  FXint fillItems(FXTreeItem* father,const FXchar** strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Fill tree list by appending items from newline separated strings
  FXint fillItems(FXTreeItem* father,const FXString& strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Insert [possibly subclassed] item under father before other item
  FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item,FXbool notify=FALSE);

  /// Insert item with given text and optional icons, and user-data pointer under father before other item
  FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Append [possibly subclassed] item as last child of father
  FXTreeItem* appendItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=FALSE);

  /// Append item with given text and optional icons, and user-data pointer as last child of father
  FXTreeItem* appendItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Prepend [possibly subclassed] item as first child of father
  FXTreeItem* prependItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=FALSE);

  /// Prepend item with given text and optional icons, and user-data pointer as first child of father
  FXTreeItem* prependItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Move item under father before other item
  FXTreeItem *moveItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item);

  /// Extract item
  FXTreeItem* extractItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Remove item
  void removeItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Remove items in range [fm, to] inclusively
  void removeItems(FXTreeItem* fm,FXTreeItem* to,FXbool notify=FALSE);

  /// Remove all items from list
  void clearItems(FXbool notify=FALSE);

  /// Return item width
  FXint getItemWidth(const FXTreeItem* item) const { return item->getWidth(this); }

  /// Return item height
  FXint getItemHeight(const FXTreeItem* item) const { return item->getHeight(this); }

  /// Get item at x,y, if any
  virtual FXTreeItem* getItemAt(FXint x,FXint y) const;

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
  FXTreeItem* findItemByData(const void *ptr,FXTreeItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Scroll to make item visible
  virtual void makeItemVisible(FXTreeItem* item);

  /// Change item's text
  void setItemText(FXTreeItem* item,const FXString& text);

  /// Return item's text
  FXString getItemText(const FXTreeItem* item) const;

  /// Change item's open icon
  void setItemOpenIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's open icon, deleting the old icon if it was owned
  FXIcon* getItemOpenIcon(const FXTreeItem* item) const;

  /// Chance item's closed icon, deleting the old icon if it was owned
  void setItemClosedIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's closed icon
  FXIcon* getItemClosedIcon(const FXTreeItem* item) const;

  /// Change item user-data pointer
  void setItemData(FXTreeItem* item,void* ptr) const;

  /// Return item user-data pointer
  void* getItemData(const FXTreeItem* item) const;

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

  /// Enable item
  virtual FXbool enableItem(FXTreeItem* item);

  /// Disable item
  virtual FXbool disableItem(FXTreeItem* item);

  /// Select item
  virtual FXbool selectItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Deselect item
  virtual FXbool deselectItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Toggle item selection
  virtual FXbool toggleItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Extend selection from anchor item to item
  virtual FXbool extendSelection(FXTreeItem* item,FXbool notify=FALSE);

  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=FALSE);

  /// Open item
  virtual FXbool openItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Close item
  virtual FXbool closeItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Collapse tree
  virtual FXbool collapseTree(FXTreeItem* tree,FXbool notify=FALSE);

  /// Expand tree
  virtual FXbool expandTree(FXTreeItem* tree,FXbool notify=FALSE);

  /// Change current item
  virtual void setCurrentItem(FXTreeItem* item,FXbool notify=FALSE);

  /// Return current item, if any
  FXTreeItem* getCurrentItem() const { return currentitem; }

  /// Change anchor item
  void setAnchorItem(FXTreeItem* item);

  /// Return anchor item, if any
  FXTreeItem* getAnchorItem() const { return anchoritem; }

  /// Return item under cursor, if any
  FXTreeItem* getCursorItem() const { return cursoritem; }

  /// Sort all items recursively
  void sortItems();

  /// Sort root items
  void sortRootItems();

  /// Sort children of item
  void sortChildItems(FXTreeItem* item);

  /// Return sort function
  FXTreeListSortFunc getSortFunc() const { return sortfunc; }

  /// Change sort function
  void setSortFunc(FXTreeListSortFunc func){ sortfunc=func; }

  /// Change text font
  void setFont(FXFont* fnt);

  /// Return text font
  FXFont* getFont() const { return font; }

  /// Change parent-child indent amount
  void setIndent(FXint in);

  /// Return parent-child indent amount
  FXint getIndent() const { return indent; }

  /// Return normal text color
  FXColor getTextColor() const { return textColor; }

  /// Change normal text color
  void setTextColor(FXColor clr);

  /// Return selected text background
  FXColor getSelBackColor() const { return selbackColor; }

  /// Change selected text background
  void setSelBackColor(FXColor clr);

  /// Return selected text color
  FXColor getSelTextColor() const { return seltextColor; }

  /// Change selected text color
  void setSelTextColor(FXColor clr);

  /// Return line color
  FXColor getLineColor() const { return lineColor; }

  /// Change line color
  void setLineColor(FXColor clr);

  /// Return list style
  FXuint getListStyle() const;

  /// Change list style
  void setListStyle(FXuint style);

  /// Set the status line help text for this list
  void setHelpText(const FXString& text);

  /// Get the status line help text for this list
  const FXString& getHelpText() const { return help; }

  /// Save object to a stream
  virtual void save(FXStream& store) const;

  /// Load object from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXTreeList();
  };

}

#endif
