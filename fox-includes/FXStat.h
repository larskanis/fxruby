/********************************************************************************
*                                                                               *
*                        F i l e   S t a t i s t i c s                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXStat.h 2291 2005-12-05 03:37:36Z lyle $                            *
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
  FXTime  createTime;           /// Create time
  FXTime  accessTime;           /// Access time
  FXTime  modifyTime;           /// Modify time
  FXlong  fileSize;             /// File size
public:

  /// Get statistics of the file into the stat buffer info
  static bool statFile(const FXString& file,FXStat& info);

  /// Get statistice of the link into the stat buffer info
  static bool statLink(const FXString& file,FXStat& info);

  /// Get statistics of already open file into stat buffer info
  static bool stat(const FXFile& file,FXStat& info);

  /// Return the mode flags for this file
  FXuint mode() const { return modeFlags; }

  /// Return file size in bytes
  FXlong size() const { return fileSize; }

  /// Return user number
  FXuint user() const { return userNumber; }

  /// Return group number
  FXuint group() const { return groupNumber; }

  /// Return time when last modified
  FXTime modified() const { return modifyTime; }

  /// Return time when last accessed
  FXTime accessed() const { return accessTime; }

  /// Return time when file was created
  FXTime created() const { return createTime; }

  /// Return time anything was changed
  FXTime touched() const;

  /// Return true if it is a hidden file (Windows-only)
  bool isHidden() const;

  /// Return true if it is a regular file
  bool isFile() const;

  /// Return true if it is a link
  bool isLink() const;

  /// Return true if character device
  bool isCharacter() const;

  /// Return true if block device
  bool isBlock() const;

  /// Return true if socket device
  bool isSocket() const;

  /// Return true if fifo (pipe) device
  bool isFifo() const;

  /// Return true if input path is a directory
  bool isDirectory() const;

  /// Return true if file is readable
  bool isReadable() const;

  /// Return true if file is writable
  bool isWritable() const;

  /// Return true if file is executable
  bool isExecutable() const;

  /// Return true if owner has read-write-execute permissions
  bool isOwnerReadWriteExecute() const;

  /// Return true if owner has read permissions
  bool isOwnerReadable() const;

  /// Return true if owner has write permissions
  bool isOwnerWritable() const;

  /// Return true if owner has execute permissions
  bool isOwnerExecutable() const;

  /// Return true if group has read-write-execute permissions
  bool isGroupReadWriteExecute() const;

  /// Return true if group has read permissions
  bool isGroupReadable() const;

  /// Return true if group has write permissions
  bool isGroupWritable() const;

  /// Return true if group has execute permissions
  bool isGroupExecutable() const;

  /// Return true if others have read-write-execute permissions
  bool isOtherReadWriteExecute() const;

  /// Return true if others have read permissions
  bool isOtherReadable() const;

  /// Return true if others have write permissions
  bool isOtherWritable() const;

  /// Return true if others have execute permissions
  bool isOtherExecutable() const;

  /// Return true if the file sets the user id on execution
  bool isSetUid() const;

  /// Return true if the file sets the group id on execution
  bool isSetGid() const;

  /// Return true if the file has the sticky bit set
  bool isSetSticky() const;

  /// Return the mode flags for this file
  static FXuint mode(const FXString& file);

  /// Change the mode flags for this file
  static bool mode(const FXString& file,FXuint perm);

  /// Return true if file exists
  static bool exists(const FXString& file);

  /// Return file size in bytes
  static FXlong size(const FXString& file);

  /**
  * Return last modified time for this file, on filesystems
  * where this is supported.  This is the time when any data
  * in the file was last modified.
  */
  static FXTime modified(const FXString& file);

  /**
  * Return last accessed time for this file, on filesystems
  * where this is supported.
  */
  static FXTime accessed(const FXString& file);

  /**
  * Return created time for this file, on filesystems
  * where this is supported.  This is also the time when
  * ownership, permissions, links, and other meta-data may
  * have changed.
  */
  static FXTime created(const FXString& file);

  /**
  * Return touched time for this file, on filesystems
  * where this is supported.  This is the time when anything
  * at all, either contents or meta-data, about the file was
  * changed.
  */
  static FXTime touched(const FXString& file);

  /// Return true if file is hidden
  static bool isHidden(const FXString& file);

  /// Return true if input path is a file name
  static bool isFile(const FXString& file);

  /// Return true if input path is a link
  static bool isLink(const FXString& file);

  /// Return true if input path is a directory
  static bool isDirectory(const FXString& file);

  /// Return true if file is readable
  static bool isReadable(const FXString& file);

  /// Return true if file is writable
  static bool isWritable(const FXString& file);

  /// Return true if file is executable
  static bool isExecutable(const FXString& file);

  /// Return true if owner has read-write-execute permissions
  static bool isOwnerReadWriteExecute(const FXString& file);

  /// Return true if owner has read permissions
  static bool isOwnerReadable(const FXString& file);

  /// Return true if owner has write permissions
  static bool isOwnerWritable(const FXString& file);

  /// Return true if owner has execute permissions
  static bool isOwnerExecutable(const FXString& file);

  /// Return true if group has read-write-execute permissions
  static bool isGroupReadWriteExecute(const FXString& file);

  /// Return true if group has read permissions
  static bool isGroupReadable(const FXString& file);

  /// Return true if group has write permissions
  static bool isGroupWritable(const FXString& file);

  /// Return true if group has execute permissions
  static bool isGroupExecutable(const FXString& file);

  /// Return true if others have read-write-execute permissions
  static bool isOtherReadWriteExecute(const FXString& file);

  /// Return true if others have read permissions
  static bool isOtherReadable(const FXString& file);

  /// Return true if others have write permissions
  static bool isOtherWritable(const FXString& file);

  /// Return true if others have execute permissions
  static bool isOtherExecutable(const FXString& file);

  /// Return true if the file sets the user id on execution
  static bool isSetUid(const FXString& file);

  /// Return true if the file sets the group id on execution
  static bool isSetGid(const FXString& file);

  /// Return true if the file has the sticky bit set
  static bool isSetSticky(const FXString& file);

  };


}

#endif
