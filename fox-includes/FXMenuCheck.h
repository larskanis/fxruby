/********************************************************************************
*                                                                               *
*                          M e n u C h e c k   W i d g e t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMenuCheck.h 2264 2005-12-02 01:45:28Z lyle $                       *
********************************************************************************/
#ifndef FXMENUCHECK_H
#define FXMENUCHECK_H

#ifndef FXMENUCOMMAND_H
#include "FXMenuCommand.h"
#endif

namespace FX {


/**
* The menu check widget is used to change a state in the
* application from a menu.  Menu checks may reflect
* the state of the application by graying out, becoming hidden,
* or by a check mark.
* When activated, a menu check sends a SEL_COMMAND to its target;
* the void* argument of the message contains the new state.
*/
class FXAPI FXMenuCheck : public FXMenuCommand {
  FXDECLARE(FXMenuCheck)
protected:
  FXuchar check;        // State of menu
  FXColor boxColor;     // Box color
protected:
  FXMenuCheck();
private:
  FXMenuCheck(const FXMenuCheck&);
  FXMenuCheck &operator=(const FXMenuCheck&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onButtonPress(FXObject*,FXSelector,void*);
  long onButtonRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
  long onCheck(FXObject*,FXSelector,void*);
  long onUncheck(FXObject*,FXSelector,void*);
  long onUnknown(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdAccel(FXObject*,FXSelector,void*);
public:

  /// Construct a menu check
  FXMenuCheck(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Set check state (TRUE, FALSE or MAYBE)
  void setCheck(FXbool s=TRUE);

  /// Get check state (TRUE, FALSE or MAYBE)
  FXbool getCheck() const { return check; }

  /// Get the box background color
  FXColor getBoxColor() const { return boxColor; }

  /// Set the box background color
  void setBoxColor(FXColor clr);

  /// Save menu to a stream
  virtual void save(FXStream& store) const;

  /// Load menu from a stream
  virtual void load(FXStream& store);
  };

}

#endif
