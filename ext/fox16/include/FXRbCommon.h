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
 * $Id: FXRbCommon.h 2797 2007-12-11 21:59:11Z lyle $
 ***********************************************************************/

extern "C" {
#include "ruby.h"
}

/**
 * The Ruby header files for Win32 redefine the symbol "select", which
 * breaks things for the FXGLViewer class (which has a member function
 * named select). This fixes it back.
 */
#ifdef select
#undef select
#endif

#ifdef open
#undef open
#endif

#ifdef close
#undef close
#endif

#ifdef connect
#undef connect
#endif

#ifdef read
#undef read
#endif

#ifdef sleep
#undef sleep
#endif

#ifdef write
#undef write
#endif

#ifdef __CYGWIN__
#define OpenFile WIN32_OpenFile
#endif

#include "fx.h"
#include "FXMemoryStream.h" // FIXME: Should be in fx.h!
#include "fx3d.h"

#ifdef __CYGWIN__
#undef OpenFile
#endif

#include "FXColorList.h"
#include "FXTranslator.h"

#include "FXCURCursor.h"
#include "FXICOIcon.h"
#include "FXICOImage.h"
#include "FXJPGIcon.h"
#include "FXJPGImage.h"
#include "FXPNGIcon.h"
#include "FXPNGImage.h"
#include "FXRGBIcon.h"
#include "FXRGBImage.h"
#include "FXTIFIcon.h"
#include "FXTIFImage.h"
#include "FXXBMIcon.h" // FIXME: Should be listed in fx.h
#ifdef WITH_FXSCINTILLA
#include "Scintilla.h"
#include "FXScintilla.h"
#endif
#include "FXRuby.h"

#ifndef NUM2USHRT
#define NUM2USHRT(n) ((0 <= NUM2UINT(n) && NUM2UINT(n) <= USHRT_MAX) ? (unsigned short) NUM2UINT(n) : (rb_raise(rb_eArgError, "integer %d out of range of `unsigned short'", NUM2UINT(n)), (short)0))
#endif
