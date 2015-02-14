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


// Menu button options
enum {
  MENUBUTTON_AUTOGRAY      = 0x00800000,                                      /// Automatically gray out when no target
  MENUBUTTON_AUTOHIDE      = 0x01000000,                                      /// Automatically hide when no target
  MENUBUTTON_TOOLBAR       = 0x02000000,                                      /// Toolbar style
  MENUBUTTON_DOWN          = 0,                                               /// Popup window appears below menu button
  MENUBUTTON_UP            = 0x04000000,                                      /// Popup window appears above menu button
  MENUBUTTON_LEFT          = 0x08000000,                                      /// Popup window to the left of the menu button
  MENUBUTTON_RIGHT         = MENUBUTTON_LEFT|MENUBUTTON_UP,                   /// Popup window to the right of the menu button
  MENUBUTTON_NOARROWS      = 0x10000000,                                      /// Do not show arrows
  MENUBUTTON_ATTACH_LEFT   = 0,                                               /// Popup attaches to the left side of the menu button
  MENUBUTTON_ATTACH_TOP    = MENUBUTTON_ATTACH_LEFT,                          /// Popup attaches to the top of the menu button
  MENUBUTTON_ATTACH_RIGHT  = 0x20000000,                                      /// Popup attaches to the right side of the menu button
  MENUBUTTON_ATTACH_BOTTOM = MENUBUTTON_ATTACH_RIGHT,                         /// Popup attaches to the bottom of the menu button
  MENUBUTTON_ATTACH_CENTER = 0x40000000,                                      /// Popup attaches to the center of the menu button
  MENUBUTTON_ATTACH_BOTH   = MENUBUTTON_ATTACH_CENTER|MENUBUTTON_ATTACH_RIGHT /// Popup attaches to both sides of the menu button
  };


/**
* A menu button posts a popup menu when clicked.
* There are many ways to control the placement where the popup will appear;
* first, the popup may be placed on either of the four sides relative to the
* menu button; this is controlled by the flags MENUBUTTON_DOWN, etc.
* Next, there are several attachment modes; the popup's left/bottom edge may
* attach to the menu button's left/top edge, or the popup's right/top edge may
* attach to the menu button's right/bottom edge, or both.
* Also, the popup may apear centered relative to the menu button.
* Finally, a small offset may be specified to displace the location of the
* popup by a few pixels so as to account for borders and so on.
* Normally, the menu button shows an arrow pointing to the direction where
* the popup is set to appear; this can be turned off by passing the option
* MENUBUTTON_NOARROWS.
*/
class FXMenuButton : public FXLabel {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdPost(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdUnpost(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXMenuButton(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=JUSTIFY_NORMAL|ICON_BEFORE_TEXT|MENUBUTTON_DOWN,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbMenuButton(p,text,ic,pup,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change the popup menu
  void setMenu(FXPopup *pup);

  /// Return current popup menu
  FXPopup* getMenu() const;

  /// Set X offset where menu pops up relative to button
  void setXOffset(FXint offx);

  /// Return current X offset
  FXint getXOffset() const;

  /// Set Y offset where menu pops up relative to button
  void setYOffset(FXint offy);

  /// Return current Y offset
  FXint getYOffset() const;

  /// Change menu button style
  void setButtonStyle(FXuint style);

  /// Get menu button style
  FXuint getButtonStyle() const;

  /// Change popup style
  void setPopupStyle(FXuint style);

  /// Get popup style
  FXuint getPopupStyle() const;

  /// Change attachment
  void setAttachment(FXuint att);

  /// Get attachment
  FXuint getAttachment() const;

  /// Destructor
  virtual ~FXMenuButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMenuButton)
DECLARE_FXID_VIRTUALS(FXMenuButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXMenuButton)
DECLARE_FXWINDOW_VIRTUALS(FXMenuButton)

%{
static swig_type_info *FXMenuButton_dynamic_cast(void **ptr) {
    FXMenuButton **ppMenuButton = reinterpret_cast<FXMenuButton **>(ptr);
    FXMDIWindowButton *pMDIWindowButton=dynamic_cast<FXMDIWindowButton*>(*ppMenuButton);
    if(pMDIWindowButton){
      *ptr=reinterpret_cast<void*>(pMDIWindowButton);
      return SWIG_TypeQuery("FXMDIWindowButton *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXMenuButton, FXMenuButton_dynamic_cast);

