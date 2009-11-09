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

/***********************************************************************
 * $Id: FXRuby.cpp 2933 2008-12-29 20:19:33Z lyle $
 ***********************************************************************/

#ifdef _MSC_VER
#pragma warning (disable : 4786)
#endif

#include "FXRbCommon.h"

#ifndef RUBY_1_9
#include "version.h"

#if RUBY_VERSION_CODE < 167
#define RB_RESCUE2_BROKEN_PROTOTYPE 1
#endif

// The prototype for st_foreach() changed at Ruby version 1.8.2
#if RUBY_VERSION_CODE < 182
#define ST_BROKEN_PROTOTYPES 1
#endif
#endif /* RUBY_1_9 */

#include "impl.h"

#ifdef __CYGWIN__
#include <io.h>		// for get_osf_handle()
#endif

#ifdef HAVE_SIGNAL_H
#include <signal.h>	// for definitions of SIGINT, etc.
#endif

#ifndef RUBY_1_9
extern "C" {
#include "rubyio.h"	// for GetOpenFile(), etc.
}
#else
#include "ruby/io.h"
#endif

// Symbol table functions from Ruby. If we included "st.h" directly
// we'd be dealing with broken prototypes anyways, so just duplicate
// the needed declarations here with the correct prototypes.

#if defined(ST_BROKEN_PROTOTYPES)

extern "C" {

struct st_table;

typedef char * st_data_t; /* this type changed to unsigned long at Ruby 1.8.2 */

st_table *st_init_strtable();
st_table *st_init_numtable();
int st_lookup(st_table *table, st_data_t key, st_data_t *value);
int st_insert(st_table *table, st_data_t key, st_data_t value);
int st_delete(st_table *table, st_data_t *key, st_data_t *value);
void st_foreach(st_table *table, int (*func)(st_data_t, st_data_t, st_data_t), st_data_t arg);

}

#else

#ifdef RUBY_1_9

#include "ruby/st.h"

#else

extern "C" {
#include "st.h"
}

#endif /* RUBY_1_9 */

#endif /* ST_BROKEN_PROTOTYPES */

// Opaque type declaration from SWIG runtime
struct swig_type_info;

// Wrapper around SWIG_TypeQuery() that caches results for performance
swig_type_info *FXRbTypeQuery(const char *desc){
  FXASSERT(desc!=0);
  static st_table *types=st_init_strtable();
  swig_type_info *typeinfo=0;
  if(st_lookup(types,reinterpret_cast<st_data_t>(const_cast<char*>(desc)),reinterpret_cast<st_data_t *>(&typeinfo))==0){
    typeinfo=SWIG_Ruby_TypeQuery(desc);
    st_insert(types,reinterpret_cast<st_data_t>(strdup(desc)),reinterpret_cast<st_data_t>(typeinfo));
    }
  FXASSERT(typeinfo!=0);
  return typeinfo;
  }


/**
 * The FXRuby_Objects hash table basically maps C++ objects to Ruby instances.
 * Each key in the table is a pointer to a C++ object we've seen before, and
 * the corresponding value is an FXRubyObjDesc struct (see below) that tells
 * us which Ruby instance corresponds to that C++ object.
 */

static st_table * FXRuby_Objects;

/**
 * Each value in the FXRuby_Objects hash table is an instance of this
 * struct. It identifies the Ruby instance associated with a C++ object.
 * It also indicates whether this is merely a "borrowed" reference to
 * some C++ object (i.e. it's not one we need to destroy later).
 */

struct FXRubyObjDesc {
  VALUE obj;
  bool borrowed;
  };


/**
 * FXRbNewPointerObj() is a wrapper around SWIG_Ruby_NewPointerObj() that also
 * registers this C++ object & Ruby instance pair in our FXRuby_Objects
 * hash table. This function should only get called for methods that return
 * a reference to an already-existing C++ object (i.e. one that FOX "owns")
 * and for that reason we mark these objects as "borrowed".
 */

VALUE FXRbNewPointerObj(void *ptr,swig_type_info* ty){
  if(ptr!=0){
    FXASSERT(ty!=0);
    VALUE obj;
    FXRubyObjDesc *desc;
    if(FXMALLOC(&desc,FXRubyObjDesc,1)){
      obj=SWIG_Ruby_NewPointerObj(ptr,ty,1);
      desc->obj=obj;
      desc->borrowed=true;
      st_insert(FXRuby_Objects,reinterpret_cast<st_data_t>(ptr),reinterpret_cast<st_data_t>(desc));
      return obj;
      }
    else{
      FXASSERT(FALSE);
      return Qnil;
      }
    }
  else{
    return Qnil;
    }
  }


/**
 * FXRbIsBorrowed() returns true if the specified C++ object is one that
 * FOX owns (i.e. it's borrowed).
 */

bool FXRbIsBorrowed(void* ptr){
  FXASSERT(ptr!=0);
  FXRubyObjDesc *desc;
  if(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(ptr),reinterpret_cast<st_data_t *>(&desc))!=0){
    return desc->borrowed;
    }
  else{
    return true;
    }
  }


/**
 * FXRbConvertPtr() is just a wrapper around SWIG_Ruby_ConvertPtr().
 */

void* FXRbConvertPtr(VALUE obj,swig_type_info* ty){
  void *ptr;
  SWIG_Ruby_ConvertPtr(obj,&ptr,ty,1);
  return ptr;
  }


// Should we catch exceptions thrown by message handlers?
FXbool FXRbCatchExceptions=FALSE;

// Returns an FXInputHandle for this Ruby file object
FXInputHandle FXRbGetReadFileHandle(VALUE obj) {
#ifdef RUBY_1_9
  rb_io_t *fptr;
  GetOpenFile(obj, fptr);
  FILE *fpr=fptr->stdio_file;
#else
  OpenFile *fptr;
  GetOpenFile(obj, fptr);
  FILE *fpr=GetReadFile(fptr);
#endif /* RUBY_1_9 */
#ifdef WIN32
#ifdef __CYGWIN__
  return (FXInputHandle) get_osfhandle(fileno(fpr));
#else
  return (FXInputHandle) _get_osfhandle(_fileno(fpr));
#endif
#else
  return (FXInputHandle) fileno(fpr);
#endif
  }


// Returns an FXInputHandle for this Ruby file object
FXInputHandle FXRbGetWriteFileHandle(VALUE obj) {
#ifdef RUBY_1_9
  rb_io_t *fptr;
  GetOpenFile(obj, fptr);
  FILE *fpw=fptr->stdio_file;
#else
  OpenFile *fptr;
  GetOpenFile(obj, fptr);
  FILE *fpw=GetWriteFile(fptr);
#endif /* RUBY_1_9 */
#ifdef WIN32
#ifdef __CYGWIN__
  return (FXInputHandle) get_osfhandle(fileno(fpw));
#else
  return (FXInputHandle) _get_osfhandle(_fileno(fpw));
#endif
#else
  return (FXInputHandle) fileno(fpw);
#endif
  }


// Register this Ruby class instance
void FXRbRegisterRubyObj(VALUE rubyObj,const void* foxObj) {
  FXASSERT(!NIL_P(rubyObj));
  FXASSERT(foxObj!=0);
  FXRubyObjDesc* desc;
  FXTRACE((1,"FXRbRegisterRubyObj(rubyObj=%d,foxObj=%p)\n",static_cast<int>(rubyObj),foxObj));
  if(FXMALLOC(&desc,FXRubyObjDesc,1)){
    desc->obj=rubyObj;
    desc->borrowed=false;
    st_insert(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t>(desc));
    }
  else{
    FXASSERT(FALSE);
    }
  FXASSERT(FXRbGetRubyObj(foxObj,false)==rubyObj);
  }


/**
 * Remove this mapping between a Ruby instance and a C++ object
 */
void FXRbUnregisterRubyObj(const void* foxObj){
  if(foxObj!=0){
    FXRubyObjDesc* desc;
    if(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t *>(&desc))!=0){
      DATA_PTR(desc->obj)=0;
      FXFREE(&desc);
      st_delete(FXRuby_Objects,reinterpret_cast<st_data_t *>(const_cast<void**>(&foxObj)),reinterpret_cast<st_data_t *>(0));
      FXASSERT(st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t *>(0))==0);
      }
    }
  }


VALUE to_ruby(const FXObject* obj){
  if(obj!=0){
    FXString className=obj->getClassName();
    if(className.length()>3){
      if(className.left(4)=="FXRb"){ className.replace(0,4,"FX"); }
      }
    FXString desc=className+" *";
    return FXRbGetRubyObj(obj,desc.text());
    }
  return Qnil;
  }


/**
 * Return the registered Ruby class instance associated with this
 * FOX object, or Qnil if not found.
 */
VALUE FXRbGetRubyObj(const void *foxObj,bool searchBoth){
  FXRubyObjDesc* desc;
  if(foxObj!=0 && st_lookup(FXRuby_Objects,reinterpret_cast<st_data_t>(const_cast<void*>(foxObj)),reinterpret_cast<st_data_t *>(&desc))!=0){
    FXASSERT(desc!=0);
    if(searchBoth){
      return desc->obj;
      }
    else{
      return desc->borrowed ? Qnil : desc->obj;
      }
    }
  else{
    return Qnil;
    }
  }

/**
 * Return the registered Ruby class instance associated with this
 * FOX object, or a new registered instance if not found.
 */
