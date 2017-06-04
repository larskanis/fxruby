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
 * $Id: FXRuby.h 2463 2006-07-11 14:02:35Z lyle $
 ***********************************************************************/

#ifndef FXRUBY_H
#define FXRUBY_H

#ifndef NUM2SIZET
#define NUM2SIZET(s) NUM2ULONG(s)
#endif
#ifndef SIZET2NUM
#define SIZET2NUM(s) ULONG2NUM(s)
#endif

// Opaque type declaration for SWIG runtime support
struct swig_type_info;

// SWIG runtime functions we need
extern "C" {
static const char * SWIG_TypeName(const swig_type_info *ty);
static VALUE SWIG_Ruby_NewPointerObj(void *ptr, swig_type_info *type, int own);
static int FXSWIG_ConvertPtr(VALUE obj, void **ptr, swig_type_info *ty, int flags);
}

// Helper for overloaded show() functions
template <class TYPE>
VALUE showHelper(VALUE self, int argc, VALUE *argv, TYPE *p, swig_type_info *typeinfo) {
  TYPE *win;
  FXSWIG_ConvertPtr(self,(void**)&win,typeinfo,1);
  if (argc == 0) {
    win->_show();
    }
  else if (argc == 1) {
    FXuint placement = NUM2UINT(argv[0]);
    win->FXTopWindow::show(placement);
    }
  else {
    rb_raise(rb_eArgError, "wrong # of arguments");
    }
  return Qnil;
  }

// Wrapper around SWIG_Ruby_NewPointerObj()
VALUE FXRbNewPointerObj(void *ptr, swig_type_info *typeinfo);
VALUE FXRbNewPointerObjCb(void *ptr, swig_type_info *typeinfo);
bool FXRbIsBorrowed(void* ptr);
bool FXRbSetInGC(const void* ptr, bool enabled);
bool FXRbIsInGC(const void* ptr);

// Wrapper around SWIG_TypeQuery()
swig_type_info *FXRbTypeQuery(const char *name);

// Wrapper around SWIG_ConvertPtr()
void* FXRbConvertPtr(VALUE obj,swig_type_info* typeinfo);

// Returns an FXInputHandle for this Ruby file object
FXInputHandle FXRbGetReadFileHandle(VALUE obj,FXuint mode);
FXInputHandle FXRbGetWriteFileHandle(VALUE obj,FXuint mode);
void FXRbRemoveReadFileHandle(VALUE obj,FXuint mode);
void FXRbRemoveWriteFileHandle(VALUE obj,FXuint mode);

// Register mapping from Ruby objects to FOX objects
void FXRbRegisterRubyObj(VALUE rubyObj, const void* foxObj);

// Remove mapping for this FOX object and zero out any pointers
// to this (now dead) C++ object held by any Ruby object
void FXRbUnregisterRubyObj(const void* foxObj);

// Register an object that must be destroyed before FXApp is destroyed
void FXRbRegisterAppSensitiveObject(FXObject* obj);
void FXRbRegisterAppSensitiveObject(FXDC* dc);

// Unregister an object that must be destroyed before FXApp is destroyed
void FXRbUnregisterAppSensitiveObject(FXObject* obj);
void FXRbUnregisterAppSensitiveObject(FXDC* dc);

// Destroy all app-sensitive objects
void FXRbDestroyAppSensitiveObjects();

/**
 * Return the registered Ruby class instance associated with this
 * FOX object (if any). If searchBoth is false, only considers the
 * Ruby-owned objects; otherwise considers all outstanding references.
 */
VALUE FXRbGetRubyObj(const void *foxObj, bool searchBoth, bool in_gc_mark=false);

/**
 * Return the registered Ruby class instance associated with this
 * FOX object, or a new unregistered instance if not found.
 */
VALUE FXRbGetRubyObj(const void *foxObj, const char *type);
VALUE FXRbGetRubyObj(const void *foxObj, swig_type_info *type);
VALUE FXRbGetRubyObjCb(const void *foxObj, swig_type_info *type);


// Mark this object as used for the garbage collector
void FXRbGcMark(void *obj);

// Returns a Ruby array of floats
extern VALUE FXRbMakeArray(const FXfloat* values,FXint size);

// Returns a Ruby array of floats
extern VALUE FXRbMakeArray(const FXdouble* values,FXint size);

