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

#include "FXRbCommon.h"
#include "FXRbObjRegistry.h"
#include "swigruby.h"

FXRbObjRegistry::FXRbObjRegistry(){
  FXRuby_Objects=st_init_numtable();
}

const char * FXRbObjRegistry::safe_rb_obj_classname(VALUE obj)
{
  int tdata = TYPE(obj)==T_DATA;
  if( (tdata && IsInGC(DATA_PTR(obj)))
#ifdef HAVE_RB_DURING_GC
      || rb_during_gc()
#endif
  ){
    /* It's not safe to call rb_obj_classname() during GC.
    * Return dummy value in this case. */
    return "during GC";
  } else if (tdata) {
    return rb_obj_classname(obj);
  } else {
    return "no T_DATA";
  }
}

VALUE FXRbObjRegistry::NewBorrowedObj(void *ptr,swig_type_info* ty){
  if(ptr!=0){
    FXASSERT(ty!=0);
    ObjDesc *desc;

    if(FXMALLOC(&desc,ObjDesc,1)){
      VALUE obj = SWIG_Ruby_NewPointerObj(ptr,ty,1);
      FXTRACE((1,"FXRbNewPointerObj(foxObj=%p) => rubyObj=%p (%s)\n",ptr,(void *)obj,safe_rb_obj_classname(obj)));
      desc->obj = obj;
      desc->type = borrowed;
      desc->in_gc = false;
      int overwritten = st_insert(FXRuby_Objects,reinterpret_cast<st_data_t>(ptr),reinterpret_cast<st_data_t>(desc));
      FXASSERT(!overwritten);
      return obj;
    } else {
      FXASSERT(FALSE);
      return Qnil;
    }
  }
  else{
    return Qnil;
  }
}

void FXRbObjRegistry::RegisterRubyObj(VALUE rubyObj,const void* foxObj) {
  FXASSERT(!NIL_P(rubyObj));
  FXASSERT(foxObj!=0);
  ObjDesc* desc;
  FXTRACE((1,"FXRbRegisterRubyObj(rubyObj=%p (%s),foxObj=%p)\n",(void *)rubyObj,safe_rb_obj_classname(rubyObj),foxObj));
  if(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t *>(&desc))!=0){
    FXASSERT(desc->type == borrowed);
    /* There is already a Ruby object registered for this foxObj.
     * This can happen, if libfox calls methods out of the C++ object constructor,
     * that can be overwritten in Ruby (like changeFocus) with the object as
     * parameter. FXFileSelector is one example.
     * To avoid double references to the same foxObj from different Ruby objects,
     * we decouple the foxObj from previoius ruby object and point to the new one.
     */
    DATA_PTR(desc->obj) = 0;
    desc->obj = rubyObj;
    desc->type = own;
  } else {
    if(FXMALLOC(&desc,ObjDesc,1)){
      desc->obj = rubyObj;
      desc->type = own;
      desc->in_gc = false;
      int overwritten = st_insert(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t>(desc));
      FXASSERT(!overwritten);
    } else {
      FXASSERT(FALSE);
    }
  }
  FXASSERT(GetRubyObj(foxObj,false)==rubyObj);
}

void FXRbObjRegistry::UnregisterRubyObj(const void* foxObj, bool alsoOwned){
  if(foxObj!=0){
    ObjDesc* desc;
    if(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t *>(&desc))!=0){
      if( !alsoOwned && desc->type!=borrowed ) return;
      FXTRACE((1,"FXRbUnregisterRubyObj(rubyObj=%p (%s),foxObj=%p)\n",(void *)desc->obj,safe_rb_obj_classname(desc->obj),foxObj));
      DATA_PTR(desc->obj)=0;
      FXFREE(&desc);
      st_delete(FXRuby_Objects,reinterpret_cast<st_data_t *>(const_cast<void**>(&foxObj)),reinterpret_cast<st_data_t *>(0));
      FXASSERT(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t *>(0))==0);
    }
  }
}


VALUE FXRbObjRegistry::GetRubyObj(const void *foxObj,bool alsoBorrowed, bool in_gc_mark){
  ObjDesc* desc;
  if(foxObj!=0 && st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t *>(&desc))!=0){
    FXASSERT(desc!=0);
    if(alsoBorrowed || desc->type!=borrowed){
      const char *classname = in_gc_mark ? "in GC" : safe_rb_obj_classname(desc->obj);
      FXTRACE((2,"%s(foxObj=%p) => rubyObj=%p (%s)\n", in_gc_mark ? "FXRbGcMark" : "FXRbGetRubyObj", foxObj, (void *)desc->obj, classname));
      return desc->obj;
    }
  }
  return Qnil;
}


bool FXRbObjRegistry::IsBorrowed(void* ptr){
  FXASSERT(ptr!=0);
  ObjDesc *desc;
  if(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(ptr),reinterpret_cast<st_data_t *>(&desc))!=0){
    return desc->type == borrowed;
  }
  else{
    return true;
  }
}

bool FXRbObjRegistry::SetInGC(const void* ptr, bool enabled){
  FXASSERT(ptr!=0);
  ObjDesc *desc;
  if(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(ptr),reinterpret_cast<st_data_t *>(&desc))!=0){
    desc->in_gc=enabled;
    return enabled;
  }
  return false;
}

bool FXRbObjRegistry::IsInGC(const void* ptr){
  FXASSERT(ptr!=0);
  ObjDesc *desc;

#ifdef HAVE_RB_DURING_GC
  if( rb_during_gc() ){
    return true;
  }
#endif
  if(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(ptr),reinterpret_cast<st_data_t *>(&desc))!=0){
    return desc->in_gc;
  }
  return false;
}

FXRbObjRegistry FXRbObjRegistry::main;
