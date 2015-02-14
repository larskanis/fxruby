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

%rename("visualType") FXVisual::getType() const;

%ignore FXVisual::getInfo() const;
%ignore FXVisual::getVisual() const;

/// Visual describes pixel format of a drawable
class FXVisual : public FXId {
public:

  /// Construct default visual
  %extend {
    FXVisual(FXApp* a,FXuint flgs,FXuint d=32){
      return new FXRbVisual(a,flgs,d);
      }
    }

  /// Get visual type
  FXVisualType getType() const;

  /// Get visual info
  void* getInfo() const;

  /// Get visual or pixel format
  void* getVisual() const;

  /// Get flags (see FXVisualOptions)
  FXuint getFlags() const;

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

