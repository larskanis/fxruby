/********************************************************************************
*                                                                               *
*              H o r i z o n t a l   C o n t a i n e r   W i d g e t            *
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
* $Id: FXHorizontalFrame.h 1536 2003-05-14 21:41:00Z lyle $                 *
********************************************************************************/
#ifndef FXHORIZONTALFRAME_H
#define FXHORIZONTALFRAME_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/**
* Horizontal frame layout manager widget is used to automatically
* place child-windows horizontally from left-to-right, or right-to-left,
* depending on the child window's layout hints.
*/
class FXAPI FXHorizontalFrame : public FXPacker {
  FXDECLARE(FXHorizontalFrame)
protected:
  FXHorizontalFrame(){}
private:
  FXHorizontalFrame(const FXHorizontalFrame&);
  FXHorizontalFrame &operator=(const FXHorizontalFrame&);
public:

  /// Construct a horizontal frame layout manager
  FXHorizontalFrame(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();
  };

}

#endif
