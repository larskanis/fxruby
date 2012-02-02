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

%rename("dockingSide=") FXToolBar::setDockingSide(FXuint side);
%rename("dockingSide")  FXToolBar::getDockingSide() const;


/**
 * A tool bar widget can be docked in a dock site; it automatically
 * adjusts its orientation based on the orientation of the dock site,
 * and adjusts the layout options accordingly.
 * See dock bar widget for more information on the docking behavior.
 */

class FXToolBar : public FXDockBar {
public:
  long onCmdDockFlip(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdDockFlip(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /**
     * Construct a floatable toolbar
     * Normally, the toolbar is docked under window p.
     * When floated, the toolbar can be docked under window q, which is
     * typically an FXToolBarShell window.
     */
    FXToolBar(FXComposite* p,FXComposite* q,FXuint opts=LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbToolBar(p,q,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }

    /**
     * Construct a non-floatable toolbar.
     * The toolbar can not be undocked.
     */
    FXToolBar(FXComposite* p,FXuint opts=LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=2,FXint pr=3,FXint pt=3,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbToolBar(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Set docking side
  void setDockingSide(FXuint side=LAYOUT_SIDE_TOP);

  /// Return docking side
  FXuint getDockingSide() const;

  /// Destroy
  virtual ~FXToolBar();
  };


DECLARE_FXOBJECT_VIRTUALS(FXToolBar)
DECLARE_FXID_VIRTUALS(FXToolBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXToolBar)
DECLARE_FXWINDOW_VIRTUALS(FXToolBar)
DECLARE_FXDOCKBAR_VIRTUALS(FXToolBar)

