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
 * $Id: FXRbGLViewer.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBGLVIEWER_H
#define FXRBGLVIEWER_H

#define DECLARE_FXGLVIEWER_STUBS(klass) \
inline FXGLObject** klass ## _select(klass* self,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(FXRbGLViewer))); \
  return dynamic_cast<FXRbGLViewer*>(self)->_select(x,y,w,h); \
  } \
inline FXGLObject* klass ## _pick(klass *self,FXint x,FXint y){ \
  return self->klass::pick(x,y); \
  } \
inline FXbool klass ## _setBounds(klass *self,const FXRangef& box){ \
  return self->klass::setBounds(box); \
  }


#define IMPLEMENT_FXGLVIEWER_STUBS(cls) \
  FXGLObject** cls::select(FXint x,FXint y,FXint w,FXint h){ \
    return FXRbCallGLObjectArrayMethod(this,"select",x,y,w,h); \
    } \
  FXGLObject* cls::pick(FXint x,FXint y){ \
    return FXRbCallGLObjectMethod(this,"pick",x,y); \
    } \
  FXbool cls::setBounds(const FXRangef& box){ \
    return FXRbCallBoolMethod(this,"setBounds",box); \
    }


class FXRbGLViewer : public FXGLViewer {
  FXDECLARE(FXRbGLViewer)
protected:
  FXRbGLViewer(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbGLCanvasVirtuals.h"
#include "FXRbGLViewerVirtuals.h"
protected:
  virtual FXGLObject* processHits(FXuint *pickbuffer,FXint nhits);
public:
  /// Construct GL viewer widget
  FXRbGLViewer(FXComposite* p,FXGLVisual *vis,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXGLViewer(p,vis,tgt,sel,opts,x,y,w,h){}

  /// Construct GL viewer widget sharing display list with another GL viewer
  FXRbGLViewer(FXComposite* p,FXGLVisual *vis,FXGLViewer* sharegroup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXGLViewer(p,vis,sharegroup,tgt,sel,opts,x,y,w,h){}

  // Overrides the base class version of select()
  FXGLObject** _select(FXint x,FXint y,FXint w,FXint h);

  // Feedback buffer sort routine stand-in
  static FXbool sortProc(FXfloat*& buffer,FXint& used,FXint& size);

  // Mark dependencies for the GC
  static void markfunc(FXGLViewer* self);

  // Destructor
  virtual ~FXRbGLViewer(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
