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

/***********************************************************************
 * $Id: FXRbDCWindow.h 2372 2006-04-20 00:38:08Z lyle $
 ***********************************************************************/

#ifndef FXRBDCWINDOW_H
#define FXRBDCWINDOW_H

class FXRbDCWindow : public FXDCWindow {
#include "FXRbDCVirtuals.h"
public:
  /// Construct for painting in response to expose;
  /// This sets the clip rectangle to the exposed rectangle
  FXRbDCWindow(FXDrawable* drawable,FXEvent* event) : FXDCWindow(drawable,event){
    FXRbRegisterAppSensitiveObject(this);
    }

  /// Construct for normal drawing;
  /// This sets clip rectangle to the whole drawable
  FXRbDCWindow(FXDrawable* drawable) : FXDCWindow(drawable){
    FXRbRegisterAppSensitiveObject(this);
    }

  // Helper for FXDCWindow initialization block
  static VALUE endit(VALUE obj){
    FXDCWindow* dc=reinterpret_cast<FXDCWindow*>(DATA_PTR(obj));
    FXASSERT(dc!=0);
    dc->end();
    return Qnil;
    }

  // Mark dependencies for the GC
  static void markfunc(FXDCWindow* self);

  // Destructor
  virtual ~FXRbDCWindow(){
    FXTRACE((100,"FXRbDCWindow::~FXRbDCWindow() %p\n",this));
    FXRbUnregisterRubyObj(this);
    FXRbUnregisterAppSensitiveObject(this);
    }
  };

#endif
