/********************************************************************************
*                                                                               *
*                           S e t t i n g s   C l a s s                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXSettings.h 2763 2007-11-19 17:37:52Z lyle $                        *
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
  FXbool modified;
protected:
  virtual void *createData(void*);
  virtual void deleteData(void*);
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

  /// Is it modified
  FXbool isModified() const { return modified; }

  /// Mark as changed
  void setModified(FXbool mdfy=true){ modified=mdfy; }

  /// Parse a file containing a settings database.
  FXbool parseFile(const FXString& filename,FXbool mark);

  /// Unparse settings database into given file.
  FXbool unparseFile(const FXString& filename);

  /// Find string dictionary for the given section; may be NULL
  FXStringDict* find(const FXchar *section) const { return (FXStringDict*)FXDict::find(section); }

  /// Obtain the string dictionary for the given section
  FXStringDict* data(FXint pos) const { return (FXStringDict*)FXDict::data(pos); }

  /// Read a formatted registry entry, using scanf-style format
  FXint readFormatEntry(const FXchar *section,const FXchar *name,const FXchar *fmt,...) const FX_SCANF(4,5) ;

  /// Read a string registry entry; if no value is found, the default value def is returned
  const FXchar *readStringEntry(const FXchar *section,const FXchar *name,const FXchar *def=NULL) const;

  /// Read a integer registry entry; if no value is found, the default value def is returned
  FXint readIntEntry(const FXchar *section,const FXchar *name,FXint def=0) const;

  /// Read a unsigned integer registry entry; if no value is found, the default value def is returned
  FXuint readUIntEntry(const FXchar *section,const FXchar *name,FXuint def=0) const;

  /// Read a 64-bit long integer registry entry; if no value is found, the default value def is returned
  FXlong readLongEntry(const FXchar *section,const FXchar *name,FXlong def=0) const;

  /// Read a 64-bit unsigned long integer registry entry; if no value is found, the default value def is returned
  FXulong readULongEntry(const FXchar *section,const FXchar *name,FXulong def=0) const;

  /// Read a double-precision floating point registry entry; if no value is found, the default value def is returned
  FXdouble readRealEntry(const FXchar *section,const FXchar *name,FXdouble def=0.0) const;

  /// Read a color value registry entry; if no value is found, the default value def is returned
  FXColor readColorEntry(const FXchar *section,const FXchar *name,FXColor def=0) const;

  /// Read a boolean registry entry
  FXbool readBoolEntry(const FXchar *section,const FXchar *name,FXbool def=false) const;

  /// Write a formatted registry entry, using printf-style format
  FXint writeFormatEntry(const FXchar *section,const FXchar *name,const FXchar *fmt,...) FX_PRINTF(4,5) ;

  /// Write a string registry entry
  FXbool writeStringEntry(const FXchar *section,const FXchar *name,const FXchar *val);

  /// Write a integer registry entry
  FXbool writeIntEntry(const FXchar *section,const FXchar *name,FXint val);

  /// Write a unsigned integer registry entry
  FXbool writeUIntEntry(const FXchar *section,const FXchar *name,FXuint val);

  /// Write a 64-bit long integer registry entry
  FXbool writeLongEntry(const FXchar *section,const FXchar *name,FXlong val);

  /// Write a 64-bit unsigned long integer registry entry
  FXbool writeULongEntry(const FXchar *section,const FXchar *name,FXulong val);

  /// Write a double-precision floating point registry entry
  FXbool writeRealEntry(const FXchar *section,const FXchar *name,FXdouble val);

  /// Write a color value entry
  FXbool writeColorEntry(const FXchar *section,const FXchar *name,FXColor val);

  /// Write a boolean value entry
  FXbool writeBoolEntry(const FXchar *section,const FXchar *name,FXbool val);

  /// See if entry exists
  FXbool existingEntry(const FXchar *section,const FXchar *name) const;

  /// Delete a registry entry
  FXbool deleteEntry(const FXchar *section,const FXchar *name);

  /// See if section exists
  FXbool existingSection(const FXchar *section) const;

  /// Delete section
  FXbool deleteSection(const FXchar *section);

  /// Clear all sections
  FXbool clear();

  /// Cleanup
  virtual ~FXSettings();
  };

}

#endif
