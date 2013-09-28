/***********************************************************************
 * $Id: unregisterOwnedObjects.cpp 2911 2008-12-11 14:09:45Z lyle $
 ***********************************************************************/

/**
 * The purpose of an unregisterOwnedObjects() function for a particular
 * class is to call FXRbUnregisterRubyObj() on any objects that this object
 * created itself, and which it "owns" and will destroy in its destructor.
 * This includes not only child widgets, like the horizontal and vertical
 * scrollbars managed by an FXScrollArea, but other non-widget objects
 * like list items.
 *
 * You don't need to worry about objects that the user created himself
 * using Ruby code, because those should get unregistered automatically
 * when they're destroyed. So, for example, if I create a button as a child
 * of a frame, e.g.
 *
 *     FXButton.new(parentFrame, ...)
 *
 * that Ruby object's peer is an FXRbButton instance, and the destructor for
 * the FXRbButton class calls FXRbUnregisterRubyObj(this). We only need to
 * worry about the C++ objects that aren't subclasses of regular FOX classes,
 * but which have somehow been "exposed" to the Ruby layer.
 */

#include "FXRbCommon.h"

void FXRbHeader::unregisterOwnedObjects(FXHeader *self)
{
    // FXRbFrame::unregisterOwnedObjects(self);
    for (FXint i = 0; i < self->getNumItems(); i++) FXRbUnregisterRubyObj(self->getItem(i));
}

void FXRbScrollArea::unregisterOwnedObjects(FXScrollArea *self)
{
    // FXRbComposite::unregisterOwnedObjects(self);
    FXRbUnregisterRubyObj(self->horizontalScrollBar());
    FXRbUnregisterRubyObj(self->verticalScrollBar());
}

/*
void FXRbBitmapView::unregisterOwnedObjects(FXBitmapView *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);
}
*/

void FXRbFoldingList::unregisterOwnedObjects(FXFoldingList *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);
    FXRbUnregisterRubyObj(self->getHeader());

    // Save pointer(s) to the soon-to-be-destroyed items
    FXObjectListOf<FXFoldingItem> items;
    FXRbFoldingList::enumerateItems(self->getFirstItem(),self->getLastItem(),items);

    // Now zero-out pointers held by still-alive Ruby objects
    for (FXint i = 0; i <items.no(); i++) FXRbUnregisterRubyObj(items[i]);
}

void FXRbIconList::unregisterOwnedObjects(FXIconList *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);
    FXRbUnregisterRubyObj(self->getHeader());
    for (FXint i = 0; i <self->getNumItems(); i++) FXRbUnregisterRubyObj(self->getItem(i));
}

void FXRbImageView::unregisterOwnedObjects(FXImageView *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);
}

void FXRbList::unregisterOwnedObjects(FXList *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);
    for (FXint i = 0; i < self->getNumItems(); i++) FXRbUnregisterRubyObj(self->getItem(i));
}

void FXRbColorList::unregisterOwnedObjects(FXColorList *self)
{
    FXRbList::unregisterOwnedObjects(self);
}

void FXRbScrollWindow::unregisterOwnedObjects(FXScrollWindow *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);
}

void FXRbTable::unregisterOwnedObjects(FXTable *self)
{
    FXint r,c;
    FXRbScrollArea::unregisterOwnedObjects(self);
    FXRbHeader::unregisterOwnedObjects(self->getRowHeader());
    FXRbHeader::unregisterOwnedObjects(self->getColumnHeader());
    FXRbUnregisterRubyObj(self->getRowHeader());
    FXRbUnregisterRubyObj(self->getColumnHeader());
    for(r=0; r<self->getNumRows(); r++){
      for(c=0; c<self->getNumColumns(); c++){
        FXRbUnregisterRubyObj(self->getItem(r,c));
        }
      }
}

void FXRbText::unregisterOwnedObjects(FXText *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);
}

void FXRbTreeList::unregisterOwnedObjects(FXTreeList *self)
{
    FXRbScrollArea::unregisterOwnedObjects(self);

    // Save pointer(s) to the soon-to-be-destroyed items
    FXObjectListOf<FXTreeItem> items;
    FXRbTreeList::enumerateItems(self->getFirstItem(), self->getLastItem(), items);

    // Now zero-out pointers held by still-alive Ruby objects
    for (FXint i = 0; i < items.no(); i++) FXRbUnregisterRubyObj(items[i]);
}
