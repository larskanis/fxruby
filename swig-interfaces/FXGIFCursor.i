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

%apply const FXColor *PIXELS { const FXColor *data };

/// GIF Cursor class
class FXGIFCursor : public FXCursor {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXGIFCursor::fileExt);
      }
    }
public:
  %extend {
    /**
    * Construct a cursor from memory stream in Compuserve GIF format.
    * Hot spot may be specified using hx and hy parameters, since the GIF
    * format does not specify a hot spot. The image must be smaller than
    * 32x32 pixels.
    */
    FXGIFCursor(FXApp* a,const void* pix,FXint hx=-1,FXint hy=-1){
      return new FXRbGIFCursor(a,pix,hx,hy);
      }
    }

  /// Destroy
  virtual ~FXGIFCursor(){}
  };

DECLARE_FXOBJECT_VIRTUALS(FXGIFCursor)
DECLARE_FXID_VIRTUALS(FXGIFCursor)
DECLARE_FXCURSOR_VIRTUALS(FXGIFCursor)


/// Save a gif file to a stream
bool fxsaveGIF(FXStream& store,const FXColor *data,FXint width,FXint height,FXbool fast=TRUE);

%inline %{
  /**
   * Load an GIF (Graphics Interchange Format) file from a stream.
   * Upon successful return, the pixel array and size are returned.
   * If an error occurred, the pixel array is set to NULL.
   */
  VALUE fxloadGIF(FXStream& store){
    FXColor* data;
    FXint width;
    FXint height;
    if(fxloadGIF(store,data,width,height)){
      VALUE ary=rb_ary_new();
      rb_ary_push(ary,FXRbMakeColorArray(data,width,height));
      FXFREE(&data);
      rb_ary_push(ary,to_ruby(width));
      rb_ary_push(ary,to_ruby(height));
      return ary;
      }
    else{
      return Qnil;
      }
    }
%}

/**
 * Check if stream contains a GIF, return TRUE if so.
 */
bool fxcheckGIF(FXStream& store);

