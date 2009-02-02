/********************************************************************************
*                                                                               *
*                     A p p l i c a t i o n   O b j e c t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2008 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXApp.h 2868 2008-05-30 17:03:51Z lyle $                            *
********************************************************************************/
#ifndef FXAPP_H
#define FXAPP_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {


// Forward declarations
class FXApp;
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
class FXTranslator;
class FXComposeContext;

// Opaque FOX objects
struct FXTimer;
struct FXChore;
struct FXSignal;
struct FXRepaint;
struct FXInput;
struct FXHandles;
struct FXInvocation;



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
  DEF_BLANK_CURSOR,                     /// Blank cursor
  DEF_WAIT_CURSOR                       /// Wait cursor
  };



/// FOX Event
struct FXAPI FXEvent {
  FXuint      type;           /// Event type
  FXuint      time;           /// Time of last event
  FXint       win_x;          /// Window-relative x-coord
  FXint       win_y;          /// Window-relative y-coord
  FXint       root_x;         /// Root x-coord
  FXint       root_y;         /// Root y-coord
  FXint       state;          /// Mouse button and modifier key state
  FXint       code;           /// Button, Keysym, or mode; DDE Source
  FXString    text;           /// Text of keyboard event
  FXint       last_x;         /// Window-relative x-coord of previous mouse location
  FXint       last_y;         /// Window-relative y-coord of previous mouse location
  FXint       click_x;        /// Window-relative x-coord of mouse press
  FXint       click_y;        /// Window-relative y-coord of mouse press
  FXint       rootclick_x;    /// Root-relative x-coord of mouse press
  FXint       rootclick_y;    /// Root-relative y-coord of mouse press
  FXuint      click_time;     /// Time of mouse button press
  FXint       click_button;   /// Mouse button pressed
  FXint       click_count;    /// Click-count
  FXint       values[6];      /// Valuators from space ball
  FXbool      moved;          /// Moved cursor since press
  FXRectangle rect;           /// Rectangle
  FXbool      synthetic;      /// True if synthetic expose event
  FXDragType  target;         /// Target drag type being requested
  };


/**
* The Application object is the central point of a FOX user-interface.
* It manages the event queue, timers, signals, chores, and input sources.
* Each FOX application should have exactly one Application object, which
* is the ultimate owner of the entire widget tree; when the application
* object is deleted, all the widgets and other reachable resources of
* the widget tree are also deleted.
* When the Application is initialized using init(), it parses the
* command line arguments meant for it, and opens the display.
* The run() function is used to run the application; this function
* does not return until the user is ready to quit the application.
* During run(), the application processes events from the various
* windows and dispatches them to the appropriate handlers.
* Finally, a call to exit() terminates the application.
* The Application object also manages a registry of configuration
* data, which is read during init() and written back at the exit();
* thus, all configurations changed by the user normally persist to
* the next invocation of the application.
* Since different organizations and different applications each need
* to keep their own set of configuration data, an application name
* and vendor name can be passed in the Application object's constructor
* to identify a particular application's configuration data.
*/
class FXAPI FXApp : public FXObject {
  FXDECLARE(FXApp)

  // We've got many friends
  friend class FXId;
  friend class FXBitmap;
  friend class FXImage;
  friend class FXIcon;
  friend class FXCursor;
  friend class FXDrawable;
  friend class FXWindow;
  friend class FXShell;
  friend class FXRootWindow;
  friend class FXTopWindow;
  friend class FXMainWindow;
  friend class FXPopup;
  friend class FXFont;
  friend class FXVisual;
  friend class FXGLVisual;
  friend class FXGLContext;
  friend class FXDC;
  friend class FXDCWindow;
  friend class FXDragCorner;
  friend class FXDockHandler;
  friend class FXComposeContext;

private:

