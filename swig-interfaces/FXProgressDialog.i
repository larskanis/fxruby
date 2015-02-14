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

enum {
  PROGRESSDIALOG_NOCANCEL = 0,                        /// Default is no cancel button
  PROGRESSDIALOG_CANCEL   = 0x01000000,               /// Enable the cancel button
  PROGRESSDIALOG_NORMAL   = (DECOR_TITLE|DECOR_BORDER)
  };



/**
* A Progress Dialog is a simple dialog which is used to
* keep a user informed of the progress of a lengthy operation
* in a program and that the program is in fact still working.
*/
class FXProgressDialog : public FXDialogBox {
public:
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdCancel(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:

  /// Construct input dialog box with given caption, icon, and prompt text
  %extend {
    FXProgressDialog(FXWindow* owner,const FXString& caption,const FXString& label,FXuint opts=PROGRESSDIALOG_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbProgressDialog(owner,caption,label,opts,x,y,w,h);
      }
    }

  /// Change the progress message
  void setMessage(const FXString& msg);

  /// Get progress message
  FXString getMessage() const;

  /// Change style of the progress bar widget
  void setBarStyle(FXuint style);

  /// Get style of the progress bar widget
  FXuint getBarStyle() const;

  /// Change the amount of progress
  void setProgress(FXuint value);

  /// Get current progress
  FXuint getProgress() const;

  /// Set total amount of progress
  void setTotal(FXuint value);

  /// Return total amount of progrss
  FXuint getTotal() const;

  /// Increment progress by given amount
  void increment(FXuint value);

  /// Has operation been cancelled?
  FXbool isCancelled() const;

  /// Change cancelled flag
  void setCancelled(FXbool flg);

  /// Destroy
  virtual ~FXProgressDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXProgressDialog)
DECLARE_FXID_VIRTUALS(FXProgressDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXProgressDialog)
DECLARE_FXWINDOW_VIRTUALS(FXProgressDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXProgressDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXProgressDialog)

