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

%ignore FXSphered::operator=(const FXSphered&);

%rename("empty?")	FXSphered::empty() const;
%rename("contains?")	FXSphered::contains(FXdouble x,FXdouble y,FXdouble z) const;
%rename("contains?")	FXSphered::contains(const FXVec3d& p) const;
%rename("contains?")	FXSphered::contains(const FXRanged& box) const;
%rename("contains?")	FXSphered::contains(const FXSphered& sphere) const;
%rename("include!")	FXSphered::include(FXdouble x,FXdouble y,FXdouble z);
%rename("include!")	FXSphered::include(const FXVec3d& p);
%rename("includeInRadius!") FXSphered::includeInRadius(FXdouble x,FXdouble y,FXdouble z);
%rename("includeInRadius!") FXSphered::includeInRadius(const FXVec3d& p);
%rename("include!")	FXSphered::include(const FXRanged& box);
%rename("includeInRadius!") FXSphered::includeInRadius(const FXRanged& box);
%rename("include!")	FXSphered::include(const FXSphered& sphere);
%rename("includeInRadius!") FXSphered::includeInRadius(const FXSphered& sphere);
%rename("intersects?")	FXSphered::intersect(const FXVec3d& u,const FXVec3d& v) const;
%rename("overlaps?")	FXSphered::overlap(const FXRanged& other) const;
%rename("overlaps?")	FXSphered::overlap(const FXSphered& other) const;

// Spherical bounds
class FXSphered {
public:
  FXVec3d center;
  FXdouble radius;
public:

  /// Default constructor
  FXSphered();

  /// Copy constructor
  FXSphered(const FXSphered& sphere);

  /// Initialize from center and radius
  FXSphered(const FXVec3d& cen,FXdouble rad=0.0);

  /// Initialize from center and radius
  FXSphered(FXdouble x,FXdouble y,FXdouble z,FXdouble rad=0.0);

  /// Initialize sphere to fully contain the given bounding box
  FXSphered(const FXRanged& bounds);

  /// Assignment
  FXSphered& operator=(const FXSphered& sphere);

  // Diameter of sphere
  FXdouble diameter() const;

  /// Test if empty
  bool empty() const;

  /// Test if sphere contains point x,y,z
  bool contains(FXdouble x,FXdouble y,FXdouble z) const;

  /// Test if sphere contains point p
  bool contains(const FXVec3d& p) const;

  /// Test if sphere properly contains another box
  bool contains(const FXRanged& box) const;

  /// Test if sphere properly contains another sphere
  bool contains(const FXSphered& sphere) const;

  /// Include point
  FXSphered& include(FXdouble x,FXdouble y,FXdouble z);

  /// Include point
  FXSphered& include(const FXVec3d& p);

  /// Expand radius to include point
  FXSphered& includeInRadius(FXdouble x,FXdouble y,FXdouble z);

  /// Expand radius to include point
  FXSphered& includeInRadius(const FXVec3d& p);

  /// Include given range into this one
  FXSphered& include(const FXRanged& box);

  /// Expand radius to include box
  FXSphered& includeInRadius(const FXRanged& box);

  /// Include given sphere into this one
  FXSphered& include(const FXSphered& sphere);

  /// Expand radius to include sphere
  FXSphered& includeInRadius(const FXSphered& sphere);

  // Intersect sphere with plane ax+by+cz+w; returns -1,0,+1
  FXint intersect(const FXVec4d& plane) const;

  /// Intersect sphere with ray u-v
  bool intersect(const FXVec3d& u,const FXVec3d& v) const;

  %extend {
    /// Test if sphere overlaps with box
    bool overlap(const FXRanged& other) const {
      return overlap(*self,other);
      }

    /// Test if spheres overlap
    bool overlap(const FXSphered& other) const {
      return overlap(*self,other);
      }
    }
  };
