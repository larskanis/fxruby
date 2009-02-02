/********************************************************************************
*                                                                               *
*       S i n g l e - P r e c i s i o n   2 - E l e m e n t   V e c t o r       *
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
* $Id: FXVec2f.h 2346 2006-02-14 03:26:11Z lyle $                           *
********************************************************************************/
#ifndef FXVEC2F_H
#define FXVEC2F_H


namespace FX {


class FXMat3f;


/// Single-precision 2-element vector
class FXAPI FXVec2f {
public:
  FXfloat x;
  FXfloat y;
public:

  /// Default constructor
  FXVec2f(){}

  /// Initialize from another vector
  FXVec2f(const FXVec2f& v){x=v.x;y=v.y;}

  /// Initialize from array of floats
  FXVec2f(const FXfloat v[]){x=v[0];y=v[1];}

  /// Initialize from components
  FXVec2f(FXfloat xx,FXfloat yy){x=xx;y=yy;}

  /// Return a non-const reference to the ith element
  FXfloat& operator[](FXint i){return (&x)[i];}

  /// Return a const reference to the ith element
  const FXfloat& operator[](FXint i) const {return (&x)[i];}

  /// Assignment
  FXVec2f& operator=(const FXVec2f& v){x=v.x;y=v.y;return *this;}

  /// Assignment from array of floats
  FXVec2f& operator=(const FXfloat v[]){x=v[0];y=v[1];return *this;}

  /// Set value from another vector
  FXVec2f& set(const FXVec2f& v){x=v.x;y=v.y;return *this;}

  /// Set value from array of floats
  FXVec2f& set(const FXfloat v[]){x=v[0];y=v[1];return *this;}

  /// Set value from components
  FXVec2f& set(FXfloat xx,FXfloat yy){x=xx;y=yy;return *this;}

  /// Assigning operators
  FXVec2f& operator*=(FXfloat n){x*=n;y*=n;return *this;}
  FXVec2f& operator/=(FXfloat n){x/=n;y/=n;return *this;}
  FXVec2f& operator+=(const FXVec2f& v){x+=v.x;y+=v.y;return *this;}
  FXVec2f& operator-=(const FXVec2f& v){x-=v.x;y-=v.y;return *this;}

  /// Conversions
  operator FXfloat*(){return &x;}
  operator const FXfloat*() const {return &x;}

  /// Unary
  FXVec2f operator+() const { return *this; }
  FXVec2f operator-() const { return FXVec2f(-x,-y); }

  /// Vector and vector
  FXVec2f operator+(const FXVec2f& v) const { return FXVec2f(x+v.x,y+v.y); }
  FXVec2f operator-(const FXVec2f& v) const { return FXVec2f(x-v.x,y-v.y); }

  /// Vector and matrix
  FXVec2f operator*(const FXMat3f& m) const;

  /// Scaling
  friend inline FXVec2f operator*(const FXVec2f& a,FXfloat n);
  friend inline FXVec2f operator*(FXfloat n,const FXVec2f& a);
  friend inline FXVec2f operator/(const FXVec2f& a,FXfloat n);
  friend inline FXVec2f operator/(FXfloat n,const FXVec2f& a);

  /// Dot product
  FXfloat operator*(const FXVec2f& v) const { return x*v.x+y*v.y; }

  /// Test if zero
  bool operator!() const { return x==0.0f && y==0.0f; }

  /// Equality tests
  bool operator==(const FXVec2f& v) const { return x==v.x && y==v.y; }
  bool operator!=(const FXVec2f& v) const { return x!=v.x || y!=v.y; }

  friend inline bool operator==(const FXVec2f& a,FXfloat n);
  friend inline bool operator!=(const FXVec2f& a,FXfloat n);
  friend inline bool operator==(FXfloat n,const FXVec2f& a);
  friend inline bool operator!=(FXfloat n,const FXVec2f& a);

