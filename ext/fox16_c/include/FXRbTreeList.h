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
 * $Id: FXRbTreeList.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBTREELIST_H
#define FXRBTREELIST_H

#define DECLARE_FXTREEITEM_STUBS(klass,subklass) \
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
inline FXint klass ## _getWidth(const klass* self,const FXTreeList* list){ \
  return self->klass::getWidth(list); \
  } \
inline FXint klass ## _getHeight(const klass* self,const FXTreeList* list){ \
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


#define IMPLEMENT_FXTREEITEM_STUBS(klass,superklass) \
  void klass::setText(const FXString& txt){ \
    FXRbCallVoidMethod(this,"setText",txt); \
    } \
  void klass::setOpenIcon(FXIcon* icn,FXbool owned){ \
    FXRbCallVoidMethod(this,"setOpenIcon",icn,owned); \
    } \
  void klass::setClosedIcon(FXIcon* icn,FXbool owned){ \
    FXRbCallVoidMethod(this,"setClosedIcon",icn,owned); \
    } \
  void klass::setFocus(FXbool focus){ \
    if(NIL_P(FXRbGetRubyObj(this,false))){ \
      superklass::setFocus(focus); \
      } \
    else{ \
      FXRbCallVoidMethod(this,"setFocus",focus); \
      } \
    } \
  void klass::setSelected(FXbool selected){ \
    FXRbCallVoidMethod(this,"setSelected",selected); \
    } \
  void klass::setOpened(FXbool opened){ \
    FXRbCallVoidMethod(this,"setOpened",opened); \
    } \
  void klass::setExpanded(FXbool expanded){ \
    FXRbCallVoidMethod(this,"setExpanded",expanded); \
    } \
  void klass::setEnabled(FXbool enabled){ \
    FXRbCallVoidMethod(this,"setEnabled",enabled); \
    } \
  void klass::setDraggable(FXbool draggable){ \
    FXRbCallVoidMethod(this,"setDraggable",draggable); \
    } \
  FXint klass::getWidth(const FXTreeList* list) const { \
    return FXRbCallIntMethod(this,"getWidth",list); \
    } \
  FXint klass::getHeight(const FXTreeList* list) const { \
    return FXRbCallIntMethod(this,"getHeight",list); \
    } \
  void klass::create(){ \
    FXRbCallVoidMethod(this,"create"); \
    } \
  void klass::detach(){ \
    FXRbCallVoidMethod(this,"detach"); \
    } \
  void klass::destroy(){ \
    FXRbCallVoidMethod(this,"destroy"); \
    }


class FXRbTreeItem : public FXTreeItem {
  FXDECLARE(FXRbTreeItem)
protected:
  FXRbTreeItem(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbTreeItemVirtuals.h"
public:
  // Is this tree item owned by an FXTreeList yet?
  FXbool owned;
public:
  // Constructor
  FXRbTreeItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL) : FXTreeItem(text,oi,ci,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXTreeItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXTreeItem* self);

  // Destructor
  virtual ~FXRbTreeItem(){
    FXRbUnregisterRubyObj(this);
    }
  };


#define DECLARE_FXTREELIST_STUBS(klass) \
inline FXbool klass ## _selectItem(klass* self,FXTreeItem* item,FXbool notify){ \
  return self->klass::selectItem(item,notify); \
  } \
inline FXbool klass ## _deselectItem(klass* self,FXTreeItem* item,FXbool notify){ \
  return self->klass::deselectItem(item,notify); \
  } \
inline FXbool klass ## _toggleItem(klass* self,FXTreeItem* item,FXbool notify){ \
  return self->klass::toggleItem(item,notify); \
  } \
inline FXbool klass ## _extendSelection(klass* self,FXTreeItem* item,FXbool notify){ \
  return self->klass::extendSelection(item,notify); \
  } \
inline FXbool klass ## _killSelection(klass* self,FXbool notify){ \
  return self->klass::killSelection(notify); \
  } \
inline FXbool klass ## _openItem(klass* self,FXTreeItem* item,FXbool notify){ \
  return self->klass::openItem(item,notify); \
  } \
inline FXbool klass ## _closeItem(klass* self,FXTreeItem* item,FXbool notify){ \
  return self->klass::closeItem(item,notify); \
  } \
inline FXbool klass ## _collapseTree(klass* self,FXTreeItem* tree,FXbool notify){ \
  return self->klass::collapseTree(tree,notify); \
  } \
