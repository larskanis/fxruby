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


/// TGA Image class
class FXTGAImage : public FXImage {
public:
  %extend {
    static VALUE fileExt() {
      return to_ruby(FXTGAImage::fileExt);
      }

    static VALUE mimeType() {
      return to_ruby(FXTGAImage::mimeType);
      }
    }
public:

  /// Construct an image from memory stream formatted in TGA format
  %extend {
    FXTGAImage(FXApp *a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1){
      return new FXRbTGAImage(a,pix,opts,w,h);
      }
    }

  /// Destroy
  virtual ~FXTGAImage();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTGAImage)
DECLARE_FXID_VIRTUALS(FXTGAImage)
DECLARE_FXDRAWABLE_VIRTUALS(FXTGAImage)
DECLARE_FXIMAGE_VIRTUALS(FXTGAImage)

