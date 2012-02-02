/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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
 * $Id: FXRbRuler.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBRULER_H
#define FXRBRULER_H

#ifndef FXRULER_H
#include "FXRuler.h"
#endif

class FXRbRuler : public FXRuler {
  FXDECLARE(FXRbRuler)
protected:
  FXRbRuler(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
public:

  /// Construct label with given text and icon
  FXRbRuler(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=RULER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD) : FXRuler(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb) {}

  // Mark dependencies for the GC
  static void markfunc(FXRuler* self);

  // Destructor
  virtual ~FXRbRuler(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
