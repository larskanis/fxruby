/********************************************************************************
*                                                                               *
*             M u l t i p l e   D o c u m e n t   B u t t o n                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2003 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMDIButton.h 1642 2003-07-09 22:56:42Z lyle $                       *
********************************************************************************/
#ifndef FXMDIBUTTON_H
#define FXMDIBUTTON_H

#ifndef FXBUTTON_H
#include "FXButton.h"
#endif

namespace FX {

class FXIcon;


/// MDI Delete button
class FXAPI FXMDIDeleteButton : public FXButton {
  FXDECLARE(FXMDIDeleteButton)
protected:
  FXMDIDeleteButton(){}
private:
  FXMDIDeleteButton(const FXMDIDeleteButton&);
  FXMDIDeleteButton &operator=(const FXMDIDeleteButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:
  /// Constructor
  FXMDIDeleteButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0);
  virtual FXint getDefaultWidth();
  virtual FXint getDefaultHeight();
  };


/// MDI Restore button
class FXAPI FXMDIRestoreButton : public FXButton {
  FXDECLARE(FXMDIRestoreButton)
protected:
  FXMDIRestoreButton(){}
private:
  FXMDIRestoreButton(const FXMDIRestoreButton&);
  FXMDIRestoreButton &operator=(const FXMDIRestoreButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:
  /// Constructor
  FXMDIRestoreButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0);
  virtual FXint getDefaultWidth();
  virtual FXint getDefaultHeight();
  };


/// MDI Maximize button
class FXAPI FXMDIMaximizeButton : public FXButton {
  FXDECLARE(FXMDIMaximizeButton)
protected:
  FXMDIMaximizeButton(){}
private:
  FXMDIMaximizeButton(const FXMDIMaximizeButton&);
  FXMDIMaximizeButton &operator=(const FXMDIMaximizeButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:
  /// Constructor
  FXMDIMaximizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0);
  virtual FXint getDefaultWidth();
  virtual FXint getDefaultHeight();
  };


/// MDI Minimize button
class FXAPI FXMDIMinimizeButton : public FXButton {
  FXDECLARE(FXMDIMinimizeButton)
protected:
  FXMDIMinimizeButton(){}
private:
  FXMDIMinimizeButton(const FXMDIMinimizeButton&);
  FXMDIMinimizeButton &operator=(const FXMDIMinimizeButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:
  /// Constructor
  FXMDIMinimizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0);
  virtual FXint getDefaultWidth();
  virtual FXint getDefaultHeight();
  };


/// MDI Window button
class FXAPI FXMDIWindowButton : public FXMenuButton {
  FXDECLARE(FXMDIWindowButton)
protected:
  FXMDIWindowButton(){}
private:
  FXMDIWindowButton(const FXMDIWindowButton&);
  FXMDIWindowButton &operator=(const FXMDIWindowButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:
  /// Constructor
  FXMDIWindowButton(FXComposite* p,FXPopup* pup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);
  virtual FXint getDefaultWidth();
  virtual FXint getDefaultHeight();
  };


/// MDI Window Menu
class FXAPI FXMDIMenu : public FXMenuPane {
  FXDECLARE(FXMDIMenu)
private:
  FXIcon *closeicon;
  FXIcon *maximizeicon;
  FXIcon *minimizeicon;
  FXIcon *restoreicon;
protected:
  FXMDIMenu(){}
private:
  FXMDIMenu(const FXMDIMenu&);
  FXMDIMenu &operator=(const FXMDIMenu&);
public:

  /// Construct MDI menu
  FXMDIMenu(FXWindow *owner,FXObject* tgt=NULL);

  /// Destructor
  virtual ~FXMDIMenu();
  };

}

#endif
