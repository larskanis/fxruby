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
 * $Id: FXRbHeader.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBHEADER_H
#define FXRBHEADER_H

#define DECLARE_FXHEADERITEM_STUBS(klass) \
inline void klass ## _setText(klass* self,const FXString& text){ \
  self->klass::setText(text); \
  } \
inline void klass ## _setIcon(klass* self,FXIcon* icn){ \
  self->klass::setIcon(icn); \
  } \
inline FXint klass ## _getWidth(const klass* self,const FXHeader* header){ \
  return self->klass::getWidth(header); \
  } \
inline FXint klass ## _getHeight(const klass* self,const FXHeader* header){ \
  return self->klass::getHeight(header); \
  } \
inline void klass ## _create(klass* self){ \
  self->klass::create(); \
  } \
inline void klass ## _detach(klass* self){ \
  self->klass::detach(); \
  } \
inline void klass ## _destroy(klass* self){ \
  self->klass::destroy(); \
  }


#define IMPLEMENT_FXHEADERITEM_STUBS(cls) \
  void cls::setText(const FXString& text){ \
    FXRbCallVoidMethod(this,"setText",text); \
    } \
  void cls::setIcon(FXIcon* icn){ \
    FXRbCallVoidMethod(this,"setIcon",icn); \
    } \
  FXint cls::getWidth(const FXHeader* header) const { \
    return FXRbCallIntMethod(this,"getWidth",header); \
    } \
  FXint cls::getHeight(const FXHeader* header) const { \
    return FXRbCallIntMethod(this,"getHeight",header); \
    } \
  void cls::create(){ \
    FXRbCallVoidMethod(this,"create"); \
    } \
  void cls::detach(){ \
    FXRbCallVoidMethod(this,"detach"); \
    } \
  void cls::destroy(){ \
    FXRbCallVoidMethod(this,"destroy"); \
    }


class FXRbHeaderItem : public FXHeaderItem {
  FXDECLARE(FXRbHeaderItem)
protected:
  FXRbHeaderItem(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbHeaderItemVirtuals.h"
public:
  // Is this header item owned by an FXHeader yet?
  FXbool owned;
public:
  /// Construct new item with given text, icon, size, and user-data
  FXRbHeaderItem(const FXString& text,FXIcon* ic=NULL,FXint s=0,void* ptr=NULL) : FXHeaderItem(text,ic,s,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXHeaderItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXHeaderItem* self);

  // Destructor
  virtual ~FXRbHeaderItem(){
    FXRbUnregisterRubyObj(this);
    }
  };


class FXRbHeader : public FXHeader {
  FXDECLARE(FXRbHeader)
protected:
  FXRbHeader(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:
  /// Construct new header control
  FXRbHeader(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=HEADER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD) : FXHeader(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb){}

  // Mark dependencies for the GC
  static void markfunc(FXHeader* self);

  // Unregister objects that this header owns and is about to destroy
  static void unregisterOwnedObjects(FXHeader *pHeader);

  // Destructor
  virtual ~FXRbHeader(){
    unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
