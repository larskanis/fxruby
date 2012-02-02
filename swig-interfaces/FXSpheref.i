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

%ignore FXSpheref::operator=(const FXSpheref&);

%rename("empty?")	FXSpheref::empty() const;
%rename("contains?")	FXSpheref::contains(FXfloat x,FXfloat y,FXfloat z) const;
%rename("contains?")	FXSpheref::contains(const FXVec3f& p) const;
%rename("contains?")	FXSpheref::contains(const FXRangef& box) const;
%rename("contains?")	FXSpheref::contains(const FXSpheref& sphere) const;
%rename("include!")	FXSpheref::include(FXfloat x,FXfloat y,FXfloat z);
%rename("include!")	FXSpheref::include(const FXVec3f& p);
%rename("includeInRadius!") FXSpheref::includeInRadius(FXfloat x,FXfloat y,FXfloat z);
%rename("includeInRadius!") FXSpheref::includeInRadius(const FXVec3f& p);
%rename("include!")	FXSpheref::include(const FXRangef& box);
%rename("includeInRadius!") FXSpheref::includeInRadius(const FXRangef& box);
%rename("include!")	FXSpheref::include(const FXSpheref& sphere);
%rename("includeInRadius!") FXSpheref::includeInRadius(const FXSpheref& sphere);
%rename("intersects?")	FXSpheref::intersect(const FXVec3f& u,const FXVec3f& v) const;
%rename("overlaps?")	FXSpheref::overlap(const FXRangef& other) const;
%rename("overlaps?")	FXSpheref::overlap(const FXSpheref& other) const;

// Spherical bounds
class FXSpheref {
public:
  FXVec3f center;
  FXfloat radius;
public:

  /// Default constructor
  FXSpheref();

  /// Copy constructor
  FXSpheref(const FXSpheref& sphere);

  /// Initialize from center and radius
  FXSpheref(const FXVec3f& cen,FXfloat rad=0.0f);

  /// Initialize from center and radius
  FXSpheref(FXfloat x,FXfloat y,FXfloat z,FXfloat rad=0.0f);

  /// Initialize sphere to fully contain the given bounding box
  FXSpheref(const FXRangef& bounds);

  /// Assignment
  FXSpheref& operator=(const FXSpheref& sphere);

  // Diameter of sphere
  FXfloat diameter() const;

  /// Test if empty
  bool empty() const;

  /// Test if sphere contains point x,y,z
  bool contains(FXfloat x,FXfloat y,FXfloat z) const;

  /// Test if sphere contains point p
  bool contains(const FXVec3f& p) const;

  /// Test if sphere properly contains another box
  bool contains(const FXRangef& box) const;

  /// Test if sphere properly contains another sphere
  bool contains(const FXSpheref& sphere) const;

  /// Include point
  FXSpheref& include(FXfloat x,FXfloat y,FXfloat z);

  /// Include point
  FXSpheref& include(const FXVec3f& p);

  /// Expand radius to include point
  FXSpheref& includeInRadius(FXfloat x,FXfloat y,FXfloat z);

  /// Expand radius to include point
  FXSpheref& includeInRadius(const FXVec3f& p);

  /// Include given range into this one
  FXSpheref& include(const FXRangef& box);

  /// Expand radius to include box
  FXSpheref& includeInRadius(const FXRangef& box);

  /// Include given sphere into this one
  FXSpheref& include(const FXSpheref& sphere);

  /// Expand radius to include sphere
  FXSpheref& includeInRadius(const FXSpheref& sphere);

  // Intersect sphere with plane ax+by+cz+w; returns -1,0,+1
  FXint intersect(const FXVec4f& plane) const;

  /// Intersect sphere with ray u-v
  bool intersect(const FXVec3f& u,const FXVec3f& v) const;

  %extend {
    /// Test if sphere overlaps with box
    bool overlap(const FXRangef& other) const {
      return overlap(*self,other);
      }

    /// Test if spheres overlap
    bool overlap(const FXSpheref& other) const {
      return overlap(*self,other);
      }
    }
  };
