/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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

/**
* The image frame is a simple frame widget displaying
* an image; the image is not owned by the image frame so
* it must be explicitly deleted elsewhere.
*/
class FXBitmapFrame : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:

  %extend {
    /// Construct image frame and pass it an image
    FXBitmapFrame(FXComposite* p,FXBitmap *bmp,FXuint opts=FRAME_SUNKEN|FRAME_THICK,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0){
      return new FXRbBitmapFrame(p,bmp,opts,x,y,w,h,pl,pr,pt,pb);
    }
  }

  /// Change the image being displayed
  void setBitmap(FXBitmap* bmp);

  /// Return the current image
  FXBitmap* getBitmap() const { return bitmap; }

  /// Set on color
  void setOnColor(FXColor clr);

  /// Get on color
  FXColor getOnColor() const { return onColor; }

  /// Set off color
  void setOffColor(FXColor clr);

  /// Get off color
  FXColor getOffColor() const { return offColor; }

  /// Set the current justification mode.
  void setJustify(FXuint mode);

  /// Get the current justification mode.
  FXuint getJustify() const;

  /// Destroy the widget, but do not destroy the image
  virtual ~FXBitmapFrame();
  };


DECLARE_FXOBJECT_VIRTUALS(FXBitmapFrame)
DECLARE_FXID_VIRTUALS(FXBitmapFrame)
DECLARE_FXDRAWABLE_VIRTUALS(FXBitmapFrame)
DECLARE_FXWINDOW_VIRTUALS(FXBitmapFrame)
