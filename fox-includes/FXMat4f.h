/********************************************************************************
*                                                                               *
*            S i n g l e - P r e c i s i o n   4 x 4   M a t r i x              *
*                                                                               *
*********************************************************************************
* Copyright (C) 1994,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMat4f.h 2344 2006-02-12 21:19:36Z lyle $                            *
********************************************************************************/
#ifndef FXMAT4F_H
#define FXMAT4F_H


namespace FX {


/// Single-precision 4x4 matrix
class FXAPI FXMat4f {
protected:
  FXVec4f m[4];
public:
  /// Constructors
  FXMat4f(){}
  FXMat4f(FXfloat w);
  FXMat4f(FXfloat a00,FXfloat a01,FXfloat a02,FXfloat a03,
          FXfloat a10,FXfloat a11,FXfloat a12,FXfloat a13,
          FXfloat a20,FXfloat a21,FXfloat a22,FXfloat a23,
          FXfloat a30,FXfloat a31,FXfloat a32,FXfloat a33);
  FXMat4f(const FXVec4f& a,const FXVec4f& b,const FXVec4f& c,const FXVec4f& d);
  FXMat4f(const FXMat4f& other);

  /// Assignment
  FXMat4f& operator=(const FXMat4f& other);
  FXMat4f& operator=(FXfloat w);

  /// Set value from another matrix
  FXMat4f& set(const FXMat4f& other);

  /// Set value from scalar
  FXMat4f& set(FXfloat w);

  /// Set value from components
  FXMat4f& set(FXfloat a00,FXfloat a01,FXfloat a02,FXfloat a03,
               FXfloat a10,FXfloat a11,FXfloat a12,FXfloat a13,
               FXfloat a20,FXfloat a21,FXfloat a22,FXfloat a23,
               FXfloat a30,FXfloat a31,FXfloat a32,FXfloat a33);

  /// Set value from four vectors
  FXMat4f& set(const FXVec4f& a,const FXVec4f& b,const FXVec4f& c,const FXVec4f& d);

  /// Assignment operators
  FXMat4f& operator+=(const FXMat4f& w);
  FXMat4f& operator-=(const FXMat4f& w);
  FXMat4f& operator*=(FXfloat w);
  FXMat4f& operator*=(const FXMat4f& w);
  FXMat4f& operator/=(FXfloat w);

  /// Indexing
  FXVec4f& operator[](FXint i){return m[i];}
  const FXVec4f& operator[](FXint i) const {return m[i];}

  /// Conversion
  operator FXfloat*(){return m[0];}
  operator const FXfloat*() const {return m[0];}

  /// Unary minus
  FXMat4f operator-() const;

  /// Matrix and matrix
  FXMat4f operator+(const FXMat4f& w) const;
  FXMat4f operator-(const FXMat4f& w) const;
  FXMat4f operator*(const FXMat4f& w) const;

  /// Other operators
  friend FXAPI FXMat4f operator*(FXfloat x,const FXMat4f& a);
  friend FXAPI FXMat4f operator*(const FXMat4f& a,FXfloat x);
  friend FXAPI FXMat4f operator/(const FXMat4f& a,FXfloat x);
  friend FXAPI FXMat4f operator/(FXfloat x,const FXMat4f& a);

  /// Multiply matrix and vector
  FXVec4f operator*(const FXVec4f& v) const;
  FXVec3f operator*(const FXVec3f& v) const;

  /// Set identity matrix
  FXMat4f& eye();

  /// Orthographic projection
  FXMat4f& ortho(FXfloat left,FXfloat right,FXfloat bottom,FXfloat top,FXfloat hither,FXfloat yon);

  /// Perspective projection
  FXMat4f& frustum(FXfloat left,FXfloat right,FXfloat bottom,FXfloat top,FXfloat hither,FXfloat yon);

  /// Multiply by left-hand matrix
  FXMat4f& left();

  /// Multiply by rotation about unit-quaternion
  FXMat4f& rot(const FXQuatf& q);

  /// Multiply by rotation c,s about axis
  FXMat4f& rot(const FXVec3f& v,FXfloat c,FXfloat s);

  /// Multiply by rotation of phi about axis
  FXMat4f& rot(const FXVec3f& v,FXfloat phi);

  /// Multiply by x-rotation
  FXMat4f& xrot(FXfloat c,FXfloat s);
  FXMat4f& xrot(FXfloat phi);

  /// Multiply by y-rotation
  FXMat4f& yrot(FXfloat c,FXfloat s);
  FXMat4f& yrot(FXfloat phi);

  /// Multiply by z-rotation
  FXMat4f& zrot(FXfloat c,FXfloat s);
  FXMat4f& zrot(FXfloat phi);

  /// Look at
  FXMat4f& look(const FXVec3f& eye,const FXVec3f& cntr,const FXVec3f& vup);

  /// Multiply by translation
  FXMat4f& trans(FXfloat tx,FXfloat ty,FXfloat tz);
  FXMat4f& trans(const FXVec3f& v);

  /// Multiply by scaling
  FXMat4f& scale(FXfloat sx,FXfloat sy,FXfloat sz);
  FXMat4f& scale(FXfloat s);
  FXMat4f& scale(const FXVec3f& v);

  /// Determinant
  FXfloat det() const;

  /// Transpose
  FXMat4f transpose() const;

  /// Invert
  FXMat4f invert() const;

  /// Save to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXMat4f& m);

  /// Load from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXMat4f& m);
  };

extern FXAPI FXMat4f operator*(FXfloat x,const FXMat4f& a);
extern FXAPI FXMat4f operator*(const FXMat4f& a,FXfloat x);
extern FXAPI FXMat4f operator/(const FXMat4f& a,FXfloat x);
extern FXAPI FXMat4f operator/(FXfloat x,const FXMat4f& a);

extern FXAPI FXStream& operator<<(FXStream& store,const FXMat4f& m);
extern FXAPI FXStream& operator>>(FXStream& store,FXMat4f& m);

}

#endif
