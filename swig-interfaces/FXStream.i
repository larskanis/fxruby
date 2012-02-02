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

/// Stream data flow direction
enum FXStreamDirection {
  FXStreamDead=0,               /// Unopened stream
  FXStreamSave=1,               /// Saving stuff to stream
  FXStreamLoad=2                /// Loading stuff from stream
  };


/// Stream status codes
enum FXStreamStatus {
  FXStreamOK=0,                 /// OK
  FXStreamEnd=1,                /// Try read past end of stream
  FXStreamFull=2,               /// Filled up stream buffer or disk full
  FXStreamNoWrite=3,            /// Unable to open for write
  FXStreamNoRead=4,             /// Unable to open for read
  FXStreamFormat=5,             /// Stream format error
  FXStreamUnknown=6,            /// Trying to read unknown class
  FXStreamAlloc=7,              /// Alloc failed
  FXStreamFailure=8             /// General failure
  };


/// Stream seeking
enum FXWhence {
  FXFromStart=0,                /// Seek from start position
  FXFromCurrent=1,              /// Seek from current position
  FXFromEnd=2                   /// Seek from end position
  };


/*********************  Persistent Store Definition  *************************/

%rename("getPosition") FXStream::position() const;
%rename("eof?")        FXStream::eof() const;

/**
* A stream is a way to serialize data and objects into a byte stream.
* Each item of data that is saved or loaded from the stream may be byte-swapped,
* thus allowing little-endian machines to read data produced on big endian ones
* and vice-versa.
* Data is serialized exactly as-is.  There are no tags or other markers
* inserted into the stream; thus, the stream may be used to save or load arbitrary
* binary data.
* Objects derived from FXObjects may be serialized also; whenever a reference to an
* object is serialized, a table is consulted to determine if the same object has
* been encountered previously; if not, the object is added to the table and then
* its contents are serialized.  If the object has been encountered before, only a
* reference to the object is serialized.
* When loading back a serialized object, new instances are constructed using
* the default constructor, and subsequently the object's contents are loaded.
* A special container object may be passed in which is placed in the table
* as if it had been encountered before; this will cause only references to this
* object to be saved.  The container object is typically the top-level document
* object which manages all objects contained by it.  Additional objects may be
* added using addObject(); these will not be actually saved or loaded.
*/
class FXStream {
public:

  /**
   * Construct stream with given container object.  The container object
   * is an object that will itself not be saved to or loaded from the stream,
   * but which may be referenced by other objects.  These references will be
   * properly saved and restored.
   */
  %extend {
    FXStream(const FXObject* cont=NULL){
      return new FXRbStream(cont);
      }
  }

  /**
  * Open stream for reading (FXStreamLoad) or for writing (FXStreamSave).
  * An initial buffer size may be given, which must be at least 16 bytes.
  * If data is not NULL, it is expected to point to an external data buffer
  * of length size; otherwise stream will use an internally managed buffer.
  */
  bool open(FXStreamDirection save_or_load,FXuval size=8192,FXuchar* data=NULL);

  /// Get available buffer space
  FXuval getSpace() const;

  /// Set available buffer space
  void setSpace(FXuval sp);

  /// Get status code
  FXStreamStatus status() const;

  /// Return TRUE if at end of file or error
  bool eof() const;

  /// Set status code
  void setError(FXStreamStatus err);

  /// Obtain direction
  FXStreamDirection direction() const;

  /// Get parent object
  const FXObject* container() const;

  /// Get position
  FXlong position() const;

  /// Change swap bytes flag
  void swapBytes(bool s);

  /// Get swap bytes flag
  bool swapBytes() const;

  /**
  * Set stream to big endian mode if TRUE.  Byte swapping will
  * be enabled if the machine native byte order is not equal to
  * the desired byte order.
  */
  void setBigEndian(bool big);

  /**
  * Return TRUE if big endian mode.
  */
  bool isBigEndian() const;

  /// Destructor
  virtual ~FXStream();
  };


DECLARE_FXSTREAM_VIRTUALS(FXStream)

