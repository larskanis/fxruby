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
* $Id: FXVisual.h 2869 2008-05-30 20:08:44Z lyle $                          *
********************************************************************************/
#ifndef FXVISUAL_H
#define FXVISUAL_H

#ifndef FXID_H
#include "FXId.h"
#endif

namespace FX {


class FXWindow;
class FXGLContext;
class FXGLCanvas;
class FXImage;
class FXIcon;
class FXBitmap;
class FXDCWindow;


/// Construction options for FXVisual class
enum {
  VISUAL_DEFAULT       = 0,     /// Default visual
  VISUAL_MONO          = 1,     /// Must be monochrome visual
  VISUAL_GRAY          = 2,     /// Gray scale visual
  VISUAL_INDEX         = 4,     /// Palette visual
  VISUAL_COLOR         = 8,     /// Must be true color visual
  VISUAL_BEST          = 16,    /// Best (deepest) visual
  VISUAL_FORCE         = 32,    /// Force given visual id (X11)
  VISUAL_OWN_COLORMAP  = 64,    /// Allocate private colormap
  VISUAL_WINDOW        = 128,   /// Draw to window [GL Visual]
  VISUAL_IMAGE         = 256,   /// Draw to image [GL Visual]
  VISUAL_BUFFER        = 512,   /// Draw to buffer [GL Visual]
  VISUAL_DOUBLE_BUFFER = 1024,  /// Double buffered [GL Visual]
  VISUAL_STEREO        = 2048,  /// Stereo buffered [GL Visual]
  VISUAL_NO_ACCEL      = 4096,  /// No hardware acceleration [GL Visual]
  VISUAL_SWAP_COPY     = 8192,  /// Buffer swap by copying [GL Visual]
  VISUAL_FLOAT         = 16384  /// Floating point buffers [GL Visual]
  };


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
  void         *visual;                 // Application visual/pixel format
  FXID          colormap;               // Color map, if any
  FXuint        maxcolors;              // Maximum number of colors
  FXuint        numcolors;              // Total number of colors
  FXuint        numred;                 // Number of reds
  FXuint        numgreen;               // Number of greens
  FXuint        numblue;                // Number of blues
  FXuint        depth;                  // Visual depth, significant bits/pixel
  FXuint        flags;                  // Visual flags
  FXuint        hint;                   // Hint value
  FXuchar       type;                   // Visual type
  FXbool        freemap;                // We allocated the map
#ifndef WIN32
protected:
  void         *scrollgc;               // Scrolling GC
  void         *gc;                     // Drawing GC
  FXPixel       rpix[16][256];          // Mapping from red -> pixel
  FXPixel       gpix[16][256];          // Mapping from green -> pixel
  FXPixel       bpix[16][256];          // Mapping from blue -> pixel
  FXPixel       lut[256];               // Color lookup table
protected:
  void setuptruecolor();
  void setupdirectcolor();
  void setuppseudocolor();
  void setupstaticcolor();
  void setupgrayscale();
  void setupstaticgray();
  void setuppixmapmono();
  void setupcolormap();
  void* setupgc(FXbool);
#endif
protected:
  FXVisual();
private:
  FXVisual(const FXVisual&);
  FXVisual &operator=(const FXVisual&);
public:

  /// Visual types
  enum {
    Unknown,    /// Undetermined visual type
    Mono,       /// Monochrome 1 bit/pixel
    Gray,       /// Gray scale color
    Index,      /// Index color
    Color       /// True color
    };

public:

  /// Construct visual
  FXVisual(FXApp* a,FXuint flgs=VISUAL_DEFAULT,FXuint hnt=32);

  /// Get visual type
  FXuchar getType() const { return type; }

  /// Get visual or pixel format
  void* getVisual() const { return visual; }

  /// Create visual
  virtual void create();

  /// Detach visual
  virtual void detach();

  /// Destroy visual
  virtual void destroy();

  /// Change option flags
  void setFlags(FXuint flgs){ flags=flgs; }

  /// Get option flags
  FXuint getFlags() const { return flags; }

  /// Change hints
  void setHint(FXuint hnt){ hint=hnt; }

  /// Get hints
  FXuint getHint() const { return hint; }

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
