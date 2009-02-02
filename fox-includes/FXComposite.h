/********************************************************************************
*                                                                               *
*                       C o m p o s i t e   W i d g e t                         *
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
* $Id: FXComposite.h 2335 2006-01-28 02:33:03Z lyle $                       *
********************************************************************************/
#ifndef FXCOMPOSITE_H
#define FXCOMPOSITE_H

#ifndef FXWINDOW_H
#include "FXWindow.h"
#endif

namespace FX {


/// Base composite
class FXAPI FXComposite : public FXWindow {
  FXDECLARE(FXComposite)
protected:
  FXComposite(){}
  FXComposite(FXApp* a,FXVisual *vis);
  FXComposite(FXApp* a,FXWindow* own,FXuint opts,FXint x,FXint y,FXint w,FXint h);
private:
  FXComposite(const FXComposite&);
  FXComposite &operator=(const FXComposite&);
public:
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onFocusNext(FXObject*,FXSelector,void*);
  long onFocusPrev(FXObject*,FXSelector,void*);
  long onCmdUpdate(FXObject*,FXSelector,void*);
public:

  /// Constructor
  FXComposite(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Return the width of the widest child window
  FXint maxChildWidth() const;

  /// Return the height of the tallest child window
  FXint maxChildHeight() const;

  /// Overrides this virtual function to return TRUE
  virtual bool isComposite() const;

  /// Destructor
  virtual ~FXComposite();
  };

}

#endif
