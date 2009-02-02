#ifndef FXCP869CODEC_H
#define FXCP869CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP869 Codec
class FXAPI FXCP869Codec : public FXTextCodec {
  FXDECLARE(FXCP869Codec)
public:
  FXCP869Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP869Codec(){}
  };

}

#endif
