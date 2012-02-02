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

%rename("iconSource=")	FXIconDict::setIconSource(FXIconSource*);
%rename("iconSource")	FXIconDict::getIconSource() const;
%rename("iconPath=")	FXIconDict::setIconPath(const FXString&);
%rename("iconPath")	FXIconDict::getIconPath() const;

/**
* The Icon Dictionary manages a collection of icons.  The icons are referenced
* by their file name.  When first encountering a new file name, the icon is
* located by searching the icon search path for the icon file.  If found, the
* services of the icon source object are used to load the icon from the file.
* A custom icon source may be installed to furnish support for additonal
* image file formats.
* Once the icon is loaded, an association between the icon name and the icon
* is entered into the icon dictionary.  Subsequent searches for an icon with
* this name will be satisfied from the cached value.
* The lifetype of the icons is managed by the icon dictionary, and thus all
* icons will be deleted when the dictionary is deleted.
*/
class FXIconDict : public FXDict {
public:

  %extend {
    /// Default icon search path
    static VALUE defaultIconPath(){
      return to_ruby(FXIconDict::defaultIconPath);
      }
  }

public:

  %extend {
    /**
    * Construct icon dictionary, and set initial search path; also
    * creates a default icon source object.
    */
    FXIconDict(FXApp* app,const FXString& p=defaultIconPath){
      return new FXRbIconDict(app,p);
      }
  }

  /// Change icon source
  void setIconSource(FXIconSource *src);

  /// Return icon source
  FXIconSource* getIconSource() const;

  /// Set icon search path
  void setIconPath(const FXString& p);

  /// Return current icon search path
  const FXString& getIconPath() const;

  /// Insert unique icon loaded from filename into dictionary
  FXIcon* insert(const FXchar* name);

  /// Remove icon from dictionary
  FXIcon* remove(const FXchar* name);

  /// Find icon by name
  FXIcon* find(const FXchar* name);

  /// Destroy the icon dict as well as the icon source
  virtual ~FXIconDict();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFileDict)

