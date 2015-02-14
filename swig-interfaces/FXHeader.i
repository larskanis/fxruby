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
class FXHeaderItem : public FXObject {
public:
  enum{
    ARROW_NONE = 0,     /// No arrow
    ARROW_UP   = 1,     /// Arrow pointing up
    ARROW_DOWN = 2,     /// Arrow pointing down
    PRESSED    = 4,     /// Pressed down
    RIGHT      = 8,     /// Align on right
    LEFT       = 16,    /// Align on left
    CENTER_X   = 0,               /// Aling centered horizontally (default)
    TOP        = 32,    /// Align on top
    BOTTOM     = 64,    /// Align on bottom
    CENTER_Y   = 0,               /// Aling centered vertically (default)
    BEFORE     = 128,   /// Icon before the text
    AFTER      = 256,   /// Icon after the text
    ABOVE      = 512,   /// Icon above the text
    BELOW      = 1024   /// Icon below the text
    };
public:
  %extend {
    /// Construct new item with given text, icon, size, and user-data
    FXHeaderItem(const FXString& text,FXIcon* ic=NULL,FXint s=0,void* ITEMDATA=NULL){
      return new FXRbHeaderItem(text,ic,s,ITEMDATA);
      }
  }

  /// Return item's text label
  const FXString& getText() const;

  /// Return item's icon
  FXIcon* getIcon() const;

  %extend {
    /// Change item's user data
    void setData(VALUE ptr) {
      self->setData((void*) ptr);
      }

    /// Get item's user data
    VALUE getData() const {
      return self->getData() ? (VALUE) self->getData() : Qnil;
      }
  }

  /// Change size
  void setSize(FXint s);

  /// Obtain current size
  FXint getSize() const;

  /// Change position
  void setPos(FXint p);

  /// Obtain current position
  FXint getPos() const;

  /// Change sort direction (FALSE, TRUE, MAYBE)
  void setArrowDir(FXuint dir=MAYBE);

  /// Return sort direction (FALSE, TRUE, MAYBE)
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

  /// Destructor
  virtual ~FXHeaderItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXHeaderItem)
DECLARE_FXHEADERITEM_VIRTUALS(FXHeaderItem)

%typemap(check) FXint HEADER_ITEM_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumItems()) {
    rb_raise(rb_eIndexError, "header item index out of bounds");
  }
}

