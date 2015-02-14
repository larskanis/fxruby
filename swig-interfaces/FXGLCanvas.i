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

%rename("shared?") FXGLCanvas::isShared() const;

/// GLCanvas, an area drawn by another object
class FXGLCanvas : public FXCanvas {
public:
  %extend {
    /**
    * Construct an OpenGL-capable canvas, with its own private display list.
    */
    FXGLCanvas(FXComposite* p,FXGLVisual *vis,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbGLCanvas(p,vis,tgt,sel,opts,x,y,w,h);
      }

    /**
    * Construct an OpenGL-capable canvas, sharing display
    * list with another GL canvas.  This canvas becomes a member
    * of a display list share group.  All members of the display
    * list share group have to have the same visual.
    */
    FXGLCanvas(FXComposite* p,FXGLVisual *vis,FXGLCanvas* sharegroup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbGLCanvas(p,vis,sharegroup,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return TRUE if it is sharing display lists
  FXbool isShared() const;

  %extend {
    /// Return current context, if any
    static FXuval getCurrentContext(){
      return reinterpret_cast<FXuval>(FXGLCanvas::getCurrentContext());
      }

    /// Get GL context handle
    FXuval getContext() const {
      return reinterpret_cast<FXuval>(self->getContext());
      }
    }

  /// Destructor
  virtual ~FXGLCanvas();
  };


DECLARE_FXOBJECT_VIRTUALS(FXGLCanvas)
DECLARE_FXID_VIRTUALS(FXGLCanvas)
DECLARE_FXDRAWABLE_VIRTUALS(FXGLCanvas)
DECLARE_FXWINDOW_VIRTUALS(FXGLCanvas)
DECLARE_FXGLCANVAS_VIRTUALS(FXGLCanvas)

%{
static swig_type_info *FXGLCanvas_dynamic_cast(void **ptr) {
    FXGLCanvas **ppGLCanvas = reinterpret_cast<FXGLCanvas **>(ptr);
    FXGLViewer *pGLViewer=dynamic_cast<FXGLViewer*>(*ppGLCanvas);
    if(pGLViewer){
      *ptr=reinterpret_cast<void*>(pGLViewer);
      return SWIG_TypeQuery("FXGLViewer *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXGLCanvas, FXGLCanvas_dynamic_cast);

