/********************************************************************************
*                                                                               *
*                S p r i n g   C o n t a i n e r   W i d g e t                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 2003 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXSpring.h 1829 2003-12-18 16:40:13Z lyle $                           *
********************************************************************************/
#ifndef FXSPRING_H
#define FXSPRING_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/**
* The spring widgets, when properly embedded side by side in a horizontal
* frame or vertical frame widget, behave like a set of connected springs
* of various lengths (hence the name!).  The parameters relw (or relh)
* determines the length of the spring.  The actual length is not really
* important; the only thing that counts is the relative length of one
* spring widget to that of another, although the length does determine
* the default size.  The special value zero may be given for relw (or relh)
* to cause the spring to calculate its default width (height) normally,
* just like the Packer base class does.
* In a typical scenario, either the relative width or height is set to
* zero, an the flag LAYOUT_FILL_X or LAYOUT_FILL_Y is passed. When
* placed inside a horizontal frame, the LAYOUT_FILL_X together with
* the relative widths of the springs will cause a fixed width-ratio
* between the springs.
* You also can mix normal controls and springs together in a horizontal
* or vertical frames to provide arbitrary stretchable spacing between
* widgets; in this case, the springs do not need to have any children.
* Since the spring widget is derived from the packer layout manager,
* it provides the same layout behavior as packer.
*/
class FXAPI FXSpring : public FXPacker {
  FXDECLARE(FXSpring)
protected:
  FXint   relWidth;     // Relative width
  FXint   relHeight;    // Relative height
protected:
  FXSpring(){}
private:
  FXSpring(const FXSpring&);
  FXSpring &operator=(const FXSpring&);
public:

  /// Construct packer layout manager
  FXSpring(FXComposite *p,FXuint opts=0,FXint relw=0,FXint relh=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Change relative width
  void setRelativeWidth(FXint relw);

  /// Return relative width
  FXint  getRelativeWidth() const { return relWidth; }

  /// Change relative height
  void setRelativeHeight(FXint relh);

  /// Return relative height
  FXint getRelativeHeight() const { return relHeight; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
