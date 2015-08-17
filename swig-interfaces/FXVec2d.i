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

%naturalvar FXVec2d;
/// Double-precision 2-element vector
class FXVec2d {
public:
  FXdouble x;
  FXdouble y;
public:

	/// Initialize with components
	FXVec2d(FXdouble xx=0.0,FXdouble yy=0.0);

  /// Copy constructor
  FXVec2d(const FXVec2d& v);

  /// Length and square of length
  FXdouble length2() const;
  FXdouble length() const;

  %extend {
    /// Indexing
    FXdouble __getitem__(FXint i) const {
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }

    FXdouble __setitem__(FXint i,FXdouble d){
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=d;
      return d;
      }

    /// Unary
    FXVec2d operator-() const { return -(*self); }

    /// Adding
    FXVec2d operator+(const FXVec2d& other) const { return (*self)+other; }

    /// Subtracting
    FXVec2d operator-(const FXVec2d& other) const { return (*self)-other; }

    /// Scaling
    FXVec2d operator*(FXdouble n) const { return (*self)*n; }
    FXVec2d operator/(FXdouble n) const {
      if(n==0.0) rb_raise(rb_eZeroDivError,"divided by 0");
      return (*self)/n;
      }

    /// Dot product
    FXdouble operator*(const FXVec2d& other) const { return (*self)*other; }
    FXdouble dot(const FXVec2d& other) const { return (*self)*other; }

    /// Equality tests
    bool operator==(const FXVec2d& other) const { return (*self)==other; }

    /// Normalize vector
    FXVec2d normalize() const { return normalize(*self); }

    /// Lowest or highest components
    FXVec2d lo(const FXVec2d& other) const { return lo(*self,other); }
    FXVec2d hi(const FXVec2d& other) const { return hi(*self,other); }
    }

    /// Clamp values of vector between limits
    FXVec2d& clamp(FXdouble lo,FXdouble hi);
  };

