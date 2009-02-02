/********************************************************************************
*                                                                               *
*            D o u b l e - P r e c i s i o n   4 x 4   M a t r i x              *
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
* $Id: FXMat4d.h 2344 2006-02-12 21:19:36Z lyle $                            *
********************************************************************************/
#ifndef FXMAT4D_H
#define FXMAT4D_H


namespace FX {


/// Double-precision 4x4 matrix
class FXAPI FXMat4d {
protected:
  FXVec4d m[4];
public:
  /// Constructors
  FXMat4d(){}
  FXMat4d(FXdouble w);
  FXMat4d(FXdouble a00,FXdouble a01,FXdouble a02,FXdouble a03,
          FXdouble a10,FXdouble a11,FXdouble a12,FXdouble a13,
          FXdouble a20,FXdouble a21,FXdouble a22,FXdouble a23,
          FXdouble a30,FXdouble a31,FXdouble a32,FXdouble a33);
  FXMat4d(const FXVec4d& a,const FXVec4d& b,const FXVec4d& c,const FXVec4d& d);
  FXMat4d(const FXMat4d& other);

  /// Assignment
  FXMat4d& operator=(const FXMat4d& other);
  FXMat4d& operator=(FXdouble w);

  /// Set value from another matrix
  FXMat4d& set(const FXMat4d& other);

  /// Set value from scalar
  FXMat4d& set(FXdouble w);

  /// Set value from components
  FXMat4d& set(FXdouble a00,FXdouble a01,FXdouble a02,FXdouble a03,
               FXdouble a10,FXdouble a11,FXdouble a12,FXdouble a13,
               FXdouble a20,FXdouble a21,FXdouble a22,FXdouble a23,
               FXdouble a30,FXdouble a31,FXdouble a32,FXdouble a33);

  /// Set value from four vectors
  FXMat4d& set(const FXVec4d& a,const FXVec4d& b,const FXVec4d& c,const FXVec4d& d);

  /// Assignment operators
  FXMat4d& operator+=(const FXMat4d& w);
  FXMat4d& operator-=(const FXMat4d& w);
  FXMat4d& operator*=(FXdouble w);
  FXMat4d& operator*=(const FXMat4d& w);
  FXMat4d& operator/=(FXdouble w);

  /// Indexing
  FXVec4d& operator[](FXint i){return m[i];}
  const FXVec4d& operator[](FXint i) const {return m[i];}

  /// Conversion
  operator FXdouble*(){return m[0];}
  operator const FXdouble*() const {return m[0];}

  /// Unary minus
  FXMat4d operator-() const;

  /// Matrix and matrix
  FXMat4d operator+(const FXMat4d& w) const;
  FXMat4d operator-(const FXMat4d& w) const;
  FXMat4d operator*(const FXMat4d& w) const;

  /// Matrix and scalar
  friend FXAPI FXMat4d operator*(FXdouble x,const FXMat4d& a);
  friend FXAPI FXMat4d operator*(const FXMat4d& a,FXdouble x);
  friend FXAPI FXMat4d operator/(const FXMat4d& a,FXdouble x);
  friend FXAPI FXMat4d operator/(FXdouble x,const FXMat4d& a);

  /// Multiply matrix and vector
  FXVec4d operator*(const FXVec4d& v) const;
  FXVec3d operator*(const FXVec3d& v) const;

  /// Set identity matrix
  FXMat4d& eye();

  /// Orthographic projection
  FXMat4d& ortho(FXdouble left,FXdouble right,FXdouble bottom,FXdouble top,FXdouble hither,FXdouble yon);

  /// Perspective projection
  FXMat4d& frustum(FXdouble left,FXdouble right,FXdouble bottom,FXdouble top,FXdouble hither,FXdouble yon);

  /// Multiply by left-hand matrix
  FXMat4d& left();

  /// Multiply by rotation about unit-quaternion
  FXMat4d& rot(const FXQuatd& q);

  /// Multiply by rotation c,s about axis
  FXMat4d& rot(const FXVec3d& v,FXdouble c,FXdouble s);

  /// Multiply by rotation of phi about axis
  FXMat4d& rot(const FXVec3d& v,FXdouble phi);

  /// Multiply by x-rotation
  FXMat4d& xrot(FXdouble c,FXdouble s);
  FXMat4d& xrot(FXdouble phi);

  /// Multiply by y-rotation
  FXMat4d& yrot(FXdouble c,FXdouble s);
  FXMat4d& yrot(FXdouble phi);

  /// Multiply by z-rotation
  FXMat4d& zrot(FXdouble c,FXdouble s);
  FXMat4d& zrot(FXdouble phi);

  /// Look at
  FXMat4d& look(const FXVec3d& eye,const FXVec3d& cntr,const FXVec3d& vup);

  /// Multiply by translation
  FXMat4d& trans(FXdouble tx,FXdouble ty,FXdouble tz);
  FXMat4d& trans(const FXVec3d& v);

  /// Multiply by scaling
  FXMat4d& scale(FXdouble sx,FXdouble sy,FXdouble sz);
  FXMat4d& scale(FXdouble s);
  FXMat4d& scale(const FXVec3d& v);

  /// Determinant
  FXdouble det() const;

  /// Transpose
  FXMat4d transpose() const;

  /// Invert
  FXMat4d invert() const;

  /// Save to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXMat4d& m);

  /// Load from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXMat4d& m);
  };

extern FXAPI FXMat4d operator*(FXdouble x,const FXMat4d& a);
extern FXAPI FXMat4d operator*(const FXMat4d& a,FXdouble x);
extern FXAPI FXMat4d operator/(const FXMat4d& a,FXdouble x);
extern FXAPI FXMat4d operator/(FXdouble x,const FXMat4d& a);

extern FXAPI FXStream& operator<<(FXStream& store,const FXMat4d& m);
extern FXAPI FXStream& operator>>(FXStream& store,FXMat4d& m);

}

#endif
