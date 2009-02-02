/********************************************************************************
*                                                                               *
*                 V e r t i c a l   C o n t a i n e r   W i d g e t             *
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
* $Id: FXVerticalFrame.h 1536 2003-05-14 21:41:00Z lyle $                   *
********************************************************************************/
#ifndef FXVERTICALFRAME_H
#define FXVERTICALFRAME_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


/**
* Vertical frame layout manager widget is used to automatically
* place child-windows vertically from top-to-bottom, or bottom-to-top,
* depending on the child window's layout hints.
*/
class FXAPI FXVerticalFrame : public FXPacker {
  FXDECLARE(FXVerticalFrame)
protected:
  FXVerticalFrame(){}
private:
  FXVerticalFrame(const FXVerticalFrame&);
  FXVerticalFrame& operator=(const FXVerticalFrame&);
public:

  /// Construct a vertical frame layout manager
  FXVerticalFrame(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();
  };

}

#endif
