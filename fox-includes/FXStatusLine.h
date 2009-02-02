/********************************************************************************
*                                                                               *
*                       S t a t u s L i n e   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXStatusLine.h 2239 2005-11-09 13:42:43Z lyle $                       *
********************************************************************************/
#ifndef FXSTATUSLINE_H
#define FXSTATUSLINE_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/**
* The status line normally shows its permanent message; when
* moving the mouse over a Widget which has status-line help, the status line
* temporarily replaces its normal message with the help information; the status
* line obtains the help message by sending the Widget a ID_QUERY_HELP message
* with type SEL_UPDATE.
* If this query does not result in a new status string, the target of
* the status line is tried via an ordinary SEL_UPDATE message.
* If none of the above work then the status line will display the normal text,
* i.e. the string set via setNormalText().
* If the message contains a newline (\n), then the part before the newline
* will be displayed in the highlight color, while the part after the newline
* is shown using the normal text color.
*/
class FXAPI FXStatusLine : public FXFrame {
  FXDECLARE(FXStatusLine)
protected:
  FXString  status;             // Current status message
  FXString  normal;             // Normally displayed message
  FXFont   *font;               // Font
  FXColor   textColor;          // Status text color
  FXColor   textHighlightColor; // Status text highlight color
protected:
  FXStatusLine();
private:
  FXStatusLine(const FXStatusLine&);
  FXStatusLine& operator=(const FXStatusLine&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onUpdate(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
public:

  /// Constructor
  FXStatusLine(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Change the temporary status message
  void setText(const FXString& text);

  /// Return the temporary status message
  FXString getText() const { return status; }

  /// Change the permanent status message
  void setNormalText(const FXString& text);

  /// Return the permanent status message
  FXString getNormalText() const { return normal; }

  /// Change the font
  void setFont(FXFont* fnt);

  /// Return the current font
  FXFont* getFont() const { return font; }

  /// Return the text color
  FXColor getTextColor() const { return textColor; }

  /// Change the text color
  void setTextColor(FXColor clr);

  /// Return the highlight text color
  FXColor getTextHighlightColor() const { return textHighlightColor; }

  /// Change the highlight text color
  void setTextHighlightColor(FXColor clr);

  /// Save status line to stream
  virtual void save(FXStream& store) const;

  /// Load status line from stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXStatusLine();
  };

}

#endif
