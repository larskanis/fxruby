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
 * $Id: FXRbTable.h 2303 2005-12-09 03:17:28Z lyle $
 ***********************************************************************/

#ifndef FXRBTABLE_H
#define FXRBTABLE_H

#define DECLARE_FXTABLEITEM_STUBS(klass,subklass) \
inline void klass ## _draw(const klass* self,const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_draw(table,dc,x,y,w,h); \
  } \
inline void klass ## _drawBorders(const klass* self,const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_drawBorders(table,dc,x,y,w,h); \
  } \
inline void klass ## _drawContent(const klass* self,const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_drawContent(table,dc,x,y,w,h); \
  } \
inline void klass ## _drawPattern(const klass* self,const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_drawPattern(table,dc,x,y,w,h); \
  } \
inline void klass ## _drawBackground(const klass* self,const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_drawBackground(table,dc,x,y,w,h); \
  } \
inline void klass ## _setText(klass* self,const FXString& text){ \
  self->klass::setText(text); \
  } \
inline FXString klass ## _getText(const klass* self){ \
  return self->klass::getText(); \
  } \
inline void klass ## _setIcon(klass* self,FXIcon* icn,FXbool owned){ \
  self->klass::setIcon(icn,owned); \
  } \
inline FXIcon* klass ## _getIcon(const klass* self){ \
  return self->klass::getIcon(); \
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
inline void klass ## _setJustify(klass* self,FXuint justify){ \
  self->klass::setJustify(justify); \
  } \
inline void klass ## _setIconPosition(klass* self,FXuint mode){ \
  self->klass::setIconPosition(mode); \
  } \
inline void klass ## _setBorders(klass* self,FXuint borders){ \
  self->klass::setBorders(borders); \
  } \
inline void klass ## _setStipple(klass* self,FXStipplePattern pattern){ \
  self->klass::setStipple(pattern); \
  } \
inline FXWindow* klass ## _getControlFor(klass* self,FXTable* table){ \
  return self->klass::getControlFor(table); \
  } \
inline void klass ## _setFromControl(klass* self,FXWindow* control){ \
  self->klass::setFromControl(control); \
  } \
inline FXint klass ## _getWidth(const klass* self,const FXTable* table){ \
  return self->klass::getWidth(table); \
  } \
inline FXint klass ## _getHeight(const klass* self,const FXTable* table){ \
  return self->klass::getHeight(table); \
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


