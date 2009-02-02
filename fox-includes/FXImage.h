/********************************************************************************
*                                                                               *
*                             I m a g e    O b j e c t                          *
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
* $Id: FXImage.h 2336 2006-02-04 15:20:33Z lyle $                           *
********************************************************************************/
#ifndef FXIMAGE_H
#define FXIMAGE_H

#ifndef FXDRAWABLE_H
#include "FXDrawable.h"
#endif

namespace FX {


/// Image rendering hints
enum {
  IMAGE_KEEP       = 0x00000001,      /// Keep pixel data in client
  IMAGE_OWNED      = 0x00000002,      /// Pixel data is owned by image
  IMAGE_DITHER     = 0,               /// Dither image to look better
  IMAGE_NEAREST    = 0x00000004,      /// Turn off dithering and map to nearest color
  IMAGE_OPAQUE     = 0x00000008,      /// Force opaque background
  IMAGE_ALPHACOLOR = 0x00000010,      /// Override transparancy color
  IMAGE_SHMI       = 0x00000020,      /// Using shared memory image
  IMAGE_SHMP       = 0x00000040,      /// Using shared memory pixmap
  IMAGE_ALPHAGUESS = 0x00000080       /// Guess transparency color from corners
  };


class FXDC;
class FXDCWindow;


/**
* An Image is a rectangular array of pixels.  It supports two representations
* of these pixels: a client-side pixel buffer which is stored as an array of
* FXColor, and a server-side pixmap which is stored in an organization directly
* compatible with the screen, for fast drawing onto the device.
* The server-side representation is not directly accessible from the current
* process as it lives in the process of the X Server or GDI.
*/
class FXAPI FXImage : public FXDrawable {
  FXDECLARE(FXImage)
  friend class FXDC;
  friend class FXDCWindow;
protected:
  FXColor *data;        // Pixel data
  FXuint   options;     // Options
private:
#ifdef WIN32
  virtual FXID GetDC() const;
  virtual int ReleaseDC(FXID) const;
#endif
#ifndef WIN32
  void render_true_32(void *xim,FXuchar *img);
  void render_true_24(void *xim,FXuchar *img);
  void render_true_16_fast(void *xim,FXuchar *img);
  void render_true_16_dither(void *xim,FXuchar *img);
  void render_true_8_fast(void *xim,FXuchar *img);
  void render_true_8_dither(void *xim,FXuchar *img);
  void render_true_N_fast(void *xim,FXuchar *img);
  void render_true_N_dither(void *xim,FXuchar *img);
  void render_index_4_fast(void *xim,FXuchar *img);
  void render_index_4_dither(void *xim,FXuchar *img);
  void render_index_8_fast(void *xim,FXuchar *img);
  void render_index_8_dither(void *xim,FXuchar *img);
  void render_index_N_fast(void *xim,FXuchar *img);
  void render_index_N_dither(void *xim,FXuchar *img);
  void render_gray_8_fast(void *xim,FXuchar *img);
  void render_gray_8_dither(void *xim,FXuchar *img);
  void render_gray_N_fast(void *xim,FXuchar *img);
  void render_gray_N_dither(void *xim,FXuchar *img);
  void render_mono_1_fast(void *xim,FXuchar *img);
  void render_mono_1_dither(void *xim,FXuchar *img);
#endif
protected:
  FXImage();
private:
  FXImage(const FXImage&);
  FXImage &operator=(const FXImage&);
public:

