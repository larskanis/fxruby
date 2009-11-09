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

/// File Store Definition
class FXFileStream : public FXStream {
public:

  /// Create file store
  %extend {
    FXFileStream(const FXObject* cont=NULL){
      return new FXRbFileStream(cont);
      }
    }

  /**
   * Open binary data file stream; allocate a buffer of the given size
   * for the file I/O; the buffer must be at least 16 bytes.
   */
  bool open(const FXString& filename,FXStreamDirection save_or_load,FXuval size=8192);

  /// Get position
  FXlong position() const;

  /// Destructor
  virtual ~FXFileStream();
  };


DECLARE_FXSTREAM_VIRTUALS(FXFileStream)

