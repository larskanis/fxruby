/********************************************************************************
*                                                                               *
*                          T I F F   I m a g e   O b j e c t                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2006 Eric Gillet.   All Rights Reserved.                   *
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
* $Id: FXTIFImage.h 2343 2006-02-12 20:26:26Z lyle $                        *
********************************************************************************/
#ifndef FXTIFIMAGE_H
#define FXTIFIMAGE_H

#ifndef FXIMAGE_H
#include "FXImage.h"
#endif

namespace FX {


/// TIFF Image class
class FXAPI FXTIFImage : public FXImage {
  FXDECLARE(FXTIFImage)
protected:
  FXushort codec;
protected:
  FXTIFImage(){}
private:
  FXTIFImage(const FXTIFImage&);
  FXTIFImage &operator=(const FXTIFImage&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct an image from memory stream formatted in TIFF format
  FXTIFImage(FXApp *a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// True if format is supported
  static const bool supported;

  /// Set codec to save with
  void setCodec(FXuint c){ codec=c; }

  /// Get codec setting
  FXuint getCodec() const { return codec; }

  /// Load pixels into stream in TIFF format
  virtual bool loadPixels(FXStream& store);

  /// Save pixels from stream in TIFF format
  virtual bool savePixels(FXStream& store) const;

  /// Destroy
  virtual ~FXTIFImage();
  };


/**
* Check if stream contains a TIFF, return TRUE if so.
*/
extern FXAPI bool fxcheckTIF(FXStream& store);


/**
* Load an TIFF (Tagged Image File Format) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadTIF(FXStream& store,FXColor*& data,FXint& width,FXint& height,FXushort& codec);


/**
* Save an TIFF (Tagged Image File Format) file to a stream.
*/
extern FXAPI bool fxsaveTIF(FXStream& store,const FXColor* data,FXint width,FXint height,FXushort codec);

}

#endif
