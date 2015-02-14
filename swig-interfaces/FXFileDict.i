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

/// Registers stuff to know about the extension
struct FXFileAssoc {
  FXFileAssoc();
  FXString   command;           /// Command to execute
  FXString   extension;         /// Full extension name
  FXString   mimetype;          /// Mime type name
  FXIcon    *bigicon;           /// Big normal icon
  FXIcon    *bigiconopen;       /// Big open icon
  FXIcon    *miniicon;          /// Mini normal icon
  FXIcon    *miniiconopen;      /// Mini open icon
  FXDragType dragtype;          /// Registered drag type
  FXuint     flags;             /// Flags
  ~FXFileAssoc();
  };


/// File Association dictionary
class FXFileDict : public FXDict {
public:
  %extend {
    /// Registry key used to find fallback executable icons
    static VALUE defaultExecBinding(){
      return to_ruby(FXFileDict::defaultExecBinding);
      }

    /// Registry key used to find fallback directory icons
    static VALUE defaultDirBinding(){
      return to_ruby(FXFileDict::defaultDirBinding);
      }

    /// Registry key used to find fallback document icons
    static VALUE defaultFileBinding(){
      return to_ruby(FXFileDict::defaultFileBinding);
      }
  }

public:

  %extend {
    /**
    * Construct a dictionary mapping file-extension to file associations,
    * using the application registry settings as a source for the bindings.
    */
    FXFileDict(FXApp* a){
      return new FXRbFileDict(a);
      }

    /**
    * Construct a dictionary mapping file-extension to file associations,
    * using the specified settings database as a source for the bindings.
    */
    FXFileDict(FXApp* a,FXSettings* db){
      return new FXRbFileDict(a,db);
      }
    }

  /// Change settings database
  void setSettings(FXSettings* s);

  /// Return settings database
  FXSettings* getSettings() const;

  /// Change icon dictionary
  void setIconDict(FXIconDict *icns);

  /// Return icon dictionary
  FXIconDict* getIconDict() const;

  /**
  * Set icon search path; the initial search path is determined by the
  * "iconpath" registry setting in the SETTINGS section.
  */
  void setIconPath(const FXString& path);

  /// Return current icon search path
  const FXString& getIconPath() const;

  /// Replace file association
  FXFileAssoc* replace(const FXchar* ext,const FXchar* str);

  /// Remove file association
  FXFileAssoc* remove(const FXchar* ext);

  /// Find file association from registry
  FXFileAssoc* find(const FXchar* ext);

  /// Destructor
  virtual ~FXFileDict();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFileDict)
DECLARE_FXFILEDICT_VIRTUALS(FXFileDict)

