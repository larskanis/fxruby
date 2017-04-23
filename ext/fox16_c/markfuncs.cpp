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
// See workaround in lib/fox16/accel_table.rb.
void FXRbAccelTable::markfunc(FXAccelTable* accelTable){
  FXRbObject::markfunc(accelTable);
  }


// Mark dependencies for the GC
void FXRbObject::markfunc(FXObject* obj){
  FXTRACE((100,"%s::markfunc(%p)\n",obj?obj->getClassName():"FXRbObject",obj));
  }

static void FXRbSetInGCParentsRecursive(FXWindow *window, bool enabled){
  FXRbSetInGC( window, true );
  if(window->getParent()) FXRbSetInGCParentsRecursive( window->getParent(), enabled );
  }

static void FXRbSetInGCChildrenRecursive(FXWindow *window, bool enabled){
  FXRbSetInGC( window, true );
  for(FXWindow* child=window->getFirst(); child; child=child->getNext()){
    FXRbSetInGCChildrenRecursive( child, enabled );
    }
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
      // FXWindow destructor calls recalc() and changeFocus() of it's parent window.
      // Since these methods are routed back to Ruby code, but calling Ruby code from
      // GC isn't a good idea, we mark the parent window as "in_gc", so that it will
      // ignore recalc() and changeFocus() calls completely.
      // The parent window should also be scheduled to be free'd. In the other case,
      // the child window would have been marked as used.
      if(self->isMemberOf(FXMETACLASS(FXWindow))){
        FXWindow *window = dynamic_cast<FXWindow*>(self);
        FXRbSetInGCParentsRecursive( window, true );
        FXRbSetInGCChildrenRecursive( window, true );
        }
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
    FXRbGcMark(translator->FXTranslator::getApp());
    FXRbGcMark(translator->FXTranslator::getTextCodec());
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
    FXRbGcMark(self->FXLabel::getFont());
    FXRbGcMark(self->FXLabel::getIcon());
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
    FXRbGcMark(self->FXDockTitle::getFont());
    }
  }

void FXRbDrawable::markfunc(FXDrawable* drawable){
  FXRbId::markfunc(drawable);
  if(drawable) FXRbGcMark(drawable->FXDrawable::getVisual());
  }


void FXRbId::markfunc(FXId* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXId::getApp());
    if(void *d=self->FXId::getUserData())
      MARK(d);
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
    FXRbGcMark(self->FXWindow::getParent());
    FXRbGcMark(self->FXWindow::getOwner());
    FXRbGcMark(self->FXWindow::getShell());
    FXRbGcMark(self->FXWindow::getRoot());
    // FXRbGcMark(self->FXWindow::getNext());
    // FXRbGcMark(self->FXWindow::getPrev());
    FXRbGcMark(self->FXWindow::getFocus());
    FXRbGcMark(self->FXWindow::getTarget());
    FXRbGcMark(self->FXWindow::getAccelTable());
    FXRbGcMark(self->FXWindow::getDefaultCursor());
    FXRbGcMark(self->FXWindow::getDragCursor());

    // Mark child windows
    register FXWindow* child=self->FXWindow::getFirst();
    while(child!=NULL){
      FXRbGcMark(child);
      child=child->FXWindow::getNext();
      }
    }
  }


void FXRbDialogBox::markfunc(FXDialogBox* dlg){
  FXRbTopWindow::markfunc(dlg);
  }


void FXRbTopWindow::markfunc(FXTopWindow* top){
  FXRbShell::markfunc(top);
  if(top){
    FXRbGcMark(top->FXTopWindow::getIcon());
    FXRbGcMark(top->FXTopWindow::getMiniIcon());
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
    FXRbGcMark(self->FXGroupBox::getFont());
    }
  }


void FXRbColorWell::markfunc(FXColorWell* cw){
  FXRbFrame::markfunc(cw);
  }


