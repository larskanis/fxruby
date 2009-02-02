/********************************************************************************
*                                                                               *
*                          C o l o r   S e l e c t o r                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXColorSelector.h 2187 2005-08-24 07:41:39Z lyle $                   *
********************************************************************************/
#ifndef FXCOLORSELECTOR_H
#define FXCOLORSELECTOR_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


class FXTabBook;
class FXColorBar;
class FXColorWell;
class FXColorWheel;
class FXColorRing;
class FXColorList;
class FXList;
class FXSlider;
class FXTextField;
class FXButton;
class FXIcon;
class FXLabel;


/// Color selection widget
class FXAPI FXColorSelector : public FXPacker {
  FXDECLARE(FXColorSelector)
protected:
  FXTabBook    *panels;               // Color panes
  FXColorWell  *well;                 // Main well
  FXColorList  *list;                 // List of color names
  FXColorRing  *wheel;                // Color ring
  FXSlider     *rgbaslider[4];        // RGBA sliders
  FXTextField  *rgbatext[4];          // RGBA text fields
  FXSlider     *hsvaslider[4];        // HSVA sliders
  FXTextField  *hsvatext[4];          // HSVA text fields
  FXSlider     *cmyslider[4];         // CMY sliders
  FXTextField  *cmytext[4];           // CMY text fields
  FXColorWell  *colorwells[24];       // Custom color wells
  FXIcon       *eyedropicon;          // Icon for eye dropper
  FXIcon       *dialmodeicon;         // Icon for dial mode
  FXIcon       *rgbmodeicon;          // Icon for RGB mode
  FXIcon       *hsvmodeicon;          // Icon for HSV mode
  FXIcon       *cmymodeicon;          // Icon for CMY mode
  FXIcon       *txtmodeicon;          // Icon for TEXT mode
  FXButton     *accept;               // Accept button
  FXButton     *cancel;               // Cancel button
  FXfloat       rgba[4];              // Accurate RGBA color
  FXfloat       hsva[4];              // Accurate HSVA color
protected:
  static const FXchar* wellname[24];  // Well names
protected:
  FXColorSelector(){}
  void updateWell();
private:
  FXColorSelector(const FXColorSelector&);
  FXColorSelector &operator=(const FXColorSelector&);
public:
  long onCmdWell(FXObject*,FXSelector,void*);
  long onChgWell(FXObject*,FXSelector,void*);
  long onCmdRGBSlider(FXObject*,FXSelector,void*);
  long onUpdRGBSlider(FXObject*,FXSelector,void*);
  long onCmdRGBText(FXObject*,FXSelector,void*);
  long onUpdRGBText(FXObject*,FXSelector,void*);
  long onCmdHSVSlider(FXObject*,FXSelector,void*);
  long onUpdHSVSlider(FXObject*,FXSelector,void*);
  long onCmdHSVText(FXObject*,FXSelector,void*);
  long onUpdHSVText(FXObject*,FXSelector,void*);
  long onCmdCMYSlider(FXObject*,FXSelector,void*);
  long onUpdCMYSlider(FXObject*,FXSelector,void*);
  long onCmdCMYText(FXObject*,FXSelector,void*);
  long onUpdCMYText(FXObject*,FXSelector,void*);
  long onCmdList(FXObject*,FXSelector,void*);
  long onCmdCustomWell(FXObject*,FXSelector,void*);
  long onChgCustomWell(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdActivePane(FXObject*,FXSelector,void*);
  long onCmdAlphaSlider(FXObject*,FXSelector,void*);
  long onUpdAlphaSlider(FXObject*,FXSelector,void*);
  long onCmdAlphaText(FXObject*,FXSelector,void*);
  long onUpdAlphaText(FXObject*,FXSelector,void*);
  long onUpdAlphaLabel(FXObject*,FXSelector,void*);
  long onCmdWheel(FXObject*,FXSelector,void*);
  long onUpdWheel(FXObject*,FXSelector,void*);
  long onCmdColorPick(FXObject*,FXSelector,void*);
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

  /// Construct a new ColorSelector
  FXColorSelector(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create the ColorSelector
  virtual void create();

  /// Return a pointer to the "Accept" button
  FXButton *acceptButton() const { return accept; }

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const { return cancel; }

  /// Set the selected color
  void setRGBA(FXColor clr);

  /// Get the selected color
  FXColor getRGBA() const;

  /// Return true if only opaque colors allowed
  FXbool isOpaqueOnly() const;

  /// Change opaque only mode
  void setOpaqueOnly(FXbool opaque);

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXColorSelector();
  };

}

#endif
