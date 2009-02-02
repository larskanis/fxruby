/********************************************************************************
*                                                                               *
*                             B i t m a p    O b j e c t                        *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXBitmap.h 2335 2006-01-28 02:33:03Z lyle $                          *
********************************************************************************/
#ifndef FXBITMAP_H
#define FXBITMAP_H

#ifndef FXDRAWABLE_H
#include "FXDrawable.h"
#endif

namespace FX {

// Image rendering hints
enum {
  BITMAP_KEEP       = 0x00000001,       // Keep pixel data in client
  BITMAP_OWNED      = 0x00000002,       // Pixel data is owned by image
  BITMAP_SHMI       = 0x00000020,       // Using shared memory image
  BITMAP_SHMP       = 0x00000040        // Using shared memory pixmap
  };


// Forward declarations
class FXDC;
class FXDCWindow;


/**
* A Bitmap is a rectangular array of pixels.  It supports two representations
* of these pixels: a client-side pixel buffer, and a server-side pixmap which
* is stored in an organization directly compatible with the screen, for fast
* drawing onto the device.
* The server-side representation is not directly accessible from the current
* process as it lives in the process of the X Server or GDI.
* The client-side pixel array is of size height x (width+7)/8 bytes, in other
* words 8 pixels packed into a single byte, starting at bit 0 on the left.
*/
class FXAPI FXBitmap : public FXDrawable {
  FXDECLARE(FXBitmap)
  friend class FXDC;
  friend class FXDCWindow;
private:
#ifdef WIN32
  virtual FXID GetDC() const;
  virtual int ReleaseDC(FXID) const;
#endif
protected:
  FXuchar *data;        // Pixel data
  FXint    bytewidth;   // Number of bytes across
  FXuint   options;     // Options
protected:
  FXBitmap();
private:
  FXBitmap(const FXBitmap&);
  FXBitmap &operator=(const FXBitmap&);
public:

  /**
  * Create a bitmap.  If a client-side pixel buffer has been specified,
  * the bitmap does not own the pixel buffer unless the BITMAP_OWNED flag is
  * set.  If the BITMAP_OWNED flag is set but a NULL pixel buffer is
  * passed, a pixel buffer will be automatically created and will be owned
  * by the bitmap. The flags BITMAP_SHMI and BITMAP_SHMP may be specified for
  * large bitmaps to instruct render() to use shared memory to communicate
  * with the server.
  */
  FXBitmap(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);

  /// Change options
  void setOptions(FXuint opts);

  /// To get to the option flags
  FXuint getOptions() const { return options; }

  /**
  * Populate the bitmap with new pixel data of the same size; it will assume
  * ownership of the pixel data if image BITMAP_OWNED option is passed.
  * The server-side representation of the image, if it exists, is not updated.
  * This can be done by calling render().
  */
  virtual void setData(FXuchar *pix,FXuint opts=0);

  /**
  * Populate the bitmap with new pixel data of a new size; it will assume ownership
  * of the pixel data if image BITMAP_OWNED option is passed.  The size of the server-
  * side representation of the image, if it exists, is adjusted but the contents are
  * not updated yet. This can be done by calling render().
  */
  virtual void setData(FXuchar *pix,FXuint opts,FXint w,FXint h);

  /// To get to the pixel data
  FXuchar* getData() const { return data; }

  /// Get pixel at x,y
  FXbool getPixel(FXint x,FXint y) const { return (FXbool)((data[y*bytewidth+(x>>3)]>>(x&7))&1); }

  /// Change pixel at x,y
  void setPixel(FXint x,FXint y,FXbool color){ color ? data[y*bytewidth+(x>>3)]|=(1<<(x&7)) : data[y*bytewidth+(x>>3)]&=~(1<<(x&7)); }

  /**
  * Create the server side pixmap, then call render() to fill it with the
  * pixel data from the client-side buffer.  After the server-side image has
  * been created, the client-side pixel buffer will be deleted unless
  * BITMAP_KEEP has been specified.  If the pixel buffer is not owned, i.e.
  * the flag BITMAP_OWNED is not set, the pixel buffer will not be deleted.
  */
  virtual void create();

  /**
  * Detach the server side pixmap from the Bitmap.
  * Afterwards, the Bitmap is left as if it never had a server-side resources.
  */
  virtual void detach();

  /**
  * Destroy the server-side pixmap.
  * The client-side pixel buffer is not affected.
  */
  virtual void destroy();

  /**
  * Retrieves pixels from the server-side bitmap.
  */
  virtual void restore();

  /**
  * Render the server-side representation of the bitmap from client-side
  * pixels.
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
  virtual void scale(FXint w,FXint h);

  /// Mirror bitmap horizontally and/or vertically
  virtual void mirror(FXbool horizontal,FXbool vertical);

  /// Rotate bitmap by degrees ccw
  virtual void rotate(FXint degrees);

  /**
  * Crop bitmap to given rectangle; this calls resize() to adjust the client
  * and server side representations.  The new bitmap may be smaller or larger
  * than the old one; blank areas are filled with color. There must be at
  * least one pixel of overlap between the old and the new bitmap.
  */
  virtual void crop(FXint x,FXint y,FXint w,FXint h,FXbool color=0);

  /// Fill bitmap with uniform value
  virtual void fill(FXbool color);

  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);

  /// Save pixel data only
  virtual bool savePixels(FXStream& store) const;

  /// Load pixel data only
  virtual bool loadPixels(FXStream& store);

  /// Cleanup
  virtual ~FXBitmap();
  };

}

#endif

