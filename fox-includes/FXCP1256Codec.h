#ifndef FXCP1256CODEC_H
#define FXCP1256CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP1256 Codec
class FXAPI FXCP1256Codec : public FXTextCodec {
  FXDECLARE(FXCP1256Codec)
public:
  FXCP1256Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP1256Codec(){}
  };

}

#endif
