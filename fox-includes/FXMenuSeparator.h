/********************************************************************************
*                                                                               *
*                    M e n u   S e p a r a t o r   W i d g e t                  *
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
* $Id: FXMenuSeparator.h 2753 2007-11-16 22:52:54Z lyle $                   *
********************************************************************************/
#ifndef FXMENUSEPARATOR_H
#define FXMENUSEPARATOR_H

#ifndef FXWINDOW_H
#include "FXWindow.h"
#endif

namespace FX {


/**
* The menu separator is a simple decorative groove used to delineate items in a
* popup menu.  When a target/message is given, the menu separator is usually
* connected to an instance of the recent files class using the ID_ANYFILES
* message.  This automatically hides the menu separator when no files are listed
* in the recent files section.  Another possible target is the MDI client using
* the ID_MDI_ANY message: in this case, the menu separator will be automatically
* hidden when no MDI child windows are present.
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
  FXMenuSeparator(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0);

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
