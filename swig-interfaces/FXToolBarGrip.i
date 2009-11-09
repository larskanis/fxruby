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

/// ToolBar Grip styles
enum {
  TOOLBARGRIP_SINGLE     = 0,             /// Single bar mode for movable toolbars
  TOOLBARGRIP_DOUBLE     = 0x00008000     /// Double bar mode for dockable toolbars
  };


class FXToolBar;

/**
 * A toolbar grip is used to move its container, a dock bar.
 * The grip draws either a single or double bar; it is customary
 * to use the single bar grip for toolbar-rearrangements only,
 * and use the double-bar when the toolbar needs to be floated
 * or docked.
 * The toolbar grip is automatically oriented properly by the
 * the toolbar widget, similar to the FXSeparator widget.
 * Holding the Control Key while dragging the grip will prevent
 * the toolbar from docking when it is near a dock site.
 */

class FXToolBarGrip : public FXDockHandler {
protected:
  FXColor activeColor;                    // Color when active
protected:
  FXToolBarGrip();
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Construct toolbar grip 
    FXToolBarGrip(FXToolBar* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TOOLBARGRIP_SINGLE,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbToolBarGrip(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Change toolbar grip to double
  void setDoubleBar(FXbool dbl=true);

  /// Return TRUE if toolbar grip is displayed as a double bar
  FXbool isDoubleBar() const;
  
  /// Set the active color
  void setActiveColor(FXColor clr);

  /// Get the active color
  FXColor getActiveColor() const;
  
  /// Destructor
  virtual ~FXToolBarGrip();
  };


DECLARE_FXOBJECT_VIRTUALS(FXToolBarGrip)
DECLARE_FXID_VIRTUALS(FXToolBarGrip)
DECLARE_FXDRAWABLE_VIRTUALS(FXToolBarGrip)
DECLARE_FXWINDOW_VIRTUALS(FXToolBarGrip)

