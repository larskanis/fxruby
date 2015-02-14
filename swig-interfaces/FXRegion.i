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

%rename("empty?") FXRegion::empty() const;
%rename("contains?") FXRegion::contains(FXint x,FXint y) const;
%rename("contains?") FXRegion::contains(FXint x,FXint y,FXint w,FXint h) const;
%rename("offset!") FXRegion::offset(FXint dx,FXint dy);

/// Region
class FXRegion {
  friend class FXDC;
  friend class FXDCWindow;
public:

  /// Construct new empty region
  FXRegion();

  /// Construct new region copied from region r
  FXRegion(const FXRegion& r);

  /// Construct new region from rectangle
  FXRegion(const FXRectangle& rect);

  /// Construct rectangle region
  FXRegion(FXint x,FXint y,FXint w,FXint h);

  /// Construct polygon region
  FXRegion(const FXPoint* points,FXuint npoints,bool winding=FALSE);

  /// Return TRUE if region is empty
  bool empty() const;

  /// Return TRUE if region contains point
  bool contains(FXint x,FXint y) const;

  /// Return TRUE if region contains rectangle
  bool contains(FXint x,FXint y,FXint w,FXint h) const;

  /// Return bounding box
  FXRectangle bounds() const;

  /// Offset region by dx,dy
  FXRegion& offset(FXint dx,FXint dy);

  %extend {
    // Union region r with this one
    FXRegion operator+(const FXRegion& other) const { return (*self)+other; }

    // Intersect region r with this one
    FXRegion operator*(const FXRegion& other) const { return (*self)*other; }

    // Subtract region r from this one
    FXRegion operator-(const FXRegion& other) const { return (*self)-other; }

    // Xor region r with this one
    FXRegion operator^(const FXRegion& other) const { return (*self)^other; }

    // Return TRUE if region equal to this one
    bool operator==(const FXRegion& other) const { return (*self)==other; }
    }

  /// Reset region to empty
  void reset();

  /// Destroy region
  ~FXRegion();
  };