void FXRbComboBox::markfunc(FXComboBox* self){
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->FXComboBox::getFont());
    for(FXint i=0; i<self->getNumItems(); i++){
      if(void *d=self->FXComboBox::getItemData(i))
        MARK(d);
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
    FXRbGcMark(self->FXApp::getMonoVisual());
    FXRbGcMark(self->FXApp::getDefaultVisual());

    // Fonts
    FXRbGcMark(self->FXApp::getNormalFont());

    // Cursors
    FXRbGcMark(self->FXApp::getWaitCursor());
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_ARROW_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_RARROW_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_TEXT_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_HSPLIT_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_VSPLIT_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_XSPLIT_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_SWATCH_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_MOVE_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DRAGH_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DRAGV_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DRAGTL_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DRAGBR_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DRAGTR_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DRAGBL_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DNDSTOP_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DNDCOPY_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DNDMOVE_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_DNDLINK_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_CROSSHAIR_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_CORNERNE_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_CORNERNW_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_CORNERSE_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_CORNERSW_CURSOR));
    FXRbGcMark(self->FXApp::getDefaultCursor(DEF_ROTATE_CURSOR));

    // Other windows
    FXRbGcMark(self->FXApp::getFocusWindow());
    FXRbGcMark(self->FXApp::getCursorWindow());

    /**
     * Root window is a special case; popups (like FXTooltip) can be created
     * without an "owner" by passing FXApp as the first argument to their
     * constructor, but in fact the "owner" of these window is the root window.
     * So unless we invoke FXRbRootWindow's mark function here, unowned windows
     * like tooltips may get garbage-collected prematurely.
     */
    if(self->FXApp::getRootWindow()){
      FXRbGcMark(self->FXApp::getRootWindow());
      FXRbRootWindow::markfunc(self->FXApp::getRootWindow());
      }

    // Registry
    FXRbGcMark(&(self->FXApp::reg()));

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
    FXRbGcMark(self->FXTreeItem::getParent());
    FXRbGcMark(self->FXTreeItem::getNext());
    FXRbGcMark(self->FXTreeItem::getPrev());
    for(FXTreeItem* item=self->FXTreeItem::getFirst(); item; item=item->FXTreeItem::getNext()){
      FXRbGcMark(item);
      FXRbTreeItem::markfunc(item);
      }
    FXRbGcMark(self->FXTreeItem::getBelow());
    FXRbGcMark(self->FXTreeItem::getAbove());
    FXRbGcMark(self->FXTreeItem::getOpenIcon());
    FXRbGcMark(self->FXTreeItem::getClosedIcon());
    if(void *d=self->FXTreeItem::getData())
      MARK(d);
    }
  }


void FXRbTreeItem::freefunc(FXTreeItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbTreeItem*>(0));
  }


void FXRbTreeList::markfunc(FXTreeList* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    for(FXTreeItem* item=self->FXTreeList::getFirstItem(); item; item=item->FXTreeItem::getNext()){
      FXRbGcMark(item);
      FXRbTreeItem::markfunc(item);
      }
    FXRbGcMark(self->FXTreeList::getFont());
    }
  }


void FXRbFoldingItem::markfunc(FXFoldingItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXFoldingItem::getParent());
    FXRbGcMark(self->FXFoldingItem::getNext());
    FXRbGcMark(self->FXFoldingItem::getPrev());
    for(FXFoldingItem* item=self->FXFoldingItem::getFirst(); item; item=item->FXFoldingItem::getNext()){
      FXRbGcMark(item);
      FXRbFoldingItem::markfunc(item);
      }
    FXRbGcMark(self->FXFoldingItem::getBelow());
    FXRbGcMark(self->FXFoldingItem::getAbove());
    FXRbGcMark(self->FXFoldingItem::getOpenIcon());
    FXRbGcMark(self->FXFoldingItem::getClosedIcon());
    if(void *d=self->FXFoldingItem::getData())
      MARK(d);
    }
  }


void FXRbFoldingItem::freefunc(FXFoldingItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbFoldingItem*>(0));
  }


void FXRbFoldingList::markfunc(FXFoldingList* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    for(FXFoldingItem* item=self->FXFoldingList::getFirstItem(); item; item=item->FXFoldingItem::getNext()){
      FXRbGcMark(item);
      FXRbFoldingItem::markfunc(item);
      }
    FXRbGcMark(self->FXFoldingList::getFont());
    }
  }


void FXRbListItem::markfunc(FXListItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXListItem::getIcon());
    if(void *d=self->FXListItem::getData())
      MARK(d);
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
    for(FXint i=0;i<self->FXList::getNumItems();i++){
      FXListItem* item=self->FXList::getItem(i);
      FXRbGcMark(item);
      FXRbListItem::markfunc(item);
      }
    FXRbGcMark(self->FXList::getFont());
    }
  }


