/********************************************************************************
*                                                                               *
*                             F i l e   C l a s s                               *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXFile.h 2335 2006-01-28 02:33:03Z lyle $                            *
********************************************************************************/
#ifndef FXFILE_H
#define FXFILE_H

#ifndef FXIO_H
#include "FXIO.h"
#endif


namespace FX {


/**
* Low level file access.
*/
class FXAPI FXFile : public FXIO {
private:
  FXFile(const FXFile&);
  FXFile &operator=(const FXFile&);
public:

  /// Construct file
  FXFile(){ }

  /// Construct file and attach existing handle h
  FXFile(FXInputHandle handle,FXuint mode);

  /// Construct and open a file
  FXFile(const FXString& file,FXuint mode=FXIO::Reading,FXuint perm=FXIO::OwnerReadWrite|FXIO::GroupReadWrite|FXIO::OtherReadWrite);

  /// Open file
  virtual bool open(const FXString& file,FXuint mode=FXIO::Reading,FXuint perm=FXIO::OwnerReadWrite|FXIO::GroupReadWrite|FXIO::OtherReadWrite);

  /// Open device with access mode and handle
  virtual bool open(FXInputHandle handle,FXuint mode);

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

  /// Return file size
  virtual FXlong size();

  /// Test if we're at the end
  virtual bool eof();

  /// Close file
  virtual bool close();


  /// Create new (empty) file
  static bool create(const FXString& file,FXuint perm=FXIO::OwnerReadWrite|FXIO::GroupReadWrite|FXIO::OtherReadWrite);

  /// Remove file
  static bool remove(const FXString& file);

  /// Rename or move srcfile to dstfile, replacing dstfile if it exists
  static bool rename(const FXString& srcfile,const FXString& dstfile);

  /// Link file
  static bool link(const FXString& srcfile,const FXString& dstfile);

  /// Read symbolic link
  static FXString symlink(const FXString& file);

  /// Symbolic link file
  static bool symlink(const FXString& srcfile,const FXString& dstfile);

  /// Return true if files are identical
  static bool identical(const FXString& file1,const FXString& file2);

  /// Copy srcfile to dstfile, overwriting dstfile if allowed
  static bool copy(const FXString& srcfile,const FXString& dstfile,bool overwrite=false);

  /// Concatenate srcfile1 and srcfile2 to dstfile, overwriting dstfile if allowed
  static bool concat(const FXString& srcfile1,const FXString& srcfile2,const FXString& dstfile,bool overwrite=false);



  /// Recursively copy files or directories from srcfile to dstfile, overwriting dstfile if allowed
  static bool copyFiles(const FXString& srcfile,const FXString& dstfile,bool overwrite=false);

  /// Recursively copy or move files or directories from srcfile to dstfile, overwriting dstfile if allowed
  static bool moveFiles(const FXString& srcfile,const FXString& dstfile,bool overwrite=false);

  /// Recursively remove file or directory, recurse if allowed
  static bool removeFiles(const FXString& path,bool recursive=false);

  /// Destroy
  virtual ~FXFile();
  };

}

#endif
