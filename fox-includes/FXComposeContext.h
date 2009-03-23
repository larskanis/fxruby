/********************************************************************************
*                                                                               *
*                         C o m p o s e - C o n t e x t                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXComposeContext.h,v 1.14 2009/01/06 13:07:22 fox Exp $                  *
********************************************************************************/
#ifndef FXCOMPOSECONTEXT_H
#define FXCOMPOSECONTEXT_H

#ifndef FXID_H
#include "FXId.h"
#endif

namespace FX {


class FXApp;
class FXWindow;
class FXFont;

/**
* Compose Context manages the state of an input method
* if input method support is enabled.
*/
class FXAPI FXComposeContext : public FXId {
  FXDECLARE(FXComposeContext)
protected:
  FXWindow  *window;            // Window we belong to
  FXSelector message;           // Message to send it
private:
#ifndef WIN32
  void* fontset;
  static int  editStartCallback(void*,FXComposeContext*,void*);
  static void editDoneCallback(void*,FXComposeContext*,void*);
  static void editDrawCallback(void*,FXComposeContext*,void*);
  static void editCaretCallback(void*,FXComposeContext*,void*);
  static void statusStartCallback(void*,FXComposeContext*,void*);
  static void statusDoneCallback(void*,FXComposeContext*,void*);
  static void statusDrawCallback(void*,FXComposeContext*,void*);
#endif
protected:
  FXComposeContext();
private:
  FXComposeContext(const FXComposeContext&);
  FXComposeContext &operator=(const FXComposeContext&);
public:

  /// Construct compose context for given window
  FXComposeContext(FXApp* a,FXWindow* win=NULL,FXSelector sel=0);

  /// Create resource
  virtual void create();

  /// Destroy resource
  virtual void destroy();

  /// Focus in
  void focusIn();

  /// Focus out
  void focusOut();

  /// Set the font
  void setFont(FXFont* fnt);

  /// Set the spot
  void setSpot(FXint x,FXint y);

  /// Set the area
  void setArea(FXint x,FXint y,FXint w,FXint h);

  /// Translate key event
  FXString translateEvent(FXRawEvent& event);

  /// Destructor
  virtual ~FXComposeContext();
  };

}

#endif
