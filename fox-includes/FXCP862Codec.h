#ifndef FXCP862CODEC_H
#define FXCP862CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP862 Codec
class FXAPI FXCP862Codec : public FXTextCodec {
  FXDECLARE(FXCP862Codec)
public:
  FXCP862Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP862Codec(){}
  };

}

#endif