// Returns a Ruby array of integers
extern VALUE FXRbMakeArray(const FXint* values,FXint size);

// Returns a Ruby array of integers
extern VALUE FXRbMakeArray(const FXuint* values,FXint size);

// Returns a Ruby array of integers
extern VALUE FXRbMakeArray(const FXchar* dashpattern,FXuint dashlength);

// Returns a Ruby array of FXArcs
extern VALUE FXRbMakeArray(const FXArc* arcs,FXuint narcs);

// Returns a Ruby array of FXPoints
extern VALUE FXRbMakeArray(const FXPoint* points,FXuint npoints);

// Returns a Ruby array of FXRectangles
extern VALUE FXRbMakeArray(const FXRectangle* rectangles,FXuint nrectangles);

// Returns a Ruby array of FXSegments
extern VALUE FXRbMakeArray(const FXSegment* segments,FXuint nsegments);

// Returns a Ruby array of FXColor values
extern VALUE FXRbMakeColorArray(const FXColor* colors,FXint w,FXint h);

// Returns a number of FXColor elements in the argument
extern FXuint FXRbNumberOfFXColors(VALUE string_or_ary);

// Allocate a FXColor buffer and populate with data
extern FXColor *FXRbConvertToFXColors(VALUE string_or_ary, FXuint *opts);

extern void* FXRbGetExpectedData(VALUE recv,FXSelector key,VALUE data);

// Returns the name of the message handler function (or NULL)
ID FXRbLookupHandler_gvlcb(FXObject* recv,FXSelector key);

// Handle this message
long FXRbHandleMessage_gvlcb(FXObject* recv,ID func,FXObject* sender,FXSelector key,void* data);

// Convert a signal name string to its corresponding signal number
FXint FXRbSignalNameToNumber(const char* name);

// Fox module instance
extern VALUE mFox;

#ifdef HAVE_RUBY_ENCODING_H
// UTF-8 encoding index
extern int utf8_enc_idx;
#endif

// Convert from FOX datatypes to Ruby objects
inline VALUE to_ruby(const void* ptr){
  return Qnil; // FIXME: Used for some FXIconSource methods
  }

inline VALUE to_ruby(FXchar c){
  return INT2NUM(c);
  }

inline VALUE to_ruby(FXbool b){ // same as FXuchar
  return b ? Qtrue : Qfalse;
  }

inline VALUE to_ruby(FXshort s){
  return INT2NUM(s);
  }

inline VALUE to_ruby(FXushort u){
  return UINT2NUM(u);
  }

inline VALUE to_ruby(FXint i){
  return INT2NUM(i);
  }

inline VALUE to_ruby(FXuint u){
  return UINT2NUM(u);
  }

inline VALUE to_ruby(FXfloat f){
  return rb_float_new(f);
  }

inline VALUE to_ruby(FXdouble d){
  return rb_float_new(d);
  }

inline VALUE to_ruby(FXlong x){
  return LONG2NUM(x);
  }

inline VALUE to_ruby(FXulong x){
  return ULONG2NUM(x);
  }

#if !defined(__LP64__) && !defined(_LP64) && (_MIPS_SZLONG != 64) && (__WORDSIZE != 64)
inline VALUE to_ruby(unsigned long l){
  return ULONG2NUM(l);
  }
#endif

inline VALUE to_ruby(const FXString& s){
  VALUE str = rb_str_new(s.text(), s.length());
#ifdef HAVE_RUBY_ENCODING_H
  rb_enc_associate_index(str, utf8_enc_idx);
#endif
  return str;
  }

inline VALUE to_ruby(const FXchar* s){
  if(!s) return Qnil;
  VALUE str = rb_str_new2(s);
#ifdef HAVE_RUBY_ENCODING_H
  rb_enc_associate_index(str, utf8_enc_idx);
#endif
  return str;
  }

inline VALUE to_ruby(const FXchar* s, int length){
  VALUE str = rb_str_new(s, length);
#ifdef HAVE_RUBY_ENCODING_H
  rb_enc_associate_index(str, utf8_enc_idx);
#endif
  return str;
  }

extern VALUE to_ruby(const FXObject* obj);

