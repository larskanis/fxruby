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

// Stock cursors
enum FXStockCursor {
  CURSOR_ARROW=1,                   // Default left pointing arrow
  CURSOR_RARROW,                    // Right arrow
  CURSOR_IBEAM,                     // Text I-Beam
  CURSOR_WATCH,                     // Stopwatch or hourglass
  CURSOR_CROSS,                     // Crosshair
  CURSOR_UPDOWN,                    // Move up, down
  CURSOR_LEFTRIGHT,                 // Move left, right
  CURSOR_MOVE                       // Move up,down,left,right
  };


/// Cursor options
enum {
  CURSOR_KEEP  = 0x00000100,    /// Keep pixel data in client
  CURSOR_OWNED = 0x00000200     /// Pixel data is owned by image
  };


/// Cursor class
class FXCursor : public FXId {
protected:
  FXColor *data;              // Source data
  FXint    width;             // Width
  FXint    height;            // Height
  FXint    hotx;              // Hot spot x
  FXint    hoty;              // Hot spot y
  FXuint   options;           // Options
protected:
  FXCursor();
public:
  %extend {
    /// Make stock cursor
    FXCursor(FXApp* a,FXStockCursor curid=CURSOR_ARROW){
      return new FXRbCursor(a,curid);
      }
  
    /// Make cursor from source and mask; cursor size should at most 32x32 for portability!
    FXCursor(FXApp* a,const FXuchar* src,const FXuchar* msk,FXint w=32,FXint h=32,FXint hx=0,FXint hy=0){
      return new FXRbCursor(a,src,msk,w,h,hx,hy);
      }

    /// Make cursor from FXColor pixels; cursor size should at most 32x32 for portability!
    FXCursor(FXApp* a,const FXColor* pix,FXint w=32,FXint h=32,FXint hx=0,FXint hy=0){
      return new FXRbCursor(a,pix,w,h,hx,hy);
      }
    }

  /// Width of cursor
  FXint getWidth() const;

  /// Height of cursor
  FXint getHeight() const;

  /// Set hotspot x
  void setHotX(FXint x);
  
  /// Get hotspot x
  FXint getHotX() const;

  /// Set hotspot y
  void setHotY(FXint y);
  
  /// Get hotspot y
  FXint getHotY() const;
  
  /// Check if there is color in the cursor
  bool isColor() const;

  /// Destructor
  virtual ~FXCursor();
  };


DECLARE_FXOBJECT_VIRTUALS(FXCursor)
DECLARE_FXID_VIRTUALS(FXCursor)
DECLARE_FXCURSOR_VIRTUALS(FXCursor)

%{
static swig_type_info *FXCursor_dynamic_cast(void **ptr) {
    FXCursor **ppCursor = reinterpret_cast<FXCursor **>(ptr);
    FXCURCursor *pCURCursor=dynamic_cast<FXCURCursor*>(*ppCursor);
    if(pCURCursor){
      *ptr=reinterpret_cast<void*>(pCURCursor);
      return SWIG_TypeQuery("FXCURCursor *");
      }
    FXGIFCursor *pGIFCursor=dynamic_cast<FXGIFCursor*>(*ppCursor);
    if(pGIFCursor){
      *ptr=reinterpret_cast<void*>(pGIFCursor);
      return SWIG_TypeQuery("FXGIFCursor *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXCursor, FXCursor_dynamic_cast);

