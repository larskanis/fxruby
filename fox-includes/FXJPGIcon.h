/********************************************************************************
*                                                                               *
*                         J P E G   I c o n   O b j e c t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2006 by David Tyree.   All Rights Reserved.                *
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
* $Id: FXJPGIcon.h 2343 2006-02-12 20:26:26Z lyle $                         *
********************************************************************************/
#ifndef FXJPGICON_H
#define FXJPGICON_H

#ifndef FXICON_H
#include "FXIcon.h"
#endif

namespace FX {


/// JPEG Icon class
class FXAPI FXJPGIcon : public FXIcon {
  FXDECLARE(FXJPGIcon)
protected:
  FXint quality;
protected:
  FXJPGIcon(){}
private:
  FXJPGIcon(const FXJPGIcon&);
  FXJPGIcon &operator=(const FXJPGIcon&);
public:
  static const FXchar fileExt[];
  static const FXchar mimeType[];
public:

  /// Construct an icon from memory stream formatted in JPEG format
  FXJPGIcon(FXApp *a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1,FXint q=75);

  /// True if format is supported
  static const bool supported;

  /// Set image quality to save with
  void setQuality(FXint q){ quality=q; }

  /// Get image quality setting
  FXint getQuality() const { return quality; }

  /// Save pixels into stream in JPEG format
  virtual bool savePixels(FXStream& store) const;

  /// Load pixels from stream in JPEG format
  virtual bool loadPixels(FXStream& store);

  /// Destroy
  virtual ~FXJPGIcon();
  };



/**
* Check if stream contains a JPG, return TRUE if so.
*/
extern FXAPI bool fxcheckJPG(FXStream& store);


/**
* Load an JPEG (Joint Photographics Experts Group) file from a stream.
* Upon successful return, the pixel array and size are returned.
* If an error occurred, the pixel array is set to NULL.
*/
extern FXAPI bool fxloadJPG(FXStream& store,FXColor*& data,FXint& width,FXint& height,FXint& quality);


/**
* Save an JPEG (Joint Photographics Experts Group) file to a stream.
*/
extern FXAPI bool fxsaveJPG(FXStream& store,const FXColor* data,FXint width,FXint height,FXint quality);

}

#endif