void FXRbColorList::markfunc(FXColorList* self){
  FXRbList::markfunc(self);
  }


void FXRbTableItem::markfunc(FXTableItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXTableItem::getIcon());
    if(void* d=self->FXTableItem::getData())
      MARK(d);
    }
  }


void FXRbTableItem::freefunc(FXTableItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbTableItem*>(0));
  }


void FXRbTable::markfunc(FXTable* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->FXTable::getFont());
    FXRbGcMark(self->FXTable::getRowHeaderFont());
    FXRbGcMark(self->FXTable::getColumnHeaderFont());
    for(FXint row=0;row<self->FXTable::getNumRows();row++){
      for(FXint col=0;col<self->FXTable::getNumColumns();col++){
        FXTableItem* item=self->FXTable::getItem(row,col);
        FXRbGcMark(item);
        }
      }
    }
  }


void FXRbHeaderItem::markfunc(FXHeaderItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXHeaderItem::getIcon());
    if(void* d=self->FXHeaderItem::getData())
      MARK(d);
    }
  }


void FXRbHeaderItem::freefunc(FXHeaderItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbHeaderItem*>(0));
  }


void FXRbHeader::markfunc(FXHeader* self){
  FXRbFrame::markfunc(self);
  if(self){
    for(FXint i=0;i<self->FXHeader::getNumItems();i++){
      FXHeaderItem* item=self->FXHeader::getItem(i);
      FXRbGcMark(item);
      FXRbHeaderItem::markfunc(item);
      }
    FXRbGcMark(self->FXHeader::getFont());
    }
  }


void FXRbIconItem::markfunc(FXIconItem* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXIconItem::getBigIcon());
    FXRbGcMark(self->FXIconItem::getMiniIcon());
    if(void *d=self->FXIconItem::getData())
      MARK(d);
    }
  }


void FXRbIconItem::freefunc(FXIconItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbIconItem*>(0));
  }


void FXRbIconList::markfunc(FXIconList* self){
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->FXIconList::getHeader());
    for(FXint i=0;i<self->FXIconList::getNumItems();i++){
      FXIconItem* item=self->FXIconList::getItem(i);
      FXRbGcMark(item);
      FXRbIconItem::markfunc(item);
      }
    FXRbGcMark(self->FXIconList::getFont());
    }
  }


void FXRbDelegator::markfunc(FXDelegator* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXDelegator::getDelegate());
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
    FXRbGcMark(self->FXRecentFiles::getTarget());
    }
  }


void FXRbScrollArea::markfunc(FXScrollArea* self){
  FXRbComposite::markfunc(self);
  if(self){
    FXRbGcMark(self->FXScrollArea::horizontalScrollBar());
    FXRbGcMark(self->FXScrollArea::verticalScrollBar());
    }
  }


void FXRbDocument::markfunc(FXDocument* self){
  FXRbObject::markfunc(self);
  }


void FXRbGLContext::markfunc(FXGLContext* self){
  FXRbObject::markfunc(self);
  if(self){
    FXRbGcMark(self->FXGLContext::getVisual());
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
    FXRbGcMark(self->FXIconDict::getIconSource());
    if(self->FXIconDict::no()>0){
      FXint pos=self->FXIconDict::first();
      FXint last=self->FXIconDict::last();
      while(pos<=last){
        const FXchar* name=self->FXIconDict::key(pos);
        FXIcon* icon=self->FXIconDict::find(name);
        FXRbGcMark(icon);
        pos=self->FXIconDict::next(pos);
        }
      }
    }
  }