VALUE FXRbGetRubyObj(const void *foxObj,swig_type_info* ty){
  if(foxObj!=0){
    VALUE rbObj=FXRbGetRubyObj(foxObj,true);
    return NIL_P(rbObj) ? FXRbNewPointerObj(const_cast<void*>(foxObj),ty) : rbObj;
    }
  else{
    return Qnil;
    }
  }

VALUE FXRbGetRubyObj(const void *foxObj,const char *type){
  if(foxObj!=0){
    FXASSERT(type!=0);
    VALUE rbObj=FXRbGetRubyObj(foxObj,true);
    return NIL_P(rbObj) ? FXRbNewPointerObj(const_cast<void*>(foxObj),FXRbTypeQuery(type)) : rbObj;
    }
  else{
    return Qnil;
    }
  }

/**
 * Look up the Ruby instance associated with this C++ object, if any, and mark
 * that instance as in use.
 *
 * We previously only marked those Ruby instances that were "non-borrowed"
 * references to C++ objects, as a way to reduce the number of Ruby instances
 * on the heap.
 */
void FXRbGcMark(void *obj){
  if(obj){
    /**
     * If the 2nd argument to FXRbGetRubyObj() is false, we only mark
     * non-borrowed references. This has led to problems in the past
     * (see e.g. SourceForge Bug #703721). I think the correct solution
     * is to mark any Ruby reference this object, "borrowed" or not;
     * so the 2nd argument to FXRbGetRubyObj() is now true.
     *
     * If you feel compelled to change this back to FXGetRubyObj(obj,false),
     * please think about it first. Especially make sure that the shutter.rb
     * example program works if you invoke the GC in ShutterWindow#create;
     * make sure that the shutter items' contents don't get blown away!
     */
    VALUE value=FXRbGetRubyObj(obj,true);
    if(!NIL_P(value)){
      rb_gc_mark(value);
      }
    }
  }

//----------------------------------------------------------------------

// Returns a Ruby array of floats
VALUE FXRbMakeArray(const FXfloat* values,FXint size){
  VALUE result=rb_ary_new();
  for(FXint i=0; i<size; i++)
    rb_ary_push(result,rb_float_new(values[i]));
  return result;
  }

// Returns a Ruby array of floats
VALUE FXRbMakeArray(const FXdouble* values,FXint size){
  VALUE result=rb_ary_new();
  for(FXint i=0; i<size; i++)
    rb_ary_push(result,rb_float_new(values[i]));
  return result;
  }

// Returns a Ruby array of integers
VALUE FXRbMakeArray(const FXint* values,FXint size){
  VALUE result=rb_ary_new();
  for(FXint i=0; i<size; i++)
    rb_ary_push(result,INT2NUM(values[i]));
  return result;
  }

// Returns a Ruby array of integers
VALUE FXRbMakeArray(const FXuint* values,FXint size){
  VALUE result=rb_ary_new();
  for(FXint i=0; i<size; i++)
    rb_ary_push(result,UINT2NUM(values[i]));
  return result;
  }

// Returns a Ruby array of integers
VALUE FXRbMakeArray(const FXchar* dashpattern,FXuint dashlength){
  VALUE result=rb_ary_new();
  for(FXuint i=0; i<dashlength; i++)
    rb_ary_push(result,INT2NUM(dashpattern[i]));
  return result;
  }

// Returns a Ruby array of FXArcs
VALUE FXRbMakeArray(const FXArc* arcs,FXuint narcs){
  VALUE result=rb_ary_new();
  for(FXuint i=0; i<narcs; i++)
    rb_ary_push(result,FXRbGetRubyObj(&arcs[i],"FXArc *"));
  return result;
  }

// Returns a Ruby array of FXPoints
VALUE FXRbMakeArray(const FXPoint* points,FXuint npoints){
  VALUE result=rb_ary_new();
  for(FXuint i=0; i<npoints; i++)
    rb_ary_push(result,FXRbGetRubyObj(&points[i],"FXPoint *"));
  return result;
  }

// Returns a Ruby array of FXRectangles
VALUE FXRbMakeArray(const FXRectangle* rectangles,FXuint nrectangles){
  VALUE result=rb_ary_new();
  for(FXuint i=0; i<nrectangles; i++)
    rb_ary_push(result,FXRbGetRubyObj(&rectangles[i],"FXRectangle *"));
  return result;
  }
  
// Returns a Ruby array of FXSegments
VALUE FXRbMakeArray(const FXSegment* segments,FXuint nsegments){
  VALUE result=rb_ary_new();
  for(FXuint i=0; i<nsegments; i++)
    rb_ary_push(result,FXRbGetRubyObj(&segments[i],"FXSegment *"));
  return result;
  }

// Returns a Ruby array of FXColor values
VALUE FXRbMakeColorArray(const FXColor* colors,FXint w,FXint h){
  VALUE result=rb_ary_new();
  FXint size=w*h;
  for(FXuint i=0; i<size; i++)
    rb_ary_push(result,to_ruby(colors[i]));
  return result;
  }

//----------------------------------------------------------------------

/**
 * Based on the sender object's class and the selector, convert the message
 * data stored in the void pointer (ptr) to a suitable Ruby object.
 *
 * This function is used when we need to pass message data into a Ruby
 * code block (or method) that is acting as a FOX message handler.
 */
