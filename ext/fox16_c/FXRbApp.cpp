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
 * $Id: FXRbApp.cpp 2902 2008-12-11 14:09:20Z lyle $
 ***********************************************************************/

#include "FXRbCommon.h"

#if defined(RUBY_1_8)
extern "C" {
#include "rubysig.h" /* For CHECK_INTS */
}
#endif

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h> /* For struct timeval */
#endif

#ifndef WIN32
  #include <unistd.h>
  #include <fcntl.h>
#endif

// Message map
FXDEFMAP(FXRbApp) FXRbAppMap[]={
#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
  FXMAPFUNC(SEL_IO_READ,FXRbApp::ID_CHORE_THREADS,FXRbApp::onChoreThreads),
#else
  FXMAPFUNC(SEL_CHORE,FXRbApp::ID_CHORE_THREADS,FXRbApp::onChoreThreads),
#endif
  };

// Class implementation
FXRbIMPLEMENT(FXRbApp,FXApp,FXRbAppMap,ARRAYNUMBER(FXRbAppMap))

#ifdef WIN32
WSAEVENT FXRbApp::interrupt_event = NULL;
#else
int FXRbApp::interrupt_fds[2] = {-1, -1};
#endif

// Constructor
FXRbApp::FXRbApp(const FXchar* appname,const FXchar* vendor) : FXApp(appname,vendor),m_bThreadsEnabled(FALSE),sleepTime(100){
  setThreadsEnabled(TRUE);
  }


// Constructor that also calls FXApp::init()
FXRbApp* FXRbApp::constructAndInit(const FXchar* appname,const FXchar* vendor){
  int argc=1;
  static char* argv[]={(char*)"",0};
  FXRbApp* app=new FXRbApp(appname,vendor);
  app->FXApp::init(argc,argv);
  return app;
  }


// Enable (or disable) threads
void FXRbApp::setThreadsEnabled(FXbool enabled){
  if(enabled){
    if(!m_bThreadsEnabled){
      m_bThreadsEnabled=TRUE;
#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
#ifdef WIN32
      interrupt_event = CreateEvent(NULL, TRUE, FALSE, NULL);
      addInput(interrupt_event,INPUT_READ,this,ID_CHORE_THREADS);
#else
      pipe(interrupt_fds);
      fcntl(interrupt_fds[0], F_SETFL, O_NONBLOCK);
      addInput(interrupt_fds[0],INPUT_READ,this,ID_CHORE_THREADS);
#endif
#else
      addChore(this,ID_CHORE_THREADS);
#endif
      }
    }
  else{
    m_bThreadsEnabled=FALSE;
#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
#ifdef WIN32
    removeInput(interrupt_event,INPUT_READ);
    CloseHandle(interrupt_event); interrupt_event = NULL;
#else
    removeInput(interrupt_fds[0],INPUT_READ);
    close(interrupt_fds[0]); interrupt_fds[0] = -1;
    close(interrupt_fds[1]); interrupt_fds[1] = -1;
#endif
#else
    removeChore(this,ID_CHORE_THREADS);
#endif
    }
  }


// Set sleep time
void FXRbApp::setSleepTime(FXuint ms){
  sleepTime=ms;
  }


// Get sleep time
FXuint FXRbApp::getSleepTime() const {
  return sleepTime;
  }

long FXRbApp::onChoreThreads(FXObject *obj,FXSelector sel,void *p){
#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
#ifdef WIN32
  ResetEvent(interrupt_event);
#else
  char byte;
  // clear the pipe
  read(interrupt_fds[0], &byte, 1);
#endif
#endif
  return FXRbApp_onChoreThreads(this, obj, sel, p);
  }

long FXRbApp_onChoreThreads_gvlcb(FXRbApp *self,FXObject *obj,FXSelector sel,void *p){
  return self->onChoreThreads_gvlcb(obj, sel, p);
  }

// Process threads
long FXRbApp::onChoreThreads_gvlcb(FXObject*,FXSelector,void*){
#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
#else
  // Pause for 'sleepTime' millseconds
  struct timeval wait;
  wait.tv_sec=0;
  wait.tv_usec=100*sleepTime;

  // Confirm that this thread can be interrupted, then go to sleep
#if defined(RUBY_1_8)
  CHECK_INTS;
  if(!rb_thread_critical)
    rb_thread_wait_for(wait);
#else
  // if(!rb_thread_critical) rb_thread_wait_for(wait);
  rb_thread_wait_for(wait);
#endif /* RUBY_1_8 */

  // Re-register this chore for next time
  addChore(this,ID_CHORE_THREADS);
#endif

  // Back to work...
  return 1;
  }

#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
void fxrb_wakeup_fox(void *){
#ifdef WIN32
  SetEvent(FXRbApp::interrupt_event);
#else
  write(FXRbApp::interrupt_fds[1], "X", 1);
#endif
  }
#endif

// Destructor
FXRbApp::~FXRbApp(){
  FXTRACE((100,"FXRbApp::~FXRbApp()\n"));
  VALUE myRegistry;
  setThreadsEnabled(FALSE);
  FXRbDestroyAppSensitiveObjects();
  myRegistry=FXRbGetRubyObj(&(reg()),true);
  if(!NIL_P(myRegistry)){
    DATA_PTR(myRegistry)=0;
    }
  FXRbUnregisterRubyObj(this);
  }

