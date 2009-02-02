#ifndef FXCP857CODEC_H
#define FXCP857CODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif

namespace FX {

/// CP857 Codec
class FXAPI FXCP857Codec : public FXTextCodec {
  FXDECLARE(FXCP857Codec)
public:
  FXCP857Codec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXCP857Codec(){}
  };

}

#endif
