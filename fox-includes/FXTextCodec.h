/********************************************************************************
*                                                                               *
*                   U n i c o d e   T e x t   C o d e c                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2006 by L.Johnson & J.van der Zijp.  All Rights Reserved.  *
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
* $Id: FXTextCodec.h 2401 2006-04-27 00:46:49Z lyle $                       *
********************************************************************************/
#ifndef FXTEXTCODEC_H
#define FXTEXTCODEC_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif


namespace FX {


/**
 * Abstract base class for a stateless coder/decoder.
 */
class FXAPI FXTextCodec : public FXObject {
  FXDECLARE_ABSTRACT(FXTextCodec)
public:

  /// Construct text codec
  FXTextCodec(){}


  /// Convert utf8 to single wide character
  static FXint utf2wc(FXwchar& wc,const FXchar* src,FXint nsrc);

  /// Convert utf16 to single wide character
  static FXint utf2wc(FXwchar& wc,const FXnchar* src,FXint nsrc);

  /// Convert utf32 to single wide character
  static FXint utf2wc(FXwchar& wc,const FXwchar* src,FXint nsrc);


  /// Convert single wide character to utf8
  static FXint wc2utf(FXchar* dst,FXint ndst,FXwchar wc);

  /// Convert single wide character to utf16
  static FXint wc2utf(FXnchar* dst,FXint ndst,FXwchar wc);

  /// Convert single wide character to utf32
  static FXint wc2utf(FXwchar* dst,FXint ndst,FXwchar wc);


  /// Count utf8 bytes needed to convert multi-byte characters from src
  virtual FXint mb2utflen(const FXchar* src,FXint nsrc) const;

  /// Count utf8 bytes needed to convert multi-byte characters from src
  FXint mb2utflen(const FXString& src) const;

  /// Convert multi-byte characters from src to utf8 characters at dst
  virtual FXint mb2utf(FXchar* dst,FXint ndst,const FXchar* src,FXint nsrc) const;

  /// Convert multi-byte characters from src to utf8 characters at dst
  FXint mb2utf(FXchar* dst,FXint ndst,const FXchar* src) const;

  /// Convert multi-byte characters from src to utf8 characters at dst
  FXint mb2utf(FXchar* dst,FXint ndst,const FXString& src) const;

  /// Convert multi-byte characters from src to utf8 string
  FXString mb2utf(const FXchar* src,FXint nsrc) const;

  /// Convert multi-byte characters from src to utf8 string
  FXString mb2utf(const FXchar* src) const;

  /// Convert multi-byte string to utf8 string
  FXString mb2utf(const FXString& src) const;

  /// Convert multi-byte characters from src to single wide character
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;



  /// Count multi-byte characters characters needed to convert utf8 from src
  virtual FXint utf2mblen(const FXchar* src,FXint nsrc) const;

  /// Count multi-byte characters characters needed to convert utf8 from src
  virtual FXint utf2mblen(const FXString& src) const;

  /// Convert utf8 characters at src to multi-byte characters at dst
  virtual FXint utf2mb(FXchar* dst,FXint ndst,const FXchar* src,FXint nsrc) const;

  /// Convert utf8 characters at src to multi-byte characters at dst
  FXint utf2mb(FXchar* dst,FXint ndst,const FXchar* src) const;

  /// Convert utf8 characters at src to multi-byte characters at dst
  FXint utf2mb(FXchar* dst,FXint ndst,const FXString& src) const;

  /// Convert utf8 characters at src to multi-byte string
  FXString utf2mb(const FXchar* src,FXint nsrc) const;

  /// Convert utf8 characters at src to multi-byte string
  FXString utf2mb(const FXchar* src) const;

  /// Convert utf8 string to multi-byte string
  FXString utf2mb(const FXString& src) const;

  /// Convert single wide character to multi-byte characters at dst
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;


  /**
  * Return the Management Information Base (MIBenum) for the character set.
  */
  virtual FXint mibEnum() const = 0;

  /**
  * Return name of the codec.
  */
  virtual const FXchar* name() const = 0;

  /**
  * Return the IANA mime name for this codec; this is used for example
  * as "text/utf-8" in drag and drop protocols.
  */
  virtual const FXchar* mimeName() const = 0;

  /**
  * Return NULL-terminated list of aliases for this codec.
  */
  virtual const FXchar* const* aliases() const = 0;

  /// Destruct codec
  virtual ~FXTextCodec(){}
  };

}

#endif
