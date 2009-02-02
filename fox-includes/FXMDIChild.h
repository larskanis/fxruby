/********************************************************************************
*                                                                               *
*          M u l t i p l e   D o c u m e n t   C h i l d   W i n d o w          *
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
* $Id: FXMDIChild.h 2344 2006-02-12 21:19:36Z lyle $                        *
********************************************************************************/
#ifndef FXMDICHILD_H
#define FXMDICHILD_H

#ifndef FXCOMPOSITE_H
#include "FXComposite.h"
#endif

namespace FX {


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
class FXAPI FXMDIChild : public FXComposite {
  FXDECLARE(FXMDIChild)
protected:
  FXString      title;                  // Window title
  FXMenuButton *windowbtn;              // Window button
  FXButton     *minimizebtn;            // Minimize button
  FXButton     *restorebtn;             // Restore button
  FXButton     *maximizebtn;            // Maximize buton
  FXButton     *deletebtn;              // Close button
  FXFont       *font;                   // Title font
  FXColor       baseColor;              // Colors
  FXColor       hiliteColor;
  FXColor       shadowColor;
  FXColor       borderColor;
  FXColor       titleColor;
  FXColor       titleBackColor;
  FXint         iconPosX;               // Saved icon position
  FXint         iconPosY;
  FXint         iconWidth;
  FXint         iconHeight;
  FXint         normalPosX;             // Saved normal position
  FXint         normalPosY;
  FXint         normalWidth;
  FXint         normalHeight;
  FXint         spotx;                  // Grab-spot of mouse on window
  FXint         spoty;
  FXint         xoff;                   // Mouse offset to add
  FXint         yoff;
  FXint         newx;                   // New location of window
  FXint         newy;
  FXint         neww;
  FXint         newh;
  FXuchar       mode;                   // Dragging mode
protected:
  FXMDIChild();
  void drawRubberBox(FXint x,FXint y,FXint w,FXint h);
  void animateRectangles(FXint ox,FXint oy,FXint ow,FXint oh,FXint nx,FXint ny,FXint nw,FXint nh);
  FXuchar where(FXint x,FXint y);
  void changeCursor(FXint x,FXint y);
  void revertCursor();
protected:
  enum {
    DRAG_NONE        = 0,
    DRAG_TOP         = 1,
    DRAG_BOTTOM      = 2,
    DRAG_LEFT        = 4,
    DRAG_RIGHT       = 8,
    DRAG_TOPLEFT     = (DRAG_TOP|DRAG_LEFT),
    DRAG_TOPRIGHT    = (DRAG_TOP|DRAG_RIGHT),
    DRAG_BOTTOMLEFT  = (DRAG_BOTTOM|DRAG_LEFT),
    DRAG_BOTTOMRIGHT = (DRAG_BOTTOM|DRAG_RIGHT),
    DRAG_INVERTED    = 16,
    DRAG_TITLE       = 32
    };
private:
  FXMDIChild(const FXMDIChild&);
  FXMDIChild &operator=(const FXMDIChild&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onFocusSelf(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onRightBtnPress(FXObject*,FXSelector,void*);
  long onRightBtnRelease(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMiddleBtnPress(FXObject*,FXSelector,void*);
  long onMiddleBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onSelected(FXObject*,FXSelector,void*);
  long onDeselected(FXObject*,FXSelector,void*);
  long onCmdClose(FXObject*,FXSelector,void*);
  long onUpdClose(FXObject*,FXSelector,void*);
  long onCmdRestore(FXObject*,FXSelector,void*);
  long onUpdRestore(FXObject*,FXSelector,void*);
  long onUpdMaximize(FXObject*,FXSelector,void*);
  long onUpdMinimize(FXObject*,FXSelector,void*);
  long onCmdMaximize(FXObject*,FXSelector,void*);
  long onCmdMinimize(FXObject*,FXSelector,void*);
  long onUpdWindow(FXObject*,FXSelector,void*);
  long onUpdMenuRestore(FXObject*,FXSelector,void*);
  long onUpdMenuMinimize(FXObject*,FXSelector,void*);
  long onUpdMenuClose(FXObject*,FXSelector,void*);
  long onUpdMenuWindow(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
  long onCmdSetIconValue(FXObject*,FXSelector,void*);
  long onCmdGetIconValue(FXObject*,FXSelector,void*);
  virtual long onDefault(FXObject*,FXSelector,void*);
public:

  /// Construct MDI Child window with given name and icon
  FXMDIChild(FXMDIClient* p,const FXString& name,FXIcon* ic=NULL,FXPopup* pup=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create window
  virtual void create();

  /// Detach window
  virtual void detach();

  /// Perform layout
  virtual void layout();

  /// Return the default width of this window
  virtual FXint getDefaultWidth();

  /// Return the default height of this window
  virtual FXint getDefaultHeight();

  /// Move the focus to this window
  virtual void setFocus();

  /// MDI Child can receive focus
  virtual bool canFocus() const;

  /// Move this window to the specified position in the parent's coordinates
  virtual void move(FXint x,FXint y);

  /// Resize this window to the specified width and height
  virtual void resize(FXint w,FXint h);

  /// Move and resize this window in the parent's coordinates
  virtual void position(FXint x,FXint y,FXint w,FXint h);

  /// Change normal (restored) position
  void setNormalX(FXint x){ normalPosX=x; }
  void setNormalY(FXint y){ normalPosY=y; }
  void setNormalWidth(FXint w){ normalWidth=w; }
  void setNormalHeight(FXint h){ normalHeight=h; }

  /// Return normal (restored) position
  FXint getNormalX() const { return normalPosX; }
  FXint getNormalY() const { return normalPosY; }
  FXint getNormalWidth() const { return normalWidth; }
  FXint getNormalHeight() const { return normalHeight; }

  /// Change iconified position
  void setIconX(FXint x){ iconPosX=x; }
  void setIconY(FXint y){ iconPosY=y; }
  void setIconWidth(FXint w){ iconWidth=w; }
  void setIconHeight(FXint h){ iconHeight=h; }

  /// Return iconified position
  FXint getIconX() const { return iconPosX; }
  FXint getIconY() const { return iconPosY; }
  FXint getIconWidth() const { return iconWidth; }
  FXint getIconHeight() const { return iconHeight; }

  /// Return content window
  FXWindow *contentWindow() const;

  /// Change MDI Child's title
  void setTitle(const FXString& name);

  /// Get current title
  FXString getTitle() const { return title; }

  /// Get colors
  FXColor getHiliteColor() const { return hiliteColor; }
  FXColor getShadowColor() const { return shadowColor; }
  FXColor getBaseColor() const { return baseColor; }
  FXColor getBorderColor() const { return borderColor; }
  FXColor getTitleColor () const { return titleColor; }
  FXColor getTitleBackColor() const { return titleBackColor; }

  /// Change colors
  void setHiliteColor(FXColor clr);
  void setShadowColor(FXColor clr);
  void setBaseColor(FXColor clr);
  void setBorderColor(FXColor clr);
  void setTitleColor(FXColor clr);
  void setTitleBackColor(FXColor clr);

  /// Maximize MDI window, return TRUE if maximized
  virtual FXbool maximize(FXbool notify=FALSE);

  /// Minimize/iconify MDI window, return TRUE if minimized
  virtual FXbool minimize(FXbool notify=FALSE);

  /// Restore MDI window to normal, return TRUE if restored
  virtual FXbool restore(FXbool notify=FALSE);

  /// Close MDI window, return TRUE if actually closed
  virtual FXbool close(FXbool notify=FALSE);

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
  FXFont* getFont() const { return font; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXMDIChild();
  };

}

#endif
