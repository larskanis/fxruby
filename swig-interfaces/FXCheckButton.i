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

/// CheckButton styles
enum {
  CHECKBUTTON_AUTOGRAY = 0x00800000,    /// Automatically gray out when not updated
  CHECKBUTTON_AUTOHIDE = 0x01000000,    /// Automatically hide when not updated
  CHECKBUTTON_PLUS     = 0x02000000,    /// Draw a + for unchecked and - for checked
  CHECKBUTTON_NORMAL   = JUSTIFY_NORMAL|ICON_BEFORE_TEXT
  };


/// Check button
class FXCheckButton : public FXLabel {
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
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCheck(FXObject*,FXSelector,void* PTR_NULL);
  long onUncheck(FXObject*,FXSelector,void* PTR_NULL);
  long onUnknown(FXObject*,FXSelector,void* PTR_NULL);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
public:
  %extend {
    /// Construct new check button
    FXCheckButton(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=CHECKBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbCheckButton(p,text,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set check button state (TRUE, FALSE or MAYBE)
  void setCheck(FXbool state=TRUE, FXbool notify=FALSE);

  /// Get check button state (TRUE, FALSE or MAYBE)
  %extend {
    FXbool getCheck() const {
      rb_warning("FXCheckButton#getCheck is deprecated; use checked?, unchecked? or maybe?");
      return self->getCheck();
      }
    FXuchar getCheckState() const { return self->getCheck(); }
  }

  /// Change check button style
  void setCheckButtonStyle(FXuint style);

  /// Return current check button style
  FXuint getCheckButtonStyle() const;

  /// Get the box background color
  FXColor getBoxColor() const;

  /// Set the box background color
  void setBoxColor(FXColor clr);

  /// Get the box check color
  FXColor getCheckColor() const;

  /// Set the box check color
  void setCheckColor(FXColor clr);

  /// Destructor
  virtual ~FXCheckButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXCheckButton)
DECLARE_FXID_VIRTUALS(FXCheckButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXCheckButton)
DECLARE_FXWINDOW_VIRTUALS(FXCheckButton)

