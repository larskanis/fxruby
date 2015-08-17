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

%rename("crosses?") FXVec4d::crosses(const FXVec3d& a,const FXVec3d& b) const;
%naturalvar FXVec4d;

/// Double-precision 4-element vector
class FXVec4d {
public:
  FXdouble x;
  FXdouble y;
  FXdouble z;
  FXdouble w;
public:

  /// Default constructor
  %extend {
		FXVec4d() {
			return new FXVec4d(0.0, 0.0, 0.0, 0.0);
		}
	}

  /// Copy constructor
  FXVec4d(const FXVec4d& v);

  /// Initialize with 3-vector and optional scalar
  FXVec4d(const FXVec3d& v,FXdouble ww=1.0);

  /// Initialize with components
  FXVec4d(FXdouble xx,FXdouble yy,FXdouble zz,FXdouble ww=1.0);

  /// Initialize with color
  FXVec4d(FXColor color);

  /// Signed distance normalized plane and point
  FXdouble distance(const FXVec3d& p) const;

  /// Return true if edge a-b crosses plane
  bool crosses(const FXVec3d& a,const FXVec3d& b) const;

  /// Length and square of length
  FXdouble length2() const;
  FXdouble length() const;

  %extend {
    /// Indexing
    FXdouble __getitem__(FXint i) const {
      if(i<0||i>3) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXdouble __setitem__(FXint i,FXdouble d){
      if(i<0||i>3) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=d;
      return d;
      }

    /// Unary
    FXVec4d operator-() const { return -(*self); }

    /// Adding
    FXVec4d operator+(const FXVec4d& other) const { return (*self)+other; }

    /// Subtracting
    FXVec4d operator-(const FXVec4d& other) const { return (*self)-other; }

    /// Scaling
    FXVec4d operator*(FXdouble n) const { return (*self)*n; }
    FXVec4d operator/(FXdouble n) const {
      if(n==0.0) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/n;
      }

    /// Dot product
    FXdouble operator*(const FXVec4d& other) const { return (*self)*other; }
    FXdouble dot(const FXVec4d& other) const { return (*self)*other; }

    /// Equality tests
    bool operator==(const FXVec4d& other) const { return (*self)==other; }

    /// Normalize vector
    FXVec4d normalize() const { return normalize(*self); }

    /// Lowest or highest components
    FXVec4d lo(const FXVec4d& other) const { return lo(*self,other); }
    FXVec4d hi(const FXVec4d& other) const { return hi(*self,other); }

    /// Compute normalized plane equation ax+by+cz+d=0
    static FXVec4d plane(const FXVec4d& vec){ return FX::plane(vec); }
    static FXVec4d plane(const FXVec3d& vec,FXdouble dist){ return FX::plane(vec,dist); }
    static FXVec4d plane(const FXVec3d& vec,const FXVec3d& p){ return FX::plane(vec,p); }
    static FXVec4d plane(const FXVec3d& a,const FXVec3d& b,const FXVec3d& c){ return FX::plane(a,b,c); }
    }

    /// Clamp values of vector between limits
    FXVec4d& clamp(FXdouble lo,FXdouble hi);
  };

