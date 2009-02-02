/********************************************************************************
*                                                                               *
*              F O X   P r i v a t e   I n c l u d e   F i l e s                *
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
* $Id: xincs.h 2343 2006-02-12 20:26:26Z lyle $                             *
********************************************************************************/
#ifndef XINCS_H
#define XINCS_H


////////////////////  DO NOT INCLUDE THIS PRIVATE HEADER FILE  //////////////////

// Thread safe
#ifndef _POSIX_PTHREAD_SEMANTICS
#define _POSIX_PTHREAD_SEMANTICS
#endif

// GNU extras if we can get them
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

// Use 64-bit files
#ifndef WIN32
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#endif
#endif

// Basic includes
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <locale.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef WIN32

#include <grp.h>
#include <pwd.h>
#include <sys/ioctl.h>
#ifdef HAVE_SYS_FILIO_H         // Get FIONREAD on Solaris
#include <sys/filio.h>
#endif
#else

#include <io.h>                 // For _access()
#if defined(_MSC_VER) || defined(__WATCOMC__)		// Microsoft Visual C++ or Watcom C++
#include <direct.h>
#define stat _stat
#define lstat _stat
#define getcwd _getcwd
#define mkdir _mkdir
#define access _access
#define vsnprintf _vsnprintf
#define execl _execl
#define execlp _execlp
#define execle _execle
#define execv _execv
#define execve _execve
#define execvp _execvp
#define strdup _strdup
#define alloca _alloca
#endif
#ifdef __BORLANDC__	        // Borland C++ Builder
#include <dir.h>
#if __BORLANDC__ <= 0x0530      // C++ Builder 3.0
#define vsnprintf(a, b, c, d) vsprintf(a, c, d)
#endif
#define lstat stat
#endif
#ifdef __MINGW32__              // GCC MingW32
#include <direct.h>
#define vsnprintf _vsnprintf
#endif
#ifdef __SC__                   // Digital Mars C++ Compiler
#include <direct.h>
#include <io.h>                 // For _access()
#define vsnprintf _vsnprintf
#endif

#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif
#ifdef TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#ifdef HAVE_SYS_SELECT_H
#if (!defined(__MINGW32__)) && (!defined(hpux))
#include <sys/select.h>
#endif
#endif
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#define NAMLEN(dirent) strlen((dirent)->d_name)
#else
#define dirent direct
#define NAMLEN(dirent) (dirent)->d_namlen
#ifdef HAVE_SYS_NDIR_H
#include <sys/ndir.h>
#endif
#ifdef HAVE_SYS_DIR_H
#include <sys/dir.h>
#endif
#ifdef HAVE_NDIR_H
#include <ndir.h>
#endif
#endif
#ifdef HAVE_XSHM_H
#include <sys/ipc.h>
#include <sys/shm.h>
#endif
#ifdef HAVE_MMAP
#include <sys/mman.h>
#endif


// For thread-safe readdir_r, we sometimes need extra
// space above and beyond the space for dirent itself
#ifdef HAVE_DIRENT_H
#ifndef WIN32
struct fxdirent : public dirent {
  char buffer[256];
  };
#endif
#endif


// MS-Windows
#ifdef WIN32
#ifndef STRICT
#define STRICT
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#ifndef __CYGWIN__
#include <winsock2.h>
#endif
#include <commctrl.h>           // For _TrackMouseEvent
#include <shellapi.h>

// X windows includes
#else

#include <X11/X.h>
#define XRegisterIMInstantiateCallback broken_XRegisterIMInstantiateCallback
#define XUnregisterIMInstantiateCallback broken_XUnregisterIMInstantiateCallback
#define XSetIMValues broken_XSetIMValues
#include <X11/Xlib.h>
#undef XRegisterIMInstantiateCallback
#undef XUnregisterIMInstantiateCallback
#undef XSetIMValues
#include <X11/Xcms.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#ifdef HUMMINGBIRD
#include <X11/XlibXtra.h>
#endif
#ifdef HAVE_XSHM_H
#include <X11/extensions/XShm.h>
#endif
#ifdef HAVE_XCURSOR_H
#include <X11/Xcursor/Xcursor.h>
#endif
#ifdef HAVE_XFT_H
#include <X11/Xft/Xft.h>
#endif
#ifdef HAVE_XSHAPE_H
#include <X11/extensions/shape.h>
#endif
#ifdef HAVE_XRANDR_H
#include <X11/extensions/Xrandr.h>
#endif

#ifndef NO_XIM
#ifndef XlibSpecificationRelease        // Not defined until X11R5
#define NO_XIM
#elif XlibSpecificationRelease < 6      // Need at least Xlib X11R6
#define NO_XIM
#endif
#endif

