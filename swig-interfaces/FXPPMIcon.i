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


/// Portable Pixmap icon
class FXPPMIcon : public FXIcon {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXPPMIcon::fileExt);
      }

    static VALUE mimeType() {
      return to_ruby(FXPPMIcon::mimeType);
      }
    }
public:
  %extend {
    /// Construct icon from memory stream formatted in Portable Pixmap format
    FXPPMIcon(FXApp* a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbPPMIcon(a,pix,clr,opts,w,h);
      }
    }

  /// Destroy icon
  virtual ~FXPPMIcon();
  };


DECLARE_FXOBJECT_VIRTUALS(FXPPMIcon)
DECLARE_FXID_VIRTUALS(FXPPMIcon)
DECLARE_FXDRAWABLE_VIRTUALS(FXPPMIcon)
DECLARE_FXIMAGE_VIRTUALS(FXPPMIcon)


%inline %{
  /**
   * Load an PPM (Portable Pixmap Format) file from a stream.
   * Upon successful return, the pixel array and size are returned.
   * If an error occurred, the pixel array is set to NULL.
   */
  VALUE fxloadPPM(FXStream& store){
    FXColor* data;
    FXint width;
    FXint height;
    if(fxloadPPM(store,data,width,height)){
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
* Save an PPM (Portable Pixmap Format) file to a stream.
*/
bool fxsavePPM(FXStream& store,const FXColor *PIXELS,FXint width,FXint height);

/**
 * Check if stream contains a bitmap, return TRUE if so.
 */
bool fxcheckPPM(FXStream& store);

