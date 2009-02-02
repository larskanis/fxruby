/********************************************************************************
*                                                                               *
*                         C o l o r   L i s t   W i d g e t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXColorList.h 2292 2005-12-06 02:22:28Z lyle $                        *
********************************************************************************/
#ifndef FXCOLORLIST_H
#define FXCOLORLIST_H

#ifndef FXLIST_H
#include "FXList.h"
#endif

namespace FX {


/// Color item
class FXColorItem : public FXListItem {
  FXDECLARE(FXColorItem)
protected:
  FXColor  color;
private:
  FXColorItem(const FXColorItem&);
  FXColorItem& operator=(const FXColorItem&);
protected:
  FXColorItem():color(0){}
  virtual void draw(const FXList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h);
  virtual FXint hitItem(const FXList* list,FXint x,FXint y) const;
public:
  /// Construct new item with given text, color, and user-data
  FXColorItem(const FXString& text,FXColor clr,void* ptr=NULL):FXListItem(text,NULL,ptr),color(clr){}

  /// Change item's color
  void setColor(FXColor clr){ color=clr; }

  /// Return item's color
  FXColor getColor() const { return color; }

  /// Return width of item as drawn in list
  virtual FXint getWidth(const FXList* list) const;

  /// Return height of item as drawn in list
  virtual FXint getHeight(const FXList* list) const;
  };


/**
* A ColorList Widget displays a list of colors.
*/
class FXAPI FXColorList : public FXList {
  FXDECLARE(FXColorList)
protected:
  FXColorList(){}
  virtual FXListItem *createItem(const FXString& text,FXIcon* icon,void* ptr);
private:
  FXColorList(const FXColorList&);
  FXColorList &operator=(const FXColorList&);
public:

  /// Construct a list with initially no items in it
  FXColorList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=LIST_BROWSESELECT,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Fill list by appending color items from array of strings and array of colors
  FXint fillItems(const FXchar** strings,FXColor *colors=NULL,void* ptr=NULL,FXbool notify=FALSE);

  /// Insert item at index with given text, color, and user-data pointer
  FXint insertItem(FXint index,const FXString& text,FXColor color=0,void* ptr=NULL,FXbool notify=FALSE);

  /// Append new item with given text, color, and user-data pointer
  FXint appendItem(const FXString& text,FXColor color=0,void* ptr=NULL,FXbool notify=FALSE);

  /// Prepend new item with given text, color, and user-data pointer
  FXint prependItem(const FXString& text,FXColor color=0,void* ptr=NULL,FXbool notify=FALSE);

  /// Change item color
  void setItemColor(FXint index,FXColor color);

  /// Return item color
  FXColor getItemColor(FXint index) const;
  };

}

#endif
