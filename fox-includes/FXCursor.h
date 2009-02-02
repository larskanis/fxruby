/********************************************************************************
*                                                                               *
*                         C u r s o r - O b j e c t                             *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXCursor.h 2725 2007-11-16 16:57:54Z lyle $                          *
********************************************************************************/
#ifndef FXCURSOR_H
#define FXCURSOR_H

#ifndef FXID_H
#include "FXId.h"
#endif

namespace FX {


// Stock cursors
enum FXStockCursor {
  CURSOR_ARROW=1,               /// Default left pointing arrow
  CURSOR_RARROW,                /// Right arrow
  CURSOR_IBEAM,                 /// Text I-Beam
  CURSOR_WATCH,                 /// Stopwatch or hourglass
  CURSOR_CROSS,                 /// Crosshair
  CURSOR_UPDOWN,                /// Move up, down
  CURSOR_LEFTRIGHT,             /// Move left, right
  CURSOR_MOVE                   /// Move up,down,left,right
  };


/// Cursor options
enum {
  CURSOR_KEEP  = 0x00000100,    /// Keep pixel data in client
  CURSOR_OWNED = 0x00000200     /// Pixel data is owned by image
  };


/// Cursor class
class FXAPI FXCursor : public FXId {
  FXDECLARE(FXCursor)
protected:
  FXColor *data;        // Source data
  FXint    width;       // Width
  FXint    height;      // Height
  FXint    hotx;        // Hot spot x
  FXint    hoty;        // Hot spot y
  FXuint   options;     // Options
protected:
  FXCursor();
private:
  FXCursor(const FXCursor&);
  FXCursor &operator=(const FXCursor&);
public:

  /// Make stock cursor
  FXCursor(FXApp* a,FXStockCursor curid=CURSOR_ARROW);

  /// Make cursor from source and mask; cursor size should at most 32x32 for portability!
  FXCursor(FXApp* a,const FXuchar* src,const FXuchar* msk,FXint w=32,FXint h=32,FXint hx=0,FXint hy=0);

  /// Make cursor from FXColor pixels; cursor size should be at most 32x32 for portability!
  FXCursor(FXApp* a,const FXColor* pix,FXint w=32,FXint h=32,FXint hx=0,FXint hy=0);

  /// Width of cursor; returns 0 for stock cursors
  FXint getWidth() const { return width; }

  /// Height of cursor; returns 0 for stock cursors
  FXint getHeight() const { return height; }

  /// Set hotspot x; returns 0 for stock cursors
  void setHotX(FXint x){ hotx=x; }

  /// Get hotspot x; returns 0 for stock cursors
  FXint getHotX() const { return hotx; }

  /// Set hotspot y; returns 0 for stock cursors
  void setHotY(FXint y){ hoty=y; }

  /// Get hotspot y; returns 0 for stock cursors
  FXint getHotY() const { return hoty; }

  /// Check if there is color in the cursor
  FXbool isColor() const;

  /// Create cursor
  virtual void create();

  /// Detach cursor
  virtual void detach();

  /// Destroy cursor
  virtual void destroy();

  /// Release pixels buffer if it was owned
  virtual void release();

  /// Save pixel data only
  virtual FXbool savePixels(FXStream& store) const;

  /// Load pixel data only
  virtual FXbool loadPixels(FXStream& store);

  /// Save cursor to a stream
  virtual void save(FXStream& store) const;

  /// Load cursor from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXCursor();
  };

}

#endif
