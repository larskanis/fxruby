/********************************************************************************
*                                                                               *
*                G L  C a n v a s   W i n d o w   W i d g e t                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2008 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLCanvas.h 2868 2008-05-30 17:03:51Z lyle $                        *
********************************************************************************/
#ifndef FXGLCANVAS_H
#define FXGLCANVAS_H

#ifndef FXCANVAS_H
#include "FXCanvas.h"
#endif

namespace FX {


class FXGLVisual;
class FXGLContext;


// GL Canvas options
enum {
  GLCANVAS_OWN_CONTEXT = 0x00008000  /// Context is owned
  };


/// GLCanvas, an area drawn by another object
class FXAPI FXGLCanvas : public FXCanvas {
  FXDECLARE(FXGLCanvas)
protected:
  FXGLContext *context; // Graphic context
protected:
  FXGLCanvas();
private:
  FXGLCanvas(const FXGLCanvas&);
  FXGLCanvas &operator=(const FXGLCanvas&);
#ifdef WIN32
  virtual const void* GetClass() const;
#endif
public:

  /**
  * Construct a GL canvas with its private context and private display lists.
  */
  FXGLCanvas(FXComposite* p,FXGLVisual *vis,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /**
  * Construct a GL canvas with its private context but shared display lists.
  */
  FXGLCanvas(FXComposite* p,FXGLVisual *vis,FXGLCanvas* share,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /**
  * Construct a GL canvas with a shared context.
  */
  FXGLCanvas(FXComposite* p,FXGLContext* ctx,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Change context
  void setContext(FXGLContext *ctx,FXbool owned=false);

  /// Get context
  FXGLContext* getContext() const { return context; }

  /// Create all of the server-side resources for this window
  virtual void create();

  /// Detach the server-side resources for this window
  virtual void detach();

  /// Destroy the server-side resources for this window
  virtual void destroy();

  /// Make OpenGL context current prior to performing OpenGL commands
  virtual FXbool makeCurrent();

  /// Make OpenGL context non current
  virtual FXbool makeNonCurrent();

  /// Return true if this window's context is current
  virtual FXbool isCurrent() const;

  /// Swap front and back buffer
  virtual void swapBuffers();

  /// Return true if it is sharing display lists
  FXbool isShared() const;

  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXGLCanvas();
  };

}

#endif

