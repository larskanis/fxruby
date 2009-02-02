/********************************************************************************
*                                                                               *
*                        X P M   I c o n   O b j e c t                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXXPMIcon.h 2747 2007-11-16 22:31:28Z lyle $                         *
********************************************************************************/
#ifndef FXXPMICON_H
#define FXXPMICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/// X Pixmap icon
class FXAPI FXXPMIcon : public FXIcon {
  FXDECLARE(FXXPMIcon)
protected:
  FXXPMIcon(){}
private:
  FXXPMIcon(const FXXPMIcon&);
  FXXPMIcon &operator=(const FXXPMIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct icon from compiled-in X Pixmap format
  FXXPMIcon(FXApp* a,const FXchar **pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in X Pixmap format
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixels from stream in X Pixmap format
  virtual FXbool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXXPMIcon();
  };


#ifndef FXLOADXPM
#define FXLOADXPM

/**
* Check if stream contains a XPM, return TRUE if so.
*/
extern FXAPI FXbool fxcheckXPM(FXStream& store);


/**
* Load an XPM (X Pixmap) from array of strings.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadXPM(const FXchar **pix,FXColor*& data,FXint& width,FXint& height);


/**
* Load an XPM (X Pixmap) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI FXbool fxloadXPM(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an XPM (X Pixmap) file to a stream.
*/
extern FXAPI FXbool fxsaveXPM(FXStream& store,const FXColor *data,FXint width,FXint height,FXbool fast=true);

#endif

}

#endif
