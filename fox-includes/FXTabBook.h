/********************************************************************************
*                                                                               *
*                         T a b   B o o k   W i d g e t                         *
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
* $Id: FXTabBook.h 2241 2005-11-09 13:51:59Z lyle $                          *
********************************************************************************/
#ifndef FXTABBOOK_H
#define FXTABBOOK_H

#ifndef FXTABBAR_H
#include "FXTabBar.h"
#endif

namespace FX {


/**
* The tab book layout manager arranges pairs of children;
* the even numbered children (0,2,4,...) are usually tab items,
* and are placed on the top.  The odd numbered children are
* usually layout managers, and are placed below; all the odd
* numbered children are placed on top of each other, similar
* to the switcher widget.  When the user presses one of the
* tab items, the tab item is raised above the neighboring tabs,
* and the corresponding panel is raised to the top.
* Thus, a tab book can be used to present many GUI controls
* in a small space by placing several panels on top of each
* other and using tab items to select the desired panel.
* When one of the tab items is pressed, the tab book's setCurrent()
* is called with notify=TRUE.  Thus causes the tab book to send a
* SEL_COMMAND message to its target.
*/
class FXAPI FXTabBook : public FXTabBar {
  FXDECLARE(FXTabBook)
protected:
  FXTabBook(){}
private:
  FXTabBook(const FXTabBook&);
  FXTabBook& operator=(const FXTabBook&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onFocusNext(FXObject*,FXSelector,void*);
  long onFocusPrev(FXObject*,FXSelector,void*);
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusLeft(FXObject*,FXSelector,void*);
  long onFocusRight(FXObject*,FXSelector,void*);
  long onCmdOpenItem(FXObject*,FXSelector,void*);
public:

  /// Construct tab book
  FXTabBook(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TABBOOK_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING);

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();
  };

}

#endif
