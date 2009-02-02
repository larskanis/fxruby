/********************************************************************************
*                                                                               *
*                            B M P   I m a g e   O b j e c t                    *
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
* $Id: FXBMPImage.h 2725 2007-11-16 16:57:54Z lyle $                        *
********************************************************************************/
#ifndef FXBMPIMAGE_H
#define FXBMPIMAGE_H

#ifndef FXIMAGE_H
#include "FXImage.h"
#endif

namespace FX {


/**
* The BMP Image class is a convenience class for working with images in the
* Microsoft Bitmap (.bmp) graphics file format.  This makes it possible to
* use resources created with Windows development tools inside FOX without
* need for graphics file format translators.  The bitmap loaded handles
* 1, 4, and 8 bit paletted bitmaps, 16 and 24 bit RGB bitmaps, and
* 32 bit RGBA bitmaps.
*/
class FXAPI FXBMPImage : public FXImage {
  FXDECLARE(FXBMPImage)
protected:
  FXBMPImage(){}
private:
  FXBMPImage(const FXBMPImage&);
  FXBMPImage &operator=(const FXBMPImage&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct image from memory stream formatted in Microsoft BMP format
  FXBMPImage(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in Microsoft bitmap format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in Microsoft bitmap format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXBMPImage();
  };


/**
* Check if stream contains a bitmap, return true if so.
*/
extern FXAPI FXbool fxcheckBMP(FXStream& store);


/**
* Load an BMP (Microsoft Bitmap) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadBMP(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an BMP (Microsoft Bitmap) file to a stream.
*/
extern FXAPI FXbool fxsaveBMP(FXStream& store,const FXColor *data,FXint width,FXint height);

}

#endif
