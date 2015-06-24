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
 * $Id: FXRbBitmap.h 2335 2006-01-28 02:33:03Z lyle $
 ***********************************************************************/

#ifndef FXRBBITMAP_H
#define FXRBBITMAP_H

#define DECLARE_FXBITMAP_STUBS(cls) \
inline void cls ## _restore(cls* self){ \
  self->cls::restore(); \
  } \
inline void cls ## _render(cls* self){ \
  self->cls::render(); \
  } \
inline void cls ## _release(cls* self){ \
  self->cls::release(); \
  } \
inline bool cls ## _savePixels(const cls* self,FXStream& store){ \
  return self->cls::savePixels(store); \
  } \
inline bool cls ## _loadPixels(cls* self,FXStream& store){ \
  return self->cls::loadPixels(store); \
  } \
inline void cls ## _scale(cls* self,FXint w,FXint h){ \
  self->cls::scale(w,h); \
  } \
inline void cls ## _mirror(cls* self,FXbool horizontal,FXbool vertical){ \
  self->cls::mirror(horizontal,vertical); \
  } \
inline void cls ## _rotate(cls* self,FXint degrees){ \
  self->cls::rotate(degrees); \
  } \
inline void cls ## _crop(cls* self,FXint x,FXint y,FXint w,FXint h,FXbool color){ \
  self->cls::crop(x,y,w,h,color); \
  } \
inline void cls ## _fill(cls* self,FXbool color){ \
  self->cls::fill(color); \
  } \
inline void cls ## _setData(cls* self,FXuchar* pix,FXuint opts){ \
  self->cls::setData(pix,opts); \
  } \
inline void cls ## _setData(cls* self,FXuchar* pix,FXuint opts,FXint w,FXint h){ \
  self->cls::setData(pix,opts,w,h); \
  }


#define IMPLEMENT_FXBITMAP_STUBS(cls) \
  void cls::restore(){ \
    FXRbCallVoidMethod(this,"restore"); \
    } \
  void cls::render(){ \
    FXRbCallVoidMethod(this,"render"); \
    } \
  void cls::release(){ \
    FXRbCallVoidMethod(this,"release"); \
    } \
  bool cls::savePixels(FXStream& store) const { \
    return FXRbCallBoolMethod(this,"savePixels",store); \
    } \
  bool cls::loadPixels(FXStream& store){ \
    return FXRbCallBoolMethod(this,"loadPixels",store); \
    } \
  void cls::scale(FXint w,FXint h){ \
    FXRbCallVoidMethod(this,"scale",w,h); \
    } \
  void cls::mirror(FXbool horizontal,FXbool vertical){ \
    FXRbCallVoidMethod(this,"mirror",horizontal,vertical); \
    } \
  void cls::rotate(FXint degrees){ \
    FXRbCallVoidMethod(this,"rotate",degrees); \
    } \
  void cls::crop(FXint x,FXint y,FXint w,FXint h,FXbool color){ \
    FXRbCallVoidMethod(this,"crop",x,y,w,h,color); \
    } \
  void cls::fill(FXbool color){ \
    FXRbCallVoidMethod(this,"fill",color); \
    } \
  void cls::setData(FXuchar* pix,FXuint opts){ \
    FXRbCallVoidMethod(this,"setData",pix,opts); \
    } \
  void cls::setData(FXuchar* pix,FXuint opts,FXint w,FXint h){ \
    FXRbCallVoidMethod(this,"setData",pix,opts,w,h); \
    }



class FXRbBitmap : public FXBitmap {
  FXDECLARE(FXRbBitmap)
protected:
  FXRbBitmap(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbBitmapVirtuals.h"
public:
  /// Create an image
  FXRbBitmap(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1) : FXBitmap(a,pix,opts,w,h){
    FXRbRegisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXBitmap* bitmap);

  // Destructor
  virtual ~FXRbBitmap(){
    FXRbUnregisterRubyObj(this);
    FXRbUnregisterAppSensitiveObject(this);
    }
  };

#endif
