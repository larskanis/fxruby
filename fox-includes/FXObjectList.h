/********************************************************************************
*                                                                               *
*                            O b j e c t   L i s t                              *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXObjectList.h,v 1.42 2009/01/06 13:07:26 fox Exp $                      *
********************************************************************************/
#ifndef FXOBJECTLIST_H
#define FXOBJECTLIST_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {

/// List of pointers to objects
class FXAPI FXObjectList {
protected:
  FXObject **ptr;
public:

  /// Default constructor
  FXObjectList();

  /// Copy constructor
  FXObjectList(const FXObjectList& src);

  /// Construct and init with single object
  FXObjectList(FXObject* object);

  /// Construct and init with n copies of object
  FXObjectList(FXObject* objects,FXint n);

  /// Construct and init with list of objects
  FXObjectList(FXObject** objects,FXint n);

  /// Assignment operator
  FXObjectList& operator=(const FXObjectList& orig);

  /// Return number of objects
  FXint no() const { return *((FXint*)(ptr-1)); }

  /// Set number of objects
  FXbool no(FXint num);

  /// Indexing operator
  FXObject*& operator[](FXint i){ return ptr[i]; }
  FXObject* const& operator[](FXint i) const { return ptr[i]; }

  /// Indexing operator
  FXObject*& at(FXint i){ return ptr[i]; }
  FXObject* const& at(FXint i) const { return ptr[i]; }

  /// First element in list
  FXObject*& head(){ return ptr[0]; }
  FXObject* const& head() const { return ptr[0]; }

  /// Last element in list
  FXObject*& tail(){ return ptr[no()-1]; }
  FXObject* const& tail() const { return ptr[no()-1]; }

  /// Access to content array
  FXObject** data() const { return ptr; }

  /// Adopt objects from orig, leaving orig empty
  FXObjectList& adopt(FXObjectList& orig);

  /// Assign object to list
  FXObjectList& assign(FXObject* object);

  /// Assign n copies of object to list
  FXObjectList& assign(FXObject* object,FXint n);

  /// Assign n objects to list
  FXObjectList& assign(FXObject** objects,FXint n);

  /// Assign objects to list
  FXObjectList& assign(FXObjectList& objects);

  /// Insert object at certain position
  FXObjectList& insert(FXint pos,FXObject* object);

  /// Insert n copies of object at specified position
  FXObjectList& insert(FXint pos,FXObject* object,FXint n);

  /// Insert n objects at specified position
  FXObjectList& insert(FXint pos,FXObject** objects,FXint n);

  /// Insert objects at specified position
  FXObjectList& insert(FXint pos,FXObjectList& objects);

  /// Prepend object
  FXObjectList& prepend(FXObject* object);

  /// Prepend n copies of object
  FXObjectList& prepend(FXObject* object,FXint n);

  /// Prepend n objects
  FXObjectList& prepend(FXObject** objects,FXint n);

  /// Prepend objects
  FXObjectList& prepend(FXObjectList& objects);

  /// Append object
  FXObjectList& append(FXObject* object);

  /// Append n copies of object
  FXObjectList& append(FXObject* object,FXint n);

  /// Append n objects
  FXObjectList& append(FXObject** objects,FXint n);

  /// Append objects
  FXObjectList& append(FXObjectList& objects);

  /// Replace object at position by given object
  FXObjectList& replace(FXint pos,FXObject* object);

  /// Replaces the m objects at pos with n objects
  FXObjectList& replace(FXint pos,FXint m,FXObject** objects,FXint n);

  /// Replaces the m objects at pos with n copies of object
  FXObjectList& replace(FXint pos,FXint m,FXObject* object,FXint n);

  /// Replace the m objects at pos with objects
  FXObjectList& replace(FXint pos,FXint m,FXObjectList& objects);

  /// Remove object at pos
  FXObjectList& erase(FXint pos);

  /// Remove n objects at pos
  FXObjectList& erase(FXint pos,FXint n);

  /// Push object to end
  FXObjectList& push(FXObject* object);

  /// Pop object from end
  FXObjectList& pop();

  /// Remove object
  FXObjectList& remove(const FXObject* object);

  /// Find object in list, searching forward; return position or -1
  FXint find(const FXObject *object,FXint pos=0) const;

  /// Find object in list, searching backward; return position or -1
  FXint rfind(const FXObject *object,FXint pos=2147483647) const;

  /// Remove all objects
  FXObjectList& clear();

  /// Save to a stream
  void save(FXStream& store) const;

  /// Load from a stream
  void load(FXStream& store);

  /// Destructor
  virtual ~FXObjectList();
  };


/// Specialize list to pointers to TYPE
template<class TYPE>
class FXObjectListOf : public FXObjectList {
public:
  FXObjectListOf(){}

  /// Indexing operator
  TYPE*& operator[](FXint i){ return (TYPE*&)ptr[i]; }
  TYPE *const& operator[](FXint i) const { return (TYPE*const&)ptr[i]; }

  /// Access to list
  TYPE*& at(FXint i){ return (TYPE*&)ptr[i]; }
  TYPE *const& at(FXint i) const { return (TYPE*const&)ptr[i]; }

  /// First element in list
  TYPE*& head(){ return (TYPE*&)ptr[0]; }
  TYPE* const& head() const { return (TYPE*const&)ptr[0]; }

  /// Last element in list
  TYPE*& tail(){ return (TYPE*&)ptr[no()-1]; }
  TYPE* const& tail() const { return (TYPE*const&)ptr[no()-1]; }

  /// Access to content array
  TYPE** data() const { return (TYPE**)ptr; }
  };

}

#endif
