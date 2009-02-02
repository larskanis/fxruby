/********************************************************************************
*                                                                               *
*                        C o l o r W h e e l   W i d g e t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXColorWheel.h 2188 2005-08-24 07:48:22Z lyle $                      *
********************************************************************************/
#ifndef FXCOLORWHEEL_H
#define FXCOLORWHEEL_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


class FXImage;


/**
* A ColorWheel is a widget which controls the hue and saturation values of a
* color.  It is most often used together with a Color Bar which controls the
* brighness.
*/
class FXAPI FXColorWheel : public FXFrame {
  FXDECLARE(FXColorWheel)
protected:
  FXImage  *dial;         // HSV dial image
  FXfloat   hsv[3];       // Hue, saturation, value
  FXint     dialx;        // Dial x location
  FXint     dialy;        // Dial Y location
  FXint     spotx;        // Spot x location
  FXint     spoty;        // Spot Y location
  FXString  tip;          // Tooltip value
  FXString  help;         // Help value
protected:
  FXColorWheel();
  void updatedial();
  void movespot(FXint x,FXint y);
  FXbool hstoxy(FXint& x,FXint& y,FXfloat h,FXfloat s) const;
  FXbool xytohs(FXfloat& h,FXfloat& s,FXint x,FXint y) const;
private:
  FXColorWheel(const FXColorWheel&);
  FXColorWheel &operator=(const FXColorWheel&);
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

  /// Construct color wheel with initial color clr
  FXColorWheel(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

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
  virtual ~FXColorWheel();
  };

}

#endif
