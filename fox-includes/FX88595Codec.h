#ifndef FX88595CODEC_H
#define FX88595CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// ISO-8859-5 Codec
class FXAPI FX88595Codec : public FXTextCodec {
  FXDECLARE(FX88595Codec)
public:
  FX88595Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FX88595Codec(){}
  };

}

#endif
