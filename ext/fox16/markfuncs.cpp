/***********************************************************************
 * $Id: markfuncs.cpp 2928 2008-12-29 19:16:57Z lyle $
 ***********************************************************************/

#include "FXRbCommon.h"

#ifdef MARK
#undef MARK
#endif
#define MARK(p) rb_gc_mark(reinterpret_cast<VALUE>((p)))


template<class BASECLASS,class SUBCLASS>
static void delete_if_not_owned(BASECLASS* self,SUBCLASS*){
  if(self!=0){
    if(!FXRbIsBorrowed(self)){
      if(self->isMemberOf(FXMETACLASS(SUBCLASS))){
        if(!dynamic_cast<SUBCLASS*>(self)->owned){
          delete self; // also unregisters it
          }
	}
      }
    FXRbUnregisterRubyObj(self);
    }
  }


template<class BASECLASS,class SUBCLASS>
static void delete_if_not_owned_by_app(BASECLASS* self,SUBCLASS*){
  if(self!=0){
    if(!FXRbIsBorrowed(self)){
      if(self->isMemberOf(FXMETACLASS(SUBCLASS))){
        if(!dynamic_cast<SUBCLASS*>(self)->ownedByApp){
          delete self; // also unregisters it
          }
	}
      }
    FXRbUnregisterRubyObj(self);
    }
  }


// FIXME: How to get to the target objects stored in the accelerator
// table? This is currently private (not protected) data for the class.
void FXRbAccelTable::markfunc(FXAccelTable* accelTable){
  FXRbObject::markfunc(accelTable);
  }


// Mark dependencies for the GC
void FXRbObject::markfunc(FXObject* obj){
  FXTRACE((100,"%s::markfunc(%p)\n",obj?obj->getClassName():"FXRbObject",obj));
  }


void FXRbObject::freefunc(FXObject* self){
  if(self!=0){
    // Unregister, but don't destroy, borrowed references
    if(FXRbIsBorrowed(self)){
      FXRbUnregisterRubyObj(self);
      return;
      }

    const FXchar* classname=self->getClassName();
    FXASSERT(classname!=0);
    FXASSERT(strlen(classname)>3);
    if(classname[0]=='F' && classname[1]=='X' && classname[2]=='R' && classname[3]=='b'){
      delete self;
      }
    else{
      FXRbUnregisterRubyObj(self);
      }
    }
  }

void FXRbIconSource::markfunc(FXIconSource* iconSource){
  FXRbObject::markfunc(iconSource);
  }
  
void FXRbTranslator::markfunc(FXTranslator* translator){
  FXRbObject::markfunc(translator);
  if(translator){
    FXRbGcMark(translator->getApp());
    FXRbGcMark(translator->getTextCodec());
    }
  }

void FXRbBMPIcon::markfunc(FXBMPIcon *icon){
  FXRbIcon::markfunc(icon);
  }


void FXRbIcon::markfunc(FXIcon* icon){
  FXRbImage::markfunc(icon);
  }


void FXRbImage::markfunc(FXImage* image){
  FXRbDrawable::markfunc(image);
  }


void FXRbBMPImage::markfunc(FXBMPImage* image){
  FXRbImage::markfunc(image);
  }


void FXRbBitmap::markfunc(FXBitmap* bitmap){
  FXRbDrawable::markfunc(bitmap);
  }


void FXRbButton::markfunc(FXButton* btn){
  FXRbLabel::markfunc(btn);
  }


void FXRbKnob::markfunc(FXKnob* self){
  FXRbFrame::markfunc(self);
  }


void FXRbLabel::markfunc(FXLabel* self){
  FXRbFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    FXRbGcMark(self->getIcon());
    }
  }


void FXRbFrame::markfunc(FXFrame* frame){
  FXRbWindow::markfunc(frame);
  }

void FXRb7Segment::markfunc(FX7Segment* seg){
  FXRbFrame::markfunc(seg);
  }

void FXRbDockHandler::markfunc(FXDockHandler *dockhandler){
  FXRbFrame::markfunc(dockhandler);
  }

void FXRbDockTitle::markfunc(FXDockTitle *self){
  FXRbDockHandler::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }

void FXRbDrawable::markfunc(FXDrawable* drawable){
  FXRbId::markfunc(drawable);
  if(drawable) FXRbGcMark(drawable->getVisual());
  }


void FXRbId::markfunc(FXId* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getApp());
    if(self->getUserData()) MARK(self->getUserData());
    }
  }


void FXRbCanvas::markfunc(FXCanvas* canvas){
  FXRbWindow::markfunc(canvas);
  }


void FXRbCheckButton::markfunc(FXCheckButton* cb){
  FXRbLabel::markfunc(cb);
  }


void FXRbColorDialog::markfunc(FXColorDialog* dlg){
  FXRbDialogBox::markfunc(dlg);
  }

void FXRbChoiceBox::markfunc(FXChoiceBox* box){
  FXRbDialogBox::markfunc(box);
  }

