/********************************************************************************
*                                                                               *
*                        G I F   I c o n   O b j e c t                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGIFIcon.h 2744 2007-11-16 22:16:04Z lyle $                         *
********************************************************************************/
#ifndef FXGIFICON_H
#define FXGIFICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {

/// GIF Icon class
class FXAPI FXGIFIcon : public FXIcon {
  FXDECLARE(FXGIFIcon)
protected:
  FXGIFIcon(){}
private:
  FXGIFIcon(const FXGIFIcon&);
  FXGIFIcon &operator=(const FXGIFIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct an icon from memory stream formatted as GIF format
  FXGIFIcon(FXApp* a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in GIF format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in GIF format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXGIFIcon();
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
