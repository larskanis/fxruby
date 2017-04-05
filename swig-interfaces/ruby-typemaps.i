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

%include constraints.i

%apply Pointer NONNULL {
  FXApp* APP,
  FXApp* a,
  FXApp* app,
  FXApp* application,
  FXComposite* PARENT,
  FXComposite* p,
  FXWindow* OWNER,
  FXWindow* own,
  FXWindow* owner
}

%typemap(in) FXchar "$1 = NUM2INT($input);";
%typemap(in) FXuchar "$1 = NUM2UINT($input);";
%typemap(in) FXshort "$1 = NUM2INT($input);";
%typemap(in) FXushort "$1 = NUM2UINT($input);";
%typemap(in) FXint "$1 = NUM2INT($input);";
%typemap(in) FXuint "$1 = NUM2UINT($input);";
%typemap(in) FXlong "$1 = NUM2LONG($input);";
%typemap(in) FXulong "$1 = NUM2ULONG($input);";

%typecheck(SWIG_TYPECHECK_INTEGER) FXchar, FXuchar, FXshort, FXushort, FXint, FXuint, FXlong, FXulong {
  $1 = (TYPE($input) == T_FIXNUM || TYPE($input) == T_BIGNUM) ? 1 : 0;
}

/* Type-checking rules */
%typecheck(SWIG_TYPECHECK_STRING) const FXString&, FXuchar *data {
  $1 = (NIL_P($input) || TYPE($input) == T_STRING) ? 1 : 0;
}

%typecheck(SWIG_TYPECHECK_POINTER) void *ITEMDATA {
  $1 = 1;
}

%typecheck(SWIG_TYPECHECK_BOOL) FXbool {
  $1 = ($input == Qtrue || $input == Qfalse) ? 1 : 0;
}

/* Convert Ruby object to FXColor */
%{
inline FXColor to_FXColor(VALUE obj){
  if(TYPE(obj)==T_STRING){
    return fxcolorfromname(StringValuePtr(obj));
    }
  else if(TYPE(obj)==T_SYMBOL){
    return fxcolorfromname(rb_id2name(SYM2ID(obj)));
    }
  else{
    return NUM2ULONG(obj);
    }
  }
%}
%typemap(in) FXColor "$1 = to_FXColor($input);";

/* Convert Ruby VALUE to VALUE */
%typemap(out) VALUE "$result = $1;";

/* Convert Ruby String to FXString */
%{
inline FXString to_FXString(VALUE obj){
  if(!NIL_P(obj)){
    Check_Type(obj,T_STRING);
    return FXString(StringValuePtr(obj));
    }
  else{
    return FXString::null;
    }
  }
%}

/* Convert Ruby string to FXString */
%typemap(in) FXString "$1 = to_FXString($input);";

/* Convert Ruby string to const FXString& */
%typemap(in) const FXString& (SwigValueWrapper<FXString> p) "p = to_FXString($input); $1 = &p;";

/* Convert either a String or nil to an FXchar* */
%typemap(in) const FXchar* "$1 = NIL_P($input) ? 0 : StringValuePtr($input);";

/* Convert Ruby true and false to FXbool inputs */
%{
inline FXbool to_FXbool(VALUE obj){
  if (obj == Qtrue || obj == Qfalse){
    return (obj == Qtrue) ? TRUE : FALSE;
    }
  else{
    return static_cast<FXbool>(NUM2UINT(obj));
    }
  }
%}

%typemap(in) FXbool "$1 = to_FXbool($input);";

/* Convert FXbool return types */
%typemap(out) FXbool "$result = $1 ? Qtrue : Qfalse;";

/* Convert FXString struct members to Ruby strings */
%typemap(out) FXString * "$result = to_ruby($1->text());";

/* Convert FXString return values to Ruby strings */
%typemap(out) FXString "$result = to_ruby($1.text());";