void FXRbFileDict::markfunc(FXFileDict* self){
  FXRbDict::markfunc(self);
  FXRbGcMark(self->FXFileDict::getSettings());
  if(self){
    if(self->FXFileDict::no()>0){
      FXint pos=self->FXFileDict::first();
      FXint last=self->FXFileDict::last();
      while(pos<=last){
        const FXchar* key=self->FXFileDict::key(pos);
        FXFileAssoc* assoc=self->FXFileDict::find(key);
        FXRbGcMark(assoc);
        pos=self->FXFileDict::next(pos);
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
    FXRbGcMark(self->FXDirItem::getAssoc());
    }
  }


void FXRbDirItem::freefunc(FXDirItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbDirItem*>(0));
  }

void FXRbDirList::markfunc(FXDirList* self){
  FXTRACE((100,"FXRbDirList::markfunc() %p\n",self));
  FXRbTreeList::markfunc(self);
  if(self){
    FXRbGcMark(self->FXDirList::getAssociations());
    }
  }


void FXRb4Splitter::markfunc(FX4Splitter* self){
  FXTRACE((100,"FXRb4Splitter::markfunc() %p\n",self));
  FXRbComposite::markfunc(self);
  if(self){
    FXRbGcMark(self->FX4Splitter::getTopLeft());
    FXRbGcMark(self->FX4Splitter::getTopRight());
    FXRbGcMark(self->FX4Splitter::getBottomLeft());
    FXRbGcMark(self->FX4Splitter::getBottomRight());
    }
  }


void FXRbFileItem::markfunc(FXFileItem* self){
  FXTRACE((100,"FXRbFileItem::markfunc() %p\n",self));
  FXRbIconItem::markfunc(self);
  if(self){
    FXRbGcMark(self->FXFileItem::getAssoc());
    }
  }


void FXRbFileItem::freefunc(FXFileItem* self){
  delete_if_not_owned(self,reinterpret_cast<FXRbFileItem*>(0));
  }


void FXRbFileList::markfunc(FXFileList* self){
  FXTRACE((100,"FXRbFileList::markfunc() %p\n",self));
  FXRbIconList::markfunc(self);
  if(self){
    FXRbGcMark(self->FXFileList::getAssociations());
    for(FXint i=0;i<self->FXFileList::getNumItems();i++){
      FXFileAssoc* assoc=self->FXFileList::getItemAssoc(i);
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
    FXRbGcMark(self->FXDirSelector::acceptButton());
    FXRbGcMark(self->FXDirSelector::cancelButton());
    }
  }


void FXRbFileSelector::markfunc(FXFileSelector* self){
  FXTRACE((100,"FXRbFileSelector::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->FXFileSelector::acceptButton());
    FXRbGcMark(self->FXFileSelector::cancelButton());
    }
  }


void FXRbFontSelector::markfunc(FXFontSelector* self){
  FXTRACE((100,"FXRbFontSelector::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->FXFontSelector::acceptButton());
    FXRbGcMark(self->FXFontSelector::cancelButton());
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
    FXRbGcMark(self->FXListBox::getFont());
    for(FXint i=0;i<self->FXListBox::getNumItems();i++){
      FXRbGcMark(self->FXListBox::getItemIcon(i));
      if(self->FXListBox::getItemData(i))
        MARK(self->FXListBox::getItemData(i));
      }
    }
  }


void FXRbTreeListBox::markfunc(FXTreeListBox* self){
  FXTRACE((100,"FXRbTreeListBox::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->FXTreeListBox::getFont());
    for(FXTreeItem* item=self->FXTreeListBox::getFirstItem();item!=0;item=item->FXTreeItem::getNext()){
      FXRbGcMark(item);
      FXRbTreeItem::markfunc(item);
      }
    }
  }


void FXRbToolTip::markfunc(FXToolTip* self){
  FXTRACE((100,"FXRbToolTip::markfunc() %p\n",self));
  FXRbShell::markfunc(self);
  if(self){
    FXRbGcMark(self->FXToolTip::getFont());
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
    FXRbGcMark(self->FXTextField::getFont());
    }
  }


void FXRbMenuCascade::markfunc(FXMenuCascade *self){
  FXTRACE((100,"FXRbMenuCascade::markfunc() %p\n",self));
  FXRbMenuCaption::markfunc(self);
  if(self){
    FXRbGcMark(self->FXMenuCascade::getMenu());
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
    FXRbGcMark(self->FXProgressBar::getFont());
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
    FXRbGcMark(self->FXSpinner::getFont());
    }
  }


void FXRbRealSpinner::markfunc(FXRealSpinner *self){
  FXTRACE((100,"FXRbRealSpinner::markfunc() %p\n",self));
  FXRbPacker::markfunc(self);
  if(self){
    FXRbGcMark(self->FXRealSpinner::getFont());
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
    FXRbGcMark(self->FXMenuButton::getMenu());
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
    FXRbGcMark(self->FXGLViewer::getScene());
    FXRbGcMark(self->FXGLViewer::getSelection());
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
    FXRbGcMark(self->FXStatusBar::getStatusLine());
    FXRbGcMark(self->FXStatusBar::getDragCorner());
    }
  }


void FXRbMDIChild::markfunc(FXMDIChild *self){
  FXTRACE((100,"FXRbMDIChild::markfunc() %p\n",self));
  FXRbComposite::markfunc(self);
  if(self){
    FXRbGcMark(self->FXMDIChild::contentWindow());
    FXRbGcMark(self->FXMDIChild::getIcon());
    FXRbGcMark(self->FXMDIChild::getMenu());
    FXRbGcMark(self->FXMDIChild::getFont());
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
    FXRbGcMark(self->FXToggleButton::getAltIcon());
    }
  }


void FXRbTriStateButton::markfunc(FXTriStateButton *self){
  FXTRACE((100,"FXRbTriStateButton::markfunc() %p\n",self));
  FXRbToggleButton::markfunc(self);
  if(self){
    FXRbGcMark(self->FXTriStateButton::getMaybeIcon());
    }
  }


void FXRbPopup::markfunc(FXPopup *self){
  FXTRACE((100,"FXRbPopup::markfunc() %p\n",self));
  FXRbShell::markfunc(self);
  if(self){
    FXRbGcMark(self->FXPopup::getGrabOwner());
    }
  }


void FXRbOptionMenu::markfunc(FXOptionMenu *self){
  FXTRACE((100,"FXRbOptionMenu::markfunc() %p\n",self));
  FXRbLabel::markfunc(self);
  if(self){
    FXRbGcMark(self->FXOptionMenu::getCurrent());
    FXRbGcMark(self->FXOptionMenu::getMenu());
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
    FXRbGcMark(self->FXToolBar::getDryDock());
    FXRbGcMark(self->FXToolBar::getWetDock());
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
    FXRbGcMark(self->FXScrollWindow::contentWindow());
    }
  }


void FXRbText::markfunc(FXText *self){
  FXTRACE((100,"FXRbText::markfunc() %p\n",self));
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->FXText::getFont());
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
    FXRbGcMark(self->FXSplashWindow::getIcon());
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
    FXRbGcMark(self->FXMenuTitle::getMenu());
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
    FXRbGcMark(self->FXImageView::getImage());
    }
  }


void FXRbShutterItem::markfunc(FXShutterItem *self){
  FXRbVerticalFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->FXShutterItem::getButton());
    FXRbGcMark(self->FXShutterItem::getContent());
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
    FXRbGcMark(self->FXMenuCaption::getFont());
    FXRbGcMark(self->FXMenuCaption::getIcon());
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
    FXRbGcMark(self->FXStatusLine::getFont());
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
    FXRbGcMark((void*)self->FXStream::container());
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
    FXRbGcMark(self->FXBitmapFrame::getBitmap());
    }
  FXTRACE((100,"end FXRbBitmapFrame::markfunc(%p)\n",self));
  }


void FXRbImageFrame::markfunc(FXImageFrame* self){
  FXTRACE((100,"start FXRbImageFrame::markfunc(%p)\n",self));
  FXRbFrame::markfunc(self);
  if(self!=0){
    FXRbGcMark(self->FXImageFrame::getImage());
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
    FXRbGcMark(self->FXWizard::advanceButton());
    FXRbGcMark(self->FXWizard::retreatButton());
    FXRbGcMark(self->FXWizard::finishButton());
    FXRbGcMark(self->FXWizard::cancelButton());
    FXRbGcMark(self->FXWizard::getContainer());
    FXRbGcMark(self->FXWizard::getImage());
    }
  }


void FXRbRuler::markfunc(FXRuler* self){
  FXTRACE((100,"FXRbRuler::markfunc() %p\n",self));
  FXRbFrame::markfunc(self);
  if(self){
    FXRbGcMark(self->FXRuler::getFont());
    }
  }


void FXRbRulerView::markfunc(FXRulerView* self){
  FXTRACE((100,"FXRbRulerView::markfunc() %p\n",self));
  FXRbScrollArea::markfunc(self);
  if(self){
    FXRbGcMark(self->FXRulerView::horizontalRuler());
    FXRbGcMark(self->FXRulerView::verticalRuler());
    FXRbGcMark(self->FXRulerView::getHRulerFont());
    FXRbGcMark(self->FXRulerView::getVRulerFont());
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

