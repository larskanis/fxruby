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
 * $Id: FXRbDataTarget.cpp 2713 2007-11-14 15:27:36Z lyle $
 ***********************************************************************/

#include "FXRbCommon.h"

/**
 * Data targets for FXRuby are implemented slightly different from
 * those in the C++ implementation since we don't have the concept
 * of C++ references for immutable types (like integers, floats and
 * strings).
 */

// Initialize a data target with this value
FXRbDataTarget::FXRbDataTarget(VALUE value,FXObject* tgt,FXSelector sel) : FXDataTarget(tgt,sel), intValue(0), doubleValue(0.0), boolValue(FALSE) {
  setValue(value);
  }

// Set new value for data target
void FXRbDataTarget::setValue(VALUE value){
  switch (TYPE(value)) {
    case T_NIL:
      connect();
      break;
    case T_FIXNUM:
      intValue=static_cast<FXint>(NUM2LONG(value));
      connect(intValue);
      break;
    case T_BIGNUM: /* still not sure about this conversion */
      intValue=static_cast<FXint>(NUM2ULONG(value));
      connect(intValue);
      break;
    case T_FLOAT:
      doubleValue=NUM2DBL(value);
      connect(doubleValue);
      break;
    case T_STRING:
      stringValue=StringValuePtr(value);
      connect(stringValue);
      break;
    case T_TRUE:
      boolValue=TRUE;
      connect(boolValue);
      break;
    case T_FALSE:
      boolValue=FALSE;
      connect(boolValue);
      break;
    default:
      rb_raise(rb_eTypeError,
        "can't initialize FXDataTarget with type %s.",
        rb_class2name(CLASS_OF(value)));
    }
  }

// Return current value for this data target
VALUE FXRbDataTarget::getValue() const {
  switch(type){
    case DT_VOID:
      return Qnil;
    case DT_CHAR:
      return to_ruby(*reinterpret_cast<FXchar*>(data));
    case DT_UCHAR:
      return to_ruby(*reinterpret_cast<FXuchar*>(data));
    case DT_SHORT:
      return to_ruby(*reinterpret_cast<FXshort*>(data));
    case DT_USHORT:
      return to_ruby(*reinterpret_cast<FXushort*>(data));
    case DT_INT:
      return to_ruby(*reinterpret_cast<FXint*>(data));
    case DT_UINT:
      return to_ruby(*reinterpret_cast<FXuint*>(data));
    case DT_LONG:
      return to_ruby(*reinterpret_cast<FXlong*>(data));
    case DT_ULONG:
      return to_ruby(*reinterpret_cast<FXulong*>(data));
    case DT_FLOAT:
      return to_ruby(*reinterpret_cast<FXfloat*>(data));
    case DT_DOUBLE:
      return to_ruby(*reinterpret_cast<FXdouble*>(data));
    case DT_STRING:
      return to_ruby(*reinterpret_cast<FXString*>(data));
    default:
      fxerror("unknown data type in FXRbDataTarget::getValue()");
    }
  return Qnil;
  }

