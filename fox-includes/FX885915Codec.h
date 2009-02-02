#ifndef FX885915CODEC_H
#define FX885915CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// ISO-8859-15 Codec
class FXAPI FX885915Codec : public FXTextCodec {
  FXDECLARE(FX885915Codec)
public:
  FX885915Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FX885915Codec(){}
  };

}

#endif
