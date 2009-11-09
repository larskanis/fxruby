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

%rename("empty?") FXExtentd::empty() const;
%rename("contains?") FXExtentd::contains(FXfloat x,FXfloat y) const;
%rename("contains?") FXExtentd::contains(const FXVec2d& p) const;
%rename("contains?") FXExtentd::contains(const FXExtentd& ext) const;
%rename("include!") FXExtentd::include(FXfloat x,FXfloat y);
%rename("include!") FXExtentd::include(const FXVec2d& v);
%rename("include!") FXExtentd::include(const FXExtentd& ext);
%rename("overlap?") FXExtentd::overlap(const FXExtentd& other) const;

/// Extent
class FXExtentd {
public:
  FXVec2d lower;
  FXVec2d upper;
public:

  /// Default constructor
  FXExtentd();

  /// Copy constructor
  FXExtentd(const FXExtentd& ext);

  /// Initialize with a single point
  FXExtentd(const FXVec2d& p);

  /// Initialize from corner points
  FXExtentd(const FXVec2d& lo,const FXVec2d& hi);

  /// Initialize with a single point
  FXExtentd(FXdouble x,FXdouble y);

  /// Initialize with explicit values
  FXExtentd(FXdouble xl,FXdouble xh,FXdouble yl,FXdouble yh);

  %extend {
    /// Indexing with 0..1
    FXVec2d& __setitem__(FXint i,FXVec2d& v) {
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      (*self)[i]=v;
      return v;
      }

    /// Indexing with 0..1
    const FXVec2d& __getitem__(FXint i) const {
      if(i<0||i>1) rb_raise(rb_eIndexError,"index %d out of bounds",i);
      return (*self)[i];
      }
  }

  /// Set value from another range
  FXExtentd& set(const FXExtentd& ext);

  /// Set value from single point
  FXExtentd& set(const FXVec2d& p);

  /// Set value from corner points
  FXExtentd& set(const FXVec2d& lo,const FXVec2d& hi);

  /// Set value from single point
  FXExtentd& set(FXdouble x,FXdouble y);

  /// Set value from explicit values
  FXExtentd& set(FXdouble xl,FXdouble xh,FXdouble yl,FXdouble yh);

  /// Width of box
  FXdouble width() const;

  /// Height of box
  FXdouble height() const;

  /// Longest side
  FXdouble longest() const;

  /// shortest side
  FXdouble shortest() const;

  /// Length of diagonal
  FXdouble diameter() const;

  /// Get radius of box
  FXdouble radius() const;

  /// Compute diagonal
  FXVec2d diagonal() const;

  /// Get center of box
  FXVec2d center() const;

  /// Test if empty
  FXbool empty() const;

  /// Test if box contains point x,y
  FXbool contains(FXdouble x,FXdouble y) const;

  /// Test if box contains point p
  FXbool contains(const FXVec2d& p) const;

  /// Test if box properly contains another box
  FXbool contains(const FXExtentd& ext) const;

  /// Include point
  FXExtentd& include(FXdouble x,FXdouble y);

  /// Include point
  FXExtentd& include(const FXVec2d& v);

  /// Include given range into extent
  FXExtentd& include(const FXExtentd& ext);

  /// Get corner number 0..3
  FXVec2d corner(FXint c) const;

  %extend {
    /// Test if bounds overlap
    FXbool overlap(const FXExtentd& other) const {
      return overlap(*self,other);
      }

    /// Union of two boxes
    FXExtentd unite_with(const FXExtentd& other) const {
      return unite(*self,other);
      }

    /// Intersection of two boxes
    FXExtentd intersect_with(const FXExtentd& other) const {
      return intersect(*self,other);
      }
    }
  };

