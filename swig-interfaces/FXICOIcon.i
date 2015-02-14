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


/// ICO icon
class FXICOIcon : public FXIcon {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXICOIcon::fileExt);
      }
    static VALUE mimeType() {
      return to_ruby(FXICOIcon::mimeType);
      }
    }
public:
  %extend {
    /// Construct icon from memory stream formatted in Microsoft ICO format
    FXICOIcon(FXApp* a,const void *pix=NULL,FXColor clr=0,FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbICOIcon(a,pix,clr,opts,w,h);
      }
    }

  /// Destroy icon
  virtual ~FXICOIcon();
  };


DECLARE_FXOBJECT_VIRTUALS(FXICOIcon)
DECLARE_FXID_VIRTUALS(FXICOIcon)
DECLARE_FXDRAWABLE_VIRTUALS(FXICOIcon)
DECLARE_FXIMAGE_VIRTUALS(FXICOIcon)


%inline %{
/**
 * Load an ICO (Microsoft icon format) file from a stream.
 * Upon successful return, the pixel array and size are returned.
 * If an error occurred, the pixel array is set to NULL.
 */
VALUE fxloadICO(FXStream& store){
  FXColor* data;
  FXint width;
  FXint height;
  FXint xspot;
  FXint yspot;
  if(fxloadICO(store,data,width,height,xspot,yspot)){
    VALUE ary=rb_ary_new();
    rb_ary_push(ary,FXRbMakeColorArray(data,width,height));
    FXFREE(&data);
    rb_ary_push(ary,to_ruby(width));
    rb_ary_push(ary,to_ruby(height));
    rb_ary_push(ary,to_ruby(xspot));
    rb_ary_push(ary,to_ruby(yspot));
    return ary;
    }
  else{
    return Qnil;
    }
  }
%}


/// Save a ICO file to a stream
bool fxsaveICO(FXStream& store,const FXColor *PIXELS,FXint width,FXint height,FXint xspot=-1,FXint yspot=-1);

/**
 * Check if stream contains a ICO, return TRUE if so.
 */
bool fxcheckICO(FXStream& store);

