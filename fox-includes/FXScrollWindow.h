/********************************************************************************
*                                                                               *
*                     S c r o l l W i n d o w   W i d g e t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXScrollWindow.h 2763 2007-11-19 17:37:52Z lyle $                    *
********************************************************************************/
#ifndef FXSCROLLWINDOW_H
#define FXSCROLLWINDOW_H

#ifndef FXSCROLLAREA_H
#include "FXScrollArea.h"
#endif

namespace FX {


/**
* The ScrollWindow widget manages one single child window and
* scrolls it when the child is larger than the available area.
* You can use ScrollWindow when parts of your user interface need to be
* scrollable, for example when applications may need to run on small screens.
* ScrollWindow normally contains only one single child window, which could
* be a VerticalFrame or any other widget.  It will measure this widget using
* getDefaultWidth() and getDefaultHeight() and place the scrollbars when needed,
* based on options like  HSCROLLING_ALWAYS, etc., and the options of the child
* window.
* ScrollWindow observes some layout hints of its child window: LAYOUT_FIX_WIDTH,
* LAYOUT_FIX_HEIGHT are observed at all times, while LAYOUT_FILL_X, LAYOUT_LEFT,
* LAYOUT_RIGHT, LAYOUT_CENTER_X, as well as LAYOUT_FILL_Y, LAYOUT_TOP, LAYOUT_BOTTOM,
* LAYOUT_CENTER_Y are only observed if the child window size is smaller than the
* ScrollWindow's viewport size.  If the content size is larger than the viewport size,
* the content must be scrolled normally.
* Note that this means that the child window's position is not necessarily equal to
* the scroll position of the scroll window!
*/
class FXAPI FXScrollWindow : public FXScrollArea {
  FXDECLARE(FXScrollWindow)
protected:
  FXScrollWindow(){}
  virtual void moveContents(FXint x,FXint y);
private:
  FXScrollWindow(const FXScrollWindow&);
  FXScrollWindow &operator=(const FXScrollWindow&);
public:
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onFocusSelf(FXObject*,FXSelector,void*);
public:

  /// Construct a scroll window
  FXScrollWindow(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Perform layout
  virtual void layout();

  /// Return a pointer to the contents window
  FXWindow* contentWindow() const;

  /// Return the width of the contents
  virtual FXint getContentWidth();

  /// Return the height of the contents
  virtual FXint getContentHeight();
  };

}

#endif
