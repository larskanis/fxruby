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
  SPIN_NORMAL  =  0,                // Normal, non-cyclic
  SPIN_CYCLIC  =  0x00020000,       // Cyclic spinner
  SPIN_NOTEXT  =  0x00040000,       // No text visible
  SPIN_NOMAX   =  0x00080000,       // Spin all the way up to infinity
  SPIN_NOMIN   =  0x00100000        // Spin all the way down to -infinity
  };


class FXTextField;
class FXArrowButton;



/// Spinner control
class FXSpinner : public FXPacker {
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
    FXSpinner(FXComposite* p,FXint cols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=SPIN_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbSpinner(p,cols,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Increment spinner
  void increment(FXbool notify=FALSE);

  /// Increment spinner by certain amount
  void incrementByAmount(FXint amount,FXbool notify=FALSE);

  /// Decrement spinner
  void decrement(FXbool notify=FALSE);

  /// Decrement spinner by certain amount
  void decrementByAmount(FXint amount, FXbool notify=FALSE);

  /// Return TRUE if in cyclic mode
  FXbool isCyclic() const;

  /// Set to cyclic mode, i.e. wrap around at maximum/minimum
  void setCyclic(FXbool cyclic);

  /// Return TRUE if text is visible
  FXbool isTextVisible() const;

  /// Set text visible flag
  void setTextVisible(FXbool shown);

  /// Return current value
  FXint getValue() const;

  %extend {
    /// Change the spinner's range
    void setRange(VALUE range,FXbool notify=FALSE){
      FXint lo,hi;
      FXRbRange2LoHi(range,lo,hi);
      self->setRange(lo,hi);
      }

    /// Get the spinner's current range
    VALUE getRange() const {
      FXint lo,hi;
      self->getRange(lo,hi);
      return rb_range_new(INT2NUM(lo),INT2NUM(hi),0);
      }
  }

  /// Change spinner increment
  void setIncrement(FXint increment);

  /// Return spinner increment
  FXint getIncrement() const;

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
  virtual ~FXSpinner();
  };


DECLARE_FXOBJECT_VIRTUALS(FXSpinner)
DECLARE_FXID_VIRTUALS(FXSpinner)
DECLARE_FXDRAWABLE_VIRTUALS(FXSpinner)
DECLARE_FXWINDOW_VIRTUALS(FXSpinner)
DECLARE_FXSPINNER_VIRTUALS(FXSpinner)

