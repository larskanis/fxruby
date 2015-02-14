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

%rename("supported?") FXJPGIcon::isSupported();

/// JPG Icon class
class FXJPGIcon : public FXIcon {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXJPGIcon::fileExt);
      }

    static VALUE mimeType() {
      return to_ruby(FXJPGIcon::mimeType);
      }

    /// True if format is supported
    static bool isSupported() { return FXJPGIcon::supported; }
    }
public:
  %extend {
    /// Construct an icon from memory stream formatted in JPG format
    FXJPGIcon(FXApp *a,const void *pix=NULL,FXColor clr=0,FXuint opts=0,FXint w=1,FXint h=1,FXint q=75){
      return new FXRbJPGIcon(a,pix,clr,opts,w,h,q);
      }
    }

  /// Set image quality to save with
  void setQuality(FXint q);

  /// Get image quality setting
  FXint getQuality() const;

  /// Destroy
  virtual ~FXJPGIcon();
  };


DECLARE_FXOBJECT_VIRTUALS(FXJPGIcon)
DECLARE_FXID_VIRTUALS(FXJPGIcon)
DECLARE_FXDRAWABLE_VIRTUALS(FXJPGIcon)
DECLARE_FXIMAGE_VIRTUALS(FXJPGIcon)

%inline %{
  /**
   * Load an JPEG (Joint Photographics Experts Group) file from a stream.
   * Upon successful return, the pixel array and size are returned.
   * If an error occurred, the pixel array is set to NULL.
   */
  VALUE fxloadJPG(FXStream& store){
    FXColor* data;
    FXint width,height,quality;
    if(fxloadJPG(store,data,width,height,quality)){
      VALUE ary=rb_ary_new();
      rb_ary_push(ary,FXRbMakeColorArray(data,width,height));
      FXFREE(&data);
      rb_ary_push(ary,to_ruby(width));
      rb_ary_push(ary,to_ruby(height));
      rb_ary_push(ary,to_ruby(quality));
      return ary;
      }
    else{
      return Qnil;
      }
    }
%}

/**
 * Save an JPEG (Joint Photographics Experts Group) file to a stream.
 */
bool fxsaveJPG(FXStream& store,const FXColor *PIXELS,FXint width,FXint height,FXint quality);

/**
 * Check if stream contains a JPEG image, return TRUE if so.
 */
bool fxcheckJPG(FXStream& store);

