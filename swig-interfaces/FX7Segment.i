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


/// 7 Segment styles
enum {
  SEVENSEGMENT_NORMAL   = 0,            /// Draw segments normally
  SEVENSEGMENT_SHADOW   = 0x00080000    /// Draw shadow under the segments
  };

%rename("text=")	FX7Segment::setText(const FXString&);
%rename("text")		FX7Segment::getText() const;
%rename("textColor=")	FX7Segment::setTextColor(FXColor);
%rename("textColor")	FX7Segment::getTextColor() const;
%rename("cellWidth=")	FX7Segment::setCellWidth(FXint);
%rename("cellWidth")	FX7Segment::getCellWidth() const;
%rename("cellHeight=")	FX7Segment::setCellHeight(FXint);
%rename("cellHeight")	FX7Segment::getCellHeight() const;
%rename("thickness=")	FX7Segment::setThickness(FXint);
%rename("thickness")	FX7Segment::getThickness() const;
%rename("justify=")	FX7Segment::setJustify(FXuint);
%rename("justify")	FX7Segment::getJustify() const;
%rename("helpText=")	FX7Segment::setHelpText(const FXString&);
%rename("helpText")	FX7Segment::getHelpText() const;
%rename("tipText=")	FX7Segment::setTipText(const FXString&);
%rename("tipText")	FX7Segment::getTipText() const;

/**
* Seven-segment (eg LCD/watch style) widget, useful for making
* indicators and timers.  Besides numbers, the seven-segment
* display widget can also display some letters and punctuations.
*/
class FX7Segment : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetIntValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetRealValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetIntValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetRealValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetStringValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetHelp(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetHelp(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetTip(FXObject*,FXSelector,void*); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void*); // FIXME
  long onQueryTip(FXObject*,FXSelector,void*); // FIXME
public:

  %extend {
    /// Create a seven segment display
    FX7Segment(FXComposite* p,const FXString& text,FXuint opts=SEVENSEGMENT_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRb7Segment(p,text,opts,x,y,w,h,pl,pr,pt,pb);
      }
  }

  /// Set the text for this label
  void setText(const FXString& text);

  /// Get the text for this label
  FXString getText() const;

  /// Change text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const;

  /// Get/set cell width
  void setCellWidth(FXint w);
  FXint getCellWidth() const;

  /// Get/set cell height
  void setCellHeight(FXint h);
  FXint getCellHeight() const;

  /// Get/set segment thickness
  void setThickness(FXint t);
  FXint getThickness() const;

  /// Change 7 segment style
  void set7SegmentStyle(FXuint style);

  /// Get current 7 segment style
  FXuint get7SegmentStyle() const;

  /// Set the current text-justification mode.
  void setJustify(FXuint mode);

  /// Get the current text-justification mode.
  FXuint getJustify() const;

  /// Set the status line help text
  void setHelpText(const FXString& text);

  /// Get the status line help text
  const FXString& getHelpText() const;

  /// Set the tool tip message
  void setTipText(const FXString& text);

  /// Get the tool tip message
  const FXString& getTipText() const;

  /// Destroy
  virtual ~FX7Segment();
  };

DECLARE_FXOBJECT_VIRTUALS(FX7Segment)
DECLARE_FXID_VIRTUALS(FX7Segment)
DECLARE_FXDRAWABLE_VIRTUALS(FX7Segment)
DECLARE_FXWINDOW_VIRTUALS(FX7Segment)

