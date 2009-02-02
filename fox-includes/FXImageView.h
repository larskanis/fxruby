/********************************************************************************
*                                                                               *
*                       I m a g e   V i e w   W i d g e t                       *
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
* $Id: FXImageView.h 2336 2006-02-04 15:20:33Z lyle $                       *
********************************************************************************/
#ifndef FXIMAGEVIEW_H
#define FXIMAGEVIEW_H

#ifndef FXSCROLLAREA_H
#include "FXScrollArea.h"
#endif

namespace FX {


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
class FXAPI FXImageView : public FXScrollArea {
  FXDECLARE(FXImageView)
protected:
  FXImage *image;         // Image to view
  FXint    grabx;         // Grab point x
  FXint    graby;         // Grab point y
protected:
  FXImageView();
private:
  FXImageView(const FXImageView&);
  FXImageView &operator=(const FXImageView&);
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
  FXImageView(FXComposite* p,FXImage* img=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Perform layout
  virtual void layout();

  /// Image view widget can receive focus
  virtual bool canFocus() const;

  /// Return the width of the contents
  virtual FXint getContentWidth();

  /// Return the height of the contents
  virtual FXint getContentHeight();

  /// Change image
  void setImage(FXImage* img);

  /// Return image
  FXImage* getImage() const { return image; }

  /// Set the current alignment.
  void setAlignment(FXuint mode);

  /// Get the current alignment.
  FXuint getAlignment() const;

  /// Save list to a stream
  virtual void save(FXStream& store) const;

  /// Load list from a stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXImageView();
  };

}

#endif
