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

/// Justification modes
enum {
  JUSTIFY_NORMAL       = 0,			      /// Default justification is centered text
  JUSTIFY_CENTER_X     = 0,			      /// Text is centered horizontally
  JUSTIFY_LEFT         = 0x00008000,		      /// Text is left-justified
  JUSTIFY_RIGHT        = 0x00010000,		      /// Text is right-justified
  JUSTIFY_HZ_APART     = JUSTIFY_LEFT|JUSTIFY_RIGHT,  /// Combination of JUSTIFY_LEFT & JUSTIFY_RIGHT
  JUSTIFY_CENTER_Y     = 0,			      /// Text is centered vertically
  JUSTIFY_TOP          = 0x00020000,		      /// Text is aligned with label top
  JUSTIFY_BOTTOM       = 0x00040000,		      /// Text is aligned with label bottom
  JUSTIFY_VT_APART     = JUSTIFY_TOP|JUSTIFY_BOTTOM   /// Combination of JUSTIFY_TOP & JUSTIFY_BOTTOM
  };


/// Default padding
enum { DEFAULT_PAD = 2 };


/// Base Frame
class FXFrame : public FXWindow {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Construct frame window
    FXFrame(FXComposite* p,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbFrame(p,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change frame style
  void setFrameStyle(FXuint style);

  /// Get current frame style
  FXuint getFrameStyle() const;

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
  };


DECLARE_FXOBJECT_VIRTUALS(FXFrame)
DECLARE_FXID_VIRTUALS(FXFrame)
DECLARE_FXDRAWABLE_VIRTUALS(FXFrame)
DECLARE_FXWINDOW_VIRTUALS(FXFrame)

%{
static swig_type_info *FXFrame_dynamic_cast(void **ptr) {
    FXFrame **ppFrame = reinterpret_cast<FXFrame **>(ptr);
    FX7Segment *p7Segment=dynamic_cast<FX7Segment*>(*ppFrame);
    if(p7Segment){
      *ptr=reinterpret_cast<void*>(p7Segment);
      return SWIG_TypeQuery("FX7Segment *");
      }
    FXArrowButton *pArrowButton=dynamic_cast<FXArrowButton*>(*ppFrame);
    if(pArrowButton){
      *ptr=reinterpret_cast<void*>(pArrowButton);
      return SWIG_TypeQuery("FXArrowButton *");
      }
    FXBitmapFrame *pBitmapFrame=dynamic_cast<FXBitmapFrame*>(*ppFrame);
    if(pBitmapFrame){
      *ptr=reinterpret_cast<void*>(pBitmapFrame);
      return SWIG_TypeQuery("FXBitmapFrame *");
      }
    FXColorBar *pColorBar=dynamic_cast<FXColorBar*>(*ppFrame);
    if(pColorBar){
      *ptr=reinterpret_cast<void*>(pColorBar);
      return SWIG_TypeQuery("FXColorBar *");
      }
    FXColorRing *pColorRing=dynamic_cast<FXColorRing*>(*ppFrame);
    if(pColorRing){
      *ptr=reinterpret_cast<void*>(pColorRing);
      return SWIG_TypeQuery("FXColorRing *");
      }
    FXColorWell *pColorWell=dynamic_cast<FXColorWell*>(*ppFrame);
    if(pColorWell){
      *ptr=reinterpret_cast<void*>(pColorWell);
      return SWIG_TypeQuery("FXColorWell *");
      }
    FXColorWheel *pColorWheel=dynamic_cast<FXColorWheel*>(*ppFrame);
    if(pColorWheel){
      *ptr=reinterpret_cast<void*>(pColorWheel);
      return SWIG_TypeQuery("FXColorWheel *");
      }
    FXDial *pDial=dynamic_cast<FXDial*>(*ppFrame);
    if(pDial){
      *ptr=reinterpret_cast<void*>(pDial);
      return SWIG_TypeQuery("FXDial *");
      }
    FXDockHandler *pDockHandler=dynamic_cast<FXDockHandler*>(*ppFrame);
    if(pDockHandler){
      *ptr=reinterpret_cast<void*>(pDockHandler);
      return SWIG_TypeQuery("FXDockHandler *");
      }
    FXHeader *pHeader=dynamic_cast<FXHeader*>(*ppFrame);
    if(pHeader){
      *ptr=reinterpret_cast<void*>(pHeader);
      return SWIG_TypeQuery("FXHeader *");
      }
    FXImageFrame *pImageFrame=dynamic_cast<FXImageFrame*>(*ppFrame);
    if(pImageFrame){
      *ptr=reinterpret_cast<void*>(pImageFrame);
      return SWIG_TypeQuery("FXImageFrame *");
      }
    FXKnob *pKnob=dynamic_cast<FXKnob*>(*ppFrame);
    if(pKnob){
      *ptr=reinterpret_cast<void*>(pKnob);
      return SWIG_TypeQuery("FXKnob *");
      }
    FXLabel *pLabel=dynamic_cast<FXLabel*>(*ppFrame);
    if(pLabel){
      *ptr=reinterpret_cast<void*>(pLabel);
      return SWIG_TypeQuery("FXLabel *");
      }
    FXProgressBar *pProgressBar=dynamic_cast<FXProgressBar*>(*ppFrame);
    if(pProgressBar){
      *ptr=reinterpret_cast<void*>(pProgressBar);
      return SWIG_TypeQuery("FXProgressBar *");
      }
    FXRealSlider *pRealSlider=dynamic_cast<FXRealSlider*>(*ppFrame);
    if(pRealSlider){
      *ptr=reinterpret_cast<void*>(pRealSlider);
      return SWIG_TypeQuery("FXRealSlider *");
      }
    FXSeparator *pSeparator=dynamic_cast<FXSeparator*>(*ppFrame);
    if(pSeparator){
      *ptr=reinterpret_cast<void*>(pSeparator);
      return SWIG_TypeQuery("FXSeparator *");
      }
    FXSlider *pSlider=dynamic_cast<FXSlider*>(*ppFrame);
    if(pSlider){
      *ptr=reinterpret_cast<void*>(pSlider);
      return SWIG_TypeQuery("FXSlider *");
      }
    FXStatusLine *pStatusLine=dynamic_cast<FXStatusLine*>(*ppFrame);
    if(pStatusLine){
      *ptr=reinterpret_cast<void*>(pStatusLine);
      return SWIG_TypeQuery("FXStatusLine *");
      }
    FXTextField *pTextField=dynamic_cast<FXTextField*>(*ppFrame);
    if(pTextField){
      *ptr=reinterpret_cast<void*>(pTextField);
      return SWIG_TypeQuery("FXTextField *");
      }
    FXToolBarTab *pToolBarTab=dynamic_cast<FXToolBarTab*>(*ppFrame);
    if(pToolBarTab){
      *ptr=reinterpret_cast<void*>(pToolBarTab);
      return SWIG_TypeQuery("FXToolBarTab *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXFrame, FXFrame_dynamic_cast);

