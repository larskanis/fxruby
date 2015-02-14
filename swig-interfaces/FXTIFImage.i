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

%rename("supported?") FXTIFImage::isSupported();

/// TIFF Image class
class FXTIFImage : public FXImage {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXTIFImage::fileExt);
      }

    static VALUE mimeType() {
      return to_ruby(FXTIFImage::mimeType);
      }

    /// True if format is supported
    static bool isSupported() { return FXTIFImage::supported; }
    }
public:

  /// Construct an image from memory stream formatted in TIFF format
  %extend {
    FXTIFImage(FXApp *a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbTIFImage(a,pix,opts,w,h);
      }
    }

  /// Set codec to save with
  void setCodec(FXuint c);

  /// Get codec setting
  FXuint getCodec() const;

  /// Destroy
  virtual ~FXTIFImage();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTIFImage)
DECLARE_FXID_VIRTUALS(FXTIFImage)
DECLARE_FXDRAWABLE_VIRTUALS(FXTIFImage)
DECLARE_FXIMAGE_VIRTUALS(FXTIFImage)


%inline %{
  /// Load a tiff from a stream
  VALUE fxloadTIF(FXStream& store){
    FXColor* data;
    FXint width;
    FXint height;
    FXushort codec;
    if(fxloadTIF(store,data,width,height,codec)){
      VALUE ary=rb_ary_new();
      rb_ary_push(ary,FXRbMakeColorArray(data,width,height));
      FXFREE(&data);
      rb_ary_push(ary,to_ruby(width));
      rb_ary_push(ary,to_ruby(height));
      rb_ary_push(ary,to_ruby(codec));
      return ary;
      }
    else{
      return Qnil;
      }
    }
%}

/// Save a tiff to a stream
bool fxsaveTIF(FXStream& store,const FXColor* PIXELS,FXint width,FXint height,FXushort codec);
