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
 * $Id: FXRbWindow.h 2344 2006-02-12 21:19:36Z lyle $
 ***********************************************************************/

#ifndef FXRBWINDOW_H
#define FXRBWINDOW_H

#define DECLARE_FXWINDOW_STUBS(klass) \
inline void klass ## _layout(klass* self){ \
  self->klass::layout(); \
  } \
inline FXint klass ## _getDefaultWidth(klass* self){ \
  return self->klass::getDefaultWidth(); \
  } \
inline FXint klass ## _getDefaultHeight(klass* self){ \
  return self->klass::getDefaultHeight(); \
  } \
inline FXint klass ## _getWidthForHeight(klass* self,FXint givenheight){ \
  return self->klass::getWidthForHeight(givenheight); \
  } \
inline FXint klass ## _getHeightForWidth(klass* self,FXint givenwidth){ \
  return self->klass::getHeightForWidth(givenwidth); \
  } \
inline bool klass ## _canFocus(const klass* self){ \
  return self->klass::canFocus(); \
  } \
inline void klass ## _setFocus(klass* self){ \
  self->klass::setFocus(); \
  } \
inline void klass ## _killFocus(klass* self){ \
  self->klass::killFocus(); \
  } \
inline void klass ## _changeFocus(klass* self,FXWindow* child){ \
  self->klass::changeFocus(child); \
  } \
inline void klass ## _setDefault(klass* self,FXbool enable){ \
  self->klass::setDefault(enable); \
  } \
inline void klass ## _enable(klass* self){ \
  self->klass::enable(); \
  } \
inline void klass ## _disable(klass* self){ \
  self->klass::disable(); \
  } \
inline void klass ## _raise(klass* self){ \
  self->klass::raise(); \
  } \
inline void klass ## _lower(klass* self){ \
  self->klass::lower(); \
  } \
inline void klass ## _move(klass* self,FXint x,FXint y){ \
  self->klass::move(x,y); \
  } \
inline void klass ## _position(klass* self,FXint x,FXint y,FXint w,FXint h){ \
  self->klass::position(x,y,w,h); \
  } \
inline void klass ## _recalc(klass* self){ \
  self->klass::recalc(); \
  } \
inline void klass ## _reparent(klass* self,FXWindow* father,FXWindow* other){ \
  self->klass::reparent(father,other); \
  } \
inline void klass ## _show(klass* self){ \
  self->klass::show(); \
  } \
inline void klass ## _hide(klass* self){ \
  self->klass::hide(); \
  } \
inline bool klass ## _isComposite(const klass* self) { \
  return self->klass::isComposite(); \
  } \
inline bool klass ## _contains(const klass* self,FXint parentx,FXint parenty) { \
  return self->klass::contains(parentx,parenty); \
  } \
inline bool klass ## _doesSaveUnder(const klass* self) { \
  return self->klass::doesSaveUnder(); \
  } \
inline void klass ## _setBackColor(klass* self,FXColor clr){ \
  self->klass::setBackColor(clr); \
  } \
inline const FXchar* klass ## _tr(const klass* self,const FXchar* message,const FXchar* hint) { \
  return self->klass::tr(message,hint); \
  } \
inline void klass ## _setShape(klass* self,const FXRegion& region){ \
  self->klass::setShape(region); \
  } \
inline void klass ## _setShape(klass* self,FXBitmap* bitmap){ \
  self->klass::setShape(bitmap); \
  } \
inline void klass ## _setShape(klass* self,FXIcon* icon){ \
  self->klass::setShape(icon); \
  } \
inline void klass ## _clearShape(klass* self){ \
  self->klass::clearShape(); \
  } \
inline void klass ## _dropEnable(klass* self){ \
  self->klass::dropEnable(); \
  } \
inline void klass ## _dropDisable(klass* self){ \
  self->klass::dropDisable(); \
  }