inline VALUE to_ruby(const FXRangef& range){
  return FXRbNewPointerObj(static_cast<void*>(const_cast<FXRangef*>(&range)),FXRbTypeQuery("FXRangef *"));
  }

inline VALUE to_ruby(FXStream& store){
  return (VALUE) 0; // FIXME
  }

inline VALUE to_ruby(const FXPoint* point){
  return FXRbNewPointerObj(static_cast<void*>(const_cast<FXPoint*>(point)),FXRbTypeQuery("FXPoint *"));
  }

inline VALUE to_ruby(const FXSegment* segment){
  return FXRbNewPointerObj(static_cast<void*>(const_cast<FXSegment*>(segment)),FXRbTypeQuery("FXSegment *"));
  }

inline VALUE to_ruby(const FXRectangle* rect){
  return FXRbNewPointerObj(static_cast<void*>(const_cast<FXRectangle*>(rect)),FXRbTypeQuery("FXRectangle *"));
  }

inline VALUE to_ruby(const FXRectangle& rect){
  return FXRbNewPointerObj(static_cast<void*>(const_cast<FXRectangle*>(&rect)),FXRbTypeQuery("FXRectangle *"));
  }

inline VALUE to_ruby(const FXArc* arc){
  return FXRbNewPointerObj(static_cast<void*>(const_cast<FXArc*>(arc)),FXRbTypeQuery("FXArc *"));
  }

inline VALUE to_ruby(const FXRegion& region){
  return (VALUE) 0; // FIXME
  }

inline VALUE to_ruby(FXEvent* event){
  return FXRbGetRubyObj(reinterpret_cast<void*>(event),FXRbTypeQuery("FXEvent *"));
  }

inline VALUE to_ruby(FXTablePos* p){
  return SWIG_Ruby_NewPointerObj(reinterpret_cast<void*>(p),FXRbTypeQuery("FXTablePos *"),0);
  }

inline VALUE to_ruby(FXTextChange* p){
  return SWIG_Ruby_NewPointerObj(reinterpret_cast<void*>(p),FXRbTypeQuery("FXTextChange *"),0);
  }

inline VALUE to_ruby(FXTableRange* r){
  return SWIG_Ruby_NewPointerObj(reinterpret_cast<void*>(r),FXRbTypeQuery("FXTableRange *"),0);
  }

inline VALUE to_ruby(FXFontDesc* fontdesc){
  return FXRbNewPointerObj(reinterpret_cast<void*>(fontdesc),FXRbTypeQuery("FXFontDesc *"));
  }

inline VALUE to_ruby(const FXFontDesc& fontdesc){
  return FXRbNewPointerObj(reinterpret_cast<void*>(const_cast<FXFontDesc*>(&fontdesc)),FXRbTypeQuery("FXFontDesc *"));
  }

inline VALUE to_ruby(FXDC& dc){
  return FXRbGetRubyObj(reinterpret_cast<void*>(&dc),FXRbTypeQuery("FXDC *"));
  }




extern VALUE to_ruby_cb(const FXObject* obj);

inline VALUE to_ruby_cb(const FXRangef& range){
  return FXRbNewPointerObjCb(static_cast<void*>(const_cast<FXRangef*>(&range)), FXRbTypeQuery("FXRangef *"));
}

inline VALUE to_ruby_cb(FXStream& store){
  return (VALUE) 0; // FIXME
}

inline VALUE to_ruby_cb(const FXPoint* point){
  return FXRbNewPointerObjCb(static_cast<void*>(const_cast<FXPoint*>(point)), FXRbTypeQuery("FXPoint *"));
}

inline VALUE to_ruby_cb(const FXSegment* segment){
  return FXRbNewPointerObjCb(static_cast<void*>(const_cast<FXSegment*>(segment)), FXRbTypeQuery("FXSegment *"));
}

inline VALUE to_ruby_cb(const FXRectangle* rect){
  return FXRbNewPointerObjCb(static_cast<void*>(const_cast<FXRectangle*>(rect)), FXRbTypeQuery("FXRectangle *"));
}

inline VALUE to_ruby_cb(const FXRectangle& rect){
  return FXRbNewPointerObjCb(static_cast<void*>(const_cast<FXRectangle*>(&rect)), FXRbTypeQuery("FXRectangle *"));
}

