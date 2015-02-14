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

class FXStatusLine : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_NULL);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
public:

  %extend {
    /// Constructor
    FXStatusLine(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0){
      return new FXRbStatusLine(p,tgt,sel);
      }
    }

  /// Change the temporary status message
  void setText(const FXString& text);

  /// Return the temporary status message
  FXString getText() const;

  /// Change the permanent status message
  void setNormalText(const FXString& text);

  /// Return the permanent status message
  FXString getNormalText() const;

  /// Change the font
  void setFont(FXFont* fnt);

  /// Return the current font
  FXFont* getFont() const;

  /// Return the text color
  FXColor getTextColor() const;

  /// Change the text color
  void setTextColor(FXColor clr);

  /// Return the highlight text color
  FXColor getTextHighlightColor() const;

  /// Change the highlight text color
  void setTextHighlightColor(FXColor clr);

  /// Destroy
  virtual ~FXStatusLine();
  };


DECLARE_FXOBJECT_VIRTUALS(FXStatusLine)
DECLARE_FXID_VIRTUALS(FXStatusLine)
DECLARE_FXDRAWABLE_VIRTUALS(FXStatusLine)
DECLARE_FXWINDOW_VIRTUALS(FXStatusLine)

