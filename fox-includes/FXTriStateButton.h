/********************************************************************************
*                                                                               *
*               T r i - S t a t e    B u t t o n    W i d g e t                 *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002 by Charles Warren.   All Rights Reserved.                  *
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
* $Id: FXTriStateButton.h 1166 2002-12-19 18:11:19Z lyle $                   *
********************************************************************************/
#ifndef FXTRISTATEBUTTON_H
#define FXTRISTATEBUTTON_H

#ifndef FXTOGGLEBUTTON_H
#include "FXToggleButton.h"
#endif


namespace FX {

/**
* The tri-state button provides a three-state button, which toggles between the
* on and the off state each time it is pressed; programmatically, it may also be
* switched into the MAYBE state.  The MAYBE state is useful to signify an unknown
* state in the application data.
* Like the toggle button, it sends a SEL_COMMAND to its target, with the
* message data set to the current state of the toggle button, of the type FXbool.
*/
class FXAPI FXTriStateButton : public FXToggleButton {
  FXDECLARE(FXTriStateButton)
protected:
  FXString  maybelabel;
  FXIcon   *maybeicon;
  FXString  maybetip;
  FXString  maybehelp;
protected:
  FXTriStateButton();
private:
  FXTriStateButton(const FXTriStateButton&);
  FXTriStateButton& operator=(const FXTriStateButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUnknown(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:

  /// Construct tri-state toggle button with three text labels, and three icons, one for each state
  FXTriStateButton(FXComposite* p,const FXString& text1,const FXString& text2,const FXString& text3,FXIcon* icon1=NULL,FXIcon* icon2=NULL,FXIcon* icon3=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TOGGLEBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Get default width
  virtual FXint getDefaultWidth();

  /// Get default height
  virtual FXint getDefaultHeight();

  /// Change maybe text shown when toggled
  void setMaybeText(const FXString& text);

  /// Return maybe text
  FXString getMaybeText() const { return maybelabel; }

  /// Change maybe icon shown when toggled
  void setMaybeIcon(FXIcon* ic);

  /// Return maybe icon
  FXIcon* getMaybeIcon() const { return maybeicon; }

  /// Change maybe help text shown when toggled
  void setMaybeHelpText(const FXString& text);

  /// Return maybe help text
  FXString getMaybeHelpText() const { return maybehelp; }

  /// Change maybe tip text shown when toggled
  void setMaybeTipText(const FXString& text);

  /// Return maybe tip text
  FXString getMaybeTipText() const { return maybetip; }

  /// Save toggle button to a stream
  virtual void save(FXStream& store) const;

  /// Load toggle button from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXTriStateButton();
  };

}

#endif
