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

/// Single-precision 3x3 matrix
class FXMat3f {
public:

  /// Default constructor
  FXMat3f();

  /// Copy constructor
  FXMat3f(const FXMat3f& other);

  /// Construct from scalar number
  FXMat3f(FXfloat w);

  /// Construct from components
  FXMat3f(FXfloat a00,FXfloat a01,FXfloat a02,
          FXfloat a10,FXfloat a11,FXfloat a12,
          FXfloat a20,FXfloat a21,FXfloat a22);

  /// Construct matrix from three vectors
  FXMat3f(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c);

  /// Construct rotation matrix from quaternion
  FXMat3f(const FXQuatf& quat);

  %extend {
    /// Indexing
    const FXVec3f& __getitem__(FXint i) const {
      if(i<0 || i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXVec3f& __setitem__(FXint i,const FXVec3d& other){
      if(i<0 || i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=other;
      return (*self)[i];
      }

    /// Other operators
    FXMat3f operator+(const FXMat3f& other) const { return (*self)+other; }
    FXMat3f operator-(const FXMat3f& other) const { return (*self)-other; }
    FXMat3f operator-() const { return -(*self); }
    FXMat3f operator*(const FXMat3f& other) const { return (*self)*other; }
    FXMat3f operator*(FXfloat x) const { return (*self)*x; }
    FXMat3f operator/(FXfloat x) const {
      if(x==0.0f) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/x;
      }

    /// Multiply matrix and vector
    FXVec3f operator*(const FXVec3f& other) const { return (*self)*other; }

    /// Mutiply matrix and vector, for non-projective matrix
    FXVec2f operator*(const FXVec2f& other) const { return (*self)*other; }
    }

  /// Set identity matrix
  FXMat3f& eye();

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
  };

