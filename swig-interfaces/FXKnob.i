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


/// Knob Control styles
enum {
  KNOB_NEEDLE    = 0,                           /// Use a needle as indicator
  KNOB_DOT       = 0x00008000,                  /// Use a dot as indicator
  KNOB_TICKS     = 0x00010000,                  /// Show ticks around the knob
  KNOB_INDICATOR = 0x00020000,                  /// Show only the indicator (like a speedometer)
  KNOB_NORMAL    = (KNOB_NEEDLE|KNOB_TICKS)     /// Normal knob looks
  };

%rename("value=")     FXKnob::setValue(FXint,FXbool);
%rename("value")      FXKnob::getValue() const;
%rename("knobStyle=") FXKnob::setKnobStyle(FXuint);
%rename("knobStyle")  FXKnob::getKnobStyle() const;
%rename("increment=") FXKnob::setIncrement(FXint);
%rename("increment")  FXKnob::getIncrement() const;
%rename("tickDelta=") FXKnob::setTickDelta(FXint);
%rename("tickDelta")  FXKnob::getTickDelta() const;
%rename("lineColor=") FXKnob::setLineColor(FXColor);
%rename("lineColor")  FXKnob::getLineColor() const;
%rename("helpText=")  FXKnob::setHelpText(const FXString&);
%rename("helpText")   FXKnob::getHelpText() const;
%rename("tipText=")   FXKnob::setTipText(const FXString&);
%rename("tipText")    FXKnob::getTipText() const;

/**
* The knob widget is a valuator widget which provides simple linear value range.
* While being moved, the knob sends SEL_CHANGED messages to its target;
* at the end of the interaction, a final SEL_COMMAND message is sent.
* The message data represents the current knob value, of type FXint.
*/
class FXKnob : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onAutoSlide(FXObject*,FXSelector,void* PTR_IVAL);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_IVAL);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetRealValue(FXObject*,FXSelector,void* PTR_PDOUBLE);
  long onCmdGetRealValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_IN);
  long onCmdGetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_OUT);
  long onCmdSetRealRange(FXObject*,FXSelector,void* PTR_DBLRANGE_IN);
  long onCmdGetRealRange(FXObject*,FXSelector,void* PTR_DBLRANGE_OUT);
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_NULL);
  long onQueryTip(FXObject*,FXSelector,void* PTR_NULL);
public:
  enum{
    ID_AUTOSLIDE=FXFrame::ID_LAST,
    ID_LAST
    };
public:

  %extend {
    /// Construct a knob widget
    FXKnob(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=KNOB_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbKnob(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
  }

  /// Change knob value
  void setValue(FXint value,FXbool notify=FALSE);

  %extend {
    /// Change the knob's range
    void setRange(VALUE range,FXbool notify=FALSE){
      FXint lo,hi;
      FXRbRange2LoHi(range,lo,hi);
      self->setRange(lo,hi,notify);
      }

    /// Get the knob's current range
    VALUE getRange() const {
      FXint lo,hi;
      self->getRange(lo,hi);
      return rb_range_new(INT2NUM(lo),INT2NUM(hi),0);
      }
  }

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
  FXint getIncrement() const;

  /// Change the knob's auto-increment/decrement value
  void setIncrement(FXint inc);

  /// Change the delta between ticks
  void setTickDelta(FXint dist);

  /// Get delta between ticks
  FXint getTickDelta() const;

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

  /// Destroy the knob
  virtual ~FXKnob();
  };

DECLARE_FXOBJECT_VIRTUALS(FXKnob)
DECLARE_FXID_VIRTUALS(FXKnob)
DECLARE_FXDRAWABLE_VIRTUALS(FXKnob)
DECLARE_FXWINDOW_VIRTUALS(FXKnob)

