/********************************************************************************
*                                                                               *
*       S i n g l e - P r e c i s i o n   4 - E l e m e n t   V e c t o r       *
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
* $Id: FXVec4f.h 2346 2006-02-14 03:26:11Z lyle $                           *
********************************************************************************/
#ifndef FXVEC4F_H
#define FXVEC4F_H


namespace FX {


class FXMat4f;


/// Single-precision 4-element vector
class FXAPI FXVec4f {
public:
  FXfloat x;
  FXfloat y;
  FXfloat z;
  FXfloat w;
public:

  /// Default constructor
  FXVec4f(){}

  /// Initialize from another vector
  FXVec4f(const FXVec4f& v){x=v.x;y=v.y;z=v.z;w=v.w;}

  /// Construct with 3-vector and optional scalar
  FXVec4f(const FXVec3f& v,FXfloat ww=1.0f){x=v.x;y=v.y;z=v.z;w=ww;}

  /// Construct from array of floats
  FXVec4f(const FXfloat v[]){x=v[0];y=v[1];z=v[2];w=v[3];}

  /// Construct from components
  FXVec4f(FXfloat xx,FXfloat yy,FXfloat zz,FXfloat ww=1.0f){x=xx;y=yy;z=zz;w=ww;}

  /// Construct from color
  FXVec4f(FXColor color);

  /// Return a non-const reference to the ith element
  FXfloat& operator[](FXint i){return (&x)[i];}

  /// Return a const reference to the ith element
  const FXfloat& operator[](FXint i) const {return (&x)[i];}

  /// Assign color
  FXVec4f& operator=(FXColor color);

  /// Assignment
  FXVec4f& operator=(const FXVec3f& v){x=v.x;y=v.y;z=v.z;w=1.0f;return *this;}
  FXVec4f& operator=(const FXVec4f& v){x=v.x;y=v.y;z=v.z;w=v.w;return *this;}

  /// Assignment from array of floats
  FXVec4f& operator=(const FXfloat v[]){x=v[0];y=v[1];z=v[2];w=v[3];return *this;}

  /// Set value from another vector
  FXVec4f& set(const FXVec4f& v){x=v.x;y=v.y;z=v.z;w=v.w;return *this;}

  /// Set value from array of floats
  FXVec4f& set(const FXfloat v[]){x=v[0];y=v[1];z=v[2];w=v[3];return *this;}

  /// Set value from components
  FXVec4f& set(FXfloat xx,FXfloat yy,FXfloat zz,FXfloat ww){x=xx;y=yy;z=zz;w=ww;return *this;}

  /// Assigning operators
  FXVec4f& operator*=(FXfloat n){x*=n;y*=n;z*=n;w*=n;return *this;}
  FXVec4f& operator/=(FXfloat n){x/=n;y/=n;z/=n;w/=n;return *this;}
  FXVec4f& operator+=(const FXVec4f& v){x+=v.x;y+=v.y;z+=v.z;w+=v.w;return *this;}
  FXVec4f& operator-=(const FXVec4f& v){x-=v.x;y-=v.y;z-=v.z;w-=v.w;return *this;}

  /// Conversion
  operator FXfloat*(){return &x;}
  operator const FXfloat*() const {return &x;}
  operator FXVec3f&(){return *reinterpret_cast<FXVec3f*>(this);}
  operator const FXVec3f&() const {return *reinterpret_cast<const FXVec3f*>(this);}

  /// Convert to color
  operator FXColor() const;

  /// Unary
  FXVec4f operator+() const { return *this; }
  FXVec4f operator-() const { return FXVec4f(-x,-y,-z,-w); }

  /// Vector and vector
  FXVec4f operator+(const FXVec4f& v) const { return FXVec4f(x+v.x,y+v.y,z+v.z,w+v.w); }
  FXVec4f operator-(const FXVec4f& v) const { return FXVec4f(x-v.x,y-v.y,z-v.z,w-v.w); }

  /// Vector and matrix
  FXVec4f operator*(const FXMat4f& m) const;

  /// Scaling
  friend inline FXVec4f operator*(const FXVec4f& a,FXfloat n);
  friend inline FXVec4f operator*(FXfloat n,const FXVec4f& a);
  friend inline FXVec4f operator/(const FXVec4f& a,FXfloat n);
  friend inline FXVec4f operator/(FXfloat n,const FXVec4f& a);

  /// Dot product
  FXfloat operator*(const FXVec4f& v) const { return x*v.x+y*v.y+z*v.z+w*v.w; }

  /// Test if zero
  bool operator!() const { return x==0.0f && y==0.0f && z==0.0f && w==0.0f; }

  /// Equality tests
  bool operator==(const FXVec4f& v) const {return x==v.x && y==v.y && z==v.z && w==v.w; }
  bool operator!=(const FXVec4f& v) const {return x!=v.x || y!=v.y || z!=v.z || w!=v.w; }

  friend inline bool operator==(const FXVec4f& a,FXfloat n);
  friend inline bool operator!=(const FXVec4f& a,FXfloat n);
  friend inline bool operator==(FXfloat n,const FXVec4f& a);
  friend inline bool operator!=(FXfloat n,const FXVec4f& a);

  /// Inequality tests
  bool operator<(const FXVec4f& v) const { return x<v.x && y<v.y && z<v.z && w<v.w; }
  bool operator<=(const FXVec4f& v) const { return x<=v.x && y<=v.y && z<=v.z && w<=v.w; }
  bool operator>(const FXVec4f& v) const { return x>v.x && y>v.y && z>v.z && w>v.w; }
  bool operator>=(const FXVec4f& v) const { return x>=v.x && y>=v.y && z>=v.z && w>=v.w; }

