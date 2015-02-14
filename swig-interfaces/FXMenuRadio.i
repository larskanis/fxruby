/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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
* The menu radio widget is used to invoke a command in the
* application from a menu.  Menu commands may reflect
* the state of the application by graying out, becoming hidden,
* or by a bullit.
* When activated, a menu radio sends a SEL_COMMAND to its target;
* the void* argument of the message contains the new state.
* A collection of menu radio widgets which belong to each other
* is supposed to be updated by a common SEL_UPDATE handler to
* properly maintain the state between them.
*/
class FXMenuRadio : public FXMenuCommand {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onButtonPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onButtonRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCheck(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUncheck(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUnknown(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdAccel(FXObject*,FXSelector,void* PTR_IGNORE);
public:

  %extend {
    /// Construct a menu radio
    FXMenuRadio(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0){
      return new FXRbMenuRadio(p,text,tgt,sel,opts);
      }
    }

  /// Set radio button state (TRUE, FALSE or MAYBE)
  void setCheck(FXbool s=TRUE);

  /// Get radio button state (TRUE, FALSE or MAYBE)
  %extend {
    FXbool getCheck() const {
      rb_warning("FXMenuRadio#getCheck is deprecated; use checked?, unchecked? or maybe?");
      return self->getCheck();
      }
    FXuchar getCheckState() const { return self->getCheck(); }
  }

  /// Get the radio background color
  FXColor getRadioColor() const;

  /// Set the radio background color
  void setRadioColor(FXColor clr);

  /// Destructor
  virtual ~FXMenuRadio();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMenuRadio)
DECLARE_FXID_VIRTUALS(FXMenuRadio)
DECLARE_FXDRAWABLE_VIRTUALS(FXMenuRadio)
DECLARE_FXWINDOW_VIRTUALS(FXMenuRadio)
