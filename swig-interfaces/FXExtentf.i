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

%rename("empty?") FXExtentf::empty() const;
%rename("contains?") FXExtentf::contains(FXdouble x,FXdouble y) const;
%rename("contains?") FXExtentf::contains(const FXVec2f& p) const;
%rename("contains?") FXExtentf::contains(const FXExtentf& ext) const;
%rename("include!") FXExtentf::include(FXdouble x,FXdouble y);
%rename("include!") FXExtentf::include(const FXVec2f& v);
%rename("include!") FXExtentf::include(const FXExtentf& ext);
%rename("overlap?") FXExtentf::overlap(const FXExtentf& other) const;

/// Extent
class FXExtentf {
public:
  FXVec2f lower;
  FXVec2f upper;
public:

  /// Default constructor
  FXExtentf();

  /// Copy constructor
  FXExtentf(const FXExtentf& ext);

  /// Initialize from two vectors
  FXExtentf(const FXVec2f& lo,const FXVec2f& hi);

  /// Initialize from six numbers
  FXExtentf(FXfloat xlo,FXfloat xhi,FXfloat ylo,FXfloat yhi);

  %extend {
    /// Indexing with 0..1
    FXVec2f& __setitem__(FXint i,FXVec2f& v) {
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=v;
      return v;
      }

    /// Indexing with 0..1
    const FXVec2f& __getitem__(FXint i) const {
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
  }

  /// Width of box
  FXfloat width() const;

  /// Height of box
  FXfloat height() const;

  /// Longest side
  FXfloat longest() const;

  /// shortest side
  FXfloat shortest() const;

  /// Length of diagonal
  FXfloat diameter() const;

  /// Get radius of box
  FXfloat radius() const;

  /// Compute diagonal
  FXVec2f diagonal() const;

  /// Get center of box
  FXVec2f center() const;

  /// Test if empty
  bool empty() const;

  /// Test if box contains point x,y
  bool contains(FXfloat x,FXfloat y) const;

  /// Test if box contains point p
  bool contains(const FXVec2f& p) const;

  /// Test if box properly contains another box
  bool contains(const FXExtentf& ext) const;

  /// Include point
  FXExtentf& include(FXfloat x,FXfloat y);

  /// Include point
  FXExtentf& include(const FXVec2f& v);

  /// Include given range into extent
  FXExtentf& include(const FXExtentf& ext);

  /// Get corner number 0..3
  FXVec2f corner(FXint c) const;

  %extend {
    /// Test if bounds overlap
    bool overlap(const FXExtentf& other) const {
      return overlap(*self,other);
      }

    /// Union of two boxes
    FXExtentf unite_with(const FXExtentf& other) const {
      return unite(*self,other);
      }

    /// Intersection of two boxes
    FXExtentf intersect_with(const FXExtentf& other) const {
      return intersect(*self,other);
      }
    }
  };

