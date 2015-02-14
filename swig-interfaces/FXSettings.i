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

class FXStringDict;

%ignore FXSettings::FXSettings(const FXSettings& orig);
%ignore FXSettings::operator=(const FXSettings& orig);
%ignore FXSettings::readFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...);
%ignore FXSettings::writeFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...);
%ignore FXSettings::readBoolEntry(const FXchar *,const FXchar *,FXbool);
%ignore FXSettings::writeBoolEntry(const FXchar *,const FXchar *,FXbool);

/**
* The Settings class manages a key-value database.  This is normally used as
* part of Registry, but can also be used separately in applications that need
* to maintain a key-value database in a file of their own.
* String values can contain any character, and will be escaped when written
* to the file.
*/
class FXSettings : public FXDict {
public:

  /// Construct settings database.
  %extend {
    FXSettings(){
      return new FXRbSettings();
      }
    }

  /// Construct copy of existing database.
  FXSettings(const FXSettings& orig);

  /// Assignment operator
  FXSettings &operator=(const FXSettings& orig);

  /// Parse a file containing a settings database.
  bool parseFile(const FXString& filename,bool mark);

  /// Unparse settings database into given file.
  bool unparseFile(const FXString& filename);

  /// Obtain the string dictionary for the given section
  FXStringDict* data(FXuint pos) const;

  /// Find string dictionary for the given section
  FXStringDict* find(const FXchar *section) const;

  /// Read a formatted registry entry, using scanf-style format
  FXint readFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...);

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
  FXint writeFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...);

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
  FXbool clear();

  /// Mark as changed
  void setModified(bool mdfy=true);

  /// Is it modified
  bool isModified() const;

  /// Destructor
  virtual ~FXSettings();
  };

DECLARE_FXOBJECT_VIRTUALS(FXSettings)

%{
static swig_type_info *FXSettings_dynamic_cast(void **ptr) {
    FXSettings **ppSettings = reinterpret_cast<FXSettings **>(ptr);
    FXRegistry *pRegistry=dynamic_cast<FXRegistry*>(*ppSettings);
    if(pRegistry){
      *ptr=reinterpret_cast<void*>(pRegistry);
      return SWIG_TypeQuery("FXRegistry *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXSettings, FXSettings_dynamic_cast);

