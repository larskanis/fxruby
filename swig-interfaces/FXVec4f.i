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

%rename("crosses?") FXVec4f::crosses(const FXVec3f& a,const FXVec3f& b) const;
%naturalvar FXVec4f;

/// Single-precision 4-element vector
class FXVec4f {
public:
  FXfloat x;
  FXfloat y;
  FXfloat z;
  FXfloat w;
public:

  /// Default constructor
  %extend {
		FXVec4f() {
			return new FXVec4f(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

  /// Copy constructor
  FXVec4f(const FXVec4f& w);

  /// Initialize with 3-vector and optional scalar
  FXVec4f(const FXVec3f& w,FXfloat ww=1.0f);

  /// Initialize with components
  FXVec4f(FXfloat x,FXfloat y,FXfloat z,FXfloat w=1.0f);

  /// Initialize with color
  FXVec4f(FXColor color);

  /// Signed distance normalized plane and point
  FXfloat distance(const FXVec3f& p) const;

  /// Return true if edge a-b crosses plane
  bool crosses(const FXVec3f& a,const FXVec3f& b) const;

  FXfloat length() const;
  FXfloat length2() const;

  %extend {
    /// Indexing
    FXfloat __getitem__(FXint i) const {
      if(i<0||i>3) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXfloat __setitem__(FXint i,FXfloat f){
      if(i<0||i>3) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=f;
      return f;
      }

    // Negation
    FXVec4f operator-() const { return -(*self); }

    // Addition
    FXVec4f operator+(const FXVec4f& b) const { return (*self)+b; }

    // Subtraction
    FXVec4f operator-(const FXVec4f& b) const { return (*self)-b; }

    // Multiply by a scalar
    FXVec4f operator*(FXfloat n) const { return (*self)*n; }

    // Divide by a scalar
    FXVec4f operator/(FXfloat n) const {
      if(n==0.0f) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/n;
      }

    /// Dot product
    FXfloat operator*(const FXVec4f& a) const { return (*self)*a; }
    FXfloat dot(const FXVec4f& a) const { return (*self)*a; }

    /// Equality tests
    bool operator==(const FXVec4f& b) const { return (*self == b); }
    bool operator==(FXfloat n) const { return (*self == n); }

    // Other functions
    FXVec4f normalize() const { return normalize(*self); }
    FXVec4f lo(const FXVec4f& other) const { return lo(*self,other); }
    FXVec4f hi(const FXVec4f& other) const { return hi(*self,other); }

    /// Compute normalized plane equation ax+by+cz+d=0
    static FXVec4f plane(const FXVec4f& vec){ return FX::plane(vec); }
    static FXVec4f plane(const FXVec3f& vec,FXfloat dist){ return FX::plane(vec,dist); }
    static FXVec4f plane(const FXVec3f& vec,const FXVec3f& p){ return FX::plane(vec,p); }
    static FXVec4f plane(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c){ return FX::plane(a,b,c); }
    }

    /// Clamp values of vector between limits
    FXVec4f& clamp(FXfloat lo,FXfloat hi);
  };

