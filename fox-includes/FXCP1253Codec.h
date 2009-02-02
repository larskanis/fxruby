#ifndef FXCP1253CODEC_H
#define FXCP1253CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP1253 Codec
class FXAPI FXCP1253Codec : public FXTextCodec {
  FXDECLARE(FXCP1253Codec)
public:
  FXCP1253Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP1253Codec(){}
  };

}

#endif
