/********************************************************************************
*                                                                               *
*                       S c r o l l A r e a   W i d g e t                       *
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
* $Id: FXScrollArea.h 2725 2007-11-16 16:57:54Z lyle $                      *
********************************************************************************/
#ifndef FXSCROLLAREA_H
#define FXSCROLLAREA_H

#ifndef FXCOMPOSITE_H
#include "FXComposite.h"
#endif

namespace FX {


/// Scrollbar options
enum {
  SCROLLERS_NORMAL     = 0,                                 /// Show the scrollbars when needed
  HSCROLLER_ALWAYS     = 0x00008000,                        /// Always show horizontal scrollers
  HSCROLLER_NEVER      = 0x00010000,                        /// Never show horizontal scrollers
  VSCROLLER_ALWAYS     = 0x00020000,                        /// Always show vertical scrollers
  VSCROLLER_NEVER      = 0x00040000,                        /// Never show vertical scrollers
  HSCROLLING_ON        = 0,                                 /// Horizontal scrolling turned on (default)
  HSCROLLING_OFF       = HSCROLLER_NEVER|HSCROLLER_ALWAYS,  /// Horizontal scrolling turned off
  VSCROLLING_ON        = 0,                                 /// Vertical scrolling turned on (default)
  VSCROLLING_OFF       = VSCROLLER_NEVER|VSCROLLER_ALWAYS,  /// Vertical scrolling turned off
  SCROLLERS_TRACK      = 0,                                 /// Scrollers track continuously for smooth scrolling
  SCROLLERS_DONT_TRACK = 0x00080000                         /// Scrollers don't track continuously
  };


class FXScrollBar;
class FXScrollCorner;


/**
* The scroll area widget manages a content area and a viewport
* area through which the content is viewed.  When the content area
* becomes larger than the viewport area, scrollbars are placed to
* permit viewing of the entire content by scrolling the content.
* Depending on the mode, scrollbars may be displayed on an as-needed
* basis, always, or never.
* Normally, the scroll area's size and the content's size are independent;
* however, it is possible to disable scrolling in the horizontal
* (vertical) direction.  In this case, the content width (height)
* will influence the width (height) of the scroll area widget.
* For content which is time-consuming to repaint, continuous
* scrolling may be turned off.
*/
class FXAPI FXScrollArea : public FXComposite {
  FXDECLARE(FXScrollArea)
protected:
  FXScrollBar    *horizontal;   // Horizontal scroll bar
  FXScrollBar    *vertical;     // Vertical scroll bar
  FXScrollCorner *corner;       // Scroll corner
  FXint           pos_x;        // X scroll position (pos_x<=0)
  FXint           pos_y;        // Y scroll position (pos_y<=0)
protected:
  FXScrollArea();
  FXScrollArea(FXComposite* p,FXuint opts,FXint x,FXint y,FXint w,FXint h);
  virtual void moveContents(FXint x,FXint y);
  FXbool startAutoScroll(FXEvent *event,FXbool onlywheninside=false);
  void stopAutoScroll();
  void placeScrollBars(FXint vw,FXint vh);
private:
  FXScrollArea(const FXScrollArea&);
  FXScrollArea &operator=(const FXScrollArea&);
public:
  long onHMouseWheel(FXObject*,FXSelector,void*);
  long onVMouseWheel(FXObject*,FXSelector,void*);
  long onHScrollerChanged(FXObject*,FXSelector,void*);
  long onVScrollerChanged(FXObject*,FXSelector,void*);
  long onHScrollerDragged(FXObject*,FXSelector,void*);
  long onVScrollerDragged(FXObject*,FXSelector,void*);
  long onAutoScroll(FXObject*,FXSelector,void*);
public:

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /// Return content area x position
  FXint getContentX() const { return pos_x; }

  /// Return content area y position
  FXint getContentY() const { return pos_y; }

  /// Return content area width
  virtual FXint getContentWidth();

  /// Return content area height
  virtual FXint getContentHeight();

  /// Return visible scroll-area x position
  virtual FXint getVisibleX() const;

  /// Return visible scroll-area y position
  virtual FXint getVisibleY() const;

  /// Return visible scroll-area width
  virtual FXint getVisibleWidth() const;

  /// Return visible scroll-area height
  virtual FXint getVisibleHeight() const;

  /// Return true if horizontally scrollable
  FXbool isHorizontalScrollable() const;

  /// Return true if vertically scrollable
  FXbool isVerticalScrollable() const;

  /// Change scroll style
  void setScrollStyle(FXuint style);

  /// Return scroll style
  FXuint getScrollStyle() const;

  /// Return a pointer to the horizontal scrollbar
  FXScrollBar* horizontalScrollBar() const { return horizontal; }

  /// Return a pointer to the vertical scrollbar
  FXScrollBar* verticalScrollBar() const { return vertical; }

  /// Set the current position
  void setPosition(FXint x,FXint y);

  /// Get the current position
  void getPosition(FXint& x,FXint& y) const { x=pos_x; y=pos_y; }

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXScrollArea();
  };

}

#endif
