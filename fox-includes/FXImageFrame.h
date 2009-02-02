/********************************************************************************
*                                                                               *
*                       I m a g e   F r a m e   W i d g e t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2002 by H. J. Daniel III. All Rights Reserved.             *
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
* $Id: FXImageFrame.h 1166 2002-12-19 18:11:19Z lyle $                       *
********************************************************************************/
#ifndef FXIMAGEFRAME_H
#define FXIMAGEFRAME_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/**
* The image frame is a simple frame widget displaying
* an image; the image is not owned by the image frame so
* it must be explicitly deleted elsewhere.
*/
class FXAPI FXImageFrame : public FXFrame {
  FXDECLARE(FXImageFrame)
protected:
  FXImage* image;       // The image being displayed
protected:
  FXImageFrame();
private:
  FXImageFrame(const FXImageFrame&);
  FXImageFrame &operator=(const FXImageFrame&);
public:
  long onPaint(FXObject*,FXSelector,void* ptr);
public:

  /// Construct image frame and pass it an image
  FXImageFrame(FXComposite* p,FXImage *img,FXuint opts=FRAME_SUNKEN|FRAME_THICK,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0);

  /// Create window
  virtual void create();

  /// Get default width
  virtual FXint getDefaultWidth();

  /// Get default height
  virtual FXint getDefaultHeight();

  /// Change the image being displayed
  void setImage(FXImage* img);

  /// Return the current image
  FXImage* getImage() const { return image; }

  /// Set the current justification mode.
  void setJustify(FXuint mode);

  /// Get the current justification mode.
  FXuint getJustify() const;

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy the widget, but do not destroy the image
  virtual ~FXImageFrame();
  };

}


#endif
