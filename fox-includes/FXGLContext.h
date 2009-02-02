/********************************************************************************
*                                                                               *
*                        G L  C o n t e x t   C l a s s                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLContext.h 809 2002-07-11 17:28:15Z lyle $                        *
********************************************************************************/
#ifndef FXGLCONTEXT_H
#define FXGLCONTEXT_H

//////////////////////////////  UNDER DEVELOPMENT  //////////////////////////////

namespace FX {

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
class FXAPI FXGLContext : public FXId {
  FXDECLARE(FXGLContext)
private:
  FXGLVisual     *visual;     // Visual for this context
  FXDrawable     *surface;    // Drawable context is locked on
  FXGLContext    *sgnext;     // Share group next in share list
  FXGLContext    *sgprev;     // Share group previous in share list
protected:
  void           *ctx;        // GL Context
protected:
  FXGLContext():visual(NULL),surface(NULL),sgnext(NULL),sgprev(NULL),ctx(NULL){}
private:
  FXGLContext(const FXGLContext&);
  FXGLContext &operator=(const FXGLContext&);
public:

  /**
  * Construct an OpenGL context with its own private display list.
  */
  FXGLContext(FXApp* a,FXGLVisual *vis);

  /**
  * Construct an OpenGL context sharing display lists with an existing GL context.
  */
  FXGLContext(FXApp* a,FXGLVisual *vis,FXGLContext *shared);

  /// Return TRUE if it is sharing display lists
  FXbool isShared() const;

  /// Get the visual
  FXGLVisual* getVisual() const { return visual; }

  /// Create context
  virtual void create();

  /// Detach the server-side resources for this window
  virtual void detach();

  /// Destroy the server-side resources for this window
  virtual void destroy();

  /// Make OpenGL context current prior to performing OpenGL commands
  FXbool begin(FXDrawable *drawable);

  /// Make OpenGL context non current
  FXbool end();

  /// Swap front and back buffer
  void swapBuffers();

  /// Copy part of backbuffer to front buffer [Mesa]
  void swapSubBuffers(FXint x,FXint y,FXint w,FXint h);

  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXGLContext();
  };

}

#endif

