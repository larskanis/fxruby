/********************************************************************************
*                                                                               *
*                            V i s u a l   C l a s s                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2004 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLVisual.h 1889 2004-05-26 03:13:01Z lyle $                        *
********************************************************************************/
#ifndef FXGLVISUAL_H
#define FXGLVISUAL_H

#ifndef FXVISUAL_H
#include "FXVisual.h"
#endif

namespace FX {


class FXFont;
class FXWindow;
class FXImage;
class FXIcon;
class FXBitmap;
class FXDCWindow;
class FXGLCanvas;


/// Visual describes pixel format of a drawable
class FXAPI FXGLVisual : public FXVisual {
  FXDECLARE(FXGLVisual)
  friend class FXWindow;
  friend class FXImage;
  friend class FXIcon;
  friend class FXBitmap;
  friend class FXDCWindow;
  friend class FXGLCanvas;
protected:
  FXint        redSize;             // Desired #bits for red
  FXint        greenSize;           // Desired #bits for green
  FXint        blueSize;            // Desired #bits for blue
  FXint        alphaSize;           // Desired #bits for alpha
  FXint        depthSize;           // Desired #bits for Z
  FXint        stencilSize;         // Desired #bits for stencil
  FXint        accumRedSize;        // Desired #bits for accum red
  FXint        accumGreenSize;      // Desired #bits for accum green
  FXint        accumBlueSize;       // Desired #bits for accum blue
  FXint        accumAlphaSize;      // Desired #bits for accum alpha
protected:
  FXGLVisual();
private:
  FXGLVisual(const FXGLVisual&);
  FXGLVisual &operator=(const FXGLVisual&);
public:

  /// Construct default visual
  FXGLVisual(FXApp* a,FXuint flags);

  /**
  * Test if OpenGL is possible, and what level is supported.
  * Because of remote display capability, the display server may
  * support a different level of OpenGL than the client; it may
  * even support no OpenGL at all!  This function returns the lesser
  * of the client support level and the display server support level.
  */
  static FXbool supported(FXApp* application,int& major,int& minor);

  /// Create visual
  virtual void create();

  /// Detach visual
  virtual void detach();

  /// Destroy visual
  virtual void destroy();

  /// Get sizes for bit-planes
  FXint getRedSize() const { return redSize; }
  FXint getGreenSize() const { return greenSize; }
  FXint getBlueSize() const { return blueSize; }
  FXint getAlphaSize() const { return alphaSize; }
  FXint getDepthSize() const { return depthSize; }
  FXint getStencilSize() const { return stencilSize; }
  FXint getAccumRedSize() const { return accumRedSize; }
  FXint getAccumGreenSize() const { return accumGreenSize; }
  FXint getAccumBlueSize() const { return accumBlueSize; }
  FXint getAccumAlphaSize() const { return accumAlphaSize; }

  /// Set sizes for bit-planes
  void setRedSize(FXint rs){ redSize=rs; }
  void setGreenSize(FXint gs){ greenSize=gs; }
  void setBlueSize(FXint bs){ blueSize=bs; }
  void setAlphaSize(FXint as){ alphaSize=as; }
  void setDepthSize(FXint ds){ depthSize=ds; }
  void setStencilSize(FXint ss){ stencilSize=ss; }
  void setAccumRedSize(FXint rs){ accumRedSize=rs; }
  void setAccumGreenSize(FXint gs){ accumGreenSize=gs; }
  void setAccumBlueSize(FXint bs){ accumBlueSize=bs; }
  void setAccumAlphaSize(FXint as){ accumAlphaSize=as; }

  /// Get ACTUAL sizes for bit-planes
  FXint getActualRedSize() const;
  FXint getActualGreenSize() const;
  FXint getActualBlueSize() const;
  FXint getActualAlphaSize() const;
  FXint getActualDepthSize() const;
  FXint getActualStencilSize() const;
  FXint getActualAccumRedSize() const;
  FXint getActualAccumGreenSize() const;
  FXint getActualAccumBlueSize() const;
  FXint getActualAccumAlphaSize() const;

  /// Is it double buffered?
  FXbool isDoubleBuffer() const;

  /// Is it stereo?
  FXbool isStereo() const;

  /// Is it hardware-accelerated?
  FXbool isAccelerated() const;

  /// Does it swap by copying instead of flipping buffers
  FXbool isBufferSwapCopy() const;

  /// Save visual info to a stream
  virtual void save(FXStream& store) const;

  /// Load visual info to a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXGLVisual();
  };


/// Create a display list of bitmaps from font glyphs in a font
extern FXAPI void glUseFXFont(FXFont* font,int first,int count,int list);

}

#endif
