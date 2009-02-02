/********************************************************************************
*                                                                               *
*                    M e n u   S e p a r a t o r   W i d g e t                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMenuSeparator.h 809 2002-07-11 17:28:15Z lyle $                   *
********************************************************************************/
#ifndef FXMENUSEPARATOR_H
#define FXMENUSEPARATOR_H

#ifndef FXWINDOW_H
#include "FXWindow.h"
#endif

namespace FX {


/**
* The menu separator is a simple decorative groove
* used to delineate items in a popup menu.
*/
class FXAPI FXMenuSeparator : public FXWindow {
  FXDECLARE(FXMenuSeparator)
protected:
  FXColor hiliteColor;
  FXColor shadowColor;
protected:
  FXMenuSeparator();
private:
  FXMenuSeparator(const FXMenuSeparator&);
  FXMenuSeparator &operator=(const FXMenuSeparator&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:

  /// Construct a menu separator
  FXMenuSeparator(FXComposite* p,FXuint opts=0);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Get highlight color
  FXColor getHiliteColor() const { return hiliteColor; }

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Get shadow color
  FXColor getShadowColor() const { return shadowColor; }

  /// Save menu to a stream
  virtual void save(FXStream& store) const;

  /// Load menu from a stream
  virtual void load(FXStream& store);
  };

}

#endif
