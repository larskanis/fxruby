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

/// Default spacing
enum { DEFAULT_SPACING = 4 };

/**
* Packer is a layout manager which automatically places child windows
* inside its area against the left, right, top, or bottom side.
* Each time a child is placed, the remaining space is decreased by the
* amount of space taken by the child window.
* The side against which a child is placed is determined by the LAYOUT_SIDE_TOP,
* LAYOUT_SIDE_BOTTOM, LAYOUT_SIDE_LEFT, and LAYOUT_SIDE_RIGHT hints given by
* the child window.  Other layout hints from the child are observed as far as
* sensible.  So for example, a child placed against the right edge can still
* have LAYOUT_FILL_Y or LAYOUT_TOP, and so on.
* The last child may have both LAYOUT_FILL_X and LAYOUT_FILL_Y, in which
* case it will be placed to take all remaining space.
*/
class FXPacker : public FXComposite {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Construct packer layout manager
    FXPacker(FXComposite *p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbPacker(p,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Change frame style
  void setFrameStyle(FXuint style);

  /// Get current frame style
  FXuint getFrameStyle() const;

  /// Change packing hints
  void setPackingHints(FXuint ph);

  /// Return packing hints
  FXuint getPackingHints() const;

  /// Get border width
  FXint getBorderWidth() const;

  /// Change top padding
  void setPadTop(FXint pt);

  /// Get top interior padding
  FXint getPadTop() const;

  /// Change bottom padding
  void setPadBottom(FXint pb);

  /// Get bottom interior padding
  FXint getPadBottom() const;

  /// Change left padding
  void setPadLeft(FXint pl);

  /// Get left interior padding
  FXint getPadLeft() const;

  /// Change right padding
  void setPadRight(FXint pr);

  /// Get right interior padding
  FXint getPadRight() const;

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Get highlight color
  FXColor getHiliteColor() const;

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Get shadow color
  FXColor getShadowColor() const;

  /// Change border color
  void setBorderColor(FXColor clr);

  /// Get border color
  FXColor getBorderColor() const;

  /// Change base gui color
  void setBaseColor(FXColor clr);

  /// Get base gui color
  FXColor getBaseColor() const;

  /// Change horizontal inter-child spacing
  void setHSpacing(FXint hs);

  /// Return current horizontal inter-child spacing
  FXint getHSpacing() const;

  /// Change vertical inter-child spacing
  void setVSpacing(FXint vs);

  /// Return current vertical inter-child spacing
  FXint getVSpacing() const;

  /// Destructor
  virtual ~FXPacker();
  };


DECLARE_FXOBJECT_VIRTUALS(FXPacker)
DECLARE_FXID_VIRTUALS(FXPacker)
DECLARE_FXDRAWABLE_VIRTUALS(FXPacker)
DECLARE_FXWINDOW_VIRTUALS(FXPacker)

%{
static swig_type_info *FXPacker_dynamic_cast(void **ptr) {
    FXPacker **ppPacker = reinterpret_cast<FXPacker **>(ptr);
    FXColorSelector *pColorSelector=dynamic_cast<FXColorSelector*>(*ppPacker);
    if(pColorSelector){
      *ptr=reinterpret_cast<void*>(pColorSelector);
      return SWIG_TypeQuery("FXColorSelector *");
      }
    FXComboBox *pComboBox=dynamic_cast<FXComboBox*>(*ppPacker);
    if(pComboBox){
      *ptr=reinterpret_cast<void*>(pComboBox);
      return SWIG_TypeQuery("FXComboBox *");
      }
    FXDirSelector *pDirSelector=dynamic_cast<FXDirSelector*>(*ppPacker);
    if(pDirSelector){
      *ptr=reinterpret_cast<void*>(pDirSelector);
      return SWIG_TypeQuery("FXDirSelector *");
      }
    FXDockBar *pDockBar=dynamic_cast<FXDockBar*>(*ppPacker);
    if(pDockBar){
      *ptr=reinterpret_cast<void*>(pDockBar);
      return SWIG_TypeQuery("FXDockBar *");
      }
    FXDockSite *pDockSite=dynamic_cast<FXDockSite*>(*ppPacker);
    if(pDockSite){
      *ptr=reinterpret_cast<void*>(pDockSite);
      return SWIG_TypeQuery("FXDockSite *");
      }
    FXFileSelector *pFileSelector=dynamic_cast<FXFileSelector*>(*ppPacker);
    if(pFileSelector){
      *ptr=reinterpret_cast<void*>(pFileSelector);
      return SWIG_TypeQuery("FXFileSelector *");
      }
    FXFontSelector *pFontSelector=dynamic_cast<FXFontSelector*>(*ppPacker);
    if(pFontSelector){
      *ptr=reinterpret_cast<void*>(pFontSelector);
      return SWIG_TypeQuery("FXFontSelector *");
      }
    FXGroupBox *pGroupBox=dynamic_cast<FXGroupBox*>(*ppPacker);
    if(pGroupBox){
      *ptr=reinterpret_cast<void*>(pGroupBox);
      return SWIG_TypeQuery("FXGroupBox *");
      }
    FXHorizontalFrame *pHorizontalFrame=dynamic_cast<FXHorizontalFrame*>(*ppPacker);
    if(pHorizontalFrame){
      *ptr=reinterpret_cast<void*>(pHorizontalFrame);
      return SWIG_TypeQuery("FXHorizontalFrame *");
      }
    FXListBox *pListBox=dynamic_cast<FXListBox*>(*ppPacker);
    if(pListBox){
      *ptr=reinterpret_cast<void*>(pListBox);
      return SWIG_TypeQuery("FXListBox *");
      }
    FXMatrix *pMatrix=dynamic_cast<FXMatrix*>(*ppPacker);
    if(pMatrix){
      *ptr=reinterpret_cast<void*>(pMatrix);
      return SWIG_TypeQuery("FXMatrix *");
      }
    FXRealSpinner *pRealSpinner=dynamic_cast<FXRealSpinner*>(*ppPacker);
    if(pRealSpinner){
      *ptr=reinterpret_cast<void*>(pRealSpinner);
      return SWIG_TypeQuery("FXRealSpinner *");
      }
    FXSpinner *pSpinner=dynamic_cast<FXSpinner*>(*ppPacker);
    if(pSpinner){
      *ptr=reinterpret_cast<void*>(pSpinner);
      return SWIG_TypeQuery("FXSpinner *");
      }
    FXSwitcher *pSwitcher=dynamic_cast<FXSwitcher*>(*ppPacker);
    if(pSwitcher){
      *ptr=reinterpret_cast<void*>(pSwitcher);
      return SWIG_TypeQuery("FXSwitcher *");
      }
    FXTabBar *pTabBar=dynamic_cast<FXTabBar*>(*ppPacker);
    if(pTabBar){
      *ptr=reinterpret_cast<void*>(pTabBar);
      return SWIG_TypeQuery("FXTabBar *");
      }
    FXTreeListBox *pTreeListBox=dynamic_cast<FXTreeListBox*>(*ppPacker);
    if(pTreeListBox){
      *ptr=reinterpret_cast<void*>(pTreeListBox);
      return SWIG_TypeQuery("FXTreeListBox *");
      }
    FXVerticalFrame *pVerticalFrame=dynamic_cast<FXVerticalFrame*>(*ppPacker);
    if(pVerticalFrame){
      *ptr=reinterpret_cast<void*>(pVerticalFrame);
      return SWIG_TypeQuery("FXVerticalFrame *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXPacker, FXPacker_dynamic_cast);

