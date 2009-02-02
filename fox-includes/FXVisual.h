/********************************************************************************
*                                                                               *
*                            V i s u a l   C l a s s                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXVisual.h 2343 2006-02-12 20:26:26Z lyle $                          *
********************************************************************************/
#ifndef FXVISUAL_H
#define FXVISUAL_H

#ifndef FXID_H
#include "FXId.h"
#endif

namespace FX {


/// Construction options for FXVisual class
enum FXVisualOptions {
  VISUAL_DEFAULT      = 0,            /// Default visual
  VISUAL_MONOCHROME   = 1,            /// Must be monochrome visual
  VISUAL_BEST         = 2,            /// Best (deepest) visual
  VISUAL_INDEXCOLOR   = 4,            /// Palette visual
  VISUAL_GRAYSCALE    = 8,            /// Gray scale visual
  VISUAL_TRUECOLOR    = 16,           /// Must be true color visual
  VISUAL_OWNCOLORMAP  = 32,           /// Allocate private colormap
  VISUAL_DOUBLEBUFFER = 64,           /// Double-buffered [FXGLVisual]
  VISUAL_STEREO       = 128,          /// Stereo [FXGLVisual]
  VISUAL_NOACCEL      = 256,          /// No hardware acceleration [for broken h/w]
  VISUAL_SWAP_COPY    = 512           /// Buffer swap by copying [FXGLVisual]
  };


/// Visual type
enum FXVisualType {
  VISUALTYPE_UNKNOWN,                 /// Undetermined visual type
  VISUALTYPE_MONO,                    /// Visual for drawing into 1-bpp surfaces
  VISUALTYPE_TRUE,                    /// True color
  VISUALTYPE_INDEX,                   /// Index [palette] color
  VISUALTYPE_GRAY                     /// Gray scale
  };


class FXApp;
class FXWindow;
class FXGLContext;
class FXGLCanvas;
class FXImage;
class FXIcon;
class FXBitmap;
class FXDCWindow;


/// Visual describes pixel format of a drawable
class FXAPI FXVisual : public FXId {
  FXDECLARE(FXVisual)
  friend class FXApp;
  friend class FXWindow;
  friend class FXImage;
  friend class FXIcon;
  friend class FXBitmap;
  friend class FXDCWindow;
  friend class FXGLCanvas;
  friend class FXGLContext;
protected:
  FXuint        flags;                  // Visual flags
  FXuint        hint;                   // Depth Hint
  FXuint        depth;                  // Visual depth, significant bits/pixel
  FXuint        numred;                 // Number of reds
  FXuint        numgreen;               // Number of greens
  FXuint        numblue;                // Number of blues
  FXuint        numcolors;              // Total number of colors
  FXuint        maxcolors;              // Maximum number of colors
  FXVisualType  type;                   // Visual type
  void         *info;                   // Opaque data
  void         *visual;                 // Application visual/pixel format
  FXID          colormap;               // Color map, if any
  FXbool        freemap;                // We allocated the map
#ifndef WIN32
protected:
  void         *gc;                     // Drawing GC
  void         *scrollgc;               // Scrolling GC
  FXPixel       rpix[16][256];          // Mapping from red -> pixel
  FXPixel       gpix[16][256];          // Mapping from green -> pixel
  FXPixel       bpix[16][256];          // Mapping from blue -> pixel
  FXPixel       lut[256];               // Color lookup table
protected:
  void* setupgc(FXbool);
  void setuptruecolor();
  void setupdirectcolor();
  void setuppseudocolor();
  void setupstaticcolor();
  void setupgrayscale();
  void setupstaticgray();
  void setuppixmapmono();
  void setupcolormap();
#endif
protected:
  FXVisual();
private:
  FXVisual(const FXVisual&);
  FXVisual &operator=(const FXVisual&);
public:

  /// Construct default visual
  FXVisual(FXApp* a,FXuint flgs,FXuint d=32);

  /// Get visual type
  FXVisualType getType() const { return type; }

  /// Get visual info
  void* getInfo() const { return info; }

  /// Get visual or pixel format
  void* getVisual() const { return visual; }

  /// Create visual
  virtual void create();

  /// Detach visual
  virtual void detach();

  /// Destroy visual
  virtual void destroy();

  /// Get flags (see FXVisualOptions)
  FXuint getFlags() const { return flags; }

  /// Get depth, i.e. number of significant bits in color representation
  FXuint getDepth() const { return depth; }

  /// Get number of colors
  FXuint getNumColors() const { return numcolors; }

  /// Get number of reds
  FXuint getNumRed() const { return numred; }

  /// Get number of greens
  FXuint getNumGreen() const { return numgreen; }

  /// Get number of blues
  FXuint getNumBlue() const { return numblue; }

  /// Get device pixel value for color
  FXPixel getPixel(FXColor clr);

  /// Get color value for device pixel value
  FXColor getColor(FXPixel pix);

  /// Set maximum number of colors to allocate
  void setMaxColors(FXuint maxcols);

  /// Get maximum number of colors
  FXuint getMaxColors() const { return maxcolors; }

  /// Save visual information to a stream
  virtual void save(FXStream& store) const;

  /// Load visual information from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXVisual();
  };

}

#endif
