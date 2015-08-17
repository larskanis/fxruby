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

%naturalvar FXVec3d;
/// Double-precision 3-element vector
class FXVec3d {
public:
  FXdouble x;
  FXdouble y;
  FXdouble z;
public:

  /// Default constructor
  %extend {
		FXVec3d() {
			return new FXVec3d(0.0, 0.0, 0.0);
		}
	}

  /// Copy constructor
  FXVec3d(const FXVec3d& v);

  /// Initialize with components
  FXVec3d(FXdouble xx,FXdouble yy,FXdouble zz=1.0);

  /// Initialize with color
  FXVec3d(FXColor color);

  /// Length and square of length
  FXdouble length2() const;
  FXdouble length() const;

  %extend {
    /// Indexing
    FXdouble __getitem__(FXint i) const {
      if(i<0||i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
    FXdouble __setitem__(FXint i,FXdouble d){
      if(i<0||i>2) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=d;
      return d;
      }

    /// Unary
    FXVec3d operator-() const { return -(*self); }

    /// Adding
    FXVec3d operator+(const FXVec3d& other) const { return (*self)+other; }

    /// Subtracting
    FXVec3d operator-(const FXVec3d& other) const { return (*self)-other; }

    /// Scaling
    FXVec3d operator*(FXdouble n) const { return (*self)*n; }
    FXVec3d operator/(FXdouble n) const {
      if(n==0.0) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/n;
      }

    /// Dot product
    FXdouble operator*(const FXVec3d& other) const { return (*self)*other; }
    FXdouble dot(const FXVec3d& other) const { return (*self)*other; }

    /// Cross product
    FXVec3d operator^(const FXVec3d& other) const  { return (*self)^other; }
    FXVec3d cross(const FXVec3d& other) const  { return (*self)^other; }

    /// Equality tests
    bool operator==(const FXVec3d& other) const { return (*self)==other; }

    /// Normalize vector
    FXVec3d normalize() const { return normalize(*self); }

    /// Lowest or highest components
    FXVec3d lo(const FXVec3d& other) const { return lo(*self,other); }
    FXVec3d hi(const FXVec3d& other) const { return hi(*self,other); }

    /// Compute normal from three points a,b,c
    static FXVec3d normal(const FXVec3d& a,const FXVec3d& b,const FXVec3d& c){
      return FX::normal(a,b,c);
      }

    /// Compute approximate normal from four points a,b,c,d
    static FXVec3d normal(const FXVec3d& a,const FXVec3d& b,const FXVec3d& c,const FXVec3d& d){
      return FX::normal(a,b,c,d);
      }
    }

    /// Clamp values of vector between limits
    FXVec3d& clamp(FXdouble lo,FXdouble hi);
  };

