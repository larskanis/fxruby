/********************************************************************************
*                                                                               *
*                              D i a l o g   B o x                              *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDialogBox.h 812 2002-07-11 18:00:42Z lyle $                       *
********************************************************************************/
#ifndef FXDIALOGBOX_H
#define FXDIALOGBOX_H

#ifndef FXTOPWINDOW_H
#include "FXTopWindow.h"
#endif

namespace FX {


/**
* DialogBox window.
* When receiving ID_CANCEL or ID_ACCEPT, the DialogBox breaks out of the
* modal loop and returns FALSE or TRUE, respectively.
* To close the DialogBox when not running modally, simply send it ID_HIDE.
*/
class FXAPI FXDialogBox : public FXTopWindow {
  FXDECLARE(FXDialogBox)
protected:
  FXDialogBox(){}
private:
  FXDialogBox(const FXDialogBox&);
  FXDialogBox &operator=(const FXDialogBox&);
public:
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onCmdAccept(FXObject*,FXSelector,void*);
  long onCmdCancel(FXObject*,FXSelector,void*);
public:
  enum {
    ID_CANCEL=FXTopWindow::ID_LAST,     /// Closes the dialog, cancel the entry
    ID_ACCEPT,                          /// Closes the dialog, accept the entry
    ID_LAST
    };
public:

  /// Construct free-floating dialog
  FXDialogBox(FXApp* a,const FXString& name,FXuint opts=DECOR_TITLE|DECOR_BORDER,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=4,FXint vs=4);

  /// Construct dialog which will always float over the owner window
  FXDialogBox(FXWindow* owner,const FXString& name,FXuint opts=DECOR_TITLE|DECOR_BORDER,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=4,FXint vs=4);

  /// Run modal invocation of the dialog
  virtual FXuint execute(FXuint placement=PLACEMENT_CURSOR);
  };

}

#endif
