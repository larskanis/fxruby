/********************************************************************************
*                                                                               *
*                        M e n u B u t t o n   W i d g e t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMenuButton.h 2344 2006-02-12 21:19:36Z lyle $                      *
********************************************************************************/
#ifndef FXMENUBUTTON_H
#define FXMENUBUTTON_H

#ifndef FXLABEL_H
#include "FXLabel.h"
#endif

namespace FX {


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
class FXAPI FXMenuButton : public FXLabel {
  FXDECLARE(FXMenuButton)
protected:
  FXPopup *pane;                  // Pane to pop up
  FXint    offsetx;               // Shift attachment point x
  FXint    offsety;               // Shift attachment point y
  FXbool   state;                 // Pane was popped
protected:
  FXMenuButton();
private:
  FXMenuButton(const FXMenuButton&);
  FXMenuButton &operator=(const FXMenuButton&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUpdate(FXObject*,FXSelector,void*);
  long onEnter(FXObject*,FXSelector,void*);
  long onLeave(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onHotKeyPress(FXObject*,FXSelector,void*);
  long onHotKeyRelease(FXObject*,FXSelector,void*);
  long onCmdPost(FXObject*,FXSelector,void*);
  long onCmdUnpost(FXObject*,FXSelector,void*);
public:

  /// Constructor
  FXMenuButton(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=JUSTIFY_NORMAL|ICON_BEFORE_TEXT|MENUBUTTON_DOWN,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Returns true because a menu button can receive focus
  virtual bool canFocus() const;

  /// Remove the focus from this window
  virtual void killFocus();

  /// Return true if window logically contains the given point
  virtual bool contains(FXint parentx,FXint parenty) const;

  /// Change the popup menu
  void setMenu(FXPopup *pup);

  /// Return current popup menu
  FXPopup* getMenu() const { return pane; }

  /// Set X offset where menu pops up relative to button
  void setXOffset(FXint offx){ offsetx=offx; }

  /// Return current X offset
  FXint getXOffset() const { return offsetx; }

  /// Set Y offset where menu pops up relative to button
  void setYOffset(FXint offy){ offsety=offy; }

  /// Return current Y offset
  FXint getYOffset() const { return offsety; }

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

  /// Save menu button to a stream
  virtual void save(FXStream& store) const;

  /// Load menu button from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXMenuButton();
  };

}

#endif
