/********************************************************************************
*                                                                               *
*       D o u b l e - P r e c i s i o n   2 - E l e m e n t   V e c t o r       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1994,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXVec2d.h 2346 2006-02-14 03:26:11Z lyle $                           *
********************************************************************************/
#ifndef FXVEC2D_H
#define FXVEC2D_H


namespace FX {


class FXMat3d;


/// Double-precision 2-element vector
class FXAPI FXVec2d {
public:
  FXdouble x;
  FXdouble y;
public:

  /// Default constructor
  FXVec2d(){}

  /// Initialize from another vector
  FXVec2d(const FXVec2d& v){x=v.x;y=v.y;}

  /// Initialize from array of floats
  FXVec2d(const FXdouble v[]){x=v[0];y=v[1];}

  /// Initialize from components
  FXVec2d(FXdouble xx,FXdouble yy){x=xx;y=yy;}

  /// Return a non-const reference to the ith element
  FXdouble& operator[](FXint i){return (&x)[i];}

  /// Return a const reference to the ith element
  const FXdouble& operator[](FXint i) const {return (&x)[i];}

  /// Assignment
  FXVec2d& operator=(const FXVec2d& v){x=v.x;y=v.y;return *this;}

  /// Assignment from array of floats
  FXVec2d& operator=(const FXdouble v[]){x=v[0];y=v[1];return *this;}

  /// Set value from another vector
  FXVec2d& set(const FXVec2d& v){x=v.x;y=v.y;return *this;}

  /// Set value from array of floats
  FXVec2d& set(const FXdouble v[]){x=v[0];y=v[1];return *this;}

  /// Set value from components
  FXVec2d& set(FXdouble xx,FXdouble yy){x=xx;y=yy;return *this;}

  /// Assigning operators
  FXVec2d& operator*=(FXdouble n){x*=n;y*=n;return *this;}
  FXVec2d& operator/=(FXdouble n){x/=n;y/=n;return *this;}
  FXVec2d& operator+=(const FXVec2d& v){x+=v.x;y+=v.y;return *this;}
  FXVec2d& operator-=(const FXVec2d& v){x-=v.x;y-=v.y;return *this;}

  /// Conversions
  operator FXdouble*(){return &x;}
  operator const FXdouble*() const {return &x;}

  /// Unary
  FXVec2d operator+() const { return *this; }
  FXVec2d operator-() const { return FXVec2d(-x,-y); }

  /// Vector and vector
  FXVec2d operator+(const FXVec2d& v) const { return FXVec2d(x+v.x,y+v.y); }
  FXVec2d operator-(const FXVec2d& v) const { return FXVec2d(x-v.x,y-v.y); }

  /// Vector and matrix
  FXVec2d operator*(const FXMat3d& m) const;

  /// Scaling
  friend inline FXVec2d operator*(const FXVec2d& a,FXdouble n);
  friend inline FXVec2d operator*(FXdouble n,const FXVec2d& a);
  friend inline FXVec2d operator/(const FXVec2d& a,FXdouble n);
  friend inline FXVec2d operator/(FXdouble n,const FXVec2d& a);

  /// Dot product
  FXdouble operator*(const FXVec2d& v) const { return x*v.x+y*v.y; }

  /// Test if zero
  bool operator!() const { return x==0.0 && y==0.0;}

  /// Equality tests
  bool operator==(const FXVec2d& v) const { return x==v.x && y==v.y; }
  bool operator!=(const FXVec2d& v) const { return x!=v.x || y!=v.y; }

  friend inline bool operator==(const FXVec2d& a,FXdouble n);
  friend inline bool operator!=(const FXVec2d& a,FXdouble n);
  friend inline bool operator==(FXdouble n,const FXVec2d& a);
  friend inline bool operator!=(FXdouble n,const FXVec2d& a);

