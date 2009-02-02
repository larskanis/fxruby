/********************************************************************************
*                                                                               *
*          D o u b l e - P r e c i s i o n    E x t e n t    C l a s s          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXExtentd.h 2335 2006-01-28 02:33:03Z lyle $                          *
********************************************************************************/
#ifndef FXEXTENTD_H
#define FXEXTENTD_H


namespace FX {


/// Extent
class FXExtentd {
public:
  FXVec2d lower;
  FXVec2d upper;
public:

  /// Default constructor
  FXExtentd(){}

  /// Copy constructor
  FXExtentd(const FXExtentd& ext):lower(ext.lower),upper(ext.upper){}

  /// Initialize from two vectors
  FXExtentd(const FXVec2d& lo,const FXVec2d& hi):lower(lo),upper(hi){}

  /// Initialize from six numbers
  FXExtentd(FXdouble xlo,FXdouble xhi,FXdouble ylo,FXdouble yhi):lower(xlo,ylo),upper(xhi,yhi){}

  /// Assignment
  FXExtentd& operator=(const FXExtentd& ext){ lower=ext.lower; upper=ext.upper; return *this; }

  /// Indexing with 0..1
  FXVec2d& operator[](FXint i){ return (&lower)[i]; }

  /// Indexing with 0..1
  const FXVec2d& operator[](FXint i) const { return (&lower)[i]; }

  /// Comparison
  bool operator==(const FXExtentd& ext) const { return lower==ext.lower && upper==ext.upper;}
  bool operator!=(const FXExtentd& ext) const { return lower!=ext.lower || upper!=ext.upper;}

  /// Width of box
  FXdouble width() const { return upper.x-lower.x; }

  /// Height of box
  FXdouble height() const { return upper.y-lower.y; }

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
  bool empty() const;

  /// Test if box contains point x,y
  bool contains(FXdouble x,FXdouble y) const;

  /// Test if box contains point p
  bool contains(const FXVec2d& p) const;

  /// Test if box properly contains another box
  bool contains(const FXExtentd& ext) const;

  /// Include point
  FXExtentd& include(FXdouble x,FXdouble y);

  /// Include point
  FXExtentd& include(const FXVec2d& v);

  /// Include given range into extent
  FXExtentd& include(const FXExtentd& ext);

  /// Test if bounds overlap
  friend FXAPI bool overlap(const FXExtentd& a,const FXExtentd& b);

  /// Get corner number 0..3
  FXVec2d corner(FXint c) const { return FXVec2d((&lower)[c&1].x, (&lower)[(c>>1)&1].y); }

  /// Union of two boxes
  friend FXAPI FXExtentd unite(const FXExtentd& a,const FXExtentd& b);

  /// Intersection of two boxes
  friend FXAPI FXExtentd intersect(const FXExtentd& a,const FXExtentd& b);

  /// Save object to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXExtentd& ext);

  /// Load object from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXExtentd& ext);
  };


extern FXAPI bool overlap(const FXExtentd& a,const FXExtentd& b);

extern FXAPI FXExtentd unite(const FXExtentd& a,const FXExtentd& b);
extern FXAPI FXExtentd intersect(const FXExtentd& a,const FXExtentd& b);

extern FXAPI FXStream& operator<<(FXStream& store,const FXExtentd& ext);
extern FXAPI FXStream& operator>>(FXStream& store,FXExtentd& ext);

}

#endif

