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

/// Separator Options
enum {
  SEPARATOR_NONE       = 0,               /// Nothing visible
  SEPARATOR_GROOVE     = 0x00008000,      /// Etched-in looking groove
  SEPARATOR_RIDGE      = 0x00010000,      /// Embossed looking ridge
  SEPARATOR_LINE       = 0x00020000       /// Simple line
  };


/**
 * A Separator widget is used to draw a horizontal or vertical divider between
 * groups of controls.  It is purely decorative.  The separator may be drawn
 * in various styles as determined by the SEPARATOR_NONE, SEPARATOR_GROOVE,
 * SEPARATOR_RIDGE, and SEPARATOR_LINE options.  Since its derived from Frame,
 * it can also have the frame's border styles.
 */
class FXSeparator : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:

  %extend {
    /// Constructor
    FXSeparator(FXComposite* p,FXuint opts=SEPARATOR_GROOVE|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0){
      return new FXRbSeparator(p,opts,x,y,w,h,pl,pr,pt,pb);
      }
  }

  /// Change separator style
  void setSeparatorStyle(FXuint style);

  /// Get separator style
  FXuint getSeparatorStyle() const;

  /// Destructor
  virtual ~FXSeparator();
  };


DECLARE_FXOBJECT_VIRTUALS(FXSeparator)
DECLARE_FXID_VIRTUALS(FXSeparator)
DECLARE_FXDRAWABLE_VIRTUALS(FXSeparator)
DECLARE_FXWINDOW_VIRTUALS(FXSeparator)


%{
static swig_type_info *FXSeparator_dynamic_cast(void **ptr) {
    FXSeparator **ppSeparator = reinterpret_cast<FXSeparator **>(ptr);
    FXHorizontalSeparator *pHorizontalSeparator=dynamic_cast<FXHorizontalSeparator*>(*ppSeparator);
    if(pHorizontalSeparator){
      *ptr=reinterpret_cast<void*>(pHorizontalSeparator);
      return SWIG_TypeQuery("FXHorizontalSeparator *");
      }
    FXVerticalSeparator *pVerticalSeparator=dynamic_cast<FXVerticalSeparator*>(*ppSeparator);
    if(pVerticalSeparator){
      *ptr=reinterpret_cast<void*>(pVerticalSeparator);
      return SWIG_TypeQuery("FXVerticalSeparator *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXSeparator, FXSeparator_dynamic_cast);

/// Horizontal separator
class FXHorizontalSeparator : public FXSeparator {
public:

  /// Constructor
  %extend {
    FXHorizontalSeparator(FXComposite* p,FXuint opts=SEPARATOR_GROOVE|LAYOUT_FILL_X,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=1,FXint pr=1,FXint pt=0,FXint pb=0){
      return new FXRbHorizontalSeparator(p,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Destructor
  virtual ~FXHorizontalSeparator();
  };


DECLARE_FXOBJECT_VIRTUALS(FXHorizontalSeparator)
DECLARE_FXID_VIRTUALS(FXHorizontalSeparator)
DECLARE_FXDRAWABLE_VIRTUALS(FXHorizontalSeparator)
DECLARE_FXWINDOW_VIRTUALS(FXHorizontalSeparator)


/// Vertical separator
class FXVerticalSeparator : public FXSeparator {
public:

  /// Constructor
  %extend {
    FXVerticalSeparator(FXComposite* p,FXuint opts=SEPARATOR_GROOVE|LAYOUT_FILL_Y,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=1,FXint pb=1){
      return new FXRbVerticalSeparator(p,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Destructor
  virtual ~FXVerticalSeparator();
  };


DECLARE_FXOBJECT_VIRTUALS(FXVerticalSeparator)
DECLARE_FXID_VIRTUALS(FXVerticalSeparator)
DECLARE_FXDRAWABLE_VIRTUALS(FXVerticalSeparator)
DECLARE_FXWINDOW_VIRTUALS(FXVerticalSeparator)