/* Convert const FXString& return values to Ruby strings */
%typemap(out) const FXString& "$result = to_ruby($1->text());";

/**
 * Used by constructors for icons and images that require an array
 * of bytes as input; accepts a Ruby string instance instead. Also
 * accepts "nil" in place of a NULL pointer.
 */
%typemap(in) const void* pix {
  if ($input != Qnil) {
    Check_Type($input, T_STRING);
    $1 = reinterpret_cast<$1_ltype>(RSTRING_PTR($input));
  } else {
    $1 = NULL;
  }
}
%typecheck(SWIG_TYPECHECK_VOIDPTR) const void * pix {
  $1 = (NIL_P($input) || TYPE($input) == T_STRING) ? 1 : 0;
}

/**
 * Used by constructors for icons and images that require an array
 * of FXColor values as input; accepts a Ruby array of Integers instead. Also
 * accepts "nil" in place of a NULL pointer.
 */
%typemap(in) const FXColor* PIXELS {
  $1=NULL;
  if($input!=Qnil){
    Check_Type($input,T_ARRAY);
    if(FXMALLOC(&$1,FXColor,RARRAY_LEN($input))){
      for(long i=0; i<RARRAY_LEN($input); i++){
        $1[i]=static_cast<FXColor>(NUM2UINT(rb_ary_entry($input,i)));
      }
    }
  }
}

/**
 * Free-up the temporary array allocated above.
 */
%typemap(freearg) const FXColor* PIXELS "FXFREE(&$1);";

/**
 * Used by constructors for FXXPMIcon and FXXPMImage, which require an array
 * of strings as input; uses a Ruby list of strings instead. Also accepts "nil"
 * in place of a NULL pointer.
 */
%typemap(in) const FXchar** pix {
  $1 = NULL;
  if ($input != Qnil) {
    Check_Type($input, T_ARRAY);
    if (FXMALLOC(&$1, FXchar *, RARRAY_LEN($input))) {
      for (long i = 0; i < RARRAY_LEN($input); i++) {
        VALUE e = rb_ary_entry($input, i);
        $1[i] = (FXchar *) StringValuePtr(e);
      }
    }
  }
}

/**
 * Free-up the temporary array allocated above.
 */
%typemap(freearg) const FXchar** pix "FXFREE(&$1);";

/* Used for FXHeader#fillItems and others */
%typecheck(SWIG_TYPECHECK_STRING_ARRAY) const FXchar** strings {
  $1 = (TYPE($input) == T_ARRAY) ? 1 : 0;
  if ($1 != 0) {
    for (long i = 0; i < RARRAY_LEN($input); i++) {
      if (TYPE(rb_ary_entry($input, i)) != T_STRING) {
        $1 = 0;
	break;
      }
    }
  }
}

%typemap(in) const FXchar** strings {
  $1 = NULL;
  if(!NIL_P($input)){
    Check_Type($input, T_ARRAY);
    if (FXMALLOC(&$1, FXchar *, RARRAY_LEN($input)+1)) {
      for (long i = 0; i < RARRAY_LEN($input); i++) {
        VALUE e = rb_ary_entry($input, i);
        $1[i] = (FXchar *) StringValuePtr(e);
      }
      $1[RARRAY_LEN($input)] = 0;
    }
  }
}

%typemap(freearg) const FXchar** strings "FXFREE(&$1);";

/* Used for FXColorList#fillItems */
%typemap(in) FXColor* colors {
  $1 = NULL;
  if(!NIL_P($input)){
    Check_Type($input, T_ARRAY);
    if (FXMALLOC(&$1, FXColor, RARRAY_LEN($input)+1)) {
      for (long i = 0; i < RARRAY_LEN($input); i++) {
        $1[i] = static_cast<FXColor>(NUM2ULONG(rb_ary_entry($input, i)));
      }
      $1[RARRAY_LEN($input)] = 0;
    }
  }
}

%typemap(freearg) FXColor* colors "FXFREE(&$1);";

