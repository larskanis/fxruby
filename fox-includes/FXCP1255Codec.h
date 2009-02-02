#ifndef FXCP1255CODEC_H
#define FXCP1255CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP1255 Codec
class FXAPI FXCP1255Codec : public FXTextCodec {
  FXDECLARE(FXCP1255Codec)
public:
  FXCP1255Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP1255Codec(){}
  };

}

#endif
