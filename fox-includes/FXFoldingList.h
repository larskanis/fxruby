/********************************************************************************
*                                                                               *
*                    F o l d i n g   L i s t   W i d g e t                      *
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
* $Id: FXFoldingList.h 2336 2006-02-04 15:20:33Z lyle $                     *
********************************************************************************/
#ifndef FXFOLDINGLIST_H
#define FXFOLDINGLIST_H

#ifndef FXSCROLLAREA_H
#include "FXScrollArea.h"
#endif

namespace FX {


class FXIcon;
class FXFont;
class FXHeader;
class FXFoldingList;


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


/// Tree list Item
class FXAPI FXFoldingItem : public FXObject {
  FXDECLARE(FXFoldingItem)
  friend class FXFoldingList;
  friend class FXDirList;
protected:
  FXFoldingItem *parent;
  FXFoldingItem *prev;
  FXFoldingItem *next;
  FXFoldingItem *first;
  FXFoldingItem *last;
  FXString       label;
  FXIcon        *openIcon;
  FXIcon        *closedIcon;
  void          *data;
  FXuint         state;
  FXint          x,y;
private:
  FXFoldingItem(const FXFoldingItem&);
  FXFoldingItem& operator=(const FXFoldingItem&);
protected:
  FXFoldingItem():parent(NULL),prev(NULL),next(NULL),first(NULL),last(NULL),openIcon(NULL),closedIcon(NULL),data(NULL),state(0),x(0),y(0){}
  virtual void draw(const FXFoldingList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual FXint hitItem(const FXFoldingList* list,FXint x,FXint y) const;
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
  FXFoldingItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL):parent(NULL),prev(NULL),next(NULL),first(NULL),last(NULL),label(text),openIcon(oi),closedIcon(ci),data(ptr),state(0),x(0),y(0){}

  /// Get parent item
  FXFoldingItem* getParent() const { return parent; }

  /// Get next sibling item
  FXFoldingItem* getNext() const { return next; }

  /// Get previous sibling item
  FXFoldingItem* getPrev() const { return prev; }

  /// Get first child item
  FXFoldingItem* getFirst() const { return first; }

  /// Get las child item
  FXFoldingItem* getLast() const { return last; }

  /// Get item below this one in list
  FXFoldingItem* getBelow() const;

  /// Get item above this one in list
  FXFoldingItem* getAbove() const;

  /// Get number of children of item
  FXint getNumChildren() const;

  /// Change item label
  virtual void setText(const FXString& txt);

  /// Get item label
  const FXString& getText() const { return label; }

  /// Change open icon, deleting old icon if it was owned
  virtual void setOpenIcon(FXIcon* icn,FXbool owned=FALSE);

  /// Get open icon
  FXIcon* getOpenIcon() const { return openIcon; }

  /// Change closed icon, deleting old icon if it was owned
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
  FXbool isChildOf(const FXFoldingItem* item) const;

  /// Return true if ancestor of child item
  FXbool isParentOf(const FXFoldingItem* item) const;

  /// Return width of item as drawn in list
  virtual FXint getWidth(const FXFoldingList* list) const;

  /// Return height of item as drawn in list
  virtual FXint getHeight(const FXFoldingList* list) const;

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
  virtual ~FXFoldingItem();
  };



/// Folding item collate function
typedef FXint (*FXFoldingListSortFunc)(const FXFoldingItem*,const FXFoldingItem*);



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
class FXAPI FXFoldingList : public FXScrollArea {
  FXDECLARE(FXFoldingList)
protected:
  FXHeader          *header;            // Tree header
  FXFoldingItem     *firstitem;         // First root item
  FXFoldingItem     *lastitem;          // Last root item
  FXFoldingItem     *anchoritem;        // Selection anchor item
  FXFoldingItem     *currentitem;       // Current item
  FXFoldingItem     *extentitem;        // Selection extent
  FXFoldingItem     *cursoritem;        // Item under cursor
  FXFoldingItem     *viewableitem;      // Viewable item
  FXFont            *font;              // Font
  FXFoldingListSortFunc sortfunc;       // Item sort function
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
  FXString           help;              // Help string
  FXbool             state;             // State of item
protected:
  FXFoldingList();
  void recompute();
  void mergesort(FXFoldingItem*& list);
  void sort(FXFoldingItem*& f1,FXFoldingItem*& t1,FXFoldingItem*& f2,FXFoldingItem*& t2,int n);
  virtual void moveContents(FXint x,FXint y);
  virtual FXFoldingItem* createItem(const FXString& text,FXIcon* oi,FXIcon* ci,void* ptr);
  static FXint compareSection(const FXchar *p,const FXchar* q,FXint s);
  static FXint compareSectionCase(const FXchar *p,const FXchar* q,FXint s);
private:
  FXFoldingList(const FXFoldingList&);
  FXFoldingList& operator=(const FXFoldingList&);
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

  /// Construct a folding list; the folding list is initially empty
  FXFoldingList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FOLDINGLIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

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

  /// Return header control
  FXHeader* getHeader() const { return header; }

