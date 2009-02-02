/********************************************************************************
*                                                                               *
*                         G I F   I m a g e   O b j e c t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXGIFImage.h 2342 2006-02-10 14:24:44Z lyle $                        *
********************************************************************************/
#ifndef FXGIFIMAGE_H
#define FXGIFIMAGE_H

#ifndef FXIMAGE_H
#include "FXImage.h"
#endif

namespace FX {

/// GIF Image class
class FXAPI FXGIFImage : public FXImage {
  FXDECLARE(FXGIFImage)
protected:
  FXGIFImage(){}
private:
  FXGIFImage(const FXGIFImage&);
  FXGIFImage &operator=(const FXGIFImage&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct an image from memory stream formatted as CompuServe GIF format
  FXGIFImage(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in [un]GIF format
  virtual bool savePixels(FXStream& store) const;

  /// Load pixels from stream in CompuServe GIF format
  virtual bool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXGIFImage();
  };


#ifndef FXLOADGIF
#define FXLOADGIF

/**
* Check if stream contains a GIF, return TRUE if so.
*/
extern FXAPI bool fxcheckGIF(FXStream& store);


/**
* Load an GIF (Graphics Interchange Format) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadGIF(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an GIF (Graphics Interchange Format) file to a stream.
*/
extern FXAPI bool fxsaveGIF(FXStream& store,const FXColor *data,FXint width,FXint height,bool fast=true);

#endif

}

#endif
