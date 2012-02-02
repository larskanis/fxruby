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
  REALSLIDER_HORIZONTAL   = 0,                        /// Slider shown horizontally
  REALSLIDER_VERTICAL     = 0x00008000,               /// Slider shown vertically
  REALSLIDER_ARROW_UP     = 0x00010000,               /// Slider has arrow head pointing up
  REALSLIDER_ARROW_DOWN   = 0x00020000,               /// Slider has arrow head pointing down
  REALSLIDER_ARROW_LEFT   = REALSLIDER_ARROW_UP,          /// Slider has arrow head pointing left
  REALSLIDER_ARROW_RIGHT  = REALSLIDER_ARROW_DOWN,        /// Slider has arrow head pointing right
  REALSLIDER_INSIDE_BAR   = 0x00040000,               /// Slider is inside the slot rather than overhanging
  REALSLIDER_TICKS_TOP    = 0x00080000,               /// Ticks on the top of horizontal slider
  REALSLIDER_TICKS_BOTTOM = 0x00100000,               /// Ticks on the bottom of horizontal slider
  REALSLIDER_TICKS_LEFT   = REALSLIDER_TICKS_TOP,         /// Ticks on the left of vertical slider
  REALSLIDER_TICKS_RIGHT  = REALSLIDER_TICKS_BOTTOM,      /// Ticks on the right of vertical slider
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
class FXRealSlider : public FXFrame {
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
    FXRealSlider(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=REALSLIDER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0){
      return new FXRbRealSlider(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change slider value
  void setValue(FXdouble value,FXbool notify=FALSE);

  /// Return slider value
  FXdouble getValue() const;

  /// Change the slider's range
  void setRange(FXdouble lo,FXdouble hi,FXbool notify=FALSE);

  %extend {
    /// Get the slider's current range
    VALUE getRange() const {
      FXdouble lo,hi;
      self->getRange(lo,hi);
      return rb_ary_new3(2,rb_float_new(lo),rb_float_new(hi));
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
  FXdouble getIncrement() const;

  /// Change the slider's auto-increment/decrement value
  void setIncrement(FXdouble inc);

  /// Change the delta between ticks
  void setTickDelta(FXdouble dist);

  /// Get delta between ticks
  FXdouble getTickDelta() const;

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
  virtual ~FXRealSlider();
  };


DECLARE_FXOBJECT_VIRTUALS(FXRealSlider)
DECLARE_FXID_VIRTUALS(FXRealSlider)
DECLARE_FXDRAWABLE_VIRTUALS(FXRealSlider)
DECLARE_FXWINDOW_VIRTUALS(FXRealSlider)

