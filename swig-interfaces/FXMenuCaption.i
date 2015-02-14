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

/// Menu Caption options
enum {
  MENU_AUTOGRAY = 0x00008000,   /// Automatically gray out when not updated
  MENU_AUTOHIDE = 0x00010000    /// Automatically hide button when not updated
  };


class FXIcon;
class FXFont;

%rename("tipText=") FXMenuCaption::setTipText(const FXString& text);
%rename("tipText")  FXMenuCaption::getTipText() const;

/**
* The menu caption is a widget which can be used as a caption
* above a number of menu commands in a menu.
*/
class FXMenuCaption : public FXWindow {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIconValue(FXObject*,FXSelector,void* PTR_ICON);
  long onCmdGetIconValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:
  %extend {
    /// Construct a new menu caption
    FXMenuCaption(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXuint opts=0){
      return new FXRbMenuCaption(p,text,ic,opts);
      }
    }

  /// Set the text for this menu
  void setText(const FXString& text);

  /// Get the text for this menu
  FXString getText() const;

  /// Set the icon for this menu
  void setIcon(FXIcon* ic);

  /// Get the icon for this menu
  FXIcon* getIcon() const;

  /// Set the text font
  void setFont(FXFont* fnt);

  /// Return the text font
  FXFont* getFont() const;

  /// Set menu caption style
  void setMenuStyle(FXuint style);

  /// Get menu caption style
  FXuint getMenuStyle() const;

  /// Get the current text color
  FXColor getTextColor() const;

  /// Return the current text color
  void setTextColor(FXColor clr);

  /// Return the selection background color
  FXColor getSelBackColor() const;

  /// Set the selection background color
  void setSelBackColor(FXColor clr);

  /// Return the selection text color
  FXColor getSelTextColor() const;

  /// Set the selection text color
  void setSelTextColor(FXColor clr);

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Get highlight color
  FXColor getHiliteColor() const;

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Get shadow color
  FXColor getShadowColor() const;

  /// Set the status line help text for this menu
  void setHelpText(const FXString& text);

  /// Get the status line help text for this menu
  const FXString& getHelpText() const;

  /// Set the tool tip message for this menu
  void setTipText(const FXString& text);

  /// Get the tool tip message for this menu
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXMenuCaption();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMenuCaption)
DECLARE_FXID_VIRTUALS(FXMenuCaption)
DECLARE_FXDRAWABLE_VIRTUALS(FXMenuCaption)
DECLARE_FXWINDOW_VIRTUALS(FXMenuCaption)

%{
static swig_type_info *FXMenuCaption_dynamic_cast(void **ptr) {
    FXMenuCaption **ppMenuCaption = reinterpret_cast<FXMenuCaption **>(ptr);
    FXMenuCascade *pMenuCascade=dynamic_cast<FXMenuCascade*>(*ppMenuCaption);
    if(pMenuCascade){
      *ptr=reinterpret_cast<void*>(pMenuCascade);
      return SWIG_TypeQuery("FXMenuCascade *");
      }
    FXMenuCommand *pMenuCommand=dynamic_cast<FXMenuCommand*>(*ppMenuCaption);
    if(pMenuCommand){
      *ptr=reinterpret_cast<void*>(pMenuCommand);
      return SWIG_TypeQuery("FXMenuCommand *");
      }
    FXMenuTitle *pMenuTitle=dynamic_cast<FXMenuTitle*>(*ppMenuCaption);
    if(pMenuTitle){
      *ptr=reinterpret_cast<void*>(pMenuTitle);
      return SWIG_TypeQuery("FXMenuTitle *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXMenuCaption, FXMenuCaption_dynamic_cast);

