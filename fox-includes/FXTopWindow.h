/********************************************************************************
*                                                                               *
*                 T o p - L e v e l   W i n d o w   W i d g e t                 *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXTopWindow.h 2246 2005-11-10 02:01:15Z lyle $                       *
********************************************************************************/
#ifndef FXTOPWINDOW_H
#define FXTOPWINDOW_H

#ifndef FXSHELL_H
#include "FXShell.h"
#endif


namespace FX {


/// Title and border decorations
enum {
  DECOR_NONE        = 0,                                  /// Borderless window
  DECOR_TITLE       = 0x00020000,                         /// Window title
  DECOR_MINIMIZE    = 0x00040000,                         /// Minimize button
  DECOR_MAXIMIZE    = 0x00080000,                         /// Maximize button
  DECOR_CLOSE       = 0x00100000,                         /// Close button
  DECOR_BORDER      = 0x00200000,                         /// Border
  DECOR_SHRINKABLE  = 0x00400000,                         /// Window can become smaller
  DECOR_STRETCHABLE = 0x00800000,                         /// Window can become larger
  DECOR_RESIZE      = DECOR_SHRINKABLE|DECOR_STRETCHABLE, /// Resize handles
  DECOR_MENU        = 0x01000000,                         /// Window menu
  DECOR_ALL         = (DECOR_TITLE|DECOR_MINIMIZE|DECOR_MAXIMIZE|DECOR_CLOSE|DECOR_BORDER|DECOR_SHRINKABLE|DECOR_STRETCHABLE|DECOR_MENU)
  };


/// Initial window placement
enum {
  PLACEMENT_DEFAULT,                  /// Place it at the default size and location
  PLACEMENT_VISIBLE,                  /// Place window to be fully visible
  PLACEMENT_CURSOR,                   /// Place it under the cursor position
  PLACEMENT_OWNER,                    /// Place it centered on its owner
  PLACEMENT_SCREEN,                   /// Place it centered on the screen
  PLACEMENT_MAXIMIZED                 /// Place it maximized to the screen size
  };


class FXToolBar;
class FXIcon;



/**
* Abstract base class for all top-level windows.
* TopWindows are usually managed by a Window Manager under X11 and
* therefore borders and window-menus and other decorations like resize-
* handles are subject to the Window Manager's interpretation of the
* decoration hints.
* When a TopWindow is closed, it sends a SEL_CLOSE message to its
* target.  The target should return 0 in response to this message if
* there is no objection to proceed with the closing of the window, and
* return 1 otherwise.  After the SEL_CLOSE message has been sent and
* no objection was raised, the window will delete itself.
* When the session is closed, the window will send a SEL_SESSION_NOTIFY
* message to its target, allowing the application to write any unsaved
* data to the disk.  If the target returns 0, then the system will proceed
* to close the session.  Subsequently a SEL_SESSION_CLOSED will be received
* which causes the window to be closed with prejudice by calling the
* function close(FALSE).
* When receiving a SEL_UPDATE, the target can update the title string
* of the window, so that the title of the window reflects the name
* of the document, for example.
* For convenience, TopWindow provides the same layout behavior as
* the Packer widget, as well as docking and undocking of toolbars.
* TopWindows can be owned by other windows, or be free-floating.
* Owned TopWindows will usually remain stacked on top of the owner
* windows. The lifetime of an owned window should not exceed that of
* the owner.
*/
class FXAPI FXTopWindow : public FXShell {
  FXDECLARE_ABSTRACT(FXTopWindow)
protected:
  FXString  title;                    // Window title
  FXIcon   *icon;                     // Window icon (big)
  FXIcon   *miniIcon;                 // Window icon (small)
  FXint     padtop;                   // Top margin
  FXint     padbottom;                // Bottom margin
  FXint     padleft;                  // Left margin
  FXint     padright;                 // Right margin
  FXint     hspacing;                 // Horizontal child spacing
  FXint     vspacing;                 // Vertical child spacing
protected:
  FXTopWindow();
  void settitle();
  void seticons();
  void setdecorations();
  FXTopWindow(FXApp* ap,const FXString& name,FXIcon *ic,FXIcon *mi,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb,FXint hs,FXint vs);
  FXTopWindow(FXWindow* ow,const FXString& name,FXIcon *ic,FXIcon *mi,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb,FXint hs,FXint vs);
private:
  FXTopWindow(const FXTopWindow&);
  FXTopWindow& operator=(const FXTopWindow&);
#ifdef WIN32
  virtual const char* GetClass() const;
#endif
public:
  long onFocusUp(FXObject*,FXSelector,void*);
  long onFocusDown(FXObject*,FXSelector,void*);
  long onFocusLeft(FXObject*,FXSelector,void*);
  long onFocusRight(FXObject*,FXSelector,void*);
  long onSessionNotify(FXObject*,FXSelector,void*);
  long onSessionClosed(FXObject*,FXSelector,void*);
  long onCmdMaximize(FXObject*,FXSelector,void*);
  long onCmdMinimize(FXObject*,FXSelector,void*);
  long onCmdRestore(FXObject*,FXSelector,void*);
  long onCmdClose(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
  long onCmdSetIconValue(FXObject*,FXSelector,void*);
  long onCmdGetIconValue(FXObject*,FXSelector,void*);
public:
  enum {
    ID_MAXIMIZE=FXShell::ID_LAST,       /// Maximize the window
    ID_MINIMIZE,                        /// Minimize the window
    ID_RESTORE,                         /// Restore the window
    ID_CLOSE,                           /// Close the window
    ID_QUERY_DOCK,                      /// Toolbar asks to dock
    ID_LAST
    };
public:

  /// Create server-side resources
  virtual void create();

  /// Detach the server-side resources for this window
  virtual void detach();

  /// Destroy the server-side resources for this window
  virtual void destroy();

  /// Perform layout
  virtual void layout();

  /// Move the focus to this window
  virtual void setFocus();

  /// Remove the focus from this window
  virtual void killFocus();

  /// Show this window
  virtual void show();

  /// Hide this window
  virtual void hide();

  /// Show this window with given placement
  virtual void show(FXuint placement);

  /// Position the window based on placement
  void place(FXuint placement);

  /// Return the default width of this window
  virtual FXint getDefaultWidth();

  /// Return the default height of this window
  virtual FXint getDefaultHeight();

  /// Obtain border sizes added to our window by the window manager
  FXbool getWMBorders(FXint& left,FXint& right,FXint& top,FXint& bottom);

  /// Raise this window to the top of the stacking order
  virtual void raise();

  /// Move this window to the specified position in the parent's coordinates
  virtual void move(FXint x,FXint y);

  /// Resize this window to the specified width and height
  virtual void resize(FXint w,FXint h);

  /// Move and resize this window in the parent's coordinates
  virtual void position(FXint x,FXint y,FXint w,FXint h);

  /// Maximize window, return TRUE if maximized
  virtual FXbool maximize(FXbool notify=FALSE);

  /// Minimize or iconify window, return TRUE if minimized
  virtual FXbool minimize(FXbool notify=FALSE);

  /// Restore window to normal, return TRUE if restored
  virtual FXbool restore(FXbool notify=FALSE);

  /**
  * Close the window, return TRUE if actually closed.  If notify=TRUE, the target
  * will receive a SEL_CLOSE message to determine if it is OK to close the window.
  * If the target ignores the SEL_CLOSE message or returns 0, the window will
  * be closed, and subsequently deleted.  When the last main window has been
  * closed, the application will receive an ID_QUIT message and will be closed.
  */
  virtual FXbool close(FXbool notify=FALSE);

  /// Return TRUE if maximized
  FXbool isMaximized() const;

  /// Return TRUE if minimized
  FXbool isMinimized() const;

  /// Change window title
  void setTitle(const FXString& name);

  /// Return window title
  FXString getTitle() const { return title; }

  /// Change top padding
  void setPadTop(FXint pt);

  /// Get top interior padding
  FXint getPadTop() const { return padtop; }

  /// Change bottom padding
  void setPadBottom(FXint pb);

  /// Get bottom interior padding
  FXint getPadBottom() const { return padbottom; }

  /// Change left padding
  void setPadLeft(FXint pl);

  /// Get left interior padding
  FXint getPadLeft() const { return padleft; }

  /// Change right padding
  void setPadRight(FXint pr);

  /// Get right interior padding
  FXint getPadRight() const { return padright; }

  /// Return horizontal spacing between children
  FXint getHSpacing() const { return hspacing; }

  /// Return vertical spacing between children
  FXint getVSpacing() const { return vspacing; }

  /// Change horizontal spacing between children
  void setHSpacing(FXint hs);

  /// Change vertical spacing between children
  void setVSpacing(FXint vs);

  /// Change packing hints for children
  void setPackingHints(FXuint ph);

  /// Return packing hints for children
  FXuint getPackingHints() const;

  /// Change title and border decorations
  void setDecorations(FXuint decorations);

  /// Return current title and border decorations
  FXuint getDecorations() const;

  /// Return window icon
  FXIcon* getIcon() const { return icon; }

  /// Change window icon
  void setIcon(FXIcon* ic);

  /// Return window mini (title) icon
  FXIcon* getMiniIcon() const { return miniIcon; }

  /// Change window mini (title) icon
  void setMiniIcon(FXIcon *ic);

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXTopWindow();
  };

}

#endif
