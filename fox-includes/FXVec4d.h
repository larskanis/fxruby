/********************************************************************************
*                                                                               *
*       D o u b l e - P r e c i s i o n   4 - E l e m e n t   V e c t o r       *
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
* $Id: FXVec4d.h 2346 2006-02-14 03:26:11Z lyle $                           *
********************************************************************************/
#ifndef FXVEC4D_H
#define FXVEC4D_H


namespace FX {


class FXMat4d;


/// Double-precision 4-element vector
class FXAPI FXVec4d {
public:
  FXdouble x;
  FXdouble y;
  FXdouble z;
  FXdouble w;
public:

  /// Default constructor
  FXVec4d(){}

  /// Initialize from another vector
  FXVec4d(const FXVec4d& v){x=v.x;y=v.y;z=v.z;w=v.w;}

  /// Construct with 3-vector and optional scalar
  FXVec4d(const FXVec3d& v,FXdouble ww=1.0){x=v.x;y=v.y;z=v.z;w=ww;}

  /// Initialize from array of doubles
  FXVec4d(const FXdouble v[]){x=v[0];y=v[1];z=v[2];w=v[3];}

  /// Initialize with components
  FXVec4d(FXdouble xx,FXdouble yy,FXdouble zz,FXdouble ww=1.0){x=xx;y=yy;z=zz;w=ww;}

  /// Initialize with color
  FXVec4d(FXColor color);

  /// Return a non-const reference to the ith element
  FXdouble& operator[](FXint i){return (&x)[i];}

  /// Return a const reference to the ith element
  const FXdouble& operator[](FXint i) const {return (&x)[i];}

  /// Assign color
  FXVec4d& operator=(FXColor color);

  /// Assignment
  FXVec4d& operator=(const FXVec3d& v){x=v.x;y=v.y;z=v.z;w=1.0;return *this;}
  FXVec4d& operator=(const FXVec4d& v){x=v.x;y=v.y;z=v.z;w=v.w;return *this;}

  /// Assignment from array of doubles
  FXVec4d& operator=(const FXdouble v[]){x=v[0];y=v[1];z=v[2];w=v[3];return *this;}

  /// Set value from another vector
  FXVec4d& set(const FXVec4d& v){x=v.x;y=v.y;z=v.z;w=v.w;return *this;}

  /// Set value from array of floats
  FXVec4d& set(const FXdouble v[]){x=v[0];y=v[1];z=v[2];w=v[3];return *this;}

  /// Set value from components
  FXVec4d& set(FXdouble xx,FXdouble yy,FXdouble zz,FXdouble ww){x=xx;y=yy;z=zz;w=ww;return *this;}

  /// Assigning operators
  FXVec4d& operator*=(FXdouble n){x*=n;y*=n;z*=n;w*=n;return *this;}
  FXVec4d& operator/=(FXdouble n){x/=n;y/=n;z/=n;w/=n;return *this;}
  FXVec4d& operator+=(const FXVec4d& v){x+=v.x;y+=v.y;z+=v.z;w+=v.w;return *this;}
  FXVec4d& operator-=(const FXVec4d& v){x-=v.x;y-=v.y;z-=v.z;w-=v.w;return *this;}

  /// Conversion
  operator FXdouble*(){return &x;}
  operator const FXdouble*() const {return &x;}
  operator FXVec3d&(){return *reinterpret_cast<FXVec3d*>(this);}
  operator const FXVec3d&() const {return *reinterpret_cast<const FXVec3d*>(this);}

  /// Convert to color
  operator FXColor() const;

  /// Unary
  FXVec4d operator+() const { return *this; }
  FXVec4d operator-() const { return FXVec4d(-x,-y,-z,-w); }

  /// Vector and vector
  FXVec4d operator+(const FXVec4d& v) const { return FXVec4d(x+v.x,y+v.y,z+v.z,w+v.w); }
  FXVec4d operator-(const FXVec4d& v) const { return FXVec4d(x-v.x,y-v.y,z-v.z,w-v.w); }

  /// Vector and matrix
  FXVec4d operator*(const FXMat4d& m) const;

  /// Scaling
  friend inline FXVec4d operator*(const FXVec4d& a,FXdouble n);
  friend inline FXVec4d operator*(FXdouble n,const FXVec4d& a);
  friend inline FXVec4d operator/(const FXVec4d& a,FXdouble n);
  friend inline FXVec4d operator/(FXdouble n,const FXVec4d& a);

  /// Dot product
  FXdouble operator*(const FXVec4d& v) const { return x*v.x+y*v.y+z*v.z+w*v.w; }

  /// Test if zero
  bool operator!() const {return x==0.0 && y==0.0 && z==0.0 && w==0.0; }

  /// Equality tests
  bool operator==(const FXVec4d& v) const { return x==v.x && y==v.y && z==v.z && w==v.w; }
  bool operator!=(const FXVec4d& v) const { return x!=v.x || y!=v.y || z!=v.z || w!=v.w; }

  friend inline bool operator==(const FXVec4d& a,FXdouble n);
  friend inline bool operator!=(const FXVec4d& a,FXdouble n);
  friend inline bool operator==(FXdouble n,const FXVec4d& a);
  friend inline bool operator!=(FXdouble n,const FXVec4d& a);

  /// Inequality tests
  bool operator<(const FXVec4d& v) const { return x<v.x && y<v.y && z<v.z && w<v.w; }
  bool operator<=(const FXVec4d& v) const { return x<=v.x && y<=v.y && z<=v.z && w<=v.w; }
  bool operator>(const FXVec4d& v) const { return x>v.x && y>v.y && z>v.z && w>v.w; }
  bool operator>=(const FXVec4d& v) const { return x>=v.x && y>=v.y && z>=v.z && w>=v.w; }

