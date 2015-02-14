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

/// Popup internal orientation
enum {
  POPUP_VERTICAL   = 0,               /// Vertical orientation
  POPUP_HORIZONTAL = 0x00020000,      /// Horizontal orientation
  POPUP_SHRINKWRAP = 0x00040000       /// Shrinkwrap to content
  };


/// Popup window
class FXPopup : public FXShell {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusNext(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusPrev(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onMap(FXObject*,FXSelector,void* PTR_EVENT);
  long onButtonPress(FXObject*,FXSelector,void* PTR_IGNORE);
  long onButtonRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdUnpost(FXObject*,FXSelector,void* PTR_IGNORE);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdChoice(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_CHOICE=FXShell::ID_LAST,
    ID_LAST=ID_CHOICE+1000
    };
public:

  /// Construct popup pane
  %extend {
    FXPopup(FXWindow* owner,FXuint opts=POPUP_VERTICAL|FRAME_RAISED|FRAME_THICK,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbPopup(owner,opts,x,y,w,h);
      }
    }

  /// Return a pointer to the prior active popup
  FXPopup* getPrevActive() const;

  /// Return a pointer to the next active popup
  FXPopup* getNextActive() const;

  /// Change frame style
  void setFrameStyle(FXuint style);

  /// Return frame style
  FXuint getFrameStyle() const;

  /// Return border width
  FXint getBorderWidth() const;

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Return highlight color
  FXColor getHiliteColor() const;

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Return shadow color
  FXColor getShadowColor() const;

  /// Change border color
  void setBorderColor(FXColor clr);

  /// Return border color
  FXColor getBorderColor() const;

  /// Change base color
  void setBaseColor(FXColor clr);

  /// Return base color
  FXColor getBaseColor() const;

  /// Return current grab owner
  FXWindow* getGrabOwner() const;

  /// Return popup orientation
  FXuint getOrientation() const;

  /// Change popup orientation
  void setOrientation(FXuint orient);

  /// Return shrinkwrap mode
  FXbool getShrinkWrap() const;

  /// Change shrinkwrap mode
  void setShrinkWrap(FXbool sw);

  /// Destructor
  virtual ~FXPopup();
  };


DECLARE_FXOBJECT_VIRTUALS(FXPopup)
DECLARE_FXID_VIRTUALS(FXPopup)
DECLARE_FXDRAWABLE_VIRTUALS(FXPopup)
DECLARE_FXWINDOW_VIRTUALS(FXPopup)
DECLARE_FXPOPUP_VIRTUALS(FXPopup)

%{
static swig_type_info *FXPopup_dynamic_cast(void **ptr) {
    FXPopup **ppPopup = reinterpret_cast<FXPopup **>(ptr);
    FXMenuPane *pMenuPane=dynamic_cast<FXMenuPane*>(*ppPopup);
    if(pMenuPane){
      *ptr=reinterpret_cast<void*>(pMenuPane);
      return SWIG_TypeQuery("FXMenuPane *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXPopup, FXPopup_dynamic_cast);

