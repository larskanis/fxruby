/********************************************************************************
*                                                                               *
*                     S h e l l   W i n d o w   W i d g e t                     *
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
* $Id: FXShell.h 2725 2007-11-16 16:57:54Z lyle $                           *
********************************************************************************/
#ifndef FXSHELL_H
#define FXSHELL_H

#ifndef FXCOMPOSITE_H
#include "FXComposite.h"
#endif

namespace FX {


/**
* The Shell widget is used as the base class for top level windows, i.e.
* windows which are direct children of the root window.
*/
class FXAPI FXShell : public FXComposite {
  FXDECLARE(FXShell)
protected:
  FXShell(){}
  FXShell(FXApp* a,FXuint opts,FXint x,FXint y,FXint w,FXint h);
  FXShell(FXWindow* own,FXuint opts,FXint x,FXint y,FXint w,FXint h);
private:
  FXShell(const FXShell&);
  FXShell &operator=(const FXShell&);
public:
  long onLayout(FXObject*,FXSelector,void*);
  long onConfigure(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onFocusNext(FXObject*,FXSelector,void*);
  long onFocusPrev(FXObject*,FXSelector,void*);
public:
  enum {
    ID_LAYOUT=FXComposite::ID_LAST,
    ID_LAST
    };
public:

  /// Create server-side resources
  virtual void create();

  /// Mark this window's layout as dirty
  virtual void recalc();

  /// Move the focus to this window
  virtual void setFocus();

  /// Remove the focus from this window
  virtual void killFocus();

  /// Destroy shell
  virtual ~FXShell();
  };

}

#endif
