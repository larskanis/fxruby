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

// Spinner Options
enum {
  REALSPIN_NORMAL  =  0,                // Normal, non-cyclic
  REALSPIN_CYCLIC  =  0x00020000,       // Cyclic spinner
  REALSPIN_NOTEXT  =  0x00040000,       // No text visible
  REALSPIN_NOMAX   =  0x00080000,       // Spin all the way up to infinity
  REALSPIN_NOMIN   =  0x00100000,       // Spin all the way down to -infinity
  REALSPIN_LOG     =  0x00200000        // Logarithmic rather than linear
  };


class FXTextField;
class FXArrowButton;

%rename("granularity=")	FXRealSpinner::setGranularity(FXdouble);
%rename("granularity")	FXRealSpinner::getGranularity() const;

/// Spinner control
class FXRealSpinner : public FXPacker {
public:
  long onUpdIncrement(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdIncrement(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdDecrement(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDecrement(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdEntry(FXObject*,FXSelector,void* PTR_IGNORE);
  long onChgEntry(FXObject*,FXSelector,void* PTR_IGNORE);
  long onWheelEntry(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_IN);
  long onCmdGetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_OUT);
  long onCmdSetRealValue(FXObject*,FXSelector,void* PTR_PDOUBLE);
  long onCmdGetRealValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetRealRange(FXObject*,FXSelector,void* PTR_DBLRANGE_IN);
  long onCmdGetRealRange(FXObject*,FXSelector,void* PTR_DBLRANGE_OUT);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
public:
  enum{
    ID_INCREMENT=FXPacker::ID_LAST,
    ID_DECREMENT,
    ID_ENTRY,
    ID_LAST
    };
public:

  /// Construct a spinner
  %extend {
    FXRealSpinner(FXComposite* p,FXint cols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=REALSPIN_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbRealSpinner(p,cols,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Increment spinner
  void increment(FXbool notify=FALSE);

  /// Increment spinner by certain amount
  void incrementByAmount(FXdouble amount,FXbool notify=FALSE);

  /// Decrement spinner
  void decrement(FXbool notify=FALSE);

  /// Decrement spinner by certain amount
  void decrementByAmount(FXdouble amount,FXbool notify=FALSE);

  /// Return TRUE if in cyclic mode
  FXbool isCyclic() const;

  /// Set to cyclic mode, i.e. wrap around at maximum/minimum
  void setCyclic(FXbool cyclic);

  /// Return TRUE if text is visible
  FXbool isTextVisible() const;

  /// Set text visible flag
  void setTextVisible(FXbool shown);

  /// Return current value
  FXdouble getValue() const;

  %extend {
    /// Change the spinner's range
    void setRange(VALUE range,FXbool notify=FALSE){
      FXdouble lo,hi;
      FXRbRange2LoHi(range,lo,hi);
      self->setRange(lo,hi);
      }

    /// Get the spinner's current range
    VALUE getRange() const {
      FXdouble lo,hi;
      self->getRange(lo,hi);
      return rb_range_new(rb_float_new(lo),rb_float_new(hi),0);
      }
  }

  /// Change spinner increment
  void setIncrement(FXdouble increment);

  /// Return spinner increment
  FXdouble getIncrement() const;

  /// Change spinner granularity
  void setGranularity(FXdouble gr);

  /// Return spinner granularity
  FXdouble getGranularity() const;

  /// Set the text font
  void setFont(FXFont *fnt);

  /// Get the text font
  FXFont *getFont() const;

  /// Set the status line help text for this spinner
  void setHelpText(const FXString& text);

  /// Get the status line help text for this spinner
  const FXString& getHelpText() const;

  /// Set the tool tip message for this spinner
  void setTipText(const FXString& text);

  /// Get the tool tip message for this spinner
  const FXString& getTipText() const;

  /// Change spinner style
  void setSpinnerStyle(FXuint style);

  /// Return current spinner style
  FXuint getSpinnerStyle() const;

  /// Allow editing of the text field
  void setEditable(FXbool edit=TRUE);

  /// Return TRUE if text field is editable
  FXbool isEditable() const;

  /// Change color of the up arrow
  void setUpArrowColor(FXColor clr);

  /// Return color of the up arrow
  FXColor getUpArrowColor() const;

  /// Change color of the down arrow
  void setDownArrowColor(FXColor clr);

  /// Return color of the the down arrow
  FXColor getDownArrowColor() const;

  /// Change text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const;

  /// Change selected background color
  void setSelBackColor(FXColor clr);

  /// Return selected background color
  FXColor getSelBackColor() const;

  /// Change selected text color
  void setSelTextColor(FXColor clr);

  /// Return selected text color
  FXColor getSelTextColor() const;

  /// Changes the cursor color
  void setCursorColor(FXColor clr);

  /// Return the cursor color
  FXColor getCursorColor() const;

  /// Change width of text field in terms of number of columns * `m'
  void setNumColumns(FXint cols);

  /// Return number of columns
  FXint getNumColumns() const;

  /// Destructor
  virtual ~FXRealSpinner();
  };


DECLARE_FXOBJECT_VIRTUALS(FXRealSpinner)
DECLARE_FXID_VIRTUALS(FXRealSpinner)
DECLARE_FXDRAWABLE_VIRTUALS(FXRealSpinner)
DECLARE_FXWINDOW_VIRTUALS(FXRealSpinner)
DECLARE_FXREALSPINNER_VIRTUALS(FXRealSpinner)

