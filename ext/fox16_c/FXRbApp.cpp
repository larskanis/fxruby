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

// Message map
FXDEFMAP(FXRbApp) FXRbAppMap[]={
  FXMAPFUNC(SEL_CHORE,FXRbApp::ID_CHORE_THREADS,FXRbApp::onChoreThreads),
  };

// Class implementation
FXRbIMPLEMENT(FXRbApp,FXApp,FXRbAppMap,ARRAYNUMBER(FXRbAppMap))

// Constructor
FXRbApp::FXRbApp(const FXchar* appname,const FXchar* vendor) : FXApp(appname,vendor),m_bThreadsEnabled(TRUE),sleepTime(100){
  if(m_bThreadsEnabled){
    addChore(this,ID_CHORE_THREADS);
    }
  }


// Constructor that also calls FXApp::init()
FXRbApp* FXRbApp::constructAndInit(const FXchar* appname,const FXchar* vendor){
  int argc=1;
  static char* argv[]={"",0};
  FXRbApp* app=new FXRbApp(appname,vendor);
  app->FXApp::init(argc,argv);
  return app;
  }


// Enable (or disable) threads
void FXRbApp::setThreadsEnabled(FXbool enabled){
  if(enabled){
    if(!m_bThreadsEnabled){
      m_bThreadsEnabled=TRUE;
      addChore(this,ID_CHORE_THREADS);
      }
    }
  else{
    m_bThreadsEnabled=FALSE;
    removeChore(this,ID_CHORE_THREADS);
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


// Process threads
long FXRbApp::onChoreThreads(FXObject*,FXSelector,void*){
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

  // Back to work...
  return 1;
  }


// Destructor
FXRbApp::~FXRbApp(){
  FXTRACE((100,"FXRbApp::~FXRbApp()\n"));
  VALUE myRegistry;
  FXRbDestroyAppSensitiveObjects();
  myRegistry=FXRbGetRubyObj(&(reg()),true);
  if(!NIL_P(myRegistry)){
    DATA_PTR(myRegistry)=0;
    }
  FXRbUnregisterRubyObj(this);
  }

