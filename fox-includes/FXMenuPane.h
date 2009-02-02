/********************************************************************************
*                                                                               *
*                        M e n u   P a n e   W i d g e t                        *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMenuPane.h 2344 2006-02-12 21:19:36Z lyle $                        *
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
  virtual bool contains(FXint parentx,FXint parenty) const;
  };

}

#endif
