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

%naturalvar FXVec3f;
/// Single-precision 3-element vector
class FXVec3f {
public:
  FXfloat x;
  FXfloat y;
  FXfloat z;
public:

  /// Default constructor
  %extend {
		FXVec3f() {
			return new FXVec3f(0.0f, 0.0f, 0.0f);
		}
	}

  /// Copy constructor
  FXVec3f(const FXVec3f& v);

  /// Initialize with components
  FXVec3f(FXfloat xx,FXfloat yy,FXfloat zz=1.0f);

  /// Initialize with color
  FXVec3f(FXColor color);

  /// Length and square of length
  FXfloat length2() const;
  FXfloat length() const;

  %extend {
    /// Indexing
    FXfloat __getitem__(FXint i) const {
      if(i<0||i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXfloat __setitem__(FXint i,FXfloat f){
      if(i<0||i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=f;
      return f;
      }

    /// Unary
    FXVec3f operator-() const { return -(*self); }

    /// Adding
    FXVec3f operator+(const FXVec3f& other) const { return (*self)+other; }

    /// Subtracting
    FXVec3f operator-(const FXVec3f& other) const { return (*self)-other; }

    /// Scaling
    FXVec3f operator*(FXfloat n) const { return (*self)*n; }
    FXVec3f operator/(FXfloat n) const {
      if(n==0.0f) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/n;
      }

    /// Dot and cross products
    FXfloat operator*(const FXVec3f& other) const { return (*self)*other; }
    FXfloat dot(const FXVec3f& other) const { return (*self)*other; }
    FXVec3f operator^(const FXVec3f& other) const  { return (*self)^other; }
    FXVec3f cross(const FXVec3f& other) const  { return (*self)^other; }

    /// Equality tests
    bool operator==(const FXVec3f& other) const { return (*self)==other; }

    /// Normalize vector
    FXVec3f normalize() const { return normalize(*self); }

    /// Lowest or highest components
    FXVec3f lo(const FXVec3f& other) const { return lo(*self,other); }
    FXVec3f hi(const FXVec3f& other) const { return hi(*self,other); }

    /// Compute normal from three points a,b,c
    static FXVec3f normal(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c){
      return FX::normal(a,b,c);
      }

    /// Compute approximate normal from four points a,b,c,d
    static FXVec3f normal(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c,const FXVec3f& d){
      return FX::normal(a,b,c,d);
      }
    }

   /// Clamp values of vector between limits
   FXVec3f& clamp(FXfloat lo,FXfloat hi);
  };