  /// Set headers from array of strings
  void setHeaders(const FXchar** strings,FXint size=1);

  /// Set headers from newline separated strings
  void setHeaders(const FXString& strings,FXint size=1);

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
  FXint getNumVisible() const { return visible; }

  /// Change number of visible items
  void setNumVisible(FXint nvis);

  /// Return first root item
  FXFoldingItem* getFirstItem() const { return firstitem; }

  /// Return last root item
  FXFoldingItem* getLastItem() const { return lastitem; }

  /// Fill list by appending items from array of strings
  FXint fillItems(FXFoldingItem* father,const FXchar** strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Fill list by appending items from newline separated strings
  FXint fillItems(FXFoldingItem* father,const FXString& strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Insert [possibly subclassed] item under father before other item
  FXFoldingItem* insertItem(FXFoldingItem* other,FXFoldingItem* father,FXFoldingItem* item,FXbool notify=FALSE);

  /// Insert item with given text and optional icons, and user-data pointer under father before other item
  FXFoldingItem* insertItem(FXFoldingItem* other,FXFoldingItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Append [possibly subclassed] item as last child of father
  FXFoldingItem* appendItem(FXFoldingItem* father,FXFoldingItem* item,FXbool notify=FALSE);

  /// Append item with given text and optional icons, and user-data pointer as last child of father
  FXFoldingItem* appendItem(FXFoldingItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Prepend [possibly subclassed] item as first child of father
  FXFoldingItem* prependItem(FXFoldingItem* father,FXFoldingItem* item,FXbool notify=FALSE);

  /// Prepend item with given text and optional icons, and user-data pointer as first child of father
  FXFoldingItem* prependItem(FXFoldingItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Move item under father before other item
  FXFoldingItem *moveItem(FXFoldingItem* other,FXFoldingItem* father,FXFoldingItem* item);

  /// Extract item
  FXFoldingItem* extractItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Remove item
  void removeItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Remove items in range [fm, to] inclusively
  void removeItems(FXFoldingItem* fm,FXFoldingItem* to,FXbool notify=FALSE);

  /// Remove all items from list
  void clearItems(FXbool notify=FALSE);

  /// Return item width
  FXint getItemWidth(const FXFoldingItem* item) const { return item->getWidth(this); }

  /// Return item height
  FXint getItemHeight(const FXFoldingItem* item) const { return item->getHeight(this); }

  /// Get item at x,y, if any
  virtual FXFoldingItem* getItemAt(FXint x,FXint y) const;

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
  FXFoldingItem* findItemByData(const void *ptr,FXFoldingItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Scroll to make item visible
  virtual void makeItemVisible(FXFoldingItem* item);

  /// Change item's text
  void setItemText(FXFoldingItem* item,const FXString& text);

  /// Return item's text
  FXString getItemText(const FXFoldingItem* item) const;

  /// Change item's open icon, deleting old icon if it was owned
  void setItemOpenIcon(FXFoldingItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's open icon
  FXIcon* getItemOpenIcon(const FXFoldingItem* item) const;

  /// Chance item's closed icon, deleting old icon if it was owned
  void setItemClosedIcon(FXFoldingItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's closed icon
  FXIcon* getItemClosedIcon(const FXFoldingItem* item) const;

  /// Change item user-data pointer
  void setItemData(FXFoldingItem* item,void* ptr) const;

  /// Return item user-data pointer
  void* getItemData(const FXFoldingItem* item) const;

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

  /// Enable item
  virtual FXbool enableItem(FXFoldingItem* item);

  /// Disable item
  virtual FXbool disableItem(FXFoldingItem* item);

  /// Select item
  virtual FXbool selectItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Deselect item
  virtual FXbool deselectItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Toggle item selection
  virtual FXbool toggleItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Extend selection from anchor item to item
  virtual FXbool extendSelection(FXFoldingItem* item,FXbool notify=FALSE);

  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=FALSE);

  /// Open item
  virtual FXbool openItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Close item
  virtual FXbool closeItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Collapse tree
  virtual FXbool collapseTree(FXFoldingItem* tree,FXbool notify=FALSE);

  /// Expand tree
  virtual FXbool expandTree(FXFoldingItem* tree,FXbool notify=FALSE);

  /// Change current item
  virtual void setCurrentItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Return current item, if any
  FXFoldingItem* getCurrentItem() const { return currentitem; }

  /// Change anchor item
  void setAnchorItem(FXFoldingItem* item);

  /// Return anchor item, if any
  FXFoldingItem* getAnchorItem() const { return anchoritem; }

  /// Return item under cursor, if any
  FXFoldingItem* getCursorItem() const { return cursoritem; }

  /// Sort all items recursively
  void sortItems();

  /// Sort root items
  void sortRootItems();

  /// Sort children of item
  void sortChildItems(FXFoldingItem* item);

  /// Return sort function
  FXFoldingListSortFunc getSortFunc() const { return sortfunc; }

  /// Change sort function
  void setSortFunc(FXFoldingListSortFunc func){ sortfunc=func; }

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
  virtual ~FXFoldingList();
  };

}


#endif
