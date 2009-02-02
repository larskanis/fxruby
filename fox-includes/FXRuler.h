/********************************************************************************
*                                                                               *
*                            R u l e r   W i d g e t                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXRuler.h 2344 2006-02-12 21:19:36Z lyle $                           *
********************************************************************************/
#ifndef FXRULER_H
#define FXRULER_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/// Ruler options
enum {
  RULER_NORMAL        = 0,                                      /// Default appearance (default)
  RULER_HORIZONTAL    = 0,                                      /// Ruler is horizontal (default)
  RULER_VERTICAL      = 0x00008000,                             /// Ruler is vertical
  RULER_TICKS_OFF     = 0,                                      /// Tick marks off (default)
  RULER_TICKS_TOP     = 0x00010000,                             /// Ticks on the top (if horizontal)
  RULER_TICKS_BOTTOM  = 0x00020000,                             /// Ticks on the bottom (if horizontal)
  RULER_TICKS_LEFT    = RULER_TICKS_TOP,                        /// Ticks on the left (if vertical)
  RULER_TICKS_RIGHT   = RULER_TICKS_BOTTOM,                     /// Ticks on the right (if vertical)
  RULER_TICKS_CENTER  = RULER_TICKS_TOP|RULER_TICKS_BOTTOM,     /// Tickmarks centered
  RULER_NUMBERS       = 0x00040000,                             /// Show numbers
  RULER_ARROW         = 0x00080000,                             /// Draw small arrow for cursor position
  RULER_MARKERS       =  0x00100000,                            /// Draw markers for indentation settings
  RULER_METRIC        = 0,                                      /// Metric subdivision (default)
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


/**
* The ruler widget is placed alongside a document to measure position
* and size of entities within the document, such as margins, paragraph
* indents, and tickmarks.
* The ruler widget sends a SEL_CHANGED when the indentation or margins
* are interactively changed by the user.
* If the document size exceeds the available space, it is possible to
* scroll the document using setPosition().  When the document size is
* less than the available space, the alignment options can be used to
* center, left-adjust, or right-adjust the document.
* Finally, a special option exists to stretch the document to the
* available space, that is to say, the document will always be fitten
* with given left and right edges substracted from the available space.
*/
class FXAPI FXRuler : public FXFrame {
  FXDECLARE(FXRuler)
protected:
  FXFont  *font;                // Font for numbers
  FXint    documentSize;        // Size of document
  FXint    edgeSpacing;         // Edge spacing around document
  FXint    marginLower;         // Lower margin
  FXint    marginUpper;         // Upper margin
  FXint    indentFirst;         // First line paragraph indent
  FXint    indentLower;         // Lower paragraph indent
  FXint    indentUpper;         // Upper paragraph indent
  FXdouble pixelPerTick;        // Number of pixels per tick increment
  FXint    numberTicks;         // Tick increments between numbers
  FXint    majorTicks;          // Tick increments between major ticks
  FXint    mediumTicks;         // Tick increments between medium ticks
  FXint    tinyTicks;           // Tick increments between tiny ticks
  FXint    arrowPos;            // Arrow position
  FXColor  textColor;           // Color for numbers and ticks
  FXint    shift;               // Left edge of content
  FXint    pos;                 // Scroll position
  FXint    off;                 // Offset item was grabbed
  FXString tip;                 // Tooltip text
  FXString help;                // Help text
  FXuchar  mode;                // Mode widget is in
protected:
  FXRuler();
  FXint picked(FXint x,FXint y);
  void drawLeftArrow(FXDCWindow& dc,FXint x,FXint y);
  void drawRightArrow(FXDCWindow& dc,FXint x,FXint y);
  void drawUpArrow(FXDCWindow& dc,FXint x,FXint y);
  void drawDownArrow(FXDCWindow& dc,FXint x,FXint y);
  void drawLeftMarker(FXDCWindow& dc,FXint x,FXint y);
  void drawRightMarker(FXDCWindow& dc,FXint x,FXint y);
  void drawUpMarker(FXDCWindow& dc,FXint x,FXint y);
  void drawDownMarker(FXDCWindow& dc,FXint x,FXint y);
protected:
  enum{
    MOUSE_NONE,         // No mouse operation
    MOUSE_MARG_LOWER,   // Drag lower margin
    MOUSE_MARG_UPPER,   // Drag upper margin
    MOUSE_PARA_FIRST,   // Drag first indent
    MOUSE_PARA_LOWER,   // Drag lower indent
    MOUSE_PARA_UPPER    // Drag upper indent
    };
private:
  FXRuler(const FXRuler&);
  FXRuler &operator=(const FXRuler&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:
  enum{
    ID_ARROW=FXFrame::ID_LAST,
    ID_LAST
    };
public:

  /// Construct label with given text and icon
  FXRuler(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=RULER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Perform layout
  virtual void layout();

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Set the current position
  void setPosition(FXint pos,FXbool notify=FALSE);

  /// Return the current position
  FXint getPosition() const { return pos; }

  /// Change/return content size
  void setContentSize(FXint size,FXbool notify=FALSE);
  FXint getContentSize() const;

  /// Get lower edge of document
  FXint getDocumentLower() const;

  /// Get upper edge of document
  FXint getDocumentUpper() const;

  /// Change/return document size
  void setDocumentSize(FXint size,FXbool notify=FALSE);
  FXint getDocumentSize() const { return documentSize; }

  /// Change/return document edge spacing
  void setEdgeSpacing(FXint space,FXbool notify=FALSE);
  FXint getEdgeSpacing() const { return edgeSpacing; }

  /// Change/return lower document margin
  void setMarginLower(FXint mgn,FXbool notify=FALSE);
  FXint getMarginLower() const { return marginLower; }

  /// Change/return upper document margin
  void setMarginUpper(FXint mgn,FXbool notify=FALSE);
  FXint getMarginUpper() const { return marginUpper; }

  /// Change/return first line indent
  void setIndentFirst(FXint ind,FXbool notify=FALSE);
  FXint getIndentFirst() const { return indentFirst; }

  /// Change/return lower indent
  void setIndentLower(FXint ind,FXbool notify=FALSE);
  FXint getIndentLower() const { return indentLower; }

  /// Change/return upper indent
  void setIndentUpper(FXint ind,FXbool notify=FALSE);
  FXint getIndentUpper() const { return indentUpper; }

  /// Change/return document number placement
  void setNumberTicks(FXint ticks,FXbool notify=FALSE);
  FXint getNumberTicks() const { return numberTicks; }

  /// Change/return document major ticks
  void setMajorTicks(FXint ticks,FXbool notify=FALSE);
  FXint getMajorTicks() const { return majorTicks; }

  /// Change/return document medium ticks
  void setMediumTicks(FXint ticks,FXbool notify=FALSE);
  FXint getMediumTicks() const { return mediumTicks; }

  /// Change/return document tiny ticks
  void setTinyTicks(FXint ticks,FXbool notify=FALSE);
  FXint getTinyTicks() const { return tinyTicks; }

  /// Change/return pixel per tick spacing
  void setPixelPerTick(FXdouble space,FXbool notify=FALSE);
  FXdouble getPixelPerTick() const { return pixelPerTick; }

  /// Set the text font
  void setFont(FXFont *fnt,FXbool notify=FALSE);

  /// Get the text font
  FXFont* getFont() const { return font; }

  /// Change arrow value, relative to document position
  void setValue(FXint value);

  /// Return arrow value in document
  FXint getValue() const { return arrowPos; }

  /// Set ruler style
  void setRulerStyle(FXuint style);

  /// Get ruler style
  FXuint getRulerStyle() const;

  /// Set ruler alignment
  void setRulerAlignment(FXuint alignment,FXbool notify=FALSE);

  /// Get ruler alignment
  FXuint getRulerAlignment() const;

  /// Get the current text color
  FXColor getTextColor() const { return textColor; }

  /// Set the current text color
  void setTextColor(FXColor clr);

  /// Set the status line help text for the ruler
  void setHelpText(const FXString& text){ help=text; }

  /// Get the status line help text for the ruler
  const FXString& getHelpText() const { return help; }

  /// Set the tool tip message for the ruler
  void setTipText(const FXString& text){ tip=text; }

  /// Get the tool tip message for the ruler
  const FXString& getTipText() const { return tip; }

  /// Save label to a stream
  virtual void save(FXStream& store) const;

  /// Load label from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXRuler();
  };

}

#endif