static VALUE FXRbConvertMessageData(FXObject* sender,FXObject* recv,FXSelector sel,void* ptr){
  FXTRACE((1,"FXRbConvertMessageData(%s(%p),FXSEL(%s,%d),%p)\n",sender->getClassName(),sender,FXDebugTarget::messageTypeName[FXSELTYPE(sel)],FXSELID(sel),ptr));
  FXInputHandle fff;
  FXushort type=FXSELTYPE(sel);
  FXushort id=FXSELID(sel);

  FXASSERT(type!=SEL_NONE);
  FXASSERT(type!=SEL_LAST);

  if(type==SEL_KEYPRESS ||
     type==SEL_KEYRELEASE ||
     type==SEL_LEFTBUTTONPRESS ||
     type==SEL_LEFTBUTTONRELEASE ||
     type==SEL_MIDDLEBUTTONPRESS ||
     type==SEL_MIDDLEBUTTONRELEASE ||
     type==SEL_RIGHTBUTTONPRESS ||
     type==SEL_RIGHTBUTTONRELEASE ||
     type==SEL_MOTION ||
     type==SEL_ENTER ||
     type==SEL_LEAVE ||
     type==SEL_FOCUSIN ||
     type==SEL_FOCUSOUT ||
     type==SEL_KEYMAP ||
     type==SEL_UNGRABBED ||
     type==SEL_PAINT ||
     type==SEL_CREATE ||
     type==SEL_DESTROY ||
     type==SEL_UNMAP ||
     type==SEL_MAP ||
     type==SEL_CONFIGURE ||
     type==SEL_SELECTION_LOST ||
     type==SEL_SELECTION_GAINED ||
     type==SEL_SELECTION_REQUEST ||
     type==SEL_RAISED ||
     type==SEL_LOWERED ||
     type==SEL_MOUSEWHEEL ||
     type==SEL_BEGINDRAG ||
     type==SEL_ENDDRAG ||
     type==SEL_TIMEOUT ||
     type==SEL_CLIPBOARD_LOST ||
     type==SEL_CLIPBOARD_GAINED ||
     type==SEL_CLIPBOARD_REQUEST ||
     type==SEL_CHORE ||
     type==SEL_FOCUS_SELF ||
     type==SEL_FOCUS_RIGHT ||
     type==SEL_FOCUS_LEFT ||
     type==SEL_FOCUS_DOWN ||
     type==SEL_FOCUS_UP ||
     type==SEL_FOCUS_NEXT ||
     type==SEL_FOCUS_PREV ||
     type==SEL_DND_ENTER ||
     type==SEL_DND_LEAVE ||
     type==SEL_DND_DROP ||
     type==SEL_DND_MOTION ||
     type==SEL_DND_REQUEST ||
     type==SEL_PICKED ||
     type==SEL_SESSION_NOTIFY ||
     type==SEL_SESSION_CLOSED) {
    return to_ruby(reinterpret_cast<FXEvent*>(ptr));
    }
  else if(type==SEL_DRAGGED && !sender->isMemberOf(FXMETACLASS(FXGLViewer))){
    return to_ruby(reinterpret_cast<FXEvent*>(ptr));
    }
  else if(type==SEL_SIGNAL){
    return to_ruby(static_cast<int>(reinterpret_cast<long>(ptr)));
    }
  else if(type==SEL_IO_READ ||
          type==SEL_IO_WRITE ||
	  type==SEL_IO_EXCEPT){
#ifdef WIN32
    fff=reinterpret_cast<FXInputHandle>(ptr);
#else
    fff=static_cast<FXInputHandle>(reinterpret_cast<long>(ptr));
#endif
    return Qnil;
    }
  else if(type==SEL_CLOSE ||
          type==SEL_DELETE ||
          type==SEL_MINIMIZE ||
          type==SEL_RESTORE ||
          type==SEL_MAXIMIZE ||
          type==SEL_UPDATE ||
          type==SEL_QUERY_HELP ||
	  type==SEL_QUERY_TIP){
    FXASSERT(ptr==0);
    return Qnil;
    }
  else if(sender->isMemberOf(FXMETACLASS(FX4Splitter))){
    if(type==SEL_CHANGED||type==SEL_COMMAND) return Qnil;
    }
  else if(sender->isMemberOf(FXMETACLASS(FXArrowButton))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXuint>(reinterpret_cast<FXuval>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXPicker))){
    if(type==SEL_COMMAND || type==SEL_CHANGED) return to_ruby(reinterpret_cast<FXPoint*>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXButton))){
    if(type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED ||
       type==SEL_COMMAND) return to_ruby(static_cast<FXuint>(reinterpret_cast<FXuval>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXCheckButton))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXuchar>(reinterpret_cast<FXuval>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXColorBar))){
    if(type==SEL_CHANGED || type==SEL_COMMAND){
      FXfloat* hsv=reinterpret_cast<FXfloat*>(ptr);
      return rb_ary_new3(3,to_ruby(hsv[0]),to_ruby(hsv[1]),to_ruby(hsv[2]));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXColorDialog))){
    if(type==SEL_CHANGED || type==SEL_COMMAND) return to_ruby(static_cast<FXColor>(reinterpret_cast<unsigned long>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXColorRing))){
    if(type==SEL_CHANGED || type==SEL_COMMAND){
      FXfloat* hsv=reinterpret_cast<FXfloat*>(ptr);
      return rb_ary_new3(3,to_ruby(hsv[0]),to_ruby(hsv[1]),to_ruby(hsv[2]));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXColorSelector))){
    if(type==SEL_CHANGED || type==SEL_COMMAND) return to_ruby(static_cast<FXColor>(reinterpret_cast<unsigned long>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXColorWell))){
    if(type==SEL_CHANGED ||
       type==SEL_COMMAND ||
       type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED) {
	       VALUE v=to_ruby(static_cast<FXColor>(reinterpret_cast<unsigned long>(ptr)));
	       return v;
    }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXColorWheel))){
    if(type==SEL_CHANGED || type==SEL_COMMAND){
      FXfloat* hsv=reinterpret_cast<FXfloat*>(ptr);
      return rb_ary_new3(3,to_ruby(hsv[0]),to_ruby(hsv[1]),to_ruby(hsv[2]));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXComboBox))){
    if(type==SEL_CHANGED || type==SEL_COMMAND) return to_ruby(reinterpret_cast<FXchar*>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXDataTarget))){
    if(type==SEL_COMMAND || type==SEL_CHANGED){
      if(recv->isMemberOf(FXMETACLASS(FXWindow))){
        switch(id){
          case FXWindow::ID_SETINTVALUE:
            return to_ruby(*reinterpret_cast<FXint*>(ptr));
          case FXWindow::ID_SETREALVALUE:
            return to_ruby(*reinterpret_cast<FXdouble*>(ptr));
          case FXWindow::ID_SETSTRINGVALUE:
            return to_ruby(*reinterpret_cast<FXString*>(ptr));
          case FXWindow::ID_GETINTVALUE:
          case FXWindow::ID_GETREALVALUE:
          case FXWindow::ID_GETSTRINGVALUE:
            FXASSERT(FALSE);
            break;
          default:
            FXASSERT(FALSE);
          }
        }
      else{
        // It's not a window object...
        FXASSERT(sender->isMemberOf(FXMETACLASS(FXRbDataTarget)));
        return dynamic_cast<FXRbDataTarget*>(sender)->getValue();
        }
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXDial))){
    if(type==SEL_CHANGED || type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXDirBox))){
    if(type==SEL_CHANGED || type==SEL_COMMAND) return to_ruby(reinterpret_cast<FXchar*>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXDockBar))){
    if(type==SEL_DOCKED || type==SEL_FLOATED) return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXDockSite *"));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXFileList))){
    if (type==SEL_CHANGED ||
        type==SEL_CLICKED ||
        type==SEL_DOUBLECLICKED ||
        type==SEL_TRIPLECLICKED ||
        type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXFoldingList))){
    if(type==SEL_COLLAPSED ||
       type==SEL_EXPANDED ||
       type==SEL_COMMAND ||
       type==SEL_CHANGED ||
       type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED ||
       type==SEL_OPENED ||
       type==SEL_CLOSED ||
       type==SEL_SELECTED ||
       type==SEL_DESELECTED ||
       type==SEL_INSERTED ||
       type==SEL_DELETED){
      return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXFoldingItem *"));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXGLViewer))){
    if(type==SEL_CHANGED ||
       type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED ||
       type==SEL_DRAGGED){
      return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXGLObject *"));
      }
    else if(type==SEL_COMMAND){
      if(id==FXWindow::ID_QUERY_MENU)
        return to_ruby(reinterpret_cast<FXEvent*>(ptr));
      else
        return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXGLObject *"));
      }
    else if(type==SEL_LASSOED ||
            type==SEL_INSERTED ||
            type==SEL_DELETED ||
            type==SEL_SELECTED ||
            type==SEL_DESELECTED){
      VALUE ary=rb_ary_new();
      // FXGLObject** objlist=reinterpret_cast<FXGLObject**>(ptr);
      // FIXME: objlist is a NULL-terminated array of pointers to FXGLObject
      return ary;
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXGradientBar))){
    if(type==SEL_CHANGED){
      return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
      }
    else if(type==SEL_SELECTED || type==SEL_DESELECTED){
      return Qnil;
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXHeader))){
    if(type==SEL_COMMAND ||
       type==SEL_CHANGED ||
       type==SEL_CLICKED ||
       type==SEL_REPLACED ||
       type==SEL_INSERTED ||
       type==SEL_DELETED) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXIconList))){
    if(type==SEL_CHANGED ||
       type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED ||
       type==SEL_COMMAND ||
       type==SEL_SELECTED ||
       type==SEL_DESELECTED ||
       type==SEL_REPLACED ||
       type==SEL_INSERTED ||
       type==SEL_DELETED) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXKnob))){
    if(type==SEL_CHANGED || type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXList))){
    if(type==SEL_CHANGED ||
       type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED ||
       type==SEL_SELECTED ||
       type==SEL_DESELECTED ||
       type==SEL_REPLACED ||
       type==SEL_INSERTED ||
       type==SEL_DELETED ||
       type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXListBox))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    else if(type==SEL_CHANGED) return Qnil;
    }
  else if(sender->isMemberOf(FXMETACLASS(FXMDIChild))){
    if(type==SEL_MINIMIZE ||
       type==SEL_MAXIMIZE ||
       type==SEL_CLOSE ||
       type==SEL_RESTORE){
       return Qnil;
      }
    else if(type==SEL_SELECTED ||
            type==SEL_DESELECTED){
      return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXMDIChild *"));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXMDIClient))){
    if(type==SEL_CHANGED) return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXMDIChild *"));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXMenuCheck))){
    if(type==SEL_COMMAND) return to_ruby(reinterpret_cast<FXuval>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXMenuRadio))){
    if(type==SEL_COMMAND) return to_ruby(reinterpret_cast<FXuval>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXMenuCommand))){
    if(type==SEL_COMMAND) return to_ruby(true);
    }
  else if(sender->isMemberOf(FXMETACLASS(FXOption))){
    if(type==SEL_COMMAND) return to_ruby(reinterpret_cast<FXEvent*>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXOptionMenu))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXRadioButton))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXuchar>(reinterpret_cast<FXuval>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXRealSlider))){
    if(type==SEL_CHANGED || type==SEL_COMMAND)
      return to_ruby(*(reinterpret_cast<FXdouble *>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXRealSpinner))){
    if(type==SEL_COMMAND || type==SEL_CHANGED) return to_ruby(*(reinterpret_cast<FXdouble *>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXRecentFiles))){
    if(type==SEL_COMMAND) return to_ruby(reinterpret_cast<FXchar*>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXRuler))){
    if(type==SEL_CHANGED) return Qnil;
    }
  else if(sender->isMemberOf(FXMETACLASS(FXScrollBar))){
    if(type==SEL_CHANGED || type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXShutter))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXSlider))){
    if(type==SEL_CHANGED || type==SEL_COMMAND)
      return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXSpinner))){
    if(type==SEL_CHANGED || type==SEL_COMMAND)
      return to_ruby(static_cast<FXint>(reinterpret_cast<long>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXSplitter))){
    if(type==SEL_CHANGED || type==SEL_COMMAND)
      return to_ruby(reinterpret_cast<FXWindow *>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXSwitcher))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXTabBar))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXTable))){
    if(type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED ||
       type==SEL_CHANGED ||
       type==SEL_COMMAND ||
       type==SEL_SELECTED ||
       type == SEL_DESELECTED) return to_ruby(reinterpret_cast<FXTablePos*>(ptr));
    else if(type == SEL_INSERTED ||
            type == SEL_DELETED ||
            type == SEL_REPLACED){
	      return to_ruby(reinterpret_cast<FXTableRange*>(ptr));
	      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXText))){
    if     (type == SEL_COMMAND) {
      switch(id){
        case FXText::ID_COPY_SEL:
        case FXText::ID_PASTE_SEL:
        case FXText::ID_DELETE_SEL:
          return Qnil;
          break;
        default:
          FXASSERT(FALSE);
          return reinterpret_cast<VALUE>(ptr); // pass-through as is
        }
      }
    else if(type==SEL_CHANGED){
      return to_ruby(static_cast<FXint>(reinterpret_cast<FXival>(ptr)));
      }
    else if(type==SEL_SELECTED ||
            type == SEL_DESELECTED) {
      FXint* what=reinterpret_cast<FXint*>(ptr);
      FXASSERT(what!=0);
      VALUE ary=rb_ary_new();
      rb_ary_push(ary,to_ruby(what[0])); // start position of text
      rb_ary_push(ary,to_ruby(what[1])); // length of text
      return ary;
      }
    else if(type==SEL_INSERTED || type==SEL_DELETED || type==SEL_REPLACED) {
      return to_ruby(reinterpret_cast<FXTextChange*>(ptr));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXTextField))){
    if(type==SEL_CHANGED ||
       type==SEL_COMMAND ||
       type==SEL_VERIFY) return to_ruby(reinterpret_cast<FXchar*>(ptr));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXToggleButton))){
    if(type==SEL_COMMAND) return to_ruby(static_cast<FXuchar>(reinterpret_cast<FXuval>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXToolBarTab))){
    if (type==SEL_COMMAND) return to_ruby(static_cast<FXbool>(reinterpret_cast<FXuval>(ptr)));
    }
  else if(sender->isMemberOf(FXMETACLASS(FXTopWindow))){
    if(type==SEL_MINIMIZE ||
       type==SEL_MAXIMIZE ||
       type==SEL_RESTORE ||
       type==SEL_CLOSE){
      return Qnil;
      }
    else if (type==SEL_SESSION_NOTIFY ||
             type==SEL_SESSION_CLOSED) {
      return to_ruby(reinterpret_cast<FXEvent*>(ptr));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXTreeList))){
    if(type==SEL_COLLAPSED ||
       type==SEL_EXPANDED ||
       type==SEL_COMMAND ||
       type==SEL_CHANGED ||
       type==SEL_CLICKED ||
       type==SEL_DOUBLECLICKED ||
       type==SEL_TRIPLECLICKED ||
       type==SEL_OPENED ||
       type==SEL_CLOSED ||
       type==SEL_SELECTED ||
       type==SEL_DESELECTED ||
       type==SEL_INSERTED ||
       type==SEL_DELETED){
      return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXTreeItem *"));
      }
    }
  else if(sender->isMemberOf(FXMETACLASS(FXTreeListBox))){
    if(type==SEL_CHANGED || type==SEL_COMMAND)
      return FXRbGetRubyObj(ptr,FXRbTypeQuery("FXTreeItem *"));
    }
