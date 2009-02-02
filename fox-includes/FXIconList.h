/********************************************************************************
*                                                                               *
*                         I c o n   L i s t   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXIconList.h 2336 2006-02-04 15:20:33Z lyle $                        *
********************************************************************************/
#ifndef FXICONLIST_H
#define FXICONLIST_H

#ifndef FXSCROLLAREA_H
#include "FXScrollArea.h"
#endif

namespace FX {


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
class FXFileList;


/// Icon item
class FXAPI FXIconItem : public FXObject {
  FXDECLARE(FXIconItem)
  friend class FXIconList;
  friend class FXFileList;
protected:
  FXString  label;
  FXIcon   *bigIcon;
  FXIcon   *miniIcon;
  void     *data;
  FXuint    state;
private:
  FXIconItem(const FXIconItem&);
  FXIconItem& operator=(const FXIconItem&);
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

  /// Construct new item with given text, icons, and user-data
  FXIconItem(const FXString& text,FXIcon* bi=NULL,FXIcon* mi=NULL,void* ptr=NULL):label(text),bigIcon(bi),miniIcon(mi),data(ptr),state(0){}

  /// Change item's text label
  virtual void setText(const FXString& txt);

  /// Return item's text label
  const FXString& getText() const { return label; }

  /// Change item's big icon, deleting the old icon if it was owned
  virtual void setBigIcon(FXIcon* icn,FXbool owned=FALSE);

  /// Return item's big icon
  FXIcon* getBigIcon() const { return bigIcon; }

  /// Change item's mini icon, deleting the old icon if it was owned
  virtual void setMiniIcon(FXIcon* icn,FXbool owned=FALSE);

  /// Return item's mini icon
  FXIcon* getMiniIcon() const { return miniIcon; }

  /// Change item's user data
  void setData(void* ptr){ data=ptr; }

  /// Get item's user data
  void* getData() const { return data; }

  /// Make item draw as focused
  virtual void setFocus(FXbool focus);

  /// Return true if item has focus
  FXbool hasFocus() const { return (state&FOCUS)!=0; }

  /// Select item
  virtual void setSelected(FXbool selected);

  /// Return true if this item is selected
  FXbool isSelected() const { return (state&SELECTED)!=0; }

  /// Enable or disable item
  virtual void setEnabled(FXbool enabled);

  /// Return true if this item is enabled
  FXbool isEnabled() const { return (state&DISABLED)==0; }

  /// Make item draggable
  virtual void setDraggable(FXbool draggable);

  /// Return true if this item is draggable
  FXbool isDraggable() const { return (state&DRAGGABLE)!=0; }

  /// Return width of item as drawn in list
  virtual FXint getWidth(const FXIconList* list) const;

