/********************************************************************************
*                                                                               *
*                     FOX Definitions, Types, and Macros                        *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: fxdefs.h 2360 2006-03-29 04:10:56Z lyle $                           *
********************************************************************************/
#ifndef FXDEFS_H
#define FXDEFS_H


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

/// Pi
#ifndef PI
#define PI      3.1415926535897932384626433833
#endif

/// Euler constant
#define EULER   2.7182818284590452353602874713

/// Multiplier for degrees to radians
#define DTOR    0.0174532925199432957692369077

/// Multiplier for radians to degrees
#define RTOD    57.295779513082320876798154814


// Path separator
#ifdef WIN32
#define PATHSEP '\\'
#define PATHSEPSTRING "\\"
#define PATHLISTSEP ';'
#define PATHLISTSEPSTRING ";"
#define ISPATHSEP(c) ((c)=='/' || (c)=='\\')
#else
#define PATHSEP '/'
#define PATHSEPSTRING "/"
#define PATHLISTSEP ':'
#define PATHLISTSEPSTRING ":"
#define ISPATHSEP(c) ((c)=='/')
#endif

// End Of Line
#ifdef WIN32
#define ENDLINE "\r\n"
#else
#define ENDLINE "\n"
#endif


// For Windows
#ifdef _DEBUG
#ifndef DEBUG
#define DEBUG
#endif
#endif
#ifdef _NDEBUG
#ifndef NDEBUG
#define NDEBUG
#endif
#endif


// Shared library support
#ifdef WIN32
#define FXLOCAL
#define FXEXPORT __declspec(dllexport)
#define FXIMPORT __declspec(dllimport)
#else
#if defined(__GNUC__) && (__GNUC__ >= 4)
#define FXLOCAL  __attribute__ ((visibility("hidden")))
#define FXEXPORT __attribute__ ((visibility("default")))
#define FXIMPORT
#else
#define FXLOCAL
#define FXEXPORT
#define FXIMPORT
#endif
#endif

// Define FXAPI for DLL builds
#ifdef FOXDLL
#ifdef FOXDLL_EXPORTS
#define FXAPI FXEXPORT
#else
#define FXAPI FXIMPORT
#endif
#else
#define FXAPI
#endif

// Callback
#ifdef WIN32
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif
#endif


// Templates with DLL linkage
#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif

// Checking printf and scanf format strings
#if defined(_CC_GNU_) || defined(__GNUG__) || defined(__GNUC__)
#define FX_PRINTF(fmt,arg) __attribute__((format(printf,fmt,arg)))
#define FX_SCANF(fmt,arg)  __attribute__((format(scanf,fmt,arg)))
#else
#define FX_PRINTF(fmt,arg)
#define FX_SCANF(fmt,arg)
#endif

// Raw event type
#ifndef WIN32
union _XEvent;
#else
struct tagMSG;
#endif


