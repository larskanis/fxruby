/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

/********************************  Definitions  ********************************/

// Truth values
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef MAYBE
#define MAYBE 2
#endif
#ifndef NULL
#define NULL 0
#endif

// FOX System Defined Selector Types 
enum FXSelType {
  SEL_NONE,
  SEL_KEYPRESS,                       // Key
  SEL_KEYRELEASE,            
  SEL_LEFTBUTTONPRESS,                // Buttons
  SEL_LEFTBUTTONRELEASE,     
  SEL_MIDDLEBUTTONPRESS,
  SEL_MIDDLEBUTTONRELEASE,
  SEL_RIGHTBUTTONPRESS,
  SEL_RIGHTBUTTONRELEASE,
  SEL_MOTION,                         // Mouse motion
  SEL_ENTER,
  SEL_LEAVE,
  SEL_FOCUSIN,
  SEL_FOCUSOUT,
  SEL_KEYMAP, 
  SEL_UNGRABBED,                      // Lost the grab (Windows)
  SEL_PAINT,                          // Must repaint window
  SEL_CREATE,                
  SEL_DESTROY,               
  SEL_UNMAP,                            /// Window was hidden
  SEL_MAP,                              /// Window was shown
  SEL_CONFIGURE,                        /// Resize
  SEL_SELECTION_LOST,                   /// Widget lost selection
  SEL_SELECTION_GAINED,                 /// Widget gained selection
  SEL_SELECTION_REQUEST,                /// Inquire selection data
  SEL_RAISED,                           /// Window to top of stack
  SEL_LOWERED,                          /// Window to bottom of stack
  SEL_CLOSE,                            /// Close window
  SEL_DELETE,                           /// Delete window
  SEL_MINIMIZE,                         /// Iconified
  SEL_RESTORE,                          /// No longer iconified or maximized
  SEL_MAXIMIZE,                         /// Maximized
  SEL_UPDATE,                           /// GUI update
  SEL_COMMAND,                          /// GUI command
  SEL_CLICKED,                          /// Clicked
  SEL_DOUBLECLICKED,                    /// Double-clicked
  SEL_TRIPLECLICKED,                    /// Triple-clicked
  SEL_MOUSEWHEEL,                       /// Mouse wheel
  SEL_CHANGED,                          /// GUI has changed
  SEL_VERIFY,                           /// Verify change
  SEL_DESELECTED,                       /// Deselected
  SEL_SELECTED,                         /// Selected
  SEL_INSERTED,                         /// Inserted
  SEL_REPLACED,                         /// Replaced
  SEL_DELETED,                          /// Deleted
  SEL_OPENED,                           /// Opened
  SEL_CLOSED,                           /// Closed
  SEL_EXPANDED,                         /// Expanded
  SEL_COLLAPSED,                        /// Collapsed
  SEL_BEGINDRAG,                        /// Start a drag
  SEL_ENDDRAG,                          /// End a drag
  SEL_DRAGGED,                          /// Dragged
  SEL_LASSOED,                          /// Lassoed
  SEL_TIMEOUT,                          /// Timeout occurred
  SEL_SIGNAL,                           /// Signal received
  SEL_CLIPBOARD_LOST,                   /// Widget lost clipboard
  SEL_CLIPBOARD_GAINED,                 /// Widget gained clipboard
  SEL_CLIPBOARD_REQUEST,                /// Inquire clipboard data
  SEL_CHORE,                            /// Background chore
  SEL_FOCUS_SELF,                       /// Focus on widget itself
  SEL_FOCUS_RIGHT,                      /// Focus moved right
  SEL_FOCUS_LEFT,                       /// Focus moved left
  SEL_FOCUS_DOWN,                       /// Focus moved down
  SEL_FOCUS_UP,                         /// Focus moved up
  SEL_FOCUS_NEXT,                       /// Focus moved to next widget
  SEL_FOCUS_PREV,                       /// Focus moved to previous widget
  SEL_DND_ENTER,                        /// Drag action entering potential drop target
  SEL_DND_LEAVE,                        /// Drag action leaving potential drop target
  SEL_DND_DROP,                         /// Drop on drop target
  SEL_DND_MOTION,                       /// Drag position changed over potential drop target
  SEL_DND_REQUEST,                      /// Inquire drag and drop data
  SEL_IO_READ,                          /// Read activity on a pipe
  SEL_IO_WRITE,                         /// Write activity on a pipe
  SEL_IO_EXCEPT,                        /// Except activity on a pipe
  SEL_PICKED,                           /// Picked some location
  SEL_QUERY_TIP,                        /// Message inquiring about tooltip
  SEL_QUERY_HELP,                       /// Message inquiring about statusline help
  SEL_DOCKED,                           /// Toolbar docked
  SEL_FLOATED,                          /// Toolbar floated
  SEL_SESSION_NOTIFY,                   /// Session is about to close
  SEL_SESSION_CLOSED,                   /// Session is closed
  SEL_LAST
  };


