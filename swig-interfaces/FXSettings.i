/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

class FXStringDict;

// Added an alias for backwards compatibility with FXRuby 1.6
%alias FXSettings::readUIntEntry(const FXchar *section,const FXchar *name,FXuint def=0) const "readUnsignedEntry";
%alias FXSettings::writeUIntEntry(const FXchar *section,const FXchar *name,FXuint val) "writeUnsignedEntry";

%ignore FXSettings::FXSettings(const FXSettings& orig);
%ignore FXSettings::operator=(const FXSettings& orig);
%ignore FXSettings::readFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...) const;
%ignore FXSettings::writeFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...);
%ignore FXSettings::readBoolEntry(const FXchar *,const FXchar *,FXbool);
%ignore FXSettings::writeBoolEntry(const FXchar *,const FXchar *,FXbool);

%rename("modified=")    FXSettings::setModified(FXbool);
%rename("modified?")    FXSettings::isModified() const;

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

  /// Is it modified
  FXbool isModified() const;
  
  /// Mark as changed
  void setModified(FXbool mdfy=true);
  
  /// Parse a file containing a settings database.
  FXbool parseFile(const FXString& filename,FXbool mark);
  
  /// Unparse settings database into given file.
  FXbool unparseFile(const FXString& filename);

  /// Find string dictionary for the given section
  FXStringDict* find(const FXchar *section) const;

  /// Obtain the string dictionary for the given section
  FXStringDict* data(FXuint pos) const;

  /// Read a formatted registry entry, using scanf-style format
  FXint readFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...) const;

  /// Read a string registry entry; if no value is found, the default value def is returned
  const FXchar *readStringEntry(const FXchar *section,const FXchar *key,const FXchar *def=NULL) const;

  /// Read a integer registry entry; if no value is found, the default value def is returned
  FXint readIntEntry(const FXchar *section,const FXchar *key,FXint def=0) const;

  /// Read a unsigned integer registry entry; if no value is found, the default value def is returned
  FXuint readUIntEntry(const FXchar *section,const FXchar *name,FXuint def=0) const;
  
  /// Read a 64-bit long integer registry entry; if no value is found, the default value def is returned
  FXlong readLongEntry(const FXchar *section,const FXchar *name,FXlong def=0) const;
  
  /// Read a 64-bit unsigned long integer registry entry; if no value is found, the default value def is returned
  FXulong readULongEntry(const FXchar *section,const FXchar *name,FXulong def=0) const;

  /// Read a double-precision floating point registry entry; if no value is found, the default value def is returned
  FXdouble readRealEntry(const FXchar *section,const FXchar *key,FXdouble def=0.0) const;

  /// Read a color value registry entry; if no value is found, the default value def is returned
  FXColor readColorEntry(const FXchar *section,const FXchar *key,FXColor def=0) const;

  /// Read a boolean registry entry
  FXbool readBoolEntry(const FXchar *section,const FXchar *key,FXbool def=false) const;

  /// Write a formatted registry entry, using printf-style format
  FXint writeFormatEntry(const FXchar *section,const FXchar *key,const FXchar *fmt,...);

  /// Write a string registry entry
  FXbool writeStringEntry(const FXchar *section,const FXchar *key,const FXchar *val);

  /// Write a integer registry entry
  FXbool writeIntEntry(const FXchar *section,const FXchar *key,FXint val);

  /// Write a unsigned integer registry entry
  FXbool writeUIntEntry(const FXchar *section,const FXchar *name,FXuint val);
  
  /// Write a 64-bit long integer registry entry
  FXbool writeLongEntry(const FXchar *section,const FXchar *name,FXlong val);
  
  /// Write a 64-bit unsigned long integer registry entry
  FXbool writeULongEntry(const FXchar *section,const FXchar *name,FXulong val);

  /// Write a double-precision floating point registry entry
  FXbool writeRealEntry(const FXchar *section,const FXchar *key,FXdouble val);

  /// Write a color value entry
  FXbool writeColorEntry(const FXchar *section,const FXchar *key,FXColor val);

  /// Write a boolean value entry
  FXbool writeBoolEntry(const FXchar *section,const FXchar *key,FXbool val);
 
  /// Delete a registry entry
  FXbool deleteEntry(const FXchar *section,const FXchar *key);

  /// See if entry exists
  FXbool existingEntry(const FXchar *section,const FXchar *key);

  /// Delete section
  FXbool deleteSection(const FXchar *section);

  /// See if section exists
  FXbool existingSection(const FXchar *section);

  /// Clear all sections
  FXbool clear();

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

