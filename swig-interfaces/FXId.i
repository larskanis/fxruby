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

class FXApp;

%rename("xid") FXId::id() const;
%rename("created?") FXId::created() const;


/// Encapsulates server side resource
class FXId : public FXObject {
public:

  /// Get application
  FXApp* getApp() const;

  /// Get XID handle
  FXID id() const;

  /// Returns true if this resource has been create-ed (i.e. it's ID is non-NULL)
  %extend {
    bool created() const {
      return self->id() != 0;
      }
    }

  %extend {
    /// Set user data pointer
    void setUserData(VALUE ptr){
      self->setUserData(reinterpret_cast<void*>(ptr));
      }

    /// Get user data pointer
    VALUE getUserData() const {
      return self->getUserData() ? reinterpret_cast<VALUE>(self->getUserData()) : Qnil;
      }
  }

  /// Destructor
  virtual ~FXId();
  };


DECLARE_FXOBJECT_VIRTUALS(FXId)
DECLARE_FXID_VIRTUALS(FXId)

%{
static swig_type_info *FXId_dynamic_cast(void **ptr) {
    FXId **ppId = reinterpret_cast<FXId **>(ptr);
    FXCursor *pCursor=dynamic_cast<FXCursor*>(*ppId);
    if(pCursor){
      *ptr=reinterpret_cast<void*>(pCursor);
      return SWIG_TypeQuery("FXCursor *");
      }
    FXDrawable *pDrawable=dynamic_cast<FXDrawable*>(*ppId);
    if(pDrawable){
      *ptr=reinterpret_cast<void*>(pDrawable);
      return SWIG_TypeQuery("FXDrawable *");
      }
    FXFont *pFont=dynamic_cast<FXFont*>(*ppId);
    if(pFont){
      *ptr=reinterpret_cast<void*>(pFont);
      return SWIG_TypeQuery("FXFont *");
      }
    FXGLContext *pGLContext=dynamic_cast<FXGLContext*>(*ppId);
    if(pGLContext){
      *ptr=reinterpret_cast<void*>(pGLContext);
      return SWIG_TypeQuery("FXGLContext *");
      }
    FXVisual *pVisual=dynamic_cast<FXVisual*>(*ppId);
    if(pVisual){
      *ptr=reinterpret_cast<void*>(pVisual);
      return SWIG_TypeQuery("FXVisual *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXId, FXId_dynamic_cast);

