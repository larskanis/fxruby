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

/**
* The menu command widget is used to invoke a command in the
* application from a menu.  Menu commands may reflect
* the state of the application by graying out, or becoming hidden.
* When activated, a menu command sends a SEL_COMMAND to its target.
*/
class FXMenuCommand : public FXMenuCaption {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onButtonPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onButtonRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdAccel(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  %extend {
    /// Construct a menu command
    FXMenuCommand(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0){
      return new FXRbMenuCommand(p,text,ic,tgt,sel,opts);
      }
    }

  /// Set accelerator text
  void setAccelText(const FXString& text);

  /// Return accelarator text
  FXString getAccelText() const;

  /// Destructor
  virtual ~FXMenuCommand();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMenuCommand)
DECLARE_FXID_VIRTUALS(FXMenuCommand)
DECLARE_FXDRAWABLE_VIRTUALS(FXMenuCommand)
DECLARE_FXWINDOW_VIRTUALS(FXMenuCommand)

