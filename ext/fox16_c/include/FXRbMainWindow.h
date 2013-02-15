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
 * $Id: FXRbMainWindow.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBMAINWINDOW_H
#define FXRBMAINWINDOW_H

// Main window class
class FXRbMainWindow : public FXMainWindow {
  FXDECLARE(FXRbMainWindow)
protected:
  FXRbMainWindow(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbTopWindowVirtuals.h"
public:
  // Constructor
  FXRbMainWindow(FXApp* a,const FXString& name,FXIcon *ic=NULL,FXIcon *mi=NULL,FXuint opts=DECOR_ALL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0,FXint hs=4,FXint vs=4) : FXMainWindow(a,name,ic,mi,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Mark dependencies for the GC
  static void markfunc(FXMainWindow *self);

  // Destructor
  virtual ~FXRbMainWindow(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif

