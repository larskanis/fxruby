/********************************************************************************
*                                                                               *
*                  R a d i o   B u t t o n    W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXRadioButton.h 2343 2006-02-12 20:26:26Z lyle $                     *
********************************************************************************/
#ifndef FXRADIOBUTTON_H
#define FXRADIOBUTTON_H

#ifndef FXLABEL_H
#include "FXLabel.h"
#endif

namespace FX {


/// RadioButton flags
enum {
  RADIOBUTTON_AUTOGRAY = 0x00800000,  /// Automatically gray out when not updated
  RADIOBUTTON_AUTOHIDE = 0x01000000,  /// Automatically hide when not updated
  RADIOBUTTON_NORMAL   = JUSTIFY_NORMAL|ICON_BEFORE_TEXT
  };



/**
* A radio button is a tri-state button.  Normally, it is either
* TRUE or FALSE; a third state MAYBE may be set to indicate that no selection
* has been made yet by the user, or that the state is ambiguous.
* When pressed, the radio button sets its state to TRUE and sends a SEL_COMMAND
* to its target, and the message data set to the state of the radio button,
* of the type FXbool.
* A group of radio buttons can be made mutually exclusive by linking them
* to a common data target.  Alternatively, an application can implement a
* common SEL_UPDATED handler to check and uncheck radio buttons as appropriate.
*/
class FXAPI FXRadioButton : public FXLabel {
  FXDECLARE(FXRadioButton)
protected:
  FXColor  radioColor;  // Color of radio ball
  FXColor  diskColor;   // Color of radio disk
  FXbool   check;       // Radio state
  FXbool   oldcheck;    // Old radio state
protected:
  FXRadioButton();
private:
  FXRadioButton(const FXRadioButton&);
  FXRadioButton &operator=(const FXRadioButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUpdate(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
  long onCheck(FXObject*,FXSelector,void*);
  long onUncheck(FXObject*,FXSelector,void*);
  long onUnknown(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
public:

  /// Construct new radio button
  FXRadioButton(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=RADIOBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Returns true because a radio button can receive focus
  virtual bool canFocus() const;

  /// Get default width
  virtual FXint getDefaultWidth();

  /// Get default height
  virtual FXint getDefaultHeight();

  /// Set radio button state (TRUE, FALSE or MAYBE)
  void setCheck(FXbool s=TRUE,FXbool notify=FALSE);

  /// Get radio button state (TRUE, FALSE or MAYBE)
  FXbool getCheck() const { return check; }

  /// Change radio button style
  void setRadioButtonStyle(FXuint style);

  /// Return current radio button style
  FXuint getRadioButtonStyle() const;

  /// Get the radio ball color
  FXColor getRadioColor() const { return radioColor; }

  /// Set the radio ball color
  void setRadioColor(FXColor clr);

  /// Get the radio disk color
  FXColor getDiskColor() const { return diskColor; }

  /// Set the radio disk color
  void setDiskColor(FXColor clr);

  /// Save radio button to a stream
  virtual void save(FXStream& store) const;

  /// Load radio button from a stream
  virtual void load(FXStream& store);
  };

}

#endif
