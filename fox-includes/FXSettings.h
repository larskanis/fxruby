/********************************************************************************
*                                                                               *
*                           S e t t i n g s   C l a s s                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXSettings.h 2345 2006-02-14 03:07:05Z lyle $                        *
********************************************************************************/
#ifndef FXSETTINGS_H
#define FXSETTINGS_H

#ifndef FXDICT_H
#include "FXDict.h"
#endif

namespace FX {


class FXStringDict;


/**
* The Settings class manages a key-value database.  This is normally used as
* part of Registry, but can also be used separately in applications that need
* to maintain a key-value database in a file of their own.
* String values can contain any character, and will be escaped when written
* to the file.
*/
class FXAPI FXSettings : public FXDict {
  FXDECLARE(FXSettings)
protected:
  bool modified;
protected:
  virtual void *createData(const void*);
  virtual void deleteData(void*);
  FXchar* dequote(FXchar* text) const;
  FXchar* enquote(FXchar* result,const FXchar* text);
  FXStringDict* insert(const FXchar* ky){ return (FXStringDict*)FXDict::insert(ky,NULL); }
  FXStringDict* replace(const FXchar* ky,FXStringDict* section){ return (FXStringDict*)FXDict::replace(ky,section,true); }
  FXStringDict* remove(const FXchar* ky){ return (FXStringDict*)FXDict::remove(ky); }
public:

  /// Construct settings database.
  FXSettings();

  /// Construct copy of existing database.
  FXSettings(const FXSettings& orig);

  /// Assignment operator
  FXSettings &operator=(const FXSettings& orig);

  /// Parse a file containing a settings database.
  bool parseFile(const FXString& filename,bool mark);

  /// Unparse settings database into given file.
  bool unparseFile(const FXString& filename);

  /// Obtain the string dictionary for the given section
  FXStringDict* data(FXuint pos) const { return (FXStringDict*)FXDict::data(pos); }

  /// Find string dictionary for the given section; may be NULL
  FXStringDict* find(const FXchar *section) const { return (FXStringDict*)FXDict::find(section); }

  /// Read a formatted registry entry, using scanf-style format
  FXint readFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...) FX_SCANF(4,5) ;

  /// Read a string registry entry; if no value is found, the default value def is returned
  const FXchar *readStringEntry(const FXchar *section,const FXchar *key,const FXchar *def=NULL);

  /// Read a integer registry entry; if no value is found, the default value def is returned
  FXint readIntEntry(const FXchar *section,const FXchar *key,FXint def=0);

  /// Read a unsigned integer registry entry; if no value is found, the default value def is returned
  FXuint readUnsignedEntry(const FXchar *section,const FXchar *key,FXuint def=0);

  /// Read a double-precision floating point registry entry; if no value is found, the default value def is returned
  FXdouble readRealEntry(const FXchar *section,const FXchar *key,FXdouble def=0.0);

  /// Read a color value registry entry; if no value is found, the default value def is returned
  FXColor readColorEntry(const FXchar *section,const FXchar *key,FXColor def=0);

  /// Read a boolean registry entry
  FXbool readBoolEntry(const FXchar *section,const FXchar *key,FXbool def=FALSE);

  /// Write a formatted registry entry, using printf-style format
  FXint writeFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...) FX_PRINTF(4,5) ;

  /// Write a string registry entry
  bool writeStringEntry(const FXchar *section,const FXchar *key,const FXchar *val);

  /// Write a integer registry entry
  bool writeIntEntry(const FXchar *section,const FXchar *key,FXint val);

  /// Write a unsigned integer registry entry
  bool writeUnsignedEntry(const FXchar *section,const FXchar *key,FXuint val);

  /// Write a double-precision floating point registry entry
  bool writeRealEntry(const FXchar *section,const FXchar *key,FXdouble val);

  /// Write a color value entry
  bool writeColorEntry(const FXchar *section,const FXchar *key,FXColor val);

  /// Write a boolean value entry
  bool writeBoolEntry(const FXchar *section,const FXchar *key,FXbool val);

  /// Delete a registry entry
  bool deleteEntry(const FXchar *section,const FXchar *key);

  /// See if entry exists
  bool existingEntry(const FXchar *section,const FXchar *key);

  /// Delete section
  bool deleteSection(const FXchar *section);

  /// See if section exists
  bool existingSection(const FXchar *section);

  /// Clear all sections
  bool clear();

  /// Mark as changed
  void setModified(bool mdfy=true){ modified=mdfy; }

  /// Is it modified
  bool isModified() const { return modified; }

  /// Cleanup
  virtual ~FXSettings();
  };

}

#endif
