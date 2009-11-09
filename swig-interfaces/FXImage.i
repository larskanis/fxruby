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

%rename("hasAlpha?") FXImage::hasAlpha() const;

/**
* An Image is a rectangular array of pixels.  It supports two representations
* of these pixels: a client-side pixel buffer which is stored as an array of
* FXColor, and a server-side pixmap which is stored in an organization directly
* compatible with the screen, for fast drawing onto the device.
* The server-side representation is not directly accessible from the current
* process as it lives in the process of the X Server or GDI.
*/
class FXImage : public FXDrawable {
public:
  %extend {
    /**
    * Create an image.  If a client-side pixel buffer has been specified,
    * the image does not own the pixel buffer unless the IMAGE_OWNED flag is
    * set.  If the IMAGE_OWNED flag is set but a NULL pixel buffer is
    * passed, a pixel buffer will be automatically created and will be owned
    * by the image. The flags IMAGE_SHMI and IMAGE_SHMP may be specified for
    * large images to instruct render() to use shared memory to communicate
    * with the server.
    */
    FXImage(FXApp* a,VALUE ary=Qnil,FXuint opts=0,FXint w=1,FXint h=1){
      FXColor* pix=0;
      if(!NIL_P(ary)){
        Check_Type(ary,T_ARRAY);
        if(FXMALLOC(&pix,FXColor,RARRAY_LEN(ary))){
          for(long i=0; i<RARRAY_LEN(ary); i++){
            pix[i]=static_cast<FXColor>(NUM2UINT(rb_ary_entry(ary,i)));
	    }
          }
	  opts&=IMAGE_OWNED;
        }
      return new FXRbImage(a,pix,opts,w,h);
      }

    /// To get to the pixel data
    FXMemoryBuffer *getData() const {
      if(self->getData()){
        return new FXMemoryBuffer(self->getData(),self->getWidth()*self->getHeight());
	}
      else{
        return 0;
	}
      }
  }
  
  /// To get to the option flags
  FXuint getOptions() const;

  /// Change options
  void setOptions(FXuint opts);

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

  /// Get pixel at x,y
  FXColor getPixel(FXint x,FXint y) const;

  /// Change pixel at x,y
  void setPixel(FXint x,FXint y,FXColor color);
  
  /// Scan the image and return FALSE if fully opaque
  bool hasAlpha() const;

  /// Destructor
  virtual ~FXImage();
  };


DECLARE_FXOBJECT_VIRTUALS(FXImage)
DECLARE_FXID_VIRTUALS(FXImage)
DECLARE_FXDRAWABLE_VIRTUALS(FXImage)
DECLARE_FXIMAGE_VIRTUALS(FXImage)

%{
static swig_type_info *FXImage_dynamic_cast(void **ptr) {
    FXImage **ppImage = reinterpret_cast<FXImage **>(ptr);
    FXBMPImage *pBMPImage=dynamic_cast<FXBMPImage*>(*ppImage);
    if(pBMPImage){
      *ptr=reinterpret_cast<void*>(pBMPImage);
      return SWIG_TypeQuery("FXBMPImage *");
      }
    FXGIFImage *pGIFImage=dynamic_cast<FXGIFImage*>(*ppImage);
    if(pGIFImage){
      *ptr=reinterpret_cast<void*>(pGIFImage);
      return SWIG_TypeQuery("FXGIFImage *");
      }
    FXICOImage *pICOImage=dynamic_cast<FXICOImage*>(*ppImage);
    if(pICOImage){
      *ptr=reinterpret_cast<void*>(pICOImage);
      return SWIG_TypeQuery("FXICOImage *");
      }
    FXIcon *pIcon=dynamic_cast<FXIcon*>(*ppImage);
    if(pIcon){
      *ptr=reinterpret_cast<void*>(pIcon);
      return SWIG_TypeQuery("FXIcon *");
      }
    FXJPGImage *pJPGImage=dynamic_cast<FXJPGImage*>(*ppImage);
    if(pJPGImage){
      *ptr=reinterpret_cast<void*>(pJPGImage);
      return SWIG_TypeQuery("FXJPGImage *");
      }
    FXPCXImage *pPCXImage=dynamic_cast<FXPCXImage*>(*ppImage);
    if(pPCXImage){
      *ptr=reinterpret_cast<void*>(pPCXImage);
      return SWIG_TypeQuery("FXPCXImage *");
      }
    FXPNGImage *pPNGImage=dynamic_cast<FXPNGImage*>(*ppImage);
    if(pPNGImage){
      *ptr=reinterpret_cast<void*>(pPNGImage);
      return SWIG_TypeQuery("FXPNGImage *");
      }
    FXPPMImage *pPPMImage=dynamic_cast<FXPPMImage*>(*ppImage);
    if(pPPMImage){
      *ptr=reinterpret_cast<void*>(pPPMImage);
      return SWIG_TypeQuery("FXPPMImage *");
      }
    FXRGBImage *pRGBImage=dynamic_cast<FXRGBImage*>(*ppImage);
    if(pRGBImage){
      *ptr=reinterpret_cast<void*>(pRGBImage);
      return SWIG_TypeQuery("FXRGBImage *");
      }
    FXTGAImage *pTGAImage=dynamic_cast<FXTGAImage*>(*ppImage);
    if(pTGAImage){
      *ptr=reinterpret_cast<void*>(pTGAImage);
      return SWIG_TypeQuery("FXTGAImage *");
      }
    FXTIFImage *pTIFImage=dynamic_cast<FXTIFImage*>(*ppImage);
    if(pTIFImage){
      *ptr=reinterpret_cast<void*>(pTIFImage);
      return SWIG_TypeQuery("FXTIFImage *");
      }
    FXXBMImage *pXBMImage=dynamic_cast<FXXBMImage*>(*ppImage);
    if(pXBMImage){
      *ptr=reinterpret_cast<void*>(pXBMImage);
      return SWIG_TypeQuery("FXXBMImage *");
      }
    FXXPMImage *pXPMImage=dynamic_cast<FXXPMImage*>(*ppImage);
    if(pXPMImage){
      *ptr=reinterpret_cast<void*>(pXPMImage);
      return SWIG_TypeQuery("FXXPMImage *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXImage, FXImage_dynamic_cast);

