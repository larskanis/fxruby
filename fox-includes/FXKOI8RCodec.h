#ifndef FXKOI8RCODEC_H
#define FXKOI8RCODEC_H

#ifndef FXTEXTCODEC_H
#include "FXTextCodec.h"
#endif



namespace FX {


/// KOI8-R Codec
class FXAPI FXKOI8RCodec : public FXTextCodec {
  FXDECLARE(FXKOI8RCodec)
public:
  FXKOI8RCodec(){}
  virtual FXint mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const;
  virtual FXint wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const;
  virtual FXint mibEnum() const;
  virtual const FXchar* name() const;
  virtual const FXchar* mimeName() const;
  virtual const FXchar* const* aliases() const;
  virtual ~FXKOI8RCodec(){}
  };

}

#endif
