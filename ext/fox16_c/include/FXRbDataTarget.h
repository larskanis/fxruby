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
 * $Id: FXRbDataTarget.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBDATATARGET_H
#define FXRBDATATARGET_H

class FXRbDataTarget : public FXDataTarget {
  FXDECLARE(FXRbDataTarget)
#include "FXRbObjectVirtuals.h"
private:
  // Associated integer value (if it's an integer)
  FXint intValue;

  // Associated double value (if it's a float)
  FXdouble doubleValue;

  // Associated string value (if it's a string)
  FXString stringValue;

  // Associated boolean value (if it's a boolean)
  FXbool boolValue;

public:
  /// Initialize with this value
  FXRbDataTarget(VALUE value=Qnil,FXObject* tgt=NULL,FXSelector sel=0);

  // Return its current value
  VALUE getValue() const;

  // Set a new value
  void setValue(VALUE value);

  // Mark dependencies for the GC
  static void markfunc(FXDataTarget* obj);

  // Destructor
  virtual ~FXRbDataTarget(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
