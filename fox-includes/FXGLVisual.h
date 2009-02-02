/********************************************************************************
*                                                                               *
*                            V i s u a l   C l a s s                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2008 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLVisual.h 2869 2008-05-30 20:08:44Z lyle $                        *
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
  FXuchar redSize;              // Red bits
  FXuchar greenSize;            // Green depth
  FXuchar blueSize;             // Blue bits
  FXuchar alphaSize;            // Alpha bits
  FXuchar depthSize;            // Depth bits
  FXuchar stencilSize;          // Stencil bits
  FXuchar multiSamples;         // Multi-sampling
  FXuchar accumRedSize;         // Red accu buffer bits
  FXuchar accumGreenSize;       // Green accu buffer bits
  FXuchar accumBlueSize;        // Blue accu buffer bits
  FXuchar accumAlphaSize;       // Alpha accu buffer bits
  FXuchar actualRedSize;        // Actual Red bits
  FXuchar actualGreenSize;      // Actual Green depth
  FXuchar actualBlueSize;       // Actual Blue bits
  FXuchar actualAlphaSize;      // Actual Alpha bits
  FXuchar actualDepthSize;      // Actual Depth bits
  FXuchar actualStencilSize;    // Actual Stencil bits
  FXuchar actualMultiSamples;   // Actual multi-sampling
  FXuchar actualAccumRedSize;   // Actual Red accu buffer bits
  FXuchar actualAccumGreenSize; // Actual Green accu buffer bits
  FXuchar actualAccumBlueSize;  // Actual Blue accu buffer bits
  FXuchar actualAccumAlphaSize; // Actual Alpha accu buffer bits
  FXbool  doubleBuffer;
  FXbool  stereoBuffer;
  FXbool  accelerated;
  FXbool  copying;
protected:
  FXGLVisual();
private:
  FXGLVisual(const FXGLVisual&);
  FXGLVisual &operator=(const FXGLVisual&);
public:

  /// Construct default visual
  FXGLVisual(FXApp* a,FXuint flgs=VISUAL_DOUBLE_BUFFER|VISUAL_WINDOW);

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
  FXint getMultiSamples() const { return multiSamples; }
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
  void setMultiSamples(FXint ms){ multiSamples=ms; }
  void setAccumRedSize(FXint rs){ accumRedSize=rs; }
  void setAccumGreenSize(FXint gs){ accumGreenSize=gs; }
  void setAccumBlueSize(FXint bs){ accumBlueSize=bs; }
  void setAccumAlphaSize(FXint as){ accumAlphaSize=as; }

  /// Get ACTUAL sizes for bit-planes
  FXint getActualRedSize() const { return actualRedSize; }
  FXint getActualGreenSize() const { return actualGreenSize; }
  FXint getActualBlueSize() const { return actualBlueSize; }
  FXint getActualAlphaSize() const { return actualAlphaSize; }
  FXint getActualDepthSize() const { return actualDepthSize; }
  FXint getActualStencilSize() const { return actualStencilSize; }
  FXint getActualMultiSamples() const { return actualMultiSamples; }
  FXint getActualAccumRedSize() const { return actualAccumRedSize; }
  FXint getActualAccumGreenSize() const { return actualAccumGreenSize; }
  FXint getActualAccumBlueSize() const { return actualAccumBlueSize; }
  FXint getActualAccumAlphaSize() const { return actualAccumAlphaSize; }

  /// Is it double buffered?
  FXbool isDoubleBuffer() const { return doubleBuffer; }

  /// Is it stereo?
  FXbool isStereo() const { return stereoBuffer; }

  /// Is it hardware-accelerated?
  FXbool isAccelerated() const { return accelerated; }

  /// Does it swap by copying instead of flipping buffers
  FXbool isBufferSwapCopy() const { return copying; }

  /// Test if if OpenGL is supported.
  static FXbool hasOpenGL(FXApp* application);

  /// Save visual info to a stream
  virtual void save(FXStream& store) const;

  /// Load visual info to a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXGLVisual();
  };

}

#endif
