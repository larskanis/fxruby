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
 * at "lyle@rubyforge.org".
 ***********************************************************************/

%apply const FXchar **strings { const FXchar** choices };

/**
* The Choice Box provides a dialog panel to select one item out of a list
* of choices.  The choices are provided as a list of text strings.
* When the dialog closes, the index of the selected choice is returned,
* while a -1 is returned if the dialog was canceled,
*/
class FXChoiceBox : public FXDialogBox {
public:
  long onCmdClicked(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCancel(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_CLICKED=FXDialogBox::ID_LAST,
    ID_LAST
    };
public:

  %extend {
    /// Construct choice box with given caption, icon, message text, and with choices from array of strings
    FXChoiceBox(FXWindow* owner,const FXString& caption,const FXString& text,FXIcon* icon,const FXchar** choices,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbChoiceBox(owner,caption,text,icon,choices,opts,x,y,w,h);
      }

    /// Construct free floating choice box with given caption, icon, message text, and with choices from array of strings
    FXChoiceBox(FXApp* app,const FXString& caption,const FXString& text,FXIcon* icon,const FXchar** choices,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbChoiceBox(app,caption,text,icon,choices,opts,x,y,w,h);
      }
  }

  /**
  * Show a modal choice dialog.
  * Prompt the user using a dialog with given caption, icon,
  * message text, and with choices from newline array of strings.
  * The return value is -1 if cancelled, or the given choice.
  */
  static FXint ask(FXWindow* owner,FXuint opts,const FXString& caption,const FXString& text,FXIcon* icon,const FXchar** choices);

  /**
  * Show modal choice message, in free floating window.
  * Prompt the user using a dialog with given caption, icon,
  * message text, and with choices from newline array of strings.
  * The return value is -1 if cancelled, or the given choice
  */
  static FXint ask(FXApp* app,FXuint opts,const FXString& caption,const FXString& text,FXIcon* icon,const FXchar** choices);

  // Destructor
  virtual ~FXChoiceBox();
  };

%clear const FXchar** choices;

DECLARE_FXOBJECT_VIRTUALS(FXChoiceBox)
DECLARE_FXID_VIRTUALS(FXChoiceBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXChoiceBox)
DECLARE_FXWINDOW_VIRTUALS(FXChoiceBox)
DECLARE_FXTOPWINDOW_VIRTUALS(FXChoiceBox)
DECLARE_FXDIALOGBOX_VIRTUALS(FXChoiceBox)


