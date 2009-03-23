/********************************************************************************
*                                                                               *
*          S i n g l e - P r e c i s i o n    E x t e n t    C l a s s          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXExtentf.h,v 1.18 2009/01/26 09:40:22 fox Exp $                         *
********************************************************************************/
#ifndef FXEXTENTF_H
#define FXEXTENTF_H


namespace FX {


/// Extent
class FXAPI FXExtentf {
public:
  FXVec2f lower;
  FXVec2f upper;
public:

  /// Default constructor; value is not initialized
  FXExtentf(){}

  /// Copy constructor
  FXExtentf(const FXExtentf& ext):lower(ext.lower),upper(ext.upper){}

  /// Initialize with a single point
  FXExtentf(const FXVec2f& p):lower(p),upper(p){}

  /// Initialize from corner points
  FXExtentf(const FXVec2f& lo,const FXVec2f& hi):lower(lo),upper(hi){}

  /// Initialize with a single point
  FXExtentf(FXfloat x,FXfloat y):lower(x,y),upper(x,y){}

  /// Initialize with explicit values
  FXExtentf(FXfloat xl,FXfloat xh,FXfloat yl,FXfloat yh):lower(xl,yl),upper(xh,yh){}

  /// Assignment
  FXExtentf& operator=(const FXExtentf& ext){ lower=ext.lower; upper=ext.upper; return *this; }

  /// Set value from another range
  FXExtentf& set(const FXExtentf& ext){ lower=ext.lower; upper=ext.upper; return *this; }

  /// Set value from single point
  FXExtentf& set(const FXVec2f& p){ lower=upper=p; return *this; }

  /// Set value from corner points
  FXExtentf& set(const FXVec2f& lo,const FXVec2f& hi){ lower=lo; upper=hi; return *this; }

  /// Set value from single point
  FXExtentf& set(FXfloat x,FXfloat y){ lower.x=upper.x=x; lower.y=upper.y=y; return *this; }

  /// Set value from explicit values
  FXExtentf& set(FXfloat xl,FXfloat xh,FXfloat yl,FXfloat yh){ lower.set(xl,yl); upper.set(xh,yh); return *this; }

  /// Indexing with 0..1
  FXVec2f& operator[](FXint i){ return (&lower)[i]; }

  /// Indexing with 0..1
  const FXVec2f& operator[](FXint i) const { return (&lower)[i]; }

  /// Comparison
  FXbool operator==(const FXExtentf& ext) const { return lower==ext.lower && upper==ext.upper;}
  FXbool operator!=(const FXExtentf& ext) const { return lower!=ext.lower || upper!=ext.upper;}

  /// Width of box
  FXfloat width() const { return upper.x-lower.x; }

  /// Height of box
  FXfloat height() const { return upper.y-lower.y; }

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
  FXbool empty() const;

  /// Test if box contains point x,y
  FXbool contains(FXfloat x,FXfloat y) const;

  /// Test if box contains point p
  FXbool contains(const FXVec2f& p) const;

  /// Test if box properly contains another box
  FXbool contains(const FXExtentf& ext) const;

  /// Include point
  FXExtentf& include(FXfloat x,FXfloat y);

  /// Include point
  FXExtentf& include(const FXVec2f& v);

  /// Include given range into extent
  FXExtentf& include(const FXExtentf& ext);

  /// Test if bounds overlap
  friend FXAPI FXbool overlap(const FXExtentf& a,const FXExtentf& b);

  /// Get corner number 0..3
  FXVec2f corner(FXint c) const { return FXVec2f((&lower)[c&1].x, (&lower)[(c>>1)&1].y); }

  /// Union of two boxes
  friend FXAPI FXExtentf unite(const FXExtentf& a,const FXExtentf& b);

  /// Intersection of two boxes
  friend FXAPI FXExtentf intersect(const FXExtentf& a,const FXExtentf& b);

  /// Save object to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXExtentf& ext);

  /// Load object from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXExtentf& ext);
  };


extern FXAPI FXbool overlap(const FXExtentf& a,const FXExtentf& b);

extern FXAPI FXExtentf unite(const FXExtentf& a,const FXExtentf& b);
extern FXAPI FXExtentf intersect(const FXExtentf& a,const FXExtentf& b);

extern FXAPI FXStream& operator<<(FXStream& store,const FXExtentf& ext);
extern FXAPI FXStream& operator>>(FXStream& store,FXExtentf& ext);

}

#endif

