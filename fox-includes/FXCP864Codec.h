#ifndef FXCP864CODEC_H
#define FXCP864CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP864 Codec
class FXAPI FXCP864Codec : public FXTextCodec {
  FXDECLARE(FXCP864Codec)
public:
  FXCP864Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP864Codec(){}
  };

}

#endif
