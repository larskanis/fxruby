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
 * $Id: FXRbListBox.h 2255 2005-11-30 13:55:50Z lyle $
 ***********************************************************************/

#ifndef FXRBLISTBOX_H
#define FXRBLISTBOX_H

#define DECLARE_FXLISTBOX_STUBS(klass) \
inline void klass ## _setCurrentItem(klass* self,FXint index,FXbool notify){ \
  self->klass::setCurrentItem(index,notify); \
  }

#define IMPLEMENT_FXLISTBOX_STUBS(cls) \
  void cls::setCurrentItem(FXint index,FXbool notify){ \
    FXRbCallVoidMethod(this,"setCurrentItem",index,notify); \
    }

class FXRbListBox : public FXListBox {
  FXDECLARE(FXRbListBox)
protected:
  FXRbListBox(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbListBoxVirtuals.h"
public:
  /// Constructor
  FXRbListBox(FXComposite *p,FXObject* tgt,FXSelector sel,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb) : FXListBox(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb){
    setSortFunc(FXRbListBox::sortFunc);
    }

  // Sort function stand-in
  static FXint sortFunc(const FXListItem* a,const FXListItem* b);

  // Mark dependencies for the GC
  static void markfunc(FXListBox* self);

  // Destructor
  virtual ~FXRbListBox(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
