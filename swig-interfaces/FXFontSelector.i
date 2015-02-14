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

class FXTextField;
class FXList;
class FXComboBox;
class FXLabel;
class FXButton;
class FXCheckButton;
class FXFont;


/// Font selection widget
class FXFontSelector : public FXPacker {
public:
  long onCmdFamily(FXObject*,FXSelector,void* PTR_INT);
  long onCmdWeight(FXObject*,FXSelector,void* PTR_INT);
  long onCmdStyle(FXObject*,FXSelector,void* PTR_INT);
  long onCmdStyleText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSize(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSizeText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCharset(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCharset(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetWidth(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSetWidth(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPitch(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdPitch(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdScalable(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdScalable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdAllFonts(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdAllFonts(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_FAMILY=FXPacker::ID_LAST,
    ID_WEIGHT,
    ID_STYLE,
    ID_STYLE_TEXT,
    ID_SIZE,
    ID_SIZE_TEXT,
    ID_CHARSET,
    ID_SETWIDTH,
    ID_PITCH,
    ID_SCALABLE,
    ID_ALLFONTS,
    ID_LAST
    };
public:
  %extend {
    /// Constructor
    FXFontSelector(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbFontSelector(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return a pointer to the "Accept" button
  FXButton *acceptButton() const;

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const;

  /// Set font selection
  void setFontSelection(const FXFontDesc& fontdesc);

  %extend {
    /// Get font selection
    FXFontDesc getFontSelection() const {
      FXFontDesc fontdesc;
      self->getFontSelection(fontdesc);
      return fontdesc;
    }
  }

  /// Destructor
  virtual ~FXFontSelector();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFontSelector)
DECLARE_FXID_VIRTUALS(FXFontSelector)
DECLARE_FXDRAWABLE_VIRTUALS(FXFontSelector)
DECLARE_FXWINDOW_VIRTUALS(FXFontSelector)