  // Platform independent private data
  void            *display;             // Display we're talking to
  const FXchar    *dpy;                 // Initial display guess
  FXHash           hash;                // Window handle hash table
  FXRegistry       registry;            // Application setting registry
  FXWindow        *activeWindow;        // Active toplevel window
  FXWindow        *cursorWindow;        // Window under the cursor
  FXWindow        *mouseGrabWindow;     // Window which grabbed the mouse
  FXWindow        *keyboardGrabWindow;  // Window which grabbed the keyboard
  FXWindow        *keyWindow;           // Window in which keyboard key was pressed
  FXWindow        *selectionWindow;     // Selection window
  FXWindow        *clipboardWindow;     // Clipboard window
  FXWindow        *dropWindow;          // Drop target window
  FXWindow        *dragWindow;          // Drag source window
  FXWindow        *refresher;           // GUI refresher pointer
  FXWindow        *refresherstop;       // GUI refresher end pointer
  FXPopup         *popupWindow;         // Current popup window
  FXRootWindow    *root;                // Root window
  FXVisual        *monoVisual;          // Monochrome visual
  FXVisual        *defaultVisual;       // Default [color] visual
  FXTimer         *timers;              // List of timers, sorted by time
  FXChore         *chores;              // List of chores
  FXRepaint       *repaints;            // Unhandled repaint rectangles
  FXTimer         *timerrecs;           // List of recycled timer records
  FXChore         *chorerecs;           // List of recycled chore records
  FXRepaint       *repaintrecs;         // List of recycled repaint records
  FXInvocation    *invocation;          // Modal loop invocation
  FXSignal        *signals;             // Array of signal records
  FXint            signalreceived;      // Latest signal received
  FXFont          *normalFont;          // Normal font
  FXFont          *stockFont;           // Stock font
  FXMutex          appMutex;            // Application wide mutex
  FXEvent          event;               // Event
  FXuint           stickyMods;          // Sticky modifier state
  FXInput         *inputs;              // Input file descriptors being watched
  FXint            ninputs;             // Number of inputs
  FXHandles       *handles;             // Input handles
  FXint            maxhandle;           // Maximum handle number
  FXuchar         *ddeData;             // DDE array
  FXuint           ddeSize;             // DDE array size
  FXuint           maxcolors;           // Maximum number of colors to allocate
  FXTime           typingSpeed;         // Typing speed
  FXTime           clickSpeed;          // Double click speed
  FXTime           scrollSpeed;         // Scroll speed
  FXTime           scrollDelay;         // Scroll delay
  FXTime           blinkSpeed;          // Cursor blink speed
  FXTime           animSpeed;           // Animation speed
  FXTime           menuPause;           // Menu popup delay
  FXTime           toolTipPause;        // Tooltip popup delay
  FXTime           toolTipTime;         // Tooltip display time
  FXTime           autoHideDelay;       // Cursor autohide delay time
  FXint            dragDelta;           // Minimum distance considered a move
  FXint            wheelLines;          // Scroll by this many lines
  FXint            scrollBarSize;       // Scrollbar size
  FXColor          borderColor;         // Border color
  FXColor          baseColor;           // Background color of GUI controls
  FXColor          hiliteColor;         // Highlight color of GUI controls
  FXColor          shadowColor;         // Shadow color of GUI controls
  FXColor          backColor;           // Background color
  FXColor          foreColor;           // Foreground color
  FXColor          selforeColor;        // Select foreground color
  FXColor          selbackColor;        // Select background color
  FXColor          tipforeColor;        // Tooltip foreground color
  FXColor          tipbackColor;        // Tooltip background color
  FXColor          selMenuTextColor;    // Select foreground color in menus
  FXColor          selMenuBackColor;    // Select background color in menus
  FXCursor        *waitCursor;          // Current wait cursor
  FXuint           waitCount;           // Number of times wait cursor was called
  FXuint           windowCount;         // Number of windows
  FXCursor        *cursor[DEF_WAIT_CURSOR+1];
  FXTranslator    *translator;          // Message translator
  FXint                appArgc;         // Argument count
  const FXchar *const *appArgv;         // Argument vector
  const FXchar    *inputmethod;         // Input method name
  const FXchar    *inputstyle;          // Input method style
  FXbool           initialized;         // Has been initialized

private:
  static FXApp    *app;                 // Application pointer

  // Platform dependent private stuff
#ifdef WIN32

