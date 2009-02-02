/********************************************************************************
*                                                                               *
*                  P a t h   N a m e   M a n i p u l a t i o n                  *
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
* $Id: FXPath.h 2291 2005-12-05 03:37:36Z lyle $                             *
********************************************************************************/
#ifndef FXPATH_H
#define FXPATH_H


namespace FX {


namespace FXPath {

  /**
  * Return root of absolute path; on Unix, this is just "/". On
  * Windows, this is "\\" or "C:\".  Returns the empty string
  * if the given path is not absolute.
  */
  FXString FXAPI root(const FXString& file);

  /**
  * Return the directory part of the path name.
  * Note that directory("/bla/bla/") is "/bla/bla" and NOT "/bla".
  * However, directory("/bla/bla") is "/bla" as we expect!
  */
  FXString FXAPI directory(const FXString& file);

  /**
  * Return name and extension part of the path name.
  * Note that name("/bla/bla/") is "" and NOT "bla".
  * However, name("/bla/bla") is "bla" as we expect!
  */
  FXString FXAPI name(const FXString& file);

  /// Return file title, i.e. document name only
  FXString FXAPI title(const FXString& file);

  /// Return extension part of the file name
  FXString FXAPI extension(const FXString& file);

  /// Return file name less the extension
  FXString FXAPI stripExtension(const FXString& file);

  /// Return the drive letter prefixing this file name (if any).
  FXString FXAPI drive(const FXString& file);

  /// Perform tilde or environment variable expansion
  FXString FXAPI expand(const FXString& file);

  /// Contract path based on user name and environment variable
  FXString FXAPI contract(const FXString& file,const FXString& user=FXString::null,const FXString& var=FXString::null);

  /**
  * Simplify a file path; the path will remain relative if it was relative,
  * or absolute if it was absolute.  Also, a trailing "/" will be preserved
  * as this is important in other functions.
  * For example, simplify("..//aaa/./bbb//../c/") becomes "../aaa/c/".
  */
  FXString FXAPI simplify(const FXString& file);

  /// Return absolute path from current directory and file name
  FXString FXAPI absolute(const FXString& file);

  /// Return absolute path from base directory and file name
  FXString FXAPI absolute(const FXString& base,const FXString& file);

  /// Return relative path of file to the current directory
  FXString FXAPI relative(const FXString& file);

  /// Return relative path of file to given base directory
  FXString FXAPI relative(const FXString& base,const FXString& file);

  /// Return path following local path separator conventions
  FXString FXAPI convert(const FXString& path);

  /// Return path to directory above input directory name
  FXString FXAPI upLevel(const FXString& file);

  /// Return true if file name is absolute
  bool FXAPI isAbsolute(const FXString& file);

  /// Return true if input directory is a top-level directory
  bool FXAPI isTopDirectory(const FXString& file);

  /// Return true if input path is a file share
  bool FXAPI isShare(const FXString& file);

  /// Enquote filename to make safe for shell
  FXString FXAPI enquote(const FXString& file,bool forcequotes=false);

  /// Dequote filename to get original again
  FXString FXAPI dequote(const FXString& file);

  /**
  * Perform wildcard match of a filename against a wildcard pattern.
  * The wildcard pattern may comprise ordinary characters or special
  * matching characters, as given below:
  *
  *  ?           Any single character.
  *  *           Zero or more of any character.
  *  [abc]       Any character from the set {a,b,c}.
  *  [^abc]      Any character BUT the ones from the set {a,b,c}.
  *  [!abc]      Ditto.
  *  [a-zA-Z]    Matches single character, which must be one of a-z or A-Z.
  *  [^a-zA-Z]   Matches single character, which must be anything other than a-z or A-Z.
  *  [!a-zA-Z]   Ditto.
  *  pat1|pat2   Match sub-pattern pat1 or pat2.
  *  pat1,pat2   Ditto.
  *  (pat1|pat2) Match sub-pattern pat1 or pat2; patterns may be nested.
  *  (pat1,pat2) Ditto.
  *
  * The special characters may be escaped to treat them as ordinary characters.
  * Matching may be influenced by a number of flags:
  *
  *  FILEMATCH_FILE_NAME         No wildcard can ever match /
  *  FILEMATCH_NOESCAPE          Backslashes don't quote special chars
  *  FILEMATCH_PERIOD            Leading . is matched only explicitly
  *  FILEMATCH_LEADING_DIR       Ignore /... after a match
  *  FILEMATCH_CASEFOLD          Compare without regard to case
  */
  bool FXAPI match(const FXString& pattern,const FXString& file,FXuint flags=(FILEMATCH_NOESCAPE|FILEMATCH_FILE_NAME));

  /**
  * Generate unique filename of the form pathnameXXX.ext, where
  * pathname.ext is the original input file, and XXX is a number,
  * possibly empty, that makes the file unique.
  */
  FXString FXAPI unique(const FXString& file);

  /**
  * Search path list for this file, return full path name for first occurrence.
  */
  FXString FXAPI search(const FXString& pathlist,const FXString& file);

  }

}

#endif
