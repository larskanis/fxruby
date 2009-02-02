/********************************************************************************
*                                                                               *
*                        M e n u C a s c a d e   W i d g e t                    *
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
* $Id: FXMenuCascade.h 2344 2006-02-12 21:19:36Z lyle $                     *
********************************************************************************/
#ifndef FXMENUCASCADE_H
#define FXMENUCASCADE_H

#ifndef FXMENUCAPTION_H
#include "FXMenuCaption.h"
#endif

namespace FX {


class FXPopup;


/**
* The cascade menu widget is used to bring up a sub menu from a
* pull down menu.
*/
class FXAPI FXMenuCascade : public FXMenuCaption {
  FXDECLARE(FXMenuCascade)
protected:
  FXPopup *pane;
protected:
  FXMenuCascade();
  void drawTriangle(FXDCWindow& dc,FXint l,FXint t,FXint r,FXint b);
private:
  FXMenuCascade(const FXMenuCascade&);
  FXMenuCascade &operator=(const FXMenuCascade&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onButtonPress(FXObject*,FXSelector,void*);
  long onButtonRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
  long onCmdPost(FXObject*,FXSelector,void*);
  long onCmdUnpost(FXObject*,FXSelector,void*);
public:
  enum {
    ID_MENUTIMER=FXMenuCaption::ID_LAST,
    ID_LAST
    };
public:

  /// Construct a menu cascade responsible for the given popup menu
  FXMenuCascade(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Yes it can receive the focus
  virtual bool canFocus() const;

  /// Move the focus to this window
  virtual void setFocus();

  /// Remove the focus from this window
  virtual void killFocus();

  /// Set popup menu to pop up
  void setMenu(FXPopup *pup){ pane = pup; }

  /// Return popup menu
  FXPopup* getMenu() const { return pane; }

  /// True if this menu or is popup logically contains the mouse
  virtual bool contains(FXint parentx,FXint parenty) const;

  /// Save menu to a stream
  virtual void save(FXStream& store) const;

  /// Load menu from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXMenuCascade();
  };

}

#endif
