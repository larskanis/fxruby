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
 * $Id: FXRbIconSource.h 2259 2005-12-01 13:51:21Z lyle $
 ***********************************************************************/

#ifndef FXRBICONSOURCE_H
#define FXRBICONSOURCE_H

#define DECLARE_FXICONSOURCE_STUBS(cls) \
inline FXIcon* cls ## _loadIconFile(const cls* self,const FXString& filename,const FXString& type){ \
  return self->cls::loadIconFile(filename,type); \
  } \
inline FXIcon* cls ## _loadIconData(const cls* self,const void* pixels,const FXString& type){ \
  return self->cls::loadIconData(pixels,type); \
  } \
inline FXIcon* cls ## _loadIconStream(const cls* self,FXStream& store,const FXString& type){ \
  return self->cls::loadIconStream(store,type); \
  } \
inline FXImage* cls ## _loadImageFile(const cls* self,const FXString& filename,const FXString& type){ \
  return self->cls::loadImageFile(filename,type); \
  } \
inline FXImage* cls ## _loadImageData(const cls* self,const void* pixels,const FXString& type){ \
  return self->cls::loadImageData(pixels,type); \
  } \
inline FXImage* cls ## _loadImageStream(const cls* self,FXStream& store,const FXString& type){ \
  return self->cls::loadImageStream(store,type); \
  } \
inline FXIcon* cls ## _loadScaledIconFile(const cls* self,const FXString& filename,FXint size,FXint qual,const FXString& type){ \
  return self->cls::loadScaledIconFile(filename,size,qual,type); \
  } \
inline FXIcon* cls ## _loadScaledIconData(const cls* self,const void* pixels,FXint size,FXint qual,const FXString& type){ \
  return self->cls::loadScaledIconData(pixels,size,qual,type); \
  } \
inline FXIcon* cls ## _loadScaledIconStream(const cls* self,FXStream& store,FXint size,FXint qual,const FXString& type){ \
  return self->cls::loadScaledIconStream(store,size,qual,type); \
  } \
inline FXImage* cls ## _loadScaledImageFile(const cls* self,const FXString& filename,FXint size,FXint qual,const FXString& type){ \
  return self->cls::loadScaledImageFile(filename,size,qual,type); \
  } \
inline FXImage* cls ## _loadScaledImageData(const cls* self,const void* pixels,FXint size,FXint qual,const FXString& type){ \
  return self->cls::loadScaledImageData(pixels,size,qual,type); \
  } \
inline FXImage* cls ## _loadScaledImageStream(const cls* self,FXStream& store,FXint size,FXint qual,const FXString& type){ \
  return self->cls::loadScaledImageStream(store,size,qual,type); \
  }


#define IMPLEMENT_FXICONSOURCE_STUBS(cls) \
  FXIcon* cls::loadIconFile(const FXString& filename,const FXString& type) const { \
    return FXRbCallIconMethod(this,"loadIconFile",filename,type); \
    } \
  FXIcon* cls::loadIconData(const void* pixels,const FXString& type) const { \
    return FXRbCallIconMethod(this,"loadIconData",pixels,type); \
    } \
  FXIcon* cls::loadIconStream(FXStream& store,const FXString& type) const { \
    return FXRbCallIconMethod(this,"loadIconStream",store,type); \
    } \
  FXImage* cls::loadImageFile(const FXString& filename,const FXString& type) const { \
    return FXRbCallImageMethod(this,"loadImageFile",filename,type); \
    } \
  FXImage* cls::loadImageData(const void* pixels,const FXString& type) const { \
    return FXRbCallImageMethod(this,"loadImageData",pixels,type); \
    } \
  FXImage* cls::loadImageStream(FXStream& store,const FXString& type) const { \
    return FXRbCallImageMethod(this,"loadImageStream",store,type); \
    } \
  FXIcon* cls::loadScaledIconFile(const FXString& filename,FXint size,FXint qual,const FXString& type) const { \
    return FXRbCallIconMethod(this,"loadScaledIconFile",filename,size,qual,type); \
    } \
  FXIcon* cls::loadScaledIconData(const void* pixels,FXint size,FXint qual,const FXString& type) const { \
    return FXRbCallIconMethod(this,"loadScaledIconData",pixels,size,qual,type); \
    } \
  FXIcon* cls::loadScaledIconStream(FXStream& store,FXint size,FXint qual,const FXString& type) const { \
    return FXRbCallIconMethod(this,"loadScaledIconStream",store,size,qual,type); \
    } \
  FXImage* cls::loadScaledImageFile(const FXString& filename,FXint size,FXint qual,const FXString& type) const { \
    return FXRbCallImageMethod(this,"loadScaledImageFile",filename,size,qual,type); \
    } \
  FXImage* cls::loadScaledImageData(const void* pixels,FXint size,FXint qual,const FXString& type) const { \
    return FXRbCallImageMethod(this,"loadScaledImageData",pixels,size,qual,type); \
    } \
  FXImage* cls::loadScaledImageStream(FXStream& store,FXint size,FXint qual,const FXString& type) const { \
    return FXRbCallImageMethod(this,"loadScaledImageStream",store,size,qual,type); \
    }


class FXRbIconSource : public FXIconSource {
  FXDECLARE(FXRbIconSource)
protected:
  FXRbIconSource(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIconSourceVirtuals.h"
public:
  // Constructor
  FXRbIconSource(FXApp* app) : FXIconSource(app){}

  // Mark dependencies for the GC
  static void markfunc(FXIconSource* self);

  // Destructor
  virtual ~FXRbIconSource(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