#ifdef WITH_FXSCINTILLA
  else if(sender->isMemberOf(FXMETACLASS(FXScintilla))){
    if(type==SEL_COMMAND){
      return FXRbGetRubyObj(ptr,FXRbTypeQuery("SCNotification *"));
      }
    }
#endif
  else{
    FXTRACE((100,"%s:%d: message data passed through as-is\n",__FILE__,__LINE__));
    return reinterpret_cast<VALUE>(ptr); // pass-through as is
    }
  FXTRACE((100,"%s:%d: message data passed through as-is\n",__FILE__,__LINE__));
  return reinterpret_cast<VALUE>(ptr); // pass-through as is
  }


/**
 * When a Ruby instance (e.g. one of your widgets) calls handle() on another
 * object, e.g.
 *
 *     def onUpdAnswer(sender, sel, ptr)
 *       if theAnswerIsTwo?
 *         sender.handle(self, FXSEL(SEL_COMMAND,FXWindow::ID_SETVALUE), 2)
 *       else
 *         sender.handle(self, FXSEL(SEL_COMMAND,FXWindow::ID_SETVALUE), 3)
 *       end
 *       return 1
 *     end
 *
 * it's usually the case that this will get passed along to the underlying
 * C++ object. In that case, we need to convert the message data (e.g. the
 * Fixnums "2" or "3" in the example above) from Ruby objects back into
 * the appropriate C++ objects. That's what this function is for.
 */
void* FXRbGetExpectedData(VALUE recv,FXSelector key,VALUE value){
  void *ptr;
  static FXint intValue;
  static FXint intRange[2];
  static FXdouble realValue;
  static FXdouble realRange[2];
  static FXString stringValue;
  static FXColor colorValue;
  FXushort type=FXSELTYPE(key);
  FXushort id=FXSELID(key);

  // Extract the FOX object (the receiver) from this Ruby instance
  FXObject* obj;
  Data_Get_Struct(recv,FXObject,obj);

  FXASSERT(type!=SEL_NONE);
  FXASSERT(type!=SEL_LAST);
  switch(type){
    case SEL_KEYPRESS:
    case SEL_KEYRELEASE:
    case SEL_LEFTBUTTONPRESS:
    case SEL_LEFTBUTTONRELEASE:
    case SEL_MIDDLEBUTTONPRESS:
    case SEL_MIDDLEBUTTONRELEASE:
    case SEL_RIGHTBUTTONPRESS:
    case SEL_RIGHTBUTTONRELEASE:
    case SEL_MOTION:
    case SEL_ENTER:
    case SEL_LEAVE:
    case SEL_FOCUSIN:
    case SEL_FOCUSOUT:
    case SEL_KEYMAP:
    case SEL_UNGRABBED:
    case SEL_PAINT:
    case SEL_CREATE:
    case SEL_DESTROY:
    case SEL_UNMAP:
    case SEL_MAP:
    case SEL_CONFIGURE:
    case SEL_SELECTION_LOST:
    case SEL_SELECTION_GAINED:
    case SEL_SELECTION_REQUEST:
    case SEL_RAISED:
    case SEL_LOWERED:
    case SEL_MOUSEWHEEL:
    case SEL_BEGINDRAG:
    case SEL_ENDDRAG:
    case SEL_LASSOED:
    case SEL_TIMEOUT:
    case SEL_CLIPBOARD_LOST:
    case SEL_CLIPBOARD_GAINED:
    case SEL_CLIPBOARD_REQUEST:
    case SEL_CHORE:
    case SEL_FOCUS_SELF:
    case SEL_FOCUS_RIGHT:
    case SEL_FOCUS_LEFT:
    case SEL_FOCUS_DOWN:
    case SEL_FOCUS_UP:
    case SEL_FOCUS_NEXT:
    case SEL_FOCUS_PREV:
    case SEL_DND_ENTER:
    case SEL_DND_LEAVE:
    case SEL_DND_DROP:
    case SEL_DND_MOTION:
    case SEL_DND_REQUEST:
    case SEL_PICKED:
      SWIG_Ruby_ConvertPtr(value,&ptr,FXRbTypeQuery("FXEvent *"),1);
      return ptr;
    case SEL_IO_READ:
    case SEL_IO_WRITE:
    case SEL_IO_EXCEPT:
      return 0; // should be an FXInputHandle?
    case SEL_SIGNAL:
      return reinterpret_cast<void*>(static_cast<long>(NUM2INT(value)));
    case SEL_CLOSE:
    case SEL_DELETE:
    case SEL_MINIMIZE:
    case SEL_RESTORE:
    case SEL_MAXIMIZE:
    case SEL_UPDATE:
    case SEL_QUERY_TIP:
    case SEL_QUERY_HELP:
      return NULL;
    case SEL_VERIFY:
      return reinterpret_cast<void*>(StringValuePtr(value));
    case SEL_CLICKED:
    case SEL_DOUBLECLICKED:
    case SEL_TRIPLECLICKED:
    case SEL_CHANGED:
    case SEL_DESELECTED:
    case SEL_SELECTED:
    case SEL_INSERTED:
    case SEL_REPLACED:
    case SEL_DELETED:
    case SEL_OPENED:
    case SEL_CLOSED:
    case SEL_EXPANDED:
    case SEL_COLLAPSED:
      return NULL;
    default:
      /* Ignore */
      break;
    }

  if(type==SEL_COMMAND){
    // Handle FXText-specific messages
    if(obj->isMemberOf(FXMETACLASS(FXText))){
      switch(id){
        case FXText::ID_COPY_SEL:
        case FXText::ID_PASTE_SEL:
        case FXText::ID_DELETE_SEL:
          return NULL;
        default:
          break;
        }
      }

    // Handle FXTextField-specific message
    if(obj->isMemberOf(FXMETACLASS(FXTextField))){
      switch(id){
        case FXTextField::ID_INSERT_STRING:
          return reinterpret_cast<void*>(StringValuePtr(value));;
        default:
          break;
        }
      }

    // Handle messages applicable to all FXWindow descendants
    if(obj->isMemberOf(FXMETACLASS(FXWindow))){
      switch(id){
        case FXWindow::ID_HIDE:
        case FXWindow::ID_SHOW:
        case FXWindow::ID_TOGGLESHOWN:
        case FXWindow::ID_LOWER:
        case FXWindow::ID_RAISE:
        case FXWindow::ID_DELETE:
        case FXWindow::ID_DISABLE:
        case FXWindow::ID_ENABLE:
        case FXWindow::ID_UNCHECK:
        case FXWindow::ID_CHECK:
        case FXWindow::ID_UNKNOWN:
        case FXWindow::ID_UPDATE:
        case FXWindow::ID_AUTOSCROLL:
        case FXWindow::ID_QUERY_MENU:
        case FXWindow::ID_HOTKEY:
        case FXWindow::ID_ACCEL:
        case FXWindow::ID_UNPOST:
        case FXWindow::ID_POST:
        case FXWindow::ID_MDI_TILEHORIZONTAL:
        case FXWindow::ID_MDI_TILEVERTICAL:
        case FXWindow::ID_MDI_CASCADE:
        case FXWindow::ID_MDI_MAXIMIZE:
        case FXWindow::ID_MDI_MINIMIZE:
        case FXWindow::ID_MDI_RESTORE:
        case FXWindow::ID_MDI_CLOSE:
        case FXWindow::ID_MDI_WINDOW:
        case FXWindow::ID_MDI_MENUWINDOW:
        case FXWindow::ID_MDI_MENUMINIMIZE:
        case FXWindow::ID_MDI_MENURESTORE:
        case FXWindow::ID_MDI_MENUCLOSE:
        case FXWindow::ID_MDI_NEXT:
        case FXWindow::ID_MDI_PREV:
          return NULL;
        case FXWindow::ID_SETVALUE:
          if(obj->isMemberOf(FXMETACLASS(FXButton)) ||
             obj->isMemberOf(FXMETACLASS(FXCheckButton)) ||
             obj->isMemberOf(FXMETACLASS(FXDial)) ||
             obj->isMemberOf(FXMETACLASS(FXRadioButton)) ||
             obj->isMemberOf(FXMETACLASS(FXShutter)) ||
             obj->isMemberOf(FXMETACLASS(FXSpinner)) ||
             obj->isMemberOf(FXMETACLASS(FXTabBar)) ||
             obj->isMemberOf(FXMETACLASS(FXToggleButton)) ||
             obj->isMemberOf(FXMETACLASS(FXScrollBar)) ||
             obj->isMemberOf(FXMETACLASS(FXSlider)) ||
             obj->isMemberOf(FXMETACLASS(FXSwitcher))){
            return reinterpret_cast<void*>(static_cast<long>(NUM2INT(value)));
            }
          else if(obj->isMemberOf(FXMETACLASS(FXColorSelector)) ||
                  obj->isMemberOf(FXMETACLASS(FXColorWell))){
            return reinterpret_cast<void*>(static_cast<unsigned long>(NUM2UINT(value)));
            }
          else if(obj->isMemberOf(FXMETACLASS(FXProgressBar))){
            return reinterpret_cast<void*>(static_cast<unsigned long>(NUM2UINT(value)));
            }
          else if(obj->isMemberOf(FXMETACLASS(FXComboBox)) ||
                  obj->isMemberOf(FXMETACLASS(FXTextField)) ||
                  obj->isMemberOf(FXMETACLASS(FXDirBox)) ||
                  obj->isMemberOf(FXMETACLASS(FXDirList)) ||
                  obj->isMemberOf(FXMETACLASS(FXDriveBox)) ||
                  obj->isMemberOf(FXMETACLASS(FXFileList))){
            return reinterpret_cast<void*>(StringValuePtr(value));
            }
          else if(obj->isMemberOf(FXMETACLASS(FXMenuCheck))){
            return reinterpret_cast<void*>(static_cast<FXuval>(RTEST(value) ? 1 : 0));
            }
          else if(obj->isMemberOf(FXMETACLASS(FXMenuRadio))){
            return reinterpret_cast<void*>(static_cast<FXuval>(RTEST(value) ? 1 : 0));
				    }
          else if(obj->isMemberOf(FXMETACLASS(FXMenuCommand))){
            return reinterpret_cast<void*>(static_cast<FXuval>(RTEST(value) ? 1 : 0));
            }
          return NULL;
        case FXWindow::ID_HSCROLLED:
        case FXWindow::ID_VSCROLLED:
          return reinterpret_cast<void*>(static_cast<unsigned long>(NUM2UINT(value)));
        case FXWindow::ID_SETINTVALUE:
          if(obj->isMemberOf(FXMETACLASS(FXColorWell))){
            colorValue=NUM2UINT(value);
            return reinterpret_cast<void*>(&colorValue);
            }
          else{
            intValue=NUM2INT(value);
            return reinterpret_cast<void*>(&intValue);
            }
        case FXWindow::ID_SETREALVALUE:
          realValue=NUM2DBL(value);
          return reinterpret_cast<void*>(&realValue);
        case FXWindow::ID_SETSTRINGVALUE:
          stringValue=FXString(StringValuePtr(value));
          return reinterpret_cast<void*>(&stringValue);
        case FXWindow::ID_SETINTRANGE:
          intRange[0]=NUM2INT(rb_ary_entry(value,0));
          intRange[1]=NUM2INT(rb_ary_entry(value,1));
          return reinterpret_cast<void*>(intRange);
        case FXWindow::ID_SETREALRANGE:
          realRange[0]=NUM2DBL(rb_ary_entry(value,0));
          realRange[1]=NUM2DBL(rb_ary_entry(value,1));
          return reinterpret_cast<void*>(realRange);
        case FXWindow::ID_GETINTVALUE:
        case FXWindow::ID_GETREALVALUE:
        case FXWindow::ID_GETSTRINGVALUE:
        case FXWindow::ID_GETINTRANGE:
        case FXWindow::ID_GETREALRANGE:
          return NULL;
        default:
          // Pass this data along as-is
          break;
        }
      }
    }

  if(type==SEL_CHANGED){
	  if(obj->isMemberOf(FXMETACLASS(FXPicker))){
			SWIG_Ruby_ConvertPtr(value,&ptr,FXRbTypeQuery("FXPoint *"),1);
			return ptr;
	    }
		return 0;
    }
	
	if(type==SEL_DRAGGED){
	    SWIG_Ruby_ConvertPtr(value,&ptr,FXRbTypeQuery("FXEvent *"),1);
	    return ptr;
	    }

  // Pass through as-is
  return reinterpret_cast<void*>(value);
  }


