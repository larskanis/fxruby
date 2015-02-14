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

/// Memory Store Definition
class FXMemoryStream : public FXStream {
public:

  /// Create memory store
  %extend {
    FXMemoryStream(const FXObject* cont=NULL){
      return new FXRbMemoryStream(cont);
      }

    /// Open memory store
    bool open(FXStreamDirection save_or_load,VALUE str){
      FXuval size=0;
      FXuchar *data=0;
      if(!NIL_P(str)){
        size=RSTRING_LEN(str);
        data=reinterpret_cast<FXuchar*>(StringValuePtr(str));
        return self->open(save_or_load,size,data);
        }
      else{
        return self->open(save_or_load,data);
        }
      }

    // Take buffer away from stream
    VALUE takeBuffer() {
      FXuchar* buffer;
      FXuval sp;
      self->takeBuffer(buffer,sp);
      VALUE result=rb_str_new(const_cast<const char *>(reinterpret_cast<char*>(buffer)),sp);
      FXFREE(&buffer);
      return result;
      }

    /// Give buffer to stream
    void giveBuffer(VALUE str){
      FXuchar* copy = NULL;
      Check_Type(str,T_STRING);
      FXuchar* buffer=reinterpret_cast<FXuchar*>(StringValuePtr(str));
      FXuval sp=RSTRING_LEN(str);
      if( FXMALLOC(&copy, FXuchar *, sp)) {
        memcpy(copy, buffer, sp);
        self->giveBuffer(copy,sp);
        }
      }
  }

  /// Get position
  FXlong position() const;

  /// Destructor
  virtual ~FXMemoryStream();
  };

