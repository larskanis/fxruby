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

%ignore FXRangef::operator=(const FXRangef& bounds);

%rename("empty?") FXRangef::empty() const;
%rename("overlaps?") FXRangef::overlaps(const FXRangef& box) const;

%rename("contains?") FXRangef::contains(FXfloat x,FXfloat y,FXfloat z) const;
%rename("contains?") FXRangef::contains(const FXVec3f& p) const;
%rename("contains?") FXRangef::contains(const FXRangef& bounds) const;
%rename("contains?") FXRangef::contains(const FXSpheref& sphere) const;

%rename("include!") FXRangef::include(FXfloat x,FXfloat y,FXfloat z);
%rename("include!") FXRangef::include(const FXVec3f& v);
%rename("include!") FXRangef::include(const FXRangef& box);
%rename("include!") FXRangef::include(const FXSpheref& sphere);

%rename("intersects?") FXRangef::intersect(const FXVec3f& u,const FXVec3f& v) const;
%rename("union") FXRangef::onion(const FXRangef& other) const;

/// Range
class FXRangef {
public:

  // Default constructor
  FXRangef();

  // Copy constructor
  FXRangef(const FXRangef& bounds);

  // Initialize
  FXRangef(FXfloat xlo,FXfloat xhi,FXfloat ylo,FXfloat yhi,FXfloat zlo,FXfloat zhi);

  // Initialize box to fully contains the given bounding sphere.
  FXRangef(const FXSpheref& sphere);

  // Assignment
  FXRangef& operator=(const FXRangef& bounds);

  %extend {
    // Indexing with 0 or 1
    FXVec3f& __getitem__(FXint i){
      if(i<0||1<i){
        rb_raise(rb_eIndexError,"index %d out of bounds",i);
        }
      return (*self)[i];
      }

    void __setitem__(FXint i,FXVec3f& slice){
      if(i<0||1<i){
        rb_raise(rb_eIndexError,"index %d out of bounds",i);
        }
      (*self)[i]=slice;
      }

    FXVec3f upper() const {
      return self->upper;
      }

    FXVec3f lower() const {
      return self->lower;
      }
  }

  // Width of box
  FXfloat width() const;

  // Height of box
  FXfloat height() const;

  // Depth of box
  FXfloat depth() const;

  // Longest side
  FXfloat longest() const;

  // Shortest side
  FXfloat shortest() const;

  // Length of diagonal
  FXfloat diameter() const;

  // Get radius of box
  FXfloat radius() const;

  // Compute diagonal
  FXVec3f diagonal() const;

  // Get center of box
  FXVec3f center() const;

  // Test if empty
  bool empty() const;

  // Test if box contains point x,y,z
  bool contains(FXfloat x,FXfloat y,FXfloat z) const;

  /// Test if box contains point p
  bool contains(const FXVec3f& p) const;

  /// Test if box properly contains another box
  bool contains(const FXRangef& bounds) const;

  /// Test if box properly contains sphere
  bool contains(const FXSpheref& sphere) const;

  // Include point
  FXRangef& include(FXfloat x,FXfloat y,FXfloat z);

  // Include point
  FXRangef& include(const FXVec3f& v);

  // Include given range into box
  FXRangef& include(const FXRangef& box);

  // Include given sphere into this box
  FXRangef& include(const FXSpheref& sphere);

  // Intersect box with plane ax+by+cz+w; returns -1,0,+1
  FXint intersect(const FXVec4f& plane) const;

  /// Intersect box with ray u-v
  bool intersect(const FXVec3f& u,const FXVec3f& v);

  %extend {
    // Test if this box overlaps with other
    bool overlaps(const FXRangef& other) const {
      return FX::overlap(*self,other);
      }

    /// Get corner number 0..7
    FXVec3f corner(FXint c) const {
      if(c<0||7<c){
        rb_raise(rb_eIndexError,"corner index %d out of bounds",c);
        }
      return self->corner(c);
      }

    /// Union of two boxes
    // This is not a typo. We're calling it "onion" here to work around
    // a bug in SWIG that thinks "union" is the C++ keyword union.
    FXRangef onion(const FXRangef& other) const {
      return FX::unite(*self,other);
      }

    /// Intersection of two boxes
    FXRangef intersection(const FXRangef& other) const {
      return FX::intersect(*self,other);
      }
    }
  };

