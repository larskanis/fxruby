/********************************************************************************
*                                                                               *
*                       M e n u C o m m a n d   W i d g e t                     *
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
* $Id: FXMenuCommand.h 2725 2007-11-16 16:57:54Z lyle $                     *
********************************************************************************/
#ifndef FXMENUCOMMAND_H
#define FXMENUCOMMAND_H

#ifndef FXMENUCAPTION_H
#include "FXMenuCaption.h"
#endif

namespace FX {


/**
* The menu command widget is used to invoke a command in the
* application from a menu.  Menu commands may reflect
* the state of the application by graying out, or becoming hidden.
* When activated, a menu command sends a SEL_COMMAND to its target.
*/
class FXAPI FXMenuCommand : public FXMenuCaption {
  FXDECLARE(FXMenuCommand)
protected:
  FXString     accel;       // Accelerator string
  FXHotKey     acckey;      // Accelerator key
protected:
  FXMenuCommand();
private:
  FXMenuCommand(const FXMenuCommand&);
  FXMenuCommand &operator=(const FXMenuCommand&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onButtonPress(FXObject*,FXSelector,void*);
  long onButtonRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
  long onCmdAccel(FXObject*,FXSelector,void*);
public:

  /// Construct a menu command
  FXMenuCommand(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Yes it can receive the focus
  virtual FXbool canFocus() const;

  /// Move the focus to this window
  virtual void setFocus();

  /// Remove the focus from this window
  virtual void killFocus();

  /// Set accelerator text
  void setAccelText(const FXString& text);

  /// Return accelarator text
  FXString getAccelText() const { return accel; }

  /// Save menu to a stream
  virtual void save(FXStream& store) const;

  /// Load menu from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXMenuCommand();
  };

}

#endif
