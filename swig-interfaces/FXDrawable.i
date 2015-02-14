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

class FXVisual;


/**
* Drawable is an abstract base class for any surface that can be
* drawn upon, such as a FXWindow, or FXImage.
*/
class FXDrawable : public FXId {
public:
  %extend {
    // Construct with this width and height
    FXDrawable(FXApp* a,FXint w,FXint h){
      return new FXRbDrawable(a,w,h);
      }
    }

  /// Width of drawable
  FXint getWidth() const;

  /// Height of drawable
  FXint getHeight() const;

  /// Get the visual
  FXVisual* getVisual() const;

  /// Change visual
  void setVisual(FXVisual* vis);

  /// Cleanup
  virtual ~FXDrawable();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDrawable)
DECLARE_FXID_VIRTUALS(FXDrawable)
DECLARE_FXDRAWABLE_VIRTUALS(FXDrawable)

%{
static swig_type_info *FXDrawable_dynamic_cast(void **ptr) {
    FXDrawable **ppDrawable = reinterpret_cast<FXDrawable **>(ptr);
    FXBitmap *pBitmap=dynamic_cast<FXBitmap*>(*ppDrawable);
    if(pBitmap){
      *ptr=reinterpret_cast<void*>(pBitmap);
      return SWIG_TypeQuery("FXBitmap *");
      }
    FXImage *pImage=dynamic_cast<FXImage*>(*ppDrawable);
    if(pImage){
      *ptr=reinterpret_cast<void*>(pImage);
      return SWIG_TypeQuery("FXImage *");
      }
    FXWindow *pWindow=dynamic_cast<FXWindow*>(*ppDrawable);
    if(pWindow){
      *ptr=reinterpret_cast<void*>(pWindow);
      return SWIG_TypeQuery("FXWindow *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXDrawable, FXDrawable_dynamic_cast);

