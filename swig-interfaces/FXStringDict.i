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


/**
* String dictionary maps a character string to a character string.
* The inserted strings are copied when they're inserted.
*/
class FXStringDict : public FXDict {
public:
  %extend {
    /// Construct a string dictionary
    FXStringDict(){
      return new FXRbStringDict();
      }
    }

  /// Insert a new string indexed by key, with given mark flag
  const FXchar* insert(const FXchar* ky,const FXchar* str,bool mrk=false);

  /// Replace or insert a new string indexed by key, unless given mark is lower that the existing mark
  const FXchar* replace(const FXchar* ky,const FXchar* str,bool mrk=false);

  /// Remove entry indexed by key
  const FXchar* remove(const FXchar* ky);

  /// Return the entry indexed by key, or return NULL if the key does not exist
  const FXchar* find(const FXchar* ky) const;

  /// Return the string at position pos
  const FXchar* data(FXuint pos) const;

  /// Destructor
  virtual ~FXStringDict();
  };


DECLARE_FXOBJECT_VIRTUALS(FXStringDict)