inline VALUE to_ruby_cb(const FXArc* arc){
  return FXRbNewPointerObjCb(static_cast<void*>(const_cast<FXArc*>(arc)), FXRbTypeQuery("FXArc *"));
}

inline VALUE to_ruby_cb(FXEvent* event){
  return FXRbGetRubyObjCb(reinterpret_cast<void*>(event), FXRbTypeQuery("FXEvent *"));
}

inline VALUE to_ruby_cb(FXFontDesc* fontdesc){
  return FXRbNewPointerObjCb(reinterpret_cast<void*>(fontdesc), FXRbTypeQuery("FXFontDesc *"));
}

inline VALUE to_ruby_cb(const FXFontDesc& fontdesc){
  return FXRbNewPointerObjCb(reinterpret_cast<void*>(const_cast<FXFontDesc*>(&fontdesc)), FXRbTypeQuery("FXFontDesc *"));
}

inline VALUE to_ruby_cb(FXDC& dc){
  return FXRbGetRubyObjCb(reinterpret_cast<void*>(&dc), FXRbTypeQuery("FXDC *"));
}

template<class TYPE>
VALUE to_ruby_cb(TYPE obj){
  return to_ruby(obj);
}


/**
 * Remember: FXID is typedef'd as an unsigned int on non-Windows platforms,
 * but as a void * on Win32.
 */
inline VALUE fxid_to_int(FXID id){
#ifndef WIN32
  return UINT2NUM(static_cast<unsigned int>(id));
#else
  return SIZET2NUM(reinterpret_cast<size_t>(id));
#endif
  }

/**
 * Remember: FXID is typedef'd as an unsigned int on non-Windows platforms,
 * but as a void * on Win32.
 */
inline FXID int_to_fxid(VALUE value){
#ifndef WIN32
  return static_cast<FXID>(NUM2UINT(value));
#else
  return reinterpret_cast<FXID>(NUM2SIZET(value));
#endif
  }

// Returns the beginning and ending values (inclusive) for a Range object
void FXRbRange2LoHi(VALUE range,FXint& lo,FXint& hi);
void FXRbRange2LoHi(VALUE range,FXdouble& lo,FXdouble& hi);

// Call function with "void" return value
void FXRbCallVoidMethod_gvlcb(FXObject* recv,const char *func);

void FXRbCallVoidMethod_gvlcb(FXDC* recv,const char *func);

/* One argument */
template<class TYPE>
void FXRbCallVoidMethod_gvlcb(FXObject* recv,const char *func, TYPE& arg){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  FXASSERT(!FXRbIsInGC(recv));
  rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  }

template<class TYPE>
void FXRbCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE arg){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  }

template<class TYPE>
void FXRbCallVoidMethod_gvlcb(const FXObject* recv, const char *func, TYPE& arg){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  FXASSERT(!FXRbIsInGC(recv));
  rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  }

/* Two arguments */
template<class TYPE1, class TYPE2>
void FXRbCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1 arg1,TYPE2 arg2){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  }

template<class TYPE1, class TYPE2>
void FXRbCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE1 arg1,TYPE2 arg2){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  }

template<class TYPE>
void FXRbCallVoidArrayMethod(FXDC* recv,const char *func,TYPE objs,FXuint num){
  VALUE obj=FXRbGetRubyObj(recv,false);
  VALUE array=FXRbMakeArray(objs,num);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),1,array);
}

FXTreeItem* FXRbCallTreeItemMethod_gvlcb(const FXTreeList* recv,const char *func,FXint x,FXint y);
FXFoldingItem* FXRbCallFoldingItemMethod_gvlcb(const FXFoldingList* recv,const char *func,FXint x,FXint y);

/* Three arguments */
template<class TYPE1, class TYPE2, class TYPE3>
void FXRbCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1 arg1,TYPE2 arg2,TYPE3 arg3){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  }

template<class TYPE1, class TYPE2, class TYPE3>
void FXRbCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE1 arg1,TYPE2 arg2,TYPE3 arg3){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  }

