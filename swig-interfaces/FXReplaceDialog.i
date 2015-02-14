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

class FXTextField;


/// Text replace dialog
class FXReplaceDialog : public FXDialogBox {
public:
  long onCmdAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdNext(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDir(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDir(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMode(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMode(FXObject*,FXSelector,void* PTR_IGNORE);
  long onSearchKey(FXObject*,FXSelector,void* PTR_EVENT);
  long onReplaceKey(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSearchHist(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdReplaceHist(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdAccept(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_NEXT=FXDialogBox::ID_LAST,
    ID_PREV,
    ID_SEARCH_UP,
    ID_SEARCH_DN,
    ID_REPLACE_UP,
    ID_REPLACE_DN,
    ID_ALL,
    ID_DIR,
    ID_SEARCH_TEXT,
    ID_REPLACE_TEXT,
    ID_MODE,
    ID_LAST=ID_MODE+32
    };
public:
  enum {
    DONE          = 0,    /// Cancel search
    SEARCH        = 1,    /// Search first occurrence
    REPLACE       = 1,    /// Replace first occurrence
    SEARCH_NEXT   = 2,    /// Search next occurrence
    REPLACE_NEXT  = 2,    /// Replace next occurrence
    REPLACE_ALL   = 3     /// Replace all occurrences
    };
public:

  /// Construct search and replace dialog box
  %extend {
    FXReplaceDialog(FXWindow* owner,const FXString& caption,FXIcon* ic=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbReplaceDialog(owner,caption,ic,opts,x,y,w,h);
      }
    }

  /// Set text or pattern to search for
  void setSearchText(const FXString& text);

  /// Return text or pattern the user has entered
  FXString getSearchText() const;

  /// Set replace text
  void setReplaceText(const FXString& text);

  /// Return replace text the user has entered
  FXString getReplaceText() const;

  /// Set search match mode
  void setSearchMode(FXuint mode);

  /// Return search mode the user has selected
  FXuint getSearchMode() const;

  /// Destructor
  virtual ~FXReplaceDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXReplaceDialog)
DECLARE_FXID_VIRTUALS(FXReplaceDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXReplaceDialog)
DECLARE_FXWINDOW_VIRTUALS(FXReplaceDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXReplaceDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXReplaceDialog)

%{
static swig_type_info *FXReplaceDialog_dynamic_cast(void **ptr) {
    FXReplaceDialog **ppReplaceDialog = reinterpret_cast<FXReplaceDialog **>(ptr);
    FXSearchDialog *pSearchDialog=dynamic_cast<FXSearchDialog*>(*ppReplaceDialog);
    if(pSearchDialog){
      *ptr=reinterpret_cast<void*>(pSearchDialog);
      return SWIG_TypeQuery("FXSearchDialog *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXReplaceDialog, FXReplaceDialog_dynamic_cast)

