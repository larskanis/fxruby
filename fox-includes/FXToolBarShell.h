/********************************************************************************
*                                                                               *
*                    T o o l   B a r   S h e l l   W i d g e t                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2003 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXToolBarShell.h 1536 2003-05-14 21:41:00Z lyle $                     *
********************************************************************************/
#ifndef FXTOOLBARSHELL_H
#define FXTOOLBARSHELL_H

#ifndef FXTOPWINDOW_H
#include "FXTopWindow.h"
#endif

namespace FX {


/**
* A Tool bar shell is a widget floating around over the Main Window.
* It typically contains an undocked tool bar.
*/
class FXAPI FXToolBarShell : public FXTopWindow {
  FXDECLARE(FXToolBarShell)
protected:
  FXColor   baseColor;
  FXColor   hiliteColor;
  FXColor   shadowColor;
  FXColor   borderColor;
  FXint     border;
protected:
  FXToolBarShell(){}
  void drawBorderRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawRaisedRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawSunkenRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawRidgeRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawGrooveRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawDoubleRaisedRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawDoubleSunkenRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawFrame(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
private:
  FXToolBarShell(const FXToolBarShell&);
  FXToolBarShell &operator=(const FXToolBarShell&);
public:
  long onPaint(FXObject*,FXSelector,void*);
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
