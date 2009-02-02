/********************************************************************************
*                                                                               *
*                         C o l o r R i n g   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXColorRing.h 2298 2005-12-07 12:03:24Z lyle $                        *
********************************************************************************/
#ifndef FXCOLORRING_H
#define FXCOLORRING_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


class FXImage;


/**
* A Color Ring widget provides an intuitive way to specify a color.
* The outer ring of the widget is rotated to control the hue of the color
* being specified, while the inner triangle varies the color saturation
* and the brightness of the color.  The color saturation axis of the
* triangle goes from a fully saturated "pure" color to "pastel" color;
* the brightness goes from black to a bright color.
*/
class FXAPI FXColorRing : public FXFrame {
  FXDECLARE(FXColorRing)
protected:
  FXImage  *dial;         // HSV dial image
  FXfloat   hsv[3];       // Hue, saturation, value
  FXint     ringwidth;    // Width of hue ring
  FXint     ringouter;    // Outer radius
  FXint     ringinner;    // Inner radius
  FXint     dialx;        // Dial x location
  FXint     dialy;        // Dial y location
  FXint     satvalx;      // Saturation value x
  FXint     satvaly;      // Saturation value y
  FXint     huex;         // Hue x
  FXint     huey;         // Hue y
  FXint     clrx;         // Color corner of triangle
  FXint     clry;
  FXint     blkx;         // Black corner of triangle
  FXint     blky;
  FXint     whtx;         // White corner of triangle
  FXint     whty;
  FXString  tip;          // Tooltip value
  FXString  help;         // Help value
  FXuchar   mode;         // Mode widget is in
protected:
  FXColorRing();
  void updatering();
  FXfloat hueFromXY(FXint x,FXint y) const;
  void hueToXY(FXint& x,FXint& y,FXfloat hue) const;
  void satValToXY(FXint& x,FXint& y,FXfloat s,FXfloat v) const;
  void satValFromXY(FXfloat& s,FXfloat& v,FXint x,FXint y) const;
  FXbool inCorner(FXint x,FXint y) const;
  FXbool inHueRing(FXint x,FXint y) const;
  FXbool inTriangle(FXint x,FXint y) const;
protected:
  enum {
    MOUSE_NONE,         // No mouse operation
    MOUSE_HUE,          // Moving in hue-ring
    MOUSE_SATVAL        // Moving in saturation/value triangle
    };
private:
  FXColorRing(const FXColorRing&);
  FXColorRing &operator=(const FXColorRing&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onMouseWheel(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:

  /// Construct color ring with initial color clr
  FXColorRing(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Change hue
  void setHue(FXfloat h);

  /// Return hue
  FXfloat getHue() const { return hsv[0]; }

  /// Change saturation
  void setSat(FXfloat s);

  /// Return saturation
  FXfloat getSat() const { return hsv[1]; }

  /// Change value
  void setVal(FXfloat v);

  /// Return value
  FXfloat getVal() const { return hsv[2]; }

  /// Set hue, saturation, value
  void setHueSatVal(FXfloat h,FXfloat s,FXfloat v);

  /// Change width of hue ring
  void setRingWidth(FXint rw);

  /// Return width of hue ring
  FXint getRingWidth() const { return ringwidth; }

  /// Set status line help text for this color well
  void setHelpText(const FXString& text){ help=text; }

  /// Get status line help text for this color well
  const FXString& getHelpText() const { return help; }

  /// Set tool tip message for this color well
  void setTipText(const FXString& text){ tip=text; }

  /// Get tool tip message for this color well
  const FXString& getTipText() const { return tip; }

  /// Save color well to a stream
  virtual void save(FXStream& store) const;

  /// Load color well from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXColorRing();
  };

}

#endif
