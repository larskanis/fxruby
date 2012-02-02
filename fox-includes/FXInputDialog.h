/********************************************************************************
*                                                                               *
*                         I n p u t   D i a l o g   B o x                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXInputDialog.h 2261 2005-12-02 01:34:31Z lyle $                     *
********************************************************************************/
#ifndef FXINPUTDIALOG_H
#define FXINPUTDIALOG_H

#ifndef FXDIALOGBOX_H
#include "FXDialogBox.h"
#endif

namespace FX {


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
class FXAPI FXInputDialog : public FXDialogBox {
  FXDECLARE(FXInputDialog)
protected:
  FXTextField *input;       // Text field widget
  FXdouble     limlo;       // Lower limit
  FXdouble     limhi;       // Upper limit
protected:
  FXInputDialog(){}
private:
  FXInputDialog(const FXInputDialog&);
  FXInputDialog &operator=(const FXInputDialog&);
  void initialize(const FXString& text,FXIcon* icon);
public:
  long onCmdAccept(FXObject*,FXSelector,void*);
public:

  /// Construct input dialog box with given caption, icon, and prompt text
  FXInputDialog(FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXuint opts=INPUTDIALOG_STRING,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Construct free floating input dialog box with given caption, icon, and prompt text
  FXInputDialog(FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXuint opts=INPUTDIALOG_STRING,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Get input string
  FXString getText() const;

  /// Set input string
  void setText(const FXString& text);

  /// Change number of visible columns of text
  void setNumColumns(FXint num);

  /// Return number of visible columns of text
  FXint getNumColumns() const;

  /// Change limits
  void setLimits(FXdouble lo,FXdouble hi){ limlo=lo; limhi=hi; }

  /// Return limits
  void getLimits(FXdouble& lo,FXdouble& hi){ lo=limlo; hi=limhi; }

  /// Run modal invocation of the dialog
  virtual FXuint execute(FXuint placement=PLACEMENT_CURSOR);

  /**
  * Prompt for a string, start with the initial value.
  * Return TRUE if the new value is accepted, and false otherwise.
  */
  static FXbool getString(FXString& result,FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL);

  /**
  * Prompt for a string, in free floating window.
  */
  static FXbool getString(FXString& result,FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL);

  /**
  * Prompt for an integer number, start with the given initial value.
  * Return TRUE if the new value is accepted, and false otherwise.
  * The input is constrained between lo and hi.
  */
  static FXbool getInteger(FXint& result,FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXint lo=-2147483647,FXint hi=2147483647);

  /**
  * Prompt for a integer number, in free floating window.
  */
  static FXbool getInteger(FXint& result,FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXint lo=-2147483647,FXint hi=2147483647);

  /**
  * Prompt for an real number, start with the given initial value.
  * Return TRUE if the new value is accepted, and false otherwise.
  * The input is constrained between lo and hi.
  */
  static FXbool getReal(FXdouble& result,FXWindow* owner,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXdouble lo=-1.797693134862315e+308,FXdouble hi=1.797693134862315e+308);

  /**
  * Prompt for a real number, in free floating window.
  */
  static FXbool getReal(FXdouble& result,FXApp* app,const FXString& caption,const FXString& label,FXIcon* icon=NULL,FXdouble lo=-1.797693134862315e+308,FXdouble hi=1.797693134862315e+308);
  };

}

#endif
