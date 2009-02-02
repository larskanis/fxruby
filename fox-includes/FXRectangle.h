/********************************************************************************
*                                                                               *
*                          R e c t a n g l e    C l a s s                       *
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
* $Id: FXRectangle.h 2344 2006-02-12 21:19:36Z lyle $                       *
********************************************************************************/
#ifndef FXRECTANGLE_H
#define FXRECTANGLE_H


#ifndef FXPOINT_H
#include "FXPoint.h"
#endif


namespace FX {


/// Rectangle
class FXAPI FXRectangle {
public:
  FXshort x;
  FXshort y;
  FXshort w;
  FXshort h;
public:

  /// Constructors
  FXRectangle(){ }
  FXRectangle(FXshort xx,FXshort yy,FXshort ww,FXshort hh):x(xx),y(yy),w(ww),h(hh){ }
  FXRectangle(const FXPoint& p,const FXSize& s):x(p.x),y(p.y),w(s.w),h(s.h){ }
  FXRectangle(const FXPoint& topleft,const FXPoint& bottomright):x(topleft.x),y(topleft.y),w(bottomright.x-topleft.x+1),h(bottomright.y-topleft.y+1){ }

  /// Test if empty
  bool empty() const { return w<=0 || h<=0; }

  /// Test if zero
  bool operator!() const { return x==0 && y==0 && w==0 && h==0; }

  /// Equality
  bool operator==(const FXRectangle& r) const { return x==r.x && y==r.y && w==r.w && h==r.h; }
  bool operator!=(const FXRectangle& r) const { return x!=r.x || y!=r.y || w!=r.w || h!=r.h; }

  /// Point in rectangle
  bool contains(const FXPoint& p) const { return x<=p.x && y<=p.y && p.x<x+w && p.y<y+h; }
  bool contains(FXshort xx,FXshort yy) const { return x<=xx && y<=yy && xx<x+w && yy<y+h; }

  /// Rectangle properly contained in rectangle
  bool contains(const FXRectangle& r) const { return x<=r.x && y<=r.y && r.x+r.w<=x+w && r.y+r.h<=y+h; }

  /// Rectangles overlap
  friend inline bool overlap(const FXRectangle& a,const FXRectangle& b);

  /// Return moved rectangle
  FXRectangle& move(const FXPoint& p){ x+=p.x; y+=p.y; return *this; }
  FXRectangle& move(FXshort dx,FXshort dy){ x+=dx; y+=dy; return *this; }

  /// Grow by amount
  FXRectangle& grow(FXshort margin);
  FXRectangle& grow(FXshort hormargin,FXshort vermargin);
  FXRectangle& grow(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  /// Shrink by amount
  FXRectangle& shrink(FXshort margin);
  FXRectangle& shrink(FXshort hormargin,FXshort vermargin);
  FXRectangle& shrink(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  /// Corners
  FXPoint tl() const { return FXPoint(x,y); }
  FXPoint tr() const { return FXPoint(x+w-1,y); }
  FXPoint bl() const { return FXPoint(x,y+h-1); }
  FXPoint br() const { return FXPoint(x+w-1,y+h-1); }

  /// Assignment
  FXRectangle& operator=(const FXRectangle& r){ x=r.x; y=r.y; w=r.w; h=r.h; return *this; }

  /// Set value from another rectangle
  FXRectangle& set(const FXRectangle& r){ x=r.x; y=r.y; w=r.w; h=r.h; return *this; }

  /// Set from point and size
  FXRectangle& set(const FXPoint& p,const FXSize& s){ x=p.x; y=p.y; w=s.w; h=s.h; return *this; }

  /// Set from corners
  FXRectangle& set(const FXPoint& topleft,const FXPoint& bottomright){ x=topleft.x; y=topleft.y; w=bottomright.x-topleft.x+1; h=bottomright.y-topleft.y+1; return *this; }

  /// Set value from components
  FXRectangle& set(FXshort xx,FXshort yy,FXshort ww,FXshort hh){ x=xx; y=yy; w=ww; h=hh; return *this; }

  /// Union and intersection with rectangle
  FXRectangle& operator+=(const FXRectangle &r);
  FXRectangle& operator*=(const FXRectangle &r);

  /// Union and intersection between rectangles
  FXRectangle operator+(const FXRectangle& r) const;
  FXRectangle operator*(const FXRectangle& r) const;

  /// Save object to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXRectangle& r);

  /// Load object from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXRectangle& r);
  };


inline bool overlap(const FXRectangle& a,const FXRectangle& b){ return b.x<a.x+a.w && b.y<a.y+a.h && a.x<b.x+b.w && a.y<b.y+b.h; }

extern FXAPI FXStream& operator<<(FXStream& store,const FXRectangle& r);
extern FXAPI FXStream& operator>>(FXStream& store,FXRectangle& r);

}

#endif
