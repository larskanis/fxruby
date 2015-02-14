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


/// Base composite
class FXComposite : public FXWindow {
public:
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusNext(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusPrev(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdUpdate(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXComposite(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbComposite(p,opts,x,y,w,h);
      }
    }

  /// Return the width of the widest child window
  FXint maxChildWidth() const;

  /// Return the height of the tallest child window
  FXint maxChildHeight() const;

  /// Destructor
  virtual ~FXComposite();
  };


DECLARE_FXOBJECT_VIRTUALS(FXComposite)
DECLARE_FXID_VIRTUALS(FXComposite)
DECLARE_FXDRAWABLE_VIRTUALS(FXComposite)
DECLARE_FXWINDOW_VIRTUALS(FXComposite)

%{
static swig_type_info *FXComposite_dynamic_cast(void **ptr) {
    FXComposite **ppComposite = reinterpret_cast<FXComposite **>(ptr);
    FX4Splitter *p4Splitter=dynamic_cast<FX4Splitter*>(*ppComposite);
    if(p4Splitter){
      *ptr=reinterpret_cast<void*>(p4Splitter);
      return SWIG_TypeQuery("FX4Splitter *");
      }
    FXMDIChild *pMDIChild=dynamic_cast<FXMDIChild*>(*ppComposite);
    if(pMDIChild){
      *ptr=reinterpret_cast<void*>(pMDIChild);
      return SWIG_TypeQuery("FXMDIChild *");
      }
    FXPacker *pPacker=dynamic_cast<FXPacker*>(*ppComposite);
    if(pPacker){
      *ptr=reinterpret_cast<void*>(pPacker);
      return SWIG_TypeQuery("FXPacker *");
      }
    FXRootWindow *pRootWindow=dynamic_cast<FXRootWindow*>(*ppComposite);
    if(pRootWindow){
      *ptr=reinterpret_cast<void*>(pRootWindow);
      return SWIG_TypeQuery("FXRootWindow *");
      }
    FXScrollArea *pScrollArea=dynamic_cast<FXScrollArea*>(*ppComposite);
    if(pScrollArea){
      *ptr=reinterpret_cast<void*>(pScrollArea);
      return SWIG_TypeQuery("FXScrollArea *");
      }
    FXShell *pShell=dynamic_cast<FXShell*>(*ppComposite);
    if(pShell){
      *ptr=reinterpret_cast<void*>(pShell);
      return SWIG_TypeQuery("FXShell *");
      }
    FXSplitter *pSplitter=dynamic_cast<FXSplitter*>(*ppComposite);
    if(pSplitter){
      *ptr=reinterpret_cast<void*>(pSplitter);
      return SWIG_TypeQuery("FXSplitter *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXComposite, FXComposite_dynamic_cast);

