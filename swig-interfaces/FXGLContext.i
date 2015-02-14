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
class FXGLVisual;


/**
* A GL context is an object representing the OpenGL state information.
* Multiple GL context may share display lists to conserve memory.
* When drawing multiple windows, it may be advantageous to share not only
* display lists, but also GL contexts.  Since the GL context is created
* for a certain frame-buffer configuration, sharing of GL contexts is
* only possible if the windows sharing the GL context all have the same
* GL visual.
* However, display lists may be shared between different GL contexts.
*/
class FXGLContext : public FXId {
public:
  %extend {
    /**
    * Construct an OpenGL context with its own private display list.
    */
    FXGLContext(FXApp* a,FXGLVisual *vis){
      return new FXRbGLContext(a,vis);
      }

    /**
    * Construct an OpenGL context sharing display lists with an existing GL context.
    */
    FXGLContext(FXApp* a,FXGLVisual *vis,FXGLContext *shared){
      return new FXRbGLContext(a,vis,shared);
      }
    }

  /// Return TRUE if it is sharing display lists
  FXbool isShared() const;

  /// Get the visual
  FXGLVisual* getVisual() const;

  /// Make OpenGL context current prior to performing OpenGL commands
  FXbool begin(FXDrawable *drawable);

  /// Make OpenGL context non current
  FXbool end();

  /// Swap front and back buffer
  void swapBuffers();

  /// Copy part of backbuffer to front buffer [Mesa]
  void swapSubBuffers(FXint x,FXint y,FXint w,FXint h);

  /// Destructor
  virtual ~FXGLContext();
  };


DECLARE_FXOBJECT_VIRTUALS(FXGLContext)
DECLARE_FXID_VIRTUALS(FXGLContext)

