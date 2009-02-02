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
  
%rename("visualType") FXVisual::getType() const;
%rename("flags=")     FXVisual::setFlags(FXuint);
%rename("flags")      FXVisual::getFlags() const;
%rename("hints=")     FXVisual::setHint(FXuint);
%rename("hints")      FXVisual::getHint() const;

%ignore FXVisual::getVisual() const;

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

// Backwards compatibility with FXRuby 1.6
%constant FXuint VISUAL_MONOCHROME = VISUAL_MONO;
%constant FXuint VISUAL_GRAYSCALE = VISUAL_GRAY;
%constant FXuint VISUAL_INDEXCOLOR = VISUAL_INDEX;
%constant FXuint VISUAL_TRUECOLOR = VISUAL_COLOR;
%constant FXuint VISUAL_OWNCOLORMAP = VISUAL_OWN_COLORMAP;
%constant FXuint VISUAL_DOUBLEBUFFER = VISUAL_DOUBLE_BUFFER;
%constant FXuint VISUAL_NOACCEL = VISUAL_NO_ACCEL;

%constant FXuint VISUALTYPE_UNKNOWN = FXVisual::Unknown;
%constant FXuint VISUALTYPE_MONO = FXVisual::Mono;
%constant FXuint VISUALTYPE_TRUE = FXVisual::Color;
%constant FXuint VISUALTYPE_INDEX = FXVisual::Index;
%constant FXuint VISUALTYPE_GRAY = FXVisual::Gray;


/// Visual describes pixel format of a drawable
class FXVisual : public FXId {
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

  /// Construct default visual
  %extend {
    FXVisual(FXApp* a,FXuint flgs=VISUAL_DEFAULT,FXuint hnt=32){
      return new FXRbVisual(a,flgs,hnt);
      }
    }

  /// Get visual type
  FXuchar getType() const;

  /// Get visual or pixel format
  void* getVisual() const;

  /// Change flags
  void setFlags(FXuint flgs);
  
  /// Get flags (see FXVisualOptions)
  FXuint getFlags() const;

  /// Change hints
  void setHint(FXuint hnt);
  
  /// Get hints
  FXuint getHint() const;
  
  /// Get depth, i.e. number of significant bits in color representation
  FXuint getDepth() const;

  /// Get number of colors
  FXuint getNumColors() const;

  /// Get number of reds
  FXuint getNumRed() const;

  /// Get number of greens
  FXuint getNumGreen() const;

  /// Get number of blues
  FXuint getNumBlue() const;

  /// Get device pixel value for color
  FXPixel getPixel(FXColor clr);

  /// Get color value for device pixel value
  FXColor getColor(FXPixel pix);

  /// Set maximum number of colors to allocate
  void setMaxColors(FXuint maxcols);

  /// Get maximum number of colors
  FXuint getMaxColors() const;

  /// Destructor
  virtual ~FXVisual();
  };


DECLARE_FXOBJECT_VIRTUALS(FXVisual)
DECLARE_FXID_VIRTUALS(FXVisual)

%{
static swig_type_info *FXVisual_dynamic_cast(void **ptr) {
    FXVisual **ppVisual = reinterpret_cast<FXVisual **>(ptr);
    FXGLVisual *pGLVisual=dynamic_cast<FXGLVisual*>(*ppVisual);
    if(pGLVisual){
      *ptr=reinterpret_cast<void*>(pGLVisual);
      return SWIG_TypeQuery("FXGLVisual *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXVisual, FXVisual_dynamic_cast);