#ifndef NO_XIM
extern "C" Bool XRegisterIMInstantiateCallback(Display*,struct _XrmHashBucketRec*,char*,char*,XIMProc,XPointer);
extern "C" Bool XUnregisterIMInstantiateCallback(Display*,struct _XrmHashBucketRec*,char*,char*,XIMProc,XPointer);
extern "C" char *XSetIMValues(XIM,...);
#endif

#endif




// OpenGL includes
#ifdef HAVE_GL_H
#ifndef SUN_OGL_NO_VERTEX_MACROS
#define SUN_OGL_NO_VERTEX_MACROS
#endif
#ifndef HPOGL_SUPPRESS_FAST_API
#define HPOGL_SUPPRESS_FAST_API
#endif
#include <GL/gl.h>
#ifndef WIN32
#include <GL/glx.h>
#endif
#endif
#ifndef GLAPIENTRY
#define GLAPIENTRY
#endif
#ifndef GLAPI
#define GLAPI
#endif
#ifdef HAVE_GLU_H
#include <GL/glu.h>
#endif

// Maximum path length
#ifndef MAXPATHLEN
#if defined(PATH_MAX)
#define MAXPATHLEN   PATH_MAX
#elif defined(_MAX_PATH)
#define MAXPATHLEN   _MAX_PATH
#elif defined(MAX_PATH)
#define MAXPATHLEN   MAX_PATH
#else
#define MAXPATHLEN   1024
#endif
#endif

// Modes for access(filename,mode) on Windows
#ifdef WIN32
#ifndef R_OK
#define R_OK 4
#endif
#ifndef W_OK
#define W_OK 2
#endif
#ifndef X_OK
#define X_OK 1
#endif
#ifndef F_OK
#define F_OK 0
#endif
#endif

// File open modes on Windows
#ifdef WIN32
#if defined(_MSC_VER)
#define O_APPEND _O_APPEND
#define O_CREAT  _O_CREAT
#define O_EXCL   _O_EXCL
#define O_RDONLY _O_RDONLY
#define O_RDWR   _O_RDWR
#define O_TRUNC  _O_TRUNC
#define O_WRONLY _O_WRONLY
#define O_BINARY _O_BINARY
#endif
#endif

// Some systems don't have it
#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

// Printer stuff
#ifdef WIN32
#include <winspool.h>
#endif


// Wheel support (OS >= W98, OS>=NT4.0)
#ifdef WIN32

// Missing wheel message id's
#ifndef SPI_GETWHEELSCROLLLINES
#define SPI_GETWHEELSCROLLLINES   104
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL             0x020A
#endif

// GetSystemMetrics parameters missing in header files
#ifndef SM_XVIRTUALSCREEN
#define SM_XVIRTUALSCREEN       76
#endif
#ifndef SM_YVIRTUALSCREEN
#define SM_YVIRTUALSCREEN       77
#endif
#ifndef SM_CXVIRTUALSCREEN
#define SM_CXVIRTUALSCREEN      78
#endif
#ifndef SM_CYVIRTUALSCREEN
#define SM_CYVIRTUALSCREEN      79
#endif
#ifndef SM_CMONITORS
#define SM_CMONITORS            80
#endif
#ifndef SM_SAMEDISPLAYFORMAT
#define SM_SAMEDISPLAYFORMAT    81
#endif

// Missing in CYGWIN
#ifndef IMAGE_SUBSYSTEM_NATIVE_WINDOWS
#define IMAGE_SUBSYSTEM_NATIVE_WINDOWS 8
#endif
#ifndef IMAGE_SUBSYSTEM_WINDOWS_CE_GUI
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI 9
#endif
#endif


// IBM VisualAge for C++ 3.5
#if defined(__IBMCPP__) && defined(WIN32)
#include <direct.h>
#include <io.h>         // for _access()
#define _mkdir(x) mkdir((char *)(x))
#define _vsnprintf(a, b, c, d) vsprintf(a, c, d)
#define ICON_SMALL      0
#define ICON_BIG        1
#define bool            int

// This declarations come from Microsoft SDK
#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002
#define TME_QUERY       0x40000000
#define TME_CANCEL      0x80000000
#define HOVER_DEFAULT   0xFFFFFFFF
#define WM_MOUSEHOVER   0x02A1
#define WM_MOUSELEAVE   0x02A3

typedef struct tagTRACKMOUSEEVENT {
    DWORD cbSize;
    DWORD dwFlags;
    HWND  hwndTrack;
    DWORD dwHoverTime;
} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;

WINUSERAPI
BOOL
WINAPI
TrackMouseEvent(
    IN OUT LPTRACKMOUSEEVENT lpEventTrack);

#ifdef __GL_H__
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
WINGDIAPI void APIENTRY glPolygonOffset (GLfloat factor,GLfloat units);
#endif

#endif

#endif
