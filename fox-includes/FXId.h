/********************************************************************************
*                                                                               *
*                                  X - O b j e c t                              *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2004 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXId.h 1889 2004-05-26 03:13:01Z lyle $                              *
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
private:
  FXId(const FXId&);
  FXId &operator=(const FXId&);
protected:
  FXId():app((FXApp*)-1L),data(NULL),xid(0){}
  FXId(FXApp* a):app(a),data(NULL),xid(0){}
public:

  /// Get application
  FXApp* getApp() const { return app; }

  /// Get XID handle
  FXID id() const { return xid; }

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
  virtual ~FXId(){app=(FXApp*)-1L;}
  };

}

#endif
