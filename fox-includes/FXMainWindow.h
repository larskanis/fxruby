/********************************************************************************
*                                                                               *
*                     M a i n   W i n d o w   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMainWindow.h 2127 2005-08-07 20:21:35Z lyle $                      *
********************************************************************************/
#ifndef FXMAINWINDOW_H
#define FXMAINWINDOW_H

#ifndef FXTOPWINDOW_H
#include "FXTopWindow.h"
#endif

namespace FX {


/**
* The Main Window is usually the central window of an application.  Applications
* may have any number of main windows.
* When a MainWindow is closed, it sends a SEL_CLOSE message to its target; the target
* should return 0 if there is no objection against proceeding with the close, and
* return 1 otherwise.
* After the SEL_CLOSE message has been sent and no objection was raised, the main
* window will delete itself.
*/
class FXAPI FXMainWindow : public FXTopWindow {
  FXDECLARE(FXMainWindow)
protected:
  FXMainWindow(){}
private:
  FXMainWindow(const FXMainWindow&);
  FXMainWindow &operator=(const FXMainWindow&);
public:

  /// Construct a main window
  FXMainWindow(FXApp* a,const FXString& name,FXIcon *ic=NULL,FXIcon *mi=NULL,FXuint opts=DECOR_ALL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0,FXint hs=0,FXint vs=0);

  /// Create server-side resources
  virtual void create();

  /// Destructor
  virtual ~FXMainWindow();
  };

}

#endif
