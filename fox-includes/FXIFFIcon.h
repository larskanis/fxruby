/********************************************************************************
*                                                                               *
*                        I F F   I c o n   O b j e c t                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXIFFIcon.h 2401 2006-04-27 00:46:49Z lyle $                          *
********************************************************************************/
#ifndef FXIFFICON_H
#define FXIFFICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/**
* The IFF Icon provides support for the EA/Amiga Image File Format.
*/
class FXAPI FXIFFIcon : public FXIcon {
  FXDECLARE(FXIFFIcon)
protected:
  FXIFFIcon(){}
private:
  FXIFFIcon(const FXIFFIcon&);
  FXIFFIcon &operator=(const FXIFFIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct an icon from memory stream formatted as IFF format
  FXIFFIcon(FXApp* a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in IFF format
  virtual bool savePixels(FXStream& store) const;

  /// Load pixels from stream in IFF format
  virtual bool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXIFFIcon();
  };



#ifndef FXLOADIFF
#define FXLOADIFF

/**
* Check if stream contains a IFF, return TRUE if so.
*/
extern FXAPI bool fxcheckIFF(FXStream& store);


/**
* Load an IFF (EA Image File Format) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadIFF(FXStream& store,FXColor*& data,FXint& width,FXint& height);


#endif

}

#endif
