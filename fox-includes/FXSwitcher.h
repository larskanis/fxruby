/********************************************************************************
*                                                                               *
*                  S w i t c h   C o n t a i n e r   W i d g e t                *
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
* $Id: FXSwitcher.h 1536 2003-05-14 21:41:00Z lyle $                        *
********************************************************************************/
#ifndef FXSWITCHER_H
#define FXSWITCHER_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {

/// Switcher options
enum {
  SWITCHER_HCOLLAPSE = 0x00020000,  /// Collapse horizontally to width of current child
  SWITCHER_VCOLLAPSE = 0x00040000   /// Collapse vertically to height of current child
  };


/**
* The Switcher layout manager automatically arranges its child
* windows such that one of them is placed on top; all other
* child windows are hidden.
* Switcher provides a convenient method to conserve screen
* real-estate by arranging several GUI panels to appear in the
* same space, depending on context.
* Switcher ignores all layout hints from its children:- all
* children are stretched according to the switcher layout
* managers own size.
* When the SWITCHER_HCOLLAPSE or SWITCHER_VCOLLAPSE options
* are used, Switcher's default size is based on the width or
* height of the current child, instead of the maximum width
* or height of all of the children.
*/
class FXAPI FXSwitcher : public FXPacker {
  FXDECLARE(FXSwitcher)
protected:
  FXint  current;
protected:
  FXSwitcher(){}
private:
  FXSwitcher(const FXSwitcher&);
  FXSwitcher& operator=(const FXSwitcher&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdOpen(FXObject*,FXSelector,void*);
  long onUpdOpen(FXObject*,FXSelector,void*);
public:
  enum {
    ID_OPEN_FIRST=FXPacker::ID_LAST,
    ID_OPEN_SECOND,
    ID_OPEN_THIRD,
    ID_OPEN_FOURTH,
    ID_OPEN_FIFTH,
    ID_OPEN_SIXTH,
    ID_OPEN_SEVENTH,
    ID_OPEN_EIGHTH,
    ID_OPEN_NINETH,
    ID_OPEN_TENTH,
    ID_OPEN_LAST=ID_OPEN_FIRST+100,
    ID_LAST
    };
public:

  /// Construct a switcher layout manager
  FXSwitcher(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /// Bring the child window at index to the top
  void setCurrent(FXint index,FXbool notify=FALSE);

  /// Return the index of the child window currently on top
  FXint getCurrent() const { return current; }

  /// Set the switcher style flags
  void setSwitcherStyle(FXuint style);

  /// Get the switcher style flags
  FXuint getSwitcherStyle() const;

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