  friend inline bool operator<(const FXVec4d& a,FXdouble n);
  friend inline bool operator<=(const FXVec4d& a,FXdouble n);
  friend inline bool operator>(const FXVec4d& a,FXdouble n);
  friend inline bool operator>=(const FXVec4d& a,FXdouble n);

  friend inline bool operator<(FXdouble n,const FXVec4d& a);
  friend inline bool operator<=(FXdouble n,const FXVec4d& a);
  friend inline bool operator>(FXdouble n,const FXVec4d& a);
  friend inline bool operator>=(FXdouble n,const FXVec4d& a);

  /// Length and square of length
  FXdouble length2() const { return x*x+y*y+z*z+w*w; }
  FXdouble length() const { return sqrt(length2()); }

  /// Clamp values of vector between limits
  FXVec4d& clamp(FXdouble lo,FXdouble hi){x=FXCLAMP(lo,x,hi);y=FXCLAMP(lo,y,hi);z=FXCLAMP(lo,z,hi);w=FXCLAMP(lo,w,hi);return *this;}

  /// Lowest or highest components
  friend inline FXVec4d lo(const FXVec4d& a,const FXVec4d& b);
  friend inline FXVec4d hi(const FXVec4d& a,const FXVec4d& b);

  /// Compute normalized plane equation ax+by+cz+d=0
  friend FXAPI FXVec4d plane(const FXVec4d& vec);
  friend FXAPI FXVec4d plane(const FXVec3d& vec,FXdouble dist);
  friend FXAPI FXVec4d plane(const FXVec3d& vec,const FXVec3d& p);
  friend FXAPI FXVec4d plane(const FXVec3d& a,const FXVec3d& b,const FXVec3d& c);

  /// Signed distance normalized plane and point
  FXdouble distance(const FXVec3d& p) const;

  /// Return true if edge a-b crosses plane
  bool crosses(const FXVec3d& a,const FXVec3d& b) const;

  /// Normalize vector
  friend FXAPI FXVec4d normalize(const FXVec4d& v);

  /// Save to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXVec4d& v);

  /// Load from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXVec4d& v);
  };


inline FXVec4d operator*(const FXVec4d& a,FXdouble n){return FXVec4d(a.x*n,a.y*n,a.z*n,a.w*n);}
inline FXVec4d operator*(FXdouble n,const FXVec4d& a){return FXVec4d(n*a.x,n*a.y,n*a.z,n*a.w);}
inline FXVec4d operator/(const FXVec4d& a,FXdouble n){return FXVec4d(a.x/n,a.y/n,a.z/n,a.w/n);}
inline FXVec4d operator/(FXdouble n,const FXVec4d& a){return FXVec4d(n/a.x,n/a.y,n/a.z,n/a.w);}

inline bool operator==(const FXVec4d& a,FXdouble n){return a.x==n && a.y==n && a.z==n && a.w==n;}
inline bool operator!=(const FXVec4d& a,FXdouble n){return a.x!=n || a.y!=n || a.z!=n || a.w!=n;}
inline bool operator==(FXdouble n,const FXVec4d& a){return n==a.x && n==a.y && n==a.z && n==a.w;}
inline bool operator!=(FXdouble n,const FXVec4d& a){return n!=a.x || n!=a.y || n!=a.z || n!=a.w;}

inline bool operator<(const FXVec4d& a,FXdouble n){return a.x<n && a.y<n && a.z<n && a.w<n;}
inline bool operator<=(const FXVec4d& a,FXdouble n){return a.x<=n && a.y<=n && a.z<=n && a.w<=n;}
inline bool operator>(const FXVec4d& a,FXdouble n){return a.x>n && a.y>n && a.z>n && a.w>n;}
inline bool operator>=(const FXVec4d& a,FXdouble n){return a.x>=n && a.y>=n && a.z>=n && a.w>=n;}

inline bool operator<(FXdouble n,const FXVec4d& a){return n<a.x && n<a.y && n<a.z && n<a.w;}
inline bool operator<=(FXdouble n,const FXVec4d& a){return n<=a.x && n<=a.y && n<=a.z && n<=a.w;}
inline bool operator>(FXdouble n,const FXVec4d& a){return n>a.x && n>a.y && n>a.z && n>a.w;}
inline bool operator>=(FXdouble n,const FXVec4d& a){return n>=a.x && n>=a.y && n>=a.z && n>=a.w;}

inline FXVec4d lo(const FXVec4d& a,const FXVec4d& b){return FXVec4d(FXMIN(a.x,b.x),FXMIN(a.y,b.y),FXMIN(a.z,b.z),FXMIN(a.w,b.w));}
inline FXVec4d hi(const FXVec4d& a,const FXVec4d& b){return FXVec4d(FXMAX(a.x,b.x),FXMAX(a.y,b.y),FXMAX(a.z,b.z),FXMAX(a.w,b.w));}

extern FXAPI FXVec4d plane(const FXVec4d& vec);
extern FXAPI FXVec4d plane(const FXVec3d& vec,FXdouble dist);
extern FXAPI FXVec4d plane(const FXVec3d& vec,const FXVec3d& p);
extern FXAPI FXVec4d plane(const FXVec3d& a,const FXVec3d& b,const FXVec3d& c);

extern FXAPI FXVec4d normalize(const FXVec4d& v);

extern FXAPI FXStream& operator<<(FXStream& store,const FXVec4d& v);
extern FXAPI FXStream& operator>>(FXStream& store,FXVec4d& v);

}

#endif
