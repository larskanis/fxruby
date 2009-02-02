/********************************************************************************
*                                                                               *
*                         G I F   I m a g e   O b j e c t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXGIFImage.h 2744 2007-11-16 22:16:04Z lyle $                        *
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
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in CompuServe GIF format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXGIFImage();
  };


#ifndef FXLOADGIF
#define FXLOADGIF

/**
* Check if stream contains a GIF, return true if so.
*/
extern FXAPI FXbool fxcheckGIF(FXStream& store);


/**
* Load an GIF (Graphics Interchange Format) file from a stream; if the flag 
* flag is true, the background color is considered transparent.  Upon successful return, 
* the pixel array and size are returned.  If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadGIF(FXStream& store,FXColor*& data,FXint& width,FXint& height,FXbool flag=true);


/**
* Save an GIF (Graphics Interchange Format) file to a stream.  If flag
* is true, the faster Floyd-Steinberg dither method instead of the slower Wu 
* quantization algorithm.
*/
extern FXAPI FXbool fxsaveGIF(FXStream& store,const FXColor *data,FXint width,FXint height,FXbool flag=true);

#endif

}

#endif
