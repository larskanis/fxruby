/********************************************************************************
*                                                                               *
*                          P N G   I m a g e   O b j e c t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXPNGIcon.h 2725 2007-11-16 16:57:54Z lyle $                         *
********************************************************************************/
#ifndef FXPNGICON_H
#define FXPNGICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/// Portable Network Graphics (PNG) Icon class
class FXAPI FXPNGIcon : public FXIcon {
  FXDECLARE(FXPNGIcon)
protected:
  FXPNGIcon(){}
private:
  FXPNGIcon(const FXPNGIcon&);
  FXPNGIcon &operator=(const FXPNGIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct an icon from memory stream formatted in PNG format
  FXPNGIcon(FXApp *a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// True if format is supported
  static const FXbool supported;

  /// Save pixels into stream in PNG format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in PNG format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXPNGIcon();
  };


/**
* Check if stream contains a PNG, return true if so.
*/
extern FXAPI FXbool fxcheckPNG(FXStream& store);


/**
* Load an PNG (Portable Network Graphics) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadPNG(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an PNG (Portable Network Graphics) file to a stream.
*/
extern FXAPI FXbool fxsavePNG(FXStream& store,const FXColor* data,FXint width,FXint height);

}

#endif