#define IMPLEMENT_FXTABLEITEM_STUBS(klass,superklass) \
  void klass::draw(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    FXRbCallVoidMethod(this,rb_intern("draw"),table,dc,x,y,w,h); \
    } \
  void klass::public_draw(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::draw(table,dc,x,y,w,h); \
    } \
  void klass::drawBorders(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    FXRbCallVoidMethod(this,rb_intern("drawBorders"),table,dc,x,y,w,h); \
    } \
  void klass::public_drawBorders(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::drawBorders(table,dc,x,y,w,h); \
    } \
  void klass::drawContent(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    FXRbCallVoidMethod(this,rb_intern("drawContent"),table,dc,x,y,w,h); \
    } \
  void klass::public_drawContent(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::drawContent(table,dc,x,y,w,h); \
    } \
  void klass::drawPattern(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    FXRbCallVoidMethod(this,rb_intern("drawPattern"),table,dc,x,y,w,h); \
    } \
  void klass::public_drawPattern(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::drawPattern(table,dc,x,y,w,h); \
    } \
  void klass::drawBackground(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    FXRbCallVoidMethod(this,rb_intern("drawBackground"),table,dc,x,y,w,h); \
    } \
  void klass::public_drawBackground(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::drawBackground(table,dc,x,y,w,h); \
    } \
  void klass::setText(const FXString& txt){ \
    FXRbCallVoidMethod(this,rb_intern("setText"),txt); \
    } \
  FXString klass::getText() const { \
    return FXRbCallStringMethod(this,rb_intern("getText")); \
    } \
  void klass::setIcon(FXIcon* icn,FXbool owned){ \
    FXRbCallVoidMethod(this,rb_intern("setIcon"),icn,owned); \
    } \
  FXIcon* klass::getIcon() const { \
    return FXRbCallIconMethod(this,rb_intern("getIcon")); \
    } \
  void klass::setFocus(FXbool focus){ \
    FXRbCallVoidMethod(this,rb_intern("setFocus"),focus); \
    } \
  void klass::setSelected(FXbool selected){ \
    FXRbCallVoidMethod(this,rb_intern("setSelected"),selected); \
    } \
  void klass::setEnabled(FXbool enabled){ \
    FXRbCallVoidMethod(this,rb_intern("setEnabled"),enabled); \
    } \
  void klass::setDraggable(FXbool draggable){ \
    FXRbCallVoidMethod(this,rb_intern("setDraggable"),draggable); \
    } \
  void klass::setJustify(FXuint justify){ \
    FXRbCallVoidMethod(this,rb_intern("setJustify"),justify); \
    } \
  void klass::setIconPosition(FXuint mode){ \
    FXRbCallVoidMethod(this,rb_intern("setIconPosition"),mode); \
    } \
  void klass::setBorders(FXuint borders){ \
    FXRbCallVoidMethod(this,rb_intern("setBorders"),borders); \
    } \
  void klass::setStipple(FXStipplePattern pattern){ \
    FXRbCallVoidMethod(this,rb_intern("setStipple"),pattern); \
    } \
  FXWindow* klass::getControlFor(FXTable* table){ \
    return FXRbCallWindowMethod(this,rb_intern("getControlFor"),table); \
    } \
  void klass::setFromControl(FXWindow* control){ \
    FXRbCallVoidMethod(this,rb_intern("setFromControl"),control); \
    } \
  FXint klass::getWidth(const FXTable* table) const { \
    return FXRbCallIntMethod(this,rb_intern("getWidth"),table); \
    } \
  FXint klass::getHeight(const FXTable* table) const { \
    return FXRbCallIntMethod(this,rb_intern("getHeight"),table); \
    } \
  void klass::create(){ \
    FXRbCallVoidMethod(this,rb_intern("create")); \
    } \
  void klass::detach(){ \
    FXRbCallVoidMethod(this,rb_intern("detach")); \
    } \
  void klass::destroy(){ \
    FXRbCallVoidMethod(this,rb_intern("destroy")); \
    }


class FXRbTableItem : public FXTableItem {
  FXDECLARE(FXRbTableItem)
protected:
  FXRbTableItem(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbTableItemVirtuals.h"
public:
  // Is this table item owned by an FXTable yet?
  FXbool owned;
public:
  // Constructor
  FXRbTableItem(const FXString& text,FXIcon* ic=NULL,void* ptr=NULL) : FXTableItem(text,ic,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXTableItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXTableItem* self);

  // Destructor
  virtual ~FXRbTableItem(){
    FXRbUnregisterRubyObj(this);
    }
  };


#define DECLARE_FXTABLE_STUBS(klass,subklass) \
inline void klass ## _drawCell(klass* self,FXDC& dc,FXint sr,FXint er,FXint sc,FXint ec){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawCell(dc,sr,er,sc,ec); \
  } \
inline void klass ## _drawRange(klass* self,FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawRange(dc,rlo,rhi,clo,chi); \
  } \
inline void klass ## _drawHGrid(klass* self,FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawHGrid(dc,rlo,rhi,clo,chi); \
  } \
inline void klass ## _drawVGrid(klass* self,FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawVGrid(dc,rlo,rhi,clo,chi); \
  } \
inline void klass ## _drawContents(klass* self,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawContents(dc,x,y,w,h); \
  } \
inline FXTableItem* klass ## _createItem(klass* self,const FXString& text,FXIcon* icon,void* ptr){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  return dynamic_cast<subklass*>(self)->public_createItem(text,icon,ptr); \
  } \
