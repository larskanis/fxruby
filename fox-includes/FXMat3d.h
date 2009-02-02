/********************************************************************************
*                                                                               *
*            D o u b l e - P r e c i s i o n   3 x 3   M a t r i x              *
*                                                                               *
*********************************************************************************
* Copyright (C) 2003,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMat3d.h 2344 2006-02-12 21:19:36Z lyle $                           *
********************************************************************************/
#ifndef FXMAT3D_H
#define FXMAT3D_H


namespace FX {


class FXQuatd;


/// Double-precision 3x3 matrix
class FXAPI FXMat3d {
protected:
  FXVec3d m[3];
public:

  /// Default constructor
  FXMat3d(){}

  /// Initialize matrix from another matrix
  FXMat3d(const FXMat3d& other);

  /// Initialize matrix from scalar
  FXMat3d(FXdouble w);

  /// Initialize matrix from components
  FXMat3d(FXdouble a00,FXdouble a01,FXdouble a02,
          FXdouble a10,FXdouble a11,FXdouble a12,
          FXdouble a20,FXdouble a21,FXdouble a22);

  /// Initialize matrix from three vectors
  FXMat3d(const FXVec3d& a,const FXVec3d& b,const FXVec3d& c);

  /// Initialize matrix from quaternion
  FXMat3d(const FXQuatd& quat);

  /// Assignment
  FXMat3d& operator=(const FXMat3d& other);
  FXMat3d& operator=(FXdouble w);

  /// Set value from another matrix
  FXMat3d& set(const FXMat3d& other);

  /// Set value from scalar
  FXMat3d& set(FXdouble w);

  /// Set value from components
  FXMat3d& set(FXdouble a00,FXdouble a01,FXdouble a02,
               FXdouble a10,FXdouble a11,FXdouble a12,
               FXdouble a20,FXdouble a21,FXdouble a22);

  /// Set value from three vectors
  FXMat3d& set(const FXVec3d& a,const FXVec3d& b,const FXVec3d& c);

  /// Set value from quaternion
  FXMat3d& set(const FXQuatd& quat);

  /// Assignment operators
  FXMat3d& operator+=(const FXMat3d& w);
  FXMat3d& operator-=(const FXMat3d& w);
  FXMat3d& operator*=(FXdouble w);
  FXMat3d& operator*=(const FXMat3d& w);
  FXMat3d& operator/=(FXdouble w);

  /// Indexing
  FXVec3d& operator[](FXint i){return m[i];}
  const FXVec3d& operator[](FXint i) const {return m[i];}

  /// Conversion
  operator FXdouble*(){return m[0];}
  operator const FXdouble*() const {return m[0];}

  /// Unary minus
  FXMat3d operator-() const;

  /// Matrix and matrix
  FXMat3d operator+(const FXMat3d& w) const;
  FXMat3d operator-(const FXMat3d& w) const;
  FXMat3d operator*(const FXMat3d& w) const;

  /// Multiply matrix and vector
  FXVec3d operator*(const FXVec3d& v) const;
  FXVec2d operator*(const FXVec2d& v) const;

  /// Matrix and scalar
  friend FXAPI FXMat3d operator*(FXdouble x,const FXMat3d& a);
  friend FXAPI FXMat3d operator*(const FXMat3d& a,FXdouble x);
  friend FXAPI FXMat3d operator/(const FXMat3d& a,FXdouble x);
  friend FXAPI FXMat3d operator/(FXdouble x,const FXMat3d& a);

  /// Set identity matrix
  FXMat3d& eye();

  /// Multiply by rotation of phi
  FXMat3d& rot(FXdouble c,FXdouble s);
  FXMat3d& rot(FXdouble phi);

  /// Multiply by translation
  FXMat3d& trans(FXdouble tx,FXdouble ty);

  /// Multiply by scaling
  FXMat3d& scale(FXdouble sx,FXdouble sy);
  FXMat3d& scale(FXdouble s);

  /// Determinant
  FXdouble det() const;

  /// Transpose
  FXMat3d transpose() const;

  /// Invert
  FXMat3d invert() const;

  /// Save to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXMat3d& m);

  /// Load from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXMat3d& m);
  };

extern FXAPI FXMat3d operator*(FXdouble x,const FXMat3d& a);
extern FXAPI FXMat3d operator*(const FXMat3d& a,FXdouble x);
extern FXAPI FXMat3d operator/(const FXMat3d& a,FXdouble x);
extern FXAPI FXMat3d operator/(FXdouble x,const FXMat3d& a);

extern FXAPI FXStream& operator<<(FXStream& store,const FXMat3d& m);
extern FXAPI FXStream& operator>>(FXStream& store,FXMat3d& m);

}

#endif
