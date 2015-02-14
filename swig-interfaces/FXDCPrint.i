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
  FXPSBounds();
  FXdouble  xmin;
  FXdouble  xmax;
  FXdouble  ymin;
  FXdouble  ymax;
  ~FXPSBounds();
  };


/// Describes printer
struct FXPrinter {
  FXPrinter();
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
  ~FXPrinter();
  };


/// Postscript Printer Device Context
class FXDCPrint : public FXDC {
public:
  %extend {
    /// Construct
    FXDCPrint(FXApp* a){
      return new FXRbDCPrint(a);
      }
    }

  /// Generate print job prolog
  FXbool beginPrint(FXPrinter& job);

  /// Generate print job epilog
  FXbool endPrint();

  /// Generate begin of page
  FXbool beginPage(FXuint page=1);

  /// Generate end of page
  FXbool endPage();

  FXbool setContentRange(FXint pxmin, FXint pymin, FXint pxmax, FXint pymax);

  /// Cleanup
  virtual ~FXDCPrint();
  };


DECLARE_FXDC_VIRTUALS(FXDCPrint)

