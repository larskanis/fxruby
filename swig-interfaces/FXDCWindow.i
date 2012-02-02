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

class FXApp;
class FXDrawable;
class FXImage;
class FXBitmap;
class FXIcon;
class FXFont;
class FXVisual;

%exception FXDCWindow::FXDCWindow {
  $action FXRbRegisterRubyObj(self, result);
  if(rb_block_given_p()){
    rb_ensure(VALUEFUNC(rb_yield), self, VALUEFUNC(FXRbDCWindow::endit), self);
    }
}

/**
 * Window Device Context
 *
 * The Window Device Context allows drawing into an FXDrawable, such as an
 * on-screen window (FXWindow and derivatives) or an off-screen image (FXImage
 * and its derivatives).
 * Because certain hardware resources are locked down, only one FXDCWindow may be
 * locked on a drawable at any one time.
 */
class FXDCWindow : public FXDC {
public:
  %extend {
    /// Construct for painting in response to expose;
    /// This sets the clip rectangle to the exposed rectangle
    FXDCWindow(FXDrawable* drawable,FXEvent* event){
      return new FXRbDCWindow(drawable,event);
      }

    /// Construct for normal drawing;
    /// This sets clip rectangle to the whole drawable
    FXDCWindow(FXDrawable* drawable){
      return new FXRbDCWindow(drawable);
      }
    }

  /// Begin locks in a drawable surface
  void begin(FXDrawable *drawable);

  /// End unlock the drawable surface
  void end();

  /// Destructor
  virtual ~FXDCWindow();
  };


DECLARE_FXDC_VIRTUALS(FXDCWindow)

