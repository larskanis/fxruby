/********************************************************************************
*                                                                               *
*                          P i c k e r   B u t t o n                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXPicker.h 2725 2007-11-16 16:57:54Z lyle $                          *
********************************************************************************/
#ifndef FXPICKER_H
#define FXPICKER_H

#ifndef FXBUTTON_H
#include "FXButton.h"
#endif

namespace FX {


/**
* A Picker button allows you to identify an arbitrary location on the screen.
* It generates SEL_CHANGED callbacks while the user is moving the mouse, and
* a final SEL_COMMAND when a location has been identified.  The void* parameter
* in the callback is a pointer to FXPoint, the location, in root-coordinates, of
* the place where the click took place.
*/
class FXAPI FXPicker : public FXButton {
  FXDECLARE(FXPicker)
protected:
  FXPoint location;     // Location
  FXbool  picked;       // Clicked
protected:
  FXPicker();
private:
  FXPicker(const FXPicker&);
  FXPicker& operator=(const FXPicker&);
public:
  long onMotion(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
public:

  /// Construct picker button with text and icon
  FXPicker(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=BUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);
  };

}

#endif
