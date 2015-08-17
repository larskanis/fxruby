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

%naturalvar FXVec2f;
/// Single-precision 2-element vector
class FXVec2f {
public:
  FXfloat x;
  FXfloat y;
public:

	/// Initialize with components
	FXVec2f(FXfloat xx=0.0f,FXfloat yy=0.0f);

  /// Copy constructor
  FXVec2f(const FXVec2f& v);

  // Initialize from array of floats
  FXVec2f(const FXfloat v[]);

  /// Length and square of length
  FXfloat length2() const;
  FXfloat length() const;

  %extend {
    /// Indexing
    FXfloat __getitem__(FXint i) const {
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXfloat __setitem__(FXint i,FXfloat f){
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=f;
      return f;
      }

    /// Unary
    FXVec2f operator-() const { return -(*self); }

    /// Adding
    FXVec2f operator+(const FXVec2f& other) const { return (*self)+other; }
    FXVec2f operator-(const FXVec2f& other) const { return (*self)-other; }

    /// Scaling
    FXVec2f operator*(FXfloat n) const { return (*self)*n; }
    FXVec2f operator/(FXfloat n) const {
      if(n==0.0f) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/n;
      }

    /// Dot product
    FXfloat operator*(const FXVec2f& other) const { return (*self)*other; }
    FXfloat dot(const FXVec2f& other) const { return (*self)*other; }

    /// Equality tests
    bool operator==(const FXVec2f& other) const { return (*self)==other; }

    /// Normalize vector
    FXVec2f normalize() const { return normalize(*self); }

    /// Lowest or highest components
    FXVec2f lo(const FXVec2f& other) const { return lo(*self,other); }
    FXVec2f hi(const FXVec2f& other) const { return hi(*self,other); }
    }

    /// Clamp values of vector between limits
    FXVec2f& clamp(FXfloat lo,FXfloat hi);
  };

