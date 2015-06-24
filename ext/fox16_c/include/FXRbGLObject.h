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
 * $Id: FXRbGLObject.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBGLOBJECT_H
#define FXRBGLOBJECT_H

#define DECLARE_FXGLOBJECT_STUBS(klass) \
inline FXRangef klass ## _bounds(klass* self){ \
  FXRangef box; \
  self->klass::bounds(box); \
  return box; \
  } \
inline void klass ## _draw(klass* self,FXGLViewer* viewer){ \
  self->klass::draw(viewer); \
  } \
inline void klass ## _hit(klass* self,FXGLViewer* viewer){ \
  self->klass::hit(viewer); \
  } \
inline FXGLObject* klass ## _copy(klass* self){ \
  return self->klass::copy(); \
  } \
inline FXbool klass ## _canDrag(const klass* self){ \
  return self->klass::canDrag(); \
  } \
inline FXbool klass ## _canDelete(const klass* self){ \
  return self->klass::canDelete(); \
  } \
inline FXbool klass ## _drag(klass* self,FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty){ \
  return self->klass::drag(viewer,fx,fy,tx,ty); \
  }


#define IMPLEMENT_FXGLOBJECT_STUBS(cls) \
  void cls::bounds(FXRangef& box){ \
    box=FXRbCallRangeMethod(this,"bounds"); \
    } \
  void cls::draw(FXGLViewer* viewer){ \
    FXRbCallVoidMethod(this,"draw",viewer); \
    } \
  void cls::hit(FXGLViewer* viewer){ \
    FXRbCallVoidMethod(this,"hit",viewer); \
    } \
  FXGLObject* cls::copy(){ \
    return FXRbCallGLObjectMethod(this,"copy"); \
    } \
  FXGLObject* cls::identify(FXuint* path,FXint n){ \
    return FXRbCallGLObjectMethod(this,"identify",path,n); \
    } \
  FXbool cls::canDrag() const { \
    return FXRbCallBoolMethod(this,"canDrag"); \
    } \
  FXbool cls::canDelete() const{ \
    return FXRbCallBoolMethod(this,"canDelete"); \
    } \
  FXbool cls::drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty){ \
    return FXRbCallBoolMethod(this,"drag",viewer,fx,fy,tx,ty); \
    }


class FXRbGLObject : public FXGLObject {
  FXDECLARE(FXRbGLObject)
#include "FXRbObjectVirtuals.h"
#include "FXRbGLObjectVirtuals.h"
public:
  // Constructor
  FXRbGLObject(){}

  // Identify sub-object given path
  virtual FXGLObject* identify(FXuint* path,FXint n);

  // Mark dependencies for the GC
  static void markfunc(FXGLObject* self);

  // Destructor
  virtual ~FXRbGLObject(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
