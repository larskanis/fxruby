#ifndef FX885916CODEC_H
#define FX885916CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// ISO-8859-16 Codec
class FXAPI FX885916Codec : public FXTextCodec {
  FXDECLARE(FX885916Codec)
public:
  FX885916Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FX885916Codec(){}
  };

}

#endif
