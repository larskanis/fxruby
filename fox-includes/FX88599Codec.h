#ifndef FX88599CODEC_H
#define FX88599CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// ISO-8859-9 Codec
class FXAPI FX88599Codec : public FXTextCodec {
  FXDECLARE(FX88599Codec)
public:
  FX88599Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FX88599Codec(){}
  };

}

#endif