static ID id_assocs;


/**
 * Look up the name of the message handler function for this
 * receiver and message (type, id) combination and return it;
 * or return zero if the designated receiver doesn't handle this
 * message.
 */
ID FXRbLookupHandler(FXObject* recv,FXSelector key){
  FXTRACE((100,"FXRbLookupHandler(recv=%p(%s),FXSEL(%d,%d))\n",recv,recv->getClassName(),FXSELTYPE(key),FXSELID(key)));
  ID id=0;
  VALUE rubyObj=to_ruby(recv);
  FXASSERT((recv==0 && rubyObj==Qnil) || (recv!=0 && rubyObj!=Qnil));
  if(rb_ivar_defined(rubyObj,id_assocs)==Qtrue){
    VALUE assocs=rb_ivar_get(rubyObj,id_assocs);
    VALUE entry;
    FXSelector keylo,keyhi;
    for(long i=0;i<RARRAY_LEN(assocs);i++){
      entry=rb_ary_entry(assocs,i);
      keylo=NUM2UINT(rb_ary_entry(entry,0));
      keyhi=NUM2UINT(rb_ary_entry(entry,1));
      if(keylo<=key && key<=keyhi){
        id=SYM2ID(rb_ary_entry(entry,2));
	FXASSERT(id!=0);
	break;
        }
      }
    }
  return id;
  }


struct FXRbHandleArgs {
  VALUE recv;
  VALUE id;
  int nargs;
  VALUE sender;
  VALUE key;
  VALUE data;
  };


static VALUE handle_body(VALUE args){
  FXRbHandleArgs* hArgs=reinterpret_cast<FXRbHandleArgs*>(args);
  FXASSERT(hArgs!=0);
  return rb_funcall(hArgs->recv,hArgs->id,hArgs->nargs,hArgs->sender,hArgs->key,hArgs->data);
  }


static ID id_backtrace;


static VALUE handle_rescue(VALUE args,VALUE error){
  VALUE info=rb_gv_get("$!");
  VALUE errat=rb_funcall(info,id_backtrace,0);
  VALUE mesg=RARRAY_PTR(errat)[0];
  fprintf(stderr,"%s: %s (%s)\n",
    StringValuePtr(mesg),
    RSTRING_PTR(rb_obj_as_string(info)),
    rb_class2name(CLASS_OF(info)));
  for(int i=1;i<RARRAY_LEN(errat);i++){
    if(TYPE(RARRAY_PTR(errat)[i])==T_STRING){
      fprintf(stderr,"\tfrom %s\n",StringValuePtr(RARRAY_PTR(errat)[i]));
      }
    }
  return Qnil;
  }


// Call the designated function and return its result (which should be a long).
long FXRbHandleMessage(FXObject* recv,ID func,FXObject* sender,FXSelector key,void* ptr){
  FXRbHandleArgs hArgs;
  hArgs.recv=to_ruby(recv);
  hArgs.sender=to_ruby(sender);
  hArgs.key=to_ruby(key);
  hArgs.data=FXRbConvertMessageData(sender,recv,key,ptr);
  hArgs.id=func;
  hArgs.nargs=3;
  VALUE retval;

  FXTRACE((100,"FXRbHandleMessage(recv=%p(%s),FXSEL(%s,%d)\n",recv,recv->getClassName(),FXDebugTarget::messageTypeName[FXSELTYPE(key)],FXSELID(key)));

  if(FXRbCatchExceptions){
#ifdef RB_RESCUE2_BROKEN_PROTOTYPE
    retval=rb_rescue2((VALUE(*)()) handle_body, reinterpret_cast<VALUE>(&hArgs),
                      (VALUE(*)()) handle_rescue, Qnil,
                      rb_eStandardError, rb_eNameError, 0);
#else
    retval=rb_rescue2((VALUE(*)(ANYARGS)) handle_body, reinterpret_cast<VALUE>(&hArgs),
                      (VALUE(*)(ANYARGS)) handle_rescue, Qnil,
                      rb_eStandardError, rb_eNameError, 0);
#endif
    }
  else{
    retval=handle_body(reinterpret_cast<VALUE>(&hArgs));
    }

  /**
   * Process the return value. For boolean return values, convert "true"
   * to 1 and "false" to zero. For numeric types, convert it to a long value
   * but trap the result to either 0 or 1 since these are usually what
   * FOX is looking for. For any other type result (including nil) return 1.
   * Thanks to Ted Meng for this suggestion.
   */
  long lresult;
  switch(TYPE(retval)){
    case T_TRUE:
      lresult=1;
      break;
    case T_FALSE:
      lresult=0;
      break;
    case T_BIGNUM:
      lresult=1;
      break;
    case T_FIXNUM:
    case T_FLOAT:
      lresult=(NUM2LONG(retval) == 0) ? 0 : 1; // trap any numeric result to either 0 or 1
      break;
    default:
      lresult=1;
    }
  return lresult;
  }