inline void klass ## _setTableSize(klass* self,FXint nr,FXint nc,FXbool notify){ \
  FXint i,r,c; \
  if(nr<0 || nc<0) rb_raise(rb_eArgError,"numbers of rows and columns must be zero or greater"); \
  FXObjectListOf<FXTableItem> tableItems; \
  FXObjectListOf<FXHeaderItem> headerItems; \
  for(r=0;r<self->getNumRows();r++){ \
    for(c=0;c<self->getNumColumns();c++){ \
      tableItems.append(self->getItem(r,c)); \
      } \
    } \
  for(i=0;i<self->getRowHeader()->getNumItems();i++){ \
    headerItems.append(self->getRowHeader()->getItem(i)); \
    } \
  for(i=0;i<self->getColumnHeader()->getNumItems();i++){ \
    headerItems.append(self->getColumnHeader()->getItem(i)); \
    } \
  self->klass::setTableSize(nr,nc,notify); \
  for(i=0;i<tableItems.no();i++){ \
    FXRbUnregisterRubyObj(tableItems[i]); \
    } \
  for(i=0;i<headerItems.no();i++){ \
    FXRbUnregisterRubyObj(headerItems[i]); \
    } \
  } \
inline void klass ## _insertRows(klass* self,FXint row,FXint nr,FXbool notify){ \
  self->klass::insertRows(row,nr,notify); \
  } \
inline void klass ## _insertColumns(klass* self,FXint col,FXint nc,FXbool notify){ \
  self->klass::insertColumns(col,nc,notify); \
  } \
inline void klass ## _removeRows(klass* self,FXint row,FXint nr,FXbool notify){ \
  FXObjectListOf<FXTableItem> items; \
  for(FXint r=row;r<row+nr;r++){ \
    for(FXint c=0;c<self->getNumColumns();c++){ \
      items.append(self->getItem(r,c)); \
      } \
    } \
  self->klass::removeRows(row,nr,notify); \
  for(FXint i=0;i<items.no();i++){ \
    FXRbUnregisterRubyObj(items[i]); \
    } \
  } \
inline void klass ## _removeColumns(klass* self,FXint col,FXint nc,FXbool notify){ \
  FXObjectListOf<FXTableItem> items; \
  for(FXint c=col;c<col+nc;c++){ \
    for(FXint r=0;r<self->getNumRows();r++){ \
      items.append(self->getItem(r,c)); \
      } \
    } \
  self->klass::removeColumns(col,nc,notify); \
  for(FXint i=0;i<items.no();i++){ \
    FXRbUnregisterRubyObj(items[i]); \
    } \
  } \
inline FXTableItem* klass ## _extractItem(klass* self,FXint row,FXint col,FXbool notify){ \
  return self->klass::extractItem(row,col,notify); \
  } \
inline void klass ## _removeItem(klass* self,FXint row,FXint col,FXbool notify=FALSE){ \
  FXTableItem* item=self->getItem(row,col); \
  self->klass::removeItem(row,col,notify); \
  FXRbUnregisterRubyObj(item); \
  } \
inline void klass ## _removeRange(klass* self,FXint startrow,FXint startcol,FXint endrow,FXint endcol,FXbool notify){ \
  self->klass::removeRange(startrow,startcol,endrow,endcol,notify); \
  } \
inline void klass ## _clearItems(klass* self,FXbool notify){ \
  FXObjectListOf<FXTableItem> items; \
  for(FXint r=0;r<self->getNumRows();r++){ \
    for(FXint c=0;c<self->getNumColumns();c++){ \
      items.append(self->getItem(r,c)); \
      } \
    } \
  self->klass::clearItems(notify); \
  for(FXint i=0;i<items.no();i++){ \
    FXRbUnregisterRubyObj(items[i]); \
    } \
  } \
inline void klass ## _setColumnWidth(klass* self,FXint col,FXint cwidth){ \
  self->klass::setColumnWidth(col,cwidth); \
  } \
inline void klass ## _setRowHeight(klass* self,FXint row,FXint rheight){ \
  self->klass::setRowHeight(row,rheight); \
  } \
inline void klass ## _setCurrentItem(klass* self,FXint r,FXint c,FXbool notify=FALSE){ \
  self->klass::setCurrentItem(r,c,notify); \
  } \
inline FXbool klass ## _selectRow(klass* self,FXint row,FXbool notify){ \
  return self->klass::selectRow(row,notify); \
  } \
