/********************************************************************************
*                                                                               *
*                   O p e n G L   S p h e r e   O b j e c t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLSphere.h 809 2002-07-11 17:28:15Z lyle $                        *
********************************************************************************/
#ifndef FXGLSPHERE_H
#define FXGLSPHERE_H

#ifndef FXGLSHAPE_H
#include "FXGLShape.h"
#endif

namespace FX {


/// OpenGL Sphere Object
class FXAPI FXGLSphere : public FXGLShape {
  FXDECLARE(FXGLSphere)
public:
  FXfloat radius;   // Radius of sphere
  FXint   slices;   // Longitudinal subdivision
  FXint   stacks;   // Latitudinal subdivision
protected:
  FXGLSphere();
  virtual void drawshape(FXGLViewer* viewer);
public:
  enum {
    ID_LAST=FXGLShape::ID_LAST
    };
public:

  /// Construct with specified origin and radius
  FXGLSphere(FXfloat x,FXfloat y,FXfloat z,FXfloat r=1.0f);

  /// Construct with specified origin, radius and material
  FXGLSphere(FXfloat x,FXfloat y,FXfloat z,FXfloat r,const FXMaterial& mtl);

  /// Copy constructor
  FXGLSphere(const FXGLSphere& orig);

  /// Copy this object
  virtual FXGLObject* copy();

  /// Change radius
  void setRadius(FXfloat r){ radius=r; }
  FXfloat getRadius() const { return radius; }

  /// Change slices
  void setSlices(FXint s){ slices=s; }
  FXint getSlices() const { return slices; }

  /// Change stacks
  void setStacks(FXint s){ stacks=s; }
  FXint getStacks() const { return stacks; }

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXGLSphere();
  };

}

#endif
