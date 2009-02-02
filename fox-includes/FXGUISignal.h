/********************************************************************************
*                                                                               *
*                        S i g n a l   G U I   T h r e a d                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXGUISignal.h 2291 2005-12-05 03:37:36Z lyle $                        *
********************************************************************************/
#ifndef FXGUISIGNAL_H
#define FXGUISIGNAL_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {

class FXApp;


/**
* A GUI Signal is an object used by a worker thread to signal the
* user interface thread of some event; it wakes up the user interface
* thread from the blocking state and causes it to send the given message
* to the GUI Signal object's target.
*/
class FXAPI FXGUISignal : public FXObject {
  FXDECLARE(FXGUISignal)
private:
  FXApp     *app;       // Application
protected:
  FXObject  *target;    // Target object
  void      *data;      // User data
  FXSelector message;   // Message id
private:
#ifndef WIN32
  FXInputHandle fd[2];
#else
  FXInputHandle event;
#endif
protected:
  FXGUISignal();
private:
  FXGUISignal(const FXGUISignal&);
  FXGUISignal& operator=(const FXGUISignal&);
public:
  enum{
    ID_IO_READ=0,
    ID_LAST
    };
public:
  long onSignal(FXObject*,FXSelector,void*);
public:

  /// Constructor
  FXGUISignal(FXApp* a,FXObject* tgt=NULL,FXSelector sel=0,void* ptr=NULL);

  /// Get application
  FXApp* getApp() const { return app; }

  /// Set the message target object
  void setTarget(FXObject *t){ target=t; }

  /// Get the message target object, if any
  FXObject* getTarget() const { return target; }

  /// Set the message identifier
  void setSelector(FXSelector sel){ message=sel; }

  /// Get the message identifier
  FXSelector getSelector() const { return message; }

  /// Set user data pointer
  void setData(void *ptr){ data=ptr; }

  /// Get user data pointer
  void* getData() const { return data; }

  /**
  * Signal the event; this API may be called by the worker thread
  * to send a message to the user-interface thread.
  */
  void signal();

  /// Destructor
  virtual ~FXGUISignal();
  };

}

#endif


