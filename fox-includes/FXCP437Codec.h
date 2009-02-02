#ifndef FXCP437CODEC_H
#define FXCP437CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP437 Codec
class FXAPI FXCP437Codec : public FXTextCodec {
  FXDECLARE(FXCP437Codec)
public:
  FXCP437Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP437Codec(){}
  };

}

#endif
