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
 * $Id: FXRbTGAImage.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBTGAIMAGE_H
#define FXRBTGAIMAGE_H

class FXRbTGAImage : public FXTGAImage {
  FXDECLARE(FXRbTGAImage)
protected:
  FXRbTGAImage(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbImageVirtuals.h"
public:
  /// Construct an image from memory stream formatted as TGA format
  FXRbTGAImage(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1) : FXTGAImage(a,pix,opts,w,h){
    FXRbRegisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXTGAImage* self);

  // Destructor
  virtual ~FXRbTGAImage(){
    FXRbUnregisterRubyObj(this);
    FXRbUnregisterAppSensitiveObject(this);
    }
  };

#endif