void FXRbWindow::markfunc(FXWindow* self){
  FXRbDrawable::markfunc(self);
  if(self){
    FXRbGcMark(self->getParent());
    FXRbGcMark(self->getOwner());
    FXRbGcMark(self->getShell());
    FXRbGcMark(self->getRoot());
    // FXRbGcMark(self->getNext());
    // FXRbGcMark(self->getPrev());
    FXRbGcMark(self->getFocus());
    FXRbGcMark(self->getTarget());
    FXRbGcMark(self->getAccelTable());
    FXRbGcMark(self->getDefaultCursor());
    FXRbGcMark(self->getDragCursor());

    // Mark child windows
    register FXWindow* child=self->getFirst();
    while(child!=NULL){
      FXRbGcMark(child);
      child=child->getNext();
      }
    }
  }


void FXRbDialogBox::markfunc(FXDialogBox* dlg){
  FXRbTopWindow::markfunc(dlg);
  }


void FXRbTopWindow::markfunc(FXTopWindow* top){
  FXRbShell::markfunc(top);
  if(top){
    FXRbGcMark(top->getIcon());
    FXRbGcMark(top->getMiniIcon());
    }
  }


void FXRbShell::markfunc(FXShell* shell){
  FXRbComposite::markfunc(shell);
  }


void FXRbComposite::markfunc(FXComposite* c){
  FXRbWindow::markfunc(c);
  }


void FXRbColorSelector::markfunc(FXColorSelector* cs){
  FXRbPacker::markfunc(cs);
  }


void FXRbPacker::markfunc(FXPacker* packer){
  FXRbComposite::markfunc(packer);
  }

void FXRbDockBar::markfunc(FXDockBar* dockbar){
  FXRbPacker::markfunc(dockbar);
  }

void FXRbDockSite::markfunc(FXDockSite* dockSite){
  FXRbPacker::markfunc(dockSite);
  }

void FXRbSpring::markfunc(FXSpring* self){
  FXRbPacker::markfunc(self);
  }


void FXRbHorizontalFrame::markfunc(FXHorizontalFrame* self){
  FXRbPacker::markfunc(self);
  }


void FXRbVerticalFrame::markfunc(FXVerticalFrame* self){
  FXRbPacker::markfunc(self);
  }


void FXRbGroupBox::markfunc(FXGroupBox* self){
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbColorWell::markfunc(FXColorWell* cw){
  FXRbFrame::markfunc(cw);
  }


void FXRbComboBox::markfunc(FXComboBox* self){
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    for(FXint i=0; i<self->getNumItems(); i++){
      if(self->getItemData(i))
        MARK(self->getItemData(i));
      }
    }
  }


void FXRbCursor::markfunc(FXCursor* cursor){
  FXRbId::markfunc(cursor);
  }


void FXRbCursor::freefunc(FXCursor* self){
  delete_if_not_owned_by_app(self,reinterpret_cast<FXRbCursor*>(0));
  }


void FXRbApp::markfunc(FXApp *self){
  FXRbObject::markfunc(self);
  if(self){
    // Visuals
    FXRbGcMark(self->getMonoVisual());
    FXRbGcMark(self->getDefaultVisual());

    // Fonts
    FXRbGcMark(self->getNormalFont());

    // Cursors
    FXRbGcMark(self->getWaitCursor());
    FXRbGcMark(self->getDefaultCursor(DEF_ARROW_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_RARROW_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_TEXT_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_HSPLIT_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_VSPLIT_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_XSPLIT_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_SWATCH_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_MOVE_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DRAGH_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DRAGV_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DRAGTL_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DRAGBR_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DRAGTR_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DRAGBL_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DNDSTOP_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DNDCOPY_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DNDMOVE_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_DNDLINK_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_CROSSHAIR_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_CORNERNE_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_CORNERNW_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_CORNERSE_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_CORNERSW_CURSOR));
    FXRbGcMark(self->getDefaultCursor(DEF_ROTATE_CURSOR));
  
    // Other windows
    FXRbGcMark(self->getFocusWindow());
    FXRbGcMark(self->getCursorWindow());
  
    /**
     * Root window is a special case; popups (like FXTooltip) can be created
     * without an "owner" by passing FXApp as the first argument to their
     * constructor, but in fact the "owner" of these window is the root window.
     * So unless we invoke FXRbRootWindow's mark function here, unowned windows
     * like tooltips may get garbage-collected prematurely.
     */
    if(self->getRootWindow()){
      FXRbGcMark(self->getRootWindow());
      FXRbRootWindow::markfunc(self->getRootWindow());
      }
  
    // Registry
    FXRbGcMark(&(self->reg()));

    // Timers, chores and signals are recycled and should never be destroyed
    }
  }


void FXRbArrowButton::markfunc(FXArrowButton *btn){
  FXRbFrame::markfunc(btn);
  }


void FXRbDataTarget::markfunc(FXDataTarget* obj){
  FXRbObject::markfunc(obj);
  }


void FXRbMainWindow::markfunc(FXMainWindow* obj){
  FXRbTopWindow::markfunc(obj);
  }


void FXRbTreeItem::markfunc(FXTreeItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getParent());
    FXRbGcMark(self->getNext());
    FXRbGcMark(self->getPrev());
    for(FXTreeItem* item=self->getFirst(); item; item=item->getNext()){
      FXRbGcMark(item);
      FXRbTreeItem::markfunc(item);
      }
    FXRbGcMark(self->getBelow());
    FXRbGcMark(self->getAbove());
    FXRbGcMark(self->getOpenIcon());
    FXRbGcMark(self->getClosedIcon());
    if(self->getData())
      MARK(self->getData());
    }
  }


