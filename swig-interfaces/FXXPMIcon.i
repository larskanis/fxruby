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


/// X Pixmap icon
class FXXPMIcon : public FXIcon {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXXPMIcon::fileExt);
      }

    static VALUE mimeType() {
      return to_ruby(FXXPMIcon::mimeType);
      }
    }
public:

  /// Construct icon from compiled-in X Pixmap format
  %extend {
    FXXPMIcon(FXApp* a,const FXchar **pix=NULL,FXColor clr=0,FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbXPMIcon(a,pix,clr,opts,w,h);
      }
    }

  /// Destroy icon
  virtual ~FXXPMIcon();
  };


DECLARE_FXOBJECT_VIRTUALS(FXXPMIcon)
DECLARE_FXID_VIRTUALS(FXXPMIcon)
DECLARE_FXDRAWABLE_VIRTUALS(FXXPMIcon)
DECLARE_FXIMAGE_VIRTUALS(FXXPMIcon)


%inline %{
  /// Load an X Pixmap file from a stream
  VALUE fxloadXPM(FXStream& store){
    FXColor* data;
    FXint width;
    FXint height;
    if(fxloadXPM(store,data,width,height)){
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

  /// Load an X Pixmap file from an array of strings
  VALUE fxloadXPM(VALUE strArray){
    long len,i;
    VALUE str;
    const FXchar **pix;
    FXColor* data;
    FXint width;
    FXint height;
    VALUE ary=Qnil;

    // Confirm that the input is an array of strings
    Check_Type(strArray,T_ARRAY);
    len=RARRAY_LEN(strArray);
    for(i=0; i<len; i++){
      str=rb_ary_entry(strArray,i);
      Check_Type(str,T_STRING);
      }

    // Convert to a C array
    if(FXMALLOC(&pix,FXchar*,len)){
      for(i=0; i<len; i++){
        str=rb_ary_entry(strArray,i);
	pix[i]=StringValuePtr(str);
	}
      if(fxloadXPM(pix,data,width,height)){
	ary=rb_ary_new();
	rb_ary_push(ary,FXRbMakeColorArray(data,width,height));
	FXFREE(&data);
	rb_ary_push(ary,to_ruby(width));
	rb_ary_push(ary,to_ruby(height));
	}
      FXFREE(&pix);
      }
    return ary;
    }
%}


/// Save an X Pixmap file to a stream
bool fxsaveXPM(FXStream& store,const FXColor *PIXELS,FXint width,FXint height,bool fast=true);

/**
 * Check if stream contains a XPM, return TRUE if so.
 */
bool fxcheckXPM(FXStream& store);

