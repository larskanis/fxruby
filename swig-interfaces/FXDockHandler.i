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

%rename("helpText=") FXDockHandler::setHelpText(const FXString&);
%rename("helpText")  FXDockHandler::getHelpText() const;
%rename("tipText=")  FXDockHandler::setTipText(const FXString&);
%rename("tipText")   FXDockHandler::getTipText() const;

/**
* The dock handler exists as a common base class for tool bar grip
* and dock title.
*/
class FXDockHandler : public FXFrame {
public:
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
public:

  /// Set the status line help text for grip
  void setHelpText(const FXString& text);

  /// Get the status line help text for grip
  const FXString& getHelpText() const;

  /// Set the tool tip message for the grip
  void setTipText(const FXString& text);

  /// Get the tool tip message for the grip
  const FXString& getTipText() const;
  };


DECLARE_FXOBJECT_VIRTUALS(FXDockHandler)
DECLARE_FXID_VIRTUALS(FXDockHandler)
DECLARE_FXDRAWABLE_VIRTUALS(FXDockHandler)
DECLARE_FXWINDOW_VIRTUALS(FXDockHandler)

%{
static swig_type_info *FXDockHandler_dynamic_cast(void **ptr) {
    FXDockHandler **ppDockHandler = reinterpret_cast<FXDockHandler **>(ptr);
    FXDockTitle *pDockTitle=dynamic_cast<FXDockTitle*>(*ppDockHandler);
    if(pDockTitle){
      *ptr=reinterpret_cast<void*>(pDockTitle);
      return SWIG_TypeQuery("FXDockTitle *");
      }
    FXToolBarGrip *pToolBarGrip=dynamic_cast<FXToolBarGrip*>(*ppDockHandler);
    if(pToolBarGrip){
      *ptr=reinterpret_cast<void*>(pToolBarGrip);
      return SWIG_TypeQuery("FXToolBarGrip *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXDockHandler, FXDockHandler_dynamic_cast);

