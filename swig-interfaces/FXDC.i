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

/// Drawing (BITBLT) functions
enum FXFunction {
  BLT_CLR,                        /// D := 0
  BLT_SRC_AND_DST,                /// D := S & D
  BLT_SRC_AND_NOT_DST,            /// D := S & ~D
  BLT_SRC,                        /// D := S
  BLT_NOT_SRC_AND_DST,            /// D := ~S & D
  BLT_DST,                        /// D := D
  BLT_SRC_XOR_DST,                /// D := S ^ D
  BLT_SRC_OR_DST,                 /// D := S | D
  BLT_NOT_SRC_AND_NOT_DST,        /// D := ~S & ~D  ==  D := ~(S | D)
  BLT_NOT_SRC_XOR_DST,            /// D := ~S ^ D
  BLT_NOT_DST,                    /// D := ~D
  BLT_SRC_OR_NOT_DST,             /// D := S | ~D
  BLT_NOT_SRC,                    /// D := ~S
  BLT_NOT_SRC_OR_DST,             /// D := ~S | D
  BLT_NOT_SRC_OR_NOT_DST,         /// D := ~S | ~D  ==  ~(S & D)
  BLT_SET                         /// D := 1
  };


/// Line Styles
enum FXLineStyle {
  LINE_SOLID,                     /// Solid lines
  LINE_ONOFF_DASH,                /// On-off dashed lines
  LINE_DOUBLE_DASH                /// Double dashed lines
  };


/// Line Cap Styles
enum FXCapStyle {
  CAP_NOT_LAST,                   /// Don't include last end cap
  CAP_BUTT,                       /// Butting line end caps
  CAP_ROUND,                      /// Round line end caps
  CAP_PROJECTING                  /// Projecting line end caps
  };


/// Line Join Styles
enum FXJoinStyle {
  JOIN_MITER,                     /// Mitered or pointy joints
  JOIN_ROUND,                     /// Round line joints
  JOIN_BEVEL                      /// Beveled or flat joints
  };


/// Fill Styles
enum FXFillStyle {
  FILL_SOLID,                     /// Fill with solid color
  FILL_TILED,                     /// Fill with tiled bitmap
  FILL_STIPPLED,                  /// Fill where stipple mask is 1
  FILL_OPAQUESTIPPLED             /// Fill with foreground where mask is 1, background otherwise
  };


/// Fill Rules
enum FXFillRule {
  RULE_EVEN_ODD,                  /// Even odd polygon filling
  RULE_WINDING                    /// Winding rule polygon filling
  };


/// Stipple/dither patterns
enum FXStipplePattern {
  STIPPLE_0         = 0,
  STIPPLE_NONE      = 0,
  STIPPLE_BLACK     = 0,            /// All ones
  STIPPLE_1         = 1,
  STIPPLE_2         = 2,
  STIPPLE_3         = 3,
  STIPPLE_4         = 4,
  STIPPLE_5         = 5,
  STIPPLE_6         = 6,
  STIPPLE_7         = 7,
  STIPPLE_8         = 8,
  STIPPLE_GRAY      = 8,            /// 50% gray
  STIPPLE_9         = 9,
  STIPPLE_10        = 10,
  STIPPLE_11        = 11,
  STIPPLE_12        = 12,
  STIPPLE_13        = 13,
  STIPPLE_14        = 14,
  STIPPLE_15        = 15,
  STIPPLE_16        = 16,
  STIPPLE_WHITE     = 16,           /// All zeroes
  STIPPLE_HORZ      = 17,           /// Horizontal hatch pattern
  STIPPLE_VERT      = 18,           /// Vertical hatch pattern
  STIPPLE_CROSS     = 19,           /// Cross-hatch pattern
  STIPPLE_DIAG      = 20,           /// Diagonal // hatch pattern
  STIPPLE_REVDIAG   = 21,           /// Reverse diagonal \\ hatch pattern
  STIPPLE_CROSSDIAG = 22            /// Cross-diagonal hatch pattern
  };


/// Line segment
struct FXSegment {
  %extend {
    FXSegment(FXshort x1=0,FXshort y1=0,FXshort x2=0,FXshort y2=0){
      FXSegment* seg=new FXSegment;
      seg->x1=x1; seg->y1=y1; seg->x2=x2; seg->y2=y2;
      return seg;
      }
    }
  FXshort x1,y1,x2,y2;
  ~FXSegment();
  };


/// Arc
struct FXArc {
  %extend {
    FXArc(FXshort x=0,FXshort y=0,FXshort w=0,FXshort h=0,FXshort a=0,FXshort b=0){
      FXArc* arc=new FXArc;
      arc->x=x; arc->y=y; arc->w=w; arc->h=h; arc->a=a; arc->b=b;
      return arc;
      }
    }
  FXshort x,y,w,h,a,b;
  ~FXArc();
  };


class FXApp;
class FXImage;
class FXBitmap;
class FXIcon;
class FXFont;
class FXDrawable;

%ignore FXDC::context() const;
%ignore FXDC::getDashLength() const;


/**
* Abstract Device Context
*
* A Device Context is used to maintain the state of the graphics drawing system.
* Defining your drawing code in terms of the Abstract Device Context allows the
* drawing commands to be rendered on different types of surfaces, such as windows
* and images (FXDCWindow), or on paper (FXDCPrint).
* WYSYWYG may be obtained by using the same identical drawing code in your
* application regardless of the actual device surface being utilized.
*/
class FXDC {
public:
  %extend {
    /// Construct dummy DC
    FXDC(FXApp* a){
      return new FXRbDC(a);
      }
    }

  /// Get context handle
  void* context() const { return ctx; }

  /// Get application
  FXApp* getApp() const;

  /// Get foreground drawing color
  FXColor getForeground() const;

  /// Get background drawing color
  FXColor getBackground() const;

  %extend {
    /// Get dash pattern
    VALUE getDashPattern() const {
      return FXRbMakeArray(self->getDashPattern(), self->getDashLength());
      }
    }

  /// Get dash offset
  FXuint getDashOffset() const;

  /// Get dash length
  FXuint getDashLength() const;

  /// Get line width
  FXuint getLineWidth() const;

  /// Get line cap style
  FXCapStyle getLineCap() const;

  /// Get line join style
  FXJoinStyle getLineJoin() const;

  /// Get line style
  FXLineStyle getLineStyle() const;

  /// Get fill style
  FXFillStyle getFillStyle() const;

  /// Get fill rule
  FXFillRule getFillRule() const;

  /// Get rasterop function
  FXFunction getFunction() const;

  /// Get the tile image
  FXImage *getTile() const;

  /// Get stipple bitmap
  FXBitmap *getStippleBitmap() const;

  /// Get pattern
  FXStipplePattern getStipplePattern() const;

  /// Return clip rectangle
  const FXRectangle& getClipRectangle() const;

  /// Return clip x
  FXint getClipX() const;

  /// Return clip y
  FXint getClipY() const;

  /// Return clip width
  FXint getClipWidth() const;

  /// Return clip height
  FXint getClipHeight() const;

  /// Get text font
  FXFont* getFont() const;

  /// Destructor
  virtual ~FXDC();
  };


DECLARE_FXDC_VIRTUALS(FXDC)

