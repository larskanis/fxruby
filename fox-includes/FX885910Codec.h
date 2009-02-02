#ifndef FX885910CODEC_H
#define FX885910CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// ISO-8859-10 Codec
class FXAPI FX885910Codec : public FXTextCodec {
  FXDECLARE(FX885910Codec)
public:
  FX885910Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FX885910Codec(){}
  };

}

#endif
