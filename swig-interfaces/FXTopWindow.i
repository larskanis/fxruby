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
class FXTopWindow : public FXShell {
public:
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
  long onSessionNotify(FXObject*,FXSelector,void* PTR_EVENT);
  long onSessionClosed(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdMaximize(FXObject*,FXSelector,void*); // FIXME
  long onCmdMinimize(FXObject*,FXSelector,void*); // FIXME
  long onCmdRestore(FXObject*,FXSelector,void*); // FIXME
  long onCmdClose(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetStringValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetIconValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetIconValue(FXObject*,FXSelector,void*); // FIXME
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
  %extend {
    // Construct free-floating top-level window
    FXTopWindow(FXApp* a,const FXString& name,FXIcon *ic,FXIcon *mi,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb,FXint hs,FXint vs){
      return new FXRbTopWindow(a,name,ic,mi,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }

    // Construct owned top-level window
    FXTopWindow(FXWindow* owner,const FXString& name,FXIcon *ic,FXIcon *mi,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb,FXint hs,FXint vs){
      return new FXRbTopWindow(owner,name,ic,mi,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }


  %extend {
    /// Obtain border sizes added to our window by the window manager
    VALUE getWMBorders(){
      FXint left,right,top,bottom;
      if(self->getWMBorders(left,right,top,bottom)){
        return rb_ary_new3(4,INT2NUM(left),INT2NUM(right),INT2NUM(top),INT2NUM(bottom));
        }
      else{
        return Qnil; // FIXME
	}
      }
  }

  /// Position the window based on placement
  void place(FXuint placement);

  /// Return TRUE if maximized
  FXbool isMaximized() const;

  /// Return TRUE if minimized
  FXbool isMinimized() const;

  /// Change window title
  void setTitle(const FXString& name);

  /// Return window title
  FXString getTitle() const;

  /// Change top padding
  void setPadTop(FXint pt);

  /// Get top interior padding
  FXint getPadTop() const;

  /// Change bottom padding
  void setPadBottom(FXint pb);

  /// Get bottom interior padding
  FXint getPadBottom() const;

  /// Change left padding
  void setPadLeft(FXint pl);

  /// Get left interior padding
  FXint getPadLeft() const;

  /// Change right padding
  void setPadRight(FXint pr);

  /// Get right interior padding
  FXint getPadRight() const;

  /// Return horizontal spacing between children
  FXint getHSpacing() const;

  /// Return vertical spacing between children
  FXint getVSpacing() const;

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
  FXIcon* getIcon() const;

  /// Change window icon
  void setIcon(FXIcon* ic);

  /// Return window mini (title) icon
  FXIcon* getMiniIcon() const;

  /// Change window mini (title) icon
  void setMiniIcon(FXIcon *ic);

  /// Destructor
  virtual ~FXTopWindow();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTopWindow)
DECLARE_FXID_VIRTUALS(FXTopWindow)
DECLARE_FXDRAWABLE_VIRTUALS(FXTopWindow)
DECLARE_FXWINDOW_VIRTUALS(FXTopWindow)
DECLARE_FXTOPWINDOW_VIRTUALS(FXTopWindow)

%{
static swig_type_info *FXTopWindow_dynamic_cast(void **ptr) {
    FXTopWindow **ppTopWindow = reinterpret_cast<FXTopWindow **>(ptr);
    FXDialogBox *pDialogBox=dynamic_cast<FXDialogBox*>(*ppTopWindow);
    if(pDialogBox){
      *ptr=reinterpret_cast<void*>(pDialogBox);
      return SWIG_TypeQuery("FXDialogBox *");
      }
    FXMainWindow *pMainWindow=dynamic_cast<FXMainWindow*>(*ppTopWindow);
    if(pMainWindow){
      *ptr=reinterpret_cast<void*>(pMainWindow);
      return SWIG_TypeQuery("FXMainWindow *");
      }
    FXSplashWindow *pSplashWindow=dynamic_cast<FXSplashWindow*>(*ppTopWindow);
    if(pSplashWindow){
      *ptr=reinterpret_cast<void*>(pSplashWindow);
      return SWIG_TypeQuery("FXSplashWindow *");
      }
    FXToolBarShell *pToolBarShell=dynamic_cast<FXToolBarShell*>(*ppTopWindow);
    if(pToolBarShell){
      *ptr=reinterpret_cast<void*>(pToolBarShell);
      return SWIG_TypeQuery("FXToolBarShell *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXTopWindow, FXTopWindow_dynamic_cast);

