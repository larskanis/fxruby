/********************************************************************************
*                                                                               *
*                           S l i d e r   W i d g e t                           *
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
* $Id: FXSlider.h 2343 2006-02-12 20:26:26Z lyle $                          *
********************************************************************************/
#ifndef FXSLIDER_H
#define FXSLIDER_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/// Slider Control styles
enum {
  SLIDER_HORIZONTAL   = 0,                        /// Slider shown horizontally
  SLIDER_VERTICAL     = 0x00008000,               /// Slider shown vertically
  SLIDER_ARROW_UP     = 0x00010000,               /// Slider has arrow head pointing up
  SLIDER_ARROW_DOWN   = 0x00020000,               /// Slider has arrow head pointing down
  SLIDER_ARROW_LEFT   = SLIDER_ARROW_UP,          /// Slider has arrow head pointing left
  SLIDER_ARROW_RIGHT  = SLIDER_ARROW_DOWN,        /// Slider has arrow head pointing right
  SLIDER_INSIDE_BAR   = 0x00040000,               /// Slider is inside the slot rather than overhanging
  SLIDER_TICKS_TOP    = 0x00080000,               /// Ticks on the top of horizontal slider
  SLIDER_TICKS_BOTTOM = 0x00100000,               /// Ticks on the bottom of horizontal slider
  SLIDER_TICKS_LEFT   = SLIDER_TICKS_TOP,         /// Ticks on the left of vertical slider
  SLIDER_TICKS_RIGHT  = SLIDER_TICKS_BOTTOM,      /// Ticks on the right of vertical slider
  SLIDER_NORMAL       = SLIDER_HORIZONTAL
  };


/**
* The slider widget is a valuator widget which provides simple linear value range.
* Two visual appearances are supported:- the sunken look, which is enabled with
* the SLIDER_INSIDE_BAR option and the regular look.  The latter may have optional
* arrows on the slider thumb.
* While being moved, the slider sends a SEL_CHANGED message to its target;
* at the end of the interaction, a SEL_COMMAND message is sent.
* The message data represents the current slider value, of type FXint.
*/
class FXAPI FXSlider : public FXFrame {
  FXDECLARE(FXSlider)
protected:
  FXint         range[2];                 // Reported data range
  FXint         pos;                      // Reported data position
  FXint         incr;                     // Increment when auto-sliding
  FXint         delta;                    // Interval between ticks
  FXint         headpos;                  // Head position
  FXint         headsize;                 // Head size
  FXint         slotsize;                 // Slot size
  FXColor       slotColor;                // Color of slot the head moves in
  FXint         dragpoint;                // Where the head is grabbed
  FXString      help;                     // Help string
  FXString      tip;                      // Tip string
protected:
  FXSlider();
  void drawSliderHead(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawHorzTicks(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawVertTicks(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
private:
  FXSlider(const FXSlider&);
  FXSlider &operator=(const FXSlider&);
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
  FXSlider(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=SLIDER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0);

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
  void setValue(FXint value,FXbool notify=FALSE);

  /// Return slider value
  FXint getValue() const { return pos; }

  /// Change the slider's range
  void setRange(FXint lo,FXint hi,FXbool notify=FALSE);

  /// Get the slider's current range
  void getRange(FXint& lo,FXint& hi) const { lo=range[0]; hi=range[1]; }

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
  FXint getIncrement() const { return incr; }

  /// Change the slider's auto-increment/decrement value
  void setIncrement(FXint inc);

  /// Change the delta between ticks
  void setTickDelta(FXint dist);

  /// Get delta between ticks
  FXint getTickDelta() const { return delta; }

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
  virtual ~FXSlider();
  };

}

#endif