  FXushort         ddeTargets;          // DDE targets atom
  FXushort         ddeAtom;             // DDE Exchange Atom
  FXDragType       ddeDelete;           // DDE Delete Target Atom
  FXDragType      *ddeTypeList;         // DDE drop type list
  FXuint           ddeNumTypes;         // DDE number of drop types
  FXDragAction     ddeAction;           // DDE action
  FXDragAction     ansAction;           // Reply action
  FXDragType      *xselTypeList;        // Selection type list
  FXuint           xselNumTypes;        // Selection number of types on list
  void*            xdndTypes;           // Handle to file mapping object for types list
  FXushort         xdndAware;           // XDND awareness atom
  FXID             xdndSource;          // XDND drag source window
  FXID             xdndTarget;          // XDND drop target window
  FXbool           xdndStatusPending;   // XDND waiting for status feedback
  FXbool           xdndFinishPending;   // XDND waiting for drop-confirmation
  FXbool           xdndStatusReceived;  // XDND received at least one status
  FXbool           xdndFinishSent;      // XDND finish sent
  FXRectangle      xdndRect;            // XDND rectangle bounding target
  FXID             stipples[17];        // Standard stipple bitmaps

#else

private:
  FXID             wmDeleteWindow;      // Catch delete window
  FXID             wmQuitApp;           // Catch quit application
  FXID             wmProtocols;         // Window manager protocols
  FXID             wmMotifHints;        // Motif hints
  FXID             wmTakeFocus;         // Focus explicitly set by app
  FXID             wmState;             // Window state
  FXID             wmNetState;          // Extended Window Manager window state
  FXID             wmNetIconName;       // Extended Window Manager icon name
  FXID             wmNetWindowName;     // Extended Window Manager window name
  FXID             wmNetSupported;      // Extended Window Manager states list
  FXID             wmNetHidden;         // Extended Window Manager hidden
  FXID             wmNetShaded;         // Extended Window Manager shaded
  FXID             wmNetHMaximized;     // Extended Window Manager horizontally maximized
  FXID             wmNetVMaximized;     // Extended Window Manager vertically maximized
  FXID             wmNetFullScreen;     // Extended Window Manager full screen
  FXID             wmNetBelowOthers;    // Extended Window Manager below others
  FXID             wmNetAboveOthers;    // Extended Window Manager above others
  FXID             wmNetNeedAttention;  // Extended Window Manager need attention
  FXID             wmNetMoveResize;     // Extended Window Manager drag corner
  FXID             wmNetRestack;        // Extended Window Manager change stacking order
  FXID             wmNetPing;           // Extended Window Manager ping
  FXID             wmNetWindowType;     // Extended Window Manager window type
  FXID             wmWindowTypes[14];   // Window types
  FXID             wmWindowRole;        // Window Role
  FXID             wmClientLeader;      // Client leader
  FXID             wmClientId;          // Client id
  FXID             embedAtom;           // XEMBED support
  FXID             embedInfoAtom;       // XEMBED info support
  FXID             timestampAtom;       // Server time
  FXID             ddeTargets;          // DDE targets atom
  FXID             ddeAtom;             // DDE exchange atom
  FXID             ddeDelete;           // DDE delete target atom
  FXID             ddeIncr;             // DDE incremental data exchange atom
  FXDragType      *ddeTypeList;         // DDE drop type list
  FXuint           ddeNumTypes;         // DDE number of drop types
  FXDragAction     ddeAction;           // DDE action
  FXDragAction     ansAction;           // Reply action
  FXID             xcbSelection;        // Clipboard selection
  FXDragType      *xcbTypeList;         // Clipboard type list
  FXuint           xcbNumTypes;         // Clipboard number of types on list
  FXDragType      *xselTypeList;        // Selection type list
  FXuint           xselNumTypes;        // Selection number of types on list
  FXDragType      *xdndTypeList;        // XDND type list
  FXuint           xdndNumTypes;        // XDND number of types
  FXID             xdndProxy;           // XDND proxy atom
  FXID             xdndAware;           // XDND awareness atom
  FXID             xdndEnter;           // XDND enter window message
  FXID             xdndLeave;           // XDND leave window message
  FXID             xdndPosition;        // XDND position update message
  FXID             xdndStatus;          // XDND status feedback message
  FXID             xdndDrop;            // XDND drop message
  FXID             xdndFinished;        // XDND finished message
  FXID             xdndSelection;       // XDND selection atom
  FXID             xdndActionMove;      // XDND Move action
  FXID             xdndActionCopy;      // XDND Copy action
  FXID             xdndActionLink;      // XDND Link action
  FXID             xdndActionPrivate;   // XDND Private action
  FXID             xdndTypes;           // XDND types list atom
  FXID             xdndSource;          // XDND drag source window
  FXID             xdndTarget;          // XDND drop target window
  FXID             xdndProxyTarget;     // XDND window to set messages to
  FXbool           xdndStatusPending;   // XDND waiting for status feedback
  FXbool           xdndStatusReceived;  // XDND received at least one status
  FXbool           xdndWantUpdates;     // XDND target wants new positions while in rect
  FXbool           xdndFinishSent;      // XDND finish sent
  FXRectangle      xdndRect;            // XDND rectangle bounding target
  FXint            xrrScreenChange;     // Xrandr ScreenChange event
  FXint            xfxFixesSelection;   // Xfixes selection event
  FXint            xsbBallMotion;       // Space ball motion event
  FXint            xsbButtonPress;      // Space ball button press event
  FXint            xsbButtonRelease;    // Space ball button release event
  FXID             stipples[23];        // Standard stipple patterns
  void            *xsbDevice;           // Space ball input device
  void            *xim;                 // Input method
  FXbool           shmi;                // Use XSHM Image possible
  FXbool           shmp;                // Use XSHM Pixmap possible
  FXbool           synchronize;         // Synchronized

#endif

private:

