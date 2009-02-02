/********************************************************************************
*                                                                               *
*                      T e x t   R e p l a c e   D i a l o g                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXReplaceDialog.h 809 2002-07-11 17:28:15Z lyle $                   *
********************************************************************************/
#ifndef FXREPLACEDIALOG_H
#define FXREPLACEDIALOG_H

#ifndef FXDIALOGBOX_H
#include "FXDialogBox.h"
#endif

namespace FX {


class FXButton;
class FXLabel;
class FXTextField;
class FXHorizontalFrame;


/// Text replace dialog
class FXAPI FXReplaceDialog : public FXDialogBox {
  FXDECLARE(FXReplaceDialog)
protected:
  FXLabel           *searchlabel;
  FXTextField       *searchtext;
  FXHorizontalFrame *searchbox;
  FXLabel           *replacelabel;
  FXTextField       *replacetext;
  FXHorizontalFrame *replacebox;
  FXButton          *accept;
  FXButton          *cancel;
  FXButton          *every;
  FXuint             searchmode;
  FXuint             current;
protected:
  FXReplaceDialog(){}
  void appendHistory(const FXString& search,const FXString& replace,FXuint mode);
private:
  FXReplaceDialog(const FXReplaceDialog&);
  FXReplaceDialog &operator=(const FXReplaceDialog&);
public:
  long onCmdAll(FXObject*,FXSelector,void*);
  long onCmdNext(FXObject*,FXSelector,void*);
  long onUpdDir(FXObject*,FXSelector,void*);
  long onCmdDir(FXObject*,FXSelector,void*);
  long onUpdMode(FXObject*,FXSelector,void*);
  long onCmdMode(FXObject*,FXSelector,void*);
  long onSearchKey(FXObject*,FXSelector,void*);
  long onReplaceKey(FXObject*,FXSelector,void*);
  long onCmdSearchHist(FXObject*,FXSelector,void*);
  long onCmdReplaceHist(FXObject*,FXSelector,void*);
  long onCmdAccept(FXObject*,FXSelector,void*);
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
  FXReplaceDialog(FXWindow* owner,const FXString& caption,FXIcon* ic=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Set text or pattern to search for
  void setSearchText(const FXString& text);

  /// Return text or pattern the user has entered
  FXString getSearchText() const;

  /// Set replace text
  void setReplaceText(const FXString& text);

  /// Return replace text the user has entered
  FXString getReplaceText() const;

  /// Set search match mode
  void setSearchMode(FXuint mode){ searchmode=mode; }

  /// Return search mode the user has selected
  FXuint getSearchMode() const { return searchmode; }

  /// Run modal invocation of the dialog
  virtual FXuint execute(FXuint placement=PLACEMENT_CURSOR);

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXReplaceDialog();
  };

}

#endif
