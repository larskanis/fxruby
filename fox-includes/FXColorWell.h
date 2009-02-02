/********************************************************************************
*                                                                               *
*                         C o l o r W e l l   W i d g e t                       *
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
* $Id: FXColorWell.h 2335 2006-01-28 02:33:03Z lyle $                       *
********************************************************************************/
#ifndef FXCOLORWELL_H
#define FXCOLORWELL_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


// Color Well Styles
enum {
  COLORWELL_OPAQUEONLY = 0x00008000,  /// Colors must be opaque
  COLORWELL_SOURCEONLY = 0x00010000,  /// ColorWell is never a target
  COLORWELL_NORMAL     = JUSTIFY_NORMAL
  };



/**
* A color well is a widget which controls color settings.
* Colors may be dragged and dropped from one color well to another.
* A double-click inside a color well will bring up the standard
* color dialog panel to edit the color well's color.
* Colors may be also pasted by name using middle-mouse click into/out of
* color wells from/to other selection-capable applications; for example,
* you can highlight the word `red' and paste it into a color well.
* While the color value is being changed, the color well sends a SEL_CHANGED
* to its target; at the end of the change, it sends a SEL_COMMAND.
* The message data represents the current color value, of the type FXColor.
*/
class FXAPI FXColorWell : public FXFrame {
  FXDECLARE(FXColorWell)
protected:
  FXColor   wellColor[2];             // Pixel value of RGBA over black and white
  FXColor   rgba;                     // Color with RGB and Alpha
  FXString  tip;                      // Tooltip value
  FXString  help;                     // Help value
protected:
  FXColorWell();
  static FXColor rgbaoverblack(FXColor clr);
  static FXColor rgbaoverwhite(FXColor clr);
private:
  FXColorWell(const FXColorWell&);
  FXColorWell &operator=(const FXColorWell&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMiddleBtnPress(FXObject*,FXSelector,void*);
  long onMiddleBtnRelease(FXObject*,FXSelector,void*);
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
  long onUngrabbed(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onBeginDrag(FXObject*,FXSelector,void*);
  long onEndDrag(FXObject*,FXSelector,void*);
  long onDragged(FXObject*,FXSelector,void*);
  long onFocusIn(FXObject*,FXSelector,void*);
  long onFocusOut(FXObject*,FXSelector,void*);
  long onDNDEnter(FXObject*,FXSelector,void*);
  long onDNDLeave(FXObject*,FXSelector,void*);
  long onDNDMotion(FXObject*,FXSelector,void*);
  long onDNDDrop(FXObject*,FXSelector,void*);
  long onDNDRequest(FXObject*,FXSelector,void*);
  long onSelectionLost(FXObject*,FXSelector,void*);
  long onSelectionGained(FXObject*,FXSelector,void*);
  long onSelectionRequest(FXObject*,FXSelector,void*);
  long onClicked(FXObject*,FXSelector,void*);
  long onDoubleClicked(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdColorWell(FXObject*,FXSelector,void*);
  long onChgColorWell(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:
  enum {
    ID_COLORDIALOG=FXFrame::ID_LAST,
    ID_LAST
    };
public:

  /// Construct color well with initial color clr
  FXColorWell(FXComposite* p,FXColor clr=0,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=COLORWELL_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Returns true because a color well can receive focus
  virtual bool canFocus() const;

  /// Move the focus to this window
  virtual void setFocus();

  /// Remove the focus from this window
  virtual void killFocus();

  /// Set color
  void setRGBA(FXColor clr,FXbool notify=FALSE);

  /// Get color
  FXColor getRGBA() const { return rgba; }

  /// Set status line help text for this color well
  void setHelpText(const FXString& text){ help=text; }

  /// Get status line help text for this color well
  const FXString& getHelpText() const { return help; }

  /// Set tool tip message for this color well
  void setTipText(const FXString& text){ tip=text; }

  /// Get tool tip message for this color well
  const FXString& getTipText() const { return tip; }

  /// Return true if only opaque colors allowed
  FXbool isOpaqueOnly() const;

  /// Change opaque only mode
  void setOpaqueOnly(FXbool opaque);

  /// Save color well to a stream
  virtual void save(FXStream& store) const;

  /// Load color well from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXColorWell();
  };

}

#endif
