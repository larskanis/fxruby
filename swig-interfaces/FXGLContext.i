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

/// OpenGL context
class FXGLContext : public FXId {
public:
  %extend {
    /**
		* Construct an GL Context with given GL Visual.  Optionally
		* share a display list with another GL Context shr.
    */
    FXGLContext(FXApp* a,FXGLVisual* vis,FXGLContext *shr=NULL){
      return new FXRbGLContext(a,vis,shr);
      }
    }

  /// Change visual
  void setVisual(FXGLVisual* vis);

  /// Get the visual
  FXGLVisual* getVisual() const;

  /// Change share context
  void setShared(FXGLContext *ctx);

  /// Get share context
  FXGLContext* getShared() const;

  /// Return active drawable
  FXDrawable *drawable() const;

  /// Make OpenGL context current prior to performing OpenGL commands
  FXbool begin(FXDrawable *drawable);
  
  /// Make OpenGL context non current 
  FXbool end();
  
  /// Swap front and back buffer
  void swapBuffers();
  
  /// Return true if this window's context is current
  FXbool isCurrent() const;

  /// Has double buffering
  FXbool isDoubleBuffer() const;

  /// Has stereo buffering
  FXbool isStereo() const;

  /// Destructor
  virtual ~FXGLContext();
  };


DECLARE_FXOBJECT_VIRTUALS(FXGLContext)
DECLARE_FXID_VIRTUALS(FXGLContext)

