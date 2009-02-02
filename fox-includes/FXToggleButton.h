/********************************************************************************
*                                                                               *
*                   T o g g l e    B u t t o n    W i d g e t                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXToggleButton.h 2343 2006-02-12 20:26:26Z lyle $                    *
********************************************************************************/
#ifndef FXTOGGLEBUTTON_H
#define FXTOGGLEBUTTON_H

#ifndef FXLABEL_H
#include "FXLabel.h"
#endif

namespace FX {


/// Toggle button flags
enum {
  TOGGLEBUTTON_AUTOGRAY = 0x00800000,       /// Automatically gray out when not updated
  TOGGLEBUTTON_AUTOHIDE = 0x01000000,       /// Automatically hide toggle button when not updated
  TOGGLEBUTTON_TOOLBAR  = 0x02000000,       /// Toolbar style toggle button [flat look]
  TOGGLEBUTTON_KEEPSTATE= 0x04000000,       /// Draw button according to state
  TOGGLEBUTTON_NORMAL   = FRAME_RAISED|FRAME_THICK|JUSTIFY_NORMAL|ICON_BEFORE_TEXT
  };


/**
* The toggle button provides a two-state button, which toggles between the
* on and the off state each time it is pressed.  For each state, the toggle
* button has a unique icon and text label.
* When pressed, the button widget sends a SEL_COMMAND to its target, with the
* message data set to the current state of the toggle button, of the type FXbool.
*/
class FXAPI FXToggleButton : public FXLabel {
  FXDECLARE(FXToggleButton)
protected:
  FXString  altlabel;
  FXIcon   *alticon;
  FXHotKey  althotkey;
  FXint     althotoff;
  FXString  alttip;
  FXString  althelp;
  FXbool    state;
  FXbool    down;
protected:
  FXToggleButton();
  void press(FXbool dn);
private:
  FXToggleButton(const FXToggleButton&);
  FXToggleButton& operator=(const FXToggleButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUpdate(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
  long onCheck(FXObject*,FXSelector,void*);
  long onUncheck(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
public:

  /// Construct toggle button with two text labels, and two icons, one for each state
  FXToggleButton(FXComposite* p,const FXString& text1,const FXString& text2,FXIcon* icon1=NULL,FXIcon* icon2=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TOGGLEBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Returns true because a toggle button can receive focus
  virtual bool canFocus() const;

  /// Get default width
  virtual FXint getDefaultWidth();

  /// Get default height
  virtual FXint getDefaultHeight();

  /// Change alternate text shown when toggled
  void setAltText(const FXString& text);

  /// Return alternate text
  FXString getAltText() const { return altlabel; }

  /// Change alternate icon shown when toggled
  void setAltIcon(FXIcon* ic);

  /// Return alternate icon
  FXIcon* getAltIcon() const { return alticon; }

  /// Change toggled state
  void setState(FXbool s=TRUE,FXbool notify=FALSE);

  /// return toggled state
  FXbool getState() const { return state; }

  /// Change alternate help text shown when toggled
  void setAltHelpText(const FXString& text);

  /// Return alternate help text
  FXString getAltHelpText() const { return althelp; }

  /// Change alternate tip text shown when toggled
  void setAltTipText(const FXString& text);

  /// Return alternate tip text
  FXString getAltTipText() const { return alttip; }

  /// Set the toggle button style flags
  void setToggleStyle(FXuint style);

  /// Get the toggle button style flags
  FXuint getToggleStyle() const;

  /// Save toggle button to a stream
  virtual void save(FXStream& store) const;

  /// Load toggle button from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXToggleButton();
  };

}

#endif
