/********************************************************************************
*                                                                               *
*                     G Z F i l e S t r e a m   C l a s s e s                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2009 by Sander Jansen.   All Rights Reserved.              *
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
* $Id: FXGZFileStream.h,v 1.15 2009/01/06 13:07:24 fox Exp $                    *
********************************************************************************/
#ifdef HAVE_ZLIB_H
#ifndef FXGZFILESTREAM_H
#define FXGZFILESTREAM_H

#ifndef FXFILESTREAM_H
#include "FXFileStream.h"
#endif


namespace FX {


struct ZBlock;


/// GZIP compressed stream
class FXAPI FXGZFileStream : public FXFileStream {
private:
  ZBlock *gz;
  int     ac;
protected:
  virtual FXuval writeBuffer(FXuval count);
  virtual FXuval readBuffer(FXuval count);
public:

  /// Create GZIP compressed file stream
  FXGZFileStream(const FXObject* cont=NULL);

  /// Create and open GZIP compressed file stream
  FXGZFileStream(const FXString& filename,FXStreamDirection save_or_load=FXStreamLoad,FXuval size=8192UL);

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
  FXGZFileStream& operator<<(const FXuchar& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXchar& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXbool& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXushort& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXshort& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXuint& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXint& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXfloat& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXdouble& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXlong& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXulong& v){ FXStream::operator<<(v); return *this; }

  /// Save arrays of items to stream
  FXGZFileStream& save(const FXuchar* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXchar* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXbool* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXushort* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXshort* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXuint* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXint* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXfloat* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXdouble* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXlong* p,FXuval n){ FXStream::save(p,n); return *this; }
  FXGZFileStream& save(const FXulong* p,FXuval n){ FXStream::save(p,n); return *this; }

  /// Load single items from stream
  FXGZFileStream& operator>>(FXuchar& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXchar& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXbool& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXushort& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXshort& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXuint& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXint& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXfloat& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXdouble& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXlong& v){ FXStream::operator>>(v); return *this; }
  FXGZFileStream& operator>>(FXulong& v){ FXStream::operator>>(v); return *this; }

  /// Load arrays of items from stream
  FXGZFileStream& load(FXuchar* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXchar* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXbool* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXushort* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXshort* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXuint* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXint* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXfloat* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXdouble* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXlong* p,FXuval n){ FXStream::load(p,n); return *this; }
  FXGZFileStream& load(FXulong* p,FXuval n){ FXStream::load(p,n); return *this; }

  /// Save object
  FXGZFileStream& saveObject(const FXObject* v){ FXStream::saveObject(v); return *this; }

  /// Load object
  FXGZFileStream& loadObject(FXObject*& v){ FXStream::loadObject(v); return *this; }

  /// Clean up
  virtual ~FXGZFileStream();
  };

}


#endif
#endif
