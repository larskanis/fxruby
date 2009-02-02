/********************************************************************************
*                                                                               *
*                       H a s h   T a b l e   C l a s s                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2003,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXHash.h 2336 2006-02-04 15:20:33Z lyle $                            *
********************************************************************************/
#ifndef FXHASH_H
#define FXHASH_H

namespace FX {


/**
* A hash table for associating pointers to pointers.
*/
class FXAPI FXHash {
private:
  struct FXEntry {
    void* key;
    void* value;
    };
private:
  FXEntry *table;       // Hash table
  FXuint   total;       // Table size
  FXuint   used;        // Number of used entries
  FXuint   free;        // Number of free entries
private:
  FXHash(const FXHash&);
  FXHash &operator=(const FXHash&);
public:

  /// Construct empty hash table
  FXHash();

  /// Resize the table to the given size.
  void size(FXuint m);

  /// Return the size of the table
  FXint size() const { return total; }

  /// Return number of items in table
  FXuint no() const { return used; }

  /// Insert key into the table
  void* insert(void* key,void* value);

  /// Replace key in table
  void* replace(void* key,void* value);

  /// Remove key from the table
  void* remove(void* key);

  /// Return value of key
  void* find(void* key) const;

  /// Return true if slot is empty
  bool empty(FXint pos) const { return (table[pos].key==NULL)||(table[pos].key==(void*)-1L); }

  /// Return key at position pos
  void* key(FXint pos) const { return table[pos].key; }

  /// Return data pointer at position pos
  void* value(FXint pos) const { return table[pos].value; }

  /// Clear hash table
  void clear();

  /// Destructor
  virtual ~FXHash();
  };


}

#endif
