/********************************************************************************
*                                                                               *
*                        M e n u   P a n e   W i d g e t                        *
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
* $Id: FXMenuPane.h 2725 2007-11-16 16:57:54Z lyle $                        *
********************************************************************************/
#ifndef FXMENUPANE_H
#define FXMENUPANE_H

#ifndef FXPOPUP_H
#include "FXPopup.h"
#endif

namespace FX {

/// Popup menu pane
class FXAPI FXMenuPane : public FXPopup {
  FXDECLARE(FXMenuPane)
protected:
  FXMenuPane(){}
private:
  FXMenuPane(const FXMenuPane&);
  FXMenuPane &operator=(const FXMenuPane&);
public:

  /// Construct menu pane
  FXMenuPane(FXWindow* owner,FXuint opts=0);

  /// Return true if popup contains this point
  virtual FXbool contains(FXint parentx,FXint parenty) const;
  };

}

#endif
