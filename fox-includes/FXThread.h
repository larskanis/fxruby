/********************************************************************************
*                                                                               *
*                 M u l i t h r e a d i n g   S u p p o r t                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXThread.h,v 1.82 2009/01/06 13:07:28 fox Exp $                          *
********************************************************************************/
#ifndef FXTHREAD_H
#define FXTHREAD_H

namespace FX {


/// Thread ID type
#ifndef WIN32
typedef unsigned long FXThreadID;
#else
typedef void*         FXThreadID;
#endif


/// Thread-local storage key
typedef FXuint FXThreadStorageKey;


class FXCondition;


/**
* FXMutex provides a mutex which can be used to enforce critical
* sections around updates of data shared by multiple threads.
*/
class FXAPI FXMutex {
  friend class FXCondition;
private:
  volatile FXuval data[24];
private:
  FXMutex(const FXMutex&);
  FXMutex &operator=(const FXMutex&);
public:

  /// Initialize the mutex
  FXMutex(FXbool recursive=false);

  /// Lock the mutex
  void lock();

  /// Return true if succeeded locking the mutex
  FXbool trylock();

  /// Return true if mutex is already locked
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

  /// Return true if succeeded locking the mutex
  FXbool trylock(){ return mtx.trylock(); }

  /// Return true if mutex is already locked
  FXbool locked(){ return mtx.locked(); }

  /// Unlock mutex
  void unlock(){ mtx.unlock(); }

  /// Destroy and unlock associated mutex
  ~FXMutexLock(){ unlock(); }
  };


/**
* FXSpinLock can be used to provide safe access to very small
* critical sections.  It is cheaper than FXMutex, but unlike
* FXMutex, threads which are unable to obtain the lock will
* not block, but spin in a tight loop until the lock can be
* obtained.
*/
class FXAPI FXSpinLock {
private:
  volatile FXuval data[4];
private:
  FXSpinLock(const FXSpinLock&);
  FXSpinLock &operator=(const FXSpinLock&);
public:

  /// Initialize the spinlock
  FXSpinLock();

  /// Lock the mutex
  void lock();

  /// Return true if succeeded locking the spinlock
  FXbool trylock();

  /// Return true if spinlock is already locked
  FXbool locked();

  /// Unlock spinlock
  void unlock();

  /// Delete the spinlock
  ~FXSpinLock();
  };


/**
* A semaphore allows for protection of a resource that can
* be accessed by a fixed number of simultaneous threads.
*/
class FXAPI FXSemaphore {
private:
  volatile FXuval data[16];
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
* A condition allows one or more threads to synchronize
* to an event.  When a thread calls wait, the associated
* mutex is unlocked while the thread is blocked.  When the
* condition becomes signaled, the associated mutex is
* locked and the thread(s) are reawakened.
*/
class FXAPI FXCondition {
private:
  volatile FXuval data[12];
private:
  FXCondition(const FXCondition&);
  FXCondition& operator=(const FXCondition&);
public:

  /// Initialize the condition
  FXCondition();

  /**
  * Wait until condition becomes signalled, using given mutex,
  * which must already have been locked prior to this call.
  * Return true if the wait ended due to the condition being
  * signalled through signal() or broadcast(), and false if the
  * wait was interrupted or some error occurred.
  */
  FXbool wait(FXMutex& mtx);

  /**
  * Wait until condition becomes signalled, using given mutex,
  * which must already have been locked prior to this call.
  * Return true if the wait ended due to the condition being
  * signalled through signal() or broadcast(), and false if the
  * wait timed out, was interrupted, or some other error occurred.
  * The absolute time is specified in nanoseconds since the Epoch
  * (Jan 1, 1970).
  */
  FXbool wait(FXMutex& mtx,FXTime nsec);

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
* A read / write lock allows multiple readers but only a single
* writer.
*/
class FXAPI FXReadWriteLock {
private:
  volatile FXuval data[32];
private:
  FXReadWriteLock(const FXReadWriteLock&);
  FXReadWriteLock &operator=(const FXReadWriteLock&);
public:

  /// Initialize the read/write lock
  FXReadWriteLock();

  /// Acquire read lock for read/write lock
  void readLock();

  /// Try to acquire read lock for read/write lock
  bool tryReadLock();

  /// Unlock read lock
  void readUnlock();

  /// Acquire write lock for read/write mutex
  void writeLock();

  /// Try to acquire write lock for read/write lock
  bool tryWriteLock();

  /// Unlock write mutex
  void writeUnlock();

  /// Delete the read/write lock
  ~FXReadWriteLock();
  };


/**
* FXRunnable represents a generic runnable thing.  It serves primarily
* as a base class for FXThread and tasks in FXThreadPool.
*/
class FXAPI FXRunnable {
private:
  FXRunnable(const FXRunnable&);
  FXRunnable &operator=(const FXRunnable&);
public:

  /// Construct a runnable
  FXRunnable(){}

  /// Subclasses of FXRunnable overload this function to perform actual work
  virtual FXint run() = 0;