#define IMPLEMENT_FXWINDOW_STUBS(cls) \
  void cls::layout(){ \
    FXRbCallVoidMethod(this,"layout"); \
    } \
  FXint cls::getDefaultWidth(){ \
    return FXRbCallIntMethod(this,"getDefaultWidth"); \
    } \
  FXint cls::getDefaultHeight(){ \
    return FXRbCallIntMethod(this,"getDefaultHeight"); \
    } \
  FXint cls::getWidthForHeight(FXint givenheight){ \
    return FXRbCallIntMethod(this,"getWidthForHeight",givenheight); \
    } \
  FXint cls::getHeightForWidth(FXint givenwidth){ \
    return FXRbCallIntMethod(this,"getHeightForWidth",givenwidth); \
    } \
  bool cls::canFocus() const { \
    return FXRbCallBoolMethod(this,"canFocus"); \
    } \
  void cls::setFocus(){ \
    FXRbCallVoidMethod(this,"setFocus"); \
    } \
  void cls::killFocus(){ \
    FXRbCallVoidMethod(this,"killFocus"); \
    } \
  void cls::changeFocus(FXWindow* child){ \
    if(!FXRbIsInGC(this)) FXRbCallVoidMethod(this,"changeFocus",child); \
    } \
  void cls::setDefault(FXbool enable){ \
    FXRbCallVoidMethod(this,"setDefault",enable); \
    } \
  void cls::enable(){ \
    FXRbCallVoidMethod(this,"enable"); \
    } \
  void cls::disable(){ \
    FXRbCallVoidMethod(this,"disable"); \
    } \
  void cls::raise(){ \
    FXRbCallVoidMethod(this,"raiseWindow"); \
    } \
  void cls::lower(){ \
    FXRbCallVoidMethod(this,"lower"); \
    } \
  void cls::move(FXint x,FXint y){ \
    FXRbCallVoidMethod(this,"move",x,y); \
    } \
  void cls::position(FXint x,FXint y,FXint w,FXint h){ \
    FXRbCallVoidMethod(this,"position",x,y,w,h); \
    } \
  void cls::recalc(){ \
    if(!FXRbIsInGC(this)) FXRbCallVoidMethod(this,"recalc"); \
    } \
  void cls::reparent(FXWindow* father,FXWindow* other){ \
    FXRbCallVoidMethod(this,"reparent",father,other); \
    } \
  void cls::show(){ \
    FXRbCallVoidMethod(this,"show"); \
    } \
  void cls::hide(){ \
    FXRbCallVoidMethod(this,"hide"); \
    } \
  bool cls::isComposite() const { \
    return FXRbCallBoolMethod(this,"isComposite"); \
    } \
  bool cls::contains(FXint parentx,FXint parenty) const{ \
    return FXRbCallBoolMethod(this,"contains",parentx,parenty); \
    } \
  bool cls::doesSaveUnder() const { \
    return FXRbCallBoolMethod(this,"doesSaveUnder"); \
    } \
  void cls::setBackColor(FXColor clr) { \
    FXRbCallVoidMethod(this,"setBackColor",clr); \
    } \
  const FXchar* cls::tr(const FXchar* message,const FXchar* hint) const { \
    return FXRbCallCStringMethod(this,"tr",message,hint); \
    } \
  void cls::setShape(const FXRegion& region) { \
    FXRbCallVoidMethod(this,"setShape",region); \
    } \
  void cls::setShape(FXBitmap* bitmap) { \
    FXRbCallVoidMethod(this,"setShape",bitmap); \
    } \
  void cls::setShape(FXIcon* icon) { \
    FXRbCallVoidMethod(this,"setShape",icon); \
    } \
  void cls::clearShape() { \
    FXRbCallVoidMethod(this,"clearShape"); \
    } \
  void cls::dropEnable() { \
    FXRbCallVoidMethod(this,"dropEnable"); \
    } \
  void cls::dropDisable() { \
    FXRbCallVoidMethod(this,"dropDisable"); \
    }

class FXRbWindow : public FXWindow {
  FXDECLARE(FXRbWindow)
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
protected:
  FXRbWindow(){}
public:
  // Constructor
  FXRbWindow(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXWindow(p,opts,x,y,w,h){}

  // Another constructor
  FXRbWindow(FXApp* a,FXVisual *vis):FXWindow(a,vis){}

  // Yet another constructor
  FXRbWindow(FXApp* a,FXWindow* own,FXuint opts,FXint x,FXint y,FXint w,FXint h):FXWindow(a,own,opts,x,y,w,h){}

  // Mark dependencies for the GC
  static void markfunc(FXWindow* win);

  // Destructor
  virtual ~FXRbWindow(){
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
