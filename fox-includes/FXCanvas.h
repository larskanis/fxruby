/********************************************************************************
*                                                                               *
*                          C a n v a s   W i d g e t                            *
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
* $Id: FXCanvas.h 2335 2006-01-28 02:33:03Z lyle $                          *
********************************************************************************/
#ifndef FXCANVAS_H
#define FXCANVAS_H

#ifndef FXWINDOW_H
#include "FXWindow.h"
#endif

namespace FX {


/// Canvas, an area drawn by another object
class FXAPI FXCanvas : public FXWindow {
  FXDECLARE(FXCanvas)
protected:
  FXCanvas();
private:
  FXCanvas(const FXCanvas&);
  FXCanvas &operator=(const FXCanvas&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:

  /// Construct new drawing canvas widget
  FXCanvas(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Return TRUE because canvas can receive focus
  virtual bool canFocus() const;
  };

}

#endif
