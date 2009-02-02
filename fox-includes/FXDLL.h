/********************************************************************************
*                                                                               *
*             D y n a m i c   L i n k   L i b r a r y   S u p p o r t           *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDLL.h 2127 2005-08-07 20:21:35Z lyle $                              *
********************************************************************************/
#ifndef FXDLL_H
#define FXDLL_H

namespace FX {

/**
* Open library with given name, returning handle to the
* library, or NULL if the operation failed.
*/
extern FXAPI void* fxdllOpen(const FXchar *dllname);


/**
* Close library represented by dllhandle.
*/
extern FXAPI void fxdllClose(void* dllhandle);


/**
* Return address of the symbol in the library represented by
* dllhandle, or NULL if the operation failed.
*/
extern FXAPI void* fxdllSymbol(void* dllhandle,const FXchar* dllsymbol);


/**
* Return the string error message when loading dll's.
*/
extern FXAPI FXString fxdllError();


}

#endif