  /**
  * Create an image.  If a client-side pixel buffer has been specified,
  * the image does not own the pixel buffer unless the IMAGE_OWNED flag is
  * set.  If the IMAGE_OWNED flag is set but a NULL pixel buffer is
  * passed, a pixel buffer will be automatically created and will be owned
  * by the image. The flags IMAGE_SHMI and IMAGE_SHMP may be specified for
  * large images to instruct render() to use shared memory to communicate
  * with the server.
  */
  FXImage(FXApp* a,const FXColor *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// Change options
  void setOptions(FXuint opts);

  /// To get to the option flags
  FXuint getOptions() const { return options; }

  /**
  * Populate the image with new pixel data of the same size; it will assume
  * ownership of the pixel data if image IMAGE_OWNED option is passed.
  * The server-side representation of the image, if it exists, is not updated.
  * This can be done by calling render().
  */
  virtual void setData(FXColor *pix,FXuint opts=0);

  /**
  * Populate the image with new pixel data of a new size; it will assume ownership
  * of the pixel data if image IMAGE_OWNED option is passed.  The size of the server-
  * side representation of the image, if it exists, is adjusted but the contents are
  * not updated yet. This can be done by calling render().
  */
  virtual void setData(FXColor *pix,FXuint opts,FXint w,FXint h);

  /// Return pointer to the pixel data of the image
  FXColor* getData() const { return data; }

  /// Get pixel at x,y
  FXColor getPixel(FXint x,FXint y) const { return data[y*width+x]; }

  /// Change pixel at x,y
  void setPixel(FXint x,FXint y,FXColor color){ data[y*width+x]=color; }

  /// Scan the image and return false if fully opaque
  bool hasAlpha() const;

  /**
  * Create the server side pixmap, then call render() to fill it with the
  * pixel data from the client-side buffer.  After the server-side image has
  * been created, the client-side pixel buffer will be deleted unless
  * IMAGE_KEEP has been specified.  If the pixel buffer is not owned, i.e.
  * the flag IMAGE_OWNED is not set, the pixel buffer will not be deleted,
  * however the pixel buffer will be set to NULL.
  */
  virtual void create();

  /**
  * Detach the server side pixmap from the Image.
  * Afterwards, the Image is left as if it never had a server-side resources.
  */
  virtual void detach();

  /**
  * Destroy the server-side pixmap.
  * The client-side pixel buffer is not affected.
  */
  virtual void destroy();

  /**
  * Retrieves pixels from the server-side image.  For example, to make
  * screen snapshots, or to retrieve an image after it has been drawn
  * into by various means.
  */
  virtual void restore();

  /**
  * Render the server-side representation of the image from client-side
  * pixels.  Normally, IMAGE_DITHER is used which causes the server-side
  * representation to be rendered using a 16x16 ordered dither if necessary;
  * however if IMAGE_NEAREST is used a faster (but uglier-looking), nearest
  * neighbor algorithm is used.
  */
  virtual void render();

  /**
  * Release the client-side pixels buffer, free it if it was owned.
  * If it is not owned, the image just forgets about the buffer.
  */
  virtual void release();

  /**
  * Resize both client-side and server-side representations (if any) to the
  * given width and height.  The new representations typically contain garbage
  * after this operation and need to be re-filled.
  */
  virtual void resize(FXint w,FXint h);

  /**
  * Rescale pixels image to the specified width and height; this calls
  * resize() to adjust the client and server side representations.
  */
  virtual void scale(FXint w,FXint h,FXint quality=0);

  /// Mirror image horizontally and/or vertically
  virtual void mirror(bool horizontal,bool vertical);

  /**
  * Rotate image by degrees ccw; this calls resize() to adjust the client
  * and server side representations if necessary.
  */
  virtual void rotate(FXint degrees);

  /**
  * Crop image to given rectangle; this calls resize() to adjust the client
  * and server side representations.  The new image may be smaller or larger
  * than the old one; blank areas are filled with color. There must be at
  * least one pixel of overlap between the old and the new image.
  */
  virtual void crop(FXint x,FXint y,FXint w,FXint h,FXColor color=0);

  /// Fill image with uniform color
  virtual void fill(FXColor color);

  /// Fade image to uniform color
  virtual void fade(FXColor color,FXint factor=255);

  /**
  * Shear image horizontally; the number of pixels is equal to the
  * shear parameter times 256.  The area outside the image is filled
  * with transparent black, unless another color is specified.
  */
  virtual void xshear(FXint shear,FXColor clr=0);

  /**
  * Shear image vertically; the number of pixels is equal to the
  * shear parameter times 256.  The area outside the image is filled
  * with transparent black, unless another color is specified.
  */
  virtual void yshear(FXint shear,FXColor clr=0);

  /// Fill horizontal gradient
  virtual void hgradient(FXColor left,FXColor right);

  /// Fill vertical gradient
  virtual void vgradient(FXColor top,FXColor bottom);

  /// Fill with gradient
  virtual void gradient(FXColor topleft,FXColor topright,FXColor bottomleft,FXColor bottomright);

  /// Blend image over uniform color
  virtual void blend(FXColor color);

  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);

  /// Save pixel data only
  virtual bool savePixels(FXStream& store) const;

  /// Load pixel data only
  virtual bool loadPixels(FXStream& store);

  /// Destructor
  virtual ~FXImage();
  };

}

#endif
