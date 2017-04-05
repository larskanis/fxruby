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

// Forward declarations
class FXWindow;
class FXIcon;
class FXBitmap;
class FXCursor;
class FXRootWindow;
class FXMainWindow;
class FXPopup;
class FXFont;
class FXDC;
class FXDCWindow;
class FXVisual;
class FXGLVisual;
class FXGLContext;


/// File input modes for addInput
enum FXInputMode {
  INPUT_NONE   = 0,                 /// Inactive
  INPUT_READ   = 1,                 /// Read input fd
  INPUT_WRITE  = 2,                 /// Write input fd
  INPUT_EXCEPT = 4                  /// Except input fd
  };


/// All ways of being modal
enum FXModality {
  MODAL_FOR_NONE,                 /// Non modal event loop (dispatch normally)
  MODAL_FOR_WINDOW,               /// Modal dialog (beep if outside of modal dialog)
  MODAL_FOR_POPUP                 /// Modal for popup (always dispatch to popup)
  };


/// Default cursors provided by the application
enum FXDefaultCursor {
  DEF_ARROW_CURSOR,                     /// Arrow cursor
  DEF_RARROW_CURSOR,                    /// Reverse arrow cursor
  DEF_TEXT_CURSOR,                      /// Text cursor
  DEF_HSPLIT_CURSOR,                    /// Horizontal split cursor
  DEF_VSPLIT_CURSOR,                    /// Vertical split cursor
  DEF_XSPLIT_CURSOR,                    /// Cross split cursor
  DEF_SWATCH_CURSOR,                    /// Color swatch drag cursor
  DEF_MOVE_CURSOR,                      /// Move cursor
  DEF_DRAGH_CURSOR,                     /// Resize horizontal edge
  DEF_DRAGV_CURSOR,                     /// Resize vertical edge
  DEF_DRAGTL_CURSOR,                    /// Resize upper-leftcorner
  DEF_DRAGBR_CURSOR=DEF_DRAGTL_CURSOR,  /// Resize bottom-right corner
  DEF_DRAGTR_CURSOR,                    /// Resize upper-right corner
  DEF_DRAGBL_CURSOR=DEF_DRAGTR_CURSOR,  /// Resize bottom-left corner
  DEF_DNDSTOP_CURSOR,                   /// Drag and drop stop
  DEF_DNDCOPY_CURSOR,                   /// Drag and drop copy
  DEF_DNDMOVE_CURSOR,                   /// Drag and drop move
  DEF_DNDLINK_CURSOR,                   /// Drag and drop link
  DEF_CROSSHAIR_CURSOR,                 /// Cross hair cursor
  DEF_CORNERNE_CURSOR,                  /// North-east cursor
  DEF_CORNERNW_CURSOR,                  /// North-west cursor
  DEF_CORNERSE_CURSOR,                  /// South-east cursor
  DEF_CORNERSW_CURSOR,                  /// South-west cursor
  DEF_HELP_CURSOR,                      /// Help arrow cursor
  DEF_HAND_CURSOR,                      /// Hand cursor
  DEF_ROTATE_CURSOR,                    /// Rotate cursor
  DEF_WAIT_CURSOR                       /// Wait cursor
  };


/// FOX Event
struct FXEvent {
  FXEvent();
  FXuint      type;           /// Event type
  FXuint      time;           /// Time of last event
  FXint       win_x;          /// Window-relative x-coord
  FXint       win_y;          /// Window-relative y-coord
  FXint       root_x;         /// Root x-coord
  FXint       root_y;         /// Root y-coord
  FXint       state;          /// Keyboard/Modifier state
  FXint       code;           /// Button, Keysym, or mode; DDE Source
  FXString    text;           /// Text of keyboard event
  FXint       last_x;         /// Window-relative x-coord of previous mouse location
  FXint       last_y;         /// Window-relative y-coord of previous mouse location
  FXint       click_x;        /// Window-relative x-coord of mouse press
  FXint       click_y;        /// Window-relative y-coord of mouse press
  FXint       rootclick_x;    /// Root-relative x-coord of mouse press
  FXint       rootclick_y;    /// Root-relative y-coord of mouse press
  FXuint      click_time;     /// Time of mouse button press
  FXuint      click_button;   /// Mouse button pressed
  FXint       click_count;    /// Click-count
  FXbool      moved;          /// Moved cursor since press
  FXRectangle rect;           /// Rectangle
  FXbool      synthetic;      /// True if synthetic expose event
  FXDragType  target;         /// Target drag type being requested
  ~FXEvent();
  };


