/********************************************************************************
*                                                                               *
*                                  X - O b j e c t                              *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2008 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXId.h 2867 2008-05-29 21:50:28Z lyle $                              *
********************************************************************************/
#ifndef FXID_H
#define FXID_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {

class FXApp;


/// Encapsulates server side resource
class FXAPI FXId : public FXObject {
  FXDECLARE_ABSTRACT(FXId)
private:
  FXApp *app;             // Back link to application object
  void  *data;            // User data
protected:
  FXID   xid;
  FXID   rsc;
private:
  FXId(const FXId&);
  FXId &operator=(const FXId&);
protected:
  FXId():app((FXApp*)-1L),data(NULL),xid(0),rsc(0){}
  FXId(FXApp* a):app(a),data(NULL),xid(0),rsc(0){}
public:

  /// Get application
  FXApp* getApp() const { return app; }

  /// Get XID handle
  FXID id() const { return xid; }

  /// Get resource handle
  FXID res() const { return rsc; }
  
  /// Create resource
  virtual void create(){}

  /// Detach resource
  virtual void detach(){}

  /// Destroy resource
  virtual void destroy(){}

  /// Set user data pointer
  void setUserData(void *ptr){ data=ptr; }

  /// Get user data pointer
  void* getUserData() const { return data; }

  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXId();
  };

}

#endif
