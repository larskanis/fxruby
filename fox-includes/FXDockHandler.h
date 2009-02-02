/********************************************************************************
*                                                                               *
*                       D o c k H a n d l e r   W i d g e t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDockHandler.h 2725 2007-11-16 16:57:54Z lyle $                      *
********************************************************************************/
#ifndef FXDOCKHANDLER_H
#define FXDOCKHANDLER_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/**
* The dock handler exists as a common base class for tool bar grip
* and dock title.
*/
class FXAPI FXDockHandler : public FXFrame {
  FXDECLARE_ABSTRACT(FXDockHandler)
protected:
  FXString  tip;        // Tool tip
  FXString  help;       // Help string
private:
  FXID      xxx;
protected:
  FXDockHandler();
private:
  FXDockHandler(const FXDockHandler&);
  FXDockHandler& operator=(const FXDockHandler&);
public:
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
protected:
  FXDockHandler(FXComposite* p,FXObject* tgt,FXSelector sel,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb);
public:

  /// The grip can receive the focus
  virtual FXbool canFocus() const;

  /// Set the status line help text for grip
  void setHelpText(const FXString& text){ help=text; }

  /// Get the status line help text for grip
  const FXString& getHelpText() const { return help; }

  /// Set the tool tip message for the grip
  void setTipText(const FXString& text){ tip=text; }

  /// Get the tool tip message for the grip
  const FXString& getTipText() const { return tip; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);
  };

}

#endif
