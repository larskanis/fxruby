/********************************************************************************
*                                                                               *
*                P a c k e r   C o n t a i n e r   W i d g e t                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2003 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXPacker.h 1536 2003-05-14 21:41:00Z lyle $                          *
********************************************************************************/
#ifndef FXPACKER_H
#define FXPACKER_H

#ifndef FXCOMPOSITE_H
#include "FXComposite.h"
#endif

namespace FX {


/// Default spacing
enum { DEFAULT_SPACING = 4 };


/**
* Packer is a layout manager which automatically places child windows
* inside its area against the left, right, top, or bottom side.
* Each time a child is placed, the remaining space is decreased by the
* amount of space taken by the child window.
* The side against which a child is placed is determined by the LAYOUT_SIDE_TOP,
* LAYOUT_SIDE_BOTTOM, LAYOUT_SIDE_LEFT, and LAYOUT_SIDE_RIGHT hints given by
* the child window.  Other layout hints from the child are observed as far as
* sensible.  So for example, a child placed against the right edge can still
* have LAYOUT_FILL_Y or LAYOUT_TOP, and so on.
* The last child may have both LAYOUT_FILL_X and LAYOUT_FILL_Y, in which
* case it will be placed to take all remaining space.
*/
class FXAPI FXPacker : public FXComposite {
  FXDECLARE(FXPacker)
protected:
  FXColor baseColor;        // Base color
  FXColor hiliteColor;      // Highlight color
  FXColor shadowColor;      // Shadow color
  FXColor borderColor;      // Border color
  FXint   padtop;           // Top margin
  FXint   padbottom;        // Bottom margin
  FXint   padleft;          // Left margin
  FXint   padright;         // Right margin
  FXint   hspacing;         // Horizontal child spacing
  FXint   vspacing;         // Vertical child spacing
  FXint   border;           // Border width
protected:
  FXPacker();
  void drawBorderRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawRaisedRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawSunkenRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawRidgeRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawGrooveRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawDoubleRaisedRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawDoubleSunkenRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawFocusRectangle(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawFrame(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
private:
  FXPacker(const FXPacker&);
  FXPacker &operator=(const FXPacker&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusLeft(FXObject*,FXSelector,void*);
  long onFocusRight(FXObject*,FXSelector,void*);
public:

  /// Construct packer layout manager
  FXPacker(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /// Change frame style
  void setFrameStyle(FXuint style);

  /// Get current frame style
  FXuint getFrameStyle() const;

  /// Change packing hints
  void setPackingHints(FXuint ph);

  /// Return packing hints
  FXuint getPackingHints() const;

  /// Get border width
  FXint getBorderWidth() const { return border; }

  /// Change top padding
  void setPadTop(FXint pt);

  /// Get top interior padding
  FXint getPadTop() const { return padtop; }

  /// Change bottom padding
  void setPadBottom(FXint pb);

  /// Get bottom interior padding
  FXint getPadBottom() const { return padbottom; }

  /// Change left padding
  void setPadLeft(FXint pl);

  /// Get left interior padding
  FXint getPadLeft() const { return padleft; }

  /// Change right padding
  void setPadRight(FXint pr);

  /// Get right interior padding
  FXint getPadRight() const { return padright; }

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Get highlight color
  FXColor getHiliteColor() const { return hiliteColor; }

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Get shadow color
  FXColor getShadowColor() const { return shadowColor; }

  /// Change border color
  void setBorderColor(FXColor clr);

  /// Get border color
  FXColor getBorderColor() const { return borderColor; }

  /// Change base gui color
  void setBaseColor(FXColor clr);

  /// Get base gui color
  FXColor getBaseColor() const { return baseColor; }

  /// Change horizontal inter-child spacing
  void setHSpacing(FXint hs);

  /// Return current horizontal inter-child spacing
  FXint getHSpacing() const { return hspacing; }

  /// Change vertical inter-child spacing
  void setVSpacing(FXint vs);

  /// Return current vertical inter-child spacing
  FXint getVSpacing() const { return vspacing; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
