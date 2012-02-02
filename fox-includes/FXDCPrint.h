/********************************************************************************
*                                                                               *
*           D e v i c e   C o n t e x t   F o r   P r i n t i n g               *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDCPrint.h 2194 2005-08-24 12:58:14Z lyle $                         *
********************************************************************************/
#ifndef FXDCPRINT_H
#define FXDCPRINT_H

#ifndef FXDC_H
#include "FXDC.h"
#endif

//////////////////////////////  UNDER DEVELOPMENT  //////////////////////////////

namespace FX {

class FXApp;
class FXDrawable;
class FXImage;
class FXBitmap;
class FXIcon;
class FXFont;


/// Printer flags
enum FXPrintFlags {
  PRINT_DEST_PAPER        = 0,    /// Send print to paper
  PRINT_DEST_FILE         = 1,    /// Send print to file
  PRINT_PAGES_ALL         = 0,    /// Print all pages
  PRINT_PAGES_EVEN        = 2,    /// Print even pages only
  PRINT_PAGES_ODD         = 4,    /// Print odd pages only
  PRINT_PAGES_RANGE       = 8,    /// Print range of pages
  PRINT_COLLATE_NORMAL    = 0,    /// Normal collate order
  PRINT_COLLATE_REVERSED  = 16,   /// Reversed collate order
  PRINT_PORTRAIT          = 0,    /// Portrait orientation
  PRINT_LANDSCAPE         = 32,   /// Landscape orientation
  PRINT_BLACKANDWHITE     = 0,    /// Black and white output
  PRINT_COLOR             = 64,   /// Color output
  PRINT_NOBOUNDS          = 128   /// Must determine bounding box
  };


/// Printer media size
enum FXMediaSize {
  MEDIA_CUSTOM            = 0,    /// Custom paper size
  MEDIA_USLETTER          = 1,    /// US Letter size
  MEDIA_LEGAL             = 2,    /// US Legal size
  MEDIA_A4                = 3,    /// A4
  MEDIA_ENVELOPE          = 4     /// #10 Envelope
  };


/// Bounding box
struct FXPSBounds {
  FXdouble  xmin;
  FXdouble  xmax;
  FXdouble  ymin;
  FXdouble  ymax;
  };


/// Describes printer
struct FXAPI FXPrinter {
  FXString name;                          /// Printer name
  FXuint   firstpage;                     /// First page that can be printed
  FXuint   lastpage;                      /// Last page that can be printed
  FXuint   currentpage;                   /// Current page to print
  FXuint   frompage;                      /// On output, this is the first page to print
  FXuint   topage;                        /// On output, last page to print
  FXuint   mediasize;                     /// Media size index
  FXdouble mediawidth;                    /// Width of paper in points [1/72 of an inch]
  FXdouble mediaheight;                   /// Height of paper in points
  FXdouble leftmargin;                    /// Left margin
  FXdouble rightmargin;                   /// Right margin
  FXdouble topmargin;                     /// Top margin
  FXdouble bottommargin;                  /// Bottom margin
  FXuint   numcopies;                     /// Number of copies
  FXuint   flags;                         /// Flags
  };


/// Postscript Printer Device Context
class FXAPI FXDCPrint : public FXDC {
//  friend class FXGLViewer; // This is TEMPORARY!!!
protected:
  void      *psout;                   // File Stream for PS output
  FXFont    *font;
  FXuint     flags;
  FXint      Xr,Yr;
  FXdouble   mediawidth;              // Media width
  FXdouble   mediaheight;             // Media height
  FXPSBounds mediabb;                 // Media bounding box
  FXPSBounds docbb;                   // Document bounding box
  FXPSBounds pagebb;                  // Page bounding box
  FXint      pagecount;               // Number of pages printed
  FXint      nchars;                  // Number of characters on a line
  FXint      pxmin;                   // min X coord in content
  FXint      pymin;                   // min Y coord in content
  FXint      pxmax;                   // max X coord in content
  FXint      pymax;                   // max Y coord in content
protected:
  void bbox(FXfloat x,FXfloat y);
  void tfm(FXfloat& xo,FXfloat& yo,FXfloat xi,FXfloat yi);
private:
  FXDCPrint();
  FXDCPrint(const FXDCPrint&);
  FXDCPrint &operator=(const FXDCPrint&);
public:

  /// Construct
  FXDCPrint(FXApp* a);

  /// Generate print job prolog
  FXbool beginPrint(FXPrinter& job);

  /// Generate print job epilog
  FXbool endPrint();

  /// Generate begin of page
  FXbool beginPage(FXuint page=1);

  /// Generate end of page
  FXbool endPage();

  FXbool setContentRange(FXint pxmin, FXint pymin, FXint pxmax, FXint pymax);

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

  /// Draw arcs
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

  /// Draw arcs
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

  /// Set foreground/background drawing color
  virtual void setForeground(FXColor clr);
  virtual void setBackground(FXColor clr);

  /// Set dash pattern
  virtual void setDashes(FXuint dashoffset,const FXchar *dashlist,FXuint n);

  /// Set line width
  virtual void setLineWidth(FXuint linewidth=0);

  /// Set line cap style
  virtual void setLineCap(FXCapStyle capstyle=CAP_BUTT);

  /// Set line join style
  virtual void setLineJoin(FXJoinStyle joinstyle=JOIN_MITER);

  /// Set line style
  virtual void setLineStyle(FXLineStyle linestyle=LINE_SOLID);

  /// Set fill style
  virtual void setFillStyle(FXFillStyle fillstyle=FILL_SOLID);

  /// Set fill rule
  virtual void setFillRule(FXFillRule fillrule=RULE_EVEN_ODD);

  /// Set blit function
  virtual void setFunction(FXFunction func=BLT_SRC);

  /// Set the tile
  virtual void setTile(FXImage* tile,FXint dx=0,FXint dy=0);

  /// Set the stipple pattern
  virtual void setStipple(FXBitmap *stipple,FXint dx=0,FXint dy=0);

  /// Set the stipple pattern
  virtual void setStipple(FXStipplePattern stipple,FXint dx=0,FXint dy=0);

  /// Set clip rectangle
  virtual void setClipRectangle(FXint x,FXint y,FXint w,FXint h);

  /// Set clip rectangle
  virtual void setClipRectangle(const FXRectangle& rectangle);

  /// Clear clipping
  virtual void clearClipRectangle();

  /// Set clip mask
  virtual void setClipMask(FXBitmap* mask,FXint dx=0,FXint dy=0);

  /// Clear clip mask
  virtual void clearClipMask();

  /// Set font to draw text with
  virtual void setFont(FXFont *fnt);

  /// Clip drawing by child windows
  virtual void clipChildren(FXbool yes);

  /// Temporarily public; do not rely on this!!
  void outhex(FXuint hex);
  void outf(const char* format,...);

  /// Cleanup
  virtual ~FXDCPrint();
  };

}

#endif