/* Convert a Ruby object into a void pointer (for list item data) */
%typemap(in) void* ITEMDATA "$1 = ($input == Qnil) ? NULL : (void *) $input;";

/* Convert a Ruby FXEvent instance into a pointer to a C++ FXEvent */
%{
static swig_type_info* FXEventTypeInfo=0;

inline void* to_FXEvent(VALUE obj){
  void* ptr;
  if(!FXEventTypeInfo){
    FXEventTypeInfo=SWIG_TypeQuery("FXEvent *");
    FXASSERT(FXEventTypeInfo!=0);
    }
  SWIG_ConvertPtr(obj,&ptr,FXEventTypeInfo,1);
  return ptr;
  }
%}

/* Convert a Ruby instance into either a NULL pointer or a non-NULL */
%typemap(in) void* PTR_BOOL "$1 = reinterpret_cast<void*>(NIL_P($input) ? 0 : 1);";

/* Convert a Ruby number into an FXColor */
%typemap(in) void* PTR_COLOR "$1 = reinterpret_cast<void*>(NUM2UINT($input));";

/* Convert a Ruby string to a C string */
%typemap(in) void* PTR_CSTRING "$1 = static_cast<void*>(StringValuePtr($input));";

/* Convert a Ruby array (of size 2) into an FXdouble array */
%typemap(in) void* PTR_DBLRANGE_IN(FXdouble values[2]) {
  Check_Type($input, T_ARRAY);
  values[0] = (FXdouble) NUM2DBL(rb_ary_entry($input, 0));
  values[1] = (FXdouble) NUM2DBL(rb_ary_entry($input, 1));
  $1 = (void *) values;
}

/* Convert an FXdouble array to a Ruby array */
%typemap(freeargs) void* PTR_DBLRANGE_OUT(FXdouble* values) {
  Check_Type($input, T_ARRAY);
  values = (FXdouble*) $1;
  rb_ary_store($input, 0, to_ruby(values[0]));
  rb_ary_store($input, 1, to_ruby(values[1]));
}

/* Convert a Ruby FXDirItem instance into a pointer to a C++ FXDirItem */
%typemap(in) void* PTR_DIRITEM "SWIG_ConvertPtr($input,&$1,SWIGTYPE_p_FXDirItem,1);";

%typemap(in) void* PTR_EVENT "$1 = to_FXEvent($input);";

/* Convert a Ruby array (of size 3) into an FXfloat array */
%typemap(in) void* PTR_FLTARRAY(FXfloat values[3]) {
  Check_Type($input, T_ARRAY);
  values[0] = (FXfloat) NUM2DBL(rb_ary_entry($input, 0));
  values[1] = (FXfloat) NUM2DBL(rb_ary_entry($input, 1));
  values[2] = (FXfloat) NUM2DBL(rb_ary_entry($input, 2));
  $1 = (void *) values;
}

/* Convert a Ruby FXIcon reference to a pointer to an FXIcon */
%typemap(in) void* PTR_ICON(void *tmp) {
  tmp = FXRbConvertPtr($input, FXRbTypeQuery("FXIcon *"));
  $1 = (void *) &tmp;
}

/* Message data is ignored (doesn't matter what we set $1 to) */
%typemap(in) void* PTR_IGNORE "$1 = 0;";

/* Convert a Ruby number into an FXint */
%typemap(in) void* PTR_INT "$1 = reinterpret_cast<void*>(NUM2INT($input));";

/* Convert a Ruby array (size 2) into an FXint array */
%typemap(in) void* PTR_INTRANGE_IN(FXint values[2]) {
  Check_Type($input, T_ARRAY);
  values[0] = (FXint) NUM2INT(rb_ary_entry($input, 0));
  values[1] = (FXint) NUM2INT(rb_ary_entry($input, 1));
  $1 = static_cast<void*>(values);
}

