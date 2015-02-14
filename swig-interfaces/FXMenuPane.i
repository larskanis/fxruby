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


/// Popup menu pane
class FXMenuPane : public FXPopup {
public:
  %extend {
    /// Construct menu pane
    FXMenuPane(FXWindow* owner,FXuint opts=0){
      return new FXRbMenuPane(owner,opts);
      }
    }

  // Destructor
  virtual ~FXMenuPane();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMenuPane)
DECLARE_FXID_VIRTUALS(FXMenuPane)
DECLARE_FXDRAWABLE_VIRTUALS(FXMenuPane)
DECLARE_FXWINDOW_VIRTUALS(FXMenuPane)
DECLARE_FXPOPUP_VIRTUALS(FXMenuPane)

%{
static swig_type_info *FXMenuPane_dynamic_cast(void **ptr) {
    FXMenuPane **ppMenuPane = reinterpret_cast<FXMenuPane **>(ptr);
    FXMDIMenu *pMDIMenu=dynamic_cast<FXMDIMenu*>(*ppMenuPane);
    if(pMDIMenu){
      *ptr=reinterpret_cast<void*>(pMDIMenu);
      return SWIG_TypeQuery("FXMDIMenu *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXMenuPane, FXMenuPane_dynamic_cast);

