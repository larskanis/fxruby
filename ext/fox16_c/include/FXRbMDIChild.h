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
 * $Id: FXRbMDIChild.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBMDICHILD_H
#define FXRBMDICHILD_H

#define DECLARE_FXMDICHILD_STUBS(klass) \
inline FXbool klass ## _minimize(klass* self,FXbool notify){ \
  return self->klass::minimize(notify); \
  } \
inline FXbool klass ## _maximize(klass* self,FXbool notify){ \
  return self->klass::maximize(notify); \
  } \
inline FXbool klass ## _restore(klass* self,FXbool notify){ \
  return self->klass::restore(notify); \
  } \
inline FXbool klass ## _close(klass* self,FXbool notify){ \
  return self->klass::close(notify); \
  }


#define IMPLEMENT_FXMDICHILD_STUBS(cls) \
  FXbool cls::minimize(FXbool notify){ \
    return FXRbCallBoolMethod(this,"minimize",notify); \
    } \
  FXbool cls::maximize(FXbool notify){ \
    return FXRbCallBoolMethod(this,"maximize",notify); \
    } \
  FXbool cls::restore(FXbool notify){ \
    return FXRbCallBoolMethod(this,"restore",notify); \
    } \
  FXbool cls::close(FXbool notify){ \
    return FXRbCallBoolMethod(this,"close",notify); \
    }


class FXRbMDIChild : public FXMDIChild {
  FXDECLARE(FXRbMDIChild)
protected:
  FXRbMDIChild(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbMDIChildVirtuals.h"
public:
  /// Construct MDI Child window with given name and icon
  FXRbMDIChild(FXMDIClient* p,const FXString& name,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIChild(p,name,ic,pup,opts,x,y,w,h){}

  // Destructor
  virtual ~FXRbMDIChild(){
    FXRbUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIChild* self);
  };

#endif
