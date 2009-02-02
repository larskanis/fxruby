/********************************************************************************
*                                                                               *
*                      U T F - 3 2  T e x t   C o d e c                         *
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
* $Id: FXUTF32Codec.h 2401 2006-04-27 00:46:49Z lyle $                       *
********************************************************************************/
#ifndef FXUTF32CODEC_H
#define FXUTF32CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif


namespace FX {


/// Codec for UTF-32BE
class FXAPI FXUTF32BECodec : public FXTextCodec {
  FXDECLARE(FXUTF32BECodec)
public:
  FXUTF32BECodec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual FXint mibEnum() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXUTF32BECodec(){}
  };


/// Codec for UTF-32LE
class FXAPI FXUTF32LECodec : public FXTextCodec {
  FXDECLARE(FXUTF32LECodec)
public:
  FXUTF32LECodec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual FXint mibEnum() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXUTF32LECodec(){}
  };


/// Codec for UTF-32
class FXAPI FXUTF32Codec : public FXTextCodec {
  FXDECLARE(FXUTF32Codec)
public:
  FXUTF32Codec(){}
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
  virtual ~FXUTF32Codec(){}
  };


}

#endif

