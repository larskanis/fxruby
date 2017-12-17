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

class FXFont;


/// Visual describes pixel format of a drawable
class FXGLVisual : public FXVisual {
public:
  %extend {
    /// Construct default visual
    FXGLVisual(FXApp* a,FXuint flags){
      return new FXRbGLVisual(a,flags);
      }
    }

  /**
   * Test if OpenGL is possible, and what level is supported.
   * Because of remote display capability, the display server may
   * support a different level of OpenGL than the client; it may
   * even support no OpenGL at all!  This function returns the lesser
   * of the client support level and the display server support level.
   */
  %extend {
    static VALUE supported(FXApp* application){
      int major,minor;
      FXbool answer=FXGLVisual::supported(application,major,minor);
      return rb_ary_new3(3,answer?Qtrue:Qfalse,INT2NUM(major),INT2NUM(minor));
      }
  }

  /// Get sizes for bit-planes
  FXint getRedSize() const;

  FXint getGreenSize() const;

  FXint getBlueSize() const;

  FXint getAlphaSize() const;

  FXint getDepthSize() const;

  FXint getStencilSize() const;

  FXint getAccumRedSize() const;

  FXint getAccumGreenSize() const;

  FXint getAccumBlueSize() const;

  FXint getAccumAlphaSize() const;

  /// Set sizes for bit-planes
  void setRedSize(FXint rs);

  void setGreenSize(FXint gs);

  void setBlueSize(FXint bs);

  void setAlphaSize(FXint as);

  void setDepthSize(FXint ds);

  void setStencilSize(FXint ss);

  void setAccumRedSize(FXint rs);

  void setAccumGreenSize(FXint gs);

  void setAccumBlueSize(FXint bs);

  void setAccumAlphaSize(FXint as);

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

  /// Does it swap by copying instead of flipping buffers?
  FXbool isBufferSwapCopy() const;

  /// Destructor
  virtual ~FXGLVisual();
  };


DECLARE_FXOBJECT_VIRTUALS(FXGLVisual)
DECLARE_FXID_VIRTUALS(FXGLVisual)


/// Create a display list of bitmaps from font glyphs in a font
void glUseFXFont(FXFont* font,int first,int count,int list);
