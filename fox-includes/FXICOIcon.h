/********************************************************************************
*                                                                               *
*                        I C O   I c o n   O b j e c t                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2006 by Janusz Ganczarski.   All Rights Reserved.          *
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
* $Id: FXICOIcon.h 2343 2006-02-12 20:26:26Z lyle $                         *
********************************************************************************/
#ifndef FXICOICON_H
#define FXICOICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/// ICO (Microsoft icon format) icon
class FXAPI FXICOIcon : public FXIcon {
  FXDECLARE(FXICOIcon)
protected:
  FXICOIcon(){}
private:
  FXICOIcon(const FXICOIcon&);
  FXICOIcon &operator=(const FXICOIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct icon from memory stream formatted in Microsoft icon format
  FXICOIcon(FXApp* a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in Microsoft icon format format
  virtual bool savePixels(FXStream& store) const;

  /// Load pixels from stream in Microsoft icon format format
  virtual bool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXICOIcon();
  };


#ifndef FXLOADICO
#define FXLOADICO

/**
* Check if stream contains a ICO, return TRUE if so.
*/
extern FXAPI bool fxcheckICO(FXStream& store);


/**
* Load an ICO (Microsoft icon format) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadICO(FXStream& store,FXColor*& data,FXint& width,FXint& height,FXint& xspot,FXint& yspot);


/**
* Save an ICO (Microsoft icon format) file to a stream.
* If no hot-spot given, save as an ICO instead of a CUR resource.
*/
extern FXAPI bool fxsaveICO(FXStream& store,const FXColor *data,FXint width,FXint height,FXint xspot=-1,FXint yspot=-1);

#endif

}

#endif
