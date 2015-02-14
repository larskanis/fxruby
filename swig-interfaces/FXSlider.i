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


/// Slider Control
class FXSlider : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onAutoSlide(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
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
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_AUTOSLIDE=FXFrame::ID_LAST,
    ID_LAST
    };
public:

  /// Construct a slider widget
  %extend {
    FXSlider(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=SLIDER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0){
      return new FXRbSlider(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change slider value
  void setValue(FXint value,FXbool notify=FALSE);

  /// Return slider value
  FXint getValue() const;

  %extend {
    /// Change the slider's range
    void setRange(VALUE range,FXbool notify=FALSE){
      FXint lo,hi;
      FXRbRange2LoHi(range,lo,hi);
      self->setRange(lo,hi,notify);
      }

    /// Get the slider's current range
    VALUE getRange() const {
      FXint lo,hi;
      self->getRange(lo,hi);
      return rb_range_new(INT2NUM(lo),INT2NUM(hi),0);
      }
  }

  /// Change the slider style
  FXuint getSliderStyle() const;

  /// Get the current slider style
  void setSliderStyle(FXuint style);

  /// Get the slider's head size
  FXint getHeadSize() const;

  /// Change the slider's head size
  void setHeadSize(FXint hs);

  /// Get the slider's current slot size
  FXint getSlotSize() const;

  /// Change the slider's slot size
  void setSlotSize(FXint bs);

  /// Get the slider's auto-increment/decrement value
  FXint getIncrement() const;

  /// Change the slider's auto-increment/decrement value
  void setIncrement(FXint inc);

  /// Change the delta between ticks
  void setTickDelta(FXint dist);

  /// Get delta between ticks
  FXint getTickDelta() const;

  /// Change the color of the slot the slider head moves in
  void setSlotColor(FXColor clr);

  /// Get the current slot color
  FXColor getSlotColor() const;

  /// Set the help text to be displayed on the status line
  void setHelpText(const FXString& text);

  /// Get the current help text
  const FXString& getHelpText() const;

  /// Set the tip text to be displayed in the tooltip
  void setTipText(const FXString& text);

  /// Get the current tooltip text value
  const FXString& getTipText() const;

  /// Destroy the slider
  virtual ~FXSlider();
  };


DECLARE_FXOBJECT_VIRTUALS(FXSlider)
DECLARE_FXID_VIRTUALS(FXSlider)
DECLARE_FXDRAWABLE_VIRTUALS(FXSlider)
DECLARE_FXWINDOW_VIRTUALS(FXSlider)