//----------------------------------------------------------------------

static ID id_begin;
static ID id_end;
static ID id_exclude_endp;

void FXRbRange2LoHi(VALUE range,FXint& lo,FXint& hi){
  if(Qtrue!=rb_obj_is_instance_of(range,rb_cRange)){
    rb_raise(rb_eTypeError,"wrong argument type %s (expected %s)",rb_class2name(CLASS_OF(range)),rb_class2name(rb_cRange));
    }
  else{
    VALUE beg=rb_funcall(range,id_begin,0,NULL);
    VALUE end=rb_funcall(range,id_end,0,NULL);
    VALUE excl=rb_funcall(range,id_exclude_endp,0,NULL);
    lo=NUM2INT(beg);
    hi=NUM2INT(end);
    if(excl==Qtrue){
      hi--;
      }
    }
  }

void FXRbRange2LoHi(VALUE range,FXdouble& lo,FXdouble& hi){
  if(Qtrue!=rb_obj_is_instance_of(range,rb_cRange)){
    rb_raise(rb_eTypeError,"wrong argument type %s (expected %s)",rb_class2name(CLASS_OF(range)),rb_class2name(rb_cRange));
    }
  else{
    VALUE beg=rb_funcall(range,id_begin,0,NULL);
    VALUE end=rb_funcall(range,id_end,0,NULL);
    VALUE excl=rb_funcall(range,id_exclude_endp,0,NULL);
    lo=NUM2DBL(beg);
    hi=NUM2DBL(end);
    if(excl==Qtrue){
      hi--;
      }
    }
  }
  
//----------------------------------------------------------------------

void FXRbCallVoidMethod(FXObject* recv, ID func) {
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,func,0,NULL);
  }

void FXRbCallVoidMethod(FXDC* recv,ID func) {
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,func,0,NULL);
  }

//----------------------------------------------------------------------

bool FXRbCallBoolMethod(const FXObject* recv,ID func){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,func,0,NULL);
  return (v==Qtrue);
  }

//----------------------------------------------------------------------

// Call function with "FXint" return value
FXint FXRbCallIntMethod(const FXObject* recv,ID func){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,0,NULL);
  return static_cast<FXint>(NUM2INT(result));
  }

//----------------------------------------------------------------------

// Call function with "FXGLObject*" return value
FXGLObject* FXRbCallGLObjectMethod(FXGLObject* recv,ID func){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,0,NULL);
  return NIL_P(result) ? 0 : reinterpret_cast<FXGLObject*>(DATA_PTR(result));
  }

FXGLObject* FXRbCallGLObjectMethod(FXGLViewer* recv,ID func,FXint x,FXint y){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,2,INT2NUM(x),INT2NUM(y));
  return NIL_P(result) ? 0 : reinterpret_cast<FXGLObject*>(DATA_PTR(result));
  }

FXGLObject* FXRbCallGLObjectMethod(FXGLObject* recv,ID func,FXuint* path,FXint n){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,1,FXRbMakeArray(path,n));
  return NIL_P(result) ? 0 : reinterpret_cast<FXGLObject*>(DATA_PTR(result));
  }

//----------------------------------------------------------------------

// Call function with "FXGLObject**" return value
FXGLObject** FXRbCallGLObjectArrayMethod(FXGLViewer* recv,ID func,FXint x,FXint y,FXint w,FXint h){
  FXGLObject** objects=NULL;
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,4,INT2NUM(x),INT2NUM(y),INT2NUM(w),INT2NUM(h));
  if(!NIL_P(result)){
    Check_Type(result,T_ARRAY);
    if(FXMALLOC(&objects,FXGLObject*,RARRAY_LEN(result)+1)){
      for(long i=0; i<RARRAY_LEN(result); i++){
	objects[i]=reinterpret_cast<FXGLObject*>(DATA_PTR(rb_ary_entry(result,i)));
        }
      objects[RARRAY_LEN(result)]=0;
      }
    }
  return objects; // caller must free this
  }

//----------------------------------------------------------------------

FXTableItem* FXRbCallTableItemMethod(FXTable* recv,ID func,const FXString& text,FXIcon* icon,void* ptr){
  VALUE itemData=(ptr==0)?Qnil:reinterpret_cast<VALUE>(ptr);
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,3,to_ruby(text),to_ruby(icon),itemData);
  return NIL_P(result)?0:reinterpret_cast<FXTableItem*>(DATA_PTR(result));
  }

FXTableItem* FXRbCallTableItemMethod(FXTable* recv,ID func,FXint row,FXint col,FXbool notify){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,3,to_ruby(row),to_ruby(col),to_ruby(notify));
  return NIL_P(result)?0:reinterpret_cast<FXTableItem*>(DATA_PTR(result));
  }

//----------------------------------------------------------------------

FXTreeItem* FXRbCallTreeItemMethod(const FXTreeList* recv,ID func,FXint x,FXint y){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,2,INT2NUM(x),INT2NUM(y));
  return NIL_P(result) ? 0 : reinterpret_cast<FXTreeItem*>(DATA_PTR(result));
  }

//----------------------------------------------------------------------

FXFoldingItem* FXRbCallFoldingItemMethod(const FXFoldingList* recv,ID func,FXint x,FXint y){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,2,INT2NUM(x),INT2NUM(y));
  return NIL_P(result) ? 0 : reinterpret_cast<FXFoldingItem*>(DATA_PTR(result));
  }

//----------------------------------------------------------------------

FXFileAssoc* FXRbCallFileAssocMethod(const FXFileDict* recv,ID func,const char* pathname){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,1,rb_str_new2(pathname));
  return NIL_P(result) ? 0 : reinterpret_cast<FXFileAssoc*>(DATA_PTR(result));
  }

//----------------------------------------------------------------------

FXIcon* FXRbCallIconMethod(const FXTableItem* recv,ID func){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
	if(!NIL_P(obj)){
	  VALUE result=rb_funcall(obj,func,0,NULL);
	  return NIL_P(result) ? 0 : reinterpret_cast<FXIcon*>(DATA_PTR(result));
		}
	else{
		return 0;
		}
  }

//----------------------------------------------------------------------

FXWindow* FXRbCallWindowMethod(const FXTableItem* recv,ID func,FXTable* table){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,1,to_ruby(table));
  return NIL_P(result) ? 0 : reinterpret_cast<FXWindow*>(DATA_PTR(result));
  }

//----------------------------------------------------------------------

// Call function with "FXRange" return value
FXRangef FXRbCallRangeMethod(FXObject* recv,ID func){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,0,NULL);
  return *reinterpret_cast<FXRangef*>(DATA_PTR(result));
  }

//----------------------------------------------------------------------

// Call functions with FXString return value
FXString FXRbCallStringMethod(const FXObject* recv, ID func){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,0,NULL);
  return FXString(StringValuePtr(result));
  }

//----------------------------------------------------------------------

// Call functions with const FXchar* return value
const FXchar* FXRbCallCStringMethod(const FXObject* recv, ID func, const FXchar* message, const FXchar* hint){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,2,to_ruby(message),to_ruby(hint));
  return NIL_P(result) ? 0 : StringValuePtr(result);
  }

// Call functions with const FXchar* return value
const FXchar* FXRbCallCStringMethod(const FXObject* recv, ID func, const FXchar* context, const FXchar* message, const FXchar* hint){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,3,to_ruby(context),to_ruby(message),to_ruby(hint));
  return NIL_P(result) ? 0 : StringValuePtr(result);
  }
//----------------------------------------------------------------------

// Call functions with FXwchar return value
FXwchar FXRbCallWCharMethod(const FXObject* recv, ID func){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,func,0,NULL);
  return static_cast<FXwchar>(NUM2ULONG(result));
  }

//----------------------------------------------------------------------

// Special destructors to handle order dependencies
FXRbMenuCommand::~FXRbMenuCommand(){
  FXAccelTable *table;
  FXWindow *owner;
  if(acckey){
    owner=getShell()->getOwner();
    if(owner){
      table=owner->getAccelTable();
      if(table && table!=reinterpret_cast<FXAccelTable*>(-1)){
        table->removeAccel(acckey);
        }
      }
    }
  acckey=(FXHotKey)NULL;
  FXRbUnregisterRubyObj(this);
  }

FXRbMenuCheck::~FXRbMenuCheck(){
  FXAccelTable *table;
  FXWindow *owner;
  if(acckey){
    owner=getShell()->getOwner();
    if(owner){
      table=owner->getAccelTable();
      if(table && table!=reinterpret_cast<FXAccelTable*>(-1)){
        table->removeAccel(acckey);
        }
      }
    }
  acckey=(FXHotKey)NULL;
  FXRbUnregisterRubyObj(this);
  }

