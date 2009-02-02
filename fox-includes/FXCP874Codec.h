#ifndef FXCP874CODEC_H
#define FXCP874CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP874 Codec
class FXAPI FXCP874Codec : public FXTextCodec {
  FXDECLARE(FXCP874Codec)
public:
  FXCP874Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP874Codec(){}
  };

}

#endif
