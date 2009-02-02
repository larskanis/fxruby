#ifndef FXCP861CODEC_H
#define FXCP861CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP861 Codec
class FXAPI FXCP861Codec : public FXTextCodec {
  FXDECLARE(FXCP861Codec)
public:
  FXCP861Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP861Codec(){}
  };

}

#endif
