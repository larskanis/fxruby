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
 * The Shell widget is used as the base class for top level windows, i.e.
 * windows which are direct children of the root window.
 */
class FXShell : public FXComposite {
public:
  long onLayout(FXObject*,FXSelector,void* PTR_IGNORE);
  long onConfigure(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusNext(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusPrev(FXObject*,FXSelector,void* PTR_EVENT);
public:
  enum {
    ID_LAYOUT=FXComposite::ID_LAST,
    ID_LAST
    };
public:
  %extend {
    // Construct free-floating shell window
    FXShell(FXApp* a,FXuint opts,FXint x,FXint y,FXint w,FXint h){
      return new FXRbShell(a,opts,x,y,w,h);
      }

    // Construct owned shell window
    FXShell(FXWindow* own,FXuint opts,FXint x,FXint y,FXint w,FXint h){
      return new FXRbShell(own,opts,x,y,w,h);
      }
    }

  /// Destroy shell
  virtual ~FXShell();
  };


DECLARE_FXOBJECT_VIRTUALS(FXShell)
DECLARE_FXID_VIRTUALS(FXShell)
DECLARE_FXDRAWABLE_VIRTUALS(FXShell)
DECLARE_FXWINDOW_VIRTUALS(FXShell)

%{
static swig_type_info *FXShell_dynamic_cast(void **ptr) {
    FXShell **ppShell = reinterpret_cast<FXShell **>(ptr);
    FXPopup *pPopup=dynamic_cast<FXPopup*>(*ppShell);
    if(pPopup){
      *ptr=reinterpret_cast<void*>(pPopup);
      return SWIG_TypeQuery("FXPopup *");
      }
    FXToolTip *pToolTip=dynamic_cast<FXToolTip*>(*ppShell);
    if(pToolTip){
      *ptr=reinterpret_cast<void*>(pToolTip);
      return SWIG_TypeQuery("FXToolTip *");
      }
    FXTopWindow *pTopWindow=dynamic_cast<FXTopWindow*>(*ppShell);
    if(pTopWindow){
      *ptr=reinterpret_cast<void*>(pTopWindow);
      return SWIG_TypeQuery("FXTopWindow *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXShell, FXShell_dynamic_cast);

