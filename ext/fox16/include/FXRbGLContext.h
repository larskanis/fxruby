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
 * $Id: FXRbGLContext.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBGLCONTEXT_H
#define FXRBGLCONTEXT_H

class FXRbGLContext : public FXGLContext {
  FXDECLARE(FXRbGLContext)
protected:
  FXRbGLContext(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
public:
  /**
   * Construct an OpenGL context with its own private display list.
   */
  FXRbGLContext(FXApp* a,FXGLVisual *vis) : FXGLContext(a,vis){}

  /**
   * Construct an OpenGL context sharing display lists with an
   * existing GL context.
   */
  FXRbGLContext(FXApp* a,FXGLVisual *vis,FXGLContext *shared) :
    FXGLContext(a,vis,shared){}

  // Mark dependencies for the GC
  static void markfunc(FXGLContext* self);

  // Destructor
  virtual ~FXRbGLContext(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
