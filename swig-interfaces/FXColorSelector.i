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

class FXTabBook;
class FXColorBar;
class FXColorWell;
class FXColorWheel;
class FXList;
class FXSlider;
class FXTextField;
class FXButton;
class FXIcon;
class FXLabel;


/// Color selection widget
class FXColorSelector : public FXPacker {
public:
  long onCmdWell(FXObject*,FXSelector,void* PTR_IGNORE);
  long onChgWell(FXObject*,FXSelector,void* PTR_COLOR);
  long onCmdRGBSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdRGBSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRGBText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdRGBText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHSVSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHSVSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHSVText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHSVText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCMYSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCMYSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCMYText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCMYText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdList(FXObject*,FXSelector,void* PTR_INT);
  long onCmdCustomWell(FXObject*,FXSelector,void* PTR_COLOR);
  long onChgCustomWell(FXObject*,FXSelector,void* PTR_COLOR);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_COLOR);
  long onCmdActivePane(FXObject*,FXSelector,void* PTR_INT);
  long onCmdAlphaSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdAlphaSlider(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdAlphaText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdAlphaText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdAlphaLabel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdWheel(FXObject*,FXSelector,void* PTR_FLTARRAY);
  long onUpdWheel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdColorPick(FXObject*,FXSelector,void* PTR_POINT);
public:
  enum {
    ID_CUSTOM_FIRST=FXPacker::ID_LAST,
    ID_CUSTOM_LAST=ID_CUSTOM_FIRST+24,
    ID_RGB_RED_SLIDER,
    ID_RGB_GREEN_SLIDER,
    ID_RGB_BLUE_SLIDER,
    ID_RGB_RED_TEXT,
    ID_RGB_GREEN_TEXT,
    ID_RGB_BLUE_TEXT,
    ID_HSV_HUE_SLIDER,
    ID_HSV_SATURATION_SLIDER,
    ID_HSV_VALUE_SLIDER,
    ID_HSV_HUE_TEXT,
    ID_HSV_SATURATION_TEXT,
    ID_HSV_VALUE_TEXT,
    ID_CMY_CYAN_SLIDER,
    ID_CMY_MAGENTA_SLIDER,
    ID_CMY_YELLOW_SLIDER,
    ID_CMY_CYAN_TEXT,
    ID_CMY_MAGENTA_TEXT,
    ID_CMY_YELLOW_TEXT,
    ID_DIAL_WHEEL,
    ID_COLOR_LIST,
    ID_WELL_CHANGED,
    ID_ACTIVEPANE,
    ID_ALPHA_SLIDER,
    ID_ALPHA_TEXT,
    ID_ALPHA_LABEL,
    ID_COLORPICK,
    ID_LAST
    };
public:
  %extend {
    /// Construct a new ColorSelector
    FXColorSelector(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbColorSelector(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return a pointer to the "Accept" button
  FXButton *acceptButton() const;

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const;

  /// Set the selected color
  void setRGBA(FXColor clr);

  /// Get the selected color
  FXColor getRGBA() const;

  /// Return true if only opaque colors allowed
  FXbool isOpaqueOnly() const;

  /// Change opaque only mode
  void setOpaqueOnly(FXbool opaque);

  /// Destructor
  virtual ~FXColorSelector();
  };


DECLARE_FXOBJECT_VIRTUALS(FXColorSelector)
DECLARE_FXID_VIRTUALS(FXColorSelector)
DECLARE_FXDRAWABLE_VIRTUALS(FXColorSelector)
DECLARE_FXWINDOW_VIRTUALS(FXColorSelector)

