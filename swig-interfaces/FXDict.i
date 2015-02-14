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

// Rename these functions
%rename("getTotalSize")	FXDict::size() const;
%rename("setTotalSize")	FXDict::size(FXint);
%rename("length")	FXDict::no() const;

// Mark these as predicate methods
%predicate FXDict::has_key(const FXchar* ky) const;


/**
* The dictionary class maintains a fast-access hash table of entities
* indexed by a character string.
* It is typically used to map strings to pointers; however, overloading
* the createData() and deleteData() members allows any type of data to
* be indexed by strings.
*/
class FXDict : public FXObject {
public:
  %extend {
    /**
    * Construct an empty dictionary.
    */
    FXDict(){
      return new FXRbDict();
      }
    }

  /**
  * Return the size of the table, including the empty slots.
  */
  FXint size() const;

  /**
  * Resize the table to the given size.
  */
  void size(FXint m);

  /**
  * Return the total number of entries in the table.
  */
  FXint no() const;

  /**
  * Insert a new entry into the table given key and mark.
  * If there is already an entry with that key, leave it unchanged,
  * otherwise insert the new entry.
  */
  // void* insert(const FXchar* ky,const void* ptr,bool mrk=false);

  /**
  * Replace data at key, if the entry's mark is less than
  * or equal to the given mark.  If there was no existing entry,
  * a new entry is inserted with the given mark.
  */
  // void* replace(const FXchar* ky,const void* ptr,bool mrk=false);

  /**
  * Remove data given key.
  */
  void* remove(const FXchar* ky);

  /**
  * Find data pointer given key.
  */
  // void* find(const FXchar* ky) const;

  /**
  * Return key at position pos.
  */
  const FXchar* key(FXuint pos) const;

  /**
  * return data pointer at position pos.
  */
  // void* data(FXuint pos) const;

  /**
  * Return mark flag of entry at position pos.
  */
  bool mark(FXuint pos) const;

  /**
  * Return position of first filled slot, or >= total
  */
  FXint first() const;

  /**
  * Return position of last filled slot or -1
  */
  FXint last() const;

  /**
  * Return position of next filled slot in hash table
  * or a value greater than or equal to total if no filled
  * slot was found
  */
  FXint next(FXint pos) const;

  /**
  * Return position of previous filled slot in hash table
  * or a -1 if no filled slot was found
  */
  FXint prev(FXint pos) const;

  /// Clear all entries
  void clear();

  // Add methods similar to those for Ruby's Hash class
  %extend {
    // Returns true if the given key is present
    bool has_key(const FXchar* ky) const {
      return (self->find(ky) != 0);
    }
  }

  /// Destructor
  virtual ~FXDict();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDict)

%{
static swig_type_info *FXDict_dynamic_cast(void **ptr) {
    FXDict **ppDict = reinterpret_cast<FXDict **>(ptr);
    FXFileDict *pFileDict=dynamic_cast<FXFileDict*>(*ppDict);
    if(pFileDict){
      *ptr=reinterpret_cast<void*>(pFileDict);
      return SWIG_TypeQuery("FXFileDict *");
      }
    FXIconDict *pIconDict=dynamic_cast<FXIconDict*>(*ppDict);
    if(pIconDict){
      *ptr=reinterpret_cast<void*>(pIconDict);
      return SWIG_TypeQuery("FXIconDict *");
      }
    FXSettings *pSettings=dynamic_cast<FXSettings*>(*ppDict);
    if(pSettings){
      *ptr=reinterpret_cast<void*>(pSettings);
      return SWIG_TypeQuery("FXSettings *");
      }
    FXStringDict *pStringDict=dynamic_cast<FXStringDict*>(*ppDict);
    if(pStringDict){
      *ptr=reinterpret_cast<void*>(pStringDict);
      return SWIG_TypeQuery("FXStringDict *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXDict, FXDict_dynamic_cast);

