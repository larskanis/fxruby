/********************************************************************************
*                                                                               *
*                             M e n u B a r   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMenuBar.h 2343 2006-02-12 20:26:26Z lyle $                         *
********************************************************************************/
#ifndef FXMENUBAR_H
#define FXMENUBAR_H

#ifndef FXTOOLBAR_H
#include "FXToolBar.h"
#endif

namespace FX {


/// Menu bar
class FXAPI FXMenuBar : public FXToolBar {
  FXDECLARE(FXMenuBar)
protected:
  FXMenuBar(){}
private:
  FXMenuBar(const FXMenuBar&);
  FXMenuBar &operator=(const FXMenuBar&);
public:
  long onFocusLeft(FXObject*,FXSelector,void*);
  long onFocusRight(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onButtonPress(FXObject*,FXSelector,void*);
  long onButtonRelease(FXObject*,FXSelector,void*);
  long onCmdUnpost(FXObject*,FXSelector,void*);
public:

  /**
  * Construct a floatable menubar
  * Normally, the menubar is docked under window p.
  * When floated, the menubar can be docked under window q, which is
  * typically an FXToolbarShell window.
  */
  FXMenuBar(FXComposite* p,FXComposite* q,FXuint opts=LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /**
  * Construct a non-floatable menubar.
  * The menubar can not be undocked.
  */
  FXMenuBar(FXComposite* p,FXuint opts,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Returns true if specified coordinate (in parent's coordinate system) is in menubar
  virtual bool contains(FXint parentx,FXint parenty) const;
  };

}

#endif
