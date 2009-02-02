/********************************************************************************
*                                                                               *
*                    T o o l   B a r   S h e l l   W i d g e t                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXToolBarShell.h 2767 2007-11-19 18:33:06Z lyle $                    *
********************************************************************************/
#ifndef FXTOOLBARSHELL_H
#define FXTOOLBARSHELL_H

#ifndef FXTOPWINDOW_H
#include "FXTopWindow.h"
#endif

namespace FX {


/**
* A Toolbar shell is a widget floating around over the Main Window.
* It typically contains an undocked tool bar.  The Toolbar shell can
* be resized horizontally by grabbing its sides if the widget contained
* in the Toolbar shell has the LAYOUT_FIX_WIDTH option.  Likewise, it
* can be resized vertically if the LAYOUT_FIX_HEIGHT option is passed
* to the widget contained in the Toolbar shell.  If both LAYOUT_FIX_WIDTH
* and LAYOUT_FIX_HEIGHT are passed to the contained widget, Toolbar shell
* can also be resized by grabbing the corners.
* Normally, the Toolbar shell tries to accomodate changes in its contained
* widget by shrink-wrapping around it, i.e. if the contained widget changes,
* the Toolbar shell will change to fit narrowly around it.
*/
class FXAPI FXToolBarShell : public FXTopWindow {
  FXDECLARE(FXToolBarShell)
protected:
  FXColor   baseColor;          // Base color
  FXColor   hiliteColor;        // Highlight color
  FXColor   shadowColor;        // Shadow color
  FXColor   borderColor;        // Border color
  FXint     border;             // Border width
  FXint     gripx;              // Grip offset x
  FXint     gripy;              // Grip offset y
  FXint     xopp;               // Opposite x
  FXint     yopp;               // Opposite y
  FXuchar   mode;               // Dragging mode
protected:
  static const FXDefaultCursor cursorType[16];
private:
  FXToolBarShell(const FXToolBarShell&);
  FXToolBarShell &operator=(const FXToolBarShell&);
protected:
  FXToolBarShell();
  FXuchar where(FXint x,FXint y) const;
  void drawBorderRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawRaisedRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawSunkenRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawRidgeRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawGrooveRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawDoubleRaisedRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawDoubleSunkenRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawFrame(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
protected:
  enum {
    DRAG_NONE        = 0,
    DRAG_TOP         = 1,
    DRAG_BOTTOM      = 2,
    DRAG_LEFT        = 4,
    DRAG_RIGHT       = 8,
    DRAG_TOPLEFT     = (DRAG_TOP|DRAG_LEFT),
    DRAG_TOPRIGHT    = (DRAG_TOP|DRAG_RIGHT),
    DRAG_BOTTOMLEFT  = (DRAG_BOTTOM|DRAG_LEFT),
    DRAG_BOTTOMRIGHT = (DRAG_BOTTOM|DRAG_RIGHT),
    DRAG_WHOLE       = (DRAG_TOP|DRAG_BOTTOM|DRAG_LEFT|DRAG_RIGHT)
    };
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onLayout(FXObject*,FXSelector,void*);
public:

  /// Construct a toolbar shell
  FXToolBarShell(FXWindow* owner,FXuint opts=FRAME_RAISED|FRAME_THICK,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint hs=4,FXint vs=4);

  /// Create server-side resources
  virtual void create();

  /// Perform layout
  virtual void layout();

  /// Return the default width of this window
  virtual FXint getDefaultWidth();

  /// Return the default height of this window
  virtual FXint getDefaultHeight();

  /// Change frame style
  void setFrameStyle(FXuint style);

  /// Get current frame style
  FXuint getFrameStyle() const;

  /// Get border width
  FXint getBorderWidth() const { return border; }

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Get highlight color
  FXColor getHiliteColor() const { return hiliteColor; }

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Get shadow color
  FXColor getShadowColor() const { return shadowColor; }

  /// Change border color
  void setBorderColor(FXColor clr);

  /// Get border color
  FXColor getBorderColor() const { return borderColor; }

  /// Change base gui color
  void setBaseColor(FXColor clr);

  /// Get base gui color
  FXColor getBaseColor() const { return baseColor; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
