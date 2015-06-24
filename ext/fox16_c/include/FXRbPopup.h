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
 * $Id: FXRbPopup.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBPOPUP_H
#define FXRBPOPUP_H

#define DECLARE_FXPOPUP_STUBS(klass) \
inline void klass ## _popup(klass* self,FXWindow* grabto,FXint x,FXint y,FXint w,FXint h){ \
  self->klass::popup(grabto,x,y,w,h); \
  } \
inline void klass ## _popdown(klass* self){ \
  self->klass::popdown(); \
  }


#define IMPLEMENT_FXPOPUP_STUBS(cls) \
  void cls::popup(FXWindow* grabto,FXint x,FXint y,FXint w,FXint h){ \
    FXRbCallVoidMethod(this,"popup",grabto,x,y,w,h); \
    } \
  void cls::popdown(){ \
    FXRbCallVoidMethod(this,"popdown"); \
    }


class FXRbPopup : public FXPopup {
  FXDECLARE(FXRbPopup)
protected:
  FXRbPopup(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbPopupVirtuals.h"
public:
  /// Construct popup pane
  FXRbPopup(FXWindow* owner,FXuint opts=POPUP_VERTICAL|FRAME_RAISED|FRAME_THICK,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXPopup(owner,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbPopup(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXPopup* self);
  };

#endif