/* Four arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
void FXRbCallVoidMethod_gvlcb(FXObject* recv,const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),4,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
void FXRbCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE1 arg1,TYPE2 arg2,TYPE3 arg3,TYPE4 arg4){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),4,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4));
  }

/* Five arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
void FXRbCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,TYPE4 arg4,TYPE5 arg5){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
void FXRbCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  }

/* Six arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6>
void FXRbCallVoidMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2& arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),6,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6>
void FXRbCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),6,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6));
  }

/* Seven arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6, class TYPE7>
void FXRbCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6, TYPE7 arg7){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),7,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6),to_ruby_cb(arg7));
  }

/* Nine arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6, class TYPE7, class TYPE8, class TYPE9>
void FXRbCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6, TYPE7 arg7, TYPE8 arg8, TYPE9 arg9){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),9,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6),to_ruby_cb(arg7), to_ruby_cb(arg8), to_ruby_cb(arg9));
  }

/* Eleven arguments (!) */
template<class TYPE1,class TYPE2,class TYPE3,class TYPE4,class TYPE5,class TYPE6,class TYPE7,class TYPE8,class TYPE9,class TYPE10,class TYPE11>
void FXRbCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,TYPE4 arg4,TYPE5 arg5,TYPE6 arg6,TYPE7 arg7,TYPE8 arg8,TYPE9 arg9,TYPE10 arg10,TYPE11 arg11){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),11,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6),to_ruby_cb(arg7),to_ruby_cb(arg8),to_ruby_cb(arg9),to_ruby_cb(arg10),to_ruby_cb(arg11));
  }

// Call function with "FXbool" return value
inline bool FXRbCallBoolMethod_gvlcb(FXStream* recv,const char *func){
  VALUE v=rb_funcall(FXRbGetRubyObj(recv,false),rb_intern(func),0,NULL);
  return (v==Qtrue);
  }

template<class TYPE1>
bool FXRbCallBoolMethod_gvlcb(FXStream* recv,const char *func,TYPE1 arg){
  VALUE v=rb_funcall(FXRbGetRubyObj(recv,false),rb_intern(func),1,to_ruby_cb(arg));
  return (v==Qtrue);
  }

template<class TYPE1,class TYPE2>
bool FXRbCallBoolMethod_gvlcb(FXStream* recv,const char *func,TYPE1 arg1,TYPE2 arg2){
  VALUE v=rb_funcall(FXRbGetRubyObj(recv,false),rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  return (v==Qtrue);
  }

bool FXRbCallBoolMethod_gvlcb(const FXObject* recv,const char *func);

template<class TYPE>
bool FXRbCallBoolMethod_gvlcb(FXObject* recv, const char *func, TYPE& arg){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return (v==Qtrue);
  }

template<class TYPE>
bool FXRbCallBoolMethod_gvlcb(const FXObject* recv,const char *func,TYPE& arg){
  VALUE v=rb_funcall(FXRbGetRubyObj(recv,false),rb_intern(func),1,to_ruby_cb(arg));
  return (v==Qtrue);
  }

template<class TYPE1, class TYPE2>
bool FXRbCallBoolMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  return (v==Qtrue);
  }

template<class TYPE1, class TYPE2, class TYPE3>
bool FXRbCallBoolMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  return (v==Qtrue);
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
bool FXRbCallBoolMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  return (v==Qtrue);
  }

// Call function with "FXint" return value
FXint FXRbCallIntMethod_gvlcb(const FXObject* recv,const char *func);

template<class TYPE>
FXint FXRbCallIntMethod_gvlcb(FXObject* recv, const char *func, TYPE arg){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return static_cast<FXint>(NUM2INT(v));
  }

template<class TYPE>
FXint FXRbCallIntMethod_gvlcb(const FXObject* recv, const char *func, TYPE arg){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return static_cast<FXint>(NUM2INT(v));
  }

template<class TYPE1, class TYPE2>
FXint FXRbCallIntMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  return static_cast<FXint>(NUM2INT(result));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
FXint FXRbCallIntMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  return static_cast<FXint>(NUM2INT(result));
  }

// Call function with "long" return value
template<class TYPE1, class TYPE2, class TYPE3>
long FXRbCallLongMethod_gvlcb(FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  return static_cast<long>(NUM2LONG(v));
  }

// Call functions with "FXuint" return value
template<class TYPE>
FXuint FXRbCallUIntMethod_gvlcb(FXObject* recv, const char *func, TYPE arg){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return static_cast<FXuint>(NUM2UINT(v));
  }

// Call functions with FXString return value
FXString FXRbCallStringMethod_gvlcb(const FXObject* recv, const char *func);

