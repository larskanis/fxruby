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
 * $Id: FXRbText.h 2395 2006-04-22 17:27:36Z lyle $
 ***********************************************************************/

#ifndef FXRBTEXT_H
#define FXRBTEXT_H

#define DECLARE_FXTEXT_STUBS(klass) \
inline void klass ## _setCursorPos(klass* self,FXint pos,FXbool notify){ \
  self->klass::setCursorPos(pos,notify); \
  } \
inline FXbool klass ## _extendSelection(klass* self,FXint pos,FXTextSelectionMode mode=SELECT_CHARS,FXbool notify=FALSE){ \
  return self->klass::extendSelection(pos,mode,notify); \
  } \
inline FXbool klass ## _killSelection(klass* self,FXbool notify=FALSE){ \
  return self->klass::killSelection(notify); \
  } \
inline void klass ## _replaceText(klass* self,FXint pos,FXint m,const FXString& text,FXbool notify){ \
  self->klass::replaceText(pos,m,text.text(),text.length(),notify); \
  } \
inline void klass ## _replaceStyledText(klass* self,FXint pos,FXint m,const FXString& text,FXint style,FXbool notify){ \
  self->klass::replaceStyledText(pos,m,text.text(),text.length(),style,notify); \
  } \
inline void klass ## _appendText(klass* self,const FXString& text,FXbool notify){ \
  self->klass::appendText(text.text(),text.length(),notify); \
  } \
inline void klass ## _appendStyledText(klass* self,const FXString& text,FXint style,FXbool notify){ \
  self->klass::appendStyledText(text.text(),text.length(),style,notify); \
  } \
inline void klass ## _insertText(klass* self,FXint pos,const FXString& text,FXbool notify){ \
  self->klass::insertText(pos,text.text(),text.length(),notify); \
  } \
inline void klass ## _insertStyledText(klass* self,FXint pos,const FXString& text,FXint style,FXbool notify){ \
  self->klass::insertStyledText(pos,text.text(),text.length(),style,notify); \
  } \
inline void klass ## _removeText(klass* self,FXint pos,FXint n,FXbool notify){ \
  self->klass::removeText(pos,n,notify); \
  } \
inline void klass ## _changeStyle(klass* self,FXint pos,FXint n,FXint style){ \
  self->klass::changeStyle(pos,n,style); \
  } \
inline void klass ## _changeStyle(klass* self,FXint pos,const FXString& style){ \
  self->klass::changeStyle(pos,style.text(),style.length()); \
  } \
inline void klass ## _setText(klass* self,const FXString& text,FXbool notify){ \
  self->klass::setText(text.text(),text.length(),notify); \
  } \
inline void klass ## _setStyledText(klass* self,const FXString& text,FXint style,FXbool notify){ \
  self->klass::setStyledText(text.text(),text.length(),style,notify); \
  }


#define IMPLEMENT_FXTEXT_STUBS(cls) \
  void cls::setCursorPos(FXint pos,FXbool notify){ \
    FXRbCallVoidMethod(this,"setCursorPos",pos,notify); \
    } \
  FXbool cls::extendSelection(FXint pos,FXTextSelectionMode mode,FXbool notify){ \
    return FXRbCallBoolMethod(this,"extendSelection",pos,mode,notify); \
    } \
  FXbool cls::killSelection(FXbool notify){ \
    return FXRbCallBoolMethod(this,"killSelection",notify); \
    } \
  void cls::replaceText(FXint pos,FXint m,const FXchar *text,FXint n,FXbool notify){ \
    FXRbCallVoidMethod(this,"replaceText",pos,m,FXString(text,n),notify); \
    } \
  void cls::replaceText(FXint pos,FXint m,const FXString& text,FXbool notify){ \
    FXRbCallVoidMethod(this,"replaceText",pos,m,text,notify); \
    } \
  void cls::replaceStyledText(FXint pos,FXint m,const FXchar *text,FXint n,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"replaceStyledText",pos,m,FXString(text,n),style,notify); \
    } \
  void cls::replaceStyledText(FXint pos,FXint m,const FXString& text,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"replaceStyledText",pos,m,text,style,notify); \
    } \
  void cls::appendText(const FXchar *text,FXint n,FXbool notify){ \
    FXRbCallVoidMethod(this,"appendText",FXString(text,n),notify); \
    } \
  void cls::appendText(const FXString& text,FXbool notify){ \
    FXRbCallVoidMethod(this,"appendText",text,notify); \
    } \
  void cls::appendStyledText(const FXchar *text,FXint n,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"appendStyledText",FXString(text,n),style,notify); \
    } \
  void cls::appendStyledText(const FXString& text,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"appendStyledText",text,style,notify); \
    } \
  void cls::insertText(FXint pos,const FXchar *text,FXint n,FXbool notify){ \
    FXRbCallVoidMethod(this,"insertText",pos,FXString(text,n),notify); \
    } \
  void cls::insertText(FXint pos,const FXString& text,FXbool notify){ \
    FXRbCallVoidMethod(this,"insertText",pos,text,notify); \
    } \
  void cls::insertStyledText(FXint pos,const FXchar *text,FXint n,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"insertStyledText",pos,FXString(text,n),style,notify); \
    } \
  void cls::insertStyledText(FXint pos,const FXString& text,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"insertStyledText",pos,text,style,notify); \
    } \
  void cls::removeText(FXint pos,FXint n,FXbool notify){ \
    FXRbCallVoidMethod(this,"removeText",pos,n,notify); \
    } \
  void cls::changeStyle(FXint pos,FXint n,FXint style){ \
    FXRbCallVoidMethod(this,"changeStyle",pos,n,style); \
    } \
  void cls::changeStyle(FXint pos,const FXchar* style,FXint n){ \
    FXRbCallVoidMethod(this,"changeStyle",pos,FXString(style,n)); \
    } \
  void cls::changeStyle(FXint pos,const FXString& style){ \
    FXRbCallVoidMethod(this,"changeStyle",pos,style); \
    } \
  void cls::setText(const FXchar* text,FXint n,FXbool notify){ \
    FXRbCallVoidMethod(this,"setText",FXString(text,n),notify); \
    } \
  void cls::setText(const FXString& text,FXbool notify){ \
    FXRbCallVoidMethod(this,"setText",text,notify); \
    } \
  void cls::setStyledText(const FXchar* text,FXint n,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"setStyledText",FXString(text,n),style,notify); \
    } \
  void cls::setStyledText(const FXString& text,FXint style,FXbool notify){ \
    FXRbCallVoidMethod(this,"setStyledText",text,style,notify); \
    }


class FXRbText : public FXText {
  FXDECLARE(FXRbText)
protected:
  FXRbText(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbScrollAreaVirtuals.h"
#include "FXRbTextVirtuals.h"
public:
  /// Construct multi-line text widget
  FXRbText(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2) : FXText(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb){
    numStyles=0;
    styles=0;
    }

  // Number of styles in style array
  FXint numStyles;

  // Style array
  FXHiliteStyle *styles;


  // Mark dependencies for the GC
  static void markfunc(FXText* self);

  // Unregister objects that this text owns and is about to destroy
  static void unregisterOwnedObjects(FXText *pText);

  // Destructor
  virtual ~FXRbText(){
    numStyles=0;
    delete [] styles;
    styles=(FXHiliteStyle*)-1;
    FXRbText::unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
