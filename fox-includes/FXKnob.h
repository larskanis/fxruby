/********************************************************************************
*                                                                               *
*                             K n o b   W i d g e t                             *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Leandro Nini.   All Rights Reserved.                    *
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
* $Id: FXKnob.h 2336 2006-02-04 15:20:33Z lyle $                             *
********************************************************************************/
#ifndef FXKNOB_H
#define FXKNOB_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/// Knob Control styles
enum {
  KNOB_NEEDLE    = 0,                           /// Use a needle as indicator
  KNOB_DOT       = 0x00008000,                  /// Use a dot as indicator
  KNOB_TICKS     = 0x00010000,                  /// Show ticks around the knob
  KNOB_INDICATOR = 0x00020000,                  /// Show only the indicator (like a speedometer)
  KNOB_NORMAL    = (KNOB_NEEDLE|KNOB_TICKS)     /// Normal knob looks
  };



/**
* The knob widget is a valuator widget which provides simple linear value range.
* While being moved, the knob sends SEL_CHANGED messages to its target;
* at the end of the interaction, a final SEL_COMMAND message is sent.
* The message data represents the current knob value, of type FXint.
*/
class FXAPI FXKnob : public FXFrame {
  FXDECLARE(FXKnob)
protected:
  FXint    range[2];            // Reported data range
  FXdouble limits[2];           // Starting and ending positions
  FXColor  lineColor;           // Color of indicator needle
  FXint    pos;                 // Reported data position
  FXint    incr;                // Increment when auto-sliding
  FXint    delta;               // Interval between ticks
  FXString help;                // Help string
  FXString tip;                 // Tip string
protected:
  FXKnob();
  FXint calcValue(FXint x,FXint y);
private:
  FXKnob(const FXKnob&);
  FXKnob &operator=(const FXKnob&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMiddleBtnPress(FXObject*,FXSelector,void*);
  long onMiddleBtnRelease(FXObject*,FXSelector,void*);
  long onMouseWheel(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onAutoSlide(FXObject*,FXSelector,void*);
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
  enum{
    ID_AUTOSLIDE=FXFrame::ID_LAST,
    ID_LAST
    };
public:

  /// Construct a knob widget
  FXKnob(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=KNOB_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Returns true because a knob can receive focus
  virtual bool canFocus() const;

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /// Enable the knob
  virtual void enable();

  /// Disable the knob
  virtual void disable();

  /// Change knob value
  void setValue(FXint value,FXbool notify=FALSE);

  /// Return knob value
  FXint getValue() const { return pos; }

  /// Change the knob's range
  void setRange(FXint lo,FXint hi,FXbool notify=FALSE);

  /// Get the knob's current range
  void getRange(FXint& lo,FXint& hi) const { lo=range[0]; hi=range[1]; }

  /**
  * Change the knob's movement limits (start and ending angles)
  * accept values in degrees from 0 (south) to 360.
  */
  void setLimits(FXint start,FXint end,FXbool notify=FALSE);

  /// Get the knob's current limits
  void getLimits(FXint& start,FXint& end);

  /// Change the knob style
  FXuint getKnobStyle() const;

  /// Get the current knob style
  void setKnobStyle(FXuint style);

  /// Get the knob's auto-increment/decrement value
  FXint getIncrement() const { return incr; }

  /// Change the knob's auto-increment/decrement value
  void setIncrement(FXint inc){ incr=inc; }

  /// Change the delta between ticks
  void setTickDelta(FXint dist);

  /// Get delta between ticks
  FXint getTickDelta() const { return delta; }

  /// Change the indicator needle color
  void setLineColor(FXColor clr);

  /// Get the current indicator needle color
  FXColor getLineColor() const { return lineColor; }

  /// Set the help text to be displayed on the status line
  void setHelpText(const FXString& text){ help=text; }

  /// Get the current help text
  const FXString& getHelpText() const { return help; }

  /// Set the tip text to be displayed in the tooltip
  void setTipText(const FXString& text){ tip=text; }

  /// Get the current tooltip text value
  const FXString& getTipText() const { return tip; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy the knob
  virtual ~FXKnob();
  };

}

#endif