void FXRbTreeItem::freefunc(FXTreeItem* self){
  if(self!=0){
    if(!FXRbIsBorrowed(self)){
      if(self->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        FXRbTreeItem* treeItem=dynamic_cast<FXRbTreeItem*>(self);
        FXASSERT(treeItem);
        FXTreeList* treeList=dynamic_cast<FXTreeList*>(treeItem->owner);
        if(treeList){
          FXRbUnregisterRubyObj(self); // MAYBE
          treeList->removeItem(self,TRUE);
          }
        else{
          FXTreeListBox* treeListBox=dynamic_cast<FXTreeListBox*>(treeItem->owner);
          if(treeListBox){
            treeListBox->removeItem(self);
            }
          }
	}
      }
    FXRbUnregisterRubyObj(self);
    }
  }


void FXRbTreeList::markfunc(FXTreeList* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    for(FXTreeItem* item=self->getFirstItem(); item; item=item->getNext()){
      FXRbGcMark(item);
      FXRbTreeItem::markfunc(item);
      }
    FXRbGcMark(self->getFont());
    }
  }


void FXRbFoldingItem::markfunc(FXFoldingItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getParent());
    FXRbGcMark(self->getNext());
    FXRbGcMark(self->getPrev());
    for(FXFoldingItem* item=self->getFirst(); item; item=item->getNext()){
      FXRbGcMark(item);
      FXRbFoldingItem::markfunc(item);
      }
    FXRbGcMark(self->getBelow());
    FXRbGcMark(self->getAbove());
    FXRbGcMark(self->getOpenIcon());
    FXRbGcMark(self->getClosedIcon());
    if(self->getData())
      MARK(self->getData());
    }
  }


void FXRbFoldingItem::freefunc(FXFoldingItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbFoldingItem*>(0));
  }


void FXRbFoldingList::markfunc(FXFoldingList* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    for(FXFoldingItem* item=self->getFirstItem(); item; item=item->getNext()){
      FXRbGcMark(item);
      FXRbFoldingItem::markfunc(item);
      }
    FXRbGcMark(self->getFont());
    }
  }


void FXRbListItem::markfunc(FXListItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getIcon());
    if(self->getData())
      MARK(self->getData());
    }
  }


void FXRbListItem::freefunc(FXListItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbListItem*>(0));
  }


void FXRbColorItem::markfunc(FXColorItem* self){
  FXRbListItem::markfunc(self);
  }


void FXRbColorItem::freefunc(FXColorItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbColorItem*>(0));
  }


void FXRbList::markfunc(FXList* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    for(FXint i=0;i<self->getNumItems();i++){
      FXListItem* item=self->getItem(i);
      FXRbGcMark(item);
      FXRbListItem::markfunc(item);
      if(self->getItemData(i))
        MARK(self->getItemData(i));
      }
    FXRbGcMark(self->getFont());
    }
  }


void FXRbColorList::markfunc(FXColorList* self){
  FXRbList::markfunc(self);
  }

  
void FXRbTableItem::markfunc(FXTableItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getIcon());
    if(self->getData())
      MARK(self->getData());
    }
  }


void FXRbTableItem::freefunc(FXTableItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbTableItem*>(0));
  }


void FXRbTable::markfunc(FXTable* self){
  register FXTableItem* item;
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    FXRbGcMark(self->getRowHeaderFont());
    FXRbGcMark(self->getColumnHeaderFont());
    for(FXint row=0;row<self->getNumRows();row++){
      for(FXint col=0;col<self->getNumColumns();col++){
        item=self->getItem(row,col);
        FXRbGcMark(item);
        FXRbGcMark(self->getItemIcon(row,col));
        if(self->getItemData(row,col))
          MARK(self->getItemData(row,col));
        }
      }
    }
  }


void FXRbHeaderItem::markfunc(FXHeaderItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getIcon());
    if(self->getData())
      MARK(self->getData());
    }
  }


void FXRbHeaderItem::freefunc(FXHeaderItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbHeaderItem*>(0));
  }


void FXRbHeader::markfunc(FXHeader* self){
  FXRbFrame::markfunc(self);
  if(self){
    for(FXint i=0;i<self->getNumItems();i++){
      FXHeaderItem* item=self->getItem(i);
      FXRbGcMark(item);
      FXRbHeaderItem::markfunc(item);
      if(item->getData())
        MARK(item->getData());
      }
    FXRbGcMark(self->getFont());
    }
  }


void FXRbIconItem::markfunc(FXIconItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getBigIcon());
    FXRbGcMark(self->getMiniIcon());
    if(self->getData())
      MARK(self->getData());
    }
  }


void FXRbIconItem::freefunc(FXIconItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbIconItem*>(0));
  }


void FXRbIconList::markfunc(FXIconList* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->getHeader());
    for(FXint i=0;i<self->getNumItems();i++){
      FXIconItem* item=self->getItem(i);
      FXRbGcMark(item);
      FXRbIconItem::markfunc(item);
      if(self->getItemData(i))
        MARK(self->getItemData(i));
      }
    FXRbGcMark(self->getFont());
    }
  }


void FXRbDelegator::markfunc(FXDelegator* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getDelegate());
    }
  }


void FXRbDebugTarget::markfunc(FXDebugTarget* self){
  FXRbObject::markfunc(self);
  }


void FXRbDict::markfunc(FXDict* self){
  FXRbObject::markfunc(self);
  }


