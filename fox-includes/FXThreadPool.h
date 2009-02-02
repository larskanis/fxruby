/********************************************************************************
*                                                                               *
*                             T h r e a d   P o o l                             *
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
* $Id: FXThreadPool.h,v 1.54 2007/07/09 16:02:50 fox Exp $                      *
********************************************************************************/
#ifndef FXTHREADPOOL_H
#define FXTHREADPOOL_H

namespace FX {


class FXWorker;
class FXRunnable;
class FXThreadPool;


/// Worker in the pool
class FXAPI FXWorker : public FXThread {
  friend class FXThreadPool;
private:
  FXCondition     condition;    // Task available
  FXMutex         mutex;        // Task mutex
  FXThreadPool   *pool;         // Backlink to pool
  FXWorker       *next;         // Next free worker
  FXRunnable     *task;         // Task to perform
  volatile FXbool runs;         // Thread runs
private:
  FXWorker(const FXWorker&);
  FXWorker &operator=(const FXWorker&);
public:

  /// Create worker belonging to given pool
  FXWorker(FXThreadPool* ptr,FXRunnable* job=NULL);

  /// Is worker running
  FXbool active();

  /// Return thread pool
  FXThreadPool* getPool() const;

  /// Get task
  FXRunnable* getTask();

  /// Wait for task
  FXRunnable* waitTask();

  /// Set task
  void setTask(FXRunnable* job);

  /// Run worker
  virtual FXint run();

  /// Destructor
  virtual ~FXWorker();
  };


/**
* A Thread Pool manages execution of jobs on a number of worker threads.
* For compute-bound tasks, the amount of parallelism in a program is limited by the
* number of physical processors available; however for I/O-bound tasks, it makes sense
* to create more threads than the number of physical processors, in order to more fully
* utilize available processors.
* The thread pool executes incoming jobs in parallel, assigning each job to the first
* available thread out of a fixed pool of worker threads.
* Fluctuations in work-load can be accomodated by creating a few extra worker threads
* during peak loads, while terminating superfluous worker threads during periods of
* low activity, thus minimizing resources.
* In order to prevent falling behind on incoming jobs, the calling thread can be made
* to block scheduling the next job until a worker thread becomes available to handle
* it.
* When the thread pool is deleted, all worker threads are allowed to complete their
* tasks prior to destroying the thread pool.
* The jobs which are passed to the thread pool are derived from FXRunnable.  In order
* to perform some useful function, a subclass of FXRunnable should overload the run()
* function.  Any exceptions thrown by this function are caught in FXWorker, thus the
* worker thread will remain running despite exceptions thrown by the job object.
*/
class FXAPI FXThreadPool {
  friend class FXWorker;
private:
  FXCondition     condition;    // Waiting list condition
  FXMutex         mutex;        // Waiting list mutex
  FXWorker       *waiters;      // List of free workers
  volatile FXint  maximum;      // Maximum number of workers
  volatile FXint  minimum;      // Minimum number of workers
  volatile FXint  running;      // Running number of workers
  volatile FXint  waiting;      // Waiting number of workers
  volatile FXbool runs;         // Thread pool is running
protected:
  FXRunnable* getTask(FXWorker* wrk);
  void appendWorker(FXWorker* wrk);
  void removeWorker(FXWorker* wrk);
  FXWorker* startWorker(FXRunnable* job);
private:
  FXThreadPool(const FXThreadPool&);
  FXThreadPool &operator=(const FXThreadPool&);
public:

  /**
  * Construct an empty thread pool.
  */
  FXThreadPool();

  /**
  * Construct an thread pool and call start() to initiate
  * the thread pool run.
  */
  FXThreadPool(FXint min,FXint max=32,FXint run=0);

  /// Is pool running
  FXbool active();

  /// Return number of waiting threads
  FXint getWaitingThreads();

  /// Return number of worker threads
  FXint getRunningThreads();

  /// Change minimum number of worker threads
  void setMinimumThreads(FXint n);

  /// Return minimum number of worker threads
  FXint getMinimumThreads();

  /// Change maximum number of worker threads
  void setMaximumThreads(FXint n);

  /// Return maximum number of worker threads
  FXint getMaximumThreads();

  /**
  * Start the thread pool; the number of workers will
  * vary between min and max, depending on work-load.
  * A total of run workers will be started immediately;
  * additional workers will be started on as-needed basis.
  * When the number of available workers exceeds min, any
  * additional workers which finish their assigned job will
  * terminate gracefully so as to minimize the number of
  * inactive threads.
  */
  FXint start(FXint min=1,FXint max=32,FXint run=0);

  /**
  * Wait until all jobs currently in progress have been finished.
  * One should not execute new jobs while waiting.
  */
  FXint wait();

  /**
  * Stop pool.
  * Wait until all workers have terminated gracefully, i.e. until
  * the last job has been completed.
  */
  FXint stop();

  /**
  * Execute job on the next available worker thread.
  * If no worker thread is available, check if the maximum number
  * of worker threads has been reached already.  If less than the maximum
  * number of workers is active, create a new worker and start it on the job.
  * Otherwise, if the flag block=true, wait until a worker finishes its job
  * and start it on the new job; if flag block=false, do not start the job at
  * this time.
  * Return the worker to whom the job was assigned, or NULL if the job could
  * not be started.
  */
  FXWorker* execute(FXRunnable *job,FXbool block=true);

  /**
  * Signal the running workers to terminate, and wait until
  * all jobs have finished.
  */
  virtual ~FXThreadPool();
  };

}

#endif