// Call functions with const FXchar* return value
const FXchar* FXRbCallCStringMethod_gvlcb(const FXObject* recv, const char *func, const FXchar*, const FXchar*);
const FXchar* FXRbCallCStringMethod_gvlcb(const FXObject* recv, const char *func, const FXchar*, const FXchar*, const FXchar*);

// Call functions with "FXGLObject*" return value
FXGLObject* FXRbCallGLObjectMethod_gvlcb(FXGLObject* recv,const char *func);
FXGLObject* FXRbCallGLObjectMethod_gvlcb(FXGLObject* recv,const char *func,FXuint* path,FXint n);
FXGLObject* FXRbCallGLObjectMethod_gvlcb(FXGLViewer* recv,const char *func,FXint x,FXint y);

// Call functions with "FXGLObject**" return value
FXGLObject** FXRbCallGLObjectArrayMethod_gvlcb(FXGLViewer* recv,const char *func,FXint x,FXint y,FXint w,FXint h);

// Call functions with "FXTreeItem*" return value
FXTableItem* FXRbCallTableItemMethod_gvlcb(FXTable* recv,const char *func,const FXString& text,FXIcon* icon,void* ptr);

// Call functions with "FXTreeItem*" return value
FXTableItem* FXRbCallTableItemMethod_gvlcb(FXTable* recv,const char *func,FXint,FXint,FXbool);

// Call functions with "FXFileAssoc*" return value
FXFileAssoc* FXRbCallFileAssocMethod_gvlcb(const FXFileDict* recv,const char *func,const FXchar* pathname);

// Call functions with "FXIcon*" return value
FXIcon* FXRbCallIconMethod_gvlcb(const FXTableItem* recv,const char *func);

template<class TYPE1, class TYPE2>
FXIcon* FXRbCallIconMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,const TYPE2& arg2){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),2,to_ruby(arg1),to_ruby(arg2));
  return NIL_P(result) ? 0 : reinterpret_cast<FXIcon*>(DATA_PTR(result));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
FXIcon* FXRbCallIconMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,const TYPE4& arg4){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),4,to_ruby(arg1),to_ruby(arg2),to_ruby(arg3),to_ruby(arg4));
  return NIL_P(result) ? 0 : reinterpret_cast<FXIcon*>(DATA_PTR(result));
  }

// Call functions with FXImage* return value
template<class TYPE1, class TYPE2>
FXImage* FXRbCallImageMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,const TYPE2& arg2){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),2,to_ruby(arg1),to_ruby(arg2));
  return NIL_P(result) ? 0 : reinterpret_cast<FXImage*>(DATA_PTR(result));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
FXImage* FXRbCallImageMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,const TYPE4& arg4){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),4,to_ruby(arg1),to_ruby(arg2),to_ruby(arg3),to_ruby(arg4));
  return NIL_P(result) ? 0 : reinterpret_cast<FXImage*>(DATA_PTR(result));
  }

// Call functions with "FXWindow*" return value
FXWindow* FXRbCallWindowMethod_gvlcb(const FXTableItem* recv,const char *func,FXTable* table);

// Call functions with "FXColor" return value
template<class TYPE1, class TYPE2>
FXColor FXRbCallColorMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2){
  VALUE obj=FXRbGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),2,to_ruby(arg1),to_ruby(arg2));
  return static_cast<FXColor>(NUM2UINT(v));
  }

// Call functions with "FXRangef" return value
FXRangef FXRbCallRangeMethod_gvlcb(FXObject* recv,const char *func);

// Call functions with FXwchar return value
FXwchar FXRbCallWCharMethod_gvlcb(const FXObject* recv,const char *func);

void FXRbCallSetDashes_gvlcb(FXDC* recv,const char *func,FXuint dashoffset,const FXchar *dashpattern,FXuint dashlength);

void FXRbCallDCDrawMethod_gvlcb(FXDC* recv, const char * func, FXint x,FXint y,const FXString& string);
void FXRbCallDCDrawMethod_gvlcb(FXDC* recv, const char * func, FXint x,FXint y,const FXchar* string,FXuint length);

