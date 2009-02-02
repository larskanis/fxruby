/********************************************************************************
*                                                                               *
*                              D e b u g   T a r g e t                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDebugTarget.h 809 2002-07-11 17:28:15Z lyle $                     *
********************************************************************************/
#ifndef FXDEBUGTARGET_H
#define FXDEBUGTARGET_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {


/**
* A DebugTarget prints out every message it receives.
* To use it, simply make the DebugTarget a target of the widget
* whose messages you want to see,
*/
class FXAPI FXDebugTarget : public FXObject {
  FXDECLARE(FXDebugTarget)
protected:
  FXObject   *lastsender;
  FXSelector  lastsel;
  FXuint      count;
public:
  static const FXchar *const messageTypeName[];
private:
  FXDebugTarget(const FXDebugTarget&);
  FXDebugTarget &operator=(const FXDebugTarget&);
public:
  long onMessage(FXObject*,FXSelector,void*);
public:

  /// Construct a debug target
  FXDebugTarget();

  };

}

#endif
