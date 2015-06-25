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
 * at "lyle@rubyforge.org".
 ***********************************************************************/

/***********************************************************************
 * $Id: FXRbDockSite.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBDOCKSITE_H
#define FXRBDOCKSITE_H

#define DECLARE_FXDOCKSITE_STUBS(klass) \
  inline void klass ## _moveToolBar(klass* self,FXDockBar* bar,FXint barx,FXint bary){ \
    self->klass::moveToolBar(bar,barx,bary); \
    } \
  inline void klass ## _dockToolBar(klass* self,FXDockBar* bar,FXWindow* before){ \
    self->klass::dockToolBar(bar,before); \
    } \
  inline void klass ## _dockToolBar(klass* self,FXDockBar* bar,FXint barx,FXint bary){ \
    self->klass::dockToolBar(bar,barx,bary); \
    } \
  inline void klass ## _undockToolBar(klass* self,FXDockBar* bar){ \
    self->klass::undockToolBar(bar); \
    }

#define IMPLEMENT_FXDOCKSITE_STUBS(cls) \
  void cls::moveToolBar(FXDockBar* bar,FXint barx,FXint bary){ \
    FXRbCallVoidMethod(this,"moveToolBar",bar,barx,bary); \
    } \
  void cls::dockToolBar(FXDockBar* bar,FXWindow* before){ \
    FXRbCallVoidMethod(this,"dockToolBar",bar,before); \
    } \
  void cls::dockToolBar(FXDockBar* bar,FXint barx,FXint bary){ \
    FXRbCallVoidMethod(this,"dockToolBar",bar,barx,bary); \
    } \
  void cls::undockToolBar(FXDockBar* bar){ \
    FXRbCallVoidMethod(this,"undockToolBar",bar); \
    }


class FXRbDockSite : public FXDockSite {
  FXDECLARE(FXRbDockSite)
protected:
  FXRbDockSite(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbDockSiteVirtuals.h"
public:
  /**
  * Construct a toolbar dock layout manager.  Passing LAYOUT_SIDE_TOP or LAYOUT_SIDE_BOTTOM
  * causes the toolbar dock to be oriented horizontally.  Passing LAYOUT_SIDE_LEFT or
  * LAYOUT_SIDE_RIGHT causes it to be oriented vertically.
  */
  FXRbDockSite(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0,FXint hs=0,FXint vs=0) : FXDockSite(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Mark dependencies for the GC
  static void markfunc(FXDockSite* self);

  // Destructor
  virtual ~FXRbDockSite(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
