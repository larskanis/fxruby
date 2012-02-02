/********************************************************************************
*                                                                               *
*               D e v i c e   C o n t e x t   B a s e   C l a s s               *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDC.h 2193 2005-08-24 08:08:50Z lyle $                              *
********************************************************************************/
#ifndef FXDC_H
#define FXDC_H

namespace FX {

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
  FXshort x1,y1,x2,y2;
  };


/// Arc
struct FXArc {
  FXshort x,y,w,h,a,b;
  };


class FXApp;
class FXImage;
class FXBitmap;
class FXIcon;
class FXFont;
class FXDrawable;
class FXRegion;


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
class FXAPI FXDC {
  friend class FXFont;
private:
  FXApp           *app;         // Application
protected:
  void            *ctx;         // Context handle
  FXFont          *font;        // Drawing font
  FXStipplePattern pattern;     // Stipple pattern
  FXBitmap        *stipple;     // Stipple bitmap
  FXImage         *tile;        // Tile image
  FXBitmap        *mask;        // Mask bitmap
  FXRectangle      clip;        // Clip rectangle
  FXColor          fg;          // Foreground color
  FXColor          bg;          // Background color
  FXuint           width;       // Line width
  FXCapStyle       cap;         // Line cap style
  FXJoinStyle      join;        // Line join style
  FXLineStyle      style;       // Line style
  FXFillStyle      fill;        // Fill style
  FXFillRule       rule;        // Fill rule
  FXFunction       rop;         // RasterOp
  FXchar           dashpat[32]; // Line dash pattern data
  FXuint           dashlen;     // Line dash pattern length
  FXuint           dashoff;     // Line dash pattern offset
  FXint            tx;          // Tile dx
  FXint            ty;          // Tile dy
  FXint            cx;          // Clip x
  FXint            cy;          // Clip y
private:
  FXDC();
  FXDC(const FXDC&);
  FXDC &operator=(const FXDC&);
public:

  /// Construct dummy DC
  FXDC(FXApp* a);

  /// Get application
  FXApp* getApp() const { return app; }

  /// Get context handle
  void* context() const { return ctx; }

  /// Read back pixel
  virtual FXColor readPixel(FXint x,FXint y);

  /// Draw points
  virtual void drawPoint(FXint x,FXint y);
  virtual void drawPoints(const FXPoint* points,FXuint npoints);
  virtual void drawPointsRel(const FXPoint* points,FXuint npoints);

  /// Draw lines
  virtual void drawLine(FXint x1,FXint y1,FXint x2,FXint y2);
  virtual void drawLines(const FXPoint* points,FXuint npoints);
  virtual void drawLinesRel(const FXPoint* points,FXuint npoints);
  virtual void drawLineSegments(const FXSegment* segments,FXuint nsegments);

  /// Draw rectangles
  virtual void drawRectangle(FXint x,FXint y,FXint w,FXint h);
  virtual void drawRectangles(const FXRectangle* rectangles,FXuint nrectangles);

  /// Draw rounded rectangle with ellipse with ew and ellips height eh
  virtual void drawRoundRectangle(FXint x,FXint y,FXint w,FXint h,FXint ew,FXint eh);

  /**
  * Draw arcs.
  * The argument ang1 specifies the start of the arc relative to the
  * three-o'clock position from the center, in units of degrees*64.
  * The argument ang2 specifies the path and extent of the arc relative
  * to the start of the arc, in units of degrees*64.
  * The arguments x,y,w,h specify the bounding rectangle.
  */
  virtual void drawArc(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);
  virtual void drawArcs(const FXArc* arcs,FXuint narcs);

  /// Draw ellipse
  virtual void drawEllipse(FXint x,FXint y,FXint w,FXint h);

  /// Filled rectangles
  virtual void fillRectangle(FXint x,FXint y,FXint w,FXint h);
  virtual void fillRectangles(const FXRectangle* rectangles,FXuint nrectangles);

  /// Filled rounded rectangle with ellipse with ew and ellips height eh
  virtual void fillRoundRectangle(FXint x,FXint y,FXint w,FXint h,FXint ew,FXint eh);

  /// Fill chord
  virtual void fillChord(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);
  virtual void fillChords(const FXArc* chords,FXuint nchords);

  /// Fill arcs
  virtual void fillArc(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);
  virtual void fillArcs(const FXArc* arcs,FXuint narcs);

  /// Fill ellipse
  virtual void fillEllipse(FXint x,FXint y,FXint w,FXint h);

  /// Filled polygon
  virtual void fillPolygon(const FXPoint* points,FXuint npoints);
  virtual void fillConcavePolygon(const FXPoint* points,FXuint npoints);
  virtual void fillComplexPolygon(const FXPoint* points,FXuint npoints);

  /// Filled polygon with relative points
  virtual void fillPolygonRel(const FXPoint* points,FXuint npoints);
  virtual void fillConcavePolygonRel(const FXPoint* points,FXuint npoints);
  virtual void fillComplexPolygonRel(const FXPoint* points,FXuint npoints);

  /// Draw hashed box
  virtual void drawHashBox(FXint x,FXint y,FXint w,FXint h,FXint b=1);

  /// Draw focus rectangle
  virtual void drawFocusRectangle(FXint x,FXint y,FXint w,FXint h);

