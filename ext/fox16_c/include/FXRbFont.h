/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

/***********************************************************************
 * $Id: FXRbFont.h 2372 2006-04-20 00:38:08Z lyle $
 ***********************************************************************/

#ifndef FXRBFONT_H
#define FXRBFONT_H

#define DECLARE_FXFONT_STUBS(klass) \
inline void klass ## _setFontDesc(klass* self,const FXFontDesc& desc){ \
  self->klass::setFontDesc(desc); \
  } \
inline void klass ## _setAngle(klass* self,FXint ang){ \
  self->klass::setAngle(ang); \
  } \
inline void klass ## _setFont(klass* self,const FXString& string){ \
  self->klass::setFont(string); \
  } \
inline FXbool klass ## _isFontMono(const klass* self){ \
  return self->klass::isFontMono(); \
  } \
inline FXbool klass ## _hasChar(const klass* self,FXwchar ch){ \
  return self->klass::hasChar(ch); \
  } \
inline FXwchar klass ## _getMinChar(const klass* self){ \
  return self->klass::getMinChar(); \
  } \
inline FXwchar klass ## _getMaxChar(const klass* self){ \
  return self->klass::getMaxChar(); \
  } \
inline FXint klass ## _leftBearing(const klass* self,FXwchar ch){ \
  return self->klass::leftBearing(ch); \
  } \
inline FXint klass ## _rightBearing(const klass* self,FXwchar ch){ \
  return self->klass::rightBearing(ch); \
  } \
inline FXint klass ## _getFontWidth(const klass* self){ \
  return self->klass::getFontWidth(); \
  } \
inline FXint klass ## _getFontHeight(const klass* self){ \
  return self->klass::getFontHeight(); \
  } \
inline FXint klass ## _getFontAscent(const klass* self){ \
  return self->klass::getFontAscent(); \
  } \
inline FXint klass ## _getFontDescent(const klass* self){ \
  return self->klass::getFontDescent(); \
  } \
inline FXint klass ## _getFontLeading(const klass* self){ \
  return self->klass::getFontLeading(); \
  } \
inline FXint klass ## _getFontSpacing(const klass* self){ \
  return self->klass::getFontSpacing(); \
  } \
inline FXint klass ## _getCharWidth(const klass* self,FXwchar ch){ \
  return self->klass::getCharWidth(ch); \
  } \
inline FXint klass ## _getTextWidth(const klass* self,const FXString& str){ \
  return self->klass::getTextWidth(str); \
  } \
inline FXint klass ## _getTextHeight(const klass* self,const FXString& str){ \
  return self->klass::getTextHeight(str); \
  }

#define IMPLEMENT_FXFONT_STUBS(cls) \
  void cls::setFontDesc(const FXFontDesc& desc) { \
    FXRbCallVoidMethod(this,"setFontDesc",desc); \
    } \
  void cls::setAngle(FXint ang) { \
    FXRbCallVoidMethod(this,"setAngle",ang); \
    } \
  void cls::setFont(const FXString& string) { \
    FXRbCallVoidMethod(this,"setFont",string); \
    } \
  FXbool cls::isFontMono() const { \
    return FXRbCallBoolMethod(this,"isFontMono"); \
    } \
  FXbool cls::hasChar(FXwchar ch) const { \
    return FXRbCallBoolMethod(this,"hasChar",ch); \
    } \
  FXwchar cls::getMinChar() const { \
    return FXRbCallWCharMethod(this,"getMinChar"); \
    } \
  FXwchar cls::getMaxChar() const { \
    return FXRbCallWCharMethod(this,"getMaxChar"); \
    } \
  FXint cls::leftBearing(FXwchar ch) const { \
    return FXRbCallIntMethod(this,"leftBearing",ch); \
    } \
  FXint cls::rightBearing(FXwchar ch) const { \
    return FXRbCallIntMethod(this,"rightBearing",ch); \
    } \
  FXint cls::getFontWidth() const { \
    return FXRbCallIntMethod(this,"getFontWidth"); \
    } \
  FXint cls::getFontHeight() const { \
    return FXRbCallIntMethod(this,"getFontHeight"); \
    } \
  FXint cls::getFontAscent() const { \
    return FXRbCallIntMethod(this,"getFontAscent"); \
    } \
  FXint cls::getFontDescent() const { \
    return FXRbCallIntMethod(this,"getFontDescent"); \
    } \
  FXint cls::getFontLeading() const { \
    return FXRbCallIntMethod(this,"getFontLeading"); \
    } \
  FXint cls::getFontSpacing() const { \
    return FXRbCallIntMethod(this,"getFontSpacing"); \
    } \
  FXint cls::getCharWidth(FXwchar ch) const { \
    return FXRbCallIntMethod(this,"getCharWidth",ch); \
    } \
  FXint cls::getTextWidth(const FXString& str) const { \
    return FXRbCallIntMethod(this,"getTextWidth",str); \
    } \
  FXint cls::getTextHeight(const FXString& str) const { \
    return FXRbCallIntMethod(this,"getTextHeight",str); \
    }

class FXRbFont : public FXFont {
  FXDECLARE(FXRbFont)
protected:
  FXRbFont(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbFontVirtuals.h"
public:
  // Is this font owned by the FXApp?
  FXbool ownedByApp;

public:
  /// Construct font from font description
  FXRbFont(FXApp* a,const FXFontDesc& fontdesc) : FXFont(a,fontdesc),ownedByApp(FALSE){
    FXRbRegisterAppSensitiveObject(this);
    }

  /// Construct a font with given face name, size in points(pixels), weight, slant, character set encoding, setwidth, and hints
  FXRbFont(FXApp* a,const FXString& face,FXuint sz,FXuint wt=FXFont::Normal,FXuint sl=FXFont::Straight,FXuint enc=FONTENCODING_DEFAULT,FXuint setw=FXFont::NonExpanded,FXuint h=0) : FXFont(a,face,sz,wt,sl,enc,setw,h),ownedByApp(FALSE){
    FXRbRegisterAppSensitiveObject(this);
    }

  /// Construct a font with given X11 font string
  FXRbFont(FXApp* a,const FXString& nm) : FXFont(a,nm),ownedByApp(FALSE){
    FXRbRegisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXFont* self);

  // Destroy this object if it's not owned
  static void freefunc(FXFont* self);

  // Destructor
  virtual ~FXRbFont(){
    FXTRACE((100,"FXRbFont::~FXRbFont() %p\n",this));
    FXRbUnregisterRubyObj(this);
    FXRbUnregisterAppSensitiveObject(this);
    }
  };

#endif
