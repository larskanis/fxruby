/********************************************************************************
*                                                                               *
*                            P P M   I m a g e   O b j e c t                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 2003,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXPPMImage.h 2725 2007-11-16 16:57:54Z lyle $                        *
********************************************************************************/
#ifndef FXPPMIMAGE_H
#define FXPPMIMAGE_H

#ifndef FXIMAGE_H
#include "FXImage.h"
#endif

namespace FX {


/// Portable Pixmap Image
class FXAPI FXPPMImage : public FXImage {
  FXDECLARE(FXPPMImage)
protected:
  FXPPMImage(){}
private:
  FXPPMImage(const FXPPMImage&);
  FXPPMImage &operator=(const FXPPMImage&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct icon from memory stream formatted in Portable Pixmap format
  FXPPMImage(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in Portable Pixmap format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in Portable Pixmap format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXPPMImage();
  };


/**
* Check if stream contains a PPM, return true if so.
*/
extern FXAPI FXbool fxcheckPPM(FXStream& store);


/**
* Load an PPM (Portable Pixmap Format) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadPPM(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an PPM (Portable Pixmap Format) file to a stream.
*/
extern FXAPI FXbool fxsavePPM(FXStream& store,const FXColor *data,FXint width,FXint height);

}

#endif
