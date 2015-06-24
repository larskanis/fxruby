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
 * $Id: FXRbObject.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBOBJECT_H
#define FXRBOBJECT_H

#define DECLARE_FXOBJECT_STUBS(cls) \
inline void cls ## _save(const cls* self,FXStream& store){ \
  self->cls::save(store); \
  } \
inline void cls ## _load(cls* self,FXStream& store){ \
  self->cls::load(store); \
  }


#define IMPLEMENT_FXOBJECT_STUBS(cls) \
  void cls::save(FXStream& store) const { \
    FXRbCallVoidMethod(this,"save",store); \
    } \
  void cls::load(FXStream& store){ \
    FXRbCallVoidMethod(this,"load",store); \
    }


class FXRbObject : public FXObject {
  FXDECLARE(FXRbObject)
#include "FXRbObjectVirtuals.h"
public:
  // Constructor
  FXRbObject(){}

  // Mark dependencies for the GC
  static void markfunc(FXObject* self);

  // Mark dependencies for the GC
  static void freefunc(FXObject* self);

  // Destructor
  virtual ~FXRbObject(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
