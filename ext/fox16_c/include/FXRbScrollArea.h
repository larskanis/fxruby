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
 * $Id: FXRbScrollArea.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBSCROLLAREA_H
#define FXRBSCROLLAREA_H

#define DECLARE_FXSCROLLAREA_STUBS(klass) \
inline FXint klass ## _getContentWidth(klass* self){ \
  return self->klass::getContentWidth(); \
  } \
inline FXint klass ## _getContentHeight(klass* self){ \
  return self->klass::getContentHeight(); \
  } \
inline FXint klass ## _getViewportWidth(klass* self){ \
  return self->klass::getViewportWidth(); \
  } \
inline FXint klass ## _getViewportHeight(klass* self){ \
  return self->klass::getViewportHeight(); \
  }


#define IMPLEMENT_FXSCROLLAREA_STUBS(cls) \
  FXint cls::getContentWidth(){ \
    return FXRbCallIntMethod(this,"getContentWidth"); \
    } \
  FXint cls::getContentHeight(){ \
    return FXRbCallIntMethod(this,"getContentHeight"); \
    } \
  FXint cls::getViewportWidth(){ \
    return FXRbCallIntMethod(this,"getViewportWidth"); \
    } \
  FXint cls::getViewportHeight(){ \
    return FXRbCallIntMethod(this,"getViewportHeight"); \
    }


class FXRbScrollArea : public FXScrollArea {
  FXDECLARE(FXRbScrollArea)
protected:
  FXRbScrollArea(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbScrollAreaVirtuals.h"
public:
  /// Constructor
  FXRbScrollArea(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXScrollArea(p,opts,x,y,w,h){}

  // Mark dependencies for the GC
  static void markfunc(FXScrollArea* self);

  // Unregister objects that this scroll area owns and is about to destroy
  static void unregisterOwnedObjects(FXScrollArea *pScrollArea);

  // Destructor
  virtual ~FXRbScrollArea(){
    FXRbScrollArea::unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(corner); // must do this here; no public accessor method for it
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
