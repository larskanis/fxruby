#ifndef FXCP866CODEC_H
#define FXCP866CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP866 Codec
class FXAPI FXCP866Codec : public FXTextCodec {
  FXDECLARE(FXCP866Codec)
public:
  FXCP866Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP866Codec(){}
  };

}

#endif
