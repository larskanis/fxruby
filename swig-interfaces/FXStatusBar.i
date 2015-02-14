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

/// StatusBar options
enum {
  STATUSBAR_WITH_DRAGCORNER = 0x00020000    /// Causes the DragCorner to be shown
  };


class FXDragCorner;
class FXStatusLine;

/// Status bar
class FXStatusBar : public FXHorizontalFrame {
public:
  %extend {
    /// Construct status bar with or without a drag corner
    FXStatusBar(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=4,FXint vs=0){
      return new FXRbStatusBar(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Show or hide the drag corner
  void setCornerStyle(FXbool withcorner=TRUE);

  /// Return TRUE if drag corner shown
  FXbool getCornerStyle() const;

  /// Acess the status line widget
  FXStatusLine *getStatusLine() const;

  /// Access the drag corner widget
  FXDragCorner *getDragCorner() const;

  /// Destructor
  virtual ~FXStatusBar();
  };


DECLARE_FXOBJECT_VIRTUALS(FXStatusBar)
DECLARE_FXID_VIRTUALS(FXStatusBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXStatusBar)
DECLARE_FXWINDOW_VIRTUALS(FXStatusBar)

