/********************************************************************************
*                                                                               *
*                     G Z F i l e S t r e a m   C l a s s e s                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2005 by Sander Jansen.   All Rights Reserved.              *
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
* $Id: FXGZFileStream.h 2336 2006-02-04 15:20:33Z lyle $                     *
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
  ZBlock *z;
  int     f;
protected:
  virtual FXuval writeBuffer(FXuval count);
  virtual FXuval readBuffer(FXuval count);
public:

  /// Create GZIP compressed file stream
  FXGZFileStream(const FXObject* cont=NULL);

  /// Open file stream
  bool open(const FXString& filename,FXStreamDirection save_or_load,FXuval size=8192);

  /// Close file stream
  virtual bool close();

  /// Get position
  FXlong position() const { return FXStream::position(); }

  /// Move to position
  virtual bool position(FXlong,FXWhence){ return FALSE; }

  /// Save single items to stream
  FXGZFileStream& operator<<(const FXuchar& v){ FXStream::operator<<(v); return *this; }
  FXGZFileStream& operator<<(const FXchar& v){ FXStream::operator<<(v); return *this; }
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
