#ifndef FXCP852CODEC_H
#define FXCP852CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP852 Codec
class FXAPI FXCP852Codec : public FXTextCodec {
  FXDECLARE(FXCP852Codec)
public:
  FXCP852Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP852Codec(){}
  };

}

#endif