  // Internal helper functions
  FXApp(const FXApp&);
  FXApp &operator=(const FXApp&);
  static void signalhandler(int sig);
  static void immediatesignalhandler(int sig);
  void leaveWindow(FXWindow *window,FXWindow *ancestor);
  void enterWindow(FXWindow *window,FXWindow *ancestor);
  void selectionSetData(const FXWindow* window,FXDragType type,FXuchar* data,FXuint size);
  void selectionGetData(const FXWindow* window,FXDragType type,FXuchar*& data,FXuint& size);
  void selectionGetTypes(const FXWindow* window,FXDragType*& types,FXuint& numtypes);
  void clipboardSetData(const FXWindow* window,FXDragType type,FXuchar* data,FXuint size);
  void clipboardGetData(const FXWindow* window,FXDragType type,FXuchar*& data,FXuint& size);
  void clipboardGetTypes(const FXWindow* window,FXDragType*& types,FXuint& numtypes);
  void dragdropSetData(const FXWindow* window,FXDragType type,FXuchar* data,FXuint size);
  void dragdropGetData(const FXWindow* window,FXDragType type,FXuchar*& data,FXuint& size);
  void dragdropGetTypes(const FXWindow* window,FXDragType*& types,FXuint& numtypes);
  void openInputDevices();
  void closeInputDevices();
#ifdef WIN32
  static long CALLBACK wndproc(FXID hwnd,unsigned int iMsg,unsigned int wParam,long lParam);
protected:
  virtual long dispatchEvent(FXID hwnd,unsigned int iMsg,unsigned int wParam,long lParam);
#else
  void addRepaint(FXID win,FXint x,FXint y,FXint w,FXint h,FXbool synth=false);
  void removeRepaints(FXID win,FXint x,FXint y,FXint w,FXint h);
  void scrollRepaints(FXID win,FXint dx,FXint dy);
  static void imcreatecallback(void*,FXApp*,void*);
  static void imdestroycallback(void*,FXApp*,void*);
#endif

protected:

  /// Return true if an event arrives within blocking nanoseconds
  virtual FXbool getNextEvent(FXRawEvent& ev,FXTime blocking=forever);

  /// Dispatch raw event
  virtual FXbool dispatchEvent(FXRawEvent& ev);

public:
  long onCmdQuit(FXObject*,FXSelector,void*);
  long onCmdDump(FXObject*,FXSelector,void*);
  long onCmdHover(FXObject*,FXSelector,void*);

public:

  /// Messages applications understand
  enum {
    ID_QUIT=1,    /// Terminate the application normally
    ID_DUMP,      /// Dump the current widget tree
    ID_HOVER,
    ID_LAST
    };

public:

  /// Information
  static const FXuchar copyright[];     /// Copyright notice of library

public:

  /**
  * Construct application object; the name and vendor strings are used
  * as keys into the registry database for this application's settings.
  * Only one single application object can be constructed.
  */
  FXApp(const FXString& name="Application",const FXString& vendor="FoxDefault");

  /// Get application name
  const FXString& getAppName() const { return registry.getAppKey(); }