/* Convert an FXint array (size 2) into a Ruby array */
%typemap(freeargs) void* PTR_INTRANGE_OUT(FXint* values) {
  Check_Type($input, T_ARRAY);
  values = (FXint *) $1;
  rb_ary_store($input, 0, to_ruby(values[0]));
  rb_ary_store($input, 1, to_ruby(values[1]));
}

/* Convert a Ruby number into an FXival */
%typemap(in) void* PTR_IVAL "$1 = reinterpret_cast<void*>(static_cast<FXival>(NUM2LONG($input)));";

/* Convert a Ruby instance (type varies) into the appropriate void pointer */
%typemap(in) void* PTR_MAGIC "$1 = FXRbGetExpectedData(self, arg3, $input);";

/* Convert a Ruby instance into a void pointer to a C++ NULL */
%typemap(in) void* PTR_NULL "$1 = 0;";

/* Convert a Ruby FXObject instance into a pointer to a C++ FXObject */
%typemap(in) void* PTR_OBJECT "SWIG_ConvertPtr($input,&$1,SWIGTYPE_p_FXObject,1);";

/* Convert a Ruby FXPoint instance into a pointer to a C++ FXPoint */
%typemap(in) void* PTR_POINT "$1 = FXRbConvertPtr($input, FXRbTypeQuery(\"FXPoint *\"));";

/* Convert a Ruby number into a pointer to an FXdouble */
%typemap(in) void* PTR_PDOUBLE(FXdouble value) {
  value = (FXdouble) NUM2DBL($input);
  $1 = (void *) &value;
}

/* Convert a Ruby number into a pointer to an FXint */
%typemap(in) void* PTR_PINT(FXint value) {
  value = (FXint) NUM2INT($input);
  $1 = static_cast<void*>(&value);
}

/* Convert a Ruby string to a pointer to an FXString */
%typemap(in) void* PTR_STRING(FXString value) {
  value = FXString(StringValuePtr($input));
  $1 = (void *) &value;
}

/* Convert a Ruby FXTreeItem instance into a pointer to a C++ FXTreeItem */
%typemap(in) void* PTR_TREEITEM "SWIG_ConvertPtr($input,&$1,SWIGTYPE_p_FXTreeItem,1);";

/* Convert a Ruby number into an FXuchar */
%typemap(in) void* PTR_UCHAR "$1 = reinterpret_cast<void*>(NUM2UINT($input));";

/* Convert a Ruby number into an FXuint */
%typemap(in) void* PTR_UINT "$1 = reinterpret_cast<void*>(NUM2UINT($input));";

/**
 * Accept either an FXVec3f instance or a 3-element array of floats
 * when an FXVec3f is expected as input.
 */

%typemap(in) const FXVec3f& {
    if (TYPE($input) == T_ARRAY) {
        $1 = new FXVec3f(NUM2DBL(rb_ary_entry($input, 0)), NUM2DBL(rb_ary_entry($input, 1)), NUM2DBL(rb_ary_entry($input, 2)));
    } else {
        FXVec3f *p;
	SWIG_ConvertPtr($input, (void **)&p, SWIGTYPE_p_FXVec3f, 1);
	$1 = new FXVec3f(*p);
    }
}

%typemap(freearg) const FXVec3f& "delete $1;";

%typemap(in) FXVec3f * (FXVec3f tmp) {
    if (TYPE($input) == T_ARRAY) {
        tmp = FXVec3f(NUM2DBL(rb_ary_entry($input, 0)), NUM2DBL(rb_ary_entry($input, 1)), NUM2DBL(rb_ary_entry($input, 2)));
        $1 = &tmp;
    } else {
	SWIG_ConvertPtr($input, (void **) &$1, SWIGTYPE_p_FXVec3f, 1);
    }
}

/**
 * Accept either an FXVec4f instance or a 4-element array of floats
 * when an FXVec4f is expected as input.
 */

