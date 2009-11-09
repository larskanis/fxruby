/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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

%rename("docked?")       FXDockBar::isDocked() const;
%rename("insideDock?")   FXDockBar::insideDock(FXDockSite* docksite,FXint barx,FXint bary);
%rename("dryDock=")      FXDockBar::setDryDock(FXComposite* dry);
%rename("dryDock")       FXDockBar::getDryDock() const;
%rename("wetDock=")      FXDockBar::setWetDock(FXComposite* wet);
%rename("wetDock")       FXDockBar::getWetDock() const;
%rename("allowedSides=") FXDockBar::allowedSides(FXuchar allow);

/**
* A dock bar widget can be docked inside a dock site widget, or floated
* around freely.  Users can move, undock, and dock the dock bar widget
* by means of a handle such as a tool bar grip.  When docking, the dock
* bar sends a SEL_DOCKED message to its target; when undocking, it sends
* a SEL_FLOATED message.  In either case the dock site involved is passed
* in the void* pointer argument of the message.
*/
class FXDockBar : public FXPacker {
protected:
  FXComposite *drydock;	        // Parent when docked
  FXComposite *wetdock;	        // Parent when floating
  FXint        gripx;           // Grip offset x
  FXint        gripy;           // Grip offset y
  FXuchar      allowed;         // Where we're allowed to dock
protected:
  FXDockBar();
  FXbool isAllowable(FXuint hints) const;
public:
  long onCmdUndock(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdUndock(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDockTop(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDockTop(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDockBottom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDockBottom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDockLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDockLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDockRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDockRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDockFlip(FXObject*,FXSelector,void* PTR_IGNORE);
  long onBeginDragGrip(FXObject*,FXSelector,void* PTR_EVENT);
  long onEndDragGrip(FXObject*,FXSelector,void* PTR_EVENT);
  long onDraggedGrip(FXObject*,FXSelector,void* PTR_EVENT);
  long onPopupMenu(FXObject*,FXSelector,void* PTR_EVENT);
  long onDockTimer(FXObject*,FXSelector,void* PTR_DOCKSITE);  // FIXME
public:
  enum {
    ID_DOCK_FLOAT=FXPacker::ID_LAST,    /// Undock the dock bar
    ID_DOCK_TOP,                        /// Dock on the top
    ID_DOCK_BOTTOM,                     /// Dock on the bottom
    ID_DOCK_LEFT,                       /// Dock on the left
    ID_DOCK_RIGHT,                      /// Dock on the right
    ID_DOCK_FLIP,                       /// Flip orientation
    ID_TOOLBARGRIP,                     /// Tool bar grip
    ID_TIMER,
    ID_LAST
    };
public:
  enum {
    ALLOW_NOWHERE=0,                                    /// Don't allow docking anywhere
    ALLOW_TOP=1,                                        /// Docking at the top only
    ALLOW_BOTTOM=2,                                     /// Docking at the bottom only
    ALLOW_LEFT=4,                                       /// Docking at the left only
    ALLOW_RIGHT=8,                                      /// Docking at the right only
    ALLOW_HORIZONTAL=ALLOW_TOP|ALLOW_BOTTOM,            /// Docking at the top and bottom
    ALLOW_VERTICAL=ALLOW_LEFT|ALLOW_RIGHT,              /// Docking at the left and right
    ALLOW_EVERYWHERE=ALLOW_HORIZONTAL|ALLOW_VERTICAL    /// Docking can be everywhere
    };
public:

  %extend {
    /**
    * Construct a floatable dock bar, with a default parent p and an
    * alternate parent q.  To allow docking and dragging the default parent
    * p must be of type FXDockSite, and the alternate parent q must be of
    * type FXToolBarShell.
    * Normally, the dock bar is docked under a window p of type FXDockSite.
    * When floated, the toolbar can be docked under window q, which is
    * usually an kind of FXToolBarShell window.
    */
    FXDockBar(FXComposite* p,FXComposite* q,FXuint opts=LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbDockBar(p,q,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }

    /**
    * Construct a non-floatable dock bar.
    * The dock bar can not be undocked.
    */
    FXDockBar(FXComposite* p,FXuint opts,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=2,FXint pr=3,FXint pt=3,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbDockBar(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
  }

  /// Return true if docked
  FXbool isDocked() const;

  /**
   * Check if the dock bar would dock or undock if at locaton barx, bary.
   */
  FXbool insideDock(FXDockSite* docksite,FXint barx,FXint bary);

  /**
  * Set parent when docked.
  * If it was docked, reparent under the new docking window.
  */
  void setDryDock(FXComposite* dry);

  /**
  * Set parent when floating.
  * If it was undocked, then reparent under the new floating window.
  */
  void setWetDock(FXComposite* wet);

  /// Return parent when docked
  FXComposite* getDryDock() const;

  /// Return parent when floating
  FXComposite* getWetDock() const;

  /// Search for dock against given side of main window
  FXDockSite* findDockAtSide(FXuint side=LAYOUT_SIDE_TOP);

  /// Search for dock close to coordinates rootx, rooty
  FXDockSite* findDockNear(FXint rootx,FXint rooty);

  /**
  * Change set of sides (a combination of ALLOW_TOP, ALLOW_LEFT, etc.), 
  * where docking is allowed. The default is to allow docking on all sides.
  */
  void allowedSides(FXuchar allow);

  /**
  * Return set of sides where docking is allowed
  */
  FXuchar allowedSides() const;

  /// Destroy
  virtual ~FXDockBar();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDockBar)
DECLARE_FXID_VIRTUALS(FXDockBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXDockBar)
DECLARE_FXWINDOW_VIRTUALS(FXDockBar)
DECLARE_FXDOCKBAR_VIRTUALS(FXDockBar)

%{
static swig_type_info *FXDockBar_dynamic_cast(void **ptr) {
    FXDockBar **ppDockBar = reinterpret_cast<FXDockBar **>(ptr);
    FXToolBar *pToolBar=dynamic_cast<FXToolBar*>(*ppDockBar);
    if(pToolBar){
      *ptr=reinterpret_cast<void*>(pToolBar);
      return SWIG_TypeQuery("FXToolBar *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXDockBar, FXDockBar_dynamic_cast);

