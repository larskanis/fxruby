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
 * $Id: FXRbList.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBLIST_H
#define FXRBLIST_H

#define DECLARE_FXLISTITEM_STUBS(klass) \
inline void klass ## _create(klass* self){ \
  self->klass::create(); \
  } \
inline void klass ## _detach(klass* self){ \
  self->klass::detach(); \
  } \
inline void klass ## _destroy(klass* self){ \
  self->klass::destroy(); \
  } \
inline void klass ## _setText(klass* self,const FXString& text){ \
  self->klass::setText(text); \
  } \
inline void klass ## _setIcon(klass* self,FXIcon* icn,FXbool owned){ \
  self->klass::setIcon(icn,owned); \
  } \
inline void klass ## _setFocus(klass* self,FXbool focus){ \
  self->klass::setFocus(focus); \
  } \
inline void klass ## _setSelected(klass* self,FXbool selected){ \
  self->klass::setSelected(selected); \
  } \
inline void klass ## _setEnabled(klass* self,FXbool enabled){ \
  self->klass::setEnabled(enabled); \
  } \
inline void klass ## _setDraggable(klass* self,FXbool draggable){ \
  self->klass::setDraggable(draggable); \
  } \
inline FXint klass ## _getWidth(const klass* self,const FXList* list){ \
  return self->klass::getWidth(list); \
  } \
inline FXint klass ## _getHeight(const klass* self,const FXList* list){ \
  return self->klass::getHeight(list); \
  }


#define IMPLEMENT_FXLISTITEM_STUBS(cls) \
  void cls::create(){ \
    FXRbCallVoidMethod(this,"create"); \
    } \
  void cls::detach(){ \
    FXRbCallVoidMethod(this,"detach"); \
    } \
  void cls::destroy(){ \
    FXRbCallVoidMethod(this,"destroy"); \
    } \
  void cls::setText(const FXString& txt){ \
    FXRbCallVoidMethod(this,"setText",txt); \
    } \
  void cls::setIcon(FXIcon* icn,FXbool owned){ \
    FXRbCallVoidMethod(this,"setIcon",icn,owned); \
    } \
  void cls::setFocus(FXbool focus){ \
    FXRbCallVoidMethod(this,"setFocus",focus); \
    } \
  void cls::setSelected(FXbool selected){ \
    FXRbCallVoidMethod(this,"setSelected",selected); \
    } \
  void cls::setEnabled(FXbool enabled){ \
    FXRbCallVoidMethod(this,"setEnabled",enabled); \
    } \
  void cls::setDraggable(FXbool draggable){ \
    FXRbCallVoidMethod(this,"setDraggable",draggable); \
    } \
  FXint cls::getWidth(const FXList* list) const { \
    return FXRbCallIntMethod(this,"getWidth",list); \
    } \
  FXint cls::getHeight(const FXList* list) const { \
    return FXRbCallIntMethod(this,"getHeight",list); \
    }


class FXRbListItem : public FXListItem {
  FXDECLARE(FXRbListItem)
protected:
  FXRbListItem(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbListItemVirtuals.h"
public:
  // Is this list item owned by an FXList yet?
  FXbool owned;
public:
  // Constructor
  FXRbListItem(const FXString& text,FXIcon* ic=NULL,void* ptr=NULL) : FXListItem(text,ic,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXListItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXListItem* self);

  // Destructor
  virtual ~FXRbListItem(){
    FXRbUnregisterRubyObj(this);
    }
  };


#define DECLARE_FXLIST_STUBS(klass) \
inline FXbool klass ## _enableItem(klass* self,FXint index){ \
  return self->klass::enableItem(index); \
  } \
inline FXbool klass ## _disableItem(klass* self,FXint index){ \
  return self->klass::disableItem(index); \
  } \
inline void klass ## _makeItemVisible(klass* self,FXint index){ \
  self->klass::makeItemVisible(index); \
  } \
inline FXint klass ## _getItemAt(const klass* self,FXint x,FXint y){ \
  return self->klass::getItemAt(x,y); \
  } \
inline FXbool klass ## _selectItem(klass* self,FXint index,FXbool notify){ \
  return self->klass::selectItem(index,notify); \
  } \
inline FXbool klass ## _deselectItem(klass* self,FXint index,FXbool notify){ \
  return self->klass::deselectItem(index,notify); \
  } \
inline FXbool klass ## _toggleItem(klass* self,FXint index,FXbool notify){ \
  return self->klass::toggleItem(index,notify); \
  } \
inline FXbool klass ## _extendSelection(klass* self,FXint index,FXbool notify){ \
  return self->klass::extendSelection(index,notify); \
  } \
inline FXbool klass ## _killSelection(klass* self,FXbool notify){ \
  return self->klass::killSelection(notify); \
  } \
inline void klass ## _setCurrentItem(klass* self,FXint index,FXbool notify){ \
  self->klass::setCurrentItem(index,notify); \
  }


#define IMPLEMENT_FXLIST_STUBS(cls) \
  FXbool cls::enableItem(FXint index){ \
    return FXRbCallBoolMethod(this,"enableItem",index); \
    } \
  FXbool cls::disableItem(FXint index){ \
    return FXRbCallBoolMethod(this,"disableItem",index); \
    } \
  void cls::makeItemVisible(FXint index) { \
    FXRbCallVoidMethod(this,"makeItemVisible",index); \
    } \
  FXint cls::getItemAt(FXint x,FXint y) const { \
    return FXRbCallIntMethod(this,"getItemAt",x,y); \
    } \
  FXbool cls::selectItem(FXint index,FXbool notify){ \
    return FXRbCallBoolMethod(this,"selectItem",index,notify); \
    } \
  FXbool cls::deselectItem(FXint index,FXbool notify){ \
    return FXRbCallBoolMethod(this,"deselectItem",index,notify); \
    } \
  FXbool cls::toggleItem(FXint index,FXbool notify){ \
    return FXRbCallBoolMethod(this,"toggleItem",index,notify); \
    } \
  FXbool cls::extendSelection(FXint index,FXbool notify){ \
    return FXRbCallBoolMethod(this,"extendSelection",index,notify); \
    } \
  FXbool cls::killSelection(FXbool notify){ \
    return FXRbCallBoolMethod(this,"killSelection",notify); \
    } \
  void cls::setCurrentItem(FXint index,FXbool notify){ \
    FXRbCallVoidMethod(this,"setCurrentItem",index,notify); \
    }


class FXRbList : public FXList {
  FXDECLARE(FXRbList)
protected:
  FXRbList(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbScrollAreaVirtuals.h"
#include "FXRbListVirtuals.h"
public:
  /// Construct a list with initially no items in it
  FXRbList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=LIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXList(p,tgt,sel,opts,x,y,w,h){
    setSortFunc(FXRbList::sortFunc);
    }

  // Sort function stand-in
  static FXint sortFunc(const FXListItem* a,const FXListItem* b);

  // Mark dependencies for the GC
  static void markfunc(FXList* self);

  // Unregister objects that this list owns and is about to destroy
  static void unregisterOwnedObjects(FXList *pList);

  // Destructor
  virtual ~FXRbList(){
    FXRbList::unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
