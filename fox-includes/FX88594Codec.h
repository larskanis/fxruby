#ifndef FX88594CODEC_H
#define FX88594CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// ISO-8859-4 Codec
class FXAPI FX88594Codec : public FXTextCodec {
  FXDECLARE(FX88594Codec)
public:
  FX88594Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FX88594Codec(){}
  };

}

#endif
