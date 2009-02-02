/********************************************************************************
*                                                                               *
*         I n t e r - T h r e a d    M e s s a g i n g    C h a n n e l         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2006,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMessageChannel.h,v 1.7 2007/10/30 17:30:55 fox Exp $                   *
********************************************************************************/
#ifndef FXMESSAGECHANNEL_H
#define FXMESSAGECHANNEL_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif


namespace FX {

class FXApp;


/**
* FXMessageChannel manages a messaging channel between a worker thread and the main
* user-interface thread.
* When an FXMessageChannel is constructed, it automatically calls addInput() function to
* register itself as the message handler for the SEL_IO_READ message from FXApp.
* Likewise, when FXMessageChannel is destroyed, it calls removeInput() to remove itself
* as the message handler for the SEL_IO_READ message from FXApp.
* When a worker thread calls the message() API, the target and message, as well
* as optional message data, are written into the message channel.
* The main user-interface thread is awakened and subsequently dispatches to the
* onMessage handler of FXMessageChannel, which reads the target, selector, and optional
* message data from the channel and then dispatches to this target using the given
* selector.
* Thus, FXMessageChannel provides a worker thread with a way to asynchronously invoke
* any message handler in the context of the main user-interface thread.
* If the size of the optional data is zero, the message handler will be passed a
* NULL pointer.
*/
class FXAPI FXMessageChannel : public FXObject {
  FXDECLARE(FXMessageChannel)
private:
  FXApp *app;
private:
  FXInputHandle h[3];
  FXMutex       m;
protected:
  FXMessageChannel();
private:
  FXMessageChannel(const FXMessageChannel&);
  FXMessageChannel& operator=(const FXMessageChannel&);
public:
  enum{
    ID_IO_READ=1,
    ID_LAST
    };
public:
  long onMessage(FXObject*,FXSelector,void*);
public:

  /// Initialize message channel
  FXMessageChannel(FXApp* a);

  /// Get application pointer
  FXApp* getApp() const { return app; }

  /// Send a message msg comprising of FXSEL(type,id) to a target tgt, and pass optional data of size bytes
  FXbool message(FXObject* tgt,FXSelector msg,const void* data=NULL,FXint size=0);

  /// Clean up message channel
  virtual ~FXMessageChannel();
  };

}

#endif


