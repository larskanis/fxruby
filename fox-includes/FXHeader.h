/********************************************************************************
*                                                                               *
*                          H e a d e r   W i d g e t                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXHeader.h 2749 2007-11-16 22:44:49Z lyle $                          *
********************************************************************************/
#ifndef FXHEADER_H
#define FXHEADER_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {

class FXIcon;
class FXFont;
class FXHeader;


/// Header style options
enum {
  HEADER_BUTTON     = 0x00008000,     /// Button style can be clicked
  HEADER_HORIZONTAL = 0,              /// Horizontal header control (default)
  HEADER_VERTICAL   = 0x00010000,     /// Vertical header control
  HEADER_TRACKING   = 0x00020000,     /// Tracks continuously while moving
  HEADER_RESIZE     = 0x00040000,     /// Allow resizing sections
  HEADER_NORMAL     = HEADER_HORIZONTAL|FRAME_NORMAL
  };


/// Header item
class FXAPI FXHeaderItem : public FXObject {
  FXDECLARE(FXHeaderItem)
  friend class FXHeader;
protected:
  FXString  label;      // Text of item
  FXString  tip;        // Tooltip of item
  FXIcon   *icon;       // Icon of item
  void     *data;       // User data pointer
  FXint     size;       // Item size
  FXint     pos;        // Item position
  FXuint    state;      // State flags
private:
  FXHeaderItem(const FXHeaderItem&);
  FXHeaderItem& operator=(const FXHeaderItem&);
protected:
  FXHeaderItem(){}
  virtual void draw(const FXHeader* header,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
public:
  enum{
    ARROW_NONE = 0,     /// No arrow
    ARROW_UP   = 1,     /// Arrow pointing up
    ARROW_DOWN = 2,     /// Arrow pointing down
    PRESSED    = 4,     /// Pressed down
    RIGHT      = 8,     /// Align on right
    LEFT       = 16,    /// Align on left
    CENTER_X   = 0,     /// Aling centered horizontally (default)
    TOP        = 32,    /// Align on top
    BOTTOM     = 64,    /// Align on bottom
    CENTER_Y   = 0,     /// Aling centered vertically (default)
    BEFORE     = 128,   /// Icon before the text
    AFTER      = 256,   /// Icon after the text
    ABOVE      = 512,   /// Icon above the text
    BELOW      = 1024   /// Icon below the text
    };
public:

  /// Construct new item with given text, icon, size, and user-data
  FXHeaderItem(const FXString& text,FXIcon* ic=NULL,FXint s=0,void* ptr=NULL);

  /// Change item's text label
  virtual void setText(const FXString& txt);

  /// Return item's text label
  const FXString& getText() const { return label; }

  /// Set the tool tip message for this item
  void setTipText(const FXString& text){ tip=text; }

  /// Get the tool tip message for this item
  const FXString& getTipText() const { return tip; }

  /// Change item's icon
  virtual void setIcon(FXIcon* icn);

  /// Return item's icon
  FXIcon* getIcon() const { return icon; }

  /// Change item's user data
  void setData(void* ptr){ data=ptr; }

  /// Get item's user data
  void* getData() const { return data; }

  /// Change size
  void setSize(FXint s){ size=s; }

  /// Obtain current size
  FXint getSize() const { return size; }

  /// Change position
  void setPos(FXint p){ pos=p; }

  /// Obtain current position
  FXint getPos() const { return pos; }

  /// Change sort direction (ARROW_NONE, ARROW_UP, ARROW_DOWN)
  void setArrowDir(FXuint dir=ARROW_NONE);

  /// Return sort direction (ARROW_NONE, ARROW_UP, ARROW_DOWN)
  FXuint getArrowDir() const;

  /// Change content justification
  void setJustify(FXuint justify=LEFT|CENTER_Y);

  /// Return content justification
  FXuint getJustify() const;

  /// Change icon position
  void setIconPosition(FXuint mode=BEFORE);

  /// Return icon position
  FXuint getIconPosition() const;

  /// Change state to pressed
  void setPressed(FXbool pressed);

  /// Return pressed state
  FXbool isPressed() const;

  /// Return the item's content width in the header
  virtual FXint getWidth(const FXHeader* header) const;

  /// Return the item's content height in the header
  virtual FXint getHeight(const FXHeader* header) const;

  /// Create server-side resources
  virtual void create();

  /// Detach from server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Stream serialization
  virtual void save(FXStream& store) const;
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXHeaderItem(){}
  };


/// List of FXHeaderItem's
typedef FXObjectListOf<FXHeaderItem> FXHeaderItemList;


/**
* Header control may be placed over a table or list to provide a resizable
* captions above a number of columns.
* Each caption comprises a label and an optional icon; in addition, an arrow
* may be shown to indicate whether the items in that column are sorted, and
* if so, whether they are sorted in increasing or decreasing order.
* Each caption can be interactively resized.  During the resizing, if the
* HEADER_TRACKING was specified, the header control sends a SEL_CHANGED message
* to its target, with the message data set to the caption number being resized,
* of the type FXint.
* If the HEADER_TRACKING was not specified the SEL_CHANGED message is sent at
* the end of the resizing operation.
* Clicking on a caption causes a message of type SEL_COMMAND to be sent to the
* target, with the message data set to the caption number being clicked.
* A single click on a split causes a message of type SEL_CLICKED to be sent to the
* target; a typical response to this message would be to adjust the size of
* the split to fit the contents displayed underneath it.
* The contents may be scrolled by calling setPosition().
*/
class FXAPI FXHeader : public FXFrame {
  FXDECLARE(FXHeader)
protected:
  FXHeaderItemList items;	// Item list
  FXColor          textColor;	// Text color
  FXFont          *font;	// Text font
  FXString         help;	// Help text
  FXint            pos;		// Scroll position
  FXint            active;	// Active button
  FXint            activepos;	// Position of active item
  FXint            activesize;	// Size of active item
  FXint            offset;	// Offset where split grabbed
protected:
  FXHeader();
  void drawSplit(FXint pos);
  virtual FXHeaderItem *createItem(const FXString& text,FXIcon* icon,FXint size,void* ptr);
private:
  FXHeader(const FXHeader&);
  FXHeader &operator=(const FXHeader&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onTipTimer(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
public:

  /// Construct new header control
  FXHeader(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=HEADER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Perform layout
  virtual void layout();

  /// Return number of items
  FXint getNumItems() const { return items.no(); }

  /// Return total size of all items
  FXint getTotalSize() const;

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Set the current position
  void setPosition(FXint pos);

  /// Return the current position
  FXint getPosition() const { return pos; }

  /**
  * Return item-index given coordinate offset, or -1 if coordinate
  * is before first item in header, or nitems if coordinate is after
  * last item in header.
  */
  FXint getItemAt(FXint coord) const;

  /// Return item at given index
  FXHeaderItem *getItem(FXint index) const;

  /// Replace the item with a [possibly subclassed] item
  FXint setItem(FXint index,FXHeaderItem* item,FXbool notify=false);

  /// Replace items text, icon, and user-data pointer
  FXint setItem(FXint index,const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ptr=NULL,FXbool notify=false);

  /// Fill header by appending items from array of strings
  FXint fillItems(const FXchar** strings,FXIcon *icon=NULL,FXint size=0,void* ptr=NULL,FXbool notify=false);

  /// Fill header by appending items from newline separated strings
  FXint fillItems(const FXString& strings,FXIcon *icon=NULL,FXint size=0,void* ptr=NULL,FXbool notify=false);

  /// Insert a new [possibly subclassed] item at the give index
  FXint insertItem(FXint index,FXHeaderItem* item,FXbool notify=false);

  /// Insert item at index with given text, icon, and user-data pointer
  FXint insertItem(FXint index,const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ptr=NULL,FXbool notify=false);

  /// Append a [possibly subclassed] item to the list
  FXint appendItem(FXHeaderItem* item,FXbool notify=false);

  /// Append new item with given text and optional icon, and user-data pointer
  FXint appendItem(const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ptr=NULL,FXbool notify=false);

  /// Prepend a [possibly subclassed] item to the list
  FXint prependItem(FXHeaderItem* item,FXbool notify=false);

  /// Prepend new item with given text and optional icon, and user-data pointer
  FXint prependItem(const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ptr=NULL,FXbool notify=false);

  /// Extract item from list
  FXHeaderItem* extractItem(FXint index,FXbool notify=false);

  /// Remove item at index
  void removeItem(FXint index,FXbool notify=false);

  /// Remove all items
  void clearItems(FXbool notify=false);

  /// Change text label for item at index
  void setItemText(FXint index,const FXString& text);

  /// Get text of item at index
  FXString getItemText(FXint index) const;

  /// Change tool tip message for item at index
  void setItemTipText(FXint index,const FXString& text);

  /// Get tool tip message of item at index
  FXString getItemTipText(FXint index) const;

  /// Change icon of item at index
  void setItemIcon(FXint index,FXIcon* icon);

  /// Return icon of item at index
  FXIcon* getItemIcon(FXint index) const;

  /// Change size of item at index
  void setItemSize(FXint index,FXint size);

  /// Return size of item at index
  FXint getItemSize(FXint index) const;

  /// Compute offset from the left side of item at index
  FXint getItemOffset(FXint index) const;

  /// Change data of item at index
  void setItemData(FXint index,void* ptr);

  /// Return data of item at index
  void* getItemData(FXint index) const;

  /// Change sort direction (ARROW_NONE, ARROW_UP, ARROW_DOWN)
  void setArrowDir(FXint index,FXuint dir=FXHeaderItem::ARROW_NONE);

  /// Return sort direction (ARROW_NONE, ARROW_UP, ARROW_DOWN)
  FXuint getArrowDir(FXint index) const;

  /**
  * Change item justification.  Horizontal justification is controlled by passing
  * FXHeaderItem::RIGHT, FXHeaderItem::LEFT, or FXHeaderItem::CENTER_X.
  * Vertical justification is controlled by FXHeaderItem::TOP, FXHeaderItem::BOTTOM,
  * or FXHeaderItem::CENTER_Y.
  * The default is a combination of FXHeaderItem::LEFT and FXHeaderItem::CENTER_Y.
  */
  void setItemJustify(FXint index,FXuint justify);

  /// Return item justification
  FXuint getItemJustify(FXint index) const;

  /**
  * Change relative position of icon and text of item.
  * Passing FXHeaderItem::BEFORE or FXHeaderItem::AFTER places the icon
  * before or after the text, and passing FXHeaderItem::ABOVE or
  * FXHeaderItem::BELOW places it above or below the text, respectively.
  * The default of FXHeaderItem::BEFORE places the icon in front of the text.
  */
  void setItemIconPosition(FXint index,FXuint mode);

  /// Return relative icon and text position
  FXuint getItemIconPosition(FXint index) const;

  /// Changed button item's pressed state
  void setItemPressed(FXint index,FXbool pressed=true);

  /// Return true if button item is pressed in
  FXbool isItemPressed(FXint index) const;

  /// Scroll to make given item visible
  void makeItemVisible(FXint index);

  /// Repaint header at index
  void updateItem(FXint index) const;

  /// Change text font
  void setFont(FXFont* fnt);

  /// return text font
  FXFont* getFont() const { return font; }

  /// Return text color
  FXColor getTextColor() const { return textColor; }

  /// Change text color
  void setTextColor(FXColor clr);

  /// Set header style options
  void setHeaderStyle(FXuint style);

  /// Get header style options
  FXuint getHeaderStyle() const;

  /// Set the status line help text for this header
  void setHelpText(const FXString& text);

  /// Get the status line help text for this header
  const FXString& getHelpText() const { return help; }

  /// Save header to a stream
  virtual void save(FXStream& store) const;

  /// Load header from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXHeader();
  };

}

#endif
