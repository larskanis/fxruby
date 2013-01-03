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

/***********************************************************************
 * $Id: FXRbColorList.h 2303 2005-12-09 03:17:28Z lyle $
 ***********************************************************************/

#ifndef FXRBCOLORLIST_H
#define FXRBCOLORLIST_H

class FXRbColorItem : public FXColorItem {
  FXDECLARE(FXRbColorItem)
protected:
  FXRbColorItem(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbListItemVirtuals.h"
public:
  // Is this list item owned by an FXColorList yet?
  FXbool owned;
public:
  // Constructor
  FXRbColorItem(const FXString& text,FXColor clr,void* ptr=NULL) : FXColorItem(text,clr,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXColorItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXColorItem* self);

  // Destructor
  virtual ~FXRbColorItem(){
    FXRbUnregisterRubyObj(this);
    }
  };


class FXRbColorList : public FXColorList {
  FXDECLARE(FXRbColorList)
protected:
  FXRbColorList(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbScrollAreaVirtuals.h"
#include "FXRbListVirtuals.h"
public:
  /// Construct a list with initially no items in it
  FXRbColorList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=LIST_BROWSESELECT,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXColorList(p,tgt,sel,opts,x,y,w,h){
    }

  // Mark dependencies for the GC
  static void markfunc(FXColorList* self);

  // Unregister objects that this list owns and is about to destroy
  static void unregisterOwnedObjects(FXColorList *pColorList);

  // Destructor
  virtual ~FXRbColorList(){
    FXRbColorList::unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