%typemap(in) const FXVec4f& {
    if (TYPE($input) == T_ARRAY) {
        $1 = new FXVec4f(NUM2DBL(rb_ary_entry($input, 0)), NUM2DBL(rb_ary_entry($input, 1)), NUM2DBL(rb_ary_entry($input, 2)), NUM2DBL(rb_ary_entry($input, 3)));
    } else {
        FXVec4f *p;
	SWIG_ConvertPtr($input,(void **)&p,SWIGTYPE_p_FXVec4f,1);
	$1 = new FXVec4f(*p);
    }
}

%typemap(freearg) const FXVec4f& "delete $1;";

%typemap(in) FXVec4f * (FXVec4f tmp) {
    if (TYPE($input) == T_ARRAY) {
        tmp = FXVec4f(NUM2DBL(rb_ary_entry($input, 0)), NUM2DBL(rb_ary_entry($input, 1)), NUM2DBL(rb_ary_entry($input, 2)), NUM2DBL(rb_ary_entry($input, 3)));
        $1 = &tmp;
    } else {
	SWIG_ConvertPtr($input, (void **) &$1, SWIGTYPE_p_FXVec4f, 1);
    }
}

/* Output typemap for FXObject instances */
%typemap(out) FXObject * {
    swig_type_info *ty = SWIG_TypeDynamicCast($1_descriptor, (void **) &$1);
    $result = FXRbGetRubyObj($1, ty);
}

/* Output typemap for FXAccelTable instances */
%typemap(out) FXAccelTable * = FXObject *;

/* Output typemap for FXApp instances */
%typemap(out) FXApp * = FXObject *;

/* Output typemap for FXBitmap instances */
%typemap(out) FXBitmap * = FXObject *;

/* Output typemap for FXButton instances */
%typemap(out) FXButton * = FXObject *;

/* Output typemap for FXChore instances */
%typemap(out) FXChore* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%nodefaultctor FXChore;

/* Output typemap for FXComposite instances */
%typemap(out) FXComposite * = FXObject *;

/* Output typemap for FXCursor instances */
%typemap(out) FXCursor * = FXObject *;

/* Output typemap for FXDragCorner instances */
%typemap(out) FXDragCorner * = FXObject *;

/* Output typemap for FXFileAssoc instances */
%typemap(out) FXFileAssoc* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXFileDict instances */
%typemap(out) FXFileDict * = FXObject *;

/* Output typemap for FXFoldingItem instances */
%typemap(out) FXFoldingItem* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXFont instances */
%typemap(out) FXFont * = FXObject *;

/* Output typemap for FXFontDesc instances */
%typemap(out) FXFontDesc {
    FXFontDesc* resultptr = new FXFontDesc($1);
    $result = FXRbGetRubyObj(resultptr, "FXFontDesc *");
}
%typemap(out) FXFontDesc* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXGLObject instances */
%typemap(out) FXGLObject* = FXObject *;

/* Output typemap for FXGLShape instances */
%typemap(out) FXGLShape * = FXObject *;

/* Output typemap for FXGLVisual instances */
%typemap(out) FXGLVisual * = FXObject *;

/* Output typemap for FXHeader instances */
%typemap(out) FXHeader * = FXObject *;

/* Output typemap for FXHeaderItem instances */
%typemap(out) FXHeaderItem * = FXObject *;

/* Output typemap for FXMat4f instances */
%typemap(out) FXMat4f {
    FXMat4f* resultptr = new FXMat4f($1);
    $result = FXRbGetRubyObj(resultptr, "FXMat4f *");
}
%typemap(out) FXMat4f& "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXVec2d instances */
%typemap(out) FXVec2d* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%typemap(out) FXVec2d& "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXVec2f instances */
%typemap(out) FXVec2f* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%typemap(out) FXVec2f& "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXVec3f instances */
%typemap(out) FXVec3f {
    FXVec3f* resultptr = new FXVec3f($1);
    $result = FXRbGetRubyObj(resultptr, "FXVec3f *");
}
%typemap(out) FXVec3f*       "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%typemap(out) const FXVec3f& {
    FXVec3f* resultptr = new FXVec3f(*$1);
    $result = FXRbGetRubyObj(resultptr, "FXVec3f *");
}

