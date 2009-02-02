#ifndef FXCP865CODEC_H
#define FXCP865CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP865 Codec
class FXAPI FXCP865Codec : public FXTextCodec {
  FXDECLARE(FXCP865Codec)
public:
  FXCP865Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP865Codec(){}
  };

}

#endif
