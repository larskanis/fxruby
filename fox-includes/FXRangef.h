/********************************************************************************
*                                                                               *
*           S i n g l e - P r e c i s i o n    R a n g e    C l a s s           *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXRangef.h 2762 2007-11-19 17:07:23Z lyle $                          *
********************************************************************************/
#ifndef FXRANGEF_H
#define FXRANGEF_H


namespace FX {


class FXSpheref;


/// Bounds
class FXAPI FXRangef {
public:
  FXVec3f lower;
  FXVec3f upper;
public:

  /// Default constructor
  FXRangef(){}

  /// Initialize with another range
  FXRangef(const FXRangef& bounds):lower(bounds.lower),upper(bounds.upper){}

  /// Initialize with a single point
  FXRangef(const FXVec3f& p):lower(p),upper(p){}

  /// Initialize with corner points
  FXRangef(const FXVec3f& l,const FXVec3f& h):lower(l),upper(h){}

  /// Initialize with a single point
  FXRangef(FXfloat x,FXfloat y,FXfloat z):lower(x,y,z),upper(x,y,z){}

  /// Initialize with explicit values
  FXRangef(FXfloat xl,FXfloat xh,FXfloat yl,FXfloat yh,FXfloat zl,FXfloat zh):lower(xl,yl,zl),upper(xh,yh,zh){}

  /// Initialize box to fully contain the given bounding sphere
  FXRangef(const FXSpheref& sphere);

  /// Assignment
  FXRangef& operator=(const FXRangef& bounds){ lower=bounds.lower; upper=bounds.upper; return *this; }

  /// Set value from another range
  FXRangef& set(const FXRangef& bounds){ lower=bounds.lower; upper=bounds.upper; return *this; }

  /// Set value from single point
  FXRangef& set(const FXVec3f& p){ lower=upper=p; return *this; }

  /// Set value from corner points
  FXRangef& set(const FXVec3f& l,const FXVec3f& h){ lower=l; upper=h; return *this; }

  /// Set value from single point
  FXRangef& set(FXfloat x,FXfloat y,FXfloat z){ lower.x=upper.x=x; lower.y=upper.y=y; lower.z=upper.z=z; return *this; }

  /// Set value from explicit values
  FXRangef& set(FXfloat xl,FXfloat xh,FXfloat yl,FXfloat yh,FXfloat zl,FXfloat zh){ lower.set(xl,yl,zl); upper.set(xh,yh,zh); return *this; }

  /// Indexing with 0..1
  FXVec3f& operator[](FXint i){ return (&lower)[i]; }

  /// Indexing with 0..1
  const FXVec3f& operator[](FXint i) const { return (&lower)[i]; }

  /// Comparison
  FXbool operator==(const FXRangef& r) const { return lower==r.lower && upper==r.upper; }
  FXbool operator!=(const FXRangef& r) const { return lower!=r.lower || upper!=r.upper; }

  /// Width of box
  FXfloat width() const { return upper.x-lower.x; }

  /// Height of box
  FXfloat height() const { return upper.y-lower.y; }

  /// Depth of box
  FXfloat depth() const { return upper.z-lower.z; }

  /// Longest side
  FXfloat longest() const;

  /// shortest side
  FXfloat shortest() const;

  /// Length of diagonal
  FXfloat diameter() const;

  /// Get radius of box
  FXfloat radius() const;

  /// Compute diagonal
  FXVec3f diagonal() const;

  /// Get center of box
  FXVec3f center() const;

  /// Test if empty
  FXbool empty() const;

  /// Test if box contains point x,y,z
  FXbool contains(FXfloat x,FXfloat y,FXfloat z) const;

  /// Test if box contains point p
  FXbool contains(const FXVec3f& p) const;

  /// Test if box properly contains another box
  FXbool contains(const FXRangef& bounds) const;

  /// Test if box properly contains sphere
  FXbool contains(const FXSpheref& sphere) const;

  /// Include point
  FXRangef& include(FXfloat x,FXfloat y,FXfloat z);

  /// Include point
  FXRangef& include(const FXVec3f& v);

  /// Include given range into box
  FXRangef& include(const FXRangef& box);

  /// Include given sphere into this box
  FXRangef& include(const FXSpheref& sphere);

  /// Intersect box with normalized plane ax+by+cz+w; returns -1,0,+1
  FXint intersect(const FXVec4f& plane) const;

  /// Intersect box with ray u-v
  FXbool intersect(const FXVec3f& u,const FXVec3f& v);

  /// Test if boxes a and b overlap
  friend FXAPI FXbool overlap(const FXRangef& a,const FXRangef& b);

  /// Get corner number 0..7
  FXVec3f corner(FXint c) const { return FXVec3f((&lower)[c&1].x,(&lower)[(c>>1)&1].y,(&lower)[c>>2].z); }

  /// Union of two boxes
  friend FXAPI FXRangef unite(const FXRangef& a,const FXRangef& b);

  /// Intersection of two boxes
  friend FXAPI FXRangef intersect(const FXRangef& a,const FXRangef& b);

  /// Save object to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXRangef& bounds);

  /// Load object from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXRangef& bounds);
  };


extern FXAPI FXbool overlap(const FXRangef& a,const FXRangef& b);

extern FXAPI FXRangef unite(const FXRangef& a,const FXRangef& b);
extern FXAPI FXRangef intersect(const FXRangef& a,const FXRangef& b);

extern FXAPI FXStream& operator<<(FXStream& store,const FXRangef& bounds);
extern FXAPI FXStream& operator>>(FXStream& store,FXRangef& bounds);

}

#endif

