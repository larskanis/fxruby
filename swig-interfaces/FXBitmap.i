/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

// Image rendering hints
enum {
  BITMAP_KEEP       = 0x00000001,       // Keep pixel data in client
  BITMAP_OWNED      = 0x00000002,       // Pixel data is owned by image
  BITMAP_SHMI       = 0x00000020,       // Using shared memory image
  BITMAP_SHMP       = 0x00000040        // Using shared memory pixmap
  };



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
class FXBitmap : public FXDrawable {
public:
  %extend {
     /**
      * Create a bitmap.  If a client-side pixel buffer has been specified,
      * the bitmap does not own the pixel buffer unless the BITMAP_OWNED flag is
      * set.  If the BITMAP_OWNED flag is set but a NULL pixel buffer is
      * passed, a pixel buffer will be automatically created and will be owned
      * by the bitmap. The flags BITMAP_SHMI and BITMAP_SHMP may be specified for
      * large bitmaps to instruct render() to use shared memory to communicate
      * with the server.
      */
    FXBitmap(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbBitmap(a,pix,opts,w,h);
      }
    }

  /// To get to the pixel data
  FXuchar* getData() const;

  /// To get to the option flags
  FXuint getOptions() const;

  /// Change options
  void setOptions(FXuint opts);

  /// Get pixel at x,y
  FXbool getPixel(FXint x,FXint y) const;

  /// Change pixel at x,y
  void setPixel(FXint x,FXint y,FXbool color);

  /// Cleanup
  virtual ~FXBitmap();
  };


DECLARE_FXOBJECT_VIRTUALS(FXBitmap)
DECLARE_FXID_VIRTUALS(FXBitmap)
DECLARE_FXDRAWABLE_VIRTUALS(FXBitmap)
DECLARE_FXBITMAP_VIRTUALS(FXBitmap)

