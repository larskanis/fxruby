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

%ignore FXRanged::operator=(const FXRanged& bounds);

%rename("empty?") FXRanged::empty() const;
%rename("overlaps?") FXRanged::overlaps(const FXRanged& box) const;

%rename("contains?") FXRanged::contains(FXfloat x,FXfloat y,FXfloat z) const;
%rename("contains?") FXRanged::contains(const FXVec3d& p) const;
%rename("contains?") FXRanged::contains(const FXRanged& bounds) const;
%rename("contains?") FXRanged::contains(const FXSphered& sphere) const;

%rename("intersects?") FXRanged::intersect(const FXVec3d& u,const FXVec3d& v) const;
%rename("union") FXRanged::onion(const FXRanged& other) const;

/// Range
class FXRanged {
public:
  FXVec3d lower;
  FXVec3d upper;
public:

  // Default constructor
  FXRanged();

  // Copy constructor
  FXRanged(const FXRanged& bounds);

  // Initialize
  FXRanged(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi,FXdouble zlo,FXdouble zhi);

  // Initialize box to fully contains the given bounding sphere.
  FXRanged(const FXSphered& sphere);

  // Assignment
  FXRanged& operator=(const FXRanged& bounds);

  %extend {
    // Indexing with 0 or 1
    FXVec3d& __getitem__(FXint i){
      if(i<0||1<i){
        rb_raise(rb_eIndexError,"index %d out of bounds",i);
        }
      return (*self)[i];
      }
    void __setitem__(FXint i,FXVec3d& slice){
      if(i<0||1<i){
        rb_raise(rb_eIndexError,"index %d out of bounds",i);
        }
      (*self)[i]=slice;
      }
  }

  // Width of box
  FXdouble width() const;

  // Height of box
  FXdouble height() const;

  // Depth of box
  FXdouble depth() const;

  // Longest side
  FXdouble longest() const;

  // Shortest side
  FXdouble shortest() const;

  // Length of diagonal
  FXdouble diameter() const;

  // Radius of box
  FXdouble radius() const;

  // Compute diagonal
  FXVec3d diagonal() const;

  // Get center of box
  FXVec3d center() const;

  // Test if empty
  bool empty() const;

  // Test if box contains point x,y,z
  bool contains(FXdouble x,FXdouble y,FXdouble z) const;

  /// Test if box contains point p
  bool contains(const FXVec3d& p) const;

  /// Test if box properly contains another box
  bool contains(const FXRanged& bounds) const;

  /// Test if box properly contains sphere
  bool contains(const FXSphered& sphere) const;

  // Include point
  FXRanged& include(FXdouble x,FXdouble y,FXdouble z);

  // Include point
  FXRanged& include(const FXVec3d& v);

  // Include given range into box
  FXRanged& include(const FXRanged& box);

  // Include given sphere into this box
  FXRanged& include(const FXSphered& sphere);

  // Intersect box with plane ax+by+cz+w; returns -1,0,+1
  FXint intersect(const FXVec4d& plane) const;

  /// Intersect box with ray u-v
  bool intersect(const FXVec3d& u,const FXVec3d& v);

  %extend {
    // Test if this box overlaps with other
    bool overlaps(const FXRanged& other) const {
      return FX::overlap(*self,other);
      }

    /// Get corner number 0..7
    FXVec3d corner(FXint c) const {
      if(c<0||7<c){
        rb_raise(rb_eIndexError,"corner index %d out of bounds",c);
        }
      return self->corner(c);
      }

    /// Union of two boxes
    // This is not a typo.
    // We're calling this method "onion" to work around a bug in SWIG
    // that mistakes the method name "union" for the C++ keyword of the same
    // name.
    FXRanged onion(const FXRanged& other) const {
      return FX::unite(*self,other);
      }

    /// Intersection of two boxes
    FXRanged intersection(const FXRanged& other) const {
      return FX::intersect(*self,other);
      }
    }
  };

