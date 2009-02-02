/********************************************************************************
*                                                                               *
*                      M e m o r y   M a p p e d   F i l e                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMemMap.h 2725 2007-11-16 16:57:54Z lyle $                          *
********************************************************************************/
#ifndef FXMEMMAP_H
#define FXMEMMAP_H


#ifndef FXFILE_H
#include "FXFile.h"
#endif

namespace FX {


/**
* A Memory Map provides a view of a file as an array of memory;
* this allows the file itself to be used as backing for the data
* and very simplified file access results.
* Moreover, mapped files may be shared by processes, resuling
* in far less "real" memory being used than would otherwise be
* the case.
*/
class FXAPI FXMemMap : public FXFile {
private:
  FXInputHandle maphandle;      // Handle for the map
  FXuchar*      mapbase;        // Memory base where it is mapped
  FXlong        mapoffset;      // Offset of the map
  FXlong        mapposition;    // Position in file
  FXival        maplength;      // Length of the map
private:
  FXMemMap(const FXMemMap&);
  FXMemMap &operator=(const FXMemMap&);
public:

  /// Construct a memory map
  FXMemMap();

  /// Open a file, and map a view of it into memory; the offset must be a multiple of the page size
  void* openMap(const FXString& filename,FXlong off=0,FXival len=-1L,FXuint m=FXIO::Reading,FXuint p=FXIO::AllReadWrite);

  /// Open map using existing file handle, and map a view of it into memory
  void* openMap(FXInputHandle h,FXlong off=0,FXival len=-1L,FXuint m=FXIO::Reading);

  /// Map a view of the already open file into memory
  void *map(FXlong off=0,FXival len=-1L);

  /// Return pointer to memory area
  void* base() const { return mapbase; }

  /// Obtain length of the map
  long length() const { return maplength; }

  /// Obtain offset of the map
  long offset() const { return mapoffset; }

  /// Get current file position
  virtual FXlong position() const;

  /// Change file position, returning new position from start
  virtual FXlong position(FXlong off,FXuint from=FXIO::Begin);

  /// Unmap the view of the file
  void* unmap();

  /// Read block of bytes, returning number of bytes read
  virtual FXival readBlock(void* data,FXival count);

  /// Write block of bytes, returning number of bytes written
  virtual FXival writeBlock(const void* data,FXival count);

  /// Flush to disk
  virtual FXbool flush();

  /// Close file, and also the map
  virtual FXbool close();

  /// Destroy the map
  ~FXMemMap();
  };


}

#endif
