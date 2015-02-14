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

/// Double-precision 4x4 matrix
class FXMat4d {
public:
  /// Constructors
  FXMat4d();
  FXMat4d(FXdouble w);
  FXMat4d(FXdouble a00,FXdouble a01,FXdouble a02,FXdouble a03,
          FXdouble a10,FXdouble a11,FXdouble a12,FXdouble a13,
          FXdouble a20,FXdouble a21,FXdouble a22,FXdouble a23,
          FXdouble a30,FXdouble a31,FXdouble a32,FXdouble a33);
  FXMat4d(const FXVec4d& a,const FXVec4d& b,const FXVec4d& c,const FXVec4d& d);
  FXMat4d(const FXMat4d& other);

  %extend {
    /// Indexing
    const FXVec4d& __getitem__(FXint i) const {
      if(i<0 || i>3) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXVec4d& __setitem__(FXint i,const FXVec3d& other){
      if(i<0 || i>3) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=other;
      return (*self)[i];
      }

    /// Other operators
    FXMat4d operator+(const FXMat4d& other) const { return (*self)+other; }
    FXMat4d operator-(const FXMat4d& other) const { return (*self)-other; }
    FXMat4d operator-() const { return -(*self); }
    FXMat4d operator*(const FXMat4d& other) const { return (*self)*other; }
    FXMat4d operator*(FXdouble x) const { return (*self)*x; }
    FXMat4d operator/(FXdouble x) const {
      if(x==0.0) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/x;
      }

    /// Multiply matrix and vector
    FXVec4d operator*(const FXVec4d& other) const { return (*self)*other; }

    /// Mutiply matrix and vector, for non-projective matrix
    FXVec3d operator*(const FXVec3d& v) const { return (*self)*v; }
    }

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

  // Determinant
  FXdouble det() const;

  /// Transpose
  FXMat4d transpose() const;

  /// Invert
  FXMat4d invert() const;
  };

