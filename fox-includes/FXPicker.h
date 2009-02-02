/********************************************************************************
*                                                                               *
*                          P i c k e r   B u t t o n                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXPicker.h 809 2002-07-11 17:28:15Z lyle $                           *
********************************************************************************/
#ifndef FXPICKER_H
#define FXPICKER_H

#ifndef FXBUTTON_H
#include "FXButton.h"
#endif

namespace FX {


/**
* A picker button allows you to identify an arbitrary
* location on the screen.
*/
class FXAPI FXPicker : public FXButton {
  FXDECLARE(FXPicker)
protected:
  FXPicker(){}
private:
  FXPicker(const FXPicker&);
  FXPicker& operator=(const FXPicker&);
public:
  long onMotion(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
public:
  FXPicker(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=BUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);
  };

}

#endif