/* Output typemap for FXVec4f instances */
%typemap(out) FXVec4f {
    FXVec4f* resultptr = new FXVec4f($1);
    $result = FXRbGetRubyObj(resultptr, "FXVec4f *");
}
%typemap(out) FXVec4f* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%typemap(out) const FXVec4f& {
    FXVec4f* resultptr = new FXVec4f(*$1);
    $result = FXRbGetRubyObj(resultptr, "FXVec4f *");
}

/* Output typemap for FXIcon instances */
%typemap(out) FXIcon * = FXObject *;

/* Output typemap for FXIconItem instances */
%typemap(out) FXIconItem * = FXObject *;

/* Output typemap for FXImage instances */
%typemap(out) FXImage * = FXObject *;

/* Output typemap for FXLight instances */
%typemap(out) FXLight {
    FXLight *resultptr = new FXLight($1);
    $result = FXRbGetRubyObj(resultptr, "FXLight *");
}
%typemap(out) FXLight* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXListItem instances */
%typemap(out) FXListItem * = FXObject *;

/* Output typemap for FXMaterial instances */
%typemap(out) FXMaterial {
    FXMaterial *resultptr = new FXMaterial($1);
    $result = FXRbGetRubyObj(resultptr, "FXMaterial *");
}

/* Output typemap for FXMDIChild instances */
%typemap(out) FXMDIChild * = FXObject *;

/* Output typemap for FXOption instances */
%typemap(out) FXOption * = FXObject *;

/* Output typemap for FXPoint instances */
%typemap(out) FXPoint* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXPopup instances */
%typemap(out) FXPopup * = FXObject *;

/* Output typemap for FXPrinter instances */
%typemap(out) FXPrinter {
    FXPrinter *resultptr = new FXPrinter($1);
    $result = FXRbGetRubyObj(resultptr, "FXPrinter *");
}

/* Output typemap for FXQuatf instances */
%typemap(out) FXQuatf {
    FXQuatf *resultptr = new FXQuatf($1);
    $result = FXRbGetRubyObj(resultptr, "FXQuatf *");
}
%typemap(out) FXQuatf& "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXRangef instances */
%typemap(out) FXRangef {
    FXRangef* resultptr = new FXRangef($1);
    $result = FXRbGetRubyObj(resultptr, "FXRangef *");
}
%typemap(out) FXRangef& "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXRectangle instances */
%typemap(out) FXRectangle*, FXRectangle&, const FXRectangle& "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%typemap(out) FXRectangle {
    FXRectangle* resultptr = new FXRectangle($1);
    $result = FXRbGetRubyObj(resultptr, "FXRectangle *");
}

/* Output typemap for FXRegion instances */
%typemap(out) FXRegion {
    FXRegion* resultptr = new FXRegion($1);
    $result = FXRbGetRubyObj(resultptr, "FXRegion *");
}
%typemap(out) FXRegion&       "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%typemap(out) const FXRegion& "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXRegistry instances */
%typemap(out) FXRegistry& = FXObject *;

/* Output typemap for FXRootWindow instances */
%typemap(out) FXRootWindow * = FXObject *;

/* Output typemap for FXScrollBar instances */
%typemap(out) FXScrollBar * = FXObject *;

/* Output typemap for FXSize instances */
%typemap(out) FXSize* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXStatusLine instances */
%typemap(out) FXStatusLine * = FXObject *;

/* Output typemap for FXStream instances */
%typemap(out) FXStream* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXStringDict instances */
%typemap(out) FXStringDict * = FXObject *;

/* Output typemap for FXTableItem instances */
%typemap(out) FXTableItem * = FXObject *;

