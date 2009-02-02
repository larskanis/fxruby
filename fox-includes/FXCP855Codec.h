#ifndef FXCP855CODEC_H
#define FXCP855CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP855 Codec
class FXAPI FXCP855Codec : public FXTextCodec {
  FXDECLARE(FXCP855Codec)
public:
  FXCP855Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP855Codec(){}
  };

}

#endif
