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
 * $Id: FXRbGLVisual.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBGLVISUAL_H
#define FXRBGLVISUAL_H

class FXRbGLVisual : public FXGLVisual {
  FXDECLARE(FXRbGLVisual)
protected:
  FXRbGLVisual(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
public:
  // Is this visual owned by the FXApp?
  FXbool ownedByApp;

public:
  /// Construct default visual
  FXRbGLVisual(FXApp* a,FXuint flags) : FXGLVisual(a,flags),ownedByApp(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXGLVisual* self);

  // Destroy this object if it's not owned
  static void freefunc(FXGLVisual* self);

  // Destructor
  virtual ~FXRbGLVisual(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
