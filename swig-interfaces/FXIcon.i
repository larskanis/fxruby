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


/// Icon class
class FXIcon : public FXImage {
public:
  %extend {
    /**
    * Create an icon with an initial pixel buffer pix, a transparent color clr,
    * and options as in FXImage.
    */
    FXIcon(FXApp* a,const FXColor *PIXELS=NULL,FXColor clr=0,FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbIcon(a,PIXELS,clr,opts,w,h);
      }
    }

  /// Obtain transparency color
  FXColor getTransparentColor() const;

  /// Change transparency color
  void setTransparentColor(FXColor color);

  /// Destructor
  virtual ~FXIcon();
  };


DECLARE_FXOBJECT_VIRTUALS(FXIcon)
DECLARE_FXID_VIRTUALS(FXIcon)
DECLARE_FXDRAWABLE_VIRTUALS(FXIcon)
DECLARE_FXIMAGE_VIRTUALS(FXIcon)

%{
static swig_type_info *FXIcon_dynamic_cast(void **ptr) {
    FXIcon **ppIcon = reinterpret_cast<FXIcon **>(ptr);
    FXBMPIcon *pBMPIcon=dynamic_cast<FXBMPIcon*>(*ppIcon);
    if(pBMPIcon){
      *ptr=reinterpret_cast<void*>(pBMPIcon);
      return SWIG_TypeQuery("FXBMPIcon *");
      }
    FXGIFIcon *pGIFIcon=dynamic_cast<FXGIFIcon*>(*ppIcon);
    if(pGIFIcon){
      *ptr=reinterpret_cast<void*>(pGIFIcon);
      return SWIG_TypeQuery("FXGIFIcon *");
      }
    FXICOIcon *pICOIcon=dynamic_cast<FXICOIcon*>(*ppIcon);
    if(pICOIcon){
      *ptr=reinterpret_cast<void*>(pICOIcon);
      return SWIG_TypeQuery("FXICOIcon *");
      }
    FXJPGIcon *pJPGIcon=dynamic_cast<FXJPGIcon*>(*ppIcon);
    if(pJPGIcon){
      *ptr=reinterpret_cast<void*>(pJPGIcon);
      return SWIG_TypeQuery("FXJPGIcon *");
      }
    FXPCXIcon *pPCXIcon=dynamic_cast<FXPCXIcon*>(*ppIcon);
    if(pPCXIcon){
      *ptr=reinterpret_cast<void*>(pPCXIcon);
      return SWIG_TypeQuery("FXPCXIcon *");
      }
    FXPNGIcon *pPNGIcon=dynamic_cast<FXPNGIcon*>(*ppIcon);
    if(pPNGIcon){
      *ptr=reinterpret_cast<void*>(pPNGIcon);
      return SWIG_TypeQuery("FXPNGIcon *");
      }
    FXPPMIcon *pPPMIcon=dynamic_cast<FXPPMIcon*>(*ppIcon);
    if(pPPMIcon){
      *ptr=reinterpret_cast<void*>(pPPMIcon);
      return SWIG_TypeQuery("FXPPMIcon *");
      }
    FXRGBIcon *pRGBIcon=dynamic_cast<FXRGBIcon*>(*ppIcon);
    if(pRGBIcon){
      *ptr=reinterpret_cast<void*>(pRGBIcon);
      return SWIG_TypeQuery("FXRGBIcon *");
      }
    FXTGAIcon *pTGAIcon=dynamic_cast<FXTGAIcon*>(*ppIcon);
    if(pTGAIcon){
      *ptr=reinterpret_cast<void*>(pTGAIcon);
      return SWIG_TypeQuery("FXTGAIcon *");
      }
    FXTIFIcon *pTIFIcon=dynamic_cast<FXTIFIcon*>(*ppIcon);
    if(pTIFIcon){
      *ptr=reinterpret_cast<void*>(pTIFIcon);
      return SWIG_TypeQuery("FXTIFIcon *");
      }
    FXXBMIcon *pXBMIcon=dynamic_cast<FXXBMIcon*>(*ppIcon);
    if(pXBMIcon){
      *ptr=reinterpret_cast<void*>(pXBMIcon);
      return SWIG_TypeQuery("FXXBMIcon *");
      }
    FXXPMIcon *pXPMIcon=dynamic_cast<FXXPMIcon*>(*ppIcon);
    if(pXPMIcon){
      *ptr=reinterpret_cast<void*>(pXPMIcon);
      return SWIG_TypeQuery("FXXPMIcon *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXIcon, FXIcon_dynamic_cast);

