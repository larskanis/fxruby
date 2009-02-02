/********************************************************************************
*                                                                               *
*                    B i t m a p   V i e w   W i d g e t                        *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXBitmapView.h 2335 2006-01-28 02:33:03Z lyle $                       *
********************************************************************************/
#ifndef FXBITMAPVIEW_H
#define FXBITMAPVIEW_H

#ifndef FXSCROLLAREA_H
#include "FXScrollArea.h"
#endif

namespace FX {


class FXBitmap;

/// Bitmap alignment styles
enum {
  BITMAPVIEW_NORMAL    = 0,              /// Normal mode is centered
  BITMAPVIEW_CENTER_X  = 0,              /// Centered horizontally
  BITMAPVIEW_LEFT      = 0x00100000,     /// Left-aligned
  BITMAPVIEW_RIGHT     = 0x00200000,     /// Right-aligned
  BITMAPVIEW_CENTER_Y  = 0,              /// Centered vertically
  BITMAPVIEW_TOP       = 0x00400000,     /// Top-aligned
  BITMAPVIEW_BOTTOM    = 0x00800000      /// Bottom-aligned
  };

/**
* The Bitmap View widget display a scrollable view of a monochrome bitmap image;
* the bitmap is not owned by the bitmap frame so it must be explicitly deleted
* elsewhere.  Thus, a single bitmap image can be displayed inside multiple bitmap
* view widgets.
*/
class FXAPI FXBitmapView : public FXScrollArea {
  FXDECLARE(FXBitmapView)
protected:
  FXBitmap *bitmap;     // Image to view
  FXColor   onColor;    // Color for on pixels
  FXColor   offColor;   // Color for off pixels
  FXint     grabx;      // Grab point x
  FXint     graby;      // Grab point y
protected:
  FXBitmapView();
private:
  FXBitmapView(const FXBitmapView&);
  FXBitmapView &operator=(const FXBitmapView&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onRightBtnPress(FXObject*,FXSelector,void*);
  long onRightBtnRelease(FXObject*,FXSelector,void*);
public:
  enum {
    ID_XYZ=FXScrollArea::ID_LAST,
    ID_LAST
    };
public:

  /// Construct a scroll window
  FXBitmapView(FXComposite* p,FXBitmap* bmp=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Perform layout immediately
  virtual void layout();

  /// Image view widget can receive focus
  virtual bool canFocus() const;

  /// Return the width of the contents
  virtual FXint getContentWidth();

  /// Return the height of the contents
  virtual FXint getContentHeight();

  /// Change image
  void setBitmap(FXBitmap* bmp);

  /// Return image
  FXBitmap* getBitmap() const { return bitmap; }

  /// Set on color
  void setOnColor(FXColor clr);

  /// Get on color
  FXColor getOnColor() const { return onColor; }

  /// Set off color
  void setOffColor(FXColor clr);

  /// Get off color
  FXColor getOffColor() const { return offColor; }

  /// Set the current alignment.
  void setAlignment(FXuint mode);

  /// Get the current alignment.
  FXuint getAlignment() const;

  /// Save list to a stream
  virtual void save(FXStream& store) const;

  /// Load list from a stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXBitmapView();
  };

}

#endif
