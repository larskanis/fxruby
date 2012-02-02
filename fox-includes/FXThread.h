/********************************************************************************
*                                                                               *
*                 M u l i t h r e a d i n g   S u p p o r t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXThread.h 2360 2006-03-29 04:10:56Z lyle $                          *
********************************************************************************/
#ifndef FXTHREAD_H
#define FXTHREAD_H

namespace FX {


// Thread ID type
#ifndef WIN32
typedef unsigned long FXThreadID;
#else
typedef void*         FXThreadID;
#endif


class FXCondition;


/**
* FXMutex provides a mutex which can be used to enforce critical
* sections around updates of data shared by multiple threads.
*/
class FXAPI FXMutex {
  friend class FXCondition;
private:
  FXuval data[24];
private:
  FXMutex(const FXMutex&);
  FXMutex &operator=(const FXMutex&);
public:

  /// Initialize the mutex
  FXMutex(FXbool recursive=FALSE);

  /// Lock the mutex
  void lock();

  /// Return TRUE if succeeded locking the mutex
  FXbool trylock();

  /// Return TRUE if mutex is already locked
  FXbool locked();

  /// Unlock mutex
  void unlock();

  /// Delete the mutex
  ~FXMutex();
  };


/**
* An easy way to establish a correspondence between a C++ scope
* and a critical section is to simply declare an FXMutexLock
* at the beginning of the scope.
* The mutex will be automatically released when the scope is
* left (either by natural means or by means of an exception.
*/
class FXAPI FXMutexLock {
private:
  FXMutex& mtx;
private:
  FXMutexLock();
  FXMutexLock(const FXMutexLock&);
  FXMutexLock& operator=(const FXMutexLock&);
public:

  /// Construct & lock associated mutex
  FXMutexLock(FXMutex& m):mtx(m){ lock(); }

  /// Return reference to associated mutex
  FXMutex& mutex(){ return mtx; }

  /// Lock mutex
  void lock(){ mtx.lock(); }

  /// Return TRUE if succeeded locking the mutex
  FXbool trylock(){ return mtx.trylock(); }

  /// Return TRUE if mutex is already locked
  FXbool locked(){ return mtx.locked(); }

  /// Unlock mutex
  void unlock(){ mtx.unlock(); }

  /// Destroy and unlock associated mutex
  ~FXMutexLock(){ unlock(); }
  };


/**
* A condition allows one or more threads to synchronize
* to an event.  When a thread calls wait, the associated
* mutex is unlocked while the thread is blocked.  When the
* condition becomes signaled, the associated mutex is
* locked and the thread(s) are reawakened.
*/
class FXAPI FXCondition {
private:
  FXuval data[12];
private:
  FXCondition(const FXCondition&);
  FXCondition& operator=(const FXCondition&);
public:

  /// Initialize the condition
  FXCondition();

  /**
  * Wait until condition becomes signalled, using given mutex,
  * which must already have been locked prior to this call.
  */
  void wait(FXMutex& mtx);

  /**
  * Wait until condition becomes signalled, using given mutex,
  * which must already have been locked prior to this call.
  * Returns TRUE if successful, FALSE if timeout occurred.
  * Note that the wait-time is specified in nanoseconds
  * since the Epoch (Jan 1, 1970).
  */
  FXbool wait(FXMutex& mtx,FXlong nsec);

  /**
  * Wake or unblock a single blocked thread
  */
  void signal();

  /**
  * Wake or unblock all blocked threads
  */
  void broadcast();

  /// Delete the condition
  ~FXCondition();
  };


/**
* A semaphore allows for protection of a resource that can
* be accessed by a fixed number of simultaneous threads.
*/
class FXSemaphore {
private:
  FXuval data[16];
private:
  FXSemaphore(const FXSemaphore&);
  FXSemaphore& operator=(const FXSemaphore&);
public:

  /// Initialize semaphore with given count
  FXSemaphore(FXint initial=1);

  /// Decrement semaphore
  void wait();

  /// Non-blocking semaphore decrement; return true if locked
  FXbool trywait();

  /// Increment semaphore
  void post();

  /// Delete semaphore
  ~FXSemaphore();
  };


/**
* FXThread provides system-independent support for threads.
* Subclasses must implement the run() function do implement
* the desired functionality of the thread.
* The storage of the FXThread object is to be managed by the
* calling thread, not by the thread itself.
*/
class FXAPI FXThread {
private:
  FXThreadID tid;
private:
  FXThread(const FXThread&);
  FXThread &operator=(const FXThread&);
#ifdef WIN32
  static unsigned int CALLBACK execute(void*);
#else
  static void* execute(void*);
#endif
protected:

  /**
  * All threads execute by deriving the run method of FXThread.
  * If an uncaught exception was thrown, this function returns -1.
  */
  virtual FXint run() = 0;

public:

  /// Initialize thread object.
  FXThread();

  /**
  * Return handle of this thread object.
  * This handle is valid in the context of the thread which
  * called start().
  */
  FXThreadID id() const;

  /**
  * Return TRUE if this thread is running.
  */
  FXbool running() const;

  /**
  * Start thread; the thread is started as attached.
  * The thread is given stacksize for its stack; a value of
  * zero for stacksize will give it the default stack size.
  */
  FXbool start(unsigned long stacksize=0);

  /**
  * Suspend calling thread until thread is done.
  */
  FXbool join();

  /**
  * Suspend calling thread until thread is done, and set code to the
  * return value of run() or the argument passed into exit().
  * If an exception happened in the thread, return -1.
  */
  FXbool join(FXint& code);

  /**
  * Cancel the thread, stopping it immediately, running or not.
  * If the calling thread is this thread, nothing happens.
  * It is probably better to wait until it is finished, in case the
  * thread currently holds mutexes.
  */
  FXbool cancel();

  /**
  * Detach thread, so that a no join() is necessary to harvest the
  * resources of this thread.
  */
  FXbool detach();

  /**
  * Exit the calling thread.
  * No destructors are invoked for objects on thread's stack;
  * to invoke destructors, throw an exception instead.
  */
  static void exit(FXint code=0);

  /**
  * Make the thread yield its time quantum.
  */
  static void yield();

  /**
  * Return time in nanoseconds since Epoch (Jan 1, 1970).
  */
  static FXlong time();

  /**
  * Make the calling thread sleep for a number of nanoseconds.
  */
  static void sleep(FXlong nsec);

  /**
  * Wake at appointed time specified in nanoseconds since Epoch.
  */
  static void wakeat(FXlong nsec);

  /**
  * Return pointer to the FXThread instance associated
  * with the calling thread; it returns NULL for the main
  * thread and all threads not created by FOX.
  */
  static FXThread* self();

  /**
  * Return thread id of calling thread.
  */
  static FXThreadID current();

  /**
  * Set thread priority.
  */
  void priority(FXint prio);

  /**
  * Return thread priority.
  */
  FXint priority();

  /**
  * Destroy the thread immediately, running or not.
  * It is probably better to wait until it is finished, in case
  * the thread currently holds mutexes.
  */
  virtual ~FXThread();
  };

}

#endif

