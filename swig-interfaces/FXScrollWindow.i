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
class FXScrollWindow : public FXScrollArea {
protected:
  FXScrollWindow(){}
public:
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
public:

  /// Construct a scroll window
  %extend {
    FXScrollWindow(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbScrollWindow(p,opts,x,y,w,h);
      }
    }

  /// Return a pointer to the contents window
  FXWindow* contentWindow() const;
  
  /// Destructor
  virtual ~FXScrollWindow();
  };


DECLARE_FXOBJECT_VIRTUALS(FXScrollWindow)
DECLARE_FXID_VIRTUALS(FXScrollWindow)
DECLARE_FXDRAWABLE_VIRTUALS(FXScrollWindow)
DECLARE_FXWINDOW_VIRTUALS(FXScrollWindow)
DECLARE_FXSCROLLAREA_VIRTUALS(FXScrollWindow)