%apply FXint HEADER_ITEM_INDEX { FXint index };

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
class FXHeader : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onTipTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  %extend {
    /// Construct new header control
    FXHeader(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=HEADER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbHeader(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Return number of items
  FXint getNumItems() const;

  /// Return total size of all items
  FXint getTotalSize() const;

  /// Set the current position
  void setPosition(FXint p);

  /// Return the current position
  FXint getPosition() const;

  /// Return item at given index
  FXHeaderItem *getItem(FXint index) const;

  /**
  * Return item-index given coordinate offset, or -1 if coordinate
  * is before first item in header, or nitems if coordinate is after
  * last item in header.
  */
  FXint getItemAt(FXint coord) const;

  %extend {
    /// Replace the item with a [possibly subclassed] item
    FXint setItem(FXint index,FXHeaderItem* item,FXbool notify=FALSE){
      // Save pointer to the soon-to-be-destroyed item
      FXHeaderItem* oldItem=self->getItem(index);

      // Do the deed
      if(item->isMemberOf(FXMETACLASS(FXRbHeaderItem)))
	dynamic_cast<FXRbHeaderItem*>(item)->owned=TRUE;
      FXint result=self->setItem(index,item,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(oldItem);

      // Done
      return result;
    }

    /// Replace items text, icon, and user-data pointer
    FXint setItem(FXint index,const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ITEMDATA=NULL,FXbool notify=FALSE){
      // Save pointer to the soon-to-be-destroyed item
      FXHeaderItem* oldItem=self->getItem(index);

      // Do the deed
      FXint result=self->setItem(index,text,icon,size,ITEMDATA,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(oldItem);

      // Done
      return result;
    }
  }

  /// Fill header by appending items from array of strings
  FXint fillItems(const FXchar** strings,FXIcon *icon=NULL,FXint size=0,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Insert a new [possibly subclassed] item at the given index
    FXint insertItem(FXint index,FXHeaderItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbHeaderItem)))
        dynamic_cast<FXRbHeaderItem*>(item)->owned=TRUE;
      return self->insertItem(index,item,notify);
    }
  }

  /// Insert item at index with given text, icon, and user-data pointer
  FXint insertItem(FXint index,const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Append a [possibly subclassed] item to the list
    FXint appendItem(FXHeaderItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbHeaderItem)))
        dynamic_cast<FXRbHeaderItem*>(item)->owned=TRUE;
      return self->appendItem(item,notify);
    }
  }

  /// Append new item with given text and optional icon, and user-data pointer
  FXint appendItem(const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ITEMDATA=NULL,FXbool notify=FALSE);

  %extend {
    /// Prepend a [possibly subclassed] item to the list
    FXint prependItem(FXHeaderItem* item,FXbool notify=FALSE){
      if(item->isMemberOf(FXMETACLASS(FXRbHeaderItem)))
        dynamic_cast<FXRbHeaderItem*>(item)->owned=TRUE;
      return self->prependItem(item,notify);
    }
  }

  /// Prepend new item with given text and optional icon, and user-data pointer
  FXint prependItem(const FXString& text,FXIcon *icon=NULL,FXint size=0,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Extract item from list
  FXHeaderItem* extractItem(FXint index,FXbool notify=FALSE);

  %extend {
    /// Remove item at index
    void removeItem(FXint index,FXbool notify=FALSE){
      // Save pointer to the soon-to-be-destroyed item
      FXHeaderItem* item=self->getItem(index);

      // Do the deed
      self->removeItem(index,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      FXRbUnregisterRubyObj(item);
      }

    /// Remove all items
    void clearItems(FXbool notify=FALSE){
      // Save pointers to the soon-to-be-destroyed items
      FXObjectListOf<FXHeaderItem> items;
      for (FXint i = 0; i < self->getNumItems(); i++) items.append(self->getItem(i));

      // Do the deed
      self->clearItems(notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for (FXint j = 0; j < items.no(); j++) FXRbUnregisterRubyObj(items[j]);
      }
  }

  /// Change text label for item at index
  void setItemText(FXint index,const FXString& text);

  /// Get text of item at index
  FXString getItemText(FXint index) const;

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

  %extend {
    /// Change data of item at index
    void setItemData(FXint index, VALUE ptr){
      self->setItemData(index, (void*) ptr);
      }

    /// Return data of item at index
    VALUE getItemData(FXint index) const {
      return self->getItemData(index) ? (VALUE) self->getItemData(index) : Qnil;
      }
  }

  /// Change sort direction (FALSE, TRUE, MAYBE)
  void setArrowDir(FXint index,FXbool dir=MAYBE);

  /// Return sort direction (FALSE, TRUE, MAYBE)
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
  void setItemPressed(FXint index,FXbool pressed=TRUE);

  /// Return TRUE if button item is pressed in
  FXbool isItemPressed(FXint index) const;

  /// Scroll to make given item visible
  void makeItemVisible(FXint index);

  /// Repaint header at index
  void updateItem(FXint index) const;

  /// Change text font
  void setFont(FXFont* fnt);

  /// return text font
  FXFont* getFont() const;

  /// Return text color
  FXColor getTextColor() const;

  /// Change text color
  void setTextColor(FXColor clr);

  /// Set header style options
  void setHeaderStyle(FXuint style);

  /// Get header style options
  FXuint getHeaderStyle() const;

  /// Set the status line help text for this header
  void setHelpText(const FXString& text);

  /// Get the status line help text for this header
  const FXString& getHelpText() const;

  /// Destructor
  virtual ~FXHeader();
  };

%clear FXint index;

DECLARE_FXOBJECT_VIRTUALS(FXHeader)
DECLARE_FXID_VIRTUALS(FXHeader)
DECLARE_FXDRAWABLE_VIRTUALS(FXHeader)
DECLARE_FXWINDOW_VIRTUALS(FXHeader)

