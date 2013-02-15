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
 * $Id: FXRbMDIButton.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBMDIMENU_H
#define FXRBMDIMENU_H

class FXRbMDIDeleteButton : public FXMDIDeleteButton {
  FXDECLARE(FXRbMDIDeleteButton)
protected:
  FXRbMDIDeleteButton(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:
  /// Constructor
  FXRbMDIDeleteButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIDeleteButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbMDIDeleteButton(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIDeleteButton* self);
  };


class FXRbMDIRestoreButton : public FXMDIRestoreButton {
  FXDECLARE(FXRbMDIRestoreButton)
protected:
  FXRbMDIRestoreButton(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:
  /// Constructor
  FXRbMDIRestoreButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIRestoreButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbMDIRestoreButton(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIRestoreButton* self);
  };


class FXRbMDIMinimizeButton : public FXMDIMinimizeButton {
  FXDECLARE(FXRbMDIMinimizeButton)
protected:
  FXRbMDIMinimizeButton(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:
  /// Constructor
  FXRbMDIMinimizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIMinimizeButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbMDIMinimizeButton(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIMinimizeButton* self);
  };


class FXRbMDIMaximizeButton : public FXMDIMaximizeButton {
  FXDECLARE(FXRbMDIMaximizeButton)
protected:
  FXRbMDIMaximizeButton(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:
  /// Constructor
  FXRbMDIMaximizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIMaximizeButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbMDIMaximizeButton(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIMaximizeButton* self);
  };


class FXRbMDIWindowButton : public FXMDIWindowButton {
  FXDECLARE(FXRbMDIWindowButton)
protected:
  FXRbMDIWindowButton(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:
  /// Constructor
  FXRbMDIWindowButton(FXComposite* p,FXPopup* pup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIWindowButton(p,pup,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbMDIWindowButton(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIWindowButton* self);
  };


class FXRbMDIMenu : public FXMDIMenu {
  FXDECLARE(FXRbMDIMenu)
protected:
  FXRbMDIMenu(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbPopupVirtuals.h"
public:
  /// Construct MDI menu
  FXRbMDIMenu(FXWindow *owner,FXObject* tgt=NULL) : FXMDIMenu(owner,tgt){}

  // Destructor
  virtual ~FXRbMDIMenu(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIMenu* self);
  };

#endif
