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
 * $Id: FXRbTopWindow.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBTOPWINDOW_H
#define FXRBTOPWINDOW_H

#define DECLARE_FXTOPWINDOW_STUBS(klass) \
inline void klass ## _show(klass* self,FXuint placement){ \
  self->klass::show(placement); \
  } \
inline FXbool klass ## _maximize(klass* self,FXbool notify){ \
  return self->klass::maximize(notify); \
  } \
inline FXbool klass ## _minimize(klass* self,FXbool notify){ \
  return self->klass::minimize(notify); \
  } \
inline FXbool klass ## _restore(klass* self,FXbool notify){ \
  return self->klass::restore(notify); \
  } \
inline FXbool klass ## _close(klass* self,FXbool notify){ \
  return self->klass::close(notify); \
  }


#define IMPLEMENT_FXTOPWINDOW_STUBS(cls) \
  void cls::show(FXuint placement){ \
    FXRbCallVoidMethod(this,"show",placement); \
    } \
  FXbool cls::maximize(FXbool notify){ \
    return FXRbCallBoolMethod(this,"maximize",notify); \
    } \
  FXbool cls::minimize(FXbool notify){ \
    return FXRbCallBoolMethod(this,"minimize",notify); \
    } \
  FXbool cls::restore(FXbool notify){ \
    return FXRbCallBoolMethod(this,"restore",notify); \
    } \
  FXbool cls::close(FXbool notify){ \
    return FXRbCallBoolMethod(this,"close",notify); \
    }


class FXRbTopWindow : public FXTopWindow {
  FXDECLARE(FXRbTopWindow)
protected:
  FXRbTopWindow(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbTopWindowVirtuals.h"
public:
  // Construct unowned top-level window
  FXRbTopWindow(FXApp* a,const FXString& name,FXIcon *ic,FXIcon *mi,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb,FXint hs,FXint vs) : FXTopWindow(a,name,ic,mi,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Construct owned top-level window
  FXRbTopWindow(FXWindow* owner,const FXString& name,FXIcon *ic,FXIcon *mi,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb,FXint hs,FXint vs) : FXTopWindow(owner,name,ic,mi,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Mark dependencies for the GC
  static void markfunc(FXTopWindow* top);

  // Destructor
  virtual ~FXRbTopWindow(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