  /// Get vendor name
  const FXString& getVendorName() const { return registry.getVendorKey(); }

  /// Connection to display; this is called by init()
  FXbool openDisplay(const FXchar* dpyname=NULL);

  /// Close connection to the display
  FXbool closeDisplay();

  /// Return pointer
  void* getDisplay() const { return display; }

  /// Is application initialized
  FXbool isInitialized() const { return initialized; }

  /// Get argument count
  FXint getArgc() const { return appArgc; }

  /// Get argument vector
  const FXchar *const *getArgv() const { return appArgv; }

  /// Return true if input method support
  FXbool hasInputMethod() const;

  /// Get default visual
  FXVisual* getDefaultVisual() const { return defaultVisual; }

  /// Change default visual
  void setDefaultVisual(FXVisual* vis);

  /// Get monochrome visual
  FXVisual* getMonoVisual() const { return monoVisual; }

  /// Get root Window
  FXRootWindow* getRootWindow() const { return root; }

  /// Set root Window
  void setRootWindow(FXRootWindow* rt);

  /// Return window at the end of the focus chain
  FXWindow *getFocusWindow() const;

  /// Get the window under the cursor, if any
  FXWindow *getCursorWindow() const { return cursorWindow; }

  /// Get the active toplevel window, if any
  FXWindow *getActiveWindow() const { return activeWindow; }

  /// Get current popup window, if any
  FXPopup* getPopupWindow() const { return popupWindow; }

  /// Return window currently owning primary selection
  FXWindow* getSelectionWindow() const { return selectionWindow; }

  /// Return window currently owning the clipboard
  FXWindow* getClipboardWindow() const { return clipboardWindow; }

  /// Return drag window if a drag operation is in progress
  FXWindow* getDragWindow() const { return dragWindow; }

  /// Find window from id
  FXWindow* findWindowWithId(FXID xid) const;

  /// Find window from root x,y, starting from given window
  FXWindow* findWindowAt(FXint rx,FXint ry,FXID window=0) const;

  /// Create application's windows
  virtual void create();

  /// Destroy application's windows
  virtual void destroy();

  /// Detach application's windows
  virtual void detach();

  /**
  * Add timeout message to be sent to target object in ns nanoseconds;
  * the timer fires only once after the interval expires.  The void* ptr
  * is user data which will be passed into the void* ptr of the message
  * handler.  If a timer with the same target and message already exists,
  * it will be rescheduled.
  * Note: the smallest interval that one can wait is actually much larger
  * than a nanosecond; on Unix systems, the smallest interval is about 1000 ns,
  * whereas on Windows, it is about 1000000 ns.
  */
  void addTimeout(FXObject* tgt,FXSelector sel,FXTime ns=1000000000,void* ptr=NULL);

  /**
  * Add deadline timeout message to be sent when the due time, expressed in nanoseconds
  * since Epoch (Jan 1, 1970), is reached.  This is the preferred way to schedule regularly
  * occuring events, as the exact time of issue will not suffer increasing errors as with the
  * addTimeout() method.  However, it is important to ensure that the due time is sufficiently far
  * into the future, as otherwise the system may be swamped executing nothing but timeout messages.
  */
  void addDeadline(FXObject* tgt,FXSelector sel,FXTime due=forever,void* ptr=NULL);

  /**
  * Remove timeout identified by tgt and sel.
  */
  void removeTimeout(FXObject* tgt,FXSelector sel);

  /**
  * Return true if given timeout has been set.
  */
  FXbool hasTimeout(FXObject *tgt,FXSelector sel) const;

  /**
  * Return, in nanoseconds, the time remaining until the given timer fires.
  * If the timer is past due, 0 is returned.  If there is no such timer, the constant
  * forever (LLONG_MAX) is returned.
  */
  FXTime remainingTimeout(FXObject *tgt,FXSelector sel);

  /**
  * Add a idle processing message to be sent to target object when
  * the system becomes idle, i.e. there are no events to be processed.
  * The void* ptr is user data which will be passed into the void* ptr
  * of the message handler. If a chore with the same target and message
  * already exists, it will be rescheduled.
  */
  void addChore(FXObject* tgt,FXSelector sel,void *ptr=NULL);

