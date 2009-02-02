/********************************************************************************
*                                                                               *
*                   S U N   R A S T E R   I m a g e   O b j e c t               *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXRASIcon.h 2725 2007-11-16 16:57:54Z lyle $                         *
********************************************************************************/
#ifndef FXRASICON_H
#define FXRASICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/// SUN Raster Image format icon
class FXAPI FXRASIcon : public FXIcon {
  FXDECLARE(FXRASIcon)
protected:
  FXRASIcon(){}
private:
  FXRASIcon(const FXRASIcon&);
  FXRASIcon &operator=(const FXRASIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct icon from memory stream formatted in SUN Raster Image format
  FXRASIcon(FXApp* a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in SUN Raster Image format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in SUN Raster Image format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXRASIcon();
  };


/**
* Check if stream contains a RAS, return true if so.
*/
extern FXAPI FXbool fxcheckRAS(FXStream& store);


/**
* Load an SUN Raster Image format file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadRAS(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an SUN Raster Image format file to a stream.
*/
extern FXAPI FXbool fxsaveRAS(FXStream& store,const FXColor *data,FXint width,FXint height);

}

#endif
