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

/// Button state bits
enum {
  STATE_UP        = 0,		  /// Button is up
  STATE_DOWN      = 1,		  /// Button is down
  STATE_ENGAGED   = 2,		  /// Button is engaged
  STATE_UNCHECKED = STATE_UP,	  /// Same as STATE_UP (used for check buttons or radio buttons)
  STATE_CHECKED   = STATE_ENGAGED /// Same as STATE_ENGAGED (used for check buttons or radio buttons)
  };


enum {
  BUTTON_AUTOGRAY  = 0x00800000,  /// Automatically gray out when not updated
  BUTTON_AUTOHIDE  = 0x01000000,  /// Automatically hide button when not updated
  BUTTON_TOOLBAR   = 0x02000000,  /// Toolbar style button [flat look]
  BUTTON_DEFAULT   = 0x04000000,  /// May become default button when receiving focus
  BUTTON_INITIAL   = 0x08000000,  /// This button is the initial default button
  BUTTON_NORMAL    = (FRAME_RAISED|FRAME_THICK|JUSTIFY_NORMAL|ICON_BEFORE_TEXT)
  };

/// FXButton provides a push button. Buttons can have icons and/or labels.
class FXButton : public FXLabel {
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
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
public:
  %extend {
    /// Construct button with text and icon
    FXButton(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=BUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbButton(p,text,ic,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set the button state
  void setState(FXuint s);

  /// Get the button state
  FXuint getState() const;

  /// Set the button style flags
  void setButtonStyle(FXuint style);

  /// Get the button style flags
  FXuint getButtonStyle() const;

  /// Destructor
  virtual ~FXButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXButton)
DECLARE_FXID_VIRTUALS(FXButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXButton)
DECLARE_FXWINDOW_VIRTUALS(FXButton)

%{
static swig_type_info *FXButton_dynamic_cast(void **ptr) {
    FXButton **ppButton = reinterpret_cast<FXButton **>(ptr);
    FXMDIDeleteButton *pMDIDeleteButton=dynamic_cast<FXMDIDeleteButton*>(*ppButton);
    if(pMDIDeleteButton){
      *ptr=reinterpret_cast<void*>(pMDIDeleteButton);
      return SWIG_TypeQuery("FXMDIDeleteButton *");
      }
    FXMDIMaximizeButton *pMDIMaximizeButton=dynamic_cast<FXMDIMaximizeButton*>(*ppButton);
    if(pMDIMaximizeButton){
      *ptr=reinterpret_cast<void*>(pMDIMaximizeButton);
      return SWIG_TypeQuery("FXMDIMaximizeButton *");
      }
    FXMDIMinimizeButton *pMDIMinimizeButton=dynamic_cast<FXMDIMinimizeButton*>(*ppButton);
    if(pMDIMinimizeButton){
      *ptr=reinterpret_cast<void*>(pMDIMinimizeButton);
      return SWIG_TypeQuery("FXMDIMinimizeButton *");
      }
    FXMDIRestoreButton *pMDIRestoreButton=dynamic_cast<FXMDIRestoreButton*>(*ppButton);
    if(pMDIRestoreButton){
      *ptr=reinterpret_cast<void*>(pMDIRestoreButton);
      return SWIG_TypeQuery("FXMDIRestoreButton *");
      }
    FXPicker *pPicker=dynamic_cast<FXPicker*>(*ppButton);
    if(pPicker){
      *ptr=reinterpret_cast<void*>(pPicker);
      return SWIG_TypeQuery("FXPicker *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXButton, FXButton_dynamic_cast);

