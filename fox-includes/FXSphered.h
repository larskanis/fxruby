/********************************************************************************
*                                                                               *
*           D o u b l e - P r e c i s i o n    S p h e r e    C l a s s         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXSphered.h 2345 2006-02-14 03:07:05Z lyle $                         *
********************************************************************************/
#ifndef FXSPHERED_H
#define FXSPHERED_H


namespace FX {


class FXRanged;


/// Spherical bounds
class FXAPI FXSphered {
public:
  FXVec3d  center;
  FXdouble radius;
public:

  /// Default constructor
  FXSphered(){}

  /// Copy constructor
  FXSphered(const FXSphered& sphere):center(sphere.center),radius(sphere.radius){}

  /// Initialize from center and radius
  FXSphered(const FXVec3d& cen,FXdouble rad=0.0):center(cen),radius(rad){}

  /// Initialize from center and radius
  FXSphered(FXdouble x,FXdouble y,FXdouble z,FXdouble rad=0.0):center(x,y,z),radius(rad){}

  /// Initialize sphere to fully contain the given bounding box
  FXSphered(const FXRanged& bounds);

  /// Assignment
  FXSphered& operator=(const FXSphered& sphere){ center=sphere.center; radius=sphere.radius; return *this; }

  /// Set value from another sphere
  FXSphered& set(const FXSphered& sphere){ center=sphere.center; radius=sphere.radius; return *this; }

  /// Set value from center and radius
  FXSphered& set(const FXVec3d& cen,FXdouble rad){ center=cen; radius=rad; return *this; }

  /// Set value from center and radius
  FXSphered& set(FXdouble x,FXdouble y,FXdouble z,FXdouble rad){ center.set(x,y,z); radius=rad; return *this; }

  /// Comparison
  bool operator==(const FXSphered& s) const { return center==s.center && radius==s.radius;}
  bool operator!=(const FXSphered& s) const { return center!=s.center || radius!=s.radius;}

  /// Diameter of sphere
  FXdouble diameter() const { return radius*2.0; }

  /// Test if empty
  bool empty() const { return radius<0.0; }

  /// Test if sphere contains point x,y,z
  bool contains(FXdouble x,FXdouble y,FXdouble z) const;

  /// Test if sphere contains point p
  bool contains(const FXVec3d& p) const;

  /// Test if sphere contains another box
  bool contains(const FXRanged& box) const;

  /// Test if sphere contains another sphere
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

  /// Intersect sphere with normalized plane ax+by+cz+w; returns -1,0,+1
  FXint intersect(const FXVec4d& plane) const;

  /// Intersect sphere with ray u-v
  bool intersect(const FXVec3d& u,const FXVec3d& v) const;

  /// Test if box overlaps with sphere
  friend FXAPI bool overlap(const FXRanged& a,const FXSphered& b);

  /// Test if sphere overlaps with box
  friend FXAPI bool overlap(const FXSphered& a,const FXRanged& b);

  /// Test if spheres overlap
  friend FXAPI bool overlap(const FXSphered& a,const FXSphered& b);

  /// Save object to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXSphered& sphere);

  /// Load object from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXSphered& sphere);
  };


extern FXAPI bool overlap(const FXRanged& a,const FXSphered& b);
extern FXAPI bool overlap(const FXSphered& a,const FXRanged& b);
extern FXAPI bool overlap(const FXSphered& a,const FXSphered& b);

extern FXAPI FXStream& operator<<(FXStream& store,const FXSphered& sphere);
extern FXAPI FXStream& operator>>(FXStream& store,FXSphered& sphere);

}

#endif