  /// Destroy a runnable
  virtual ~FXRunnable(){}
  };


/**
* Automatically generated thread-local storage key.
* This class manages a thread-local storage key, generating
* a new one when constructed, and deleting the storage key when
* destroyed.
* These keys can be used just like FXThreadStorageKey itself by
* virtue of the conversion operator.  Note that no assignment
* or copy-constructors have been defined; thus each instance of
* this class represents a unique thread-local storage key.
*/
class FXAPI FXAutoThreadStorageKey {
private:
  FXThreadStorageKey value;
private:
  FXAutoThreadStorageKey(const FXAutoThreadStorageKey&);
  FXAutoThreadStorageKey &operator=(const FXAutoThreadStorageKey&);
public:

  /// Acquire a unique thread-local storage key
  FXAutoThreadStorageKey();

  /// Return the thread-local storage key
  operator FXThreadStorageKey() const { return value; }

  /// Release thread-local storage key
 ~FXAutoThreadStorageKey();
  };


/**
* FXThread provides system-independent support for threads.
* Subclasses must implement the run() function do implement
* the desired functionality of the thread.
* The storage of the FXThread object is to be managed by the
* calling thread, not by the thread itself.
*/
class FXAPI FXThread : public FXRunnable {
private:
  volatile FXThreadID tid;
  volatile FXbool     busy;
private:
  static FXAutoThreadStorageKey selfKey;
private:
  FXThread(const FXThread&);
  FXThread &operator=(const FXThread&);
#ifdef WIN32
  static unsigned int CALLBACK function(void*);
#else
  static void* function(void*);
#endif
protected:
  static void self(FXThread* t);
public:

  /// Thread priority levels
  enum Priority {
    PriorityError=-1,   /// Failed to get priority
    PriorityDefault,  	/// Default scheduling priority
    PriorityMinimum,    /// Minimum scheduling priority
    PriorityLower,      /// Lower scheduling priority
    PriorityMedium,     /// Medium priority
    PriorityHigher,     /// Higher scheduling priority
    PriorityMaximum     /// Maximum scheduling priority
    };

  /// Thread scheduling policies
  enum Policy {
    PolicyError=-1,     /// Failed to get policy
    PolicyDefault,      /// Default scheduling
    PolicyFifo,         /// First in, first out scheduling
    PolicyRoundRobin 	/// Round-robin scheduling
    };

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
  * Return true if this thread is running.
  */
  FXbool running() const;

  /**
  * Start thread; the thread is started as attached.
  * The thread is given stacksize for its stack; a value of
  * zero for stacksize will give it the default stack size.
  * This invokes the run() function in the context of the new
  * thread.
  */
  FXbool start(unsigned long stacksize=0);

  /**
  * Suspend calling thread until thread is done.  The FXThreadID is
  * reset back to zero.
  */
  FXbool join();

  /**
  * Suspend calling thread until thread is done, and set code to the
  * return value of run() or the argument passed into exit().  The
  * FXThreadID is reset back to zero.
  * If an exception happened in the thread, return -1.
  */
  FXbool join(FXint& code);

  /**
  * Cancel the thread, stopping it immediately, running or not.
  * If the calling thread is this thread, nothing happens.
  * It is probably better to wait until it is finished, in case the
  * thread currently holds mutexes.
  * The FXThreadID is reset back to zero after the thread has been
  * stopped.
  */
  FXbool cancel();

  /**
  * Detach thread, so that a no join() is necessary to harvest the
  * resources of this thread.  The thread continues to run until
  * normal completion.
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
  static FXTime time();

  /**
  * Make the calling thread sleep for a number of nanoseconds.
  */
  static void sleep(FXTime nsec);

  /**
  * Wake at appointed time specified in nanoseconds since Epoch.
  */
  static void wakeat(FXTime nsec);

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
  * Return number of available processors in the system.
  */
  static FXint processors();

  /**
  * Generate new thread local storage key.
  */
  static FXThreadStorageKey createStorageKey();

  /**
  * Dispose of thread local storage key.
  */
  static void deleteStorageKey(FXThreadStorageKey key);

  /**
  * Get thread local storage pointer using key.
  */
  static void* getStorage(FXThreadStorageKey key);

  /**
  * Set thread local storage pointer using key.
  */
  static void setStorage(FXThreadStorageKey key,void* ptr);

  /**
  * Set thread scheduling priority.
  */
  FXbool priority(Priority prio);

  /**
  * Return thread scheduling priority.
  */
  Priority priority() const;

  /**
  * Set thread scheduling policy.
  */
  FXbool policy(Policy plcy);

  /**
  * Get thread scheduling policy.
  */
  Policy policy() const;

  /**
  * Suspend thread; return true if success.
  */
  FXbool suspend();

  /**
  * Resume thread; return true if success.
  */
  FXbool resume();

  /**
  * Destroy the thread immediately, running or not.
  * It is probably better to wait until it is finished, in case
  * the thread currently holds mutexes.
  */
  virtual ~FXThread();
  };

}

#endif

