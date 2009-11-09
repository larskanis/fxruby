/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
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
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

%rename("empty?")  FXSize::empty() const;
%rename("grow!")   FXSize::grow(FXshort);
%rename("grow!")   FXSize::grow(FXshort,FXshort);
%rename("grow!")   FXSize::grow(FXshort,FXshort,FXshort,FXshort);
%rename("shrink!") FXSize::shrink(FXshort);
%rename("shrink!") FXSize::shrink(FXshort,FXshort);
%rename("shrink!") FXSize::shrink(FXshort,FXshort,FXshort,FXshort);

/// Size
class FXSize {
public:
  FXshort w;
  FXshort h;
public:

  /// Constructors
  FXSize();
  FXSize(const FXSize& s);
  FXSize(FXshort ww,FXshort hh);

  /// Test if empty
  bool empty() const;

  %extend {
    /// Equality
    bool operator==(const FXSize& s) const { return (*self == s); }
    }

  /// Negation
  FXSize operator-();

  /// Grow by amount
  FXSize& grow(FXshort margin);
  FXSize& grow(FXshort hormargin,FXshort vermargin);
  FXSize& grow(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  /// Shrink by amount
  FXSize& shrink(FXshort margin);
  FXSize& shrink(FXshort hormargin,FXshort vermargin);
  FXSize& shrink(FXshort leftmargin,FXshort rightmargin,FXshort topmargin,FXshort bottommargin);

  %extend {
    /// Other operators
    FXSize operator+(const FXSize& s) const { return *self + s; }
    FXSize operator-(const FXSize& s) const { return *self - s; }
    FXSize operator*(FXshort c) const { return *self * c; }
    FXSize operator/(FXshort c) const { return *self / c; }
    }
  };
