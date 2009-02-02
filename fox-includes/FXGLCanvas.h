/********************************************************************************
*                                                                               *
*                G L  C a n v a s   W i n d o w   W i d g e t                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLCanvas.h 2231 2005-11-09 03:16:46Z lyle $                        *
********************************************************************************/
#ifndef FXGLCANVAS_H
#define FXGLCANVAS_H

#ifndef FXCANVAS_H
#include "FXCanvas.h"
#endif

namespace FX {


class FXGLVisual;


/// GLCanvas, an area drawn by another object
class FXAPI FXGLCanvas : public FXCanvas {
  FXDECLARE(FXGLCanvas)
private:
  FXGLCanvas  *sgnext;  // Share group next in share list
  FXGLCanvas  *sgprev;  // Share group previous in share list
protected:
  void        *ctx;     // GL Context
protected:
  FXGLCanvas();
private:
  FXGLCanvas(const FXGLCanvas&);
  FXGLCanvas &operator=(const FXGLCanvas&);
#ifdef WIN32
  virtual const char* GetClass() const;
#endif
public:

  /**
  * Construct an OpenGL-capable canvas, with its own private display list.
  */
  FXGLCanvas(FXComposite* p,FXGLVisual *vis,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /**
  * Construct an OpenGL-capable canvas, sharing display
  * list with another GL canvas.  This canvas becomes a member
  * of a display list share group.  All members of the display
  * list share group have to have the same visual.
  */
  FXGLCanvas(FXComposite* p,FXGLVisual *vis,FXGLCanvas* sharegroup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Return TRUE if it is sharing display lists
  FXbool isShared() const;

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

  /// Return TRUE if this window's context is current
  virtual FXbool isCurrent() const;

  /// Return current context, if any
  static void* getCurrentContext();

  /// Get GL context handle
  void* getContext() const { return ctx; }

  /// Swap front and back buffer
  virtual void swapBuffers();

  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXGLCanvas();
  };

}

#endif

