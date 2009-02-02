/********************************************************************************
*                                                                               *
*                       T o o l B a r G r i p   W i d g e t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXToolBarGrip.h 2767 2007-11-19 18:33:06Z lyle $                     *
********************************************************************************/
#ifndef FXTOOLBARGRIP_H
#define FXTOOLBARGRIP_H

#ifndef FXDOCKHANDLER_H
#include "FXDockHandler.h"
#endif

namespace FX {


/// Tool Bar Grip styles
enum {
  TOOLBARGRIP_SINGLE     = 0,             /// Single bar mode for movable toolbars
  TOOLBARGRIP_DOUBLE     = 0x00008000     /// Double bar mode for dockable toolbars
  };


/**
* A toolbar grip is used to move its container, a dock bar.
* The grip draws either a single or double bar; it is customary
* to use the single bar grip for toolbar-rearrangements only,
* and use the double-bar when the toolbar needs to be floated
* or docked.
* The toolbar grip is automatically oriented properly by the
* the toolbar widget, similar to the FXSeparator widget.
* Holding the Control Key while dragging the grip will prevent
* the toolbar from docking when it is near a dock site.
*/
class FXAPI FXToolBarGrip : public FXDockHandler {
  FXDECLARE(FXToolBarGrip)
protected:
  FXColor activeColor;  // Color when active
protected:
  FXToolBarGrip();
private:
  FXToolBarGrip(const FXToolBarGrip&);
  FXToolBarGrip& operator=(const FXToolBarGrip&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
public:

  /// Construct toolbar grip
  FXToolBarGrip(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TOOLBARGRIP_SINGLE,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// The grip can not receive the focus
  virtual FXbool canFocus() const;

  /// Change toolbar grip to double
  void setDoubleBar(FXbool dbl=true);

  /// Return true if toolbar grip is displayed as a double bar
  FXbool isDoubleBar() const;

  /// Set the active color
  void setActiveColor(FXColor clr);

  /// Get the active color
  FXColor getActiveColor() const { return activeColor; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
