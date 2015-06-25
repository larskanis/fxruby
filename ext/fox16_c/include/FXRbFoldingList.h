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
 * $Id: FXRbFoldingList.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBFOLDINGLIST_H
#define FXRBFOLDINGLIST_H

#define DECLARE_FXFOLDINGITEM_STUBS(klass) \
inline void klass ## _setText(klass* self,const FXString& text){ \
  self->klass::setText(text); \
  } \
inline void klass ## _setOpenIcon(klass* self,FXIcon* icn,FXbool owned){ \
  self->klass::setOpenIcon(icn,owned); \
  } \
inline void klass ## _setClosedIcon(klass* self,FXIcon* icn,FXbool owned){ \
  self->klass::setClosedIcon(icn,owned); \
  } \
inline void klass ## _setFocus(klass* self,FXbool focus){ \
  self->klass::setFocus(focus); \
  } \
inline void klass ## _setSelected(klass* self,FXbool selected){ \
  self->klass::setSelected(selected); \
  } \
inline void klass ## _setOpened(klass* self,FXbool opened){ \
  self->klass::setOpened(opened); \
  } \
inline void klass ## _setExpanded(klass* self,FXbool expanded){ \
  self->klass::setExpanded(expanded); \
  } \
inline void klass ## _setEnabled(klass* self,FXbool enabled){ \
  self->klass::setEnabled(enabled); \
  } \
inline void klass ## _setDraggable(klass* self,FXbool draggable){ \
  self->klass::setDraggable(draggable); \
  } \
inline FXint klass ## _getWidth(const klass* self,const FXFoldingList* list){ \
  return self->klass::getWidth(list); \
  } \
inline FXint klass ## _getHeight(const klass* self,const FXFoldingList* list){ \
  return self->klass::getHeight(list); \
  } \
inline void klass ## _create(klass* self){ \
  self->klass::create(); \
  } \
inline void klass ## _detach(klass* self){ \
  self->klass::detach(); \
  } \
inline void klass ## _destroy(klass* self){ \
  self->klass::destroy(); \
  }


#define IMPLEMENT_FXFOLDINGITEM_STUBS(cls) \
  void cls::setText(const FXString& txt){ \
    FXRbCallVoidMethod(this,"setText",txt); \
    } \
  void cls::setOpenIcon(FXIcon* icn,FXbool owned){ \
    FXRbCallVoidMethod(this,"setOpenIcon",icn,owned); \
    } \
  void cls::setClosedIcon(FXIcon* icn,FXbool owned){ \
    FXRbCallVoidMethod(this,"setClosedIcon",icn,owned); \
    } \
  void cls::setFocus(FXbool focus){ \
    FXRbCallVoidMethod(this,"setFocus",focus); \
    } \
  void cls::setSelected(FXbool selected){ \
    FXRbCallVoidMethod(this,"setSelected",selected); \
    } \
  void cls::setOpened(FXbool opened){ \
    FXRbCallVoidMethod(this,"setOpened",opened); \
    } \
  void cls::setExpanded(FXbool expanded){ \
    FXRbCallVoidMethod(this,"setExpanded",expanded); \
    } \
  void cls::setEnabled(FXbool enabled){ \
    FXRbCallVoidMethod(this,"setEnabled",enabled); \
    } \
  void cls::setDraggable(FXbool draggable){ \
    FXRbCallVoidMethod(this,"setDraggable",draggable); \
    } \
  FXint cls::getWidth(const FXFoldingList* list) const { \
    return FXRbCallIntMethod(this,"getWidth",list); \
    } \
  FXint cls::getHeight(const FXFoldingList* list) const { \
    return FXRbCallIntMethod(this,"getHeight",list); \
    } \
  void cls::create(){ \
    FXRbCallVoidMethod(this,"create"); \
    } \
  void cls::detach(){ \
    FXRbCallVoidMethod(this,"detach"); \
    } \
  void cls::destroy(){ \
    FXRbCallVoidMethod(this,"destroy"); \
    }


class FXRbFoldingItem : public FXFoldingItem {
  FXDECLARE(FXRbFoldingItem)
protected:
  FXRbFoldingItem(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbFoldingItemVirtuals.h"
public:
  // Is this tree item owned by an FXFoldingList yet?
  FXbool owned;
public:
  // Constructor
  FXRbFoldingItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL) : FXFoldingItem(text,oi,ci,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXFoldingItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXFoldingItem* self);

  // Destructor
  virtual ~FXRbFoldingItem(){
    FXRbUnregisterRubyObj(this);
    }
  };


