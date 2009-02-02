#ifndef FXCP856CODEC_H
#define FXCP856CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP856 Codec
class FXAPI FXCP856Codec : public FXTextCodec {
  FXDECLARE(FXCP856Codec)
public:
  FXCP856Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP856Codec(){}
  };

}

#endif
