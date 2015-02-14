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

/// Splash Window options
enum {
  SPLASH_SIMPLE    = 0,                 /// Simple rectangular splash window
  SPLASH_SHAPED    = 0x02000000,        /// Shaped splash window
  SPLASH_OWNS_ICON = 0x04000000,        /// Splash window will own the icon and destroy it
  SPLASH_DESTROY   = 0x08000000         /// Splash window will destroy itself when timer expires
  };

%rename("delay")  FXSplashWindow::getDelay() const;
%rename("delay=") FXSplashWindow::setDelay(FXuint);
%rename("icon")   FXSplashWindow::getIcon() const;
%rename("icon=")  FXSplashWindow::setIcon(FXIcon*);

/**
* The Splash Window is a window typically shown during startup
* of an application.  It comprises a large icon, which is also
* used as the shape of the window if SPLASH_SHAPED is passed;
* with the SPLASH_SIMPLE option the window will be simply rectangular.
*/
class FXSplashWindow : public FXTopWindow {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:

  %extend {
    /// Construct splash window
    FXSplashWindow(FXApp* a,FXIcon* ic,FXuint opts=SPLASH_SIMPLE,FXuint ms=5000){
      /* Icon will be free`d by Rubys GC. */
      opts &= ~SPLASH_OWNS_ICON;
      return new FXRbSplashWindow(a,ic,opts,ms);
      }

    /// Construct splash window
    FXSplashWindow(FXWindow* own,FXIcon* ic,FXuint opts=SPLASH_SIMPLE,FXuint ms=5000){
      /* Icon will be free`d by Rubys GC. */
      opts &= ~SPLASH_OWNS_ICON;
      return new FXRbSplashWindow(own,ic,opts,ms);
      }
    }

  /// Set the icon for the splash window
  void setIcon(FXIcon* ic);

  /// Get the icon for this splash window
  FXIcon* getIcon() const;

  /// Set or change delay
  void setDelay(FXuint ms);

  /// Return delay
  FXuint getDelay() const;

  /// Destroy splash window
  virtual ~FXSplashWindow();
  };

DECLARE_FXOBJECT_VIRTUALS(FXSplashWindow)
DECLARE_FXID_VIRTUALS(FXSplashWindow)
DECLARE_FXDRAWABLE_VIRTUALS(FXSplashWindow)
DECLARE_FXWINDOW_VIRTUALS(FXSplashWindow)
DECLARE_FXTOPWINDOW_VIRTUALS(FXSplashWindow)