#define DECLARE_FXFOLDINGLIST_STUBS(klass) \
inline FXFoldingItem * klass ## _getItemAt(const klass* self,FXint x,FXint y){ \
  return self->klass::getItemAt(x,y); \
  } \
inline void klass ## _makeItemVisible(klass *self,FXFoldingItem *item){ \
  self->klass::makeItemVisible(item); \
  } \
inline FXbool klass ## _enableItem(klass *self,FXFoldingItem *item){ \
  return self->klass::enableItem(item); \
  } \
inline FXbool klass ## _disableItem(klass *self,FXFoldingItem *item){ \
  return self->klass::disableItem(item); \
  } \
inline FXbool klass ## _selectItem(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::selectItem(item,notify); \
  } \
inline FXbool klass ## _deselectItem(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::deselectItem(item,notify); \
  } \
inline FXbool klass ## _toggleItem(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::toggleItem(item,notify); \
  } \
inline FXbool klass ## _extendSelection(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::extendSelection(item,notify); \
  } \
inline FXbool klass ## _killSelection(klass *self,FXbool notify){ \
  return self->klass::killSelection(notify); \
  } \
inline FXbool klass ## _openItem(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::openItem(item,notify); \
  } \
inline FXbool klass ## _closeItem(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::closeItem(item,notify); \
  } \
inline FXbool klass ## _collapseTree(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::collapseTree(item,notify); \
  } \
inline FXbool klass ## _expandTree(klass *self,FXFoldingItem *item,FXbool notify){ \
  return self->klass::expandTree(item,notify); \
  } \
inline void klass ## _setCurrentItem(klass *self,FXFoldingItem *item,FXbool notify){ \
  self->klass::setCurrentItem(item,notify); \
  }

#define IMPLEMENT_FXFOLDINGLIST_STUBS(cls) \
  FXFoldingItem * cls::getItemAt(FXint x,FXint y) const { \
    return FXRbCallFoldingItemMethod(this,"getItemAt",x,y); \
    } \
  void cls::makeItemVisible(FXFoldingItem *item) { \
    FXRbCallVoidMethod(this,"makeItemVisible",item); \
    } \
  FXbool cls::enableItem(FXFoldingItem *item) { \
    return FXRbCallBoolMethod(this,"enableItem",item); \
    } \
  FXbool cls::disableItem(FXFoldingItem *item) { \
    return FXRbCallBoolMethod(this,"disableItem",item); \
    } \
  FXbool cls::selectItem(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"selectItem",item,notify); \
    } \
  FXbool cls::deselectItem(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"deselectItem",item,notify); \
    } \
  FXbool cls::toggleItem(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"toggleItem",item,notify); \
    } \
  FXbool cls::extendSelection(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"extendSelection",item,notify); \
    } \
  FXbool cls::killSelection(FXbool notify) { \
    return FXRbCallBoolMethod(this,"killSelection",notify); \
    } \
  FXbool cls::openItem(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"openItem",item,notify); \
    } \
  FXbool cls::closeItem(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"closeItem",item,notify); \
    } \
  FXbool cls::collapseTree(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"collapseTree",item,notify); \
    } \
  FXbool cls::expandTree(FXFoldingItem *item,FXbool notify) { \
    return FXRbCallBoolMethod(this,"expandTree",item,notify); \
    } \
  void cls::setCurrentItem(FXFoldingItem *item,FXbool notify) { \
    FXRbCallVoidMethod(this,"setCurrentItem",item,notify); \
    }

class FXRbFoldingList : public FXFoldingList {
  FXDECLARE(FXRbFoldingList)
protected:
  FXRbFoldingList(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbScrollAreaVirtuals.h"
#include "FXRbFoldingListVirtuals.h"
public:
  /// Construct a folding tree list with nvis visible items; the list is initially empty
  FXRbFoldingList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FOLDINGLIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXFoldingList(p,tgt,sel,opts,x,y,w,h){
    setSortFunc(FXRbFoldingList::sortFunc);
    }

  // Sort function stand-in
  static FXint sortFunc(const FXFoldingItem* a,const FXFoldingItem* b);

  // Mark dependencies for the GC
  static void markfunc(FXFoldingList* self);

  // Unregister objects that this folding list owns and is about to destroy
  static void unregisterOwnedObjects(FXFoldingList *pFoldingList);

  // Enumerate items
  static void enumerateItem(FXFoldingItem* item,FXObjectListOf<FXFoldingItem>& items);
  static void enumerateItems(FXFoldingItem* fm,FXFoldingItem* to,FXObjectListOf<FXFoldingItem>& items);

  // Destructor
  virtual ~FXRbFoldingList(){
    FXRbFoldingList::unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
