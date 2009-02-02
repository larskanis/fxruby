/********************************************************************************
*                                                                               *
*                           D r a w a b l e   A r e a                           *
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
* $Id: FXDrawable.h 2725 2007-11-16 16:57:54Z lyle $                        *
********************************************************************************/
#ifndef FXDRAWABLE_H
#define FXDRAWABLE_H

#ifndef FXID_H
#include "FXId.h"
#endif

namespace FX {


class FXVisual;


/**
* Drawable is an abstract base class for any surface that can be
* drawn upon, such as a FXWindow, or FXImage.
*/
class FXAPI FXDrawable : public FXId {
  FXDECLARE_ABSTRACT(FXDrawable)
  friend class FXDC;
  friend class FXDCWindow;
  friend class FXGLContext;
protected:
  FXVisual     *visual;                 // Visual for this window
  FXint         width;                  // Width
  FXint         height;                 // Height
protected:
  FXDrawable();
  FXDrawable(FXApp* a,FXint w,FXint h);
private:
  FXDrawable(const FXDrawable&);
  FXDrawable &operator=(const FXDrawable&);
#ifdef WIN32
  virtual FXID GetDC() const { return NULL; }
  virtual int ReleaseDC(FXID) const { return 0; }
#endif
public:

  /// Width of drawable
  FXint getWidth() const { return width; }

  /// Height of drawable
  FXint getHeight() const { return height; }

  /// Get the visual
  FXVisual* getVisual() const { return visual; }

  /// Change visual
  void setVisual(FXVisual* vis);

  /// Resize drawable to the specified width and height
  virtual void resize(FXint w,FXint h);

  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);

  /// Cleanup
  virtual ~FXDrawable();
  };

}

#endif
