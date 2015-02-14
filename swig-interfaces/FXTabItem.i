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

// Tab Item orientations which affect border
enum {
  TAB_TOP          = 0,           // Top side tabs
  TAB_LEFT         = 0x00800000,  // Left side tabs
  TAB_RIGHT        = 0x01000000,  // Right side tabs
  TAB_BOTTOM       = 0x01800000,  // Bottom side tabs
  TAB_TOP_NORMAL   = JUSTIFY_NORMAL|ICON_BEFORE_TEXT|TAB_TOP|FRAME_RAISED|FRAME_THICK,
  TAB_BOTTOM_NORMAL= JUSTIFY_NORMAL|ICON_BEFORE_TEXT|TAB_BOTTOM|FRAME_RAISED|FRAME_THICK,
  TAB_LEFT_NORMAL  = JUSTIFY_LEFT|JUSTIFY_CENTER_Y|ICON_BEFORE_TEXT|TAB_LEFT|FRAME_RAISED|FRAME_THICK,
  TAB_RIGHT_NORMAL = JUSTIFY_LEFT|JUSTIFY_CENTER_Y|ICON_BEFORE_TEXT|TAB_RIGHT|FRAME_RAISED|FRAME_THICK
  };


/**
* A tab item is placed in a tab bar or tab book.
* When selected, the tab item sends a message to its
* parent, and causes itself to become the active tab,
* and raised slightly above the other tabs.
* In the tab book, activating a tab item also causes
* the corresponding panel to be raised to the top.
*/
class FXTabItem : public FXLabel {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
public:

  /// Construct a tab item
  %extend {
    FXTabItem(FXTabBar* p,const FXString& text,FXIcon* ic=0,FXuint opts=TAB_TOP_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbTabItem(p,text,ic,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Return current tab item orientation
  FXuint getTabOrientation() const;

  /// Change tab item orientation
  void setTabOrientation(FXuint style);

  /// Destructor
  virtual ~FXTabItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTabItem)
DECLARE_FXID_VIRTUALS(FXTabItem)
DECLARE_FXDRAWABLE_VIRTUALS(FXTabItem)
DECLARE_FXWINDOW_VIRTUALS(FXTabItem)