  friend inline bool operator<(const FXVec4f& a,FXfloat n);
  friend inline bool operator<=(const FXVec4f& a,FXfloat n);
  friend inline bool operator>(const FXVec4f& a,FXfloat n);
  friend inline bool operator>=(const FXVec4f& a,FXfloat n);

  friend inline bool operator<(FXfloat n,const FXVec4f& a);
  friend inline bool operator<=(FXfloat n,const FXVec4f& a);
  friend inline bool operator>(FXfloat n,const FXVec4f& a);
  friend inline bool operator>=(FXfloat n,const FXVec4f& a);

  /// Length and square of length
  FXfloat length2() const { return x*x+y*y+z*z+w*w; }
  FXfloat length() const { return sqrtf(length2()); }

  /// Clamp values of vector between limits
  FXVec4f& clamp(FXfloat lo,FXfloat hi){x=FXCLAMP(lo,x,hi);y=FXCLAMP(lo,y,hi);z=FXCLAMP(lo,z,hi);w=FXCLAMP(lo,w,hi);return *this;}

  /// Lowest or highest components
  friend inline FXVec4f lo(const FXVec4f& a,const FXVec4f& b);
  friend inline FXVec4f hi(const FXVec4f& a,const FXVec4f& b);

  /// Compute normalized plane equation ax+by+cz+d=0
  friend FXAPI FXVec4f plane(const FXVec4f& vec);
  friend FXAPI FXVec4f plane(const FXVec3f& vec,FXfloat dist);
  friend FXAPI FXVec4f plane(const FXVec3f& vec,const FXVec3f& p);
  friend FXAPI FXVec4f plane(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c);

  /// Signed distance normalized plane and point
  FXfloat distance(const FXVec3f& p) const;

  /// Return true if edge a-b crosses plane
  bool crosses(const FXVec3f& a,const FXVec3f& b) const;

  /// Normalize vector
  friend FXAPI FXVec4f normalize(const FXVec4f& v);

  /// Save to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXVec4f& v);

  /// Load from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXVec4f& v);
  };


inline FXVec4f operator*(const FXVec4f& a,FXfloat n){return FXVec4f(a.x*n,a.y*n,a.z*n,a.w*n);}
inline FXVec4f operator*(FXfloat n,const FXVec4f& a){return FXVec4f(n*a.x,n*a.y,n*a.z,n*a.w);}
inline FXVec4f operator/(const FXVec4f& a,FXfloat n){return FXVec4f(a.x/n,a.y/n,a.z/n,a.w/n);}
inline FXVec4f operator/(FXfloat n,const FXVec4f& a){return FXVec4f(n/a.x,n/a.y,n/a.z,n/a.w);}

inline bool operator==(const FXVec4f& a,FXfloat n){return a.x==n && a.y==n && a.z==n && a.w==n;}
inline bool operator!=(const FXVec4f& a,FXfloat n){return a.x!=n || a.y!=n || a.z!=n || a.w!=n;}
inline bool operator==(FXfloat n,const FXVec4f& a){return n==a.x && n==a.y && n==a.z && n==a.w;}
inline bool operator!=(FXfloat n,const FXVec4f& a){return n!=a.x || n!=a.y || n!=a.z || n!=a.w;}

inline bool operator<(const FXVec4f& a,FXfloat n){return a.x<n && a.y<n && a.z<n && a.w<n;}
inline bool operator<=(const FXVec4f& a,FXfloat n){return a.x<=n && a.y<=n && a.z<=n && a.w<=n;}
inline bool operator>(const FXVec4f& a,FXfloat n){return a.x>n && a.y>n && a.z>n && a.w>n;}
inline bool operator>=(const FXVec4f& a,FXfloat n){return a.x>=n && a.y>=n && a.z>=n && a.w>=n;}

inline bool operator<(FXfloat n,const FXVec4f& a){return n<a.x && n<a.y && n<a.z && n<a.w;}
inline bool operator<=(FXfloat n,const FXVec4f& a){return n<=a.x && n<=a.y && n<=a.z && n<=a.w;}
inline bool operator>(FXfloat n,const FXVec4f& a){return n>a.x && n>a.y && n>a.z && n>a.w;}
inline bool operator>=(FXfloat n,const FXVec4f& a){return n>=a.x && n>=a.y && n>=a.z && n>=a.w;}

inline FXVec4f lo(const FXVec4f& a,const FXVec4f& b){return FXVec4f(FXMIN(a.x,b.x),FXMIN(a.y,b.y),FXMIN(a.z,b.z),FXMIN(a.w,b.w));}
inline FXVec4f hi(const FXVec4f& a,const FXVec4f& b){return FXVec4f(FXMAX(a.x,b.x),FXMAX(a.y,b.y),FXMAX(a.z,b.z),FXMAX(a.w,b.w));}

extern FXAPI FXVec4f plane(const FXVec4f& vec);
extern FXAPI FXVec4f plane(const FXVec3f& vec,FXfloat dist);
extern FXAPI FXVec4f plane(const FXVec3f& vec,const FXVec3f& p);
extern FXAPI FXVec4f plane(const FXVec3f& a,const FXVec3f& b,const FXVec3f& c);

extern FXAPI FXVec4f normalize(const FXVec4f& v);

extern FXAPI FXStream& operator<<(FXStream& store,const FXVec4f& v);
extern FXAPI FXStream& operator>>(FXStream& store,FXVec4f& v);

}

#endif
