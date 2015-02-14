/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

/// Double-precision 3x3 matrix
class FXMat3d {
public:

  /// Default constructor
  FXMat3d();

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

  %extend {
    /// Indexing
    const FXVec3d& __getitem__(FXint i) const {
      if(i<0 || i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXVec3d& __setitem__(FXint i,const FXVec3d& other){
      if(i<0 || i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=other;
      return (*self)[i];
      }

    /// Other operators
    FXMat3d operator+(const FXMat3d& other) const { return (*self)+other; }
    FXMat3d operator-(const FXMat3d& other) const { return (*self)-other; }
    FXMat3d operator-() const { return -(*self); }
    FXMat3d operator*(const FXMat3d& other) const { return (*self)*other; }
    FXMat3d operator*(FXdouble x) const { return (*self)*x; }
    FXMat3d operator/(FXdouble x) const {
      if(x==0.0) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/x;
      }

    /// Multiply matrix and vector
    FXVec3d operator*(const FXVec3d& other) const { return (*self)*other; }

    /// Mutiply matrix and vector, for non-projective matrix
    FXVec2d operator*(const FXVec2d& other) const { return (*self)*other; }
    }

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
  };

