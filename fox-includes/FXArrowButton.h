/********************************************************************************
*                                                                               *
*                     A r r o w   B u t t o n   W i d g e t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXArrowButton.h 2335 2006-01-28 02:33:03Z lyle $                     *
********************************************************************************/
#ifndef FXARROWBUTTON_H
#define FXARROWBUTTON_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


// Arrow style options
enum {
  ARROW_NONE     = 0,		// No arrow
  ARROW_UP       = 0x00080000,	// Arrow points up
  ARROW_DOWN     = 0x00100000,	// Arrow points down
  ARROW_LEFT     = 0x00200000,	// Arrow points left
  ARROW_RIGHT    = 0x00400000,	// Arrow points right
  ARROW_AUTO     = 0x00800000,  // Automatically fire when hovering mouse over button
  ARROW_REPEAT   = 0x01000000,	// Button repeats if held down
  ARROW_AUTOGRAY = 0x02000000,	// Automatically gray out when not updated
  ARROW_AUTOHIDE = 0x04000000,	// Automatically hide when not updated
  ARROW_TOOLBAR  = 0x08000000,	// Button is toolbar-style
  ARROW_NORMAL   = FRAME_RAISED|FRAME_THICK|ARROW_UP
  };


/**
* Button with an arrow; the arrow can point in any direction.
* When clicked, the arrow button sends a SEL_COMMAND to its target.
* When ARROW_REPEAT is passed, the arrow button sends a SEL_COMMAND
* repeatedly while the button is pressed.
* The option ARROW_AUTO together with ARROW_REPEAT makes the arrow
* button work in repeat mode simply by hovering the cursor over it.
*/
class FXAPI FXArrowButton : public FXFrame {
  FXDECLARE(FXArrowButton)
protected:
  FXColor   arrowColor;     // Arrow color
  FXint     arrowSize;      // Arrow size
  FXString  tip;            // Tooltip value
  FXString  help;           // Help value
  FXbool    state;          // State of button
  FXbool    fired;          // Timer has fired
protected:
  FXArrowButton();
private:
  FXArrowButton(const FXArrowButton&);
  FXArrowButton &operator=(const FXArrowButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUpdate(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onRepeat(FXObject*,FXSelector,void*);
  long onAuto(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:
  enum {
    ID_REPEAT=FXFrame::ID_LAST,
    ID_AUTO,
    ID_LAST
    };
public:

  /// Construct arrow button
  FXArrowButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=ARROW_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Get default width
  virtual FXint getDefaultWidth();

  /// Get default height
  virtual FXint getDefaultHeight();

  /// Enable the button
  virtual void enable();

  /// Disable the button
  virtual void disable();

  /// Returns true because a button can receive focus
  virtual bool canFocus() const;

  /// Set the button state (where TRUE means the button is down)
  void setState(FXbool s);

  /// Get the button state (where TRUE means the button is down)
  FXbool getState() const { return state; }

  /// Set status line help text for this arrow button
  void setHelpText(const FXString& text){ help=text; }

  /// Get status line help text for this arrow button
  const FXString& getHelpText() const { return help; }

  /// Set tool tip message for this arrow button
  void setTipText(const FXString& text){ tip=text; }

  /// Get tool tip message for this arrow button
  const FXString& getTipText() const { return tip; }

  /// Set the arrow style flags
  void setArrowStyle(FXuint style);

  /// Get the arrow style flags
  FXuint getArrowStyle() const;

  /// Set the default arrow size
  void setArrowSize(FXint size);

  /// Get the default arrow size
  FXint getArrowSize() const { return arrowSize; }

  /// Set the current justification mode.
  void setJustify(FXuint mode);

  /// Get the current justification mode.
  FXuint getJustify() const;

  /// Get the fill color for the arrow
  FXColor getArrowColor() const { return arrowColor; }

  /// Set the fill color for the arrow
  void setArrowColor(FXColor clr);

  /// Save label to a stream
  virtual void save(FXStream& store) const;

  /// Load label from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXArrowButton();
  };

}

#endif
