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

/***********************************************************************
 * $Id: FXMemoryBuffer.i 2062 2005-01-29 16:54:34Z lyle $
 ***********************************************************************/

class FXMemoryBuffer {
public:
  // Create an memory buffer object
  FXMemoryBuffer(FXColor *data,FXuint size);

  // Returns the size (in bytes)
  FXuint getSize() const;

  %extend {
    // Returns the data as an array of Integers
    VALUE getData() const {
      FXColor* data = self->getData();
      if (data) {
        FXuint size = self->getSize();
        VALUE ary = rb_ary_new2(size);
        for (int i = 0; i < size; i++)
          rb_ary_store(ary, i, UINT2NUM(data[i]));
        return ary;
        }
      else {
        return Qnil;
        }
      }

    // Indexed access
    FXColor __getitem__(FXuint i) const {
      return self->getData()[i];
      }

    FXColor __setitem__(FXuint i,FXColor value){
      self->getData()[i] = value;
      return value;
      }
  }

  // Destructor
  ~FXMemoryBuffer();
  };
