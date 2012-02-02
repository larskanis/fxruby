/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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
 * $Id: FXRbWizard.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBWIZARD_H
#define FXRBWIZARD_H

#ifndef FXWIZARD_H
#include "FXWizard.h"
#endif

class FXRbWizard : public FXWizard {
  FXDECLARE(FXRbWizard)
protected:
  FXRbWizard(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbTopWindowVirtuals.h"
#include "FXRbDialogBoxVirtuals.h"
public:
  /// Construct free-floating Wizard
  FXRbWizard(FXApp* a,const FXString& name,FXImage *image,FXuint opts=DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=10,FXint vs=10) : FXWizard(a,name,image,opts,x,y,w,h,pl,pr,pt,pb,hs,vs) {}

  /// Construct Wizard which will always float over the owner window
  FXRbWizard(FXWindow* owner,const FXString& name,FXImage *image,FXuint opts=DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=10,FXint vs=10) : FXWizard(owner,name,image,opts,x,y,w,h,pl,pr,pt,pb,hs,vs) {}

  // Mark dependencies for the GC
  static void markfunc(FXWizard* self);

  // Destructor
  virtual ~FXRbWizard(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