void FXRbSettings::markfunc(FXSettings* self){
  FXRbDict::markfunc(self);
  }


void FXRbRegistry::markfunc(FXRegistry* self){
  FXRbSettings::markfunc(self);
  }


void FXRbStringDict::markfunc(FXStringDict* self){
  FXRbDict::markfunc(self);
  }


void FXRbRecentFiles::markfunc(FXRecentFiles* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getTarget());
    }
  }


void FXRbScrollArea::markfunc(FXScrollArea* self){
  FXRbComposite::markfunc(self);
  if(self){
    FXRbGcMark(self->horizontalScrollBar());
    FXRbGcMark(self->verticalScrollBar());
    }
  }


void FXRbDocument::markfunc(FXDocument* self){
  FXRbObject::markfunc(self);
  }


void FXRbGLContext::markfunc(FXGLContext* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->getVisual());
    }
  }


void FXRbGLObject::markfunc(FXGLObject* self){
  FXRbObject::markfunc(self);
  }


void FXRbFont::markfunc(FXFont* self){
  FXRbId::markfunc(self);
  }


void FXRbFont::freefunc(FXFont *self){
  delete_if_not_owned_by_app(self,reinterpret_cast<FXRbFont*>(0));
  }


void FXRbIconDict::markfunc(FXIconDict* self){
  FXRbDict::markfunc(self);
  if(self){
    FXRbGcMark(self->getIconSource());
    if(self->no()>0){
      FXint pos=self->first();
      FXint last=self->last();
      while(pos<=last){
        const FXchar* name=self->key(pos);
        FXIcon* icon=self->find(name);
        FXRbGcMark(icon);
        pos=self->next(pos);
        }
      }
    }
  }


void FXRbFileDict::markfunc(FXFileDict* self){
  FXRbDict::markfunc(self);
  FXRbGcMark(self->getSettings());
  if(self){
    if(self->no()>0){
      FXint pos=self->first();
      FXint last=self->last();
      while(pos<=last){
        const FXchar* key=self->key(pos);
        FXFileAssoc* assoc=self->find(key);
        FXRbGcMark(assoc);
        pos=self->next(pos);
        }
      }
    }
  }


