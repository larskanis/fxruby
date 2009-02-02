/********************************************************************************
*                                                                               *
*                       U R L   M a n i p u l a t i o n                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXURL.h 2769 2007-11-19 19:10:43Z lyle $                             *
********************************************************************************/
#ifndef FXURL_H
#define FXURL_H

namespace FX {

namespace FXURL {

/// Return URL of filename
extern FXAPI FXString fileToURL(const FXString& file);

/// Return filename from URL, empty if url is not a local file
extern FXAPI FXString fileFromURL(const FXString& url);

/// Decode url string
extern FXAPI FXString decode(const FXString& url);

/// Encode url string
extern FXAPI FXString encode(const FXString& url);

}

}

#endif
