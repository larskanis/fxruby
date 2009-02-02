/********************************************************************************
*                                                                               *
*                        I / O   D e v i c e   C l a s s                        *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXIO.h 2344 2006-02-12 21:19:36Z lyle $                               *
********************************************************************************/
#ifndef FXIO_H
#define FXIO_H



namespace FX {


/**
* FXIO manipulates a handle to an abstract i/o device.
* The various subclasses of FXIO perform i/o on files, sockets,
* pipes, and possibly other devices.
*/
class FXAPI FXIO {
protected:
  FXInputHandle device;         // Device (file/pipe/socket/whatever)
  FXuint        access;         // Access being performed
private:
  FXIO(const FXIO&);
  FXIO &operator=(const FXIO&);
public:

  /// File modes
  enum {

    /// Permissions
    OtherRead      = 0x00004,   /// Others have read permission
    OtherWrite     = 0x00002,   /// Others have write permisson
    OtherExec      = 0x00001,   /// Others have execute permission
    OtherReadWrite = 0x00006,   /// Others have read and write permission
    OtherFull      = 0x00007,   /// Others have full access

    GroupRead      = 0x00020,   /// Group has read permission
    GroupWrite     = 0x00010,   /// Group has write permission
    GroupExec      = 0x00008,   /// Group has execute permission
    GroupReadWrite = 0x00030,   /// Group has read and write permission
    GroupFull      = 0x00038,   /// Group has full access

    OwnerRead      = 0x00100,   /// Owner has read permission
    OwnerWrite     = 0x00080,   /// Owner has write permission
    OwnerExec      = 0x00040,   /// Owner has execute permission
    OwnerReadWrite = 0x00180,   /// Owner has read and write permission
    OwnerFull      = 0x001C0,   /// Owner has full access

    /// Other flags
    Hidden         = 0x00200,   /// Hidden file
    Directory      = 0x00400,   /// Is directory
    File           = 0x00800,   /// Is regular file
    SymLink        = 0x01000,   /// Is symbolic link

    /// Special mode bits
    SetUser        = 0x02000,   /// Set user id
    SetGroup       = 0x04000,   /// Set group id
    Sticky         = 0x08000,   /// Sticky bit

    /// Device special files
    Character      = 0x10000,   /// Character device
    Block          = 0x20000,   /// Block device
    Socket         = 0x40000,   /// Socket device
    Fifo           = 0x80000    /// Fifo device
    };

  /// Access modes
  enum {

    /// Basic access options
    NoAccess    =  0,                           /// No access
    ReadOnly    =  1,                           /// Open for reading
    WriteOnly   =  2,                           /// Open for writing
    ReadWrite   =  3,                           /// Open for read and write
    Append      =  4,                           /// Open for append
    Truncate    =  8,                           /// Truncate to zero when writing
    Create      = 16,                           /// Create if it doesn't exist
    Exclusive   = 32,                           /// Fail if trying to create a file which already exists
    NonBlocking = 64,                           /// Non-blocking i/o

    /// Convenience access options
    Reading     = ReadOnly,                     /// Normal options for reading
    Writing     = ReadWrite|Create|Truncate     /// Normal options for writing
    };

  /// Positioning modes
  enum {
    Begin   = 0,                /// Position from the begin (default)
    Current = 1,                /// Position relative to current position
    End     = 2                 /// Position from the end
    };

public:

  /// Construct
  FXIO();

  /// Open device with access mode and handle
  virtual bool open(FXInputHandle handle,FXuint mode);

  /// Return true if open
  virtual bool isOpen() const;

  /// Return access mode
  FXuint mode() const { return access; }

  /// Return handle
  FXInputHandle handle() const { return device; }

  /// Attach existing device handle
  virtual void attach(FXInputHandle handle,FXuint mode);

  /// Detach device handle
  virtual void detach();

  /// Get current file position
  virtual FXlong position() const;

  /// Change file position, returning new position from start
  virtual FXlong position(FXlong offset,FXuint from=FXIO::Begin);

  /// Read block of bytes, returning number of bytes read
  virtual FXival readBlock(void* data,FXival count);

  /// Write block of bytes, returning number of bytes written
  virtual FXival writeBlock(const void* data,FXival count);

  /// Truncate file
  virtual FXlong truncate(FXlong size);

  /// Flush to disk
  virtual bool flush();

  /// Test if we're at the end
  virtual bool eof();

  /// Return size of i/o device
  virtual FXlong size();

  /// Close handle
  virtual bool close();

  /// Destroy and close
  virtual ~FXIO();
  };

}

#endif
