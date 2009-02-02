/********************************************************************************
*                                                                               *
*                            S p l a s h    W i n d o w                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXSplashWindow.h 2765 2007-11-19 18:11:18Z lyle $                    *
********************************************************************************/
#ifndef FXSPLASHWINDOW_H
#define FXSPLASHWINDOW_H

#ifndef FXTOPWINDOW_H
#include "FXTopWindow.h"
#endif

namespace FX {


/// Splash Window options
enum {
  SPLASH_SIMPLE    = 0,                 /// Simple rectangular splash window
  SPLASH_SHAPED    = 0x02000000,        /// Shaped splash window
  SPLASH_OWNS_ICON = 0x04000000,        /// Splash window will own the icon and destroy it
  SPLASH_DESTROY   = 0x08000000         /// Splash window will destroy itself when timer expires
  };


/**
* The Splash Window is a window typically shown during startup
* of an application.  It comprises a large icon, which is also
* used as the shape of the window if SPLASH_SHAPED is passed;
* with the SPLASH_SIMPLE option the window will be simply rectangular.
*/
class FXAPI FXSplashWindow : public FXTopWindow {
  FXDECLARE(FXSplashWindow)
protected:
  FXIcon *icon;         // Really big icon
  FXTime  delay;        // Delay before hiding
protected:
  FXSplashWindow();
private:
  FXSplashWindow(const FXSplashWindow&);
  FXSplashWindow &operator=(const FXSplashWindow&);
public:
  long onPaint(FXObject*,FXSelector,void*);
public:

  /**
  * Construct splash window; the window will be automatically hidden (or deleted
  * if SPLASH_DESTROY is passed) after a given delay, specified in nanoseconds).
  * The splash window is free floating.  Use this constructor when the splash window
  * is to be displayed before the main window appears.
  */
  FXSplashWindow(FXApp* ap,FXIcon* ic,FXuint opts=SPLASH_SIMPLE,FXTime ns=2000000000);

  /**
  * Construct splash window; the window will be automatically hidden (or deleted
  * if SPLASH_DESTROY is passed) after a given delay, specified in nanoseconds).
  * The splash window stays on top of its owner window, which must already have been
  * created previously.
  */
  FXSplashWindow(FXWindow* ow,FXIcon* ic,FXuint opts=SPLASH_SIMPLE,FXTime ns=2000000000);

  /// Create
  virtual void create();

  /// Detach
  virtual void detach();

  /// Show splash window
  virtual void show();

  /// Show splash window with a given placement
  virtual void show(FXuint placement);

  /// Hide splash window
  virtual void hide();

  /// Return the default width of this window
  virtual FXint getDefaultWidth();

  /// Return the default height of this window
  virtual FXint getDefaultHeight();

  /// Set the icon for the splash window
  void setIcon(FXIcon* ic);

  /// Get the icon for this splash window
  FXIcon* getIcon() const { return icon; }

  /// Set or change delay in nanoseconds
  void setDelay(FXTime ns);

  /// Return delay
  FXTime getDelay() const { return delay; }

  /// Save label to a stream
  virtual void save(FXStream& store) const;

  /// Load label from a stream
  virtual void load(FXStream& store);

  /// Destroy splash window
  virtual ~FXSplashWindow();
  };

}

#endif
