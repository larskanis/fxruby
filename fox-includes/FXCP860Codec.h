#ifndef FXCP860CODEC_H
#define FXCP860CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP860 Codec
class FXAPI FXCP860Codec : public FXTextCodec {
  FXDECLARE(FXCP860Codec)
public:
  FXCP860Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP860Codec(){}
  };

}

#endif
