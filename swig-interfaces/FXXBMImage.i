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


/// X Bitmap image
class FXXBMImage : public FXImage {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXXBMImage::fileExt);
      }

    static VALUE mimeType() {
      return to_ruby(FXXBMImage::mimeType);
      }
    }
public:

  /// Construct image from memory stream formatted in X Bitmap format
  %extend {
    FXXBMImage(FXApp* a,const FXuchar *pixels=NULL,const FXuchar *mask=NULL,FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbXBMImage(a,pixels,mask,opts,w,h);
      }
    }

  /// Destroy icon
  virtual ~FXXBMImage();
  };


DECLARE_FXOBJECT_VIRTUALS(FXXBMImage)
DECLARE_FXID_VIRTUALS(FXXBMImage)
DECLARE_FXDRAWABLE_VIRTUALS(FXXBMImage)
DECLARE_FXIMAGE_VIRTUALS(FXXBMImage)


%inline %{
  /**
   * Load an XBM (X Bitmap) from pixel array and mask array.
   * Upon successful return, the pixel array and size are returned.
   * If an error occurred, the pixel array is set to NULL.
   */
  VALUE fxloadXBM(const FXuchar *pix,const FXuchar *msk,FXint width,FXint height){
    FXColor* data;
    if(fxloadXBM(data,pix,msk,width,height)){
      VALUE obj=FXRbMakeColorArray(data,width,height);
      FXFREE(&data);
      return obj;
      }
    else{
      return Qnil;
      }
    }


  /**
   * Load an XBM (X Bitmap) file from a stream.
   * Upon successful return, the pixel array and size, and hot-spot are returned.
   * If an error occurred, the pixel array is set to NULL.
   */
  VALUE fxloadXBM(FXStream& store){
    FXColor* data;
    FXint width,height,hotx,hoty;
    if(fxloadXBM(store,data,width,height,hotx,hoty)){
      VALUE ary=rb_ary_new();
      rb_ary_push(ary,FXRbMakeColorArray(data,width,height));
      FXFREE(&data);
      rb_ary_push(ary,to_ruby(width));
      rb_ary_push(ary,to_ruby(height));
      rb_ary_push(ary,to_ruby(hotx));
      rb_ary_push(ary,to_ruby(hoty));
      return ary;
      }
    else{
      return Qnil;
      }
    }
%}


/**
 * Save an XBM (X Bitmap) file to a stream; if the parameters hotx and hoty are set
 * to -1, no hotspot location is saved.
 */
bool fxsaveXBM(FXStream& store,const FXColor *data,FXint width,FXint height,FXint hotx=-1,FXint hoty=-1);

/**
 * Save a PostScript file to a stream; format the picture to the maximal
 * size that fits within the given margins of the indicated paper size.
 */
bool fxsavePS(FXStream& store,const FXColor *data,FXint width,FXint height,FXint paperw=612,FXint paperh=792,FXint margin=35,FXbool color=TRUE);

/**
 * Check if stream contains a XBM, return TRUE if so.
 */
bool fxcheckXBM(FXStream& store);

