/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2017-2017 by Lyle Johnson. All Rights Reserved.
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
 * at "lars@greiz-reinsdorf.de".
 ***********************************************************************/

#ifndef FXRBOBJREGISTRY_H
#define FXRBOBJREGISTRY_H

extern "C" {
  // Opaque type declaration for SWIG runtime support
  struct swig_type_info;
}

class FXRbObjRegistry {

  /**
  * The FXRuby_Objects hash table basically maps C++ objects to Ruby instances.
  * Each key in the table is a pointer to a C++ object we've seen before, and
  * the corresponding value is an FXRubyObjDesc struct (see below) that tells
  * us which Ruby instance corresponds to that C++ object.
  */

  st_table * FXRuby_Objects;

  /**
  * Each value in the FXRuby_Objects hash table is an instance of this
  * struct. It identifies the Ruby instance associated with a C++ object.
  * It also indicates whether this is merely a "borrowed" reference to
  * some C++ object (i.e. it's not one we need to destroy later).
  *
  * in_gc is set for FXWindows that are in garbage collection and must
  * not call ruby code anymore.
  */

  enum ObjType { own, borrowed, callback };

  struct ObjDesc {
    VALUE obj;
    enum ObjType type;
    bool in_gc;
  };

  const char * safe_rb_obj_classname(VALUE obj);

public:

  FXRbObjRegistry();

  /**
  * NewBorrowedObj() is a wrapper around SWIG_Ruby_NewPointerObj() that also
  * registers this C++ object & Ruby instance pair in our FXRuby_Objects
  * hash table. This function should only get called for methods that return
  * a reference to an already-existing C++ object (i.e. one that FOX "owns")
  * and for that reason we mark these objects as "borrowed".
  */
  VALUE NewBorrowedObj(void *ptr,swig_type_info* ty);

  // Register this Ruby class instance
  void RegisterRubyObj(VALUE rubyObj,const void* foxObj);

  void UnregisterRubyObj(const void* foxObj, bool alsoOwned);

  /**
  * Return the registered Ruby class instance associated with this
  * FOX object, or Qnil if not found.
  */
  VALUE GetRubyObj(const void *foxObj,bool alsoBorrowed, bool in_gc_mark=false);

  /**
  * FXRbIsBorrowed() returns true if the specified C++ object is one that
  * FOX owns (i.e. it's borrowed).
  */
  bool IsBorrowed(void* ptr);

  bool SetInGC(const void* ptr, bool enabled);
  bool IsInGC(const void* ptr);

  static FXRbObjRegistry main;
};

#endif