  /// Inequality tests
  bool operator<(const FXVec2d& v) const { return x<v.x && y<v.y; }
  bool operator<=(const FXVec2d& v) const { return x<=v.x && y<=v.y; }
  bool operator>(const FXVec2d& v) const { return x>v.x && y>v.y; }
  bool operator>=(const FXVec2d& v) const { return x>=v.x && y>=v.y; }

  friend inline bool operator<(const FXVec2d& a,FXdouble n);
  friend inline bool operator<=(const FXVec2d& a,FXdouble n);
  friend inline bool operator>(const FXVec2d& a,FXdouble n);
  friend inline bool operator>=(const FXVec2d& a,FXdouble n);

  friend inline bool operator<(FXdouble n,const FXVec2d& a);
  friend inline bool operator<=(FXdouble n,const FXVec2d& a);
  friend inline bool operator>(FXdouble n,const FXVec2d& a);
  friend inline bool operator>=(FXdouble n,const FXVec2d& a);

  /// Length and square of length
  FXdouble length2() const { return x*x+y*y; }
  FXdouble length() const { return sqrt(length2()); }

  /// Clamp values of vector between limits
  FXVec2d& clamp(FXdouble lo,FXdouble hi){x=FXCLAMP(lo,x,hi);y=FXCLAMP(lo,y,hi);return *this;}

  /// Lowest or highest components
  friend inline FXVec2d lo(const FXVec2d& a,const FXVec2d& b);
  friend inline FXVec2d hi(const FXVec2d& a,const FXVec2d& b);

  /// Normalize vector
  friend FXAPI FXVec2d normalize(const FXVec2d& v);

  /// Save vector to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXVec2d& v);

  /// Load vector from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXVec2d& v);
  };


inline FXVec2d operator*(const FXVec2d& a,FXdouble n){return FXVec2d(a.x*n,a.y*n);}
inline FXVec2d operator*(FXdouble n,const FXVec2d& a){return FXVec2d(n*a.x,n*a.y);}
inline FXVec2d operator/(const FXVec2d& a,FXdouble n){return FXVec2d(a.x/n,a.y/n);}
inline FXVec2d operator/(FXdouble n,const FXVec2d& a){return FXVec2d(n/a.x,n/a.y);}

inline bool operator==(const FXVec2d& a,FXdouble n){return a.x==n && a.y==n;}
inline bool operator!=(const FXVec2d& a,FXdouble n){return a.x!=n || a.y!=n;}
inline bool operator==(FXdouble n,const FXVec2d& a){return n==a.x && n==a.y;}
inline bool operator!=(FXdouble n,const FXVec2d& a){return n!=a.x || n!=a.y;}

inline bool operator<(const FXVec2d& a,FXdouble n){return a.x<n && a.y<n;}
inline bool operator<=(const FXVec2d& a,FXdouble n){return a.x<=n && a.y<=n;}
inline bool operator>(const FXVec2d& a,FXdouble n){return a.x>n && a.y>n;}
inline bool operator>=(const FXVec2d& a,FXdouble n){return a.x>=n && a.y>=n;}

inline bool operator<(FXdouble n,const FXVec2d& a){return n<a.x && n<a.y;}
inline bool operator<=(FXdouble n,const FXVec2d& a){return n<=a.x && n<=a.y;}
inline bool operator>(FXdouble n,const FXVec2d& a){return n>a.x && n>a.y;}
inline bool operator>=(FXdouble n,const FXVec2d& a){return n>=a.x && n>=a.y;}

inline FXVec2d lo(const FXVec2d& a,const FXVec2d& b){return FXVec2d(FXMIN(a.x,b.x),FXMIN(a.y,b.y));}
inline FXVec2d hi(const FXVec2d& a,const FXVec2d& b){return FXVec2d(FXMAX(a.x,b.x),FXMAX(a.y,b.y));}

extern FXAPI FXVec2d normalize(const FXVec2d& v);

extern FXAPI FXStream& operator<<(FXStream& store,const FXVec2d& v);
extern FXAPI FXStream& operator>>(FXStream& store,FXVec2d& v);

}

#endif
