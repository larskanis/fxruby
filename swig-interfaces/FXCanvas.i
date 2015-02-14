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


/// Canvas, an area drawn by another object
class FXCanvas : public FXWindow {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Construct new drawing canvas widget
    FXCanvas(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbCanvas(p,tgt,sel,opts,x,y,w,h);
      }
    }

    /// Destructor
    virtual ~FXCanvas();
  };


DECLARE_FXOBJECT_VIRTUALS(FXCanvas)
DECLARE_FXID_VIRTUALS(FXCanvas)
DECLARE_FXDRAWABLE_VIRTUALS(FXCanvas)
DECLARE_FXWINDOW_VIRTUALS(FXCanvas)

%{
static swig_type_info *FXCanvas_dynamic_cast(void **ptr) {
    FXCanvas **ppCanvas = reinterpret_cast<FXCanvas **>(ptr);
    FXGLCanvas *pGLCanvas=dynamic_cast<FXGLCanvas*>(*ppCanvas);
    if(pGLCanvas){
      *ptr=reinterpret_cast<void*>(pGLCanvas);
      return SWIG_TypeQuery("FXGLCanvas *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXCanvas, FXCanvas_dynamic_cast);

