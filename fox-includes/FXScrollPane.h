/********************************************************************************
*                                                                               *
*               S c r o l l i n g   M e n u   P a n e   W i d g e t             *
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
* $Id: FXScrollPane.h 2235 2005-11-09 13:33:24Z lyle $                       *
********************************************************************************/
#ifndef FXSCROLLPANE_H
#define FXSCROLLPANE_H

#ifndef FXMENUPANE_H
#include "FXMenuPane.h"
#endif

namespace FX {

class FXArrowButton;

/**
* A Scroll Pane is a menu pane which provides scrolling of menu entries.
* It is useful when menus are populated programmatically and it is not
* known in advance how many entries will be added.
*/
class FXAPI FXScrollPane : public FXMenuPane {
  FXDECLARE(FXScrollPane)
protected:
  FXArrowButton *dn;            // Button to scroll down
  FXArrowButton *up;            // Button to scroll up
  FXint          visible;       // Visible entries
  FXint          top;           // Top visible entry
protected:
  FXScrollPane();
private:
  FXScrollPane(const FXScrollPane&);
  FXScrollPane &operator=(const FXScrollPane&);
public:
  long onCmdIncrement(FXObject*,FXSelector,void*);
  long onCmdDecrement(FXObject*,FXSelector,void*);
public:
  enum {
    ID_SCROLL_DN=FXMenuPane::ID_LAST,
    ID_SCROLL_UP,
    ID_LAST
    };
public:

  /// Construct menu pane
  FXScrollPane(FXWindow* owner,FXint nvis,FXuint opts=0);

  /// Return the default width of this window
  virtual FXint getDefaultWidth();

  /// Return the default height of this window
  virtual FXint getDefaultHeight();

  /// Show this window
  virtual void show();

  /// Perform layout
  virtual void layout();

  /// Return number of visible items
  FXint getNumVisible() const { return visible; }

  /// Change the number of visible items
  void setNumVisible(FXint nvis);

  /// Get index of top most menu item
  FXint getTopItem() const { return top; }

  /// Scroll item to top
  void setTopItem(FXint t);

  /// Destroy
  virtual ~FXScrollPane();
  };

}

#endif