  /// Draw area from source
  virtual void drawArea(const FXDrawable* source,FXint sx,FXint sy,FXint sw,FXint sh,FXint dx,FXint dy);

  /// Draw area stretched area from source
  virtual void drawArea(const FXDrawable* source,FXint sx,FXint sy,FXint sw,FXint sh,FXint dx,FXint dy,FXint dw,FXint dh);

  /// Draw image
  virtual void drawImage(const FXImage* image,FXint dx,FXint dy);

  /// Draw bitmap
  virtual void drawBitmap(const FXBitmap* bitmap,FXint dx,FXint dy);

  /// Draw icon
  virtual void drawIcon(const FXIcon* icon,FXint dx,FXint dy);
  virtual void drawIconShaded(const FXIcon* icon,FXint dx,FXint dy);
  virtual void drawIconSunken(const FXIcon* icon,FXint dx,FXint dy);

  /// Draw string with base line starting at x, y
  virtual void drawText(FXint x,FXint y,const FXString& string);
  virtual void drawText(FXint x,FXint y,const FXchar* string,FXuint length);

  /// Draw text starting at x, y over filled background
  virtual void drawImageText(FXint x,FXint y,const FXString& string);
  virtual void drawImageText(FXint x,FXint y,const FXchar* string,FXuint length);

  /// Set foreground drawing color
  virtual void setForeground(FXColor clr);

  /// Get foreground drawing color
  FXColor getForeground() const { return fg; }

  /// Set background drawing color
  virtual void setBackground(FXColor clr);

  /// Get background drawing color
  FXColor getBackground() const { return bg; }

  /**
  * Set dash pattern and dash offset.
  * A dash pattern of [1 2 3 4] is a repeating pattern of 1 foreground pixel,
  * 2 background pixels, 3 foreground pixels, and 4 background pixels.
  * The offset is where in the pattern the system will start counting.
  * The maximum length of the dash pattern is 32.
  */
  virtual void setDashes(FXuint dashoffset,const FXchar *dashpattern,FXuint dashlength);

  /// Get dash pattern
  const FXchar* getDashPattern() const { return dashpat; }

  /// Get dash offset
  FXuint getDashOffset() const { return dashoff; }

  /// Get dash length
  FXuint getDashLength() const { return dashlen; }

  /// Set line width:- 0 means thinnest/fastest possible
  virtual void setLineWidth(FXuint linewidth=0);

  /// Get line width
  FXuint getLineWidth() const { return width; }

  /// Set line cap style
  virtual void setLineCap(FXCapStyle capstyle=CAP_BUTT);

  /// Get line cap style
  FXCapStyle getLineCap() const { return cap; }

  /// Set line join style
  virtual void setLineJoin(FXJoinStyle joinstyle=JOIN_MITER);

  /// Get line join style
  FXJoinStyle getLineJoin() const { return join; }

  /// Set line style
  virtual void setLineStyle(FXLineStyle linestyle=LINE_SOLID);

  /// Get line style
  FXLineStyle getLineStyle() const { return style; }

  /// Set fill style
  virtual void setFillStyle(FXFillStyle fillstyle=FILL_SOLID);

  /// Get fill style
  FXFillStyle getFillStyle() const { return fill; }

  /// Set fill rule
  virtual void setFillRule(FXFillRule fillrule=RULE_EVEN_ODD);

  /// Get fill rule
  FXFillRule getFillRule() const { return rule; }

  /// Set rasterop function
  virtual void setFunction(FXFunction func=BLT_SRC);

  /// Get rasterop function
  FXFunction getFunction() const { return rop; }

  /// Set the tile image
  virtual void setTile(FXImage* image,FXint dx=0,FXint dy=0);

  /// Get the tile image
  FXImage *getTile() const { return tile; }

  /// Set the stipple pattern
  virtual void setStipple(FXBitmap *bitmap,FXint dx=0,FXint dy=0);

  /// Get stipple bitmap
  FXBitmap *getStippleBitmap() const { return stipple; }

  /// Set the stipple pattern
  virtual void setStipple(FXStipplePattern pat,FXint dx=0,FXint dy=0);

  /// Get pattern
  FXStipplePattern getStipplePattern() const { return pattern; }

  /// Set clip region
  virtual void setClipRegion(const FXRegion& region);

  /// Set clip rectangle
  virtual void setClipRectangle(FXint x,FXint y,FXint w,FXint h);

  /// Change clip rectangle
  virtual void setClipRectangle(const FXRectangle& rectangle);

  /// Return clip rectangle
  const FXRectangle& getClipRectangle() const { return clip; }

  /// Return clip x
  FXint getClipX() const { return clip.x; }

  /// Return clip y
  FXint getClipY() const { return clip.y; }

  /// Return clip width
  FXint getClipWidth() const { return clip.w; }

  /// Return clip height
  FXint getClipHeight() const { return clip.h; }

  /// Clear clipping
  virtual void clearClipRectangle();

  /// Set clip mask
  virtual void setClipMask(FXBitmap* bitmap,FXint dx=0,FXint dy=0);

  /// Clear clip mask
  virtual void clearClipMask();

  /// Set font to draw text with
  virtual void setFont(FXFont *fnt);

  /// Get text font
  FXFont* getFont() const { return font; }

  /// Clip against child windows
  virtual void clipChildren(FXbool yes);

  /// Destructor
  virtual ~FXDC();
  };

}

#endif
