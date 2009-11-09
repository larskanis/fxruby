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

class FXToolBarShell : public FXTopWindow {
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
  FXToolBarShell();
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
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Construct a toolbar shell
    FXToolBarShell(FXWindow* owner,FXuint opts=FRAME_RAISED|FRAME_THICK,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint hs=4,FXint vs=4){
      return new FXRbToolBarShell(owner,opts,x,y,w,h,hs,vs);
      }
    }

  /// Change frame style
  void setFrameStyle(FXuint style);
  
  /// Get current frame style
  FXuint getFrameStyle() const;

  /// Get border width
  FXint getBorderWidth() const;

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Get highlight color
  FXColor getHiliteColor() const;

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Get shadow color
  FXColor getShadowColor() const;

  /// Change border color
  void setBorderColor(FXColor clr);

  /// Get border color
  FXColor getBorderColor() const;

  /// Change base gui color
  void setBaseColor(FXColor clr);
  
  /// Get base gui color
  FXColor getBaseColor() const;
  
  /// Destructor
  virtual ~FXToolBarShell();
  };


DECLARE_FXOBJECT_VIRTUALS(FXToolBarShell)
DECLARE_FXID_VIRTUALS(FXToolBarShell)
DECLARE_FXDRAWABLE_VIRTUALS(FXToolBarShell)
DECLARE_FXWINDOW_VIRTUALS(FXToolBarShell)
DECLARE_FXTOPWINDOW_VIRTUALS(FXToolBarShell)