inline FXbool klass ## _selectColumn(klass* self,FXint col,FXbool notify){ \
  return self->klass::selectColumn(col,notify); \
  } \
inline FXbool klass ## _selectRange(klass* self,FXint sr,FXint er,FXint sc,FXint ec,FXbool notify){ \
  return self->klass::selectRange(sr,er,sc,ec,notify); \
  } \
inline FXbool klass ## _extendSelection(klass* self,FXint r,FXint c,FXbool notify){ \
  return self->klass::extendSelection(r,c,notify); \
  } \
inline FXbool klass ## _killSelection(klass* self,FXbool notify){ \
  return self->klass::killSelection(notify); \
  } \
inline void klass ## _startInput(klass* self,FXint row,FXint col){ \
  self->klass::startInput(row,col); \
  } \
inline void klass ## _cancelInput(klass* self){ \
  self->klass::cancelInput(); \
  } \
inline void klass ## _acceptInput(klass* self,FXbool notify){ \
  self->klass::acceptInput(notify); \
  } \
inline void klass ## _makePositionVisible(klass* self,FXint r,FXint c){ \
  self->klass::makePositionVisible(r,c); \
  } \
inline FXbool klass ## _enableItem(klass* self,FXint r,FXint c){ \
  return self->klass::enableItem(r,c); \
  } \
inline FXbool klass ## _disableItem(klass* self,FXint r,FXint c){ \
  return self->klass::disableItem(r,c); \
  }


