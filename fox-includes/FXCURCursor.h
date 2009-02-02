/********************************************************************************
*                                                                               *
*                        C U R   C u r s o r    O b j e c t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2005 by Sander Jansen.   All Rights Reserved.              *
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
* $Id: FXCURCursor.h 2335 2006-01-28 02:33:03Z lyle $                       *
********************************************************************************/
#ifndef FXCURCURSOR_H
#define FXCURCURSOR_H

#ifndef FXCURSOR_H
#include "FXCursor.h"
#endif

namespace FX {

/// CUR Cursor class
class FXAPI FXCURCursor : public FXCursor {
  FXDECLARE(FXCURCursor)
protected:
  FXCURCursor(){}
private:
  FXCURCursor(const FXCURCursor&);
  FXCURCursor &operator=(const FXCURCursor&);
public:
  static const FXchar fileExt[];
public:

  /**
  * Construct a cursor from memory stream in Microsoft CUR format.
  * The image is limited to 32x32 pixels.
  */
  FXCURCursor(FXApp* a,const void* pix);

  /// Save pixel data only, in CUR format
  virtual bool savePixels(FXStream& store) const;

  /// Load pixel data only, in CUR format
  virtual bool loadPixels(FXStream& store);

  /// Destructor
  virtual ~FXCURCursor();
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
