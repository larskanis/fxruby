/********************************************************************************
*                                                                               *
*                           T a b   I t e m    W i d g e t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXTabItem.h 2343 2006-02-12 20:26:26Z lyle $                          *
********************************************************************************/
#ifndef FXTABITEM_H
#define FXTABITEM_H

#ifndef FXLABEL_H
#include "FXLabel.h"
#endif

namespace FX {


/// Tab Item orientations which affect border
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


class FXTabBar;


/**
* A tab item is placed in a tab bar or tab book.
* When selected, the tab item sends a message to its
* parent, and causes itself to become the active tab,
* and raised slightly above the other tabs.
* In the tab book, activating a tab item also causes
* the corresponding panel to be raised to the top.
*/
class FXAPI FXTabItem : public FXLabel {
  FXDECLARE(FXTabItem)
protected:
  FXTabItem(){}
private:
  FXTabItem(const FXTabItem&);
  FXTabItem& operator=(const FXTabItem&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
public:

  /// Construct a tab item
  FXTabItem(FXTabBar* p,const FXString& text,FXIcon* ic=0,FXuint opts=TAB_TOP_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Returns true because a tab item can receive focus
  virtual bool canFocus() const;

  /// Return current tab item orientation
  FXuint getTabOrientation() const;

  /// Change tab item orientation
  void setTabOrientation(FXuint style);
  };

}

#endif
