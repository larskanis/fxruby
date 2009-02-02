/********************************************************************************
*                                                                               *
*                       T o o l   B a r   T a b   W i d g e t                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXToolBarTab.h 2343 2006-02-12 20:26:26Z lyle $                      *
********************************************************************************/
#ifndef FXTOOLBARTAB_H
#define FXTOOLBARTAB_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/// Tool Bar Tab styles
enum {
  TOOLBARTAB_HORIZONTAL = 0,              /// Default is for horizontal toolbar
  TOOLBARTAB_VERTICAL   = 0x00008000      /// For vertical toolbar
  };



/**
* A toolbar tab is used to collapse or uncollapse a sibling
* widget.  The sibling affected is the widget immediately following
* the toolbar tab or, if the toolbar tab is the last widget in the list,
* the widget immediately preceding the toolbar tab.
*/
class FXAPI FXToolBarTab : public FXFrame {
  FXDECLARE(FXToolBarTab)
protected:
  FXColor  activeColor; // Color when active
  FXString tip;         // Tooltip
  FXbool   collapsed;   // Is collapsed flat
  FXbool   down;        // Button down
protected:
  FXToolBarTab();
  void drawUpArrow(FXDCWindow& dc);
  void drawDownArrow(FXDCWindow& dc);
  void drawRightArrow(FXDCWindow& dc);
  void drawLeftArrow(FXDCWindow& dc);
  void drawHSpeckles(FXDCWindow& dc,FXint x,FXint w);
  void drawVSpeckles(FXDCWindow& dc,FXint y,FXint h);
private:
  FXToolBarTab(const FXToolBarTab&);
  FXToolBarTab& operator=(const FXToolBarTab&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUpdate(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onCmdCollapse(FXObject*,FXSelector,void*);
  long onUpdCollapse(FXObject*,FXSelector,void*);
  long onCmdUncollapse(FXObject*,FXSelector,void*);
  long onUpdUncollapse(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:
  enum {
    ID_COLLAPSE=FXFrame::ID_LAST,
    ID_UNCOLLAPSE,
    ID_LAST
    };
public:

  /// Construct toolbar tab
  FXToolBarTab(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Toolbar tab can receive focus
  virtual bool canFocus() const;

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Enable the toolbar tab
  virtual void enable();

  /// Disable the toolbar tab
  virtual void disable();

  /// Collapse or uncollapse the toolbar
  void collapse(FXbool fold,FXbool notify=FALSE);

  /// Return true if the toolbar is collapsed
  FXbool isCollapsed() const { return collapsed; }

  /// Change the tab style
  void setTabStyle(FXuint style);

  /// Get current tab style
  FXuint getTabStyle() const;

  /// Get the active color
  FXColor getActiveColor() const { return activeColor; }

  /// Set the active color
  void setActiveColor(FXColor clr);

  /// Set the tool tip message for the toolbar tab
  void setTipText(const FXString& text){ tip=text; }

  /// Get the tool tip message for the toolbar tab
  const FXString& getTipText() const { return tip; }

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);
  };

}

#endif