/// FOX Keyboard and Button states
enum {
  SHIFTMASK        = 0x001,           /// Shift key is down
  CAPSLOCKMASK     = 0x002,           /// Caps Lock key is down
  CONTROLMASK      = 0x004,           /// Ctrl key is down
  ALTMASK          = 0x008,           /// Alt key is down
  METAMASK         = 0x040,           /// Meta key is down
  NUMLOCKMASK      = 0x010,           /// Num Lock key is down
  SCROLLLOCKMASK   = 0x0E0,           /// Scroll Lock key is down (seems to vary)
  LEFTBUTTONMASK   = 0x100,           /// Left mouse button is down
  MIDDLEBUTTONMASK = 0x200,           /// Middle mouse button is down
  RIGHTBUTTONMASK  = 0x400            /// Right mouse button is down
  };


/// FOX Mouse buttons
enum {
  LEFTBUTTON       = 1,
  MIDDLEBUTTON     = 2,
  RIGHTBUTTON      = 3
  };


/// FOX window crossing modes
enum {
  CROSSINGNORMAL,		     /// Normal crossing event
  CROSSINGGRAB,			     /// Crossing due to mouse grab
  CROSSINGUNGRAB		     /// Crossing due to mouse ungrab
  };


/// FOX window visibility modes
enum {
  VISIBILITYTOTAL,
  VISIBILITYPARTIAL,
  VISIBILITYNONE
  };


/// Options for fxfilematch
enum {
  FILEMATCH_FILE_NAME   = 1,        /// No wildcard can ever match `/'
  FILEMATCH_NOESCAPE    = 2,        /// Backslashes don't quote special chars
  FILEMATCH_PERIOD      = 4,        /// Leading `.' is matched only explicitly
  FILEMATCH_LEADING_DIR = 8,        /// Ignore `/...' after a match
  FILEMATCH_CASEFOLD    = 16        /// Compare without regard to case
  };


/// Drag and drop actions
enum FXDragAction {
  DRAG_REJECT  = 0,                 /// Reject all drop actions
  DRAG_ACCEPT  = 1,                 /// Accept any drop action
  DRAG_COPY    = 2,                 /// Copy
  DRAG_MOVE    = 3,                 /// Move
  DRAG_LINK    = 4,                 /// Link
  DRAG_PRIVATE = 5                  /// Private
  };
  

/// Origin of data
enum FXDNDOrigin {
  FROM_SELECTION  = 0,              /// Primary selection
  FROM_CLIPBOARD  = 1,              /// Clipboard
  FROM_DRAGNDROP  = 2               /// Drag and drop source
  };
  

/// Exponent display
enum FXExponent {
  EXP_NEVER=FALSE,                  /// Never use exponential notation
  EXP_ALWAYS=TRUE,                  /// Always use exponential notation
  EXP_AUTO=MAYBE                    /// Use exponential notation if needed
  };

  
/// Search modes for search/replace dialogs
enum {
  SEARCH_FORWARD      = 0,    /// Search forward (default)
  SEARCH_BACKWARD     = 1,    /// Search backward
  SEARCH_NOWRAP       = 0,    /// Don't wrap (default)
  SEARCH_WRAP         = 2,    /// Wrap around to start
  SEARCH_EXACT        = 0,    /// Exact match (default)
  SEARCH_IGNORECASE   = 4,    /// Ignore case
  SEARCH_REGEX        = 8,    /// Regular expression match
  SEARCH_PREFIX       = 16    /// Prefix of subject string
  };
  
  
/*********************************  Typedefs  **********************************/


// Forward declarations
class FXObject;
class FXStream;

// Streamable types; these are fixed size!
typedef char                   FXchar;
typedef unsigned char          FXuchar;
typedef FXuchar                FXbool;
typedef unsigned short         FXushort;
typedef short                  FXshort;
typedef unsigned int           FXuint;
typedef int                    FXint;
typedef float                  FXfloat;
typedef double                 FXdouble;
typedef FXObject              *FXObjectPtr;
typedef unsigned long          FXuval;
typedef unsigned int           FXwchar;

// Time since January 1, 1970 (UTC)
typedef long                   FXTime;

// Pixel type (could be color index)
typedef unsigned long          FXPixel;

// RGBA pixel value
typedef FXuint                 FXColor;

// Hot key
typedef FXuint                 FXHotKey;

// Drag type
typedef unsigned int            FXDragType;

// Input source handle type (see ruby-typemaps.i)
typedef FXint                  FXInputHandle;


/**********************************  Macros  ***********************************/

%{
static FXuint _MKUINT(FXushort l,FXushort h){
  return MKUINT(l,h);
  }

static FXuint _FXSEL(FXushort type,FXushort id){
  return FXSEL(type,id);
  }
 
static FXushort _FXSELTYPE(FXuint s){
  return FXSELTYPE(s);
  }

static FXushort _FXSELID(FXuint s){
  return FXSELID(s);
  }
%}

/// Make int out of two shorts 
%name(MKUINT) FXuint _MKUINT(FXushort l,FXushort h);

