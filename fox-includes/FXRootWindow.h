/********************************************************************************
*                                                                               *
*                     R o o t   W i n d o w   W i d g e t                       *
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
* $Id: FXRootWindow.h 1641 2003-07-09 19:55:56Z lyle $                      *
********************************************************************************/
#ifndef FXROOTWINDOW_H
#define FXROOTWINDOW_H

#ifndef FXCOMPOSITE_H
#include "FXComposite.h"
#endif

namespace FX {


/// Root window
class FXAPI FXRootWindow : public FXComposite {
  FXDECLARE(FXRootWindow)
protected:
  FXRootWindow(){}
#ifdef WIN32
  virtual FXID GetDC() const;
  virtual int ReleaseDC(FXID) const;
#endif
private:
  FXRootWindow(const FXRootWindow&);
  FXRootWindow &operator=(const FXRootWindow&);
public:

  /// Construct root window
  FXRootWindow(FXApp* a,FXVisual *vis);

  /// Root window need not be created
  virtual void create();

  /// Root window may not be detached
  virtual void detach();

  /// Root window can not be destroyed
  virtual void destroy();

  /// Perform layout
  virtual void layout();

  /// Return width of the root window
  virtual FXint getDefaultWidth();

  /// Return height of the root window
  virtual FXint getDefaultHeight();

  /// No op
  virtual void recalc();

  /// Root window can not be moved
  virtual void move(FXint x,FXint y);

  /// Root window can not be resized
  virtual void resize(FXint w,FXint h);

  /// Root window can not be positioned
  virtual void position(FXint x,FXint y,FXint w,FXint h);

  /// Root window can not get focus
  virtual void setFocus();

  /// Root window can not loose
  virtual void killFocus();

  /// Destructor
  virtual ~FXRootWindow();
  };

}

#endif