void FXRbDial::markfunc(FXDial* self){
  FXTRACE((100,"FXRbDial::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  }


void FXRbDragCorner::markfunc(FXDragCorner* self){
  FXTRACE((100,"FXRbDragCorner::markfunc() %p\n",self));
  FXRbWindow::markfunc(self);
  }


void FXRbDirItem::markfunc(FXDirItem* self){
  FXTRACE((100,"FXRbDirItem::markfunc() %p\n",self));
  FXRbTreeItem::markfunc(self);
  if(self){
    FXRbGcMark(self->getAssoc());
    }
  }


void FXRbDirItem::freefunc(FXDirItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbDirItem*>(0));
  }

void FXRbDirList::markfunc(FXDirList* self){
  FXTRACE((100,"FXRbDirList::markfunc() %p\n",self));
  FXRbTreeList::markfunc(self);
  if(self){
    FXRbGcMark(self->getAssociations());
    }
  }


void FXRb4Splitter::markfunc(FX4Splitter* self){
  FXTRACE((100,"FXRb4Splitter::markfunc() %p\n",self));
  FXRbComposite::markfunc(self);
  if(self){
    FXRbGcMark(self->getTopLeft());
    FXRbGcMark(self->getTopRight());
    FXRbGcMark(self->getBottomLeft());
    FXRbGcMark(self->getBottomRight());
    }
  }


void FXRbFileItem::markfunc(FXFileItem* self){
  FXTRACE((100,"FXRbFileItem::markfunc() %p\n",self));
  FXRbIconItem::markfunc(self);
  if(self){
    FXRbGcMark(self->getAssoc());
    }
  }


void FXRbFileItem::freefunc(FXFileItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbFileItem*>(0));
  }


void FXRbFileList::markfunc(FXFileList* self){
  FXTRACE((100,"FXRbFileList::markfunc() %p\n",self));
  FXRbIconList::markfunc(self);
  if(self){
    FXRbGcMark(self->getAssociations());
    for(FXint i=0;i<self->getNumItems();i++){
      FXFileAssoc* assoc=self->getItemAssoc(i);
      FXRbGcMark(assoc);
      }
    }
  }


void FXRbDirBox::markfunc(FXDirBox* self){
  FXTRACE((100,"FXRbDirBox::markfunc() %p\n",self));
  FXRbTreeListBox::markfunc(self);
  }


void FXRbDriveBox::markfunc(FXDriveBox* self){
  FXTRACE((100,"FXRbDriveBox::markfunc() %p\n",self));
  FXRbListBox::markfunc(self);
  }


void FXRbDirSelector::markfunc(FXDirSelector* self){
  FXTRACE((100,"FXRbDirSelector::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->acceptButton());
    FXRbGcMark(self->cancelButton());
    }
  }


void FXRbFileSelector::markfunc(FXFileSelector* self){
  FXTRACE((100,"FXRbFileSelector::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->acceptButton());
    FXRbGcMark(self->cancelButton());
    }
  }


void FXRbFontSelector::markfunc(FXFontSelector* self){
  FXTRACE((100,"FXRbFontSelector::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->acceptButton());
    FXRbGcMark(self->cancelButton());
    }
  }


void FXRbDirDialog::markfunc(FXDirDialog* self){
  FXTRACE((100,"FXRbDirDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbFileDialog::markfunc(FXFileDialog* self){
  FXTRACE((100,"FXRbFileDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbFontDialog::markfunc(FXFontDialog* self){
  FXTRACE((100,"FXRbFontDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbListBox::markfunc(FXListBox* self){
  FXTRACE((100,"FXRbListBox::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    for(FXint i=0;i<self->getNumItems();i++){
      FXRbGcMark(self->getItemIcon(i));
      if(self->getItemData(i))
        MARK(self->getItemData(i));
      }
    }
  }


void FXRbTreeListBox::markfunc(FXTreeListBox* self){
  FXTRACE((100,"FXRbTreeListBox::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    for(FXTreeItem* item=self->getFirstItem();item!=0;item=item->getNext()){
      FXRbGcMark(item);
      FXRbTreeItem::markfunc(item);
      }
    }
  }


void FXRbToolTip::markfunc(FXToolTip* self){
  FXTRACE((100,"FXRbToolTip::markfunc() %p\n",self));
  FXRbShell::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbRootWindow::markfunc(FXRootWindow* self){
  FXTRACE((100,"FXRbRootWindow::markfunc() %p\n",self));
  FXRbComposite::markfunc(self);
  }


void FXRbPNGIcon::markfunc(FXPNGIcon *self){
  FXTRACE((100,"FXRbPNGIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbMDIMenu::markfunc(FXMDIMenu *self){
  FXTRACE((100,"FXRbMDIMenu::markfunc() %p\n",self));
  FXRbMenuPane::markfunc(self);
  }


void FXRbMDIRestoreButton::markfunc(FXMDIRestoreButton *self){
  FXTRACE((100,"FXRbMDIRestoreButton::markfunc() %p\n",self));
  FXRbButton::markfunc(self);
  }


void FXRbXBMImage::markfunc(FXXBMImage *self){
  FXTRACE((100,"FXRbXBMImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbXPMImage::markfunc(FXXPMImage *self){
  FXTRACE((100,"FXRbXPMImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbJPGImage::markfunc(FXJPGImage *self){
  FXTRACE((100,"FXRbJPGImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbTextField::markfunc(FXTextField *self){
  FXTRACE((100,"FXRbTextField::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbMenuCascade::markfunc(FXMenuCascade *self){
  FXTRACE((100,"FXRbMenuCascade::markfunc() %p\n",self));
  FXRbMenuCaption::markfunc(self);
  if(self){
    FXRbGcMark(self->getMenu());
    }
  }


void FXRbMenuCommand::markfunc(FXMenuCommand *self){
  FXTRACE((100,"FXRbMenuCommand::markfunc() %p\n",self));
  FXRbMenuCaption::markfunc(self);
  }


void FXRbMenuBar::markfunc(FXMenuBar *self){
  FXTRACE((100,"FXRbMenuBar::markfunc() %p\n",self));
  FXRbToolBar::markfunc(self);
  }


void FXRbScrollCorner::markfunc(FXScrollCorner *self){
  FXTRACE((100,"FXRbScrollCorner::markfunc() %p\n",self));
  FXRbWindow::markfunc(self);
  }


void FXRbShutter::markfunc(FXShutter *self){
  FXRbVerticalFrame::markfunc(self);
  }


void FXRbProgressBar::markfunc(FXProgressBar *self){
  FXTRACE((100,"FXRbProgressBar::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbSeparator::markfunc(FXSeparator* self){
  FXTRACE((100,"FXRbSeparator::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
 }
 
 
void FXRbHorizontalSeparator::markfunc(FXHorizontalSeparator *self){
  FXTRACE((100,"FXRbHorizontalSeparator::markfunc() %p\n",self));
  FXRbSeparator::markfunc(self);
  }


void FXRbSpinner::markfunc(FXSpinner *self){
  FXTRACE((100,"FXRbSpinner::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbRealSpinner::markfunc(FXRealSpinner *self){
  FXTRACE((100,"FXRbRealSpinner::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbGIFIcon::markfunc(FXGIFIcon *self){
  FXTRACE((100,"FXRbGIFIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbTIFIcon::markfunc(FXTIFIcon *self){
  FXTRACE((100,"FXRbTIFIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbPCXIcon::markfunc(FXPCXIcon *self){
  FXTRACE((100,"FXRbPCXIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbRGBIcon::markfunc(FXRGBIcon *self){
  FXTRACE((100,"FXRbRGBIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbMDIMaximizeButton::markfunc(FXMDIMaximizeButton *self){
  FXTRACE((100,"FXRbMDIMaximizeButton::markfunc() %p\n",self));
  FXRbButton::markfunc(self);
  }


void FXRbMDIDeleteButton::markfunc(FXMDIDeleteButton *self){
  FXTRACE((100,"FXRbMDIDeleteButton::markfunc() %p\n",self));
  FXRbButton::markfunc(self);
  }


void FXRbMenuButton::markfunc(FXMenuButton *self){
  FXTRACE((100,"FXRbMenuButton::markfunc() %p\n",self));
  FXRbLabel::markfunc(self);
  if(self){
    FXRbGcMark(self->getMenu());
    }
  }


void FXRbMatrix::markfunc(FXMatrix *self){
  FXTRACE((100,"FXRbMatrix::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  }


void FXRbMenuSeparator::markfunc(FXMenuSeparator *self){
  FXTRACE((100,"FXRbMenuSeparator::markfunc() %p\n",self));
  FXRbWindow::markfunc(self);
  }


void FXRbSwitcher::markfunc(FXSwitcher *self){
  FXTRACE((100,"FXRbSwitcher::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  }


void FXRbRealSlider::markfunc(FXRealSlider *self){
  FXTRACE((100,"FXRbRealSlider::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  }


void FXRbSlider::markfunc(FXSlider *self){
  FXTRACE((100,"FXRbSlider::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  }


void FXRbToolBarGrip::markfunc(FXToolBarGrip *self){
  FXTRACE((100,"FXRbToolBarGrip::markfunc() %p\n",self));
  FXRbDockHandler::markfunc(self);
  }


void FXRbJPGIcon::markfunc(FXJPGIcon *self){
  FXTRACE((100,"FXRbJPGIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbTabBar::markfunc(FXTabBar *self){
  FXTRACE((100,"FXRbTabBar::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  }


void FXRbToolBarTab::markfunc(FXToolBarTab *self){
  FXTRACE((100,"FXRbToolBarTab::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  }


void FXRbSearchDialog::markfunc(FXSearchDialog *self){
  FXTRACE((100,"FXRbSearchDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbPrintDialog::markfunc(FXPrintDialog *self){
  FXTRACE((100,"FXRbPrintDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbMDIMinimizeButton::markfunc(FXMDIMinimizeButton *self){
  FXTRACE((100,"FXRbMDIMinimizeButton::markfunc() %p\n",self));
  FXRbButton::markfunc(self);
  }


void FXRbGIFCursor::markfunc(FXGIFCursor *self){
  FXTRACE((100,"FXRbGIFCursor::markfunc() %p\n",self));
  FXRbCursor::markfunc(self);
  }


void FXRbGIFCursor::freefunc(FXGIFCursor* self){
  delete_if_not_owned_by_app(self,reinterpret_cast<FXRbGIFCursor*>(0));
  }


void FXRbCURCursor::markfunc(FXCURCursor *self){
  FXTRACE((100,"FXRbCURCursor::markfunc() %p\n",self));
  FXRbCursor::markfunc(self);
  }


void FXRbCURCursor::freefunc(FXCURCursor* self){
  delete_if_not_owned_by_app(self,reinterpret_cast<FXRbCURCursor*>(0));
  }


void FXRbGLViewer::markfunc(FXGLViewer *self){
  FXTRACE((100,"FXRbGLViewer::markfunc() %p\n",self));
  FXRbGLCanvas::markfunc(self);
  if(self){
    FXRbGcMark(self->getScene());
    FXRbGcMark(self->getSelection());
    }
  }


void FXRbGIFImage::markfunc(FXGIFImage *self){
  FXTRACE((100,"FXRbGIFImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbTIFImage::markfunc(FXTIFImage *self){
  FXTRACE((100,"FXRbTIFImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbPCXImage::markfunc(FXPCXImage *self){
  FXTRACE((100,"FXRbPCXImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbRGBImage::markfunc(FXRGBImage *self){
  FXTRACE((100,"FXRbRGBImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbMenuPane::markfunc(FXMenuPane *self){
  FXTRACE((100,"FXRbMenuPane::markfunc() %p\n",self));
  FXRbPopup::markfunc(self);
  }


void FXRbScrollPane::markfunc(FXScrollPane *self){
  FXRbMenuPane::markfunc(self);
  }


void FXRbSplitter::markfunc(FXSplitter *self){
  FXTRACE((100,"FXRbSplitter::markfunc() %p\n",self));
  FXRbComposite::markfunc(self);
  }


void FXRbStatusBar::markfunc(FXStatusBar *self){
  FXTRACE((100,"FXRbStatusBar::markfunc() %p\n",self));
  FXRbHorizontalFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->getStatusLine());
    FXRbGcMark(self->getDragCorner());
    }
  }


void FXRbMDIChild::markfunc(FXMDIChild *self){
  FXTRACE((100,"FXRbMDIChild::markfunc() %p\n",self));
  FXRbComposite::markfunc(self);
  if(self){
    FXRbGcMark(self->contentWindow());
    FXRbGcMark(self->getIcon());
    FXRbGcMark(self->getMenu());
    FXRbGcMark(self->getFont());
    }
  }


void FXRbPNGImage::markfunc(FXPNGImage *self){
  FXTRACE((100,"FXRbPNGImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbVisual::markfunc(FXVisual *self){
  FXTRACE((100,"FXRbVisual::markfunc() %p\n",self));
  FXRbId::markfunc(self);
  }


void FXRbVisual::freefunc(FXVisual *self){
  delete_if_not_owned_by_app(self,reinterpret_cast<FXRbVisual*>(0));
  }


void FXRbVerticalSeparator::markfunc(FXVerticalSeparator *self){
  FXTRACE((100,"FXRbVerticalSeparator::markfunc() %p\n",self));
  FXRbSeparator::markfunc(self);
  }


void FXRbToggleButton::markfunc(FXToggleButton *self){
  FXTRACE((100,"FXRbToggleButton::markfunc() %p\n",self));
  FXRbLabel::markfunc(self);
  if(self){
    FXRbGcMark(self->getAltIcon());
    }
  }


void FXRbTriStateButton::markfunc(FXTriStateButton *self){
  FXTRACE((100,"FXRbTriStateButton::markfunc() %p\n",self));
  FXRbToggleButton::markfunc(self);
  if(self){
    FXRbGcMark(self->getMaybeIcon());
    }
  }


void FXRbPopup::markfunc(FXPopup *self){
  FXTRACE((100,"FXRbPopup::markfunc() %p\n",self));
  FXRbShell::markfunc(self);
  if(self){
    FXRbGcMark(self->getGrabOwner());
    }
  }


void FXRbOptionMenu::markfunc(FXOptionMenu *self){
  FXTRACE((100,"FXRbOptionMenu::markfunc() %p\n",self));
  FXRbLabel::markfunc(self);
  if(self){
    FXRbGcMark(self->getCurrent());
    FXRbGcMark(self->getMenu());
    }
  }


void FXRbMessageBox::markfunc(FXMessageBox *self){
  FXTRACE((100,"FXRbMessageBox::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbToolBar::markfunc(FXToolBar *self){
  FXTRACE((100,"FXRbToolBar::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->getDryDock());
    FXRbGcMark(self->getWetDock());
    }
  }


void FXRbGLCanvas::markfunc(FXGLCanvas *self){
  FXTRACE((100,"FXRbGLCanvas::markfunc() %p\n",self));
  FXRbCanvas::markfunc(self);
  }


void FXRbGLVisual::markfunc(FXGLVisual *self){
  FXTRACE((100,"FXRbGLVisual::markfunc() %p\n",self));
  FXRbVisual::markfunc(self);
  }


void FXRbGLVisual::freefunc(FXGLVisual *self){
  delete_if_not_owned_by_app(self,reinterpret_cast<FXRbGLVisual*>(0));
  }


void FXRbOption::markfunc(FXOption *self){
  FXTRACE((100,"FXRbOption::markfunc() %p\n",self));
  FXRbLabel::markfunc(self);
  }


void FXRbScrollWindow::markfunc(FXScrollWindow *self){
  FXTRACE((100,"FXRbScrollWindow::markfunc() %p\n",self));
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->contentWindow());
    }
  }


void FXRbText::markfunc(FXText *self){
  FXTRACE((100,"FXRbText::markfunc() %p\n",self));
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbToolBarShell::markfunc(FXToolBarShell *self){
  FXTRACE((100,"FXRbToolBarShell::markfunc() %p\n",self));
  FXRbTopWindow::markfunc(self);
  }

void FXRbSplashWindow::markfunc(FXSplashWindow *self){
  FXTRACE((100,"FXRbSplashWindow::markfunc() %p\n",self));
  FXRbTopWindow::markfunc(self);
  if(self){
    FXRbGcMark(self->getIcon());
    }
  }

void FXRbInputDialog::markfunc(FXInputDialog *self){
  FXTRACE((100,"FXRbInputDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbMDIClient::markfunc(FXMDIClient *self){
  FXTRACE((100,"FXRbMDIClient::markfunc() %p\n",self));
  FXRbComposite::markfunc(self);
  }


void FXRbMenuTitle::markfunc(FXMenuTitle *self){
  FXTRACE((100,"FXRbMenuTitle::markfunc() %p\n",self));
  FXRbMenuCaption::markfunc(self);
  if(self){
    FXRbGcMark(self->getMenu());
    }
  }


/*
void FXRbBitmapView::markfunc(FXBitmapView *self){
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->getBitmap());
    }
  }
*/


void FXRbImageView::markfunc(FXImageView *self){
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->getImage());
    }
  }


void FXRbShutterItem::markfunc(FXShutterItem *self){
  FXRbVerticalFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->getButton());
    FXRbGcMark(self->getContent());
    }
  }


void FXRbMDIWindowButton::markfunc(FXMDIWindowButton *self){
  FXTRACE((100,"FXRbMDIWindowButton::markfunc() %p\n",self));
  FXRbMenuButton::markfunc(self);
  }


void FXRbMenuCaption::markfunc(FXMenuCaption *self){
  FXTRACE((100,"FXRbMenuCaption::markfunc() %p\n",self));
  FXRbWindow::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    FXRbGcMark(self->getIcon());
    }
  }


void FXRbTabItem::markfunc(FXTabItem *self){
  FXTRACE((100,"FXRbTabItem::markfunc() %p\n",self));
  FXRbLabel::markfunc(self);
  }


void FXRbStatusLine::markfunc(FXStatusLine *self){
  FXTRACE((100,"FXRbStatusLine::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbGLShape::markfunc(FXGLShape *self){
  FXTRACE((100,"FXRbGLShape::markfunc() %p\n",self));
  FXRbGLObject::markfunc(self);
  }


void FXRbTabBook::markfunc(FXTabBook *self){
  FXTRACE((100,"FXRbTabBook::markfunc() %p\n",self));
  FXRbTabBar::markfunc(self);
  }


void FXRbReplaceDialog::markfunc(FXReplaceDialog *self){
  FXTRACE((100,"FXRbReplaceDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbXBMIcon::markfunc(FXXBMIcon *self){
  FXTRACE((100,"FXRbXBMIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbXPMIcon::markfunc(FXXPMIcon *self){
  FXTRACE((100,"FXRbXPMIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbRadioButton::markfunc(FXRadioButton *self){
  FXTRACE((100,"FXRbRadioButton::markfunc() %p\n",self));
  FXRbLabel::markfunc(self);
  }


void FXRbScrollBar::markfunc(FXScrollBar *self){
  FXTRACE((100,"FXRbScrollBar::markfunc() %p\n",self));
  FXRbWindow::markfunc(self);
  }


void FXRbStream::markfunc(FXStream *self){
  FXTRACE((100,"FXRbStream::markfunc() %p\n",self));
  if(self){
    FXRbGcMark((void*)self->container());
    }
  }


void FXRbFileStream::markfunc(FXFileStream *self){
  FXTRACE((100,"FXRbFileStream::markfunc() %p\n",self));
  FXRbStream::markfunc(self);
  }


void FXRbMemoryStream::markfunc(FXMemoryStream *self){
  FXTRACE((100,"FXRbMemoryStream::markfunc() %p\n",self));
  FXRbStream::markfunc(self);
  }


void FXRbDC::markfunc(FXDC *self){
  FXTRACE((100,"FXRbDC::markfunc() %p\n",self));
  }


void FXRbDCWindow::markfunc(FXDCWindow *self){
  FXTRACE((100,"FXRbDCWindow::markfunc() %p\n",self));
  FXRbDC::markfunc(self);
  }


void FXRbDCPrint::markfunc(FXDCPrint *self){
  FXTRACE((100,"FXRbDCPrint::markfunc() %p\n",self));
  FXRbDC::markfunc(self);
  }


void FXRbProgressDialog::markfunc(FXProgressDialog* self){
  FXTRACE((100,"FXRbProgressDialog::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  }


void FXRbPicker::markfunc(FXPicker* self){
  FXTRACE((100,"FXRbPicker::markfunc() %p\n",self));
  FXRbButton::markfunc(self);
  }


void FXRbColorBar::markfunc(FXColorBar* self){
  FXTRACE((100,"FXRbColorBar::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  }


void FXRbColorRing::markfunc(FXColorRing* self){
  FXTRACE((100,"FXRbColorRing::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  }


void FXRbColorWheel::markfunc(FXColorWheel* self){
  FXTRACE((100,"FXRbColorWheel::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  }


void FXRbICOIcon::markfunc(FXICOIcon* self){
  FXTRACE((100,"FXRbICOIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbICOImage::markfunc(FXICOImage* self){
  FXTRACE((100,"FXRbICOImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbTGAIcon::markfunc(FXTGAIcon* self){
  FXTRACE((100,"FXRbTGAIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbTGAImage::markfunc(FXTGAImage* self){
  FXTRACE((100,"FXRbTGAImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }


void FXRbBitmapFrame::markfunc(FXBitmapFrame* self){
  FXTRACE((100,"start FXRbBitmapFrame::markfunc(%p)\n",self));
  FXRbFrame::markfunc(self);
  if(self!=0){
    FXRbGcMark(self->getBitmap());
    }
  FXTRACE((100,"end FXRbBitmapFrame::markfunc(%p)\n",self));
  }


void FXRbImageFrame::markfunc(FXImageFrame* self){
  FXTRACE((100,"start FXRbImageFrame::markfunc(%p)\n",self));
  FXRbFrame::markfunc(self);
  if(self!=0){
    FXRbGcMark(self->getImage());
    }
  FXTRACE((100,"end FXRbImageFrame::markfunc(%p)\n",self));
  }


void FXRbGradientBar::markfunc(FXGradientBar* self){
  FXTRACE((100,"start FXRbGradientBar::markfunc(%p)\n",self));
  FXRbFrame::markfunc(self);
  FXTRACE((100,"end FXRbGradientBar::markfunc(%p)\n",self));
  }

#ifdef WITH_FXSCINTILLA

void FXRbScintilla::markfunc(FXScintilla* self){
  FXTRACE((100,"FXRbScintilla::markfunc() %p\n",self));
  FXRbScrollArea::markfunc(self);
  }

#endif

void FXRbWizard::markfunc(FXWizard* self){
  FXTRACE((100,"FXRbWizard::markfunc() %p\n",self));
  FXRbDialogBox::markfunc(self);
  if(self){
    FXRbGcMark(self->advanceButton());
    FXRbGcMark(self->retreatButton());
    FXRbGcMark(self->finishButton());
    FXRbGcMark(self->cancelButton());
    FXRbGcMark(self->getContainer());
    FXRbGcMark(self->getImage());
    }
  }


void FXRbRuler::markfunc(FXRuler* self){
  FXTRACE((100,"FXRbRuler::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->getFont());
    }
  }


void FXRbRulerView::markfunc(FXRulerView* self){
  FXTRACE((100,"FXRbRulerView::markfunc() %p\n",self));
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->horizontalRuler());
    FXRbGcMark(self->verticalRuler());
    FXRbGcMark(self->getHRulerFont());
    FXRbGcMark(self->getVRulerFont());
    }
  }

  
void FXRbPPMIcon::markfunc(FXPPMIcon* self){
  FXTRACE((100,"FXRbPPMIcon::markfunc() %p\n",self));
  FXRbIcon::markfunc(self);
  }


void FXRbPPMImage::markfunc(FXPPMImage* self){
  FXTRACE((100,"FXRbPPMImage::markfunc() %p\n",self));
  FXRbImage::markfunc(self);
  }

