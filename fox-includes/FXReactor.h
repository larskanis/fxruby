/********************************************************************************
*                                                                               *
*                     E v e n t   R e a c t o r   C l a s s                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2006,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXReactor.h,v 1.29 2007/03/22 21:09:43 fox Exp $                         *
********************************************************************************/
#ifndef FXREACTOR_H
#define FXREACTOR_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

//////////////////////////////  UNDER DEVELOPMENT  //////////////////////////////


namespace FX {


class FXReactor;
struct FXHandles;


/// Dispatchable
class FXAPI FXDispatchable {
private:
  FXDispatchable(const FXDispatchable&);
  FXDispatchable &operator=(const FXDispatchable&);
public:
  FXDispatchable(){}
  virtual FXbool dispatch();
  virtual ~FXDispatchable(){}
  };


/// Timer dispatchable 
class FXAPI FXTimerDispatchable : public FXDispatchable {
  friend class FXReactor;
private:
  FXTimerDispatchable *next;    // Next timeout in list
  FXTime               due;     // When timer is due (ns)
private:
  FXTimerDispatchable(const FXTimerDispatchable&);
  FXTimerDispatchable &operator=(const FXTimerDispatchable&);
public:
  FXTimerDispatchable(FXTime d=0):next(NULL),due(d){}
  };
  

/// Chore dispatchable
class FXAPI FXChoreDispatchable : public FXDispatchable {
  friend class FXReactor;
private:
  FXChoreDispatchable *next;    // Next timeout in list
private:
  FXChoreDispatchable(const FXChoreDispatchable&);
  FXChoreDispatchable &operator=(const FXChoreDispatchable&);
public:
  FXChoreDispatchable():next(NULL){}
  };


/**
* A Reactor watches a number of devices and signals for activity
* and dispatches to the proper function when activity is observed.
*/
class FXAPI FXReactor : public FXObject {
  FXDECLARE(FXReactor)
private:
  FXMutex              accessing;       // Accessing internals
  FXMutex              working;         // Working and not blocked
  FXHandles           *handles;         // Handle to watch
  FXTimerDispatchable *timers;          // Timers
  FXbool               signotified[64]; // Notified signals
  FXint                sigreceived;     // Latest signal received
  FXint                maxhandle;       // Highest active handle
  FXint                current;         // Current handle
  FXbool               initialized;     // Is initialized
protected:
  static FXAutoThreadStorageKey reactorStorageKey;
private:
  FXReactor(const FXReactor&);
  FXReactor &operator=(const FXReactor&);
  static void signalhandler(int sig);
public:
  enum {
    InputNone   = 0,            /// Inactive handle
    InputRead   = 1,            /// Read input handle
    InputWrite  = 2,            /// Write input handle
    InputExcept = 4             /// Except input handle
    };
public:

  /**
  * Construct reactor object.
  */
  FXReactor();

  /**
  * The global mutex signifies that the reactor is busy; it is unlocked
  * when the reactor is blocked.
  */
  FXMutex& mutex(){ return working; }

  /**
  * Initialize reactor.
  */
  virtual void init();

  /// Is reactor initialized
  FXbool isInitialized() const { return initialized; }

  /**
  * Append handle hnd to watch-list.
  */
  virtual FXbool addHandle(FXInputHandle hnd,FXuint mode=InputRead);

  /**
  * Remove handle hnd from watch-list.
  */
  virtual FXbool remHandle(FXInputHandle hnd,FXuint mode=InputRead);

  /**
  * Check if handle hnd is being watched.
  */
  FXbool hasHandle(FXInputHandle hnd,FXuint mode=InputRead);

  /**
  * Append signal to signal-set observed by the reactor.
  */
  virtual FXbool addSignal(FXint sig);

  /**
  * Remove signal from signal-set observed by the reactor.
  */
  virtual FXbool remSignal(FXint sig);

  /**
  * Check if handle hnd is in signal-set observed by the reactor.
  */
  FXbool hasSignal(FXint sig);

  /**
  * Reactor has timers scheduled.
  */
  FXbool hasTimers() const { return timers!=NULL; }

  /**
  * Add timer dispatchable.
  */
  FXTimerDispatchable* addTimer(FXTimerDispatchable* timer);

  /** 
  * Remove timer dispatchable.
  */
  FXTimerDispatchable* remTimer(FXTimerDispatchable* timer);

  /**
  * Wait for active handles.
  */
  virtual FXint processActiveHandles(FXTime block=forever,FXuint flags=0);

  /**
  * Dispatch when when handle hnd is signaled with mode.
  */
  virtual FXbool doHandle(FXInputHandle hnd,FXint mode);

  /**
  * Dispatch when timeout expires.
  */
  virtual FXbool doTimeout(FXTime t);

  /**
  * Dispatch when a signal was fired.
  */
  virtual FXbool doSignal(FXint sig);

  /**
  * Dispatch when idle.
  */
  virtual FXbool doIdle();

  /**
  * Exit reactor.
  */
  virtual void exit();

  /**
  * Destroy reactor object.
  */
  virtual ~FXReactor();
  };

}

#endif
