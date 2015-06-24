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
 * $Id: FXRbMDIClient.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBMDICLIENT_H
#define FXRBMDICLIENT_H

#define DECLARE_FXMDICLIENT_STUBS(klass) \
  inline FXbool klass ## _setActiveChild(klass* self,FXMDIChild* child,FXbool notify){ \
    return self->klass::setActiveChild(child,notify); \
    } \
  inline void klass ## _cascade(klass* self,FXbool notify){ \
    self->klass::cascade(notify); \
    } \
  inline void klass ## _horizontal(klass* self,FXbool notify){ \
    self->klass::horizontal(notify); \
    } \
  inline void klass ## _vertical(klass* self,FXbool notify){ \
    self->klass::vertical(notify); \
    }

#define IMPLEMENT_FXMDICLIENT_STUBS(cls) \
  FXbool cls::setActiveChild(FXMDIChild* child,FXbool notify){ \
    return FXRbCallBoolMethod(this,"setActiveChild",child,notify); \
    } \
  void cls::cascade(FXbool notify){ \
    FXRbCallVoidMethod(this,"cascade",notify); \
    } \
  void cls::horizontal(FXbool notify){ \
    FXRbCallVoidMethod(this,"horizontal",notify); \
    } \
  void cls::vertical(FXbool notify){ \
    FXRbCallVoidMethod(this,"vertical",notify); \
    }

class FXRbMDIClient : public FXMDIClient {
  FXDECLARE(FXRbMDIClient)
protected:
  FXRbMDIClient(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbMDIClientVirtuals.h"
public:
  /// Construct MDI Client window
  FXRbMDIClient(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIClient(p,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbMDIClient(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIClient* self);
  };

#endif
