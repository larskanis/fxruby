/********************************************************************************
*                                                                               *
*                        O p e n G L   C u b e    O b j e c t                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLCube.h 809 2002-07-11 17:28:15Z lyle $                          *
********************************************************************************/
#ifndef FXGLCUBE_H
#define FXGLCUBE_H

#ifndef FXGLSHAPE_H
#include "FXGLShape.h"
#endif

namespace FX {


/// OpenGL Cube Object
class FXAPI FXGLCube : public FXGLShape {
  FXDECLARE(FXGLCube)
public:
  FXfloat width;
  FXfloat height;
  FXfloat depth;
protected:
  FXGLCube();
  virtual void drawshape(FXGLViewer* viewer);
public:

  /// Construct with specified origin, width, height and depth
  FXGLCube(FXfloat x,FXfloat y,FXfloat z,FXfloat w=1.0f,FXfloat h=1.0f,FXfloat d=1.0f);

  /// Construct with specified origin, width, height, depth and material
  FXGLCube(FXfloat x,FXfloat y,FXfloat z,FXfloat w,FXfloat h,FXfloat d,const FXMaterial& mtl);

  /// Copy constructor
  FXGLCube(const FXGLCube& orig);

  /// Copy this object
  virtual FXGLObject* copy();

  /// Change width
  void setWidth(FXfloat w){ width=w; }
  FXfloat getWidth() const { return width; }

  /// Change height
  void setHeight(FXfloat h){ height=h; }
  FXfloat getHeight() const { return height; }

  /// Change depth
  void setDepth(FXfloat d){ depth=d; }
  FXfloat getDepth() const { return depth; }

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXGLCube();
  };

}

#endif
