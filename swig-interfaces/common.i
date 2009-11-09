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
 * $Id: common.i 2463 2006-07-11 14:02:35Z lyle $
 ***********************************************************************/

%{
#include "FXRbCommon.h"
%}

// Redefine the FXAPI macro to a no-op for SWIG
#ifdef FXAPI
#undef FXAPI
#endif
#define FXAPI

// Redefine the FXDECLARE macro to a no-op for SWIG
#ifdef FXDECLARE
#undef FXDECLARE
#endif
#define FXDECLARE(classname)

%include ruby-typemaps.i
%include markfuncs.i
%include exceptions.i
%include freefuncs.i
%include macros.i
%include handlers.i