  /// Inequality tests
  bool operator<(const FXVec2f& v) const { return x<v.x && y<v.y; }
  bool operator<=(const FXVec2f& v) const { return x<=v.x && y<=v.y; }
  bool operator>(const FXVec2f& v) const { return x>v.x && y>v.y; }
  bool operator>=(const FXVec2f& v) const { return x>=v.x && y>=v.y; }

  friend inline bool operator<(const FXVec2f& a,FXfloat n);
  friend inline bool operator<=(const FXVec2f& a,FXfloat n);
  friend inline bool operator>(const FXVec2f& a,FXfloat n);
  friend inline bool operator>=(const FXVec2f& a,FXfloat n);

  friend inline bool operator<(FXfloat n,const FXVec2f& a);
  friend inline bool operator<=(FXfloat n,const FXVec2f& a);
  friend inline bool operator>(FXfloat n,const FXVec2f& a);
  friend inline bool operator>=(FXfloat n,const FXVec2f& a);

  /// Length and square of length
  FXfloat length2() const { return x*x+y*y; }
  FXfloat length() const { return sqrtf(length2()); }

  /// Clamp values of vector between limits
  FXVec2f& clamp(FXfloat lo,FXfloat hi){x=FXCLAMP(lo,x,hi);y=FXCLAMP(lo,y,hi);return *this;}

  /// Lowest or highest components
  friend inline FXVec2f lo(const FXVec2f& a,const FXVec2f& b);
  friend inline FXVec2f hi(const FXVec2f& a,const FXVec2f& b);

  /// Normalize vector
  friend FXAPI FXVec2f normalize(const FXVec2f& v);

  /// Save vector to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXVec2f& v);

  /// Load vector from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXVec2f& v);
  };


inline FXVec2f operator*(const FXVec2f& a,FXfloat n){return FXVec2f(a.x*n,a.y*n);}
inline FXVec2f operator*(FXfloat n,const FXVec2f& a){return FXVec2f(n*a.x,n*a.y);}
inline FXVec2f operator/(const FXVec2f& a,FXfloat n){return FXVec2f(a.x/n,a.y/n);}
inline FXVec2f operator/(FXfloat n,const FXVec2f& a){return FXVec2f(n/a.x,n/a.y);}

inline bool operator==(const FXVec2f& a,FXfloat n){return a.x==n && a.y==n;}
inline bool operator!=(const FXVec2f& a,FXfloat n){return a.x!=n || a.y!=n;}
inline bool operator==(FXfloat n,const FXVec2f& a){return n==a.x && n==a.y;}
inline bool operator!=(FXfloat n,const FXVec2f& a){return n!=a.x || n!=a.y;}

inline bool operator<(const FXVec2f& a,FXfloat n){return a.x<n && a.y<n;}
inline bool operator<=(const FXVec2f& a,FXfloat n){return a.x<=n && a.y<=n;}
inline bool operator>(const FXVec2f& a,FXfloat n){return a.x>n && a.y>n;}
inline bool operator>=(const FXVec2f& a,FXfloat n){return a.x>=n && a.y>=n;}

inline bool operator<(FXfloat n,const FXVec2f& a){return n<a.x && n<a.y;}
inline bool operator<=(FXfloat n,const FXVec2f& a){return n<=a.x && n<=a.y;}
inline bool operator>(FXfloat n,const FXVec2f& a){return n>a.x && n>a.y;}
inline bool operator>=(FXfloat n,const FXVec2f& a){return n>=a.x && n>=a.y;}

inline FXVec2f lo(const FXVec2f& a,const FXVec2f& b){return FXVec2f(FXMIN(a.x,b.x),FXMIN(a.y,b.y));}
inline FXVec2f hi(const FXVec2f& a,const FXVec2f& b){return FXVec2f(FXMAX(a.x,b.x),FXMAX(a.y,b.y));}

extern FXAPI FXVec2f normalize(const FXVec2f& v);

extern FXAPI FXStream& operator<<(FXStream& store,const FXVec2f& v);
extern FXAPI FXStream& operator>>(FXStream& store,FXVec2f& v);

}

#endif
