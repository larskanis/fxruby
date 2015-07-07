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
 * $Id: FXRbApp.h 2927 2008-12-29 19:16:57Z lyle $
 ***********************************************************************/

#ifndef FXRBAPP_H
#define FXRBAPP_H


#define DECLARE_FXAPP_STUBS(cls) \
inline void cls ## _destroy(cls *self){ \
  self->cls::destroy(); \
  } \
inline void cls ## _detach(cls *self){ \
  self->cls::detach(); \
  } \
inline void cls ## _create(cls *self){ \
  self->cls::create(); \
  } \
inline FXint cls ## _run_gvl(cls *self){ \
  return self->cls::run(); \
  } \
inline FXint cls ## _runOneEvent_gvl(cls *self, bool blocking=true){ \
  return self->cls::runOneEvent(blocking); \
  } \
inline FXint cls ## _runUntil_gvl(cls *self, FXuint& condition){ \
  return self->cls::runUntil(condition); \
  } \
inline FXint cls ## _runWhileEvents_gvl(cls *self){ \
  return self->cls::runWhileEvents(); \
  } \
inline FXint cls ## _runModalWhileEvents_gvl(cls *self, FXWindow* window=NULL){ \
  return self->cls::runModalWhileEvents(window); \
  } \
inline FXint cls ## _runModal_gvl(cls *self){ \
  return self->cls::runModal(); \
  } \
inline FXint cls ## _runModalFor_gvl(cls *self, FXWindow* window){ \
  return self->cls::runModalFor(window); \
  } \
inline FXint cls ## _runModalWhileShown_gvl(cls *self, FXWindow* window){ \
  return self->cls::runModalWhileShown(window); \
  } \
inline FXint cls ## _runPopup_gvl(cls *self, FXWindow* owner){ \
  return self->cls::runPopup(owner); \
  } \
static void cls ## _init(cls* self,VALUE ary,bool connect){ \
  int i; \
  char **argv; \
  int argc=static_cast<int>(1+RARRAY_LEN(ary)); \
  if(FXMALLOC(&argv,char*,argc+1)){ \
    argv[0]=const_cast<char *>("foo"); \
    for(i=1;i<argc;i++){ \
      VALUE e=rb_ary_entry(ary,i-1); \
      argv[i]=StringValuePtr(e); \
      } \
    argv[argc]=0; \
    self->cls::init(argc,argv,connect); \
    while(RARRAY_LEN(ary)!=0){ \
      rb_ary_pop(ary); \
      } \
    for(i=1;i<argc;i++){ \
      rb_ary_push(ary,rb_str_new2(argv[i])); \
      } \
    } \
  } \
inline void cls ## _exit(cls *self,FXint code){ \
  self->cls::exit(code); \
  }

/**
 * For C/C++ applications, the argument count (argc) will always be at least
 * one, and the first element of the argument array (argv[0]) will contain
 * the program name. So if you type something like this:
 *
 *     myprogram one two three
 *
 * then argc will be four (4) and argv will contain "myprogram", "one",
 * "two" and "three".
 *
 * For Ruby applications, the size and contents of the argument array (ARGV)
 * just correspond to the application arguments; so if you type something like
 * this:
 *
 *     ruby myprogram.rb one two three
 *
 * then the ARGV will have three elements ("one", "two" and "three").
 */
#define IMPLEMENT_FXAPP_STUBS(cls) \
  void cls::create(){ \
    FXRbCallVoidMethod(this,"create"); \
    } \
  void cls::detach(){ \
    FXRbCallVoidMethod(this,"detach"); \
    } \
  void cls::destroy(){ \
    FXRbCallVoidMethod(this,"destroy"); \
    } \
  void cls::init(int& argc,char** argv,bool connect){ \
    int i; \
    VALUE ary=rb_ary_new(); \
    for(i=1; i<argc; i++){ \
      rb_ary_push(ary,rb_str_new2(argv[i])); \
      } \
    FXRbCallVoidMethod(this,"init",ary,connect); \
    argc=static_cast<int>(RARRAY_LEN(ary)+1); \
    for(i=1; i<argc; i++){ \
      VALUE e=rb_ary_entry(ary,i-1); \
      argv[i]=StringValuePtr(e); \
      } \
    } \
  void cls::exit(FXint code){ \
    FXRbCallVoidMethod(this,"exit",code); \
    }


class FXRbApp : public FXApp {
  FXDECLARE(FXRbApp)
protected:
  FXbool m_bThreadsEnabled;
  FXuint sleepTime;
public:
#ifdef WIN32
  static WSAEVENT interrupt_event;
#else
  static int interrupt_fds[2];
#endif
protected:
  FXRbApp(){}
public:
#include "FXRbObjectVirtuals.h"
#include "FXRbAppVirtuals.h"
public:
  enum {
    ID_CHORE_THREADS=FXApp::ID_LAST,
    ID_LAST
    };
public:
  long onChoreThreads(FXObject*,FXSelector,void*);
  long onChoreThreads_gvlcb(FXObject*,FXSelector,void*);
public:
  // Constructor
  FXRbApp(const FXchar* name,const FXchar* vendor);

  // Construct and call init()
  static FXRbApp* constructAndInit(const FXchar* name,const FXchar* vendor);

  // Enable (or disable) support for multithreaded applications
  void setThreadsEnabled(FXbool enabled);

  // Are threads enabled?
  FXbool threadsEnabled() const { return m_bThreadsEnabled; }

  // Set sleep time (in milliseconds)
  void setSleepTime(FXuint ms);

  // Get sleep time (in milliseconds)
  FXuint getSleepTime() const;

  // Mark dependencies for GC
  static void markfunc(FXApp *app);

  // Destructor
  virtual ~FXRbApp();
  };

long FXRbApp_onChoreThreads_gvlcb(FXRbApp*,FXObject*,FXSelector,void*);

#endif
