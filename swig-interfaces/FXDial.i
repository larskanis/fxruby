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

// Dial style options
enum {
  DIAL_VERTICAL   = 0,                            // Vertically oriented
  DIAL_HORIZONTAL = 0x00008000,                   // Horizontal oriented
  DIAL_CYCLIC     = 0x00010000,                   // Value wraps around
  DIAL_HAS_NOTCH  = 0x00020000,                   // Dial has a Center Notch
  DIAL_NORMAL     = DIAL_VERTICAL
  };


/// Dial
class FXDial : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdSetRealValue(FXObject*,FXSelector,void* PTR_PDOUBLE);
  long onCmdGetRealValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
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
  %extend {
    /// Construct a dial widget
    FXDial(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=DIAL_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbDial(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set the dial value
  void setValue(FXint value,FXbool notify=FALSE);

  /// Return the dial value
  FXint getValue() const;

  %extend {
    /// Change the dial's range
    void setRange(VALUE range, FXbool notify=FALSE){
      FXint lo,hi;
      FXRbRange2LoHi(range,lo,hi);
      self->setRange(lo,hi,notify);
      }

    /// Obtain the current range of the dial
    VALUE getRange() const {
      FXint lo,hi;
      self->getRange(lo,hi);
      return rb_range_new(INT2NUM(lo),INT2NUM(hi),0);
      }
  }

  /**
  * Set the revolution increment, which is the amount of change
  * in the position for revolution of the dial; the dial may go
  * through multiple revolutions to go through its whole range;
  * by default it takes one 360 degree turn of the dial to go
  * from the lower to the upper range.
  */
  void setRevolutionIncrement(FXint i);

  /// Get the current value of the revolution increment
  FXint getRevolutionIncrement() const;

  /**
  * Change the spacing for the small notches; this should be set
  * in tenths of degrees in the range [1,3600], and the value should
  * be a divisor of 3600, so as to make the notches come out evenly
  */
  void setNotchSpacing(FXint spacing);

  /// Get the current notch spacing
  FXint getNotchSpacing() const;

  /**
  * Change the notch offset, which is the position of the
  * center notch; the value should be tenths of degrees
  * in the range [-3600,3600]
  */
  void setNotchOffset(FXint offset);

  /// Get the current center notch offset
  FXint getNotchOffset() const;

  /// Changes the dial style.
  void setDialStyle(FXuint opts);

  /// Get the current dial style.
  FXuint getDialStyle() const;

  /// Change the center notch color
  void setNotchColor(FXColor clr);

  /// Get the current center notch color
  FXColor getNotchColor() const;

  /// Set the help text to be displayed on the status line
  void setHelpText(const FXString& text);

  /// Get the current help text
  const FXString& getHelpText() const;

  /// Set the tip text to be displayed in the tooltip
  void setTipText(const FXString& text);

  /// Get the current tooltip text value
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXDial();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDial)
DECLARE_FXID_VIRTUALS(FXDial)
DECLARE_FXDRAWABLE_VIRTUALS(FXDial)
DECLARE_FXWINDOW_VIRTUALS(FXDial)

