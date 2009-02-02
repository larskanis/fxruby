/********************************************************************************
*                                                                               *
*                    C h e c k   B u t t o n   W i d g e t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXCheckButton.h 2335 2006-01-28 02:33:03Z lyle $                     *
********************************************************************************/
#ifndef FXCHECKBUTTON_H
#define FXCHECKBUTTON_H

#ifndef FXLABEL_H
#include "FXLabel.h"
#endif

namespace FX {


/// CheckButton styles
enum {
  CHECKBUTTON_AUTOGRAY = 0x00800000,    /// Automatically gray out when not updated
  CHECKBUTTON_AUTOHIDE = 0x01000000,    /// Automatically hide when not updated
  CHECKBUTTON_PLUS     = 0x02000000,    /// Draw a + for unchecked and - for checked
  CHECKBUTTON_NORMAL   = JUSTIFY_NORMAL|ICON_BEFORE_TEXT
  };


/**
* A Check Button is a tri-state button.  Normally, it is either
* TRUE or FALSE, and toggles between TRUE or FALSE whenever it is pressed.
* A third state MAYBE may be set to indicate that no selection has been made yet
* by the user, or that the state is ambiguous.
* When pressed, the Check Button sends a SEL_COMMAND to its target, and the
* message data represents the state of the check button.
* The option CHECKBUTTON_AUTOGRAY (CHECKBUTTON_AUTOHIDE) causes the button to be
* grayed out (hidden) if its handler does not respond to the SEL_UPDATE message.
* With the CHECKBUTTON_PLUS option, the Check Button will draw a + or - sign instead
* of a check.  You can use this to make collapsable panels, by hooking up a Check
* Button to a layout manager via the ID_TOGGLE_SHOWN message.  This will give a
* similar visual element as collapsing folders in a Tree List.
*/
class FXAPI FXCheckButton : public FXLabel {
  FXDECLARE(FXCheckButton)
protected:
  FXColor  checkColor;  // Color of check mark
  FXColor  boxColor;    // Color of check box
  FXbool   check;       // Check state
  FXbool   oldcheck;    // Old check state
protected:
  FXCheckButton();
private:
  FXCheckButton(const FXCheckButton&);
  FXCheckButton &operator=(const FXCheckButton&);
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

  /// Construct new check button
  FXCheckButton(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=CHECKBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Returns true because a check button can receive focus
  virtual bool canFocus() const;

  /// Get default width
  virtual FXint getDefaultWidth();

  /// Get default height
  virtual FXint getDefaultHeight();

  /// Set check button state (TRUE, FALSE or MAYBE)
  void setCheck(FXbool state=TRUE,FXbool notify=FALSE);

  /// Get check button state (TRUE, FALSE or MAYBE)
  FXbool getCheck() const { return check; }

  /// Change check button style
  void setCheckButtonStyle(FXuint style);

  /// Return current check button style
  FXuint getCheckButtonStyle() const;

  /// Get the box background color
  FXColor getBoxColor() const { return boxColor; }

  /// Set the box background color
  void setBoxColor(FXColor clr);

  /// Get the box check color
  FXColor getCheckColor() const { return checkColor; }

  /// Set the box check color
  void setCheckColor(FXColor clr);

  /// Save check button to a stream
  virtual void save(FXStream& store) const;

  /// Load check button from a stream
  virtual void load(FXStream& store);
  };

}

#endif