#define IMPLEMENT_FXTABLE_STUBS(klass,superklass) \
  void klass::drawCell(FXDC& dc,FXint sr,FXint er,FXint sc,FXint ec){ \
    FXRbCallVoidMethod(this,rb_intern("drawCell"),dc,sr,er,sc,ec); \
    } \
  void klass::public_drawCell(FXDC& dc,FXint sr,FXint er,FXint sc,FXint ec){ \
    superklass::drawCell(dc,sr,er,sc,ec); \
    } \
  void klass::drawRange(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
    FXRbCallVoidMethod(this,rb_intern("drawRange"),dc,rlo,rhi,clo,chi); \
    } \
  void klass::public_drawRange(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
    superklass::drawRange(dc,rlo,rhi,clo,chi); \
    } \
  void klass::drawHGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
    FXRbCallVoidMethod(this,rb_intern("drawHGrid"),dc,rlo,rhi,clo,chi); \
    } \
  void klass::public_drawHGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
    superklass::drawHGrid(dc,rlo,rhi,clo,chi); \
    } \
  void klass::drawVGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
    FXRbCallVoidMethod(this,rb_intern("drawVGrid"),dc,rlo,rhi,clo,chi); \
    } \
  void klass::public_drawVGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi){ \
    superklass::drawVGrid(dc,rlo,rhi,clo,chi); \
    } \
  void klass::drawContents(FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
    FXRbCallVoidMethod(this,rb_intern("drawContents"),dc,x,y,w,h); \
    } \
  void klass::public_drawContents(FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
    superklass::drawContents(dc,x,y,w,h); \
    } \
  FXTableItem* klass::createItem(const FXString& text,FXIcon* icon,void* ptr){ \
    return FXRbCallTableItemMethod(this,rb_intern("createItem"),text,icon,ptr); \
    } \
  FXTableItem* klass::public_createItem(const FXString& text,FXIcon* icon,void* ptr){ \
    return superklass::createItem(text,icon,ptr); \
    } \
  void klass::setTableSize(FXint nr,FXint nc,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("setTableSize"),nr,nc,notify); \
    } \
  void klass::insertRows(FXint row,FXint nr,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("insertRows"),row,nr,notify); \
    } \
  void klass::insertColumns(FXint col,FXint nc,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("insertColumns"),col,nc,notify); \
    } \
  void klass::removeRows(FXint row,FXint nr,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("removeRows"),row,nr,notify); \
    } \
  void klass::removeColumns(FXint col,FXint nc,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("removeColumns"),col,nc,notify); \
    } \
  FXTableItem* klass::extractItem(FXint row,FXint col,FXbool notify){ \
    return FXRbCallTableItemMethod(this,rb_intern("extractItem"),row,col,notify); \
    } \
  void klass::removeItem(FXint row,FXint col,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("removeItem"),row,col,notify); \
    } \
  void klass::removeRange(FXint startrow,FXint startcol,FXint endrow,FXint endcol,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("removeRange"),startrow,startcol,endrow,endcol,notify); \
    } \
  void klass::clearItems(FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("clearItems"),notify); \
    } \
  void klass::setColumnWidth(FXint col,FXint cwidth){ \
    FXRbCallVoidMethod(this,rb_intern("setColumnWidth"),col,cwidth); \
    } \
  void klass::setRowHeight(FXint row,FXint rheight){ \
    FXRbCallVoidMethod(this,rb_intern("setRowHeight"),row,rheight); \
    } \
  void klass::setCurrentItem(FXint r,FXint c,FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("setCurrentItem"),r,c,notify); \
    } \
  FXbool klass::selectRow(FXint row,FXbool notify){ \
    return FXRbCallBoolMethod(this,rb_intern("selectRow"),row,notify); \
    } \
  FXbool klass::selectColumn(FXint col,FXbool notify){ \
    return FXRbCallBoolMethod(this,rb_intern("selectColumn"),col,notify); \
    } \
  FXbool klass::selectRange(FXint sr,FXint er,FXint sc,FXint ec,FXbool notify){ \
    return FXRbCallBoolMethod(this,rb_intern("selectRange"),sr,er,sc,ec,notify); \
    } \
  FXbool klass::extendSelection(FXint r,FXint c,FXbool notify){ \
    return FXRbCallBoolMethod(this,rb_intern("extendSelection"),r,c,notify); \
    } \
  FXbool klass::killSelection(FXbool notify){ \
    return FXRbCallBoolMethod(this,rb_intern("killSelection"),notify); \
    } \
  void klass::startInput(FXint row,FXint col){ \
    FXRbCallVoidMethod(this,rb_intern("startInput"),row,col); \
    } \
  void klass::cancelInput(){ \
    FXRbCallVoidMethod(this,rb_intern("cancelInput")); \
    } \
  void klass::acceptInput(FXbool notify){ \
    FXRbCallVoidMethod(this,rb_intern("acceptInput"),notify); \
    } \
  void klass::makePositionVisible(FXint r,FXint c){ \
    FXRbCallVoidMethod(this,rb_intern("makePositionVisible"),r,c); \
    } \
  FXbool klass::enableItem(FXint r,FXint c){ \
    return FXRbCallBoolMethod(this,rb_intern("enableItem"),r,c); \
    } \
  FXbool klass::disableItem(FXint r,FXint c){ \
    return FXRbCallBoolMethod(this,rb_intern("disableItem"),r,c); \
    }

class FXRbTable : public FXTable {
  FXDECLARE(FXRbTable)
protected:
  FXRbTable(){}
#include "FXRbObjectVirtuals.h"
#include "FXRbIdVirtuals.h"
#include "FXRbDrawableVirtuals.h"
#include "FXRbWindowVirtuals.h"
#include "FXRbScrollAreaVirtuals.h"
#include "FXRbTableVirtuals.h"
public:
  /// Make new table with nr visible rows and nc visible columns; the table
  /// is initially empty, i.e. contains no cells (nrows=0, ncols=0)
  FXRbTable(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_MARGIN,FXint pr=DEFAULT_MARGIN,FXint pt=DEFAULT_MARGIN,FXint pb=DEFAULT_MARGIN) : FXTable(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb){}

  // Mark dependencies for the GC
  static void markfunc(FXTable* self);

  // Unregister objects that this table owns and is about to destroy
  static void unregisterOwnedObjects(FXTable *pTable);

  // Destructor
  virtual ~FXRbTable(){
    FXRbTable::unregisterOwnedObjects(this);
    FXRbUnregisterRubyObj(corner); // created by FXScrollArea; must do this here; no public accessor method for it
    FXRbUnregisterRubyObj(cornerButton); // must do this here; no public accessor method for it
    FXRbUnregisterRubyObj(this);
    }
  };

#endif