  /**
  * Remove idle processing message identified by tgt and sel.
  */
  void removeChore(FXObject* tgt,FXSelector sel);

  /**
  * Return true if given chore has been set
  */
  FXbool hasChore(FXObject *tgt,FXSelector sel) const;

  /**
  * Add signal processing message to be sent to target object when
  * the signal sig is raised; flags are to be set as per POSIX definitions.
  * When immediate is true, the message will be sent to the target right away;
  * this should be used with extreme care as the application is interrupted
  * at an unknown point in its execution.
  */
  void addSignal(FXint sig,FXObject* tgt,FXSelector sel,FXbool immediate=false,FXuint flags=0);

  /// Remove signal message for signal sig
  void removeSignal(FXint sig);

  /**
  * Add a file descriptor fd to be watched for activity as determined by
  * mode, where mode is a bitwise OR of (INPUT_READ, INPUT_WRITE, INPUT_EXCEPT).
  * A message of type SEL_IO_READ, SEL_IO_WRITE, or SEL_IO_EXCEPT will be sent
  * to the target when the specified activity is detected on the file descriptor;
  * the void* ptr is user data which will be passed into the void* ptr of the
  * mesage handler; often you will want to pass the file descriptor fd itself
  * as the value for ptr so that the message handler knows which file descriptor
  * is involved.
  */
  FXbool addInput(FXObject *tgt,FXSelector sel,FXInputHandle fd,FXuint mode=INPUT_READ,void* ptr=NULL);

  /**
  * Remove input message and target object for the specified file descriptor
  * and mode, which is a bitwise OR of (INPUT_READ, INPUT_WRITE, INPUT_EXCEPT).
  * Omitting the last parameter will delete all the handlers associated with the
  * file descriptor.
  */
  FXbool removeInput(FXInputHandle fd,FXuint mode=INPUT_READ);

  /// Return key state of given key
  FXbool getKeyState(FXuint keysym) const;

  /// Peek to determine if there's an event
  FXbool peekEvent();

  /// Perform one event dispatch; return true if event was dispatched
  FXbool runOneEvent(FXTime blocking=forever);

  /**
  * Run the main application event loop until stop() is called,
  * and return the exit code passed as argument to stop().
  */
  FXint run();

  /**
  * Run an event loop till some flag becomes non-zero, and
  * then return.
  */
  FXint runUntil(FXuint& condition);

  /**
  * Run non-modal event loop while events arrive within blocking nanoseconds.
  * Returns when no new events arrive in this time, and no timers, or chores
  * are outstanding.
  */
  FXint runWhileEvents(FXTime blocking=0);

  /**
  * Run modal event loop while events arrive within blocking nanoseconds.
  * Returns 1 when all events in the queue have been handled, and 0 when
  * the event loop was terminated due to stop() or stopModal().
  * Except for the modal window and its children, user input to all windows
  * is blocked; if the modal window is NULL, all user input is blocked.
  */
  FXint runModalWhileEvents(FXWindow* window=NULL,FXTime blocking=0);

  /**
  * Run modal event loop, blocking keyboard and mouse events to all windows
  * until stopModal is called.
  */
  FXint runModal();

  /**
  * Run a modal event loop for the given window, until stop() or stopModal() is
  * called. Except for the modal window and its children, user input to all
  * windows is blocked; if the modal window is NULL all user input is blocked.
  */
  FXint runModalFor(FXWindow* window);

  /**
  * Run modal while window is shown, or until stop() or stopModal() is called.
  * Except for the modal window and its children, user input to all windows
  * is blocked; if the modal window is NULL all user input is blocked.
  */
  FXint runModalWhileShown(FXWindow* window);

  /**
  * Run popup menu while shown, until stop() or stopModal() is called.
  * Also returns when entering previous cascading popup menu.
  */
  FXint runPopup(FXWindow* window);

  /// True if the window is modal
  FXbool isModal(FXWindow* window) const;

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
  void flush(FXbool sync=false);

  /**
  * Paint all windows marked for repainting.
  * On return all the applications windows have been painted.
  */
  void repaint();

  /**
  * Initialize application.
  * Parses and removes common command line arguments, reads the registry.
  * Finally, if connect is true, it opens the display.
  */
  virtual void init(int& argc,char** argv,FXbool connect=true);

  /**
  * Exit application.
  * Closes the display and writes the registry.
  */
  virtual void exit(FXint code=0);

