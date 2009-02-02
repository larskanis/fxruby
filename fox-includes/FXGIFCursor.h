/********************************************************************************
*                                                                               *
*                        G I F   C u r so r   O b j e c t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2005 by Daniel Gehriger.   All Rights Reserved.            *
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
* $Id: FXGIFCursor.h 2336 2006-02-04 15:20:33Z lyle $                       *
********************************************************************************/
#ifndef FXGIFCURSOR_H
#define FXGIFCURSOR_H

#ifndef FXCURSOR_H
#include "FXCursor.h"
#endif

namespace FX {


/// GIF Cursor class
class FXAPI FXGIFCursor : public FXCursor {
  FXDECLARE(FXGIFCursor)
protected:
  FXGIFCursor(){}
private:
  FXGIFCursor(const FXGIFCursor&);
  FXGIFCursor &operator=(const FXGIFCursor&);
public:
  static const FXchar fileExt[];
public:

  /**
  * Construct a cursor from memory stream in Compuserve GIF format.
  * Hot spot may be specified using hx and hy parameters, since the GIF
  * format does not specify a hot spot. The image must be smaller than
  * 32x32 pixels.
  */
  FXGIFCursor(FXApp* a,const void* pix,FXint hx=0,FXint hy=0);

  /// Save pixel data only, in GIF format
  virtual bool savePixels(FXStream& store) const;

  /// Load pixel data only, in GIF format
  virtual bool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXGIFCursor(){}
  };


#ifndef FXLOADGIF
#define FXLOADGIF

/**
* Check if stream contains a GIF, return TRUE if so.
*/
extern FXAPI bool fxcheckGIF(FXStream& store);


/**
* Load an GIF (Graphics Interchange Format) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadGIF(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an GIF (Graphics Interchange Format) file to a stream.
*/
extern FXAPI bool fxsaveGIF(FXStream& store,const FXColor *data,FXint width,FXint height,bool fast=true);

#endif

}

#endif
