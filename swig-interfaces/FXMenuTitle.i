/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

class FXPopup;


/**
* A menu title is a child of a menu bar which is responsible
* for popping up a pulldown menu.
*/
class FXMenuTitle : public FXMenuCaption {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_IGNORE);
  long onFocusUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onFocusDown(FXObject*,FXSelector,void* PTR_IGNORE);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdPost(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdUnpost(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  %extend {
    /// Constructor
    FXMenuTitle(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=0){
      return new FXRbMenuTitle(p,text,ic,pup,opts);
      }
    }

  /// Set popup menu to pop up
  void setMenu(FXPopup *menu);

  /// Return popup menu
  FXPopup* getMenu() const;

  /// Destructor
  virtual ~FXMenuTitle();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMenuTitle)
DECLARE_FXID_VIRTUALS(FXMenuTitle)
DECLARE_FXDRAWABLE_VIRTUALS(FXMenuTitle)
DECLARE_FXWINDOW_VIRTUALS(FXMenuTitle)

