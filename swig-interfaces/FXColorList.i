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

%rename("color=") FXColorItem::setColor(FXColor);
%rename("color")  FXColorItem::getColor() const;

/// Color item
class FXColorItem : public FXListItem {
public:
  %extend {
    /// Construct new item with given text, color, and user-data
    FXColorItem(const FXString& text,FXColor clr,void* ITEMDATA=NULL){
      return new FXRbColorItem(text,clr,ITEMDATA);
      }
  }

  /// Change item's color
  void setColor(FXColor clr);

  /// Return item's color
  FXColor getColor() const;

  // Destructor
  virtual ~FXColorItem();
  };

DECLARE_FXOBJECT_VIRTUALS(FXColorItem)
DECLARE_FXLISTITEM_VIRTUALS(FXColorItem)

/**
* A ColorList Widget displays a list of colors.
*/
class FXColorList : public FXList {
public:
  %extend {
    /// Construct a list with initially no items in it
    FXColorList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=LIST_BROWSESELECT,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbColorList(p,tgt,sel,opts,x,y,w,h);
      }
  }

  /// Fill list by appending color items from array of strings and array of colors
  FXint fillItems(const FXchar** strings,FXColor *colors=NULL,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Insert item at index with given text, color, and user-data pointer
  FXint insertItem(FXint index,const FXString& text,FXColor color=0,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Append new item with given text, color, and user-data pointer
  FXint appendItem(const FXString& text,FXColor color=0,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Prepend new item with given text, color, and user-data pointer
  FXint prependItem(const FXString& text,FXColor color=0,void* ITEMDATA=NULL,FXbool notify=FALSE);

  /// Change item color
  void setItemColor(FXint index,FXColor color);

  /// Return item color
  FXColor getItemColor(FXint index) const;

  // Destructor
  virtual ~FXColorList();
  };

DECLARE_FXOBJECT_VIRTUALS(FXColorList)
DECLARE_FXID_VIRTUALS(FXColorList)
DECLARE_FXDRAWABLE_VIRTUALS(FXColorList)
DECLARE_FXWINDOW_VIRTUALS(FXColorList)
DECLARE_FXSCROLLAREA_VIRTUALS(FXColorList)
DECLARE_FXLIST_VIRTUALS(FXColorList)


