/********************************************************************************
*                                                                               *
*                           T a b  B a r   W i d g e t                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXTabBar.h 2241 2005-11-09 13:51:59Z lyle $                          *
********************************************************************************/
#ifndef FXTABBAR_H
#define FXTABBAR_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/// Tab Book options
enum {
  TABBOOK_TOPTABS    = 0,                                   /// Tabs on top (default)
  TABBOOK_BOTTOMTABS = 0x00020000,                          /// Tabs on bottom
  TABBOOK_SIDEWAYS   = 0x00040000,                          /// Tabs on left
  TABBOOK_LEFTTABS   = TABBOOK_SIDEWAYS|TABBOOK_TOPTABS,    /// Tabs on left
  TABBOOK_RIGHTTABS  = TABBOOK_SIDEWAYS|TABBOOK_BOTTOMTABS, /// Tabs on right
  TABBOOK_NORMAL     = TABBOOK_TOPTABS                      /// Normal tabs
  };



/**
* The tab bar layout manager arranges tab items side by side,
* and raises the active tab item above the neighboring tab items.
* In a the horizontal arrangement, the tab bar can have the tab
* items on the top or on the bottom.  In the vertical arrangement,
* the tabs can be on the left or on the right.
* When one of the tab items is pressed, the tab bar's setCurrent()
* is called with notify=TRUE.  Thus causes the tab bar to send a
* SEL_COMMAND message to its target.
*/
class FXAPI FXTabBar : public FXPacker {
  FXDECLARE(FXTabBar)
protected:
  FXint current;        // Current tab index
  FXint shift;          // Shift amount
protected:
  FXTabBar(){}
private:
  FXTabBar(const FXTabBar&);
  FXTabBar& operator=(const FXTabBar&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onFocusNext(FXObject*,FXSelector,void*);
  long onFocusPrev(FXObject*,FXSelector,void*);
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusLeft(FXObject*,FXSelector,void*);
  long onFocusRight(FXObject*,FXSelector,void*);
  long onCmdOpenItem(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdOpen(FXObject*,FXSelector,void*);
  long onUpdOpen(FXObject*,FXSelector,void*);
public:
  enum {
    ID_OPEN_ITEM=FXPacker::ID_LAST,   /// Sent from one of the FXTabItems
    ID_OPEN_FIRST,                    /// Switch to panel ID_OPEN_FIRST+i
    ID_OPEN_SECOND,
    ID_OPEN_THIRD,
    ID_OPEN_FOURTH,
    ID_OPEN_FIFTH,
    ID_OPEN_SIXTH,
    ID_OPEN_SEVENTH,
    ID_OPEN_EIGHTH,
    ID_OPEN_NINETH,
    ID_OPEN_TENTH,
    ID_OPEN_LAST=ID_OPEN_FIRST+100,
    ID_LAST
    };
public:

  /// Construct a tab bar
  FXTabBar(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TABBOOK_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /**
  * Change currently active tab item; this raises the active tab item
  * slightly above the neighboring tab items.  If notify=TRUE then the
  * tab bar will also send a SEL_COMMAND message to its target.
  */
  virtual void setCurrent(FXint panel,FXbool notify=FALSE);

  /// Return the currently active tab item
  FXint getCurrent() const { return current; }

  /// Return tab bar style
  FXuint getTabStyle() const;

  /// Change tab tab style
  void setTabStyle(FXuint style);

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
