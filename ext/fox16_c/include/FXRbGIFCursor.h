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
 * $Id: FXRbGIFCursor.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBGIFCURSOR_H
#define FXRBGIFCURSOR_H

class FXRbGIFCursor : public FXGIFCursor {
  FXDECLARE(FXRbGIFCursor)
protected:
  FXRbGIFCursor(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbCursorVirtuals.h"
public:
  // Is this cursor owned by the FXApp?
  FXbool ownedByApp;

public:
  /// Construct a cursor from memory stream formatted as CompuServe GIF format
  FXRbGIFCursor(FXApp* a,const void* pix,FXint hx=0,FXint hy=0):FXGIFCursor(a,pix,hx,hy),ownedByApp(FALSE){
    FXRbRegisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXGIFCursor* self);

  // Destroy this object if it's not owned
  static void freefunc(FXGIFCursor* self);

  // Destructor
  virtual ~FXRbGIFCursor(){
    FXRbUnregisterRubyObj(this);
    FXRbUnregisterAppSensitiveObject(this);
    }
  };

#endif
