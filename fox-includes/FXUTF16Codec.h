/********************************************************************************
*                                                                               *
*                      U T F - 1 6  T e x t   C o d e c                         *
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
* $Id: FXUTF16Codec.h 2401 2006-04-27 00:46:49Z lyle $                       *
********************************************************************************/
#ifndef FXUTF16CODEC_H
#define FXUTF16CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif


namespace FX {

/// Codec for UTF-16BE
class FXAPI FXUTF16BECodec : public FXTextCodec {
  FXDECLARE(FXUTF16BECodec)
public:
  FXUTF16BECodec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual FXint mibEnum() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXUTF16BECodec(){}
  };


/// Codec for UTF-16LE
class FXAPI FXUTF16LECodec : public FXTextCodec {
  FXDECLARE(FXUTF16LECodec)
public:
  FXUTF16LECodec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual FXint mibEnum() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXUTF16LECodec(){}
  };


/// Codec for UTF-16
class FXAPI FXUTF16Codec : public FXTextCodec {
  FXDECLARE(FXUTF16Codec)
public:
  FXUTF16Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint mb2utflen(const FXchar* src,FXint nsrc) const;
  virtual FXint mb2utf(FXchar* dst,FXint ndst,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint utf2mblen(const FXchar* src,FXint nsrc) const;
  virtual FXint utf2mb(FXchar* dst,FXint ndst,const FXchar* src,FXint nsrc) const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual FXint mibEnum() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXUTF16Codec(){}
  };

}

#endif

