/********************************************************************************
*                                                                               *
*                              D i a l   W i d g e t                            *
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
* $Id: FXDial.h 2335 2006-01-28 02:33:03Z lyle $                            *
********************************************************************************/
#ifndef FXDIAL_H
#define FXDIAL_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


// Dial style options
enum {
  DIAL_VERTICAL   = 0,                            // Vertically oriented
  DIAL_HORIZONTAL = 0x00008000,                   // Horizontal oriented
  DIAL_CYCLIC     = 0x00010000,                   // Value wraps around
  DIAL_HAS_NOTCH  = 0x00020000,                   // Dial has a Center Notch
  DIAL_NORMAL     = DIAL_VERTICAL
  };


/**
* The Dial widget is a valuator widget which is able to provide a cyclic
* value range when the DIAL_CYCLIC is passed, or a simple linear value range.
* While being turned, the dial sends a SEL_CHANGED message to its target;
* at the end of the interaction, a SEL_COMMAND message is sent.
* The message data represents the current value, of type FXint.  The options
* DIAL_VERTICAL and DIAL_HORIZONTAL control the orientation of the dial.
* An optional notch can be used to indicate the zero-position of
* the dial; display of the notch is controlled by the DIAL_HAS_NOTCH option.
*/
class FXAPI FXDial : public FXFrame {
  FXDECLARE(FXDial)
protected:
  FXint         range[2];       // Reported data range
  FXColor       notchColor;     // Main notch color
  FXint         notchangle;     // Angle of main notch
  FXint         notchspacing;   // Angle between notches
  FXint         notchoffset;    // Notch offset
  FXint         dragpoint;      // Place where clicked
  FXint         dragpos;        // Value where clicked
  FXint         incr;           // Rate of change/revolution
  FXint         pos;            // Reported data position
  FXString      help;           // Help string
  FXString      tip;            // Tip string
protected:
  FXDial();
private:
  FXDial(const FXDial&);
  FXDial &operator=(const FXDial&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onMouseWheel(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void* );
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdSetRealValue(FXObject*,FXSelector,void*);
  long onCmdGetRealValue(FXObject*,FXSelector,void*);
  long onCmdSetIntRange(FXObject*,FXSelector,void*);
  long onCmdGetIntRange(FXObject*,FXSelector,void*);
  long onCmdSetRealRange(FXObject*,FXSelector,void*);
  long onCmdGetRealRange(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:

  /// Construct a dial widget
  FXDial(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=DIAL_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Returns true because a dial can receive focus
  virtual bool canFocus() const;

  /// Set the dial value
  void setValue(FXint value,FXbool notify=FALSE);

  /// Return the dial value
  FXint getValue() const { return pos; }

  /// Change the dial's range
  void setRange(FXint lo,FXint hi,FXbool notify=FALSE);

  /// Obtain the current range of the dial
  void getRange(FXint& lo,FXint& hi) const { lo=range[0]; hi=range[1]; }

  /**
  * Set the revolution increment, which is the amount of change
  * in the position for revolution of the dial; the dial may go
  * through multiple revolutions to go through its whole range;
  * by default it takes one 360 degree turn of the dial to go
  * from the lower to the upper range.
  */
  void setRevolutionIncrement(FXint i);

  /// Get the current value of the revolution increment
  FXint getRevolutionIncrement() const { return incr; }

  /**
  * Change the spacing for the small notches; this should be set
  * in tenths of degrees in the range [1,3600], and the value should
  * be a divisor of 3600, so as to make the notches come out evenly
  */
  void setNotchSpacing(FXint spacing);

  /// Get the current notch spacing
  FXint getNotchSpacing() const { return notchspacing; }

  /**
  * Change the notch offset, which is the position of the
  * center notch; the value should be tenths of degrees
  * in the range [-3600,3600]
  */
  void setNotchOffset(FXint offset);

  /// Get the current center notch offset
  FXint getNotchOffset() const { return notchoffset; }

  /// Changes the dial style.
  void setDialStyle(FXuint opts);

  /// Get the current dial style.
  FXuint getDialStyle() const;

  /// Change the center notch color
  void setNotchColor(FXColor clr);

  /// Get the current center notch color
  FXColor getNotchColor() const { return notchColor; }

  /// Set the help text to be displayed on the status line
  void setHelpText(const FXString& text);

  /// Get the current help text
  const FXString& getHelpText() const { return help; }

  /// Set the tip text to be displayed in the tooltip
  void setTipText(const FXString& text);

  /// Get the current tooltip text value
  const FXString& getTipText() const { return tip; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
