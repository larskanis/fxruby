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

class FXImage;


/// Image alignment styles
enum {
  IMAGEVIEW_NORMAL    = 0,              /// Normal mode is centered
  IMAGEVIEW_CENTER_X  = 0,              /// Centered horizontally
  IMAGEVIEW_LEFT      = 0x00100000,     /// Left-aligned
  IMAGEVIEW_RIGHT     = 0x00200000,     /// Right-aligned
  IMAGEVIEW_CENTER_Y  = 0,              /// Centered vertically
  IMAGEVIEW_TOP       = 0x00400000,     /// Top-aligned
  IMAGEVIEW_BOTTOM    = 0x00800000      /// Bottom-aligned
  };


/**
* The Image View widget display a scrollable view of an image.
*/
class FXImageView : public FXScrollArea {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
public:
  enum {
    ID_XYZ=FXScrollArea::ID_LAST,
    ID_LAST
    };
public:
  %extend {
    /// Construct a scroll window
    FXImageView(FXComposite* p,FXImage* img=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbImageView(p,img,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Change image
  void setImage(FXImage* img);

  /// Return image
  FXImage* getImage() const;

  /// Set the current alignment.
  void setAlignment(FXuint mode);

  /// Get the current alignment.
  FXuint getAlignment() const;

  /// Destroy
  virtual ~FXImageView();
  };


DECLARE_FXOBJECT_VIRTUALS(FXImageView)
DECLARE_FXID_VIRTUALS(FXImageView)
DECLARE_FXDRAWABLE_VIRTUALS(FXImageView)
DECLARE_FXWINDOW_VIRTUALS(FXImageView)
DECLARE_FXSCROLLAREA_VIRTUALS(FXImageView)

