/********************************************************************************
*                                                                               *
*                  S t r i n g   D i c t i o n a r y    C l a s s               *
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
* $Id: FXStringDict.h 2345 2006-02-14 03:07:05Z lyle $                      *
********************************************************************************/
#ifndef FXSTRINGDICT_H
#define FXSTRINGDICT_H

#ifndef FXDICT_H
#include "FXDict.h"
#endif

namespace FX {

/**
* String dictionary maps a character string to a character string.
* The inserted strings are copied when they're inserted.
*/
class FXAPI FXStringDict : public FXDict {
  FXDECLARE(FXStringDict)
protected:
  virtual void *createData(const void*);
  virtual void deleteData(void*);
public:

  /// Construct a string dictionary
  FXStringDict();

  /// Copy constructor
  FXStringDict(const FXStringDict& orig);

  /// Assignment operator
  FXStringDict &operator=(const FXStringDict& orig);

  /// Insert a new string indexed by key, with given mark flag
  const FXchar* insert(const FXchar* ky,const FXchar* str,bool mrk=false){ return (const FXchar*)FXDict::insert(ky,str,mrk); }

  /// Replace or insert a new string indexed by key, unless given mark is lower that the existing mark
  const FXchar* replace(const FXchar* ky,const FXchar* str,bool mrk=false){ return (const FXchar*)FXDict::replace(ky,str,mrk); }

  /// Remove entry indexed by key
  const FXchar* remove(const FXchar* ky){ return (const FXchar*)FXDict::remove(ky); }

  /// Return the entry indexed by key, or return NULL if the key does not exist
  const FXchar* find(const FXchar* ky) const { return (const FXchar*)FXDict::find(ky); }

  /// Return the string at position pos
  const FXchar* data(FXuint pos) const { return (const FXchar*)dict[pos].data; }

  /// Destructor
  virtual ~FXStringDict();
  };

}

#endif
