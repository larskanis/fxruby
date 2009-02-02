/********************************************************************************
*                                                                               *
*                            X P M   I m a g e   O b j e c t                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXXPMImage.h 2343 2006-02-12 20:26:26Z lyle $                        *
********************************************************************************/
#ifndef FXXPMIMAGE_H
#define FXXPMIMAGE_H

#ifndef FXIMAGE_H
#include "FXImage.h"
#endif

namespace FX {


/// X Pixmap image
class FXAPI FXXPMImage : public FXImage {
  FXDECLARE(FXXPMImage)
protected:
  FXXPMImage(){}
private:
  FXXPMImage(const FXXPMImage&);
  FXXPMImage &operator=(const FXXPMImage&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct image from compiled-in X Pixmap format
  FXXPMImage(FXApp* a,const FXchar **pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in X Pixmap format
  virtual bool savePixels(FXStream& store) const;

  /// Load pixels from stream in X Pixmap format
  virtual bool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXXPMImage();
  };


#ifndef FXLOADXPM
#define FXLOADXPM

/**
* Check if stream contains a XPM, return TRUE if so.
*/
extern FXAPI bool fxcheckXPM(FXStream& store);


/**
* Load an XPM (X Pixmap) from array of strings.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadXPM(const FXchar **pix,FXColor*& data,FXint& width,FXint& height);


/**
* Load an XPM (X Pixmap) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadXPM(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an XPM (X Pixmap) file to a stream.
*/
extern FXAPI bool fxsaveXPM(FXStream& store,const FXColor *data,FXint width,FXint height,bool fast=true);

#endif

}

#endif
