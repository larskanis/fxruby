/********************************************************************************
*                                                                               *
*                     R o o t   W i n d o w   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXRootWindow.h 2762 2007-11-19 17:07:23Z lyle $                      *
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
