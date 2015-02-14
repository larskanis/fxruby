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
* The cascade menu widget is used to bring up a sub menu from a
* pull down menu.
*/
class FXMenuCascade : public FXMenuCaption {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onButtonPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onButtonRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPost(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdUnpost(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_MENUTIMER=FXMenuCaption::ID_LAST,
    ID_LAST
    };
public:
  %extend {
    /// Construct a menu cascade responsible for the given popup menu
    FXMenuCascade(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=0){
      return new FXRbMenuCascade(p,text,ic,pup,opts);
      }
    }

  /// Set popup menu to pop up
  void setMenu(FXPopup *pup);

  /// Return popup menu
  FXPopup* getMenu() const;

  /// Destructor
  virtual ~FXMenuCascade();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMenuCascade)
DECLARE_FXID_VIRTUALS(FXMenuCascade)
DECLARE_FXDRAWABLE_VIRTUALS(FXMenuCascade)
DECLARE_FXWINDOW_VIRTUALS(FXMenuCascade)