inline FXbool klass ## _expandTree(klass* self,FXTreeItem* tree,FXbool notify){ \
  return self->klass::expandTree(tree,notify); \
  } \
inline void klass ## _setCurrentItem(klass* self,FXTreeItem* item,FXbool notify){ \
  self->klass::setCurrentItem(item,notify); \
  } \
inline FXTreeItem* klass ## _getItemAt(const klass* self,FXint x,FXint y){ \
  return self->klass::getItemAt(x,y); \
  } \
inline void klass ## _makeItemVisible(klass* self,FXTreeItem* item){ \
  self->klass::makeItemVisible(item); \
  } \
inline FXbool klass ## _enableItem(klass* self,FXTreeItem* item){ \
  return self->klass::enableItem(item); \
  } \
inline FXbool klass ## _disableItem(klass* self,FXTreeItem* item){ \
  return self->klass::disableItem(item); \
  }


#define IMPLEMENT_FXTREELIST_STUBS(cls) \
  FXbool cls::selectItem(FXTreeItem* item,FXbool notify){ \
    return FXRbCallBoolMethod(this,"selectItem",item,notify); \
    } \
  FXbool cls::deselectItem(FXTreeItem* item,FXbool notify){ \
    return FXRbCallBoolMethod(this,"deselectItem",item,notify); \
    } \
  FXbool cls::toggleItem(FXTreeItem* item,FXbool notify){ \
    return FXRbCallBoolMethod(this,"toggleItem",item,notify); \
    } \
  FXbool cls::extendSelection(FXTreeItem* item,FXbool notify){ \
    return FXRbCallBoolMethod(this,"extendSelection",item,notify); \
    } \
  FXbool cls::killSelection(FXbool notify){ \
    return FXRbCallBoolMethod(this,"killSelection",notify); \
    } \
  FXbool cls::openItem(FXTreeItem* item,FXbool notify){ \
    return FXRbCallBoolMethod(this,"openItem",item,notify); \
    } \
  FXbool cls::closeItem(FXTreeItem* item,FXbool notify){ \
    return FXRbCallBoolMethod(this,"closeItem",item,notify); \
    } \
  FXbool cls::collapseTree(FXTreeItem* tree,FXbool notify){ \
    return FXRbCallBoolMethod(this,"collapseTree",tree,notify); \
    } \
  FXbool cls::expandTree(FXTreeItem* tree,FXbool notify){ \
    return FXRbCallBoolMethod(this,"expandTree",tree,notify); \
    } \
  void cls::setCurrentItem(FXTreeItem* item,FXbool notify){ \
    FXRbCallVoidMethod(this,"setCurrentItem",item,notify); \
    } \
  FXTreeItem* cls::getItemAt(FXint x,FXint y) const { \
    return FXRbCallTreeItemMethod(this,"getItemAt",x,y); \
    } \
  void cls::makeItemVisible(FXTreeItem* item) { \
    FXRbCallVoidMethod(this,"makeItemVisible",item); \
    } \
  FXbool cls::enableItem(FXTreeItem* item){ \
    return FXRbCallBoolMethod(this,"enableItem",item); \
    } \
  FXbool cls::disableItem(FXTreeItem* item){ \
    return FXRbCallBoolMethod(this,"disableItem",item); \
    }


class FXRbTreeList : public FXTreeList {
  FXDECLARE(FXRbTreeList)
protected:
  FXRbTreeList(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbScrollAreaVirtuals.h"
#include "FXRbTreeListVirtuals.h"
public:
  /// Construct a new, initially empty tree list
  FXRbTreeList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TREELIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXTreeList(p,tgt,sel,opts,x,y,w,h){
    setSortFunc(FXRbTreeList::sortFunc);
    }

  // Sort function stand-in
  static FXint sortFunc(const FXTreeItem* a,const FXTreeItem* b);

  // Mark dependencies for the GC
  static void markfunc(FXTreeList* self);

  // Unregister objects that this tree list owns and is about to destroy
  static void unregisterOwnedObjects(FXTreeList *pTreeList);

  // Enumerate items
  static void enumerateItem(FXTreeItem* item,FXObjectListOf<FXTreeItem>& items);
  static void enumerateItems(FXTreeItem* fm,FXTreeItem* to,FXObjectListOf<FXTreeItem>& items);

  // Destructor
  virtual ~FXRbTreeList(){
    FXRbTreeList::unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
