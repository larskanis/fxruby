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
 * $Id: FXRbRecentFiles.h 2272 2005-12-02 02:11:23Z lyle $
 ***********************************************************************/

#ifndef FXRBRECENTFILES_H
#define FXRBRECENTFILES_H

class FXRbRecentFiles : public FXRecentFiles {
  FXDECLARE(FXRbRecentFiles)
#include "FXRbObjectVirtuals.h"
public:
  /// Make new Recent Files Group using global application instance
  FXRbRecentFiles(){}

  /// Make new recent files group with default groupname
  FXRbRecentFiles(FXApp* a) : FXRecentFiles(a){}

  /// Make new Recent Files Group with groupname gp
  FXRbRecentFiles(FXApp* a,const FXString& gp,FXObject *tgt=NULL,FXSelector sel=0) : FXRecentFiles(a,gp,tgt,sel){}

  // Mark dependencies for the GC
  static void markfunc(FXRecentFiles* self);

  // Destructor
  virtual ~FXRbRecentFiles(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
