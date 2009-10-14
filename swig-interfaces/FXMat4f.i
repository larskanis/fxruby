/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

// Provide aliases for backwards-compatibility with FXRuby 1.6
%alias FXMat4f::identity() "eye";
%alias FXMat4f::setOrtho(FXfloat, FXfloat, FXfloat, FXfloat, FXfloat, FXfloat) "ortho";
%alias FXMat4f::setFrustum(FXfloat, FXfloat, FXfloat, FXfloat, FXfloat, FXfloat) "frustum";

// Single-precision 4x4 matrix
class FXMat4f {
protected:
  FXVec4f m[4];
public:
  /// Constructors
  FXMat4f();
  FXMat4f(FXfloat w);
  FXMat4f(FXfloat a00,FXfloat a01,FXfloat a02,FXfloat a03,
          FXfloat a10,FXfloat a11,FXfloat a12,FXfloat a13,
          FXfloat a20,FXfloat a21,FXfloat a22,FXfloat a23,
          FXfloat a30,FXfloat a31,FXfloat a32,FXfloat a33);
  FXMat4f(const FXVec4f& a,const FXVec4f& b,const FXVec4f& c,const FXVec4f& d);
  FXMat4f(const FXMat4f& other);

  // Determinant
  FXfloat det() const;

  // Transpose
  FXMat4f transpose() const;

  // Invert
  FXMat4f invert() const;

  %extend {
    /// Indexing
    const FXVec4f& __getitem__(FXint i) const {
      if(i<0 || i>3) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }

    // Add matrices
    FXMat4f operator+(const FXMat4f& other) const { return (*self)+other; }

    // Subtract matrices
    FXMat4f operator-(const FXMat4f& other) const { return (*self)-other; }

    // Multiply by a matrix
    FXMat4f operator*(const FXMat4f& other) const { return (*self)*other; }
    
    // Multiply by a scalar
    FXMat4f operator*(FXfloat x) const { return (*self)*x; }
    
    // Multiply by a homogenous vector
    FXVec4f operator*(const FXVec4f& other) const { return (*self)*other; }
    
    // Multiply by a non-homogeneous vector, for non-projective matrix
    FXVec3f operator*(const FXVec3f& other) const { return (*self)*other; }
    
    // Divide by a scalar
    FXMat4f operator/(FXfloat x) const {
      if(x==0.0f) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/x;
      }
    
    // Negation
    FXMat4f operator-() const { return -(*self); }
    }

  /// Set identity matrix
  FXMat4f& identity();

  /// Return true if identity matrix
  FXbool isIdentity() const;

  /// Orthographic projection
  FXMat4f& setOrtho(FXfloat xlo,FXfloat xhi,FXfloat ylo,FXfloat yhi,FXfloat zlo,FXfloat zhi);

  /// Perspective projection
  FXMat4f& setFrustum(FXfloat xlo,FXfloat xhi,FXfloat ylo,FXfloat yhi,FXfloat zlo,FXfloat zhi);

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
  FXMat4f& look(const FXVec3f& from,const FXVec3f& to,const FXVec3f& up);

  /// Multiply by translation
  FXMat4f& trans(FXfloat tx,FXfloat ty,FXfloat tz);
  FXMat4f& trans(const FXVec3f& v);

  /// Multiply by scaling
  FXMat4f& scale(FXfloat sx,FXfloat sy,FXfloat sz);
  FXMat4f& scale(FXfloat s);
  FXMat4f& scale(const FXVec3f& v);
  };