/* Output typemap for FXTablePos instances */
// %typemap(out) FXTablePos* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXTableRange instances */
// %typemap(out) FXTableRange* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

/* Output typemap for FXTimer instances */
%typemap(out) FXTimer* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";
%nodefaultctor FXTimer;

/* Output typemap for FXTreeItem instances */
%typemap(out) FXTreeItem * = FXObject *;

/* Output typemap for FXVerticalFrame instances */
%typemap(out) FXVerticalFrame * = FXObject *;

/* Output typemap for FXViewport instances */
%typemap(out) FXViewport {
    FXViewport* resultptr = new FXViewport($1);
    $result = FXRbGetRubyObj(resultptr, "FXViewport *");
}

/* Output typemap for FXVisual instances */
%typemap(out) FXVisual* = FXObject *;

/* Output typemap for FXWindow instances */
%typemap(out) FXWindow * = FXObject *;

/* Output typemap for NotifyHeader instances */
// %typemap(out) NotifyHeader* "$result = FXRbGetRubyObj($1, \"$1_ltype\");";

// Extract a C array (points) and its length (npoints) from a Ruby array of FXPoint instances
%typecheck(SWIG_TYPECHECK_OBJECT_ARRAY) (const FXPoint* points, FXuint npoints) {
  $1 = (TYPE($input) == T_ARRAY) ? 1 : 0;
}
%typemap(in) (const FXPoint* points, FXuint npoints) {
    Check_Type($input, T_ARRAY);
    $1 = new FXPoint[RARRAY_LEN($input)];
    $2 = static_cast<FXuint>( RARRAY_LEN($input) );
    for (FXuint i = 0; i < $2; i++) {
        FXPoint *pPoint;
        Data_Get_Struct(rb_ary_entry($input, i), FXPoint, pPoint);
        $1[i] = *pPoint;
    }
}
%typemap(freearg) (const FXPoint* points, FXuint npoints) {
    delete [] $1;
}

// Extract a C array (segments) and its length (nsegments) from a Ruby array of FXSegment instances
%typemap(in) (const FXSegment* segments, FXuint nsegments) {
    Check_Type($input, T_ARRAY);
    $1 = new FXSegment[RARRAY_LEN($input)];
    $2 = static_cast<FXuint>( RARRAY_LEN($input) );
    for (FXuint i = 0; i < $2; i++) {
        FXSegment *pSeg;
        Data_Get_Struct(rb_ary_entry($input, i), FXSegment, pSeg);
        $1[i] = *pSeg;
    }
}

%typemap(freearg) (const FXSegment* segments, FXuint nsegments) {
    delete [] $1;
}

// Extract a C array (rectangles) and its length (nrectangles) from a Ruby array of FXRectangle instances
%typemap(in) (const FXRectangle* rectangles, FXuint nrectangles) {
    Check_Type($input, T_ARRAY);
    $1 = new FXRectangle[RARRAY_LEN($input)];
    $2 = static_cast<FXuint>( RARRAY_LEN($input) );
    for (FXuint i = 0; i < $2; i++) {
        FXRectangle *pRect;
        Data_Get_Struct(rb_ary_entry($input, i), FXRectangle, pRect);
        $1[i] = *pRect;
    }
}

%typemap(freearg) (const FXRectangle* rectangles, FXuint nrectangles) {
    delete [] $1;
}

// Extract a C array (arcs) and its length (narcs) from a Ruby array of FXArc instances
%typemap(in) (const FXArc* arcs, FXuint narcs) {
    Check_Type($input, T_ARRAY);
    $1 = new FXArc[RARRAY_LEN($input)];
    $2 = static_cast<FXuint>( RARRAY_LEN($input) );
    for (FXuint i = 0; i < $2; i++) {
        FXArc *pArc;
        Data_Get_Struct(rb_ary_entry($input, i), FXArc, pArc);
        $1[i] = *pArc;
    }
}

