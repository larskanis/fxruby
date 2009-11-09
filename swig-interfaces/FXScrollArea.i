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

/// ScrollBar options
enum {
  SCROLLERS_NORMAL     = 0,                                 /// Show the scrollbars when needed 
  HSCROLLER_ALWAYS     = 0x00008000,                        /// Always show horizontal scrollers 
  HSCROLLER_NEVER      = 0x00010000,                        /// Never show horizontal scrollers
  VSCROLLER_ALWAYS     = 0x00020000,                        /// Always show vertical scrollers
  VSCROLLER_NEVER      = 0x00040000,                        /// Never show vertical scrollers
  HSCROLLING_ON        = 0,                                 /// Horizontal scrolling turned on (default)
  HSCROLLING_OFF       = HSCROLLER_NEVER|HSCROLLER_ALWAYS,  /// Horizontal scrolling turned off
  VSCROLLING_ON        = 0,                                 /// Vertical scrolling turned on (default)
  VSCROLLING_OFF       = VSCROLLER_NEVER|VSCROLLER_ALWAYS,  /// Vertical scrolling turned off
  SCROLLERS_TRACK      = 0,                                 /// Scrollers track continuously for smooth scrolling
  SCROLLERS_DONT_TRACK = 0x00080000                         /// Scrollers don't track continuously
  };


class FXScrollBar;
class FXScrollCorner;

%rename("contentX")			FXScrollArea::getContentX() const;
%rename("contentY")			FXScrollArea::getContentY() const;

/**
* The scroll area widget manages a content area and a viewport
* area through which the content is viewed.  When the content area
* becomes larger than the viewport area, scrollbars are placed to
* permit viewing of the entire content by scrolling the content.
* Depending on the mode, scrollbars may be displayed on an as-needed
* basis, always, or never.
* Normally, the scroll area's size and the content's size are independent;
* however, it is possible to disable scrolling in the horizontal 
* (vertical) direction.  In this case, the content width (height) 
* will influence the width (height) of the scroll area widget.
* For content which is time-consuming to repaint, continuous
* scrolling may be turned off.
*/
class FXScrollArea : public FXComposite {
protected:
  FXScrollBar    *horizontal;   // Horizontal scroll bar
  FXScrollBar    *vertical;     // Vertical scroll bar
  FXScrollCorner *corner;       // Scroll corner
  FXint           pos_x;        // X scroll position (pos_x<=0)
  FXint           pos_y;        // Y scroll position (pos_y<=0)
protected:
  FXScrollArea();
  // FXScrollArea(FXComposite* p,FXuint opts,FXint x,FXint y,FXint w,FXint h);
  virtual void moveContents(FXint x,FXint y);
  FXbool startAutoScroll(FXEvent *event,FXbool onlywheninside=false);
  void stopAutoScroll();
  void placeScrollBars(FXint vw,FXint vh);
public:
  long onHMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onVMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onHScrollerChanged(FXObject*,FXSelector,void* PTR_INT);
  long onVScrollerChanged(FXObject*,FXSelector,void* PTR_INT);
  long onHScrollerDragged(FXObject*,FXSelector,void* PTR_INT);
  long onVScrollerDragged(FXObject*,FXSelector,void* PTR_INT);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  %extend {
    /// Constructor
    FXScrollArea(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbScrollArea(p,opts,x,y,w,h);
      }
    }

  /// Return content area x position
  FXint getContentX() const;

  /// Return content area y position
  FXint getContentY() const;

  /// Change scroll style
  void setScrollStyle(FXuint style);
  
  /// Return scroll style
  FXuint getScrollStyle() const;
  
  /// Return TRUE if horizontally scrollable
  FXbool isHorizontalScrollable() const;
  
  /// Return TRUE if vertically scrollable
  FXbool isVerticalScrollable() const;

  /// Return a pointer to the horizontal scrollbar
  FXScrollBar* horizontalScrollBar() const;

  /// Return a pointer to the vertical scrollbar
  FXScrollBar* verticalScrollBar() const;

  /// Set the current position
  void setPosition(FXint x,FXint y);

  /// Destructor
  virtual ~FXScrollArea();
  };


DECLARE_FXOBJECT_VIRTUALS(FXScrollArea)
DECLARE_FXID_VIRTUALS(FXScrollArea)
DECLARE_FXDRAWABLE_VIRTUALS(FXScrollArea)
DECLARE_FXWINDOW_VIRTUALS(FXScrollArea)
DECLARE_FXSCROLLAREA_VIRTUALS(FXScrollArea)

%{
static swig_type_info *FXScrollArea_dynamic_cast(void **ptr) {
    FXScrollArea **ppScrollArea = reinterpret_cast<FXScrollArea **>(ptr);
    FXBitmapView *pBitmapView=dynamic_cast<FXBitmapView*>(*ppScrollArea);
    if(pBitmapView){
      *ptr=reinterpret_cast<void*>(pBitmapView);
      return SWIG_TypeQuery("FXBitmapView *");
      }
    FXFoldingList *pFoldingList=dynamic_cast<FXFoldingList*>(*ppScrollArea);
    if(pFoldingList){
      *ptr=reinterpret_cast<void*>(pFoldingList);
      return SWIG_TypeQuery("FXFoldingList *");
      }
    FXIconList *pIconList=dynamic_cast<FXIconList*>(*ppScrollArea);
    if(pIconList){
      *ptr=reinterpret_cast<void*>(pIconList);
      return SWIG_TypeQuery("FXIconList *");
      }
    FXImageView *pImageView=dynamic_cast<FXImageView*>(*ppScrollArea);
    if(pImageView){
      *ptr=reinterpret_cast<void*>(pImageView);
      return SWIG_TypeQuery("FXImageView *");
      }
    FXList *pList=dynamic_cast<FXList*>(*ppScrollArea);
    if(pList){
      *ptr=reinterpret_cast<void*>(pList);
      return SWIG_TypeQuery("FXList *");
      }
    FXMDIClient *pMDIClient=dynamic_cast<FXMDIClient*>(*ppScrollArea);
    if(pMDIClient){
      *ptr=reinterpret_cast<void*>(pMDIClient);
      return SWIG_TypeQuery("FXMDIClient *");
      }
    FXScrollWindow *pScrollWindow=dynamic_cast<FXScrollWindow*>(*ppScrollArea);
    if(pScrollWindow){
      *ptr=reinterpret_cast<void*>(pScrollWindow);
      return SWIG_TypeQuery("FXScrollWindow *");
      }
    FXTable *pTable=dynamic_cast<FXTable*>(*ppScrollArea);
    if(pTable){
      *ptr=reinterpret_cast<void*>(pTable);
      return SWIG_TypeQuery("FXTable *");
      }
    FXText *pText=dynamic_cast<FXText*>(*ppScrollArea);
    if(pText){
      *ptr=reinterpret_cast<void*>(pText);
      return SWIG_TypeQuery("FXText *");
      }
    FXTreeList *pTreeList=dynamic_cast<FXTreeList*>(*ppScrollArea);
    if(pTreeList){
      *ptr=reinterpret_cast<void*>(pTreeList);
      return SWIG_TypeQuery("FXTreeList *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXScrollArea, FXScrollArea_dynamic_cast);

