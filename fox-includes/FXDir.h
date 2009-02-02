/********************************************************************************
*                                                                               *
*                    D i r e c t o r y   E n u m e r a t o r                    *
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
* $Id: FXDir.h 2335 2006-01-28 02:33:03Z lyle $                             *
********************************************************************************/
#ifndef FXDIR_H
#define FXDIR_H

namespace FX {


/// Directory enumerator
class FXAPI FXDir {
private:
  FXuval space[256];
private:
  FXDir(const FXDir&);
  FXDir &operator=(const FXDir&);
public:

  /// Options for listing files
  enum {
    MatchAll    = 0,              /// Matching files and directories
    NoFiles     = 1,              /// Don't list any files
    NoDirs      = 2,              /// Don't list any directories
    AllFiles    = 4,              /// List all files
    AllDirs     = 8,              /// List all directories
    HiddenFiles = 16,             /// List hidden files also
    HiddenDirs  = 32,             /// List hidden directories also
    NoParent    = 64,             /// Don't include '..' in the listing
    CaseFold    = 128             /// Matching is case-insensitive
    };

public:

  /// Construct directory enumerator
  FXDir();

  /// Construct directory enumerator open on path
  FXDir(const FXString& path);

  /// Open directory to path, return true if ok.
  virtual bool open(const FXString& path);

  /// Returns true if the directory is open
  virtual bool isOpen() const;

  /// Go to next one
  virtual bool next();

  /// Return current file name
  virtual FXString name() const;

  /// Close directory
  virtual void close();

  /// Create directory
  static bool create(const FXString& path,FXuint mode=FXIO::OwnerFull|FXIO::GroupFull|FXIO::OtherFull);

  /// Remove directory
  static bool remove(const FXString& path);

  /// Rename or move srcpath to dstpath
  static bool rename(const FXString& srcpath,const FXString& dstpath);

  /**
  * List files in a given directory.
  * Returns the number of files in the string-array list which matched the
  * pattern or satisfied the flag conditions.
  */
  static FXint listFiles(FXString*& filelist,const FXString& path,const FXString& pattern="*",FXuint flags=FXDir::MatchAll);

  /**
  * List drives, i.e. roots of directory trees.
  * Return the number of drives in the string array.
  */
  static FXint listDrives(FXString*& drivelist);


  /// Destructor
  virtual ~FXDir();
  };

}

#endif
