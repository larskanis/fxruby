/********************************************************************************
*                                                                               *
*                               S i z e    C l a s s                            *
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
* $Id: FXSize.h 2345 2006-02-14 03:07:05Z lyle $                            *
********************************************************************************/
#ifndef FXSIZE_H
#define FXSIZE_H


namespace FX {


/// Size
class FXAPI FXSize {
public:
  FXshort w;
  FXshort h;
public:

  /// Constructors
  FXSize(){ }
  FXSize(const FXSize& s):w(s.w),h(s.h){ }
  FXSize(FXshort ww,FXshort hh):w(ww),h(hh){ }

  /// Test if empty
  bool empty() const { return w<=0 || h<=0; }

  /// Test if zero
  bool operator!() const { return w==0 && h==0; }

  /// Equality
  bool operator==(const FXSize& s) const { return w==s.w && h==s.h; }
  bool operator!=(const FXSize& s) const { return w!=s.w || h!=s.h; }

  /// Grow by amount
  FXSize& grow(FXshort margin);
  FXSize& grow(FXshort hormargin,FXshort vermargin);
  FXSize& grow(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  /// Shrink by amount
  FXSize& shrink(FXshort margin);
  FXSize& shrink(FXshort hormargin,FXshort vermargin);
  FXSize& shrink(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  /// Assignment
  FXSize& operator=(const FXSize& s){ w=s.w; h=s.h; return *this; }

  /// Set value from another size
  FXSize& set(const FXSize& s){ w=s.w; h=s.h; return *this; }

  /// Set value from components
  FXSize& set(FXshort ww,FXshort hh){ w=ww; h=hh; return *this; }

  /// Assignment operators
  FXSize& operator+=(const FXSize& s){ w+=s.w; h+=s.h; return *this; }
  FXSize& operator-=(const FXSize& s){ w-=s.w; h-=s.h; return *this; }
  FXSize& operator*=(FXshort c){ w*=c; h*=c; return *this; }
  FXSize& operator/=(FXshort c){ w/=c; h/=c; return *this; }

  /// Negation
  FXSize operator-(){ return FXSize(-w,-h); }

  /// Addition operators
  FXSize operator+(const FXSize& s) const { return FXSize(w+s.w,h+s.h); }
  FXSize operator-(const FXSize& s) const { return FXSize(w-s.w,h-s.h); }

  /// Scale operators
  friend inline FXSize operator*(const FXSize& s,FXshort c);
  friend inline FXSize operator*(FXshort c,const FXSize& s);
  friend inline FXSize operator/(const FXSize& s,FXshort c);
  friend inline FXSize operator/(FXshort c,const FXSize& s);

  /// Save object to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXSize& s);

  /// Load object from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXSize& s);
  };

inline FXSize operator*(const FXSize& s,FXshort c){ return FXSize(s.w*c,s.h*c); }
inline FXSize operator*(FXshort c,const FXSize& s){ return FXSize(c*s.w,c*s.h); }
inline FXSize operator/(const FXSize& s,FXshort c){ return FXSize(s.w/c,s.h/c); }
inline FXSize operator/(FXshort c,const FXSize& s){ return FXSize(c/s.w,c/s.h); }

extern FXAPI FXStream& operator<<(FXStream& store,const FXSize& s);
extern FXAPI FXStream& operator>>(FXStream& store,FXSize& s);

}

#endif
