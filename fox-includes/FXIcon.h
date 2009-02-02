/********************************************************************************
*                                                                               *
*                               I c o n - O b j e c t                           *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXIcon.h 2127 2005-08-07 20:21:35Z lyle $                            *
********************************************************************************/
#ifndef FXICON_H
#define FXICON_H

#ifndef FXIMAGE_H
#include "FXImage.h"
#endif

namespace FX {

class FXDC;
class FXDCWindow;
class FXDrawable;
class FXTopWindow;


/**
* An Icon is an image with two additional server-side resources: a shape
* bitmap, which is used to mask those pixels where the background should
* be preserved during the drawing, and a etch bitmap, which is used to
* draw the icon when it is disabled.
*/
class FXAPI FXIcon : public FXImage {
  FXDECLARE(FXIcon)
  friend class FXDC;
  friend class FXWindow;
  friend class FXDCWindow;
  friend class FXDrawable;
  friend class FXTopWindow;
protected:
  FXID     shape;             // Shape pixmap
  FXID     etch;              // Etch pixmap
  FXColor  transp;            // Transparency color
protected:
  FXIcon(){}
  FXColor guesstransp();
private:
  FXIcon(const FXIcon&);
  FXIcon &operator=(const FXIcon&);
public:

  /**
  * Create an icon with an initial pixel buffer pix, a transparent color clr,
  * and options as in FXImage.  The transparent color is used to determine which
  * pixel values are transparent, i.e. need to be masked out in the absence of
  * a true alpha channel.
  * If the flag IMAGE_OPAQUE is passed, the shape and etch bitmaps are generated
  * as if the image is fully opaque, even if it has an alpha channel or transparancy
  * color.  The flag IMAGE_ALPHACOLOR is used to force a specific alpha color instead
  * of the alpha channel obtained from the image file.
  * Specifying IMAGE_ALPHAGUESS causes Icon to obtain the alpha color from the background
  * color of the image; it has the same effect as IMAGE_ALPHACOLOR in the sense that
  * the icon will be transparent for those colors matching the alpha color.
  */
  FXIcon(FXApp* a,const FXColor *pix=NULL,FXColor clr=0,FXuint opts=0,FXint w=1,FXint h=1);

  /**
  * Create the server side pixmap, the shape bitmap, and the etch bitmap, then
  * call render() to fill it with the pixel data from the client-side buffer.  After
  * the server-side pixmap and bitmaps have been created, the client-side pixel
  * buffer will be deleted unless IMAGE_KEEP has been specified. If the pixel buffer
  * is not owned, i.e. the flag IMAGE_OWNED is not set, the pixel buffer will not
  * be deleted; however the pixel buffer will be set to NULL.
  */
  virtual void create();

  /**
  * Detach the server side pixmap, shape bitmap, and etch bitmap from the Icon.
  * Afterwards, the Icon is left as if it never had a server-side resources.
  */
  virtual void detach();

  /**
  * Destroy the server-side pixmap and the shape bitmap and etch bitmap.
  * The client-side pixel buffer is not affected.
  */
  virtual void destroy();

  /**
  * Render the server-side pixmap, shape bitmap and etch bitmap for the icon
  * from the client-side pixel buffer.
  */
  virtual void render();

  /**
  * Resize both client-side and server-side representations (if any) to the
  * given width and height.  The new representations typically contain garbage
  * after this operation and need to be re-filled.
  */
  virtual void resize(FXint w,FXint h);

  /// Obtain transparency color
  FXColor getTransparentColor() const { return transp; }

  /// Change transparency color
  void setTransparentColor(FXColor color){ transp=color; }

  /// Destructor
  virtual ~FXIcon();
  };

}

#endif
