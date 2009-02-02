/********************************************************************************
*                                                                               *
*                          T I F F   I c o n   O b j e c t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2007 Eric Gillet.   All Rights Reserved.                   *
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
* $Id: FXTIFIcon.h 2766 2007-11-19 18:16:33Z lyle $                         *
********************************************************************************/
#ifndef FXTIFICON_H
#define FXTIFICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/// TIFF Icon class
class FXAPI FXTIFIcon : public FXIcon {
  FXDECLARE(FXTIFIcon)
protected:
  FXushort codec;
protected:
  FXTIFIcon(){}
private:
  FXTIFIcon(const FXTIFIcon&);
  FXTIFIcon &operator=(const FXTIFIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct an icon from memory stream formatted in TIFF format
  FXTIFIcon(FXApp *a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// True if format is supported
  static const FXbool supported;

  /// Set codec to save with
  void setCodec(FXuint c){ codec=c; }

  /// Get codec setting
  FXuint getCodec() const { return codec; }

  /// Save pixels into stream in TIFF format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in TIFF format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXTIFIcon();
  };


/**
* Check if stream contains a TIFF, return true if so.
*/
extern FXAPI FXbool fxcheckTIF(FXStream& store);


/**
* Load an TIFF (Tagged Image File Format) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadTIF(FXStream& store,FXColor*& data,FXint& width,FXint& height,FXushort& codec);


/**
* Save an TIFF (Tagged Image File Format) file to a stream.
*/
extern FXAPI FXbool fxsaveTIF(FXStream& store,const FXColor* data,FXint width,FXint height,FXushort codec);

}

#endif
