/********************************************************************************
*                                                                               *
*                      M e m o r y   M a p p e d   F i l e                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXMemMap.h 2136 2005-08-14 00:36:26Z lyle $                           *
********************************************************************************/
#ifndef FXMEMMAP_H
#define FXMEMMAP_H

namespace FX {


/**
* A Memory Map provides a view of a file as an array of memory;
* this allows the file itself to be used as backing for the data
* and very simplified file access results.
* Moreover, mapped files may be shared by processes, resuling
* in far less "real" memory being used than would otherwise be
* the case.
*/
class FXAPI FXMemMap {
private:
  void*         mapbase;        // Memory base where it is mapped
  long          maplength;      // Length of the map
  long          mapoffset;      // Offset of the map
  FXInputHandle handle;         // Handle for the map
  FXInputHandle file;           // Handle for the file
private:
  FXMemMap(const FXMemMap&);
  FXMemMap &operator=(const FXMemMap&);
public:

  /// Memory map access modes
  enum {
    NONE  = 0,          /// Map is inaccessible
    READ  = 1,          /// Readable
    WRITE = 2,          /// Writable
    EXEC  = 4,          /// Executable (where supported)
    TRUNC = 8           /// Truncate file to 0
    };

  /// Share mode
  enum {
    PRIV = 0,        /// Private
    SHAR = 1         /// Shared
    };

public:

  /// Construct a memory map
  FXMemMap();

  /// Map a view of the file; the offset must be a multiple of the page size
  void* mapFile(const FXString& filename,long off=0,long len=-1L,FXuint access=READ,FXuint share=PRIV);

  /// Unmap the view of the file
  void* unmap();

  /// Synchronize disk
  void sync();

  /// Return pointer to memory area
  void* base() const { return mapbase; }

  /// Obtain length of the map
  long length() const { return maplength; }

  /// Obtain offset of the map
  long offset() const { return mapoffset; }

  /// Destroy the map
  ~FXMemMap();
  };


}

#endif
