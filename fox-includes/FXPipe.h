/********************************************************************************
*                                                                               *
*                             P i p e   C l a s s                               *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXPipe.h 2725 2007-11-16 16:57:54Z lyle $                            *
********************************************************************************/
#ifndef FXPIPE_H
#define FXPIPE_H

#ifndef FXIO_H
#include "FXIO.h"
#endif


////////////////////////////  UNDER DEVELOPMENT  ////////////////////////////////


namespace FX {


/**
* Pipe i/o device.
*/
class FXAPI FXPipe : public FXIO {
private:
  FXPipe(const FXPipe&);
  FXPipe &operator=(const FXPipe&);
public:

  /// Construct socket
  FXPipe(){ }

  /// Construct file and attach existing handle h
  FXPipe(FXInputHandle h,FXuint m);

  /// Open device with access mode and handle
  virtual FXbool open(FXInputHandle h,FXuint m);

  /// Read block of bytes, returning number of bytes read
  virtual FXival readBlock(void* data,FXival count);

  /// Write block of bytes, returning number of bytes written
  virtual FXival writeBlock(const void* data,FXival count);

  /// Close socket
  virtual FXbool close();

  /// Create a named pipe
  static FXbool create(const FXString& file,FXuint perm=FXIO::AllReadWrite);

  /// Destroy
  virtual ~FXPipe();
  };

}

#endif
