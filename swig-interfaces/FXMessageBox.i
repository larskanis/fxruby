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

// Message box buttons
enum {
  MBOX_OK               = 0x10000000,   /// Message box has a only an OK button
  MBOX_OK_CANCEL        = 0x20000000,   /// Message box has OK and CANCEL buttons
  MBOX_YES_NO           = 0x30000000,   /// Message box has YES and NO buttons
  MBOX_YES_NO_CANCEL    = 0x40000000,   /// Message box has YES, NO, and CANCEL buttons
  MBOX_QUIT_CANCEL      = 0x50000000,   /// Message box has QUIT and CANCEL buttons
  MBOX_QUIT_SAVE_CANCEL   = 0x60000000, /// Message box has QUIT, SAVE, and CANCEL buttons
  MBOX_SKIP_SKIPALL_CANCEL  = 0x70000000 /// Message box has SKIP, SKIP ALL, and CANCEL buttons
  };

/* SWIG doesn't wrap this value correctly without a hint */
%constant FXuint MBOX_SAVE_CANCEL_DONTSAVE = 0x80000000; // Message box has DON'T SAVE,CANCEL and SAVE buttons


// Return values
enum {
  MBOX_CLICKED_YES      = 1,            /// The YES button was clicked
  MBOX_CLICKED_NO       = 2,            /// The NO button was clicked
  MBOX_CLICKED_OK       = 3,            /// The OK button was clicked
  MBOX_CLICKED_CANCEL   = 4,            /// The CANCEL button was clicked
  MBOX_CLICKED_QUIT     = 5,            /// The QUIT button was clicked
  MBOX_CLICKED_SAVE     = 6,            /// The SAVE button was clicked
  MBOX_CLICKED_SKIP     = 7,            /// The SKIP button was clicked
  MBOX_CLICKED_SKIPALL  = 8             /// The SKIP ALL button was clicked
  };

/* FOX doesn't define this constant, but we do for consistency */
%constant MBOX_CLICKED_DONTSAVE = MBOX_CLICKED_NO;

/**
* A Message Box is a convenience class which provides a dialog for
* very simple common yes/no type interactions with the user.
* The message box has an optional icon, a title string, and the question
* which is presented to the user.  It also has up to three buttons which
* furnish standard responses to the question.
* Message boxes are usually ran modally: the question must be answered
* before the program may continue.
*/
class FXMessageBox : public FXDialogBox {
public:
  long onCmdClicked(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCancel(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_CLICKED_YES=FXDialogBox::ID_LAST,
    ID_CLICKED_NO,
    ID_CLICKED_OK,
    ID_CLICKED_CANCEL,
    ID_CLICKED_QUIT,
    ID_CLICKED_SAVE,
    ID_CLICKED_SKIP,
    ID_CLICKED_SKIPALL,
    ID_LAST
    };
public:
  %extend {
    /// Construct message box with given caption, icon, and message text
    FXMessageBox(FXWindow* owner,const FXString& caption,const FXString& text,FXIcon* ic=NULL,FXuint opts=0,FXint x=0,FXint y=0){
      return new FXRbMessageBox(owner,caption,text,ic,opts,x,y);
      }

    /// Construct free floating message box with given caption, icon, and message text
    FXMessageBox(FXApp* app,const FXString& caption,const FXString& text,FXIcon* ic=NULL,FXuint opts=0,FXint x=0,FXint y=0){
      return new FXRbMessageBox(app,caption,text,ic,opts,x,y);
      }
    }

  %typemap(in) (const char* message_format, const char* message_string) {
    $1 = (char*)"%s";
    $2 = RSTRING_PTR($input);
  }

  /// Show a modal error message
  static FXuint error(FXWindow* owner,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  // Show modal error message, in free floating window.
  static FXuint error(FXApp* app,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  /// Show a modal warning message
  static FXuint warning(FXWindow* owner,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  /// Show a modal warning message, in a free-floating window
  static FXuint warning(FXApp* app,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  /// Show a modal question dialog
  static FXuint question(FXWindow* owner,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  /// Show a modal question dialog, in a free-floating window
  static FXuint question(FXApp* app,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  /// Show a modal information dialog
  static FXuint information(FXWindow* owner,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  /// Show a modal information dialog, in a free-floating window
  static FXuint information(FXApp* app,FXuint opts,const char* caption,const char* message_format, const char* message_string);

  // Destructor
  virtual ~FXMessageBox();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMessageBox)
DECLARE_FXID_VIRTUALS(FXMessageBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXMessageBox)
DECLARE_FXWINDOW_VIRTUALS(FXMessageBox)
DECLARE_FXTOPWINDOW_VIRTUALS(FXMessageBox)
DECLARE_FXDIALOGBOX_VIRTUALS(FXMessageBox)