  /// Return height of item as drawn in list
  virtual FXint getHeight(const FXIconList* list) const;

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
  virtual ~FXIconItem();
  };


/// Icon item collate function
typedef FXint (*FXIconListSortFunc)(const FXIconItem*,const FXIconItem*);


typedef FXObjectListOf<FXIconItem> FXIconItemList;


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
class FXAPI FXIconList : public FXScrollArea {
  FXDECLARE(FXIconList)
protected:
  FXHeader          *header;            // Header control
  FXIconItemList     items;		// Item list
  FXint              nrows;             // Number of rows
  FXint              ncols;             // Number of columns
  FXint              anchor;            // Anchor item
  FXint              current;           // Current item
  FXint              extent;            // Extent item
  FXint              cursor;            // Cursor item
  FXint              viewable;          // Visible item
  FXFont            *font;              // Font
  FXIconListSortFunc sortfunc;          // Item sort function
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
private:
  FXIconList(const FXIconList&);
  FXIconList &operator=(const FXIconList&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onRightBtnPress(FXObject*,FXSelector,void*);
  long onRightBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onTipTimer(FXObject*,FXSelector,void*);
  long onCmdSelectAll(FXObject*,FXSelector,void*);
  long onCmdDeselectAll(FXObject*,FXSelector,void*);
  long onCmdSelectInverse(FXObject*,FXSelector,void*);
  long onCmdArrangeByRows(FXObject*,FXSelector,void*);
  long onUpdArrangeByRows(FXObject*,FXSelector,void*);
  long onCmdArrangeByColumns(FXObject*,FXSelector,void*);
  long onUpdArrangeByColumns(FXObject*,FXSelector,void*);
  long onCmdShowDetails(FXObject*,FXSelector,void*);
  long onUpdShowDetails(FXObject*,FXSelector,void*);
  long onCmdShowBigIcons(FXObject*,FXSelector,void*);
  long onUpdShowBigIcons(FXObject*,FXSelector,void*);
  long onCmdShowMiniIcons(FXObject*,FXSelector,void*);
  long onUpdShowMiniIcons(FXObject*,FXSelector,void*);
  long onHeaderChanged(FXObject*,FXSelector,void*);
  long onHeaderResize(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onClicked(FXObject*,FXSelector,void*);
  long onDoubleClicked(FXObject*,FXSelector,void*);
  long onTripleClicked(FXObject*,FXSelector,void*);
  long onCommand(FXObject*,FXSelector,void*);
  long onAutoScroll(FXObject*,FXSelector,void*);
  long onLookupTimer(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
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

  /// Construct icon list with no items in it initially
  FXIconList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=ICONLIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Recalculate layout
  virtual void recalc();

  /// Perform layout
  virtual void layout();

 /// Compute and return content width
  virtual FXint getContentWidth();

  /// Return content height
  virtual FXint getContentHeight();

  /// Icon list can receive focus
  virtual bool canFocus() const;

  /// Move the focus to this window
  virtual void setFocus();

  /// Remove the focus from this window
  virtual void killFocus();

  /// Return viewport size
  virtual FXint getViewportHeight();

  /// Resize this window to the specified width and height
  virtual void resize(FXint w,FXint h);

  /// Move and resize this window in the parent's coordinates
  virtual void position(FXint x,FXint y,FXint w,FXint h);

  /// Return number of items
  FXint getNumItems() const { return items.no(); }

  /// Return number of rows
  FXint getNumRows() const { return nrows; }

  /// Return number of columns
  FXint getNumCols() const { return ncols; }

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

  /// Return the item at the given index
  FXIconItem *getItem(FXint index) const;

  /// Replace the item with a [possibly subclassed] item
  FXint setItem(FXint index,FXIconItem* item,FXbool notify=FALSE);

  /// Replace items text, icons, and user-data pointer
  FXint setItem(FXint index,const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Fill list by appending items from array of strings
  FXint fillItems(const FXchar** strings,FXIcon *big=NULL,FXIcon* mini=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Fill list by appending items from newline separated strings
  FXint fillItems(const FXString& strings,FXIcon *big=NULL,FXIcon* mini=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Insert a new [possibly subclassed] item at the give index
  FXint insertItem(FXint index,FXIconItem* item,FXbool notify=FALSE);

  /// Insert item at index with given text, icons, and user-data pointer
  FXint insertItem(FXint index,const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Append a [possibly subclassed] item to the end of the list
  FXint appendItem(FXIconItem* item,FXbool notify=FALSE);

  /// Append new item with given text and optional icons, and user-data pointer
  FXint appendItem(const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Prepend a [possibly subclassed] item to the end of the list
  FXint prependItem(FXIconItem* item,FXbool notify=FALSE);

  /// Prepend new item with given text and optional icons, and user-data pointer
  FXint prependItem(const FXString& text,FXIcon *big=NULL,FXIcon* mini=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Move item from oldindex to newindex
  FXint moveItem(FXint newindex,FXint oldindex,FXbool notify=FALSE);

  /// Extract item from list
  FXIconItem* extractItem(FXint index,FXbool notify=FALSE);

  /// Remove item from list
  void removeItem(FXint index,FXbool notify=FALSE);

  /// Remove all items from list
  void clearItems(FXbool notify=FALSE);

  /// Return item width
  FXint getItemWidth() const { return itemWidth; }

  /// Return item height
  FXint getItemHeight() const { return itemHeight; }

  /// Return index of item at x,y, or -1 if none
  virtual FXint getItemAt(FXint x,FXint y) const;

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

  /// Scroll to make item at index visible
  virtual void makeItemVisible(FXint index);

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

  /// Change item user-data pointer
  void setItemData(FXint index,void* ptr);

  /// Return item user-data pointer
  void* getItemData(FXint index) const;

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

  /// Enable item at index
  virtual FXbool enableItem(FXint index);

  /// Disable item at index
  virtual FXbool disableItem(FXint index);

  /// Select item at index
  virtual FXbool selectItem(FXint index,FXbool notify=FALSE);

  /// Deselect item at index
  virtual FXbool deselectItem(FXint index,FXbool notify=FALSE);

  /// Toggle item at index
  virtual FXbool toggleItem(FXint index,FXbool notify=FALSE);

  /// Select items in rectangle
  virtual FXbool selectInRectangle(FXint x,FXint y,FXint w,FXint h,FXbool notify=FALSE);

  /// Extend selection from anchor index to index
  virtual FXbool extendSelection(FXint index,FXbool notify=FALSE);

  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=FALSE);

  /// Change current item index
  virtual void setCurrentItem(FXint index,FXbool notify=FALSE);

  /// Return current item index, or -1 if none
  FXint getCurrentItem() const { return current; }

  /// Change anchor item index
  void setAnchorItem(FXint index);

  /// Return anchor item index, or -1 if none
  FXint getAnchorItem() const { return anchor; }

  /// Return index of item under cursor, or -1 if none
  FXint getCursorItem() const { return cursor; }

  /// Sort items
  void sortItems();

  /// Return sort function
  FXIconListSortFunc getSortFunc() const { return sortfunc; }

  /// Change sort function
  void setSortFunc(FXIconListSortFunc func){ sortfunc=func; }

  /// Change text font
  void setFont(FXFont* fnt);

  /// Return text font
  FXFont* getFont() const { return font; }

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

  /// Change maximum item space for each item
  void setItemSpace(FXint s);

  /// Return maximum item space
  FXint getItemSpace() const { return itemSpace; }

  /// Get the current icon list style
  FXuint getListStyle() const;

  /// Set the current icon list style.
  void setListStyle(FXuint style);

  /// Set the status line help text for this widget
  void setHelpText(const FXString& text);

  /// Get the status line help text for this widget
  const FXString& getHelpText() const { return help; }

  /// Save list to a stream
  virtual void save(FXStream& store) const;

  /// Load list from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXIconList();
  };

}

#endif
