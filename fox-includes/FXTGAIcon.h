/********************************************************************************
*                                                                               *
*                     T A R G A   I c o n   O b j e c t                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2007 by Janusz Ganczarski.   All Rights Reserved.          *
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
* $Id: FXTGAIcon.h 2766 2007-11-19 18:16:33Z lyle $                         *
********************************************************************************/
#ifndef FXTGAICON_H
#define FXTGAICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/// TARGA image format icon
class FXAPI FXTGAIcon : public FXIcon {
  FXDECLARE(FXTGAIcon)
protected:
  FXTGAIcon(){}
private:
  FXTGAIcon(const FXTGAIcon&);
  FXTGAIcon &operator=(const FXTGAIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct icon from memory stream formatted in TARGA format
  FXTGAIcon(FXApp* a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in TARGA format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in TARGA format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXTGAIcon();
  };


/**
* Check if stream contains a TARGA, return true if so.
*/
extern FXAPI FXbool fxcheckTGA(FXStream& store);


/**
* Load an TARGA file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadTGA(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an TARGA file to a stream.
*/
extern FXAPI FXbool fxsaveTGA(FXStream& store,const FXColor *data,FXint width,FXint height);

}

#endif
