/********************************************************************************
*                                                                               *
*                         I c o n   D i c t i o n a r y                         *
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
* $Id: FXIconDict.h 2725 2007-11-16 16:57:54Z lyle $                         *
********************************************************************************/
#ifndef FXICONDICT_H
#define FXICONDICT_H

#ifndef FXDICT_H
#include "FXDict.h"
#endif

namespace FX {


class FXIconSource;


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
class FXAPI FXIconDict : public FXDict {
  FXDECLARE(FXIconDict)
private:
  FXIconSource *source; // Icon source
  FXString      path;   // Where to search icons
protected:
  FXIconDict():source(NULL){}
  virtual void *createData(void*);
  virtual void deleteData(void*);
private:
  FXIconDict(const FXIconDict&);
  FXIconDict &operator=(const FXIconDict&);
public:

  /// Default icon search path
  static const FXchar defaultIconPath[];

public:

  /**
  * Construct icon dictionary, and set initial search path; also
  * creates a default icon source object.
  */
  FXIconDict(FXApp* app,const FXString& p=defaultIconPath);

  /// Change icon source
  void setIconSource(FXIconSource *src){ source=src; }

  /// Return icon source
  FXIconSource* getIconSource() const { return source; }

  /// Set icon search path
  void setIconPath(const FXString& p){ path=p; }

  /// Return current icon search path
  const FXString& getIconPath() const { return path; }

  /// Insert unique icon loaded from filename into dictionary
  FXIcon* insert(const FXchar* name){ return (FXIcon*)FXDict::insert(name,(void*)name); }

  /// Replace icon loaded from filename into dictionary
  FXIcon* replace(const FXchar* name){ return (FXIcon*)FXDict::replace(name,(void*)name); }

  /// Remove icon from dictionary
  FXIcon* remove(const FXchar* name){ return (FXIcon*)FXDict::remove(name); }

  /// Find icon by name
  FXIcon* find(const FXchar* name){ return (FXIcon*)FXDict::find(name); }

  /// Return icon at position pos
  FXIcon* data(FXint pos) const { return (FXIcon*)FXDict::data(pos); }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy the icon dict as well as the icon source
  virtual ~FXIconDict();
  };


}

#endif
