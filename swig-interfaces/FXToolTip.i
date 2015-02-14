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

/// ToolTip styles
enum {
  TOOLTIP_PERMANENT  = 0x00020000,      /// ToolTip stays up indefinitely
  TOOLTIP_VARIABLE   = 0x00040000,      /// ToolTip stays up variable time, depending on the length of the string
  TOOLTIP_NORMAL     = 0
  };


class FXFont;

/// Hopefully Helpful Hint message
class FXToolTip : public FXShell {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_NULL);
  long onTipShow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onTipHide(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
public:
  enum {
    ID_TIP_SHOW=FXShell::ID_LAST,
    ID_TIP_HIDE,
    ID_LAST
    };
public:
  %extend {
    /// Construct a tool tip
    FXToolTip(FXApp* a,FXuint opts=TOOLTIP_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbToolTip(a,opts,x,y,w,h);
      }
    }

  /// Set the text for this tip
  void setText(const FXString& text);

  /// Get the text for this tip
  FXString getText() const;

  /// Set the tip text font
  void setFont(FXFont *fnt);

  /// Get the tip text font
  FXFont* getFont() const;

  /// Get the current tip text color
  FXColor getTextColor() const;

  /// Set the current tip text color
  void setTextColor(FXColor clr);

  /// Destructor
  virtual ~FXToolTip();
  };


DECLARE_FXOBJECT_VIRTUALS(FXToolTip)
DECLARE_FXID_VIRTUALS(FXToolTip)
DECLARE_FXDRAWABLE_VIRTUALS(FXToolTip)
DECLARE_FXWINDOW_VIRTUALS(FXToolTip)

