#ifndef FXCP863CODEC_H
#define FXCP863CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP863 Codec
class FXAPI FXCP863Codec : public FXTextCodec {
  FXDECLARE(FXCP863Codec)
public:
  FXCP863Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP863Codec(){}
  };

}

#endif
