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

/// Relationship options for icon-labels
enum {
  ICON_UNDER_TEXT      = 0,			      /// Icon appears under text
  ICON_AFTER_TEXT      = 0x00080000,		      /// Icon appears after text (to its right)
  ICON_BEFORE_TEXT     = 0x00100000,		      /// Icon appears before text (to its left)
  ICON_ABOVE_TEXT      = 0x00200000,		      /// Icon appears above text
  ICON_BELOW_TEXT      = 0x00400000,		      /// Icon appears below text
  TEXT_OVER_ICON       = ICON_UNDER_TEXT,	      /// Same as ICON_UNDER_TEXT
  TEXT_AFTER_ICON      = ICON_BEFORE_TEXT,	      /// Same as ICON_BEFORE_TEXT
  TEXT_BEFORE_ICON     = ICON_AFTER_TEXT,	      /// Same as ICON_AFTER_TEXT
  TEXT_ABOVE_ICON      = ICON_BELOW_TEXT,	      /// Same as ICON_BELOW_TEXT
  TEXT_BELOW_ICON      = ICON_ABOVE_TEXT	      /// Same as ICON_ABOVE_TEXT
  };


/// Normal way to show label
enum {
  LABEL_NORMAL         = JUSTIFY_NORMAL|ICON_BEFORE_TEXT
  };


class FXIcon;
class FXFont;


/**
* A label widget can be used to place a text and/or icon for
* explanation purposes.  The text label may have an optional tooltip
* and/or help string.
*/
class FXLabel : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIconValue(FXObject*,FXSelector,void* PTR_ICON);
  long onCmdGetIconValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  %extend {
    /// Construct label with given text and icon
    FXLabel(FXComposite* p,const FXString& text,FXIcon* ic=0,FXuint opts=LABEL_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbLabel(p,text,ic,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set the text for this label
  void setText(const FXString& text);

  /// Get the text for this label
  FXString getText() const;

  /// Set the icon for this label
  void setIcon(FXIcon* ic);

  /// Get the icon for this label
  FXIcon* getIcon() const;

  /// Set the text font
  void setFont(FXFont *fnt);

  /// Get the text font
  FXFont* getFont() const;

  /// Get the current text color
  FXColor getTextColor() const;

  /// Set the current text color
  void setTextColor(FXColor clr);

  /// Set the current text-justification mode.
  void setJustify(FXuint mode);

  /// Get the current text-justification mode.
  FXuint getJustify() const;

  /// Set the current icon position
  void setIconPosition(FXuint mode);

  /// Get the current icon position
  FXuint getIconPosition() const;

  /// Set the status line help text for this label
  void setHelpText(const FXString& text);

  /// Get the status line help text for this label
  const FXString& getHelpText() const;

  /// Set the tool tip message for this label
  void setTipText(const FXString& text);

  /// Get the tool tip message for this label
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXLabel();
  };


DECLARE_FXOBJECT_VIRTUALS(FXLabel)
DECLARE_FXID_VIRTUALS(FXLabel)
DECLARE_FXDRAWABLE_VIRTUALS(FXLabel)
DECLARE_FXWINDOW_VIRTUALS(FXLabel)

%{
static swig_type_info *FXLabel_dynamic_cast(void **ptr) {
    FXLabel **ppLabel = reinterpret_cast<FXLabel **>(ptr);
    FXButton *pButton=dynamic_cast<FXButton*>(*ppLabel);
    if(pButton){
      *ptr=reinterpret_cast<void*>(pButton);
      return SWIG_TypeQuery("FXButton *");
      }
    FXCheckButton *pCheckButton=dynamic_cast<FXCheckButton*>(*ppLabel);
    if(pCheckButton){
      *ptr=reinterpret_cast<void*>(pCheckButton);
      return SWIG_TypeQuery("FXCheckButton *");
      }
    FXMenuButton *pMenuButton=dynamic_cast<FXMenuButton*>(*ppLabel);
    if(pMenuButton){
      *ptr=reinterpret_cast<void*>(pMenuButton);
      return SWIG_TypeQuery("FXMenuButton *");
      }
    FXOption *pOption=dynamic_cast<FXOption*>(*ppLabel);
    if(pOption){
      *ptr=reinterpret_cast<void*>(pOption);
      return SWIG_TypeQuery("FXOption *");
      }
    FXOptionMenu *pOptionMenu=dynamic_cast<FXOptionMenu*>(*ppLabel);
    if(pOptionMenu){
      *ptr=reinterpret_cast<void*>(pOptionMenu);
      return SWIG_TypeQuery("FXOptionMenu *");
      }
    FXRadioButton *pRadioButton=dynamic_cast<FXRadioButton*>(*ppLabel);
    if(pRadioButton){
      *ptr=reinterpret_cast<void*>(pRadioButton);
      return SWIG_TypeQuery("FXRadioButton *");
      }
    FXTabItem *pTabItem=dynamic_cast<FXTabItem*>(*ppLabel);
    if(pTabItem){
      *ptr=reinterpret_cast<void*>(pTabItem);
      return SWIG_TypeQuery("FXTabItem *");
      }
    FXToggleButton *pToggleButton=dynamic_cast<FXToggleButton*>(*ppLabel);
    if(pToggleButton){
      *ptr=reinterpret_cast<void*>(pToggleButton);
      return SWIG_TypeQuery("FXToggleButton *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXLabel, FXLabel_dynamic_cast);

