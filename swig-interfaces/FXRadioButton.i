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

/// RadioButton flags
enum {
  RADIOBUTTON_AUTOGRAY = 0x00800000,  /// Automatically gray out when not updated
  RADIOBUTTON_AUTOHIDE = 0x01000000,  /// Automatically hide when not updated
  RADIOBUTTON_NORMAL   = JUSTIFY_NORMAL|ICON_BEFORE_TEXT
  };

/**
* A radio button is a tri-state button.  Normally, it is either
* TRUE or FALSE; a third state MAYBE may be set to indicate that no selection
* has been made yet by the user, or that the state is ambiguous.
* When pressed, the radio button sets its state to TRUE and sends a SEL_COMMAND
* to its target, and the message data set to the state of the radio button,
* of the type FXbool.
* A group of radio buttons can be made mutually exclusive by linking them
* to a common data target.  Alternatively, an application can implement a
* common SEL_UPDATED handler to check and uncheck radio buttons as appropriate.
*/
class FXRadioButton : public FXLabel {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_NULL);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCheck(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUncheck(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUnknown(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:

  /// Construct new radio button
  %extend {
    FXRadioButton(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=RADIOBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbRadioButton(p,text,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set radio button state (TRUE, FALSE or MAYBE)
  void setCheck(FXbool s=TRUE,FXbool notify=FALSE);

  /// Get radio button state (TRUE, FALSE or MAYBE)
  %extend {
    FXbool getCheck() const {
      rb_warning("FXRadioButton#getCheck is deprecated; use checked?, unchecked? or maybe?");
      return self->getCheck();
      }
    FXuchar getCheckState() const { return self->getCheck(); }
  }

  /// Change radio button style
  void setRadioButtonStyle(FXuint style);

  /// Return current radio button style
  FXuint getRadioButtonStyle() const;

  /// Get the radio ball color
  FXColor getRadioColor() const;

  /// Set the radio ball color
  void setRadioColor(FXColor clr);

  /// Get the radio disk color
  FXColor getDiskColor() const;

  /// Set the radio disk color
  void setDiskColor(FXColor clr);

  /// Destructor
  virtual ~FXRadioButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXRadioButton)
DECLARE_FXID_VIRTUALS(FXRadioButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXRadioButton)
DECLARE_FXWINDOW_VIRTUALS(FXRadioButton)

