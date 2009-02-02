/********************************************************************************
*                                                                               *
*                         D o c k S i t e   W i d g e t                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDockSite.h 2725 2007-11-16 16:57:54Z lyle $                        *
********************************************************************************/
#ifndef FXDOCKSITE_H
#define FXDOCKSITE_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


class FXDockBar;

/// Dock site options
enum {
  DOCKSITE_WRAP    = 0,           /// Dockbars are wrapped to another galley when not enough space on current galley
  DOCKSITE_NO_WRAP = 0x00020000   /// Never wrap dockbars to another galley even if not enough space
  };


/**
* The dock site widget is a widget where dock bars can be docked.
* Dock site widgets are typically embedded inside the main window, placed
* against those sides where docking of toolbars is to be allowed.
* Dock bars placed inside a dock site are laid out in horizontal or vertical bands
* called galleys.  A toolbar with the LAYOUT_DOCK_SAME hint is preferentially placed
* on the same galley as its previous sibling.  A dock bar with the LAYOUT_DOCK_NEXT is
* always placed on the next galley.
* Each galley will have at least one dock bar shown in it.  Several dock bars
* may be placed side-by-side inside one galley, unless there is insufficient
* room.  If there is insufficient room to place another dock bar, that dock bar
* will be moved to the next galley, even though its LAYOUT_DOCK_NEXT option
* is not set.  This implies that when the main window is resized and more room
* becomes available, it will jump back to its preferred galley.
* Within a galley, dock bars will be placed from left to right, at the given
* x and y coordinates, with the constraints that the dock bar will stay within
* the galley, and do not overlap each other.  It is possible to use LAYOUT_FILL_X
* and/or LAYOUT_FILL_Y to stretch a toolbar to the available space on its galley.
* The galleys are oriented horizontally if the dock site is placed inside
* a top level window using LAYOUT_SIDE_TOP or LAYOUT_SIDE_BOTTOM, and
* vertically oriented if placed with LAYOUT_SIDE_LEFT or LAYOUT_SIDE_RIGHT.
*/
class FXAPI FXDockSite : public FXPacker {
  FXDECLARE(FXDockSite)
protected:
//  FXuchar      mode;            // Dragging mode
protected:
//  static const FXDefaultCursor cursorType[16];
private:
  FXDockSite(const FXDockSite&);
  FXDockSite &operator=(const FXDockSite&);
protected:
  FXDockSite(){}
  void moveVerBar(FXWindow*& begin,FXWindow*& end,FXWindow* bar,FXint barx,FXint bary,FXint barw,FXint barh,FXbool hop);
  void moveHorBar(FXWindow*& begin,FXWindow*& end,FXWindow* bar,FXint barx,FXint bary,FXint barw,FXint barh,FXbool hop);
  void galleyOfHorzBar(FXWindow *bar,FXWindow*& begin,FXWindow*& end) const;
  void galleyOfVertBar(FXWindow *bar,FXWindow*& begin,FXWindow*& end) const;
  FXint galleyWidth(FXWindow* begin,FXWindow*& end,FXint space,FXint& require,FXint& expand) const;
  FXint galleyHeight(FXWindow* begin,FXWindow*& end,FXint space,FXint& require,FXint& expand) const;
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
    DRAG_BOTTOMRIGHT = (DRAG_BOTTOM|DRAG_RIGHT)
    };
public:
//  long onEnter(FXObject*,FXSelector,void*);
//  long onLeave(FXObject*,FXSelector,void*);
//  long onMotion(FXObject*,FXSelector,void*);
//  long onLeftBtnPress(FXObject*,FXSelector,void*);
//  long onLeftBtnRelease(FXObject*,FXSelector,void*);
public:

  /**
  * Construct a toolbar dock layout manager.  Passing LAYOUT_SIDE_TOP or LAYOUT_SIDE_BOTTOM
  * causes the toolbar dock to be oriented horizontally.  Passing LAYOUT_SIDE_LEFT or
  * LAYOUT_SIDE_RIGHT causes it to be oriented vertically.
  */
  FXDockSite(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0,FXint hs=0,FXint vs=0);

  /**
  * Return default width.  This is the width the toolbar
  * dock would have if no toolbars need to be moved to other
  * galleys than they would be logically placed.
  */
  virtual FXint getDefaultWidth();

  /**
  * Return default height.  This is the height the toolbar
  * dock would have if no toolbars need to be moved to other
  * galleys than they would be logically placed.
  */
  virtual FXint getDefaultHeight();

  /**
  * For a vertically oriented dock site, this computes
  * the total width of all the galleys based on any "wrapping"
  * needed to fit the toolbars on a galley.
  */
  virtual FXint getWidthForHeight(FXint h);

  /**
  * For a horizontally oriented dock site, this computes
  * the total height of all the galleys based on any "wrapping"
  * needed to fit the toolbars on a galley.
  */
  virtual FXint getHeightForWidth(FXint w);

  /// Perform layout
  virtual void layout();

  /// Resize toolbar
  virtual void resizeToolBar(FXDockBar* bar,FXint barx,FXint bary,FXint barw,FXint barh);

  /**
  * Move tool bar, changing its options to suite the new position.
  * Used by the toolbar dragging to rearrange the toolbars inside the
  * toolbar dock.
  */
  virtual void moveToolBar(FXDockBar* bar,FXint barx,FXint bary);

  /**
  * The dock site is notified that the given bar has been added
  * logically before the other window, and is to placed on a new
  * galley all by itself.  The default implementation adjusts
  * the layout options of the bars accordingly.
  */
  virtual void dockToolBar(FXDockBar* bar,FXWindow* other);

  /**
  * The dock site is informed that the given bar has been docked
  * at the given coordinates.  The default implementation determines
  * where to insert the newly docked bar and adjusts the layout
  * options of the bars accordingly.
  */
  virtual void dockToolBar(FXDockBar* bar,FXint barx,FXint bary);

  /**
  * The dock site is informed that the given bar has been removed.
  * In the default implementation, the dock site fixes the layout
  * options of the remaining bars so they stay in the same place
  * if possible.
  */
  virtual void undockToolBar(FXDockBar* bar);

  /// Change wrap option
  void wrapGalleys(FXbool wrap);

  /// Get wrap option
  FXbool wrapGalleys() const;
  };

}

#endif
