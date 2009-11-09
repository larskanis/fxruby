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

%rename("wrapGalleys=") FXDockSite::wrapGalleys(FXbool);
%rename("wrapGalleys?") FXDockSite::wrapGalleys() const;

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
class FXDockSite : public FXPacker {
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

  %extend {
    /**
    * Construct a toolbar dock layout manager.  Passing LAYOUT_SIDE_TOP or LAYOUT_SIDE_BOTTOM
    * causes the toolbar dock to be oriented horizontally.  Passing LAYOUT_SIDE_LEFT or
    * LAYOUT_SIDE_RIGHT causes it to be oriented vertically.
    */
    FXDockSite(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0,FXint hs=0,FXint vs=0){
      return new FXRbDockSite(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
  }
  
  /// Change wrap option
  void wrapGalleys(FXbool wrap);

  /// Get wrap option
  FXbool wrapGalleys() const;

  // Destroy
  virtual ~FXDockSite();
  };

DECLARE_FXOBJECT_VIRTUALS(FXDockSite)
DECLARE_FXID_VIRTUALS(FXDockSite)
DECLARE_FXDRAWABLE_VIRTUALS(FXDockSite)
DECLARE_FXWINDOW_VIRTUALS(FXDockSite)
DECLARE_FXDOCKSITE_VIRTUALS(FXDockSite)

