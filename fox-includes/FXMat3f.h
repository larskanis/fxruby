/********************************************************************************
*                                                                               *
*            S i n g l e - P r e c i s i o n   3 x 3   M a t r i x              *
*                                                                               *
*********************************************************************************
* Copyright (C) 2003,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMat3f.h,v 1.27 2009/01/26 09:40:22 fox Exp $                           *
********************************************************************************/
#ifndef FXMAT3F_H
#define FXMAT3F_H


namespace FX {


class FXQuatf;
class FXMat4f;


/// Single-precision 3x3 matrix
class FXAPI FXMat3f {
protected:
  FXVec3f m[3];
public:

  /// Default constructor; value is not initialized
  FXMat3f(){}

  /// Initialize matrix from another matrix
  FXMat3f(const FXMat3f& other);

  /// Initialize from rotation and scaling part of 4x4 matrix
  FXMat3f(const FXMat4f& other);

  /// Initialize matrix from scalar
  FXMat3f(FXfloat w);

  /// Initialize diagonal matrix
  FXMat3f(FXfloat a,FXfloat b,FXfloat c);

  /// Initialize matrix from components
  FXMat3f(FXfloat a00,FXfloat a01,FXfloat a02,
          FXfloat a10,FXfloat a11,FXfloat a12,
          FXfloat a20,FXfloat a21,FXfloat a22);

  /// Initialize matrix from three vectors
  FXMat3f(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c);

  /// Initialize matrix from quaternion
  FXMat3f(const FXQuatf& quat);

  /// Assignment
  FXMat3f& operator=(const FXMat3f& other);
  FXMat3f& operator=(const FXMat4f& other);
  FXMat3f& operator=(FXfloat w);

  /// Set value from another matrix
  FXMat3f& set(const FXMat3f& other);

  /// Set from rotation and scaling part of 4x4 matrix
  FXMat3f& set(const FXMat4f& q);

  /// Set value from scalar
  FXMat3f& set(FXfloat w);

  /// Set diagonal matrix
  FXMat3f& set(FXfloat a,FXfloat b,FXfloat c);

  /// Set value from components
  FXMat3f& set(FXfloat a00,FXfloat a01,FXfloat a02,
               FXfloat a10,FXfloat a11,FXfloat a12,
               FXfloat a20,FXfloat a21,FXfloat a22);

  /// Set value from three vectors
  FXMat3f& set(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c);

  /// Set value from quaternion
  FXMat3f& set(const FXQuatf& quat);

  /// Assignment operators
  FXMat3f& operator+=(const FXMat3f& w);
  FXMat3f& operator-=(const FXMat3f& w);
  FXMat3f& operator*=(const FXMat3f& w);
  FXMat3f& operator*=(FXfloat w);
  FXMat3f& operator/=(FXfloat w);

  /// Indexing
  FXVec3f& operator[](FXint i){return m[i];}
  const FXVec3f& operator[](FXint i) const {return m[i];}

  /// Conversion
  operator FXfloat*(){return m[0];}
  operator const FXfloat*() const {return m[0];}

  /// Unary minus
  FXMat3f operator-() const;

  /// Matrix and matrix
  FXMat3f operator+(const FXMat3f& w) const;
  FXMat3f operator-(const FXMat3f& w) const;
  FXMat3f operator*(const FXMat3f& w) const;

  /// Multiply matrix and vector
  FXVec3f operator*(const FXVec3f& v) const;
  FXVec2f operator*(const FXVec2f& v) const;

  /// Equality tests
  FXbool operator==(const FXMat3f& a) const;
  FXbool operator!=(const FXMat3f& a) const;

  friend FXAPI FXbool operator==(const FXMat3f& a,FXfloat n);
  friend FXAPI FXbool operator==(FXfloat n,const FXMat3f& a);

  friend FXAPI FXbool operator!=(const FXMat3f& a,FXfloat n);
  friend FXAPI FXbool operator!=(FXfloat n,const FXMat3f& a);

  /// Matrix and scalar
  friend FXAPI FXMat3f operator*(FXfloat x,const FXMat3f& a);
  friend FXAPI FXMat3f operator*(const FXMat3f& a,FXfloat x);
  friend FXAPI FXMat3f operator/(const FXMat3f& a,FXfloat x);
  friend FXAPI FXMat3f operator/(FXfloat x,const FXMat3f& a);

  /// Set to identity matrix
  FXMat3f& identity();

  /// Return true if identity matrix
  FXbool isIdentity() const;

  /// Multiply by rotation of phi
  FXMat3f& rot(FXfloat c,FXfloat s);
  FXMat3f& rot(FXfloat phi);

  /// Multiply by translation
  FXMat3f& trans(FXfloat tx,FXfloat ty);

  /// Multiply by scaling
  FXMat3f& scale(FXfloat sx,FXfloat sy);
  FXMat3f& scale(FXfloat s);

  /// Determinant
  FXfloat det() const;

  /// Transpose
  FXMat3f transpose() const;

  /// Invert
  FXMat3f invert() const;

  /// Save to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXMat3f& m);

  /// Load from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXMat3f& m);
  };

extern FXAPI FXMat3f operator*(FXfloat x,const FXMat3f& a);
extern FXAPI FXMat3f operator*(const FXMat3f& a,FXfloat x);

extern FXAPI FXMat3f operator/(const FXMat3f& a,FXfloat x);
extern FXAPI FXMat3f operator/(FXfloat x,const FXMat3f& a);

extern FXAPI FXbool operator==(const FXMat3f& a,FXdouble n);
extern FXAPI FXbool operator==(FXdouble n,const FXMat3f& a);

extern FXAPI FXbool operator!=(const FXMat3f& a,FXdouble n);
extern FXAPI FXbool operator!=(FXdouble n,const FXMat3f& a);

extern FXAPI FXStream& operator<<(FXStream& store,const FXMat3f& m);
extern FXAPI FXStream& operator>>(FXStream& store,FXMat3f& m);

}

#endif
