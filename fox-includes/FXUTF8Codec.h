/********************************************************************************
*                                                                               *
*                      U T F - 8  T e x t   C o d e c                           *
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
* $Id: FXUTF8Codec.h 2401 2006-04-27 00:46:49Z lyle $                       *
********************************************************************************/
#ifndef FXUTF8CODEC_H
#define FXUTF8CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif


namespace FX {

/// Codec for UTF-8
class FXAPI FXUTF8Codec : public FXTextCodec {
public:
  FXUTF8Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual FXint mibEnum() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXUTF8Codec(){}
  };

}

#endif

