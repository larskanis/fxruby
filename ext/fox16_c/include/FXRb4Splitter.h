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
 * $Id: FXRb4Splitter.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRB4SPLITTER_H
#define FXRB4SPLITTER_H

class FXRb4Splitter : public FX4Splitter {
  FXDECLARE(FXRb4Splitter)
protected:
  FXRb4Splitter(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:
  /// Create 4-way splitter, initially shown as four unexpanded panes
  FXRb4Splitter(FXComposite* p,FXuint opts=FOURSPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FX4Splitter(p,opts,x,y,w,h){}

  /// Create 4-way splitter, initially shown as four unexpanded panes; target is informed of size changes
  FXRb4Splitter(FXComposite* p,FXObject* tgt,FXSelector sel,FXuint opts=FOURSPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FX4Splitter(p,tgt,sel,opts,x,y,w,h){}

  // Mark dependencies for the GC
  static void markfunc(FX4Splitter* self);

  // Destructor
  virtual ~FXRb4Splitter(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
