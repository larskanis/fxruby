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

/// Toggle button flags
enum {
  TOGGLEBUTTON_AUTOGRAY = 0x00800000,       /// Automatically gray out when not updated
  TOGGLEBUTTON_AUTOHIDE = 0x01000000,       /// Automatically hide toggle button when not updated
  TOGGLEBUTTON_TOOLBAR  = 0x02000000,       /// Toolbar style toggle button [flat look]
  TOGGLEBUTTON_KEEPSTATE= 0x04000000,       /// Draw button according to state
  TOGGLEBUTTON_NORMAL   = FRAME_RAISED|FRAME_THICK|JUSTIFY_NORMAL|ICON_BEFORE_TEXT
  };


/// Toggle Button
class FXToggleButton : public FXLabel {
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
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:

  /// Construct toggle button with two text labels, and two icons, one for each state
  %extend {
    FXToggleButton(FXComposite* p,const FXString& text1,const FXString& text2,FXIcon* icon1=NULL,FXIcon* icon2=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TOGGLEBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbToggleButton(p,text1,text2,icon1,icon2,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change alternate text shown when toggled
  void setAltText(const FXString& text);

  /// Return alternate text
  FXString getAltText() const;

  /// Change alternate icon shown when toggled
  void setAltIcon(FXIcon* ic);

  /// Return alternate icon
  FXIcon* getAltIcon() const;

  /// Change toggled state
  void setState(FXbool s=TRUE,FXbool notify=FALSE);

  /// return toggled state
  FXbool getState() const;

  /// Change alternate help text shown when toggled
  void setAltHelpText(const FXString& text);

  /// Return alternate help text
  FXString getAltHelpText() const;

  /// Change alternate tip text shown when toggled
  void setAltTipText(const FXString& text);

  /// Return alternate tip text
  FXString getAltTipText() const;

  /// Set the toggle button style flags
  void setToggleStyle(FXuint style);

  /// Get the toggle button style flags
  FXuint getToggleStyle() const;

  /// Destructor
  virtual ~FXToggleButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXToggleButton)
DECLARE_FXID_VIRTUALS(FXToggleButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXToggleButton)
DECLARE_FXWINDOW_VIRTUALS(FXToggleButton)

%{
static swig_type_info *FXToggleButton_dynamic_cast(void **ptr) {
    FXToggleButton **ppToggleButton = reinterpret_cast<FXToggleButton **>(ptr);
    FXTriStateButton *pTriStateButton=dynamic_cast<FXTriStateButton*>(*ppToggleButton);
    if(pTriStateButton){
      *ptr=reinterpret_cast<void*>(pTriStateButton);
      return SWIG_TypeQuery("FXTriStateButton *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXToggleButton, FXToggleButton_dynamic_cast);

