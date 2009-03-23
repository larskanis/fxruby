/********************************************************************************
*                                                                               *
*                      B Z F i l e S t r e a m   C l a s s e s                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2009 by Lyle Johnson. All Rights Reserved.                 *
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
* $Id: FXBZFileStream.h,v 1.16 2009/01/06 13:07:22 fox Exp $                    *
********************************************************************************/
#ifdef HAVE_BZ2LIB_H
#ifndef FXBZFILESTREAM_H
#define FXBZFILESTREAM_H

#ifndef FXFILESTREAM_H
#include "FXFileStream.h"
#endif


namespace FX {


struct BZBlock;


/// BZIP2 compressed file stream
class FXAPI FXBZFileStream : public FXFileStream {
private:
  BZBlock *bz;
  int      ac;
protected:
  virtual FXuval writeBuffer(FXuval count);
  virtual FXuval readBuffer(FXuval count);
public:

  /// Create BZIP2 file stream
  FXBZFileStream(const FXObject* cont=NULL);

  /// Create and open BZIP2 file stream
  FXBZFileStream(const FXString& filename,FXStreamDirection save_or_load=FXStreamLoad,FXuval size=8192UL);

  /// Open file stream
  FXbool open(const FXString& filename,FXStreamDirection save_or_load=FXStreamLoad,FXuval size=8192UL);

  /// Flush buffer
  virtual FXbool flush();

  /// Close file stream
  virtual FXbool close();

  /// Get position
  FXlong position() const { return FXStream::position(); }

  /// Move to position
  virtual FXbool position(FXlong,FXWhence){ return false; }

  /// Save single items to stream
  FXBZFileStream& operator<<(const FXuchar& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXchar& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXbool& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXushort& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXshort& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXuint& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXint& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXfloat& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXdouble& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXlong& v){ FXStream::operator<<(v); return *this; }
  FXBZFileStream& operator<<(const FXulong& v){ FXStream::operator<<(v); return *this; }

  /// Save arrays of items to stream
  FXBZFileStream& save(const FXuchar* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXchar* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXbool* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXushort* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXshort* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXuint* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXint* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXfloat* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXdouble* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXlong* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXBZFileStream& save(const FXulong* p,FXuval n){ FXStream::save(p,n); return *this; }

  /// Load single items from stream
  FXBZFileStream& operator>>(FXuchar& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXchar& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXbool& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXushort& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXshort& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXuint& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXint& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXfloat& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXdouble& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXlong& v){ FXStream::operator>>(v); return *this; }
  FXBZFileStream& operator>>(FXulong& v){ FXStream::operator>>(v); return *this; }

  /// Load arrays of items from stream
  FXBZFileStream& load(FXuchar* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXchar* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXbool* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXushort* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXshort* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXuint* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXint* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXfloat* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXdouble* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXlong* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXBZFileStream& load(FXulong* p,FXuval n){ FXStream::load(p,n); return *this; }

  /// Save object
  FXBZFileStream& saveObject(const FXObject* v){ FXStream::saveObject(v); return *this; }

  /// Load object
  FXBZFileStream& loadObject(FXObject*& v){ FXStream::loadObject(v); return *this; }

  /// Clean up
  virtual ~FXBZFileStream();
  };


}

#endif
#endif