%typemap(freearg) (const FXArc* rectangles, FXuint narcs) {
    delete [] $1;
}

// Extract the C string pointer and string length from a Ruby string
%typemap(in) (const FXchar* string, FXuint length) {
    Check_Type($input, T_STRING);
    $1 = StringValuePtr($input);
    $2 = RSTRING_LEN($input);
}

// Extract a C array (dashpattern) and its length (dashlength) from a Ruby array of Integers
%typemap(in) (const FXchar* dashpattern, FXuint dashlength) {
    Check_Type($input, T_ARRAY);
    $1 = new FXchar[RARRAY_LEN($input)];
    $2 = static_cast<FXuint>( RARRAY_LEN($input) );
    for (FXuint i = 0; i < $2; i++) {
        $1[i] = NUM2INT(rb_ary_entry($input, i));
    }
}

%typemap(freearg) (const FXchar* dashpattern, FXuint dashlength) {
    delete [] $1;
}

%typemap(in) (FXuint* path, FXint n) {
  Check_Type($input, T_ARRAY);
  FXMALLOC(&$1,FXuint,RARRAY_LEN($input));
  $2=static_cast<FXint>(RARRAY_LEN($input));
  for(FXint i=0; i<$2; i++){
    $1[i]=NUM2UINT(rb_ary_entry($input,i));
    }
}

%typemap(freearg) (FXuint* path, FXint n) {
  FXFREE(&$1);
}

/* Convert an array of FXColor values (see constructor for FXMemoryBuffer) */
%typemap(in) (FXColor *data,FXuint size) {
  Check_Type($input, T_ARRAY);
  FXMALLOC(&$1,FXColor,RARRAY_LEN($input));
  $2=static_cast<FXuint>(RARRAY_LEN($input));
  for(FXint i=0; i<$2; i++){
    $1[i]=static_cast<FXColor>(NUM2UINT(rb_ary_entry($input,i)));
    }
}

%typemap(freearg) (FXColor *data,FXuint size) {
  FXFREE(&$1);
}

/**
 * Special typemap for the 2nd argument to FXToolBar::dock(). They should
 * be able to pass either zero, -1, or a window to that function and get
 * the same behavior as in FOX.
 */

%typemap(in) FXWindow* TOOLBAR_DOCK_AFTER {
    if (TYPE($input) == T_FIXNUM || TYPE($input) == T_BIGNUM)) {
        $1 = reinterpret_cast<FXWindow *>(static_cast<long>(NUM2INT($input)));
    } else {
        SWIG_ConvertPtr($input, (void **) &$1, SWIGTYPE_p_FXWindow, 1);
    }
}

/* Convert a null-terminated array of FXGLObject pointers to a Ruby array */
%typemap(out) FXGLObject** {
  $result=Qnil;
  if($1){
    $result=rb_ary_new();
    register FXGLObject** p=$1;
    while(*p){
      rb_ary_push($result,to_ruby(*p));
      p++;
      }
    FXFREE(&$1);
    }
}

/* Convert a Ruby Integer to an FXID (int_to_fxid() is defined in FXRuby.h) */
%typemap(in) FXID "$1 = int_to_fxid($input);";

/* Convert an FXID to a Ruby Integer (fxid_to_int() is defined in FXRuby.h) */
%typemap(out) FXID "$result = fxid_to_int($1);";

%typemap(in) FXuchar *data "$1 = NIL_P($input) ? 0 : reinterpret_cast<FXuchar*>(StringValuePtr($input));";

// FXlong values
%typemap(in)  FXlong "$1 = static_cast<FXlong>(NUM2LONG($input));";
%typemap(out) FXlong "$result = LONG2NUM($1);";

// FXulong values
%typemap(in)  FXulong "$1 = static_cast<FXulong>(NUM2ULONG($input));";
%typemap(out) FXulong "$result = ULONG2NUM($1);";
