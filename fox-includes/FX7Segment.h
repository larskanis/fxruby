/********************************************************************************
*                                                                               *
*                7 - S e g m e n t   D i s p l a y   W i d g e t                *
*                                                                               *
*********************************************************************************
* Copyright (C) 2004,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FX7Segment.h 2360 2006-03-29 04:10:56Z lyle $                        *
********************************************************************************/
#ifndef FX7SEGMENT_H
#define FX7SEGMENT_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif


namespace FX {

/// 7 Segment styles
enum {
  SEVENSEGMENT_NORMAL   = 0,            /// Draw segments normally
  SEVENSEGMENT_SHADOW   = 0x00080000    /// Draw shadow under the segments
  };


/**
* Seven-segment (eg LCD/watch style) widget, useful for making
* indicators and timers.  Besides numbers, the seven-segment
* display widget can also display some letters and punctuations.
*/
class FXAPI FX7Segment : public FXFrame {
  FXDECLARE(FX7Segment)
protected:
  FXString label;       // Text being shown
  FXColor  textColor;   // Text color
  FXint    thickness;   // Segment thickness
  FXint    cellwidth;   // Width of cell
  FXint    cellheight;  // height of cell
  FXString tip;         // Tooltip
  FXString help;        // Help message
protected:
  FX7Segment();
private:
  FX7Segment(const FX7Segment&);
  FX7Segment &operator=(const FX7Segment&);
  void drawCells(FXDCWindow &dc,FXint x,FXint y,FXint cw,FXint ch);
  void drawSegments(FXDCWindow &dc,FXint x,FXint y,FXint w,FXint h,FXuint segments);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdSetRealValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetRealValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:

  /// Create a seven segment display
  FX7Segment(FXComposite* p,const FXString& text,FXuint opts=SEVENSEGMENT_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Set the text for this label
  void setText(const FXString& text);

  /// Get the text for this label
  FXString getText() const { return label; }

  /// Change text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const { return textColor; }

  /// Get/set cell width
  void setCellWidth(FXint w);
  FXint getCellWidth() const { return cellwidth; }

  /// Get/set cell height
  void setCellHeight(FXint h);
  FXint getCellHeight() const { return cellheight; }

  /// Get/set segment thickness
  void setThickness(FXint t);
  FXint getThickness() const { return thickness; }

  /// Change 7 segment style
  void set7SegmentStyle(FXuint style);

  /// Get current 7 segment style
  FXuint get7SegmentStyle() const;

  /// Set the current text-justification mode.
  void setJustify(FXuint mode);

  /// Get the current text-justification mode.
  FXuint getJustify() const;

  /// Set the status line help text
  void setHelpText(const FXString& text){ help=text; }

  /// Get the status line help text
  const FXString& getHelpText() const { return help; }

  /// Set the tool tip message
  void setTipText(const FXString& text){ tip=text; }

  /// Get the tool tip message
  const FXString& getTipText() const { return tip; }

  /// Save to a stream
  virtual void save(FXStream &store) const;

  /// Load from a stream
  virtual void load(FXStream &store);
  };

}

#endif
