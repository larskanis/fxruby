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
 * $Id: FXRbCursor.h 2335 2006-01-28 02:33:03Z lyle $
 ***********************************************************************/

#ifndef FXRBCURSOR_H
#define FXRBCURSOR_H

#define DECLARE_FXCURSOR_STUBS(klass) \
inline bool klass ## _savePixels(const klass* self,FXStream& store){ \
  return self->klass::savePixels(store); \
  } \
inline bool klass ## _loadPixels(klass* self,FXStream& store){ \
  return self->klass::loadPixels(store); \
  }


#define IMPLEMENT_FXCURSOR_STUBS(cls) \
  bool cls::savePixels(FXStream& store) const { \
    return FXRbCallBoolMethod(this,"savePixels",store); \
    } \
  bool cls::loadPixels(FXStream& store){ \
    return FXRbCallBoolMethod(this,"loadPixels",store); \
    }

class FXRbCursor : public FXCursor {
  FXDECLARE(FXRbCursor)
protected:
  FXRbCursor(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbCursorVirtuals.h"
public:
  // Is this cursor owned by the FXApp?
  FXbool ownedByApp;

public:
  /// Make stock cursor
  FXRbCursor(FXApp* a,FXStockCursor curid=CURSOR_ARROW) : FXCursor(a,curid),ownedByApp(FALSE){
    FXRbRegisterAppSensitiveObject(this);
    }

  /// Make cursor from source and mask; cursor size should at most 32x32 for portability!
  FXRbCursor(FXApp* a,const FXuchar* src,const FXuchar* msk,FXint w=32,FXint h=32,FXint hx=0,FXint hy=0) : FXCursor(a,src,msk,w,h,hx,hy),ownedByApp(FALSE){
    FXRbRegisterAppSensitiveObject(this);
    }

  /// Make cursor from FXColor pixels; cursor size should at most 32x32 for portability!
  FXRbCursor(FXApp* a,const FXColor* pix,FXint w=32,FXint h=32,FXint hx=0,FXint hy=0) : FXCursor(a,pix,w,h,hx,hy),ownedByApp(FALSE){
    FXRbRegisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXCursor* cursor);

  // Destroy this object if it's not owned
  static void freefunc(FXCursor* self);

  // Destructor
  virtual ~FXRbCursor(){
    FXRbUnregisterRubyObj(this);
    FXRbUnregisterAppSensitiveObject(this);
    }
  };

#endif
