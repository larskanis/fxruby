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

class FXIcon;


/// MDI Delete button
class FXMDIDeleteButton : public FXButton {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXMDIDeleteButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbMDIDeleteButton(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Destructor
  virtual ~FXMDIDeleteButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIDeleteButton)
DECLARE_FXID_VIRTUALS(FXMDIDeleteButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIDeleteButton)
DECLARE_FXWINDOW_VIRTUALS(FXMDIDeleteButton)


/// MDI Restore button
class FXMDIRestoreButton : public FXButton {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXMDIRestoreButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbMDIRestoreButton(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Destructor
  virtual ~FXMDIRestoreButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIRestoreButton)
DECLARE_FXID_VIRTUALS(FXMDIRestoreButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIRestoreButton)
DECLARE_FXWINDOW_VIRTUALS(FXMDIRestoreButton)


/// MDI Maximize button
class FXMDIMaximizeButton : public FXButton {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXMDIMaximizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbMDIMaximizeButton(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Destructor
  virtual ~FXMDIMaximizeButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIMaximizeButton)
DECLARE_FXID_VIRTUALS(FXMDIMaximizeButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIMaximizeButton)
DECLARE_FXWINDOW_VIRTUALS(FXMDIMaximizeButton)


/// MDI Minimize button
class FXMDIMinimizeButton : public FXButton {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXMDIMinimizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbMDIMinimizeButton(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Destructor
  virtual ~FXMDIMinimizeButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIMinimizeButton)
DECLARE_FXID_VIRTUALS(FXMDIMinimizeButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIMinimizeButton)
DECLARE_FXWINDOW_VIRTUALS(FXMDIMinimizeButton)


/// MDI Window button
class FXMDIWindowButton : public FXMenuButton {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXMDIWindowButton(FXComposite* p,FXPopup* pup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbMDIWindowButton(p,pup,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Destructor
  virtual ~FXMDIWindowButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIWindowButton)
DECLARE_FXID_VIRTUALS(FXMDIWindowButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIWindowButton)
DECLARE_FXWINDOW_VIRTUALS(FXMDIWindowButton)


/// MDI Window Menu
class FXMDIMenu : public FXMenuPane {
public:
  %extend {
    /// Construct MDI menu
    FXMDIMenu(FXWindow *owner,FXObject* tgt=NULL){
      return new FXRbMDIMenu(owner,tgt);
      }
    }

  /// Destructor
  virtual ~FXMDIMenu();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIMenu)
DECLARE_FXID_VIRTUALS(FXMDIMenu)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIMenu)
DECLARE_FXWINDOW_VIRTUALS(FXMDIMenu)
DECLARE_FXPOPUP_VIRTUALS(FXMDIMenu)