/**
 * Macro to set up class implementation.
 * This is a modified version of the standard FOX macro FXIMPLEMENT();
 * this version's implementation of the virtual handle() function
 * first checks the Ruby class instance's message map to see if it
 * can handle the incoming message. If not, the regular C++ message
 * mapping takes over as in standard FOX applications.
 */

#define FXRbIMPLEMENT(classname,baseclassname,mapping,nmappings) \
  FXObject* classname::manufacture(){return new classname;} \
  const FX::FXMetaClass classname::metaClass(#classname,classname::manufacture,&baseclassname::metaClass,mapping,nmappings,sizeof(classname::FXMapEntry)); \
  long classname::handle(FXObject* sender,FXSelector key,void* ptr){ \
    ID func=FXRbLookupHandler(this,key); \
    if(func!=0){ \
      return FXRbHandleMessage(this,func,sender,key,ptr); \
      } \
    else{ \
      const FXMapEntry* me=reinterpret_cast<const FXMapEntry*>(metaClass.search(key)); \
      return me ? (this->* me->func)(sender,key,ptr) : baseclassname::handle(sender,key,ptr); \
      } \
    }


#define SORTFUNC(list, item) \
  FXint list##_sortFunc_gvlcb(const item* a,const item* b);

SORTFUNC( FXRbComboBox, FXListItem )
SORTFUNC( FXRbFoldingList, FXFoldingItem )
SORTFUNC( FXRbIconList, FXIconItem )
SORTFUNC( FXRbList, FXListItem )
SORTFUNC( FXRbListBox, FXListItem )
SORTFUNC( FXRbTreeList, FXTreeItem )

#undef SORTFUNC

// FXRuby classes
#include "FXRbStream.h"
#include "FXRbObject.h"
#include "FXRbDelegator.h"
#include "FXRbDict.h"
#include "FXRbStringDict.h"
#include "FXRbAccelTable.h"
#include "FXRbRecentFiles.h"
#include "FXRbApp.h"
#include "FXRbId.h"
#include "FXRbVisual.h"
#include "FXRbFont.h"
#include "FXRbCursor.h"
#include "FXRbCURCursor.h"
#include "FXRbGIFCursor.h"
#include "FXRbDrawable.h"
#include "FXRbBitmap.h"
#include "FXMemoryBuffer.h"
#include "FXRbImage.h"
#include "FXRbBMPImage.h"
#include "FXRbGIFImage.h"
#include "FXRbICOImage.h"
#include "FXRbJPGImage.h"
#include "FXRbPCXImage.h"
#include "FXRbPNGImage.h"
#include "FXRbPPMImage.h"
#include "FXRbRGBImage.h"
#include "FXRbTGAImage.h"
#include "FXRbTIFImage.h"
#include "FXRbXBMImage.h"
#include "FXRbXPMImage.h"
#include "FXRbIcon.h"
#include "FXRbBMPIcon.h"
#include "FXRbGIFIcon.h"
#include "FXRbICOIcon.h"
#include "FXRbJPGIcon.h"
#include "FXRbPCXIcon.h"
#include "FXRbPNGIcon.h"
#include "FXRbPPMIcon.h"
#include "FXRbRGBIcon.h"
#include "FXRbTGAIcon.h"
#include "FXRbTIFIcon.h"
#include "FXRbXBMIcon.h"
#include "FXRbXPMIcon.h"
#include "FXRbDC.h"
#include "FXRbDCWindow.h"
#include "FXRbDCPrint.h"
#include "FXRbFileDict.h"
#include "FXRbWindow.h"
#include "FXRbFrame.h"
#include "FXRbKnob.h"
#include "FXRb7Segment.h"
#include "FXRbDockHandler.h"
#include "FXRbDockTitle.h"
#include "FXRbSeparator.h"
#include "FXRbLabel.h"
#include "FXRbDial.h"
#include "FXRbColorBar.h"
#include "FXRbColorRing.h"
#include "FXRbColorWell.h"
#include "FXRbColorWheel.h"
#include "FXRbTextField.h"
#include "FXRbButton.h"
#include "FXRbPicker.h"
#include "FXRbToggleButton.h"
#include "FXRbTriStateButton.h"
#include "FXRbCheckButton.h"
#include "FXRbRadioButton.h"
#include "FXRbArrowButton.h"
#include "FXRbMenuButton.h"
#include "FXRbComposite.h"
#include "FXRbPacker.h"
#include "FXRbDockBar.h"
#include "FXRbDockSite.h"
#include "FXRbSpring.h"
#include "FXRbHorizontalFrame.h"
#include "FXRbVerticalFrame.h"
#include "FXRbMatrix.h"
#include "FXRbSpinner.h"
#include "FXRbRealSpinner.h"
#include "FXRbRootWindow.h"
#include "FXRbCanvas.h"
#include "FXRbGroupBox.h"
#include "FXRbShell.h"
#include "FXRbToolTip.h"
#include "FXRbPopup.h"
#include "FXRbTopWindow.h"
#include "FXRbSplashWindow.h"
#include "FXRbDialogBox.h"
#include "FXRbMainWindow.h"
#include "FXRbMenuPane.h"
#include "FXRbScrollPane.h"
#include "FXRbMenuCaption.h"
#include "FXRbMenuSeparator.h"
#include "FXRbMenuTitle.h"
#include "FXRbMenuCascade.h"
#include "FXRbMenuCommand.h"
#include "FXRbMenuCheck.h"
#include "FXRbMenuRadio.h"
#include "FXRbToolBar.h"
#include "FXRbMenuBar.h"
#include "FXRbOptionMenu.h"
#include "FXRbSwitcher.h"
#include "FXRbTabBar.h"
#include "FXRbTabBook.h"
#include "FXRbTabItem.h"
#include "FXRbScrollBar.h"
#include "FXRbScrollArea.h"
#include "FXRbScrollWindow.h"
#include "FXRbList.h"
#include "FXRbColorList.h"
#include "FXRbComboBox.h"
#include "FXRbListBox.h"
#include "FXRbFoldingList.h"
#include "FXRbTreeList.h"
#include "FXRbTreeListBox.h"
// #include "FXRbBitmapView.h"
#include "FXRbImageView.h"
#include "FXRbTable.h"
#include "FXRbDragCorner.h"
#include "FXRbStatusBar.h"
#include "FXRbStatusLine.h"
#include "FXRbMessageBox.h"
#include "FXRbDirList.h"
#include "FXRbRealSlider.h"
#include "FXRbSlider.h"
#include "FXRbSplitter.h"
#include "FXRb4Splitter.h"
#include "FXRbHeader.h"
#include "FXRbShutter.h"
#include "FXRbIconList.h"
#include "FXRbIconSource.h"
#include "FXRbFileList.h"
#include "FXRbDirBox.h"
#include "FXRbDriveBox.h"
#include "FXRbDirSelector.h"
#include "FXRbDirDialog.h"
#include "FXRbFileSelector.h"
#include "FXRbFileDialog.h"
#include "FXRbColorSelector.h"
#include "FXRbColorDialog.h"
#include "FXRbFontSelector.h"
#include "FXRbFontDialog.h"
#include "FXRbText.h"
#include "FXRbDataTarget.h"
#include "FXRbProgressBar.h"
#include "FXRbSearchDialog.h"
#include "FXRbReplaceDialog.h"
#include "FXRbInputDialog.h"
#include "FXRbProgressDialog.h"
#include "FXRbChoiceBox.h"
#include "FXRbMDIButton.h"
#include "FXRbMDIClient.h"
#include "FXRbMDIChild.h"
#include "FXRbDocument.h"
#include "FXRbToolBarGrip.h"
#include "FXRbToolBarShell.h"
#include "FXRbToolBarTab.h"
#include "FXRbPrintDialog.h"
#include "FXRbDebugTarget.h"
#include "FXRbGradientBar.h"
#include "FXRbBitmapFrame.h"
#include "FXRbImageFrame.h"
#include "FXRbRuler.h"
#include "FXRbRulerView.h"
#include "FXRbWizard.h"
#ifdef WITH_FXSCINTILLA
#include "FXRbScintilla.h"
#endif
#include "FXRbSettings.h"
#include "FXRbRegistry.h"
#include "FXRbTranslator.h"

// OpenGL support
#include "FXRbGLVisual.h"
#include "FXRbGLContext.h"
#include "FXRbGLCanvas.h"
#include "FXRbGLViewer.h"
#include "FXRbGLObject.h"
#include "FXRbGLShape.h"

// Inlined implementations of stubs
#include "inlinestubs.h"

#endif