namespace FX {


// FOX System Defined Selector Types
enum FXSelType {
  SEL_NONE,
  SEL_KEYPRESS,                         /// Key pressed
  SEL_KEYRELEASE,                       /// Key released
  SEL_LEFTBUTTONPRESS,                  /// Left mouse button pressed
  SEL_LEFTBUTTONRELEASE,                /// Left mouse button released
  SEL_MIDDLEBUTTONPRESS,                /// Middle mouse button pressed
  SEL_MIDDLEBUTTONRELEASE,              /// Middle mouse button released
  SEL_RIGHTBUTTONPRESS,                 /// Right mouse button pressed
  SEL_RIGHTBUTTONRELEASE,               /// Right mouse button released
  SEL_MOTION,                           /// Mouse motion
  SEL_ENTER,                            /// Mouse entered window
  SEL_LEAVE,                            /// Mouse left window
  SEL_FOCUSIN,                          /// Focus into window
  SEL_FOCUSOUT,                         /// Focus out of window
  SEL_KEYMAP,
  SEL_UNGRABBED,                        /// Lost the grab (Windows)
  SEL_PAINT,                            /// Must repaint window
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
#ifdef __APPLE__
  ALTMASK          = 0x2000,          /// Alt key is down
  METAMASK         = 0x10,            /// Meta key is down
#else
  ALTMASK          = 0x008,           /// Alt key is down
  METAMASK         = 0x040,           /// Meta key is down
#endif
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
class                          FXObject;
class                          FXStream;
class                          FXString;


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
#ifdef WIN32
typedef unsigned int           FXwchar;
#if defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
typedef unsigned short         FXnchar;
#elif defined(__WATCOM_INT64__)
typedef long char FXnchar;
#else
typedef wchar_t                FXnchar;
#endif
#else
typedef wchar_t                FXwchar;
typedef unsigned short         FXnchar;
#endif
#if defined(__LP64__) || defined(_LP64) || (_MIPS_SZLONG == 64) || (__WORDSIZE == 64)
typedef unsigned long          FXulong;
typedef long                   FXlong;
#elif defined(_MSC_VER) || (defined(__BCPLUSPLUS__) && __BORLANDC__ > 0x500) || defined(__WATCOM_INT64__)
typedef unsigned __int64       FXulong;
typedef __int64                FXlong;
#elif defined(__GNUG__) || defined(__GNUC__) || defined(__SUNPRO_CC) || defined(__MWERKS__) || defined(__SC__) || defined(_LONGLONG)
typedef unsigned long long     FXulong;
typedef long long              FXlong;
#else
#error "FXlong and FXulong not defined for this architecture!"
#endif

// Integral types large enough to hold value of a pointer
#if defined(_MSC_VER) && defined(_WIN64)
typedef __int64                FXival;
typedef unsigned __int64       FXuval;
#else
typedef long                   FXival;
typedef unsigned long          FXuval;
#endif


// Handle to something in server
#ifndef WIN32
typedef unsigned long          FXID;
#else
typedef void*                  FXID;
#endif

// Time since January 1, 1970 (UTC)
typedef long                   FXTime;

// Pixel type (could be color index)
typedef unsigned long          FXPixel;

// RGBA pixel value
typedef FXuint                 FXColor;

// Hot key
typedef FXuint                 FXHotKey;

// Drag type
#ifndef WIN32
typedef FXID                   FXDragType;
#else
typedef FXushort               FXDragType;
#endif

// Input source handle type
#ifndef WIN32
typedef FXint                  FXInputHandle;
#else
typedef void*                  FXInputHandle;
#endif

// Raw event type
#ifndef WIN32
typedef _XEvent                FXRawEvent;
#else
typedef tagMSG                 FXRawEvent;
#endif


/**********************************  Macros  ***********************************/


/// Abolute value
#define FXABS(val) (((val)>=0)?(val):-(val))

/// Return the maximum of a or b
#define FXMAX(a,b) (((a)>(b))?(a):(b))

/// Return the minimum of a or b
#define FXMIN(a,b) (((a)>(b))?(b):(a))

/// Return the minimum of x, y and z
#define FXMIN3(x,y,z) ((x)<(y)?FXMIN(x,z):FXMIN(y,z))

/// Return the maximum of x, y and z
#define FXMAX3(x,y,z) ((x)>(y)?FXMAX(x,z):FXMAX(y,z))

/// Return the minimum of x, y, z, and w
#define FXMIN4(x,y,z,w) (FXMIN(FXMIN(x,y),FXMIN(z,w)))

/// Return the maximum of of x, y, z, and w
#define FXMAX4(x,y,z,w) (FXMAX(FXMAX(x,y),FXMAX(z,w)))

/// Return minimum and maximum of a, b
#define FXMINMAX(lo,hi,a,b) ((a)<(b)?((lo)=(a),(hi)=(b)):((lo)=(b),(hi)=(a)))

/// Clamp value x to range [lo..hi]
#define FXCLAMP(lo,x,hi) ((x)<(lo)?(lo):((x)>(hi)?(hi):(x)))

/// Swap a pair of numbers
#define FXSWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))

/// Linear interpolation between a and b, where 0<=f<=1
#define FXLERP(a,b,f) ((a)+((b)-(a))*(f))

/// Offset of member in a structure
#define STRUCTOFFSET(str,member) (((char *)(&(((str *)0)->member)))-((char *)0))

/// Number of elements in a static array
#define ARRAYNUMBER(array) (sizeof(array)/sizeof(array[0]))

/// Container class of a member class
#define CONTAINER(ptr,str,mem) ((str*)(((char*)(ptr))-STRUCTOFFSET(str,mem)))

/// Make int out of two shorts
#define MKUINT(l,h) ((((FX::FXuint)(l))&0xffff) | (((FX::FXuint)(h))<<16))

/// Make selector from message type and message id
#define FXSEL(type,id) ((((FX::FXuint)(id))&0xffff) | (((FX::FXuint)(type))<<16))

/// Get type from selector
#define FXSELTYPE(s) ((FX::FXushort)(((s)>>16)&0xffff))

/// Get ID from selector
#define FXSELID(s) ((FX::FXushort)((s)&0xffff))

/// Reverse bits in byte
#define FXBITREVERSE(b) (((b&0x01)<<7)|((b&0x02)<<5)|((b&0x04)<<3)|((b&0x08)<<1)|((b&0x10)>>1)|((b&0x20)>>3)|((b&0x40)>>5)|((b&0x80)>>7))

/// Test if character c is at the start of a utf8 sequence
#define FXISUTF(c) (((c)&0xC0)!=0x80)


// Definitions for big-endian machines
#if FOX_BIGENDIAN == 1

/// Make RGBA color
#define FXRGBA(r,g,b,a)    (((FX::FXuint)(FX::FXuchar)(r)<<24) | ((FX::FXuint)(FX::FXuchar)(g)<<16) | ((FX::FXuint)(FX::FXuchar)(b)<<8) | ((FX::FXuint)(FX::FXuchar)(a)))

/// Make RGB color
#define FXRGB(r,g,b)       (((FX::FXuint)(FX::FXuchar)(r)<<24) | ((FX::FXuint)(FX::FXuchar)(g)<<16) | ((FX::FXuint)(FX::FXuchar)(b)<<8) | 0x000000ff)

/// Get red value from RGBA color
#define FXREDVAL(rgba)     ((FX::FXuchar)(((rgba)>>24)&0xff))

/// Get green value from RGBA color
#define FXGREENVAL(rgba)   ((FX::FXuchar)(((rgba)>>16)&0xff))

/// Get blue value from RGBA color
#define FXBLUEVAL(rgba)    ((FX::FXuchar)(((rgba)>>8)&0xff))

/// Get alpha value from RGBA color
#define FXALPHAVAL(rgba)   ((FX::FXuchar)((rgba)&0xff))

/// Get component value of RGBA color
#define FXRGBACOMPVAL(rgba,comp) ((FX::FXuchar)(((rgba)>>((3-(comp))<<3))&0xff))

#endif


// Definitions for little-endian machines
#if FOX_BIGENDIAN == 0

/// Make RGBA color
#define FXRGBA(r,g,b,a)    (((FX::FXuint)(FX::FXuchar)(r)) | ((FX::FXuint)(FX::FXuchar)(g)<<8) | ((FX::FXuint)(FX::FXuchar)(b)<<16) | ((FX::FXuint)(FX::FXuchar)(a)<<24))

/// Make RGB color
#define FXRGB(r,g,b)       (((FX::FXuint)(FX::FXuchar)(r)) | ((FX::FXuint)(FX::FXuchar)(g)<<8) | ((FX::FXuint)(FX::FXuchar)(b)<<16) | 0xff000000)

/// Get red value from RGBA color
#define FXREDVAL(rgba)     ((FX::FXuchar)((rgba)&0xff))

/// Get green value from RGBA color
#define FXGREENVAL(rgba)   ((FX::FXuchar)(((rgba)>>8)&0xff))

/// Get blue value from RGBA color
#define FXBLUEVAL(rgba)    ((FX::FXuchar)(((rgba)>>16)&0xff))

/// Get alpha value from RGBA color
#define FXALPHAVAL(rgba)   ((FX::FXuchar)(((rgba)>>24)&0xff))

/// Get component value of RGBA color
#define FXRGBACOMPVAL(rgba,comp) ((FX::FXuchar)(((rgba)>>((comp)<<3))&0xff))

#endif


/**
* FXASSERT() prints out a message when the expression fails,
* and nothing otherwise.  Unlike assert(), FXASSERT() will not
* terminate the execution of the application.
* When compiling your application for release, all assertions
* are compiled out; thus there is no impact on execution speed.
*/
#ifndef NDEBUG
#define FXASSERT(exp) ((exp)?((void)0):(void)FX::fxassert(#exp,__FILE__,__LINE__))
#else
#define FXASSERT(exp) ((void)0)
#endif


/**
* FXTRACE() allows you to trace the execution of your application
* with increasing levels of detail the higher the trace level.
* The trace level is determined by variable fxTraceLevel, which
* may be set from the command line with "-tracelevel <level>".
* When compiling your application for release, all trace statements
* are compiled out, just like FXASSERT.
* A statement like: FXTRACE((10,"The value of x=%d\n",x)) will
* generate output only if fxTraceLevel is set to 11 or greater.
* The default value fxTraceLevel=0 will block all trace outputs.
* Note the double parentheses!
*/
#ifndef NDEBUG
#define FXTRACE(arguments) FX::fxtrace arguments
#else
#define FXTRACE(arguments) ((void)0)
#endif


/**
* Allocate a memory block of no elements of type and store a pointer
* to it into the address pointed to by ptr.
* Return FALSE if size!=0 and allocation fails, TRUE otherwise.
* An allocation of a zero size block returns a NULL pointer.
*/
#define FXMALLOC(ptr,type,no)     (FX::fxmalloc((void **)(ptr),sizeof(type)*(no)))

/**
* Allocate a zero-filled memory block no elements of type and store a pointer
* to it into the address pointed to by ptr.
* Return FALSE if size!=0 and allocation fails, TRUE otherwise.
* An allocation of a zero size block returns a NULL pointer.
*/
#define FXCALLOC(ptr,type,no)     (FX::fxcalloc((void **)(ptr),sizeof(type)*(no)))

/**
* Resize the memory block referred to by the pointer at the address ptr, to a
* hold no elements of type.
* Returns FALSE if size!=0 and reallocation fails, TRUE otherwise.
* If reallocation fails, pointer is left to point to old block; a reallocation
* to a zero size block has the effect of freeing it.
* The ptr argument must be the address where the pointer to the allocated
* block is to be stored.
*/
#define FXRESIZE(ptr,type,no)     (FX::fxresize((void **)(ptr),sizeof(type)*(no)))

/**
* Allocate and initialize memory from another block.
* Return FALSE if size!=0 and source!=NULL and allocation fails, TRUE otherwise.
* An allocation of a zero size block returns a NULL pointer.
* The ptr argument must be the address where the pointer to the allocated
* block is to be stored.
*/
#define FXMEMDUP(ptr,src,type,no) (FX::fxmemdup((void **)(ptr),(const void*)(src),sizeof(type)*(no)))

/**
* Free a block of memory allocated with either FXMALLOC, FXCALLOC, FXRESIZE, or FXMEMDUP.
* It is OK to call free a NULL pointer.  The argument must be the address of the
* pointer to the block to be released.  The pointer is set to NULL to prevent
* any further references to the block after releasing it.
*/
#define FXFREE(ptr)               (FX::fxfree((void **)(ptr)))


/**
* These are some of the ISO C99 standard single-precision transcendental functions.
* On LINUX, specify _GNU_SOURCE or _ISOC99_SOURCE to enable native implementation;
* otherwise, these macros will be used.  Apple OS-X implements fabsf(x), ceilf(x),
* floorf(x), and fmodf(x,y).
* Define FLOAT_MATH_FUNCTIONS if these functions are available in some other
* library you're linking to.
*/
#ifdef __OpenBSD__
#define FLOAT_MATH_FUNCTIONS
#endif
#ifndef FLOAT_MATH_FUNCTIONS
#ifndef __USE_ISOC99
#ifndef __APPLE__
#define fabsf(x)    ((float)fabs((double)(x)))
#define ceilf(x)    ((float)ceil((double)(x)))
#define floorf(x)   ((float)floor((double)(x)))
#define fmodf(x,y)  ((float)fmod((double)(x),(double)(y)))
#endif
#define sqrtf(x)    ((float)sqrt((double)(x)))
#define sinf(x)     ((float)sin((double)(x)))
#define cosf(x)     ((float)cos((double)(x)))
#define tanf(x)     ((float)tan((double)(x)))
#define asinf(x)    ((float)asin((double)(x)))
#define acosf(x)    ((float)acos((double)(x)))
#define atanf(x)    ((float)atan((double)(x)))
#define atan2f(y,x) ((float)atan2((double)(y),(double)(x)))
#define powf(x,y)   ((float)pow((double)(x),(double)(y)))
#define expf(x)     ((float)exp((double)(x)))
#define logf(x)     ((float)log((double)(x)))
#define log10f(x)   ((float)log10((double)(x)))
#endif
#endif


/**********************************  Globals  **********************************/

/// Simple, thread-safe, random number generator
extern FXAPI FXuint fxrandom(FXuint& seed);

/// Allocate memory
extern FXAPI FXint fxmalloc(void** ptr,unsigned long size);

/// Allocate cleaned memory
extern FXAPI FXint fxcalloc(void** ptr,unsigned long size);

/// Resize memory
extern FXAPI FXint fxresize(void** ptr,unsigned long size);

/// Duplicate memory
extern FXAPI FXint fxmemdup(void** ptr,const void* src,unsigned long size);

/// Free memory, resets ptr to NULL afterward
extern FXAPI void fxfree(void** ptr);

/// Error routine
extern FXAPI void fxerror(const char* format,...) FX_PRINTF(1,2) ;

/// Warning routine
extern FXAPI void fxwarning(const char* format,...) FX_PRINTF(1,2) ;

/// Log message to [typically] stderr
extern FXAPI void fxmessage(const char* format,...) FX_PRINTF(1,2) ;

/// Assert failed routine:- usually not called directly but called through FXASSERT
extern FXAPI void fxassert(const char* expression,const char* filename,unsigned int lineno);

/// Trace printout routine:- usually not called directly but called through FXTRACE
extern FXAPI void fxtrace(unsigned int level,const char* format,...) FX_PRINTF(2,3) ;

/// Sleep n microseconds
extern FXAPI void fxsleep(unsigned int n);

/// Match a file name with a pattern
extern FXAPI bool fxfilematch(const char *pattern,const char *string,FXuint flags=(FILEMATCH_NOESCAPE|FILEMATCH_FILE_NAME));

/// Get highlight color
extern FXAPI FXColor makeHiliteColor(FXColor clr);

/// Get shadow color
extern FXAPI FXColor makeShadowColor(FXColor clr);

/// Get process id
extern FXAPI FXint fxgetpid();

/// Convert string of length len to MSDOS; return new string and new length
extern FXAPI bool fxtoDOS(FXchar*& string,FXint& len);

/// Convert string of length len from MSDOS; return new string and new length
extern FXAPI bool fxfromDOS(FXchar*& string,FXint& len);

/// Duplicate string
extern FXAPI FXchar *fxstrdup(const FXchar* str);

/// Calculate a hash value from a string
extern FXAPI FXuint fxstrhash(const FXchar* str);

/// Get RGB value from color name
extern FXAPI FXColor fxcolorfromname(const FXchar* colorname);

/// Get name of (closest) color to RGB
extern FXAPI FXchar* fxnamefromcolor(FXchar *colorname,FXColor color);

/// Convert RGB to HSV
extern FXAPI void fxrgb_to_hsv(FXfloat& h,FXfloat& s,FXfloat& v,FXfloat r,FXfloat g,FXfloat b);

/// Convert HSV to RGB
extern FXAPI void fxhsv_to_rgb(FXfloat& r,FXfloat& g,FXfloat& b,FXfloat h,FXfloat s,FXfloat v);

/// Floating point number classification: 0=OK, +/-1=Inf, +/-2=NaN
extern FXAPI FXint fxieeefloatclass(FXfloat number);
extern FXAPI FXint fxieeedoubleclass(FXdouble number);

/// Convert keysym to unicode character
extern FXAPI FXwchar fxkeysym2ucs(FXwchar sym);

/// Convert unicode character to keysym
extern FXAPI FXwchar fxucs2keysym(FXwchar ucs);

/// Parse geometry, a-la X11 geometry specification
extern FXAPI FXint fxparsegeometry(const FXchar *string,FXint& x,FXint& y,FXint& w,FXint& h);

/// True if executable with given path is a console application
extern FXAPI FXbool fxisconsole(const FXchar *path);

/// Version number that the library has been compiled with
extern FXAPI const FXuchar fxversion[3];

/// Controls tracing level
extern FXAPI unsigned int fxTraceLevel;

/// Return wide character from utf8 string at ptr
extern FXAPI FXwchar wc(const FXchar *ptr);

/// Return wide character from utf16 string at ptr
extern FXAPI FXwchar wc(const FXnchar *ptr);

/// Return number of FXchar's of wide character at ptr
extern FXAPI FXint wclen(const FXchar *ptr);

/// Return number of FXnchar's of narrow character at ptr
extern FXAPI FXint wclen(const FXnchar *ptr);

/// Return start of utf8 character containing position
extern FXAPI FXint wcvalidate(const FXchar* string,FXint pos);

/// Return start of utf16 character containing position
extern FXAPI FXint wcvalidate(const FXnchar *string,FXint pos);

/// Advance to next utf8 character start
extern FXAPI FXint wcinc(const FXchar* string,FXint pos);

/// Advance to next utf16 character start
extern FXAPI FXint wcinc(const FXnchar *string,FXint pos);

/// Retreat to previous utf8 character start
extern FXAPI FXint wcdec(const FXchar* string,FXint pos);

/// Retreat to previous utf16 character start
extern FXAPI FXint wcdec(const FXnchar *string,FXint pos);

/// Length of utf8 representation of wide characters string str of length n
extern FXAPI FXint utfslen(const FXwchar *str,FXint n);

/// Length of utf8 representation of wide character string str
extern FXAPI FXint utfslen(const FXwchar *str);

/// Length of utf8 representation of narrow characters string str of length n
extern FXAPI FXint utfslen(const FXnchar *str,FXint n);

/// Length of utf8 representation of narrow characters string str
extern FXAPI FXint utfslen(const FXnchar *str);

/// Length of wide character representation of utf8 string str of length n
extern FXAPI FXint wcslen(const FXchar *str,FXint n);

/// Length of wide character representation of utf8 string str
extern FXAPI FXint wcslen(const FXchar *str);

/// Length of narrow character representation of utf8 string str of length n
extern FXAPI FXint ncslen(const FXchar *str,FXint n);

/// Length of narrow character representation of utf8 string str
extern FXAPI FXint ncslen(const FXchar *str);

/// Copy utf8 string of length n to wide character string dst
extern FXAPI FXint utf2wcs(FXwchar *dst,const FXchar *src,FXint n);

/// Copy utf8 string to wide character string dst
extern FXAPI FXint utf2wcs(FXwchar *dst,const FXchar *src);

/// Copy utf8 string of length n to narrow character string dst
extern FXAPI FXint utf2ncs(FXnchar *dst,const FXchar *src,FXint n);

/// Copy utf8 string to narrow character string dst
extern FXAPI FXint utf2ncs(FXnchar *dst,const FXchar *src);

/// Copy wide character substring of length n to dst
extern FXAPI FXint wc2utfs(FXchar* dst,const FXwchar *src,FXint n);

/// Copy wide character string to dst
extern FXAPI FXint wc2utfs(FXchar* dst,const FXwchar *src);

/// Copy narrow character substring of length n to dst
extern FXAPI FXint nc2utfs(FXchar* dst,const FXnchar *src,FXint n);

/// Copy narrow character string to dst
extern FXAPI FXint nc2utfs(FXchar* dst,const FXnchar *src);


}

#endif
