#ifndef FXCP850CODEC_H
#define FXCP850CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP8502 Codec
class FXAPI FXCP850Codec : public FXTextCodec {
  FXDECLARE(FXCP850Codec)
public:
  FXCP850Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP850Codec(){}
  };

}

#endif
