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
* DialogBox window.
* When receiving ID_CANCEL or ID_ACCEPT, the DialogBox breaks out of the
* modal loop and returns FALSE or TRUE, respectively.
* To close the DialogBox when not running modally, simply send it ID_HIDE.
*/
class FXDialogBox : public FXTopWindow {
public:
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdAccept(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCancel(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_CANCEL=FXTopWindow::ID_LAST,     /// Closes the dialog, cancel the entry
    ID_ACCEPT,                          /// Closes the dialog, accept the entry
    ID_LAST
    };
public:
  %extend {
    /// Construct free-floating dialog
    FXDialogBox(FXApp* APP,const FXString& name,FXuint opts=DECOR_TITLE|DECOR_BORDER,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=4,FXint vs=4){
      return new FXRbDialogBox(APP,name,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }

    /// Construct dialog which will always float over the owner window
    FXDialogBox(FXWindow* OWNER,const FXString& name,FXuint opts=DECOR_TITLE|DECOR_BORDER,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=4,FXint vs=4){
      return new FXRbDialogBox(OWNER,name,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Destructor
  virtual ~FXDialogBox();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDialogBox)
DECLARE_FXID_VIRTUALS(FXDialogBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXDialogBox)
DECLARE_FXWINDOW_VIRTUALS(FXDialogBox)
DECLARE_FXTOPWINDOW_VIRTUALS(FXDialogBox)
DECLARE_FXDIALOGBOX_VIRTUALS(FXDialogBox)

%{
static swig_type_info *FXDialogBox_dynamic_cast(void **ptr) {
    FXDialogBox **ppDialogBox = reinterpret_cast<FXDialogBox **>(ptr);
    FXChoiceBox *pChoiceBox=dynamic_cast<FXChoiceBox*>(*ppDialogBox);
    if(pChoiceBox){
      *ptr=reinterpret_cast<void*>(pChoiceBox);
      return SWIG_TypeQuery("FXChoiceBox *");
      }
    FXColorDialog *pColorDialog=dynamic_cast<FXColorDialog*>(*ppDialogBox);
    if(pColorDialog){
      *ptr=reinterpret_cast<void*>(pColorDialog);
      return SWIG_TypeQuery("FXColorDialog *");
      }
    FXDirDialog *pDirDialog=dynamic_cast<FXDirDialog*>(*ppDialogBox);
    if(pDirDialog){
      *ptr=reinterpret_cast<void*>(pDirDialog);
      return SWIG_TypeQuery("FXDirDialog *");
      }
    FXFileDialog *pFileDialog=dynamic_cast<FXFileDialog*>(*ppDialogBox);
    if(pFileDialog){
      *ptr=reinterpret_cast<void*>(pFileDialog);
      return SWIG_TypeQuery("FXFileDialog *");
      }
    FXFontDialog *pFontDialog=dynamic_cast<FXFontDialog*>(*ppDialogBox);
    if(pFontDialog){
      *ptr=reinterpret_cast<void*>(pFontDialog);
      return SWIG_TypeQuery("FXFontDialog *");
      }
    FXInputDialog *pInputDialog=dynamic_cast<FXInputDialog*>(*ppDialogBox);
    if(pInputDialog){
      *ptr=reinterpret_cast<void*>(pInputDialog);
      return SWIG_TypeQuery("FXInputDialog *");
      }
    FXMessageBox *pMessageBox=dynamic_cast<FXMessageBox*>(*ppDialogBox);
    if(pMessageBox){
      *ptr=reinterpret_cast<void*>(pMessageBox);
      return SWIG_TypeQuery("FXMessageBox *");
      }
    FXPrintDialog *pPrintDialog=dynamic_cast<FXPrintDialog*>(*ppDialogBox);
    if(pPrintDialog){
      *ptr=reinterpret_cast<void*>(pPrintDialog);
      return SWIG_TypeQuery("FXPrintDialog *");
      }
    FXProgressDialog *pProgressDialog=dynamic_cast<FXProgressDialog*>(*ppDialogBox);
    if(pProgressDialog){
      *ptr=reinterpret_cast<void*>(pProgressDialog);
      return SWIG_TypeQuery("FXProgressDialog *");
      }
    FXReplaceDialog *pReplaceDialog=dynamic_cast<FXReplaceDialog*>(*ppDialogBox);
    if(pReplaceDialog){
      *ptr=reinterpret_cast<void*>(pReplaceDialog);
      return SWIG_TypeQuery("FXReplaceDialog *");
      }
    FXWizard *pWizard=dynamic_cast<FXWizard*>(*ppDialogBox);
    if(pWizard){
      *ptr=reinterpret_cast<void*>(pWizard);
      return SWIG_TypeQuery("FXWizard *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXDialogBox, FXDialogBox_dynamic_cast);