FXRbMenuRadio::~FXRbMenuRadio(){
  FXAccelTable *table;
  FXWindow *owner;
  if(acckey){
    owner=getShell()->getOwner();
    if(owner){
      table=owner->getAccelTable();
      if(table && table!=reinterpret_cast<FXAccelTable*>(-1)){
        table->removeAccel(acckey);
        }
      }
    }
  acckey=(FXHotKey)NULL;
  FXRbUnregisterRubyObj(this);
  }

//----------------------------------------------------------------------

// Visit all of the items between fm and to (inclusive), plus their
// child items, and add to the items list
void FXRbTreeList::enumerateItem(FXTreeItem* item,FXObjectListOf<FXTreeItem>& items){
  // Add this item to the list
  items.append(item);
  
  // Add this item's children
  FXRbTreeList::enumerateItems(item->getFirst(),item->getLast(),items);
  }


// Visit all of the items between fm and to (inclusive), plus their
// child items, and add to the items list
void FXRbTreeList::enumerateItems(FXTreeItem* fm,FXTreeItem* to,FXObjectListOf<FXTreeItem>& items){
  register FXTreeItem *item;
  if(fm && to){
    do{
      item=fm;
      fm=fm->getNext();
      FXRbTreeList::enumerateItem(item,items);
      }
    while(item!=to);
    }
  }

//----------------------------------------------------------------------

/**
 * Visit all of the items between fm and to (inclusive), plus their
 * child items, and add to the items list.
 */
void FXRbFoldingList::enumerateItem(FXFoldingItem* item,FXObjectListOf<FXFoldingItem>& items){
  // Add this item to the list
  items.append(item);
  
  // Add this item's children
  FXRbFoldingList::enumerateItems(item->getFirst(),item->getLast(),items);
  }


/**
 * Visit all of the items between fm and to (inclusive), plus their
 * child items, and add to the items list.
 */
void FXRbFoldingList::enumerateItems(FXFoldingItem* fm,FXFoldingItem* to,FXObjectListOf<FXFoldingItem>& items){
  register FXFoldingItem *item;
  if(fm && to){
    do{
      item=fm;
      fm=fm->getNext();
      FXRbFoldingList::enumerateItem(item,items);
      }
    while(item!=to);
    }
  }


//----------------------------------------------------------------------

static ID id_cmp;

// Sort function stand-in for FXComboBox
FXint FXRbComboBox::sortFunc(const FXListItem* a,const FXListItem* b){
  VALUE itemA = FXRbGetRubyObj(const_cast<FXListItem*>(a), "FXListItem *");
  VALUE itemB = FXRbGetRubyObj(const_cast<FXListItem*>(b), "FXListItem *");
  VALUE result=rb_funcall(itemA,id_cmp,1,itemB);
  return static_cast<FXint>(NUM2INT(result));
  }

  
// Sort function stand-in for FXFoldingList
FXint FXRbFoldingList::sortFunc(const FXFoldingItem* a,const FXFoldingItem* b){
  VALUE itemA = FXRbGetRubyObj(const_cast<FXFoldingItem*>(a), "FXFoldingItem *");
  VALUE itemB = FXRbGetRubyObj(const_cast<FXFoldingItem*>(b), "FXFoldingItem *");
  VALUE result=rb_funcall(itemA,id_cmp,1,itemB);
  return static_cast<FXint>(NUM2INT(result));
  }


// Sort function stand-in for FXIconList
FXint FXRbIconList::sortFunc(const FXIconItem* a,const FXIconItem* b){
  VALUE itemA = FXRbGetRubyObj(const_cast<FXIconItem*>(a), "FXIconItem *");
  VALUE itemB = FXRbGetRubyObj(const_cast<FXIconItem*>(b), "FXIconItem *");
  VALUE result = rb_funcall(itemA,id_cmp,1,itemB);
  return static_cast<FXint>(NUM2INT(result));
  }


// Sort function stand-in for FXList
FXint FXRbList::sortFunc(const FXListItem* a,const FXListItem* b){
  VALUE itemA = FXRbGetRubyObj(const_cast<FXListItem*>(a), "FXListItem *");
  VALUE itemB = FXRbGetRubyObj(const_cast<FXListItem*>(b), "FXListItem *");
  VALUE result=rb_funcall(itemA,id_cmp,1,itemB);
  return static_cast<FXint>(NUM2INT(result));
  }


// Sort function stand-in for FXListBox
FXint FXRbListBox::sortFunc(const FXListItem* a,const FXListItem* b){
  VALUE itemA = FXRbGetRubyObj(const_cast<FXListItem*>(a), "FXListItem *");
  VALUE itemB = FXRbGetRubyObj(const_cast<FXListItem*>(b), "FXListItem *");
  VALUE result=rb_funcall(itemA,id_cmp,1,itemB);
  return static_cast<FXint>(NUM2INT(result));
  }

  
// Sort function stand-in for FXTreeList
FXint FXRbTreeList::sortFunc(const FXTreeItem* a,const FXTreeItem* b){
  VALUE itemA = FXRbGetRubyObj(const_cast<FXTreeItem*>(a), "FXTreeItem *");
  VALUE itemB = FXRbGetRubyObj(const_cast<FXTreeItem*>(b), "FXTreeItem *");
  VALUE result=rb_funcall(itemA,id_cmp,1,itemB);
  return static_cast<FXint>(NUM2INT(result));
  }


// Feedback buffer sort routine stand-in for FXGLViewer
FXbool FXRbGLViewer::sortProc(FXfloat*& buffer,FXint& used,FXint& size){
  return TRUE;
  }

//----------------------------------------------------------------------

// Copied from the Ruby 1.8.6 sources (signal.c)
static struct signals {
    const char *signm;
    int  signo;
} siglist [] = {
    {"EXIT", 0},
#ifdef SIGHUP
    {"HUP", SIGHUP},
#endif
    {"INT", SIGINT},
#ifdef SIGQUIT
    {"QUIT", SIGQUIT},
#endif
#ifdef SIGILL
    {"ILL", SIGILL},
#endif
#ifdef SIGTRAP
    {"TRAP", SIGTRAP},
#endif
#ifdef SIGIOT
    {"IOT", SIGIOT},
#endif
#ifdef SIGABRT
    {"ABRT", SIGABRT},
#endif
#ifdef SIGEMT
    {"EMT", SIGEMT},
#endif
#ifdef SIGFPE
    {"FPE", SIGFPE},
#endif
#ifdef SIGKILL
    {"KILL", SIGKILL},
#endif
#ifdef SIGBUS
    {"BUS", SIGBUS},
#endif
#ifdef SIGSEGV
    {"SEGV", SIGSEGV},
#endif
#ifdef SIGSYS
    {"SYS", SIGSYS},
#endif
#ifdef SIGPIPE
    {"PIPE", SIGPIPE},
#endif
#ifdef SIGALRM
    {"ALRM", SIGALRM},
#endif
#ifdef SIGTERM
    {"TERM", SIGTERM},
#endif
#ifdef SIGURG
    {"URG", SIGURG},
#endif
#ifdef SIGSTOP
    {"STOP", SIGSTOP},
#endif
#ifdef SIGTSTP
    {"TSTP", SIGTSTP},
#endif
#ifdef SIGCONT
    {"CONT", SIGCONT},
#endif
#ifdef SIGCHLD
    {"CHLD", SIGCHLD},
#endif
#ifdef SIGCLD
    {"CLD", SIGCLD},
#else
# ifdef SIGCHLD
    {"CLD", SIGCHLD},
# endif
#endif
#ifdef SIGTTIN
    {"TTIN", SIGTTIN},
#endif
#ifdef SIGTTOU
    {"TTOU", SIGTTOU},
#endif
#ifdef SIGIO
    {"IO", SIGIO},
#endif
#ifdef SIGXCPU
    {"XCPU", SIGXCPU},
#endif
#ifdef SIGXFSZ
    {"XFSZ", SIGXFSZ},
#endif
#ifdef SIGVTALRM
    {"VTALRM", SIGVTALRM},
#endif
#ifdef SIGPROF
    {"PROF", SIGPROF},
#endif
#ifdef SIGWINCH
    {"WINCH", SIGWINCH},
#endif
#ifdef SIGUSR1
    {"USR1", SIGUSR1},
#endif
#ifdef SIGUSR2
    {"USR2", SIGUSR2},
#endif
#ifdef SIGLOST
    {"LOST", SIGLOST},
#endif
#ifdef SIGMSG
    {"MSG", SIGMSG},
#endif
#ifdef SIGPWR
    {"PWR", SIGPWR},
#endif
#ifdef SIGPOLL
    {"POLL", SIGPOLL},
#endif
#ifdef SIGDANGER
    {"DANGER", SIGDANGER},
#endif
#ifdef SIGMIGRATE
    {"MIGRATE", SIGMIGRATE},
#endif
#ifdef SIGPRE
    {"PRE", SIGPRE},
#endif
#ifdef SIGGRANT
    {"GRANT", SIGGRANT},
#endif
#ifdef SIGRETRACT
    {"RETRACT", SIGRETRACT},
#endif
#ifdef SIGSOUND
    {"SOUND", SIGSOUND},
#endif
#ifdef SIGINFO
    {"INFO", SIGINFO},
#endif
    {NULL, 0}
};

