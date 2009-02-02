/********************************************************************************
*                                                                               *
*                            P C X   I m a g e   O b j e c t                    *
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
* $Id: FXPCXImage.h 2343 2006-02-12 20:26:26Z lyle $                        *
********************************************************************************/
#ifndef FXPCXIMAGE_H
#define FXPCXIMAGE_H

#ifndef FXIMAGE_H
#include "FXImage.h"
#endif

namespace FX {

///  PCX graphics file
class FXAPI FXPCXImage : public FXImage {
  FXDECLARE(FXPCXImage)
protected:
  FXPCXImage(){}
private:
  FXPCXImage(const FXPCXImage&);
  FXPCXImage &operator=(const FXPCXImage&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct image from memory stream formatted in PCX file
  FXPCXImage(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// Save pixels into stream in PCX file
  virtual bool savePixels(FXStream& store) const;

  /// Load pixels from stream in  bitmap format
  virtual bool loadPixels(FXStream& store);

  /// Destroy icon
  virtual ~FXPCXImage();
  };


/**
* Check if stream contains a PCX, return TRUE if so.
*/
extern FXAPI bool fxcheckPCX(FXStream& store);


/**
* Load an PCX (PC Paintbrush) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadPCX(FXStream& store,FXColor*& data,FXint& width,FXint& height);


/**
* Save an PCX (PC Paintbrush) file to a stream.
*/
extern FXAPI bool fxsavePCX(FXStream& store,const FXColor *data,FXint width,FXint height);

}

#endif
