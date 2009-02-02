/********************************************************************************
*                                                                               *
*          D o u b l e - P r e c i s i o n    R a n g e    C l a s s            *
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
* $Id: FXRanged.h 2344 2006-02-12 21:19:36Z lyle $                          *
********************************************************************************/
#ifndef FXRANGED_H
#define FXRANGED_H


namespace FX {


class FXSphered;


/// Bounds
class FXAPI FXRanged {
public:
  FXVec3d lower;
  FXVec3d upper;
public:

  /// Default constructor
  FXRanged(){}

  /// Initialize from another range
  FXRanged(const FXRanged& bounds):lower(bounds.lower),upper(bounds.upper){}

  /// Initialize from two vectors
  FXRanged(const FXVec3d& lo,const FXVec3d& hi):lower(lo),upper(hi){}

  /// Initialize from six numbers
  FXRanged(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi,FXdouble zlo,FXdouble zhi):lower(xlo,ylo,zlo),upper(xhi,yhi,zhi){}

  /// Initialize box to fully contain the given bounding sphere
  FXRanged(const FXSphered& sphere);

  /// Assignment
  FXRanged& operator=(const FXRanged& bounds){ lower=bounds.lower; upper=bounds.upper; return *this; }

  /// Set value from another range
  FXRanged& set(const FXRanged& bounds){ lower=bounds.lower; upper=bounds.upper; return *this; }

  /// Set value from two vectors
  FXRanged& set(const FXVec3d& lo,const FXVec3d& hi){ lower=lo; upper=hi; return *this; }

  /// Set value from six numbers
  FXRanged& set(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi,FXdouble zlo,FXdouble zhi){ lower.set(xlo,ylo,zlo); upper.set(xhi,yhi,zhi); return *this; }

  /// Indexing with 0..1
  FXVec3d& operator[](FXint i){ return (&lower)[i]; }

  /// Indexing with 0..1
  const FXVec3d& operator[](FXint i) const { return (&lower)[i]; }

  /// Comparison
  bool operator==(const FXRanged& r) const { return lower==r.lower && upper==r.upper; }
  bool operator!=(const FXRanged& r) const { return lower!=r.lower || upper!=r.upper; }

  /// Width of box
  FXdouble width() const { return upper.x-lower.x; }

  /// Height of box
  FXdouble height() const { return upper.y-lower.y; }

  /// Depth of box
  FXdouble depth() const { return upper.z-lower.z; }

  /// Longest side
  FXdouble longest() const;

  /// shortest side
  FXdouble shortest() const;

  /// Length of diagonal
  FXdouble diameter() const;

  /// Get radius of box
  FXdouble radius() const;

  /// Compute diagonal
  FXVec3d diagonal() const;

  /// Get center of box
  FXVec3d center() const;

  /// Test if empty
  bool empty() const;

  /// Test if box contains point x,y,z
  bool contains(FXdouble x,FXdouble y,FXdouble z) const;

  /// Test if box contains point p
  bool contains(const FXVec3d& p) const;

  /// Test if box properly contains another box
  bool contains(const FXRanged& bounds) const;

  /// Test if box properly contains sphere
  bool contains(const FXSphered& sphere) const;

  /// Include point
  FXRanged& include(FXdouble x,FXdouble y,FXdouble z);

  /// Include point
  FXRanged& include(const FXVec3d& v);

  /// Include given range into box
  FXRanged& include(const FXRanged& box);

  /// Include given sphere into this box
  FXRanged& include(const FXSphered& sphere);

  /// Intersect box with normalized plane ax+by+cz+w; returns -1,0,+1
  FXint intersect(const FXVec4d &plane) const;

  /// Intersect box with ray u-v
  bool intersect(const FXVec3d& u,const FXVec3d& v);

  /// Test if bounds overlap
  friend FXAPI bool overlap(const FXRanged& a,const FXRanged& b);

  /// Get corner number 0..7
  FXVec3d corner(FXint c) const { return FXVec3d((&lower)[c&1].x, (&lower)[(c>>1)&1].y, (&lower)[c>>2].z); }

  /// Union of two boxes
  friend FXAPI FXRanged unite(const FXRanged& a,const FXRanged& b);

  /// Intersection of two boxes
  friend FXAPI FXRanged intersect(const FXRanged& a,const FXRanged& b);

  /// Save object to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXRanged& bounds);

  /// Load object from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXRanged& bounds);
  };


extern FXAPI bool overlap(const FXRanged& a,const FXRanged& b);

extern FXAPI FXRanged unite(const FXRanged& a,const FXRanged& b);
extern FXAPI FXRanged intersect(const FXRanged& a,const FXRanged& b);

extern FXAPI FXStream& operator<<(FXStream& store,const FXRanged& bounds);
extern FXAPI FXStream& operator>>(FXStream& store,FXRanged& bounds);

}

#endif

