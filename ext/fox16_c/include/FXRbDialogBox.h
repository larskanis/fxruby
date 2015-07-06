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
 * $Id: FXRbDialogBox.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBDIALOGBOX_H
#define FXRBDIALOGBOX_H

#define DECLARE_FXDIALOGBOX_STUBS(klass) \
inline FXuint klass ## _execute_gvl(klass* self,FXuint placement){ \
  return self->klass::execute(placement); \
  }


#define IMPLEMENT_FXDIALOGBOX_STUBS(cls) \
  FXuint cls::execute(FXuint placement){ \
    return FXRbCallUIntMethod(this,"execute",placement); \
    }


class FXRbDialogBox : public FXDialogBox {
  FXDECLARE(FXRbDialogBox)
protected:
  FXRbDialogBox(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbTopWindowVirtuals.h"
#include "FXRbDialogBoxVirtuals.h"
public:
  /// Construct free-floating dialog
  FXRbDialogBox(FXApp* a,const FXString& name,FXuint opts=DECOR_TITLE|DECOR_BORDER,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=4,FXint vs=4) : FXDialogBox(a,name,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  /// Construct dialog which will always float over the owner window
  FXRbDialogBox(FXWindow* owner,const FXString& name,FXuint opts=DECOR_TITLE|DECOR_BORDER,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=4,FXint vs=4) : FXDialogBox(owner,name,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Mark dependencies for the GC
  static void markfunc(FXDialogBox* dlg);

  // Destructor
  virtual ~FXRbDialogBox(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
