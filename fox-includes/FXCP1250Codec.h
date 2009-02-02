#ifndef FXCP1250CODEC_H
#define FXCP1250CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP1250 Codec
class FXAPI FXCP1250Codec : public FXTextCodec {
  FXDECLARE(FXCP1250Codec)
public:
  FXCP1250Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP1250Codec(){}
  };

}

#endif
