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
* Horizontal frame layout manager widget is used to automatically
* place child-windows horizontally from left-to-right, or right-to-left,
* depending on the child window's layout hints.
*/
class FXHorizontalFrame : public FXPacker {
public:
  %extend {
    /// Construct a horizontal frame layout manager
    FXHorizontalFrame(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbHorizontalFrame(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }
  };


DECLARE_FXOBJECT_VIRTUALS(FXHorizontalFrame)
DECLARE_FXID_VIRTUALS(FXHorizontalFrame)
DECLARE_FXDRAWABLE_VIRTUALS(FXHorizontalFrame)
DECLARE_FXWINDOW_VIRTUALS(FXHorizontalFrame)

%{
static swig_type_info *FXHorizontalFrame_dynamic_cast(void **ptr) {
    FXHorizontalFrame **ppHorizontalFrame = reinterpret_cast<FXHorizontalFrame **>(ptr);
    FXStatusBar *pStatusBar=dynamic_cast<FXStatusBar*>(*ppHorizontalFrame);
    if(pStatusBar){
      *ptr=reinterpret_cast<void*>(pStatusBar);
      return SWIG_TypeQuery("FXStatusBar *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXHorizontalFrame, FXHorizontalFrame_dynamic_cast);

