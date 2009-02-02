/********************************************************************************
*                                                                               *
*                         M e n u C a p t i o n   W i d g e t                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXMenuCaption.h 2344 2006-02-12 21:19:36Z lyle $                     *
********************************************************************************/
#ifndef FXMENUCAPTION_H
#define FXMENUCAPTION_H

#ifndef FXWINDOW_H
#include "FXWindow.h"
#endif

namespace FX {


/// Menu Caption options
enum {
  MENU_AUTOGRAY = 0x00008000,   /// Automatically gray out when not updated
  MENU_AUTOHIDE = 0x00010000    /// Automatically hide button when not updated
  };


class FXIcon;
class FXFont;


/**
* The menu caption is a widget which can be used as a caption
* above a number of menu commands in a menu.
*/
class FXAPI FXMenuCaption : public FXWindow {
  FXDECLARE(FXMenuCaption)
protected:
  FXString     label;
  FXString     help;
  FXString     tip;
  FXIcon      *icon;
  FXFont      *font;
  FXint        hotoff;
  FXHotKey     hotkey;
  FXColor      textColor;
  FXColor      selbackColor;
  FXColor      seltextColor;
  FXColor      hiliteColor;
  FXColor      shadowColor;
protected:
  FXMenuCaption();
private:
  FXMenuCaption(const FXMenuCaption&);
  FXMenuCaption &operator=(const FXMenuCaption&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUpdate(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdSetIconValue(FXObject*,FXSelector,void*);
  long onCmdGetIconValue(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:

  /// Construct a menu caption
  FXMenuCaption(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXuint opts=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Enable the menu
  virtual void enable();

  /// Disable the menu
  virtual void disable();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Set the text for this menu
  void setText(const FXString& text);

  /// Get the text for this menu
  FXString getText() const { return label; }

  /// Set the icon for this menu
  void setIcon(FXIcon* ic);

  /// Get the icon for this menu
  FXIcon* getIcon() const { return icon; }

  /// Set the text font
  void setFont(FXFont* fnt);

  /// Return the text font
  FXFont* getFont() const { return font; }

  /// Set menu caption style
  void setMenuStyle(FXuint style);

  /// Get menu caption style
  FXuint getMenuStyle() const;

  /// Return the current text color
  void setTextColor(FXColor clr);

  /// Get the current text color
  FXColor getTextColor() const { return textColor; }

  /// Return the selection background color
  void setSelBackColor(FXColor clr);

  /// Return the selection background color
  FXColor getSelBackColor() const { return selbackColor; }

  /// Return the selection text color
  void setSelTextColor(FXColor clr);

  /// Return the selection text color
  FXColor getSelTextColor() const { return seltextColor; }

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Get highlight color
  FXColor getHiliteColor() const { return hiliteColor; }

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Get shadow color
  FXColor getShadowColor() const { return shadowColor; }

  /// Set the status line help text for this menu
  void setHelpText(const FXString& text);

  /// Get the status line help text for this menu
  const FXString& getHelpText() const { return help; }

  /// Set the tool tip message for this menu
  void setTipText(const FXString& text){ tip=text; }

  /// Get the tool tip message for this menu
  const FXString& getTipText() const { return tip; }

  /// Save menu to a stream
  virtual void save(FXStream& store) const;

  /// Load menu from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXMenuCaption();
  };

}

#endif
