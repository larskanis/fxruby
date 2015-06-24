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
 * $Id: FXRbDockBar.h 2225 2005-11-08 13:51:28Z lyle $
 ***********************************************************************/

#ifndef FXRBDOCKBAR_H
#define FXRBDOCKBAR_H

#define DECLARE_FXDOCKBAR_STUBS(klass) \
  inline void klass ## _dock(klass* self,FXDockSite* docksite,FXWindow* before,FXbool notify){ \
    self->klass::dock(docksite,before,notify); \
    } \
  inline void klass ## _dock(klass* self,FXDockSite* docksite,FXint localx,FXint localy,FXbool notify){ \
    self->klass::dock(docksite,localx,localy,notify); \
    } \
  inline void klass ## _undock(klass* self,FXint rootx,FXint rooty,FXbool notify){ \
    self->klass::undock(rootx,rooty,notify); \
    }

#define IMPLEMENT_FXDOCKBAR_STUBS(cls) \
  void cls::dock(FXDockSite* docksite,FXWindow* before,FXbool notify){ \
    FXRbCallVoidMethod(this,"dock",docksite,before,notify); \
    } \
  void cls::dock(FXDockSite* docksite,FXint localx,FXint localy,FXbool notify){ \
    FXRbCallVoidMethod(this,"dock",docksite,localx,localy,notify); \
    } \
  void cls::undock(FXint rootx,FXint rooty, FXbool notify){ \
    FXRbCallVoidMethod(this,"undock",rootx,rooty,notify); \
    }


class FXRbDockBar : public FXDockBar {
  FXDECLARE(FXRbDockBar)
protected:
  FXRbDockBar(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbDockBarVirtuals.h"
public:
  /**
  * Construct a floatable Dockbar
  * Normally, the Dockbar is docked under window p.
  * When floated, the Dockbar can be docked under window q, which is
  * typically an FXToolBarShell window.
  */
  FXRbDockBar(FXComposite* p,FXComposite* q,FXuint opts=LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING) : FXDockBar(p,q,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  /**
  * Construct a non-floatable Dockbar.
  * The Dockbar can not be undocked.
  */
  FXRbDockBar(FXComposite* p,FXuint opts=LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=2,FXint pr=3,FXint pt=3,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING) : FXDockBar(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Destructor
  virtual ~FXRbDockBar(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXDockBar* self);
  };

#endif