FXint FXRbSignalNameToNumber(const char* s){
#ifdef HAVE_SIGNAL_H
  const char *nm=s;
  if(strncmp("SIG",nm,3)==0){
    nm+=3;
    }
  for(signals* sigs=siglist;sigs->signm;sigs++){
    if(strcmp(sigs->signm,nm)==0)
      return sigs->signo;
    }
#endif /* HAVE_SIGNAL_H */
  return 0;
  }

//----------------------------------------------------------------------

/*
 * The Ruby header files define a TYPE(x) macro that conflicts with the
 * TYPE template parameter used in FXArray.h and FXElement.h.
 */
#ifdef TYPE
#undef TYPE
#endif

#include <new>

#include "FXArray.h"
#include "FXElement.h"

static st_table * appSensitiveObjs;
static st_table * appSensitiveDCs;

void FXRbRegisterAppSensitiveObject(FXObject* obj){
  FXASSERT(obj!=0);
  FXTRACE((100,"%s:%d: FXRbRegisterAppSensitiveObject(obj=%p(%s))\n",__FILE__,__LINE__,obj,obj->getClassName()));
  st_insert(appSensitiveObjs,reinterpret_cast<st_data_t>(obj),(st_data_t)0);
  FXASSERT(st_lookup(appSensitiveObjs,reinterpret_cast<st_data_t>(obj),reinterpret_cast<st_data_t *>(0))!=0);
  }

void FXRbRegisterAppSensitiveObject(FXDC* dc){
  FXASSERT(dc!=0);
  FXTRACE((100,"%s:%d: FXRbRegisterAppSensitiveObject(dc=%p)\n",__FILE__,__LINE__,dc));
  st_insert(appSensitiveDCs,reinterpret_cast<st_data_t>(dc),(st_data_t)0);
  FXASSERT(st_lookup(appSensitiveDCs,reinterpret_cast<st_data_t>(dc),reinterpret_cast<st_data_t *>(0))!=0);
  }

void FXRbUnregisterAppSensitiveObject(FXObject* obj){
  FXASSERT(obj!=0);
  FXTRACE((100,"%s:%d: FXRbUnregisterAppSensitiveObject(obj=%p(%s))\n",__FILE__,__LINE__,obj,obj->getClassName()));
  st_delete(appSensitiveObjs,reinterpret_cast<st_data_t *>(&obj),reinterpret_cast<st_data_t *>(0));
  FXASSERT(st_lookup(appSensitiveObjs,reinterpret_cast<st_data_t>(obj),reinterpret_cast<st_data_t *>(0))==0);
  }

void FXRbUnregisterAppSensitiveObject(FXDC* dc){
  FXASSERT(dc!=0);
  FXTRACE((100,"%s:%d: FXRbUnregisterAppSensitiveObject(dc=%p)\n",__FILE__,__LINE__,dc));
  st_delete(appSensitiveDCs,reinterpret_cast<st_data_t *>(&dc),reinterpret_cast<st_data_t *>(0));
  FXASSERT(st_lookup(appSensitiveDCs,reinterpret_cast<st_data_t>(dc),reinterpret_cast<st_data_t *>(0))==0);
  }

#ifdef ST_BROKEN_PROTOTYPES
static int st_cbfunc_obj(st_data_t key,st_data_t,st_data_t arg){
#else
static int st_cbfunc_obj(st_data_t key,st_data_t,st_data_t arg,int){
#endif
  FXASSERT(key!=0);
  FXASSERT(arg!=0);
  FXObjectListOf<FXObject> *pObjectList=reinterpret_cast<FXObjectListOf<FXObject>*>(arg);
  FXObject *pObject=reinterpret_cast<FXObject*>(key);
  pObjectList->append(pObject);
  return 0;
  }

#ifdef ST_BROKEN_PROTOTYPES
static int st_cbfunc_dc(st_data_t key,st_data_t,st_data_t arg){
#else
static int st_cbfunc_dc(st_data_t key,st_data_t,st_data_t arg,int){
#endif
  FXASSERT(key!=0);
  FXASSERT(arg!=0);
  FXArray<FXDC*> *pDCArray=reinterpret_cast<FXArray<FXDC*>*>(arg);
  FXDC *pDC=reinterpret_cast<FXDC*>(key);
  pDCArray->append(pDC);
  return 0;
  }

void FXRbDestroyAppSensitiveObjects(){
  FXTRACE((100,"%s:%d: Begin destroying objects that hold references to the FXApp...\n",__FILE__,__LINE__));

  FXObjectListOf<FXObject> objs;
#ifdef ST_BROKEN_PROTOTYPES
  st_foreach(appSensitiveObjs,st_cbfunc_obj,reinterpret_cast<st_data_t>(&objs));
#else
  st_foreach(appSensitiveObjs,reinterpret_cast<int (*)(ANYARGS)>(st_cbfunc_obj),reinterpret_cast<st_data_t>(&objs));
#endif
  for(FXint i=0;i<objs.no();i++){
    if(objs[i]->isMemberOf(FXMETACLASS(FXRbCursor))){
      if(dynamic_cast<FXRbCursor*>(objs[i])->ownedByApp)
	continue;
      }
    else if(objs[i]->isMemberOf(FXMETACLASS(FXRbCURCursor))){
      if(dynamic_cast<FXRbCURCursor*>(objs[i])->ownedByApp)
	continue;
      }
    else if(objs[i]->isMemberOf(FXMETACLASS(FXRbGIFCursor))){
      if(dynamic_cast<FXRbGIFCursor*>(objs[i])->ownedByApp)
	continue;
      }
    else if(objs[i]->isMemberOf(FXMETACLASS(FXRbFont))){
      if(dynamic_cast<FXRbFont*>(objs[i])->ownedByApp)
	continue;
      }
    else if(objs[i]->isMemberOf(FXMETACLASS(FXRbGLVisual))){
      if(dynamic_cast<FXRbGLVisual*>(objs[i])->ownedByApp)
	continue;
      }
    else if(objs[i]->isMemberOf(FXMETACLASS(FXRbVisual))){
      if(dynamic_cast<FXRbVisual*>(objs[i])->ownedByApp)
	continue;
      }
    delete objs[i];
    }

  FXArray<FXDC*> dcs;
#ifdef ST_BROKEN_PROTOTYPES
  st_foreach(appSensitiveDCs,st_cbfunc_dc,reinterpret_cast<st_data_t>(&dcs));
#else
  st_foreach(appSensitiveDCs,reinterpret_cast<int (*)(ANYARGS)>(st_cbfunc_dc),reinterpret_cast<st_data_t>(&dcs));
#endif
  for(FXint j=0;j<dcs.no();j++){
    delete dcs[j];
    }

  FXTRACE((100,"%s:%d: Finished destroying objects that hold references to the FXApp.\n",__FILE__,__LINE__));
  }

//----------------------------------------------------------------------

extern "C" void Init_core(void);
extern "C" void Init_dc(void);
extern "C" void Init_dialogs(void);
extern "C" void Init_frames(void);
extern "C" void Init_fx3d(void);
extern "C" void Init_image(void);
extern "C" void Init_iconlist(void);
extern "C" void Init_icons(void);
extern "C" void Init_label(void);
extern "C" void Init_layout(void);
extern "C" void Init_list(void);
extern "C" void Init_mdi(void);
extern "C" void Init_menu(void);
#ifdef WITH_FXSCINTILLA
extern "C" void Init_scintilla(void);
#endif
extern "C" void Init_table(void);
extern "C" void Init_text(void);
extern "C" void Init_treelist(void);
extern "C" void Init_ui(void);

#ifdef USE_RB_REQUIRE
#define REQUIRE(fname) rb_require((fname))
#else
#define REQUIRE(fname) rb_funcall(rb_mKernel,rb_intern("require"),1,rb_str_new2((fname))) 
#endif

extern "C" void
#if defined _WIN32
__declspec(dllexport)
#endif
Init_fox16(void) {
  Init_core();
  Init_dc();
  Init_frames();
  Init_layout();
  Init_label();
  Init_ui();
  Init_iconlist();
  Init_list();
  Init_dialogs();
  Init_image();
  Init_icons();
  Init_menu();
  Init_mdi();
  Init_fx3d();
#ifdef WITH_FXSCINTILLA
  Init_scintilla();
#endif
  Init_table();
  Init_text();
  Init_treelist();
  REQUIRE("fox16/core");
  REQUIRE("fox16/dict");
  REQUIRE("fox16/settings");
  REQUIRE("fox16/iterators");
  REQUIRE("fox16/keys");
  REQUIRE("fox16/aliases");
  REQUIRE("fox16/responder2");
  REQUIRE("fox16/glgroup");
  REQUIRE("fox16/execute_nonmodal");
  REQUIRE("fox16/version");
  REQUIRE("fox16/kwargs");
  REQUIRE("fox16/exceptions_for_fxerror");
  
  id_assocs=rb_intern("@assocs");
  id_backtrace=rb_intern("backtrace");
  id_cmp=rb_intern("<=>");
  id_begin=rb_intern("begin");
  id_end=rb_intern("end");
  id_exclude_endp=rb_intern("exclude_end?");
  
  FXRuby_Objects=st_init_numtable();
  appSensitiveObjs=st_init_numtable();
  appSensitiveDCs=st_init_numtable();
  }
