/********************************************************************************
*                                                                               *
*                S p l i t t e r   W i n d o w   W i d g e t                    *
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
* $Id: FXSplitter.h 2127 2005-08-07 20:21:35Z lyle $                        *
********************************************************************************/
#ifndef FXSPLITTER_H
#define FXSPLITTER_H

#ifndef FXCOMPOSITE_H
#include "FXComposite.h"
#endif

namespace FX {


/// Splitter options
enum {
  SPLITTER_HORIZONTAL = 0,                  /// Split horizontally
  SPLITTER_VERTICAL   = 0x00008000,         /// Split vertically
  SPLITTER_REVERSED   = 0x00010000,         /// Reverse-anchored
  SPLITTER_TRACKING   = 0x00020000,         /// Track continuous during split
  SPLITTER_NORMAL     = SPLITTER_HORIZONTAL
  };



/**
* Splitter window is used to interactively repartition
* two or more subpanels.
* Space may be subdivided horizontally (SPLITTER_HORIZONTAL, which
* the default) or vertically (SPLITTER_VERTICAL option).
* When the splitter is itself resized, the right-most (bottom-most)
* child window will be resized unless the splitter window is reversed;
* if the splitter is reversed, the left-most (top-most) child window
* will be resized instead.
* The splitter widget sends a SEL_CHANGED to its target
* during the resizing of the panels; at the end of the resize interaction,
* it sends a SEL_COMMAND to signify that the resize operation is complete.
* Normally, children are resizable from 0 upwards; however, if the child
* in a horizontally oriented splitter has LAYOUT_FILL_X in combination with
* LAYOUT_FIX_WIDTH, it will not be made smaller than its default width,
* except when the child is the last visible widget (or first when the option
* SPLITTER_REVERSED has been passed to the splitter).
* In a vertically oriented splitter, children with LAYOUT_FILL_Y and
* LAYOUT_FIX_HEIGHT behave analogously.
*/
class FXAPI FXSplitter : public FXComposite {
  FXDECLARE(FXSplitter)
private:
  FXWindow *window;         // Window being resized
  FXint     split;          // Split value
  FXint     offset;         // Mouse offset
  FXint     barsize;        // Size of the splitter bar
protected:
  FXSplitter();
  void adjustHLayout();
  void adjustVLayout();
  void moveHSplit(FXint amount);
  void moveVSplit(FXint amount);
  void drawHSplit(FXint pos);
  void drawVSplit(FXint pos);
  FXWindow* findHSplit(FXint pos);
  FXWindow* findVSplit(FXint pos);
private:
  FXSplitter(const FXSplitter&);
  FXSplitter& operator=(const FXSplitter&);
public:
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onFocusNext(FXObject*,FXSelector,void*);
  long onFocusPrev(FXObject*,FXSelector,void*);
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusLeft(FXObject*,FXSelector,void*);
  long onFocusRight(FXObject*,FXSelector,void*);
public:

  /// Construct new splitter widget
  FXSplitter(FXComposite* p,FXuint opts=SPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Construct new splitter widget, which will notify target about size changes
  FXSplitter(FXComposite* p,FXObject* tgt,FXSelector sel,FXuint opts=SPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Get default width
  virtual FXint getDefaultWidth();

  /// Get default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /// Return size of the panel at index
  FXint getSplit(FXint index) const;

  /// Change the size of panel at the given index
  void setSplit(FXint index,FXint size);

  /// Change splitter style
  void setSplitterStyle(FXuint style);

  /// Return current splitter style
  FXuint getSplitterStyle() const;

  /// Change splitter bar size
  void setBarSize(FXint bs);

  /// Return current bar size
  FXint getBarSize() const { return barsize; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy splitter
  virtual ~FXSplitter();
  };

}

#endif
