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

/// Input dialog options
enum {
  INPUTDIALOG_STRING   = 0,             /// Ask for a string
  INPUTDIALOG_INTEGER  = 0x01000000,    /// Ask for an integer number
  INPUTDIALOG_REAL     = 0x02000000,    /// Ask for a real number
  INPUTDIALOG_PASSWORD = 0x04000000     /// Do not reveal key-in
  };


class FXTextField;


/**
* An Input Dialog is a simple dialog which is used
* to obtain a text string, integer, or real number from the user.
* A password mode allows the key-in to remain hidden.
*/
class FXInputDialog : public FXDialogBox {
public:
  long onCmdAccept(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  %extend {
    /// Construct input dialog box with given caption, icon, and prompt text
    FXInputDialog(FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXuint opts=INPUTDIALOG_STRING,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbInputDialog(owner,caption,label,icon,opts,x,y,w,h);
      }

    /// Construct free floating input dialog box with given caption, icon, and prompt text
    FXInputDialog(FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXuint opts=INPUTDIALOG_STRING,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbInputDialog(app,caption,label,icon,opts,x,y,w,h);
      }
    }

  /// Get input string
  FXString getText() const;

  /// Set input string
  void setText(const FXString& text);

  /// Change number of visible columns of text
  void setNumColumns(FXint num);

  /// Return number of visible columns of text
  FXint getNumColumns() const;

  /// Change limits
  void setLimits(FXdouble lo,FXdouble hi);

  %extend {
    // Return limits
    VALUE getLimits() {
      FXdouble lo, hi;
      self->getLimits(lo, hi);
      VALUE result = rb_ary_new();
      rb_ary_push(result, rb_float_new(lo));
      rb_ary_push(result, rb_float_new(hi));
      return result;
    }
  }

  /**
  * Prompt for a string, start with the initial value.
  * Return TRUE if the new value is accepted, and false otherwise.
  */
  %extend {
    static VALUE getString(const FXString& initial,FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL){
      FXString result(initial);
      if(FXInputDialog::getString(result,owner,caption,label,icon)){
        return to_ruby(result);
        }
      else{
        return Qnil;
        }
    }

   /**
    * Prompt for a string, in free floating window.
    */
    static VALUE getString(const FXString& initial,FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL){
      FXString result(initial);
      if(FXInputDialog::getString(result,app,caption,label,icon)){
        return to_ruby(result);
        }
      else{
        return Qnil;
        }
    }
  }

  /**
  * Prompt for an integer number, start with the given initial value.
  * Return TRUE if the new value is accepted, and false otherwise.
  * The input is constrained between lo and hi.
  */
  %extend {
    static VALUE getInteger(FXint initial,FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXint lo=-2147483647,FXint hi=2147483647){
      FXint result=initial;
      if(FXInputDialog::getInteger(result,owner,caption,label,icon,lo,hi)){
        return to_ruby(result);
        }
      else{
        return Qnil;
        }
      }
    static VALUE getInteger(FXint initial,FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXint lo=-2147483647,FXint hi=2147483647){
      FXint result=initial;
      if(FXInputDialog::getInteger(result,app,caption,label,icon,lo,hi)){
        return to_ruby(result);
        }
      else{
        return Qnil;
        }
      }
  }

  /**
  * Prompt for an real number, start with the given initial value.
  * Return TRUE if the new value is accepted, and false otherwise.
  * The input is constrained between lo and hi.
  */
  %extend {
    static VALUE getReal(FXdouble initial,FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXdouble lo=-1.797693134862315e+308,FXdouble hi=1.797693134862315e+308){
      FXdouble result=initial;
      if(FXInputDialog::getReal(result,owner,caption,label,icon,lo,hi)){
        return to_ruby(result);
        }
      else{
        return Qnil;
        }
      }
    static VALUE getReal(FXdouble initial,FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXdouble lo=-1.797693134862315e+308,FXdouble hi=1.797693134862315e+308){
      FXdouble result=initial;
      if(FXInputDialog::getReal(result,app,caption,label,icon,lo,hi)){
        return to_ruby(result);
        }
      else{
        return Qnil;
        }
      }
    }
  };


DECLARE_FXOBJECT_VIRTUALS(FXInputDialog)
DECLARE_FXID_VIRTUALS(FXInputDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXInputDialog)
DECLARE_FXWINDOW_VIRTUALS(FXInputDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXInputDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXInputDialog)

