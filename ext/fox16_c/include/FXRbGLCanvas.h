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
 * $Id: FXRbGLCanvas.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBGLCANVAS_H
#define FXRBGLCANVAS_H

#define DECLARE_FXGLCANVAS_STUBS(klass) \
inline FXbool klass ## _makeCurrent(klass* self){ \
  return self->klass::makeCurrent(); \
  } \
inline FXbool klass ## _makeNonCurrent(klass* self){ \
  return self->klass::makeNonCurrent(); \
  } \
inline FXbool klass ## _isCurrent(const klass* self){ \
  return self->klass::isCurrent(); \
  } \
inline void klass ## _swapBuffers(klass* self){ \
  self->klass::swapBuffers(); \
  }


#define IMPLEMENT_FXGLCANVAS_STUBS(cls) \
  FXbool cls::makeCurrent(){ \
    return FXRbCallBoolMethod(this,"makeCurrent"); \
    } \
  FXbool cls::makeNonCurrent(){ \
    return FXRbCallBoolMethod(this,"makeNonCurrent"); \
    } \
  FXbool cls::isCurrent() const { \
    return FXRbCallBoolMethod(this,"isCurrent"); \
    } \
  void cls::swapBuffers(){ \
    FXRbCallVoidMethod(this,"swapBuffers"); \
    }


class FXRbGLCanvas : public FXGLCanvas {
  FXDECLARE(FXRbGLCanvas)
protected:
  FXRbGLCanvas(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbGLCanvasVirtuals.h"
public:
  /**
  * Construct an OpenGL-capable canvas, with its own private display list.
  */
  FXRbGLCanvas(FXComposite* p,FXGLVisual *vis,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXGLCanvas(p,vis,tgt,sel,opts,x,y,w,h){}

  /**
  * Construct an OpenGL-capable canvas, sharing display
  * list with another GL canvas.  This canvas becomes a member
  * of a display list share group.  All members of the display
  * list share group have to have the same visual.
  */
  FXRbGLCanvas(FXComposite* p,FXGLVisual *vis,FXGLCanvas* sharegroup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXGLCanvas(p,vis,sharegroup,tgt,sel,opts,x,y,w,h){}

  // Mark dependencies for the GC
  static void markfunc(FXGLCanvas* self);

  // Destructor
  virtual ~FXRbGLCanvas(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
