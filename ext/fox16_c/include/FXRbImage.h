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
 * $Id: FXRbImage.h 2336 2006-02-04 15:20:33Z lyle $
 ***********************************************************************/

#ifndef FXRBIMAGE_H
#define FXRBIMAGE_H

#define DECLARE_FXIMAGE_STUBS(klass) \
inline void klass ## _restore(klass* self){ \
  self->klass::restore(); \
  } \
inline void klass ## _render(klass* self){ \
  self->klass::render(); \
  } \
inline void klass ## _release(klass* self){ \
  self->klass::release(); \
  } \
inline void klass ## _scale(klass* self,FXint w,FXint h,FXint quality){ \
  self->klass::scale(w,h,quality); \
  } \
inline void klass ## _mirror(klass* self,bool horizontal,bool vertical){ \
  self->klass::mirror(horizontal,vertical); \
  } \
inline void klass ## _rotate(klass* self,FXint degrees){ \
  self->klass::rotate(degrees); \
  } \
inline void klass ## _crop(klass* self,FXint x,FXint y,FXint w,FXint h,FXColor color){ \
  self->klass::crop(x,y,w,h,color); \
  } \
inline void klass ## _fill(klass* self,FXColor color){ \
  self->klass::fill(color); \
  } \
inline void klass ## _fade(klass* self,FXColor color,FXint factor){ \
  self->klass::fade(color,factor); \
  } \
inline void klass ## _xshear(klass* self,FXint shear,FXColor clr){ \
  self->klass::xshear(shear,clr); \
  } \
inline void klass ## _yshear(klass* self,FXint shear,FXColor clr){ \
  self->klass::yshear(shear,clr); \
  } \
inline void klass ## _hgradient(klass* self,FXColor left,FXColor right){ \
  self->klass::hgradient(left,right); \
  } \
inline void klass ## _vgradient(klass* self,FXColor top,FXColor bottom){ \
  self->klass::vgradient(top,bottom); \
  } \
inline void klass ## _gradient(klass* self,FXColor topleft,FXColor topright,FXColor bottomleft,FXColor bottomright){ \
  self->klass::gradient(topleft,topright,bottomleft,bottomright); \
  } \
inline void klass ## _blend(klass* self,FXColor color){ \
  self->klass::blend(color); \
  } \
inline bool klass ## _savePixels_gvl(const klass* self,FXStream& store){ \
  return self->klass::savePixels(store); \
  } \
inline bool klass ## _loadPixels_gvl(klass* self,FXStream& store){ \
  return self->klass::loadPixels(store); \
  }


#define IMPLEMENT_FXIMAGE_STUBS(cls) \
  void cls::restore(){ \
    FXRbCallVoidMethod(this,"restore"); \
    } \
  void cls::render(){ \
    FXRbCallVoidMethod(this,"render"); \
    } \
  void cls::release(){ \
    FXRbCallVoidMethod(this,"release"); \
    } \
  void cls::scale(FXint w,FXint h,FXint quality){ \
    FXRbCallVoidMethod(this,"scale",w,h,quality); \
    } \
  void cls::mirror(bool horizontal,bool vertical){ \
    FXRbCallVoidMethod(this,"mirror",horizontal,vertical); \
    } \
  void cls::rotate(FXint degrees){ \
    FXRbCallVoidMethod(this,"rotate",degrees); \
    } \
  void cls::crop(FXint x,FXint y,FXint w,FXint h,FXColor color){ \
    FXRbCallVoidMethod(this,"crop",x,y,w,h,color); \
    } \
  void cls::fill(FXColor color){ \
    FXRbCallVoidMethod(this,"fill",color); \
    } \
  void cls::fade(FXColor color,FXint factor){ \
    FXRbCallVoidMethod(this,"fade",color,factor); \
    } \
  void cls::xshear(FXint shear,FXColor clr){ \
    FXRbCallVoidMethod(this,"xshear",shear,clr); \
    } \
  void cls::yshear(FXint shear,FXColor clr){ \
    FXRbCallVoidMethod(this,"yshear",shear,clr); \
    } \
  void cls::hgradient(FXColor left,FXColor right){ \
    FXRbCallVoidMethod(this,"hgradient",left,right); \
    } \
  void cls::vgradient(FXColor top,FXColor bottom){ \
    FXRbCallVoidMethod(this,"vgradient",top,bottom); \
    } \
  void cls::gradient(FXColor topleft,FXColor topright,FXColor bottomleft,FXColor bottomright){ \
    FXRbCallVoidMethod(this,"gradient",topleft,topright,bottomleft,bottomright); \
    } \
  void cls::blend(FXColor color){ \
    FXRbCallVoidMethod(this,"blend",color); \
    } \
  bool cls::savePixels(FXStream& store) const { \
    return FXRbCallBoolMethod(this,"savePixels",store); \
    } \
  bool cls::loadPixels(FXStream& store){ \
    return FXRbCallBoolMethod(this,"loadPixels",store); \
    }


class FXRbImage : public FXImage {
  FXDECLARE(FXRbImage)
protected:
  FXRbImage(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbImageVirtuals.h"
public:
  /// Create an image
  FXRbImage(FXApp* a,const FXColor* pix=NULL,FXuint opts=0,FXint w=1,FXint h=1):FXImage(a,pix,opts,w,h){
    FXRbRegisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXImage* image);

  // Destructor
  virtual ~FXRbImage(){
    FXRbUnregisterRubyObj(this);
    FXRbUnregisterAppSensitiveObject(this);
    }
  };

#endif
