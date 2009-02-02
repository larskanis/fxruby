/********************************************************************************
*                                                                               *
*                             P i p e   C l a s s                               *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXPipe.h 2343 2006-02-12 20:26:26Z lyle $                             *
********************************************************************************/
#ifndef FXPIPE_H
#define FXFILE_H

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
  FXPipe(FXInputHandle handle,FXuint mode);

  /// Open device with access mode and handle
  virtual bool open(FXInputHandle handle,FXuint mode);

  /// Read block of bytes, returning number of bytes read
  virtual FXival readBlock(void* data,FXival count);

  /// Write block of bytes, returning number of bytes written
  virtual FXival writeBlock(const void* data,FXival count);

  /// Close socket
  virtual bool close();

  /// Create a named pipe
  static bool create(const FXString& file,FXuint perm=FXIO::OwnerReadWrite|FXIO::GroupReadWrite|FXIO::OtherReadWrite);

  /// Destroy
  virtual ~FXPipe();
  };

}

#endif
