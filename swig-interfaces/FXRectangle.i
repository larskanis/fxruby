/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

%rename("contains?") FXRectangle::contains(const FXPoint& p) const;
%rename("contains?") FXRectangle::contains(FXshort xx,FXshort yy) const;
%rename("contains?") FXRectangle::contains(const FXRectangle& r) const;
%rename("grow!")     FXRectangle::grow(FXshort margin);
%rename("grow!")     FXRectangle::grow(FXshort hormargin,FXshort vermargin);
%rename("grow!")     FXRectangle::grow(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);
%rename("move!")     FXRectangle::move(const FXPoint&);
%rename("move!")     FXRectangle::move(FXshort dx,FXshort dy);
%rename("overlaps?") FXRectangle::overlap(const FXRectangle& p) const;
%rename("shrink!")   FXRectangle::shrink(FXshort margin);
%rename("shrink!")   FXRectangle::shrink(FXshort hormargin,FXshort vermargin);
%rename("shrink!")   FXRectangle::shrink(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

/// Rectangle
class FXRectangle {
public:
  FXshort x;
  FXshort y;
  FXshort w;
  FXshort h;
public:

  /// Constructors
  FXRectangle();
  FXRectangle(FXshort xx,FXshort yy,FXshort ww,FXshort hh);
  FXRectangle(const FXPoint& p,const FXSize& s);
  FXRectangle(const FXPoint& topleft,const FXPoint& bottomright);

  %extend {
    /// Equality
    bool operator==(const FXRectangle& p) const {
      return *self == p;
      }
    }

  /// Point in rectangle
  bool contains(const FXPoint& p) const;
  bool contains(FXshort xx,FXshort yy) const;

  /// Rectangle properly contained in rectangle
  bool contains(const FXRectangle& r) const;

  %extend {
    /// Rectangles overlap
    bool overlap(const FXRectangle& p) const {
      return overlap(*self,p);
      }
    }

  /// Return moved rectangle
  FXRectangle& move(const FXPoint& p);
  FXRectangle& move(FXshort dx,FXshort dy);

  /// Grow by amount
  FXRectangle& grow(FXshort margin);
  FXRectangle& grow(FXshort hormargin,FXshort vermargin);
  FXRectangle& grow(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  /// Shrink by amount
  FXRectangle& shrink(FXshort margin);
  FXRectangle& shrink(FXshort hormargin,FXshort vermargin);
  FXRectangle& shrink(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  /// Corners
  FXPoint tl() const;
  FXPoint tr() const;
  FXPoint bl() const;
  FXPoint br() const;

  %extend {
    /// Union with rectangle
    FXRectangle operator+(const FXRectangle& p) const {
      return *self + p;
      }

    /// Intersection with rectangle
    FXRectangle operator*(const FXRectangle& p) const {
      return *self * p;
      }
    }
  };

