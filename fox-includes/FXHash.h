/********************************************************************************
*                                                                               *
*                       H a s h   T a b l e   C l a s s                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2003,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXHash.h 2725 2007-11-16 16:57:54Z lyle $                            *
********************************************************************************/
#ifndef FXHASH_H
#define FXHASH_H

namespace FX {


/**
* A hash table for associating pointers to pointers.
*/
class FXAPI FXHash {
protected:
  struct FXEntry {
    void* name;
    void* data;
    };
protected:
  FXEntry *table;       // Hash table
  FXuint   total;       // Table size
  FXuint   used;        // Number of used entries
  FXuint   free;        // Number of free entries
private:
  FXHash(const FXHash&);
  FXHash &operator=(const FXHash&);
public:

  /**
  * Construct empty hash table.
  */
  FXHash();

  /**
  * Resize the table to the given size; the size must be
  * a power of two.
  */
  void size(FXuint m);

  /**
  * Return the total number of slots in the table.
  */
  FXuint size() const { return total; }

  /**
  * Return number of non-empty slots in the table.
  */
  FXuint no() const { return used; }

  /**
  * Insert key into table, unless the key already exists.
  * Returns the current value of the key.
  */
  void* insert(void* name,void* data);

  /**
  * Replace key in table, overwriting the old value if the
  * given key already exists.  Returns the old value of the key.
  */
  void* replace(void* name,void* data);

  /**
  * Remove key from the table. Returns the old value of the key.
  */
  void* remove(void* name);

  /**
  * Return value of key, or return NULL.
  */
  void* find(void* name) const;

  /**
  * Return true if slot is not occupied by a key.
  */
  FXbool empty(FXuint pos) const { return (table[pos].name==NULL)||(table[pos].name==(void*)-1L); }

  /**
  * Return key at position pos.
  */
  void* key(FXuint pos) const { return table[pos].name; }

  /**
  * Return data pointer at position pos.
  */
  void* value(FXuint pos) const { return table[pos].data; }

  /**
  * Clear hash table.
  */
  void clear();

  /// Destructor
  virtual ~FXHash();
  };


}

#endif
