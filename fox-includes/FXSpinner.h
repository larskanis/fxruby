/********************************************************************************
*                                                                               *
*                        S p i n   B u t t o n   W i d g e t                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Lyle Johnson.   All Rights Reserved.               *
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
* $Id: FXSpinner.h 2343 2006-02-12 20:26:26Z lyle $                         *
********************************************************************************/
#ifndef FXSPINNER_H
#define FXSPINNER_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/// Spinner Options
enum {
  SPIN_NORMAL  =  0,                /// Normal, non-cyclic
  SPIN_CYCLIC  =  0x00020000,       /// Cyclic spinner
  SPIN_NOTEXT  =  0x00040000,       /// No text visible
  SPIN_NOMAX   =  0x00080000,       /// Spin all the way up to infinity
  SPIN_NOMIN   =  0x00100000        /// Spin all the way down to -infinity
  };


class FXTextField;
class FXArrowButton;


/// Spinner control
class FXAPI FXSpinner : public FXPacker {
  FXDECLARE(FXSpinner)
protected:
  FXTextField   *textField;         // Text field
  FXArrowButton *upButton;          // The up button
  FXArrowButton *downButton;        // The down button
  FXint          range[2];          // Reported data range
  FXint          incr;              // Increment
  FXint          pos;               // Current position
protected:
  FXSpinner();
private:
  FXSpinner(const FXSpinner&);
  FXSpinner& operator=(const FXSpinner&);
public:
  long onUpdIncrement(FXObject*,FXSelector,void*);
  long onCmdIncrement(FXObject*,FXSelector,void*);
  long onUpdDecrement(FXObject*,FXSelector,void*);
  long onCmdDecrement(FXObject*,FXSelector,void*);
  long onCmdEntry(FXObject*,FXSelector,void*);
  long onChgEntry(FXObject*,FXSelector,void*);
  long onWheelEntry(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdSetIntRange(FXObject*,FXSelector,void*);
  long onCmdGetIntRange(FXObject*,FXSelector,void*);
  long onFocusSelf(FXObject*,FXSelector,void*);
public:
  enum{
    ID_INCREMENT=FXPacker::ID_LAST,
    ID_DECREMENT,
    ID_ENTRY,
    ID_LAST
    };
public:

  /// Construct a spinner
  FXSpinner(FXComposite *p,FXint cols,FXObject *tgt=NULL,FXSelector sel=0,FXuint opts=SPIN_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Perform layout
  virtual void layout();

  /// Disable spinner
  virtual void disable();

  /// Enable spinner
  virtual void enable();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

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

  /// Change current value
  virtual void setValue(FXint value,FXbool notify=FALSE);

  /// Return current value
  FXint getValue() const { return pos; }

  /// Change the spinner's range
  void setRange(FXint lo,FXint hi,FXbool notify=FALSE);

  /// Get the spinner's current range
  void getRange(FXint& lo,FXint& hi) const { lo=range[0]; hi=range[1]; }

  /// Change spinner increment
  void setIncrement(FXint increment);

  /// Return spinner increment
  FXint getIncrement() const { return incr; }

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

  /// Save spinner to a stream
  virtual void save(FXStream& store) const;

  /// Load spinner from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXSpinner();
  };

}

#endif
