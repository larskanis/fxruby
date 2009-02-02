/********************************************************************************
*                                                                               *
*                        T o o l B a r   W i d g e t                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXToolBar.h 2244 2005-11-10 01:45:23Z lyle $                         *
********************************************************************************/
#ifndef FXTOOLBAR_H
#define FXTOOLBAR_H

#ifndef FXDOCKBAR_H
#include "FXDockBar.h"
#endif

namespace FX {

class FXDockSite;


/**
* A tool bar widget can be docked in a dock site; it automatically
* adjusts its orientation based on the orientation of the dock site,
* and adjusts the layout options accordingly.
* See dock bar widget for more information on the docking behavior.
*/
class FXAPI FXToolBar : public FXDockBar {
  FXDECLARE(FXToolBar)
protected:
  FXToolBar(){}
private:
  FXToolBar(const FXToolBar&);
  FXToolBar &operator=(const FXToolBar&);
public:
  long onCmdDockFlip(FXObject*,FXSelector,void*);
  long onUpdDockFlip(FXObject*,FXSelector,void*);
public:

  /// Construct floatable toolbar, initially docked under parent p
  FXToolBar(FXComposite* p,FXComposite* q,FXuint opts=LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Construct a non-floatable toolbar
  FXToolBar(FXComposite* p,FXuint opts,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=2,FXint pr=3,FXint pt=3,FXint pb=2,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Dock and optionally flip orientation of toolbar
  virtual void dock(FXDockSite* docksite,FXWindow* before=NULL,FXbool notify=FALSE);

  /// Dock and optionally flip orientation of toolbar
  virtual void dock(FXDockSite* docksite,FXint localx,FXint localy,FXbool notify);

  /// Set docking side
  void setDockingSide(FXuint side=LAYOUT_SIDE_TOP);

  /// Return docking side
  FXuint getDockingSide() const;
  };

}

#endif