/// Make selector from message type and message id
%name(FXSEL) FXuint _FXSEL(FXushort type,FXushort id);

/// Get type from selector
%name(FXSELTYPE) FXushort _FXSELTYPE(FXuint s);

/// Get ID from selector
%name(FXSELID) FXushort _FXSELID(FXuint s);

// The order in memory is [R G B A] matches that in FXColor
%{
static FXuint _FXRGB(FXuchar r,FXuchar g,FXuchar b){
  return FXRGB(r,g,b);
  }

static FXuint _FXRGBA(FXuchar r,FXuchar g,FXuchar b,FXuchar a){
  return FXRGBA(r,g,b,a);
  }

static FXuchar _FXREDVAL(FXuint rgba){
  return FXREDVAL(rgba);
  }

static FXuchar _FXGREENVAL(FXuint rgba){
  return FXGREENVAL(rgba);
  }

static FXuchar _FXBLUEVAL(FXuint rgba){
  return FXBLUEVAL(rgba);
  }

static FXuchar _FXALPHAVAL(FXuint rgba){
  return FXALPHAVAL(rgba);
  }

static FXuchar _FXRGBACOMPVAL(FXuint rgba,FXuchar comp){
  return FXRGBACOMPVAL(rgba,comp);
  }
%}

/// Make RGB color
%name(FXRGB) FXuint _FXRGB(FXuchar r,FXuchar g,FXuchar b);

/// Make RGBA color
%name(FXRGBA) FXuint _FXRGBA(FXuchar r,FXuchar g,FXuchar b,FXuchar a);

/// Get red value from RGBA color
%name(FXREDVAL) FXuchar _FXREDVAL(FXuint rgba);

/// Get green value from RGBA color
%name(FXGREENVAL) FXuchar _FXGREENVAL(FXuint rgba);

/// Get blue value from RGBA color
%name(FXBLUEVAL) FXuchar _FXBLUEVAL(FXuint rgba);

/// Get alpha value from RGBA color
%name(FXALPHAVAL) FXuchar _FXALPHAVAL(FXuint rgba);

/// Get component value of RGBA color
%name(FXRGBACOMPVAL) FXuchar _FXRGBACOMPVAL(FXuint rgba,FXuchar comp);

/**********************************  Globals  **********************************/


/// Sleep n microseconds
void fxsleep(unsigned int n);

/// Match a file name with a pattern
FXint fxfilematch(const char *pattern,const char *string,FXuint flags=(FILEMATCH_NOESCAPE|FILEMATCH_FILE_NAME));

/// Get highlight color
FXColor makeHiliteColor(FXColor clr);

/// Get shadow color
FXColor makeShadowColor(FXColor clr);

/// Get RGB value from color name
FXColor fxcolorfromname(const FXchar* colorname);

%inline %{
  /// Get name of (closest) color to RGB
  FXchar* fxnamefromcolor(FXColor color){
    static FXchar colorname[128]; // should be large enough, but still a buffer overflow risk!
    return fxnamefromcolor(colorname,color);
    }
%}

%inline %{
/// Convert RGB to HSV
VALUE fxrgb_to_hsv(FXfloat r,FXfloat g,FXfloat b){
  FXfloat h,s,v;
  fxrgb_to_hsv(h,s,v,r,g,b);
  VALUE ary=rb_ary_new();
  rb_ary_push(ary,rb_float_new(h));
  rb_ary_push(ary,rb_float_new(s));
  rb_ary_push(ary,rb_float_new(v));
  return ary;
  }

/// Convert HSV to RGB
VALUE fxhsv_to_rgb(FXfloat h,FXfloat s,FXfloat v){
  FXfloat r,g,b;
  fxhsv_to_rgb(r,g,b,h,s,v);
  VALUE ary=rb_ary_new();
  rb_ary_push(ary,rb_float_new(r));
  rb_ary_push(ary,rb_float_new(g));
  rb_ary_push(ary,rb_float_new(b));
  return ary;
  }
%}

/// Parse geometry, a-la X11 geometry specification
%{
VALUE fxparsegeometry(const FXchar *string){
  FXint x,y,w,h;
  FXint result=fxparsegeometry(string,x,y,w,h);
  VALUE ary=rb_ary_new();
  rb_ary_push(ary,INT2NUM(result));
  rb_ary_push(ary,INT2NUM(x));
  rb_ary_push(ary,INT2NUM(y));
  rb_ary_push(ary,INT2NUM(w));
  rb_ary_push(ary,INT2NUM(h));
  return ary;
  }
%}

/// True if executable with given path is a console application
FXbool fxisconsole(const FXchar *path);

%{
/// Version number that the library has been compiled with
VALUE _fxversion(){
  FXString version=FXStringFormat("%d.%d.%d",fxversion[0],fxversion[1],fxversion[2]);
  return rb_str_new2(version.text());
  }
%}

%name(fxversion) VALUE _fxversion();

/// Controls tracing level
unsigned int fxTraceLevel;

