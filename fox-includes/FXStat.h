/********************************************************************************
*                                                                               *
*                        F i l e   S t a t i s t i c s                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXStat.h,v 1.33 2009/01/06 13:07:27 fox Exp $                            *
********************************************************************************/
#ifndef FXSTAT_H
#define FXSTAT_H


namespace FX {


class FXFile;


/// Statistics about a file or directory
class FXAPI FXStat {
  friend class FXFile;
private:
  FXuint  modeFlags;            /// Mode bits
  FXuint  userNumber;           /// User number
  FXuint  groupNumber;          /// Group number
  FXuint  linkCount;            /// Number of links
  FXTime  createTime;           /// Create time (ns)
  FXTime  accessTime;           /// Access time (ns)
  FXTime  modifyTime;           /// Modify time (ns)
  FXlong  fileVolume;           /// File volume (device)
  FXlong  fileIndex;            /// File index (inode)
  FXlong  fileSize;             /// File size
public:

  /// Get statistics of the file into the stat buffer info
  static FXbool statFile(const FXString& file,FXStat& info);

  /// Get statistice of the link into the stat buffer info
  static FXbool statLink(const FXString& file,FXStat& info);

  /// Get statistics of already open file into stat buffer info
  static FXbool stat(const FXFile& file,FXStat& info);

  /// Return the mode flags for this file
  FXuint mode() const { return modeFlags; }

  /// Return file size in bytes
  FXlong size() const { return fileSize; }

  /// Return user number
  FXuint user() const { return userNumber; }

  /// Return group number
  FXuint group() const { return groupNumber; }

  /// Return number of links to file
  FXuint links() const { return linkCount; }

  /// Return file volume number
  FXlong volume() const { return fileVolume; }

  /// Return file index number
  FXlong index() const { return fileIndex; }

  /// Return time when last modified, in nanoseconds
  FXTime modified() const { return modifyTime; }

  /// Return time when last accessed, in nanoseconds
  FXTime accessed() const { return accessTime; }

  /// Return time when file was created, in nanoseconds
  FXTime created() const { return createTime; }

  /// Return true if it is a hidden file (Windows-only)
  FXbool isHidden() const;

  /// Return true if it is a regular file
  FXbool isFile() const;

  /// Return true if it is a link
  FXbool isLink() const;

  /// Return true if character device
  FXbool isCharacter() const;

  /// Return true if block device
  FXbool isBlock() const;

  /// Return true if socket device
  FXbool isSocket() const;

  /// Return true if fifo (pipe) device
  FXbool isFifo() const;

  /// Return true if input path is a directory
  FXbool isDirectory() const;

  /// Return true if file is readable
  FXbool isReadable() const;

  /// Return true if file is writable
  FXbool isWritable() const;

  /// Return true if file is executable
  FXbool isExecutable() const;

  /// Return true if owner has read-write-execute permissions
  FXbool isOwnerReadWriteExecute() const;

  /// Return true if owner has read permissions
  FXbool isOwnerReadable() const;

  /// Return true if owner has write permissions
  FXbool isOwnerWritable() const;

  /// Return true if owner has execute permissions
  FXbool isOwnerExecutable() const;

  /// Return true if group has read-write-execute permissions
  FXbool isGroupReadWriteExecute() const;

  /// Return true if group has read permissions
  FXbool isGroupReadable() const;

  /// Return true if group has write permissions
  FXbool isGroupWritable() const;

  /// Return true if group has execute permissions
  FXbool isGroupExecutable() const;

  /// Return true if others have read-write-execute permissions
  FXbool isOtherReadWriteExecute() const;

  /// Return true if others have read permissions
  FXbool isOtherReadable() const;

  /// Return true if others have write permissions
  FXbool isOtherWritable() const;

  /// Return true if others have execute permissions
  FXbool isOtherExecutable() const;

  /// Return true if the file sets the user id on execution
  FXbool isSetUid() const;

  /// Return true if the file sets the group id on execution
  FXbool isSetGid() const;

  /// Return true if the file has the sticky bit set
  FXbool isSetSticky() const;

  /// Return the mode flags for this file
  static FXuint mode(const FXString& file);

  /// Change the mode flags for this file
  static FXbool mode(const FXString& file,FXuint perm);

  /// Return true if file exists
  static FXbool exists(const FXString& file);

  /// Return file size in bytes
  static FXlong size(const FXString& file);

  /// Return file volume number
  static FXlong volume(const FXString& file);

  /// Return file index number
  static FXlong index(const FXString& file);

  /// Return number of links to file
  static FXuint links(const FXString& file);

  /**
  * Return last modified time for this file, on filesystems
  * where this is supported.  This is the time when any data
  * in the file was last modified, in nanoseconds since Epoch.
  */
  static FXTime modified(const FXString& file);

  /**
  * Return last accessed time for this file, on filesystems
  * where this is supported, in nanoseconds since Epoch.
  */
  static FXTime accessed(const FXString& file);

  /**
  * Return created time for this file, on filesystems
  * where this is supported.  This is also the time when
  * ownership, permissions, links, and other meta-data may
  * have changed, in nanoseconds since Epoch.
  */
  static FXTime created(const FXString& file);

  /// Return true if file is hidden
  static FXbool isHidden(const FXString& file);

  /// Return true if input path is a file name
  static FXbool isFile(const FXString& file);

  /// Return true if input path is a link
  static FXbool isLink(const FXString& file);

  /// Return true if input path is a directory
  static FXbool isDirectory(const FXString& file);

  /// Return true if file is readable
  static FXbool isReadable(const FXString& file);

  /// Return true if file is writable
  static FXbool isWritable(const FXString& file);

  /// Return true if file is executable
  static FXbool isExecutable(const FXString& file);

  /// Return true if owner has read-write-execute permissions
  static FXbool isOwnerReadWriteExecute(const FXString& file);

  /// Return true if owner has read permissions
  static FXbool isOwnerReadable(const FXString& file);

  /// Return true if owner has write permissions
  static FXbool isOwnerWritable(const FXString& file);

  /// Return true if owner has execute permissions
  static FXbool isOwnerExecutable(const FXString& file);

  /// Return true if group has read-write-execute permissions
  static FXbool isGroupReadWriteExecute(const FXString& file);

  /// Return true if group has read permissions
  static FXbool isGroupReadable(const FXString& file);

  /// Return true if group has write permissions
  static FXbool isGroupWritable(const FXString& file);

  /// Return true if group has execute permissions
  static FXbool isGroupExecutable(const FXString& file);

  /// Return true if others have read-write-execute permissions
  static FXbool isOtherReadWriteExecute(const FXString& file);

  /// Return true if others have read permissions
  static FXbool isOtherReadable(const FXString& file);

  /// Return true if others have write permissions
  static FXbool isOtherWritable(const FXString& file);

  /// Return true if others have execute permissions
  static FXbool isOtherExecutable(const FXString& file);

  /// Return true if the file sets the user id on execution
  static FXbool isSetUid(const FXString& file);

  /// Return true if the file sets the group id on execution
  static FXbool isSetGid(const FXString& file);

  /// Return true if the file has the sticky bit set
  static FXbool isSetSticky(const FXString& file);

  };


}

#endif
