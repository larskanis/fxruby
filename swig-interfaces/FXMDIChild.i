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

class FXMDIClient;
class FXMenuButton;
class FXButton;
class FXFont;



/// MDI Child Window styles
enum {
  MDI_NORMAL    = 0,                /// Normal display mode
  MDI_MAXIMIZED = 0x00001000,       /// Window appears maximized
  MDI_MINIMIZED = 0x00002000,       /// Window is iconified or minimized
  MDI_TRACKING  = 0x00004000        /// Track continuously during dragging
  };


/**
* The MDI child window contains the application work area in a Multiple Document
* Interface application.  GUI Controls are connected to the MDI child via delegation
* through the MDI client, which forwards messages it receives to the active MDI child.
* The MDI child itself tries to further delegate messages to its single content window,
* and if not handled there, to its target object.
* When the MDI child is maximized, it sends a SEL_MAXIMIZE message; when the MDI
* child is minimized, it sends a SEL_MINIMIZE message.  When it is restored, it
* sends a SEL_RESTORE message to its target.  The MDI child also notifies its
* target when it becomes the active MDI child, via the SEL_SELECTED message.
* The void* in the SEL_SELECTED message refers to the previously active MDI child,
* if any.  When an MDI child ceases to be the active one, a SEL_DESELECTED message
* is sent.  The void* in the SEL_DESELECTED message refers to the newly activated
* MDI child, if any.  Thus, interception of SEL_SELECTED and SEL_DESELECTED allows
* the target object to determine whether the user switched between MDI windows of
* the same document (target) or between MDI windows belonging to the same document.
* When the MDI child is closed, it sends a SEL_CLOSE message to its target.
* The target has an opportunity to object to the closing; if the MDI child should
* not be closed, it should return 1 (objection). If the MDI child should be closed,
* the target can either just return 0 or simply not handle the SEL_CLOSE message.
* The SEL_UPDATE message can be used to modify the MDI child's title (via
* ID_SETSTRINGVALUE), and window icon (via ID_SETICONVALUE).
*/
class FXMDIChild : public FXComposite {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelected(FXObject*,FXSelector,void* PTR_MDICHILD);
  long onDeselected(FXObject*,FXSelector,void* PTR_MDICHILD);
  long onCmdClose(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdClose(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRestore(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdRestore(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMaximize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMaximize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdWindow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuRestore(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuClose(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuWindow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_STRING); // FIXME
  long onCmdSetIconValue(FXObject*,FXSelector,void* PTR_STRING); // FIXME
  long onCmdGetIconValue(FXObject*,FXSelector,void* PTR_STRING); // FIXME
public:
  %extend {
    /// Construct MDI Child window with given name and icon
    FXMDIChild(FXMDIClient* p,const FXString& name,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbMDIChild(p,name,ic,pup,opts,x,y,w,h);
      }
    }

  /// Change normal (restored) position
  void setNormalX(FXint x);
  void setNormalY(FXint y);
  void setNormalWidth(FXint w);
  void setNormalHeight(FXint h);

  /// Return normal (restored) position
  FXint getNormalX() const;
  FXint getNormalY() const;
  FXint getNormalWidth() const;
  FXint getNormalHeight() const;

  /// Change iconified position
  void setIconX(FXint x);
  void setIconY(FXint y);
  void setIconWidth(FXint w);
  void setIconHeight(FXint h);

  /// Return iconified position
  FXint getIconX() const;
  FXint getIconY() const;
  FXint getIconWidth() const;
  FXint getIconHeight() const;

  /// Return content window
  FXWindow *contentWindow() const;

  /// Change MDI Child's title
  void setTitle(const FXString& name);

  /// Get current title
  FXString getTitle() const;

  /// Get colors
  FXColor getHiliteColor() const;
  FXColor getShadowColor() const;
  FXColor getBaseColor() const;
  FXColor getBorderColor() const;
  FXColor getTitleColor () const;
  FXColor getTitleBackColor() const;

  /// Change colors
  void setHiliteColor(FXColor clr);
  void setShadowColor(FXColor clr);
  void setBaseColor(FXColor clr);
  void setBorderColor(FXColor clr);
  void setTitleColor(FXColor clr);
  void setTitleBackColor(FXColor clr);

  /// Return TRUE if maximized
  FXbool isMaximized() const;

  /// Return TRUE if minimized
  FXbool isMinimized() const;

  /// Get window icon
  FXIcon *getIcon() const;

  /// Set window icon
  void setIcon(FXIcon* icon);

  /// Get window menu
  FXPopup* getMenu() const;

  /// Set window menu
  void setMenu(FXPopup* menu);

  /// Set tracking instead of just outline
  void setTracking(FXbool tracking=TRUE);

  /// Return true if tracking
  FXbool getTracking() const;

  /// Set title font
  void setFont(FXFont *fnt);

  /// Get title font
  FXFont* getFont() const;

  /// Destroy
  virtual ~FXMDIChild();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIChild)
DECLARE_FXID_VIRTUALS(FXMDIChild)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIChild)
DECLARE_FXWINDOW_VIRTUALS(FXMDIChild)
DECLARE_FXMDICHILD_VIRTUALS(FXMDIChild)

