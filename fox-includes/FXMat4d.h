/********************************************************************************
*                                                                               *
*            D o u b l e - P r e c i s i o n   4 x 4   M a t r i x              *
*                                                                               *
*********************************************************************************
* Copyright (C) 1994,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMat4d.h,v 1.30 2009/01/26 09:40:22 fox Exp $                           *
********************************************************************************/
#ifndef FXMAT4D_H
#define FXMAT4D_H


namespace FX {


class FXQuatd;
class FXMat3d;


/// Double-precision 4x4 matrix
class FXAPI FXMat4d {
protected:
  FXVec4d m[4];
public:

  /// Default constructor; value is not initialized
  FXMat4d(){}

  /// Initialize matrix from another matrix
  FXMat4d(const FXMat4d& other);

  /// Initialize with 3x3 rotation and scaling matrix
  FXMat4d(const FXMat3d& other);

  /// Initialize matrix from scalar
  FXMat4d(FXdouble w);

  /// Initialize diagonal matrix
  FXMat4d(FXdouble a,FXdouble b,FXdouble c,FXdouble d);

  /// Initialize matrix from components
  FXMat4d(FXdouble a00,FXdouble a01,FXdouble a02,FXdouble a03,
          FXdouble a10,FXdouble a11,FXdouble a12,FXdouble a13,
          FXdouble a20,FXdouble a21,FXdouble a22,FXdouble a23,
          FXdouble a30,FXdouble a31,FXdouble a32,FXdouble a33);

  /// Initialize matrix from four vectors
  FXMat4d(const FXVec4d& a,const FXVec4d& b,const FXVec4d& c,const FXVec4d& d);

  /// Assignment
  FXMat4d& operator=(const FXMat4d& other);
  FXMat4d& operator=(const FXMat3d& other);
  FXMat4d& operator=(FXdouble w);

  /// Set value from another matrix
  FXMat4d& set(const FXMat4d& other);

  /// Set value from 3x3 rotation and scaling matrix
  FXMat4d& set(const FXMat3d& other);

  /// Set value from scalar
  FXMat4d& set(FXdouble w);

  /// Set diagonal matrix
  FXMat4d& set(FXdouble a,FXdouble b,FXdouble c,FXdouble d);

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
  FXMat4d& operator*=(const FXMat4d& w);
  FXMat4d& operator*=(FXdouble w);
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

  /// Multiply matrix and vector
  FXVec4d operator*(const FXVec4d& v) const;
  FXVec3d operator*(const FXVec3d& v) const;

  /// Equality tests
  FXbool operator==(const FXMat4d& a) const;
  FXbool operator!=(const FXMat4d& a) const;

  friend FXAPI FXbool operator==(const FXMat4d& a,FXdouble n);
  friend FXAPI FXbool operator==(FXdouble n,const FXMat4d& a);

  friend FXAPI FXbool operator!=(const FXMat4d& a,FXdouble n);
  friend FXAPI FXbool operator!=(FXdouble n,const FXMat4d& a);

  /// Matrix and scalar
  friend FXAPI FXMat4d operator*(FXdouble x,const FXMat4d& a);
  friend FXAPI FXMat4d operator*(const FXMat4d& a,FXdouble x);
  friend FXAPI FXMat4d operator/(const FXMat4d& a,FXdouble x);
  friend FXAPI FXMat4d operator/(FXdouble x,const FXMat4d& a);

  /// Set to identity matrix
  FXMat4d& identity();

  /// Return true if identity matrix
  FXbool isIdentity() const;

  /// Set orthographic projection from view volume
  FXMat4d& setOrtho(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi,FXdouble zlo,FXdouble zhi);

  /// Get view volume from orthographic projection
  void getOrtho(FXdouble& xlo,FXdouble& xhi,FXdouble& ylo,FXdouble& yhi,FXdouble& zlo,FXdouble& zhi) const;

  /// Set to inverse orthographic projection
  FXMat4d& setInverseOrtho(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi,FXdouble zlo,FXdouble zhi);

  /// Set to perspective projection from view volume
  FXMat4d& setFrustum(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi,FXdouble zlo,FXdouble zhi);

  /// Get view volume from perspective projection
  void getFrustum(FXdouble& xlo,FXdouble& xhi,FXdouble& ylo,FXdouble& yhi,FXdouble& zlo,FXdouble& zhi) const;

  /// Set to inverse perspective projection from view volume
  FXMat4d& setInverseFrustum(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi,FXdouble zlo,FXdouble zhi);

  /// Multiply by left-hand matrix
  FXMat4d& left();

  /// Multiply by rotation matrix
  FXMat4d& rot(const FXMat3d& r);

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
  FXMat4d& look(const FXVec3d& from,const FXVec3d& to,const FXVec3d& up);

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

extern FXAPI FXbool operator==(const FXMat4d& a,FXdouble n);
extern FXAPI FXbool operator==(FXdouble n,const FXMat4d& a);

extern FXAPI FXbool operator!=(const FXMat4d& a,FXdouble n);
extern FXAPI FXbool operator!=(FXdouble n,const FXMat4d& a);

extern FXAPI FXStream& operator<<(FXStream& store,const FXMat4d& m);
extern FXAPI FXStream& operator>>(FXStream& store,FXMat4d& m);

}

#endif