  /**
  * Return a reference to the registry.  The registry keeps
  * settings and configuration information for an application,
  * which are automatically loaded when the application starts
  * up, and saved when the application terminates.
  */
  FXRegistry& reg(){ return registry; }

  /// Register new DND type
  FXDragType registerDragType(const FXString& name) const;

  /// Get drag type name
  FXString getDragTypeName(FXDragType type) const;

  /// Beep
  void beep();

  /// Return application instance
  static inline FXApp* instance(){ return app; }

  /// Change default font
  void setNormalFont(FXFont* font);

  /// Return default font
  FXFont* getNormalFont() const { return normalFont; }

  /// Begin of wait-cursor block; wait-cursor blocks may be nested.
  void beginWaitCursor();

  /// End of wait-cursor block
  void endWaitCursor();

  /// Change to a new wait cursor
  void setWaitCursor(FXCursor *cur);

  /// Return current wait cursor
  FXCursor* getWaitCursor() const { return waitCursor; }

  /// Obtain a default cursor
  FXCursor* getDefaultCursor(FXDefaultCursor which) const { return cursor[which]; }

  /// Change default cursor
  void setDefaultCursor(FXDefaultCursor which,FXCursor* cur);

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
  FXMutex& mutex(){ return appMutex; }

  /**
  * Change message translator.
  * The new translator will be owned by FXApp.
  */
  void setTranslator(FXTranslator* trans);

  /// Return message translator
  FXTranslator* getTranslator() const { return translator; }

  /// Obtain application-wide timing constants, in nanoseconds
  FXTime getTypingSpeed() const { return typingSpeed; }
  FXTime getClickSpeed() const { return clickSpeed; }
  FXTime getScrollSpeed() const { return scrollSpeed; }
  FXTime getScrollDelay() const { return scrollDelay; }
  FXTime getBlinkSpeed() const { return blinkSpeed; }
  FXTime getAnimSpeed() const { return animSpeed; }
  FXTime getMenuPause() const { return menuPause; }
  FXTime getToolTipPause() const { return toolTipPause; }
  FXTime getToolTipTime() const { return toolTipTime; }
  FXTime getAutoHideDelay() const { return autoHideDelay; }

  /// Change application-wide timing constants, in nanoseconds
  void setTypingSpeed(FXTime speed);
  void setClickSpeed(FXTime speed);
  void setScrollSpeed(FXTime speed);
  void setScrollDelay(FXTime delay);
  void setBlinkSpeed(FXTime speed);
  void setAnimSpeed(FXTime speed);
  void setMenuPause(FXTime pause);
  void setToolTipPause(FXTime pause);
  void setToolTipTime(FXTime time);
  void setAutoHideDelay(FXTime time);

  /// Access drag hysteresis
  void setDragDelta(FXint delta);
  FXint getDragDelta() const { return dragDelta; }

  /// Access mouse wheel scroll lines
  void setWheelLines(FXint lines);
  FXint getWheelLines() const { return wheelLines; }

  /// Access scroll bar slot size
  void setScrollBarSize(FXint size);
  FXint getScrollBarSize() const { return scrollBarSize; }

  /// Obtain default colors
  FXColor getBorderColor() const { return borderColor; }
  FXColor getBaseColor() const { return baseColor; }
  FXColor getHiliteColor() const { return hiliteColor; }
  FXColor getShadowColor() const { return shadowColor; }
  FXColor getBackColor() const { return backColor; }
  FXColor getForeColor() const { return foreColor; }
  FXColor getSelforeColor() const { return selforeColor; }
  FXColor getSelbackColor() const { return selbackColor; }
  FXColor getTipforeColor() const { return tipforeColor; }
  FXColor getTipbackColor() const { return tipbackColor; }
  FXColor getSelMenuTextColor() const { return selMenuTextColor; }
  FXColor getSelMenuBackColor() const { return selMenuBackColor; }

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

  /// Get number of existing windows
  FXuint getWindowCount() const { return windowCount; }

  /// Save
  virtual void save(FXStream& store) const;

  /// Load
  virtual void load(FXStream& store);

  /// Dump widget information
  void dumpWidgets() const;

  /// Destroy the application and all reachable resources
  virtual ~FXApp();
  };

}

#endif
