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


/**
* Vertical frame layout manager widget is used to automatically
* place child-windows vertically from top-to-bottom, or bottom-to-top,
* depending on the child window's layout hints.
*/
class FXVerticalFrame : public FXPacker {
public:

  /// Construct a vertical frame layout manager
  %extend {
    FXVerticalFrame(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbVerticalFrame(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Destructor
  virtual ~FXVerticalFrame();
  };


DECLARE_FXOBJECT_VIRTUALS(FXVerticalFrame)
DECLARE_FXID_VIRTUALS(FXVerticalFrame)
DECLARE_FXDRAWABLE_VIRTUALS(FXVerticalFrame)
DECLARE_FXWINDOW_VIRTUALS(FXVerticalFrame)

%{
static swig_type_info *FXVerticalFrame_dynamic_cast(void **ptr) {
    FXVerticalFrame **ppVerticalFrame = reinterpret_cast<FXVerticalFrame **>(ptr);
    FXShutter *pShutter=dynamic_cast<FXShutter*>(*ppVerticalFrame);
    if(pShutter){
      *ptr=reinterpret_cast<void*>(pShutter);
      return SWIG_TypeQuery("FXShutter *");
      }
    FXShutterItem *pShutterItem=dynamic_cast<FXShutterItem*>(*ppVerticalFrame);
    if(pShutterItem){
      *ptr=reinterpret_cast<void*>(pShutterItem);
      return SWIG_TypeQuery("FXShutterItem *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXVerticalFrame, FXVerticalFrame_dynamic_cast);