// FXChore is an opaque struct for FOX; this is just a declaration for SWIG
struct FXChore {
  };


// FXTimer is an opaque struct for FOX; this is just a declaration for SWIG
struct FXTimer {
  };

%rename("hasInputMethod?") FXApp::hasInputMethod() const;
%rename("hasChore?") FXApp::hasChore(FXObject *tgt,FXSelector sel) const;
%rename("hasTimeout?") FXApp::hasTimeout(FXObject *tgt,FXSelector sel) const;
%rename("focusWindow") FXApp::getFocusWindow() const;
%rename("activeWindow") FXApp::getActiveWindow() const;
%rename("scrollBarSize") FXApp::getScrollBarSize() const;
%rename("scrollBarSize=") FXApp::setScrollBarSize(FXint);

/// Application Object
class FXApp : public FXObject {
public:
  long onCmdQuit(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDump(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHover(FXObject*,FXSelector,void* PTR_IGNORE);

public:

  // Messages applications understand
  enum {
    ID_QUIT=1,    /// Terminate the application normally
    ID_DUMP,      /// Dump the current widget tree
    ID_HOVER,
    ID_LAST
    };

public:

  %extend {
    // Copyright notice for library
    static VALUE copyright() {
      return to_ruby(FXApp::copyright);
    }
  }

public:

  %extend {
    /**
    * Construct application object; the name and vendor strings are used
    * as keys into the registry database for this application's settings
    */
    FXApp(const FXchar* name="Application",const FXchar* vendor="FoxDefault"){
      if(FXApp::instance()){
        rb_raise(rb_eRuntimeError,"attempted to create more than one FXApp instance");
        return 0;
        }
      else{
        return FXRbApp::constructAndInit(name,vendor);
        }
      }
  }

  /// Get application name
  const FXString& getAppName() const;

  /// Get vendor name
  const FXString& getVendorName() const;

  /// Connection to display; this is called by init()
  bool openDisplay(const FXchar* dpyname=NULL);

  /// Close connection to the display
  bool closeDisplay();

  %extend {
    /// Return pointer to display
    FXuval getDisplay() const {
      return reinterpret_cast<FXuval>(self->getDisplay());
      }
    }

  /// Is application initialized
  bool isInitialized() const;

  /// Get argument count
  FXint getArgc() const;

  /// Get argument vector
  const FXchar *const *getArgv() const; // FIXME

  /// Return true if input method support
  bool hasInputMethod() const;

  /// Get default visual
  FXVisual* getDefaultVisual() const;

  %extend {
    /// Change default visual
    void setDefaultVisual(FXVisual* vis){
      FXASSERT(vis);
      if(vis->isMemberOf(FXMETACLASS(FXRbVisual))){
        dynamic_cast<FXRbVisual*>(vis)->ownedByApp=TRUE;
        }
      else if(vis->isMemberOf(FXMETACLASS(FXRbGLVisual))){
        dynamic_cast<FXRbGLVisual*>(vis)->ownedByApp=TRUE;
        }
      self->setDefaultVisual(vis);
      }
  }

  /// Get monochrome visual
  FXVisual* getMonoVisual() const;

  /// Get root Window
  FXRootWindow* getRootWindow() const;

  /// Set root Window
  void setRootWindow(FXRootWindow* rt);

  /// Return window at the end of the focus chain
  FXWindow *getFocusWindow() const;

  /// Get the window under the cursor, if any
  FXWindow *getCursorWindow() const;

  /// Get the active toplevel window, if any
  FXWindow *getActiveWindow() const;

  /// Get current popup window, if any
  FXPopup* getPopupWindow() const;

  /// Find window from id
  FXWindow* findWindowWithId(FXID xid) const;

  /// Find window from root x,y, starting from given window
  FXWindow* findWindowAt(FXint rx,FXint ry,FXID window=0) const;

  /**
  * Add timeout message to be sent to target object in ms milliseconds;
  * the timer fires only once after the interval expires.  The void* ptr
  * is user data which will be passed into the void* ptr of the message
  * handler.  If a timer with the same target and message already exists,
  * it will be rescheduled.
  */
  void addTimeout(FXObject* tgt,FXSelector sel,FXuint ms=1000,void* ptr=NULL);

  /**
  * Remove timeout identified by tgt and sel.
  */
  void removeTimeout(FXObject* tgt,FXSelector sel);

   /**
   * Return TRUE if given timeout has been set
   */
  bool hasTimeout(FXObject *tgt,FXSelector sel) const;

   /**
  * Return, in ms, the time remaining until the given timer fires.
  * If the timer is past due, 0 is returned.  If there is no such
  * timer, infinity (UINT_MAX) is returned.
  */
  FXuint remainingTimeout(FXObject *tgt,FXSelector sel);

  /**
   * Process any timeouts due at this time.
   */
  void handleTimeouts();

  /**
  * Add a idle processing message to be sent to target object when
  * the system becomes idle, i.e. there are no events to be processed.
  * The void* ptr is user data which will be passed into the void* ptr
  * of the message handler. If a chore with the same target and message
  * already exists, it will be rescheduled.
  */
  void addChore(FXObject* tgt,FXSelector sel,void *ptr=NULL);

  /**
  * Remove idle processing message(s) identified by tgt and sel.
  */
  void removeChore(FXObject* tgt,FXSelector sel);

   /**
  * Return TRUE if given chore has been set
  */
  bool hasChore(FXObject *tgt,FXSelector sel) const;

  %extend {
    /**
    * Add signal processing message to be sent to target object when
    * the signal sig is raised; flags are to be set as per POSIX definitions.
    * When immediate is TRUE, the message will be sent to the target right away;
    * this should be used with extreme care as the application is interrupted
    * at an unknown point in its execution.
    */
    void addSignal(VALUE sigObj,FXObject* tgt,FXSelector sel,FXbool immediate=FALSE,FXuint flags=0){
      const char *s;
      FXint sig;
      switch(TYPE(sigObj)){
        case T_STRING:
          s=StringValuePtr(sigObj);
          sig=FXRbSignalNameToNumber(s);
          if(sig==0) rb_raise(rb_eArgError,"unrecognized signal name `%s'",s);
          break;
        case T_FIXNUM:
          sig=(FXint)NUM2INT(sigObj);
          break;
        default:
          rb_raise(rb_eArgError,"bad signal type %s",rb_class2name(CLASS_OF(sigObj)));
          break;
        }
      self->addSignal(sig,tgt,sel,immediate,flags);
      }

    /// Remove signal message for signal sig
    void removeSignal(VALUE sigObj){
      const char *s;
      FXint sig;
      switch(TYPE(sigObj)){
        case T_STRING:
          s=StringValuePtr(sigObj);
          sig=FXRbSignalNameToNumber(s);
          if(sig==0) rb_raise(rb_eArgError,"unrecognized signal name `%s'",s);
          break;
        case T_FIXNUM:
          sig=(FXint)NUM2INT(sigObj);
          break;
        default:
          rb_raise(rb_eArgError,"bad signal type %s",rb_class2name(CLASS_OF(sigObj)));
          break;
        }
      self->removeSignal(sig);
      }
  }

  %extend {
    /**
    * Add a file descriptor fd to be watched for activity as determined
    * by mode, where mode is a bitwise OR (INPUT_READ, INPUT_WRITE, INPUT_EXCEPT).
    * A message of type SEL_IO_READ, SEL_IO_WRITE, or SEL_IO_EXCEPT will be sent
    * to the target when the specified activity is detected on the file descriptor.
    */
    bool addInput(VALUE obj,FXuint mode,FXObject *tgt,FXSelector sel){
      FXInputHandle fd;
      if(mode&(INPUT_READ|INPUT_EXCEPT)){
        fd=FXRbGetReadFileHandle(obj, mode);
        self->addInput(fd,mode,tgt,sel);
        }
      if(mode&(INPUT_WRITE|INPUT_EXCEPT)){
        fd=FXRbGetWriteFileHandle(obj, mode);
        self->addInput(fd,mode,tgt,sel);
        }
      return true;
      }

    /**
    * Remove input message and target object for the specified file descriptor
    * and mode, which is a bitwise OR of (INPUT_READ, INPUT_WRITE, INPUT_EXCEPT).
    */
    bool removeInput(VALUE obj,FXuint mode){
      FXInputHandle fd;
      if(mode&(INPUT_READ|INPUT_EXCEPT)){
        fd=FXRbGetReadFileHandle(obj, mode);
        self->removeInput(fd,mode);
        FXRbRemoveReadFileHandle(obj, mode);
        }
      if(mode&(INPUT_WRITE|INPUT_EXCEPT)){
        fd=FXRbGetWriteFileHandle(obj, mode);
        self->removeInput(fd,mode);
        FXRbRemoveWriteFileHandle(obj, mode);
        }
      return true;
      }
  }

  /// Return key state
  bool getKeyState(FXuint keysym) const;

  /// Peek to determine if there's an event
  bool peekEvent();

  /// True if the window is modal
  bool isModal(FXWindow* window) const;

  /// Return window of current modal loop
  FXWindow* getModalWindow() const;

  /// Return mode of current modal loop
  FXModality getModality() const;

  /**
  * Terminate the outermost event loop, and all inner modal loops;
  * All more deeper nested event loops will be terminated with code equal
  * to 0, while the outermost event loop will return code equal to value.
  */
  void stop(FXint value=0);

  /**
  * Break out of the matching modal loop, returning code equal to value.
  * All deeper nested event loops are terminated with code equal to 0.
  */
  void stopModal(FXWindow* window,FXint value=0);

  /**
  * Break out of the innermost modal loop, returning code equal to value.
  */
  void stopModal(FXint value=0);

  /// Force GUI refresh
  void forceRefresh();

  /// Schedule a refresh
  void refresh();

  /// Flush pending repaints
  void flush(bool sync=false);

  /**
  * Paint all windows marked for repainting.
  * On return all the applications windows have been painted.
  */
  void repaint();

  /**
   * Return a reference to the registry.  The registry keeps
   * settings and configuration information for an application,
   * which are automatically loaded when the application starts
   * up, and saved when the application terminates.
   */
  FXRegistry& reg();

  /// Register new DND type
  FXDragType registerDragType(const FXString& name) const;

  /// Get drag type name
  FXString getDragTypeName(FXDragType type) const;

  /// Return drag window if a drag operation is in progress
  FXWindow* getDragWindow() const;

  /// Beep
  void beep();

  /// Return application instance
  static inline FXApp* instance();

  %extend {
    /// Change default font
    void setNormalFont(FXFont* font){
      FXASSERT(font);
      if(font->isMemberOf(FXMETACLASS(FXRbFont))){
        dynamic_cast<FXRbFont*>(font)->ownedByApp=TRUE;
	}
      self->setNormalFont(font);
      }
  }

  /// Return default font
  FXFont* getNormalFont() const;

  /// Begin of wait-cursor block; wait-cursor blocks may be nested.
  void beginWaitCursor();

  /// End of wait-cursor block
  void endWaitCursor();

  %extend {
    /// Change to a new wait cursor
    void setWaitCursor(FXCursor *cur){
      FXASSERT(cur);
      if(cur->isMemberOf(FXMETACLASS(FXRbCursor))){
        dynamic_cast<FXRbCursor*>(cur)->ownedByApp=TRUE;
        }
      else if(cur->isMemberOf(FXMETACLASS(FXRbCURCursor))){
        dynamic_cast<FXRbCURCursor*>(cur)->ownedByApp=TRUE;
        }
      else if(cur->isMemberOf(FXMETACLASS(FXRbGIFCursor))){
        dynamic_cast<FXRbGIFCursor*>(cur)->ownedByApp=TRUE;
        }
      self->setWaitCursor(cur);
      }
  }

  /// Return current wait cursor
  FXCursor* getWaitCursor() const;

  /// Obtain a default cursor
  FXCursor* getDefaultCursor(FXDefaultCursor which) const;

  %extend {
    /// Change default cursor
    void setDefaultCursor(FXDefaultCursor which,FXCursor* cur){
      FXASSERT(cur);
      if(cur->isMemberOf(FXMETACLASS(FXRbCursor))){
        dynamic_cast<FXRbCursor*>(cur)->ownedByApp=TRUE;
        }
      else if(cur->isMemberOf(FXMETACLASS(FXRbCURCursor))){
        dynamic_cast<FXRbCURCursor*>(cur)->ownedByApp=TRUE;
        }
      else if(cur->isMemberOf(FXMETACLASS(FXRbGIFCursor))){
        dynamic_cast<FXRbGIFCursor*>(cur)->ownedByApp=TRUE;
        }
      self->setDefaultCursor(which,cur);
      }
  }

  /**
   * Write a window and its children, and all resources reachable from this
   * window, into the stream store.
   */
  FXbool writeWindow(FXStream& store,FXWindow *window);

  %extend {
    /**
     * Read a window and its children from the stream store, and append
     * it under father; note it is initially not created yet.
     */
    FXWindow* readWindow(FXStream& store,FXWindow*& window,FXWindow* father,FXWindow* owner){
      window=0;
      self->readWindow(store,window,father,owner);
      return window;
      }
  }

  /**
  * Return a reference to the application-wide mutex.
  * Normally, the main user interface thread holds this mutex,
  * insuring that no other threads are modifying data during the
  * processing of user interface messages. However, whenever the
  * main user interface thread blocks for messages, it releases
  * this mutex, to allow other threads to modify the same data.
  * When a new message becomes available, the main user interface
  * thread regains the mutex prior to dispatching the message.
  * Other threads should hold this mutex only for short durations,
  * so as to not starve the main user interface thread.
  */
  FXMutex& mutex();

  /**
  * Change message translator.
  * The new translator will be owned by FXApp.
  */
  void setTranslator(FXTranslator* trans);

  /// Return message translator
  FXTranslator* getTranslator() const;

  /// Obtain application-wide settings
  FXuint getTypingSpeed() const;
  FXuint getClickSpeed() const;
  FXuint getScrollSpeed() const;
  FXuint getScrollDelay() const;
  FXuint getBlinkSpeed() const;
  FXuint getAnimSpeed() const;
  FXuint getMenuPause() const;
  FXuint getTooltipPause() const;
  FXuint getTooltipTime() const;
  FXint getDragDelta() const;
  FXint getWheelLines() const;
  FXint getScrollBarSize() const;

  /// Change application-wide settings
  void setTypingSpeed(FXuint speed);
  void setClickSpeed(FXuint speed);
  void setScrollSpeed(FXuint speed);
  void setScrollDelay(FXuint delay);
  void setBlinkSpeed(FXuint speed);
  void setAnimSpeed(FXuint speed);
  void setMenuPause(FXuint pause);
  void setTooltipPause(FXuint pause);
  void setTooltipTime(FXuint time);
  void setDragDelta(FXint delta);
  void setWheelLines(FXint lines);
  void setScrollBarSize(FXint size);

  /// Obtain default colors
  FXColor getBorderColor() const;
  FXColor getBaseColor() const;
  FXColor getHiliteColor() const;
  FXColor getShadowColor() const;
  FXColor getBackColor() const;
  FXColor getForeColor() const;
  FXColor getSelforeColor() const;
  FXColor getSelbackColor() const;
  FXColor getTipforeColor() const;
  FXColor getTipbackColor() const;
  FXColor getSelMenuTextColor() const;
  FXColor getSelMenuBackColor() const;

  /// Change default colors
  void setBorderColor(FXColor color);
  void setBaseColor(FXColor color);
  void setHiliteColor(FXColor color);
  void setShadowColor(FXColor color);
  void setBackColor(FXColor color);
  void setForeColor(FXColor color);
  void setSelforeColor(FXColor color);
  void setSelbackColor(FXColor color);
  void setTipforeColor(FXColor color);
  void setTipbackColor(FXColor color);
  void setSelMenuTextColor(FXColor color);
  void setSelMenuBackColor(FXColor color);

  /// Dump widget information
  void dumpWidgets() const;

  /// Get number of existing windows
  FXuint getWindowCount() const;

  /// Destroy the application and all reachable resources
  virtual ~FXApp();
  };

DECLARE_FXOBJECT_VIRTUALS(FXApp)
DECLARE_FXAPP_VIRTUALS(FXApp)

#ifdef SWIGRUBY

%rename("threadsEnabled=") FXApp::setThreadsEnabled(FXbool);
%rename("threadsEnabled?") FXApp::threadsEnabled() const;

%extend FXApp {
  // Enable (or disable) support for multithreaded applications
  void setThreadsEnabled(FXbool enabled){
    FXASSERT(self->isMemberOf(FXMETACLASS(FXRbApp)));
    dynamic_cast<FXRbApp*>(self)->setThreadsEnabled(enabled);
    }

  // Are threads enabled?
  FXbool threadsEnabled() const {
    FXASSERT(self->isMemberOf(FXMETACLASS(FXRbApp)));
    return dynamic_cast<const FXRbApp*>(self)->threadsEnabled();
    }

  // Set the amount of time to sleep
  void setSleepTime(FXuint sleepTime){
    FXASSERT(self->isMemberOf(FXMETACLASS(FXRbApp)));
    dynamic_cast<FXRbApp*>(self)->setSleepTime(sleepTime);
    }

  // Get the amount of time to sleep
  FXuint getSleepTime() const {
    FXASSERT(self->isMemberOf(FXMETACLASS(FXRbApp)));
    return dynamic_cast<const FXRbApp*>(self)->getSleepTime();
    }
  }

#endif
