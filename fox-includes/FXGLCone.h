/********************************************************************************
*                                                                               *
*                        O p e n G L   C o n e    O b j e c t                   *
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
* $Id: FXGLCone.h 809 2002-07-11 17:28:15Z lyle $                          *
********************************************************************************/
#ifndef FXGLCONE_H
#define FXGLCONE_H

#ifndef FXGLSHAPE_H
#include "FXGLShape.h"
#endif

namespace FX {


/// OpenGL Cone Object
class FXAPI FXGLCone : public FXGLShape {
  FXDECLARE(FXGLCone)
public:
  FXfloat height;
  FXfloat radius;
protected:
  FXGLCone();
  virtual void drawshape(FXGLViewer* viewer);
public:

  /// Construct with specified origin, height and radius
  FXGLCone(FXfloat x,FXfloat y,FXfloat z,FXfloat h=1.0f,FXfloat r=1.0f);

  /// Construct with specified origin, height, radius and material
  FXGLCone(FXfloat x,FXfloat y,FXfloat z,FXfloat h,FXfloat r,const FXMaterial& mtl);

  /// Copy constructor
  FXGLCone(const FXGLCone& orig);

  /// Copy this object
  virtual FXGLObject* copy();

  /// Change radius
  void setRadius(FXfloat r){ radius=r; }
  FXfloat getRadius() const { return radius; }

  /// Change height
  void setHeight(FXfloat h){ height=h; }
  FXfloat getHeight() const { return height; }

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXGLCone();
  };

}

#endif
