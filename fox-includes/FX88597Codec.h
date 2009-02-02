#ifndef FX88597CODEC_H
#define FX88597CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// ISO-8859-7 Codec
class FXAPI FX88597Codec : public FXTextCodec {
  FXDECLARE(FX88597Codec)
public:
  FX88597Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FX88597Codec(){}
  };

}

#endif
