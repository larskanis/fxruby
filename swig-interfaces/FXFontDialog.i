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

class FXFontSelector;


/// Font selection dialog
class FXFontDialog : public FXDialogBox {
public:
  %extend {
    /// Constructor
    FXFontDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=600,FXint h=380){
      return new FXRbFontDialog(owner,name,opts,x,y,w,h);
      }
    }

  /// Set the current font selection
  void setFontSelection(const FXFontDesc& fontdesc);

  %extend {
    /// Get the current font selection
    FXFontDesc getFontSelection() const {
      FXFontDesc fontdesc;
      self->getFontSelection(fontdesc);
      return fontdesc;
    }
  }

  /// Destructor
  virtual ~FXFontDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFontDialog)
DECLARE_FXID_VIRTUALS(FXFontDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXFontDialog)
DECLARE_FXWINDOW_VIRTUALS(FXFontDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXFontDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXFontDialog)

