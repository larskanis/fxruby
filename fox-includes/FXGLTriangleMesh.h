/********************************************************************************
*                                                                               *
*             O p e n G L   T r i a n g l e   M e s h   O b j e c t             *
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
* $Id: FXGLTriangleMesh.h 809 2002-07-11 17:28:15Z lyle $                  *
********************************************************************************/
#ifndef FXGLTRIANGLEMESH_H
#define FXGLTRIANGLEMESH_H

#ifndef FXGLSHAPE_H
#include "FXGLShape.h"
#endif

namespace FX {


/*
 * Arrays Formats
 *
 * vertex: x,y,z
 * normal: x,y,z
 * Color: r,g.b,a
 * texture: u,v
 */


/// OpenGL Triangle Mesh Object
class FXAPI FXGLTriangleMesh : public FXGLShape {
  FXDECLARE(FXGLTriangleMesh)
private:
  FXfloat   *vertexBuffer;
  FXfloat   *colorBuffer;
  FXfloat   *normalBuffer;
  FXfloat   *textureBuffer;
  FXint      vertexNumber;
protected:
  FXGLTriangleMesh();
  virtual void drawshape(FXGLViewer* viewer);
  virtual void recomputerange();
  virtual void generatenormals();
public:

  /// Construct triangle mesh with nv vertices, and optional normals, colors, and texture coordinates
  FXGLTriangleMesh(FXfloat x,FXfloat y,FXfloat z,FXint nv,FXfloat *v,FXfloat *n=NULL,FXfloat *c=NULL,FXfloat *t=NULL);

  /// Construct triangle mesh with nv vertices, and optional normals, colors, and texture coordinates, and surface material
  FXGLTriangleMesh(FXfloat x,FXfloat y,FXfloat z,FXint nv,FXfloat *v,FXfloat *n,FXfloat *c,FXfloat *t,const FXMaterial& mtl);

  /// Copy constructor
  FXGLTriangleMesh(const FXGLTriangleMesh& orig);

  /// Copy this object
  virtual FXGLObject* copy();

  /// Change number of vertices
  void setVertexNumber(FXint nvertices){ vertexNumber=nvertices; }

  /// Get number of vertices
  FXint getVertexNumber() const { return vertexNumber; }

  /// Set vertex buffer
  void setVertexBuffer(FXfloat *vertices);

  /// Get vertex buffer
  FXfloat* getVertexBuffer() const { return vertexBuffer; }

  /// Set color buffer
  void setColorBuffer(FXfloat *colors){ colorBuffer=colors; }

  /// Get color buffer
  FXfloat* getColorBuffer() const { return colorBuffer; }

  /// Set normals buffer
  void setNormalBuffer(FXfloat *normals){ normalBuffer=normals; }

  /// Get normals buffer
  FXfloat* getNormalBuffer() const { return normalBuffer; }

  /// Set texture coordinate buffer
  void setTextureCoordBuffer(FXfloat *textures){ textureBuffer=textures; }

  /// Get texture coordinate buffer
  FXfloat* getTextureCoordBuffer() const { return textureBuffer; }

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXGLTriangleMesh();
  };

}

#endif
