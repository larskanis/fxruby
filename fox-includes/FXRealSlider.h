/********************************************************************************
*                                                                               *
*                       R e a l S l i d e r   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXRealSlider.h 2343 2006-02-12 20:26:26Z lyle $                      *
********************************************************************************/
#ifndef FXREALSLIDER_H
#define FXREALSLIDER_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/// Slider Control styles
enum {
  REALSLIDER_HORIZONTAL   = 0,                          /// Slider shown horizontally
  REALSLIDER_VERTICAL     = 0x00008000,                 /// Slider shown vertically
  REALSLIDER_ARROW_UP     = 0x00010000,                 /// Slider has arrow head pointing up
  REALSLIDER_ARROW_DOWN   = 0x00020000,                 /// Slider has arrow head pointing down
  REALSLIDER_ARROW_LEFT   = REALSLIDER_ARROW_UP,        /// Slider has arrow head pointing left
  REALSLIDER_ARROW_RIGHT  = REALSLIDER_ARROW_DOWN,      /// Slider has arrow head pointing right
  REALSLIDER_INSIDE_BAR   = 0x00040000,                 /// Slider is inside the slot rather than overhanging
  REALSLIDER_TICKS_TOP    = 0x00080000,                 /// Ticks on the top of horizontal slider
  REALSLIDER_TICKS_BOTTOM = 0x00100000,                 /// Ticks on the bottom of horizontal slider
  REALSLIDER_TICKS_LEFT   = REALSLIDER_TICKS_TOP,       /// Ticks on the left of vertical slider
  REALSLIDER_TICKS_RIGHT  = REALSLIDER_TICKS_BOTTOM,    /// Ticks on the right of vertical slider
  REALSLIDER_NORMAL       = REALSLIDER_HORIZONTAL
  };


/**
* The real slider widget is a valuator widget which provides simple linear value range.
* Two visual appearances are supported:- the sunken look, which is enabled with
* the SLIDER_INSIDE_BAR option and the regular look.  The latter may have optional
* arrows on the slider thumb.
* While being moved, the real slider sends a SEL_CHANGED message to its target;
* at the end of the interaction, a SEL_COMMAND message is sent.
* The message data represents the current slider value, of type pointer to FXdouble.
*/
class FXAPI FXRealSlider : public FXFrame {
  FXDECLARE(FXRealSlider)
protected:
  FXdouble      range[2];                 // Reported data range
  FXdouble      pos;                      // Reported data position
  FXdouble      incr;                     // Increment when auto-sliding
  FXdouble      delta;                    // Interval between ticks
  FXint         headpos;                  // Head position
  FXint         headsize;                 // Head size
  FXint         slotsize;                 // Slot size
  FXColor       slotColor;                // Color of slot the head moves in
  FXint         dragpoint;                // Where on the head is grabbed
  FXString      help;                     // Help string
  FXString      tip;                      // Tip string
protected:
  FXRealSlider();
  void drawSliderHead(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawHorzTicks(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawVertTicks(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
private:
  FXRealSlider(const FXRealSlider&);
  FXRealSlider &operator=(const FXRealSlider&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onMouseWheel(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMiddleBtnPress(FXObject*,FXSelector,void*);
  long onMiddleBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
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

  /// Construct a slider widget
  FXRealSlider(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=REALSLIDER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Returns true because a slider can receive focus
  virtual bool canFocus() const;

  /// Perform layout
  virtual void layout();

  /// Enable the slider
  virtual void enable();

  /// Disable the slider
  virtual void disable();

  /// Change slider value
  void setValue(FXdouble value,FXbool notify=FALSE);

  /// Return slider value
  FXdouble getValue() const { return pos; }

  /// Change the slider's range
  void setRange(FXdouble lo,FXdouble hi,FXbool notify=FALSE);

  /// Get the slider's current range
  void getRange(FXdouble& lo,FXdouble& hi) const { lo=range[0]; hi=range[1]; }

  /// Change the slider style
  FXuint getSliderStyle() const;

  /// Get the current slider style
  void setSliderStyle(FXuint style);

  /// Get the slider's head size
  FXint getHeadSize() const { return headsize; }

  /// Change the slider's head size
  void setHeadSize(FXint hs);

  /// Get the slider's current slot size
  FXint getSlotSize() const { return slotsize; }

  /// Change the slider's slot size
  void setSlotSize(FXint bs);

  /// Get the slider's auto-increment/decrement value
  FXdouble getIncrement() const { return incr; }

  /// Change the slider's auto-increment/decrement value
  void setIncrement(FXdouble inc);

  /// Change the delta between ticks
  void setTickDelta(FXdouble dist);

  /// Get delta between ticks
  FXdouble getTickDelta() const { return delta; }

  /// Change the color of the slot the slider head moves in
  void setSlotColor(FXColor clr);

  /// Get the current slot color
  FXColor getSlotColor() const { return slotColor; }

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

  /// Destroy the slider
  virtual ~FXRealSlider();
  };

}

#endif
