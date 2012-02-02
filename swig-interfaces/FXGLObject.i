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


class FXGLViewer;


/// Basic OpenGL object
class FXGLObject : public FXObject {
public:
  enum {
    ID_LAST=10000       // Leaving ample room for FXGLViewer subclasses
    };
public:

  %extend {
    /// Constructor
    FXGLObject(){
      return new FXRbGLObject();
      }
    }

  %extend {
    /// Identify sub-object given path
    virtual FXGLObject* identify(FXuint* path,FXint n){
      return self->identify(path);
      }
    }

  // Destructor
  virtual ~FXGLObject();
  };


DECLARE_FXOBJECT_VIRTUALS(FXGLObject)
DECLARE_FXGLOBJECT_VIRTUALS(FXGLObject)

%{
static swig_type_info *FXGLObject_dynamic_cast(void **ptr) {
    FXGLObject **ppGLObject = reinterpret_cast<FXGLObject **>(ptr);
    FXGLShape *pGLShape=dynamic_cast<FXGLShape*>(*ppGLObject);
    if(pGLShape){
      *ptr=reinterpret_cast<void*>(pGLShape);
      return SWIG_TypeQuery("FXGLShape *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXGLObject, FXGLObject_dynamic_cast);

