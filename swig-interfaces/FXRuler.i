/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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

/// Ruler options
enum {
  RULER_NORMAL       = 0,                                   /// Default appearance (default)
  RULER_HORIZONTAL   = 0,                                   /// Ruler is horizontal (default)
  RULER_VERTICAL     = 0x00008000,                          /// Ruler is vertical
  RULER_TICKS_OFF    = 0,                                   /// Tick marks off (default)
  RULER_TICKS_TOP    = 0x00010000,                          /// Ticks on the top (if horizontal)
  RULER_TICKS_BOTTOM = 0x00020000,                          /// Ticks on the bottom (if horizontal)
  RULER_TICKS_LEFT   = RULER_TICKS_TOP,                     /// Ticks on the left (if vertical)
  RULER_TICKS_RIGHT  = RULER_TICKS_BOTTOM,                  /// Ticks on the right (if vertical)
  RULER_TICKS_CENTER = RULER_TICKS_TOP|RULER_TICKS_BOTTOM,  /// Tickmarks centered
  RULER_NUMBERS      = 0x00040000,                          /// Show numbers
  RULER_ARROW        = 0x00080000,                          /// Draw small arrow for cursor position
  RULER_MARKERS      = 0x00100000,                          /// Draw markers for indentation settings
  RULER_METRIC       = 0,                                   /// Metric subdivision (default)
  RULER_ENGLISH       = 0x00200000,                             /// English subdivision
  RULER_MARGIN_ADJUST = 0x00400000,                             /// Allow margin adjustment
  RULER_ALIGN_CENTER  = 0,                                      /// Center document horizontally
  RULER_ALIGN_LEFT    = 0x00800000,                             /// Align document to the left
  RULER_ALIGN_RIGHT   = 0x01000000,                             /// Align document to the right
  RULER_ALIGN_TOP     = RULER_ALIGN_LEFT,                       /// Align document to the top
  RULER_ALIGN_BOTTOM  = RULER_ALIGN_RIGHT,                      /// Align document to the bottom
  RULER_ALIGN_STRETCH = RULER_ALIGN_LEFT|RULER_ALIGN_RIGHT,     /// Stretch document to fit horizontally
  RULER_ALIGN_NORMAL  = RULER_ALIGN_CENTER                      /// Normally, document is centered both ways
  };


class FXFont;

%rename("documentUpper") FXRuler::getDocumentUpper() const;
%rename("documentLower") FXRuler::getDocumentLower() const;

/**
* The Ruler widget is placed alongside a document to measure position
* and size of entities within the document.
*/
class FXRuler : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetIntValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetIntValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_ARROW=FXFrame::ID_LAST,
    ID_LAST
    };
public:
  %extend {
    /// Construct label with given text and icon
    FXRuler(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=RULER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbRuler(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set the current position
  void setPosition(FXint pos,FXbool notify=FALSE);

  /// Return the current position
  FXint getPosition() const;

  /// Change/return content size
  void setContentSize(FXint size,FXbool notify=FALSE);
  FXint getContentSize() const;

  /// Get lower edge of document
  FXint getDocumentLower() const;

  /// Get upper edge of document
  FXint getDocumentUpper() const;

  /// Change/return document size
  void setDocumentSize(FXint size,FXbool notify=FALSE);
  FXint getDocumentSize() const;

  /// Change/return document edge spacing
  void setEdgeSpacing(FXint space,FXbool notify=FALSE);
  FXint getEdgeSpacing() const;

  /// Change/return lower document margin
  void setMarginLower(FXint mgn,FXbool notify=FALSE);
  FXint getMarginLower() const;

  /// Change/return upper document margin
  void setMarginUpper(FXint mgn,FXbool notify=FALSE);
  FXint getMarginUpper() const;

  /// Change/return first line indent
  void setIndentFirst(FXint ind,FXbool notify=FALSE);
  FXint getIndentFirst() const;

  /// Change/return lower indent
  void setIndentLower(FXint ind,FXbool notify=FALSE);
  FXint getIndentLower() const;

  /// Change/return upper indent
  void setIndentUpper(FXint ind,FXbool notify=FALSE);
  FXint getIndentUpper() const;

  /// Change/return document number placement
  void setNumberTicks(FXint ticks,FXbool notify=FALSE);
  FXint getNumberTicks() const;

  /// Change/return document major ticks
  void setMajorTicks(FXint ticks,FXbool notify=FALSE);
  FXint getMajorTicks() const;

  /// Change/return document medium ticks
  void setMediumTicks(FXint ticks,FXbool notify=FALSE);
  FXint getMediumTicks() const;

  /// Change/return document tiny ticks
  void setTinyTicks(FXint ticks,FXbool notify=FALSE);
  FXint getTinyTicks() const;

  /// Change/return pixel per tick spacing
  void setPixelPerTick(FXdouble space,FXbool notify=FALSE);
  FXdouble getPixelPerTick() const;

  /// Set the text font
  void setFont(FXFont *fnt,FXbool notify=FALSE);

  /// Get the text font
  FXFont* getFont() const;

  /// Change slider value
  void setValue(FXint value);

  /// Return slider value
  FXint getValue() const;

  /// Set ruler style
  void setRulerStyle(FXuint style);

  /// Get ruler style
  FXuint getRulerStyle() const;

  /// Set ruler alignment
  void setRulerAlignment(FXuint alignment,FXbool notify=FALSE);

  /// Get ruler alignment
  FXuint getRulerAlignment() const;

  /// Get the current text color
  FXColor getTextColor() const;

  /// Set the current text color
  void setTextColor(FXColor clr);

  /// Set the status line help text for this label
  void setHelpText(const FXString& text);

  /// Get the status line help text for this label
  const FXString& getHelpText() const;

  /// Set the tool tip message for this label
  void setTipText(const FXString& text);

  /// Get the tool tip message for this label
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXRuler();
  };

DECLARE_FXOBJECT_VIRTUALS(FXRuler)
DECLARE_FXID_VIRTUALS(FXRuler)
DECLARE_FXDRAWABLE_VIRTUALS(FXRuler)
DECLARE_FXWINDOW_VIRTUALS(FXRuler)
