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

class FXColorSelector;


/**
* The Color dialog is a standard dialog panel used to edit colors.
* Colors can be edited via RGB (Red, Green, Blue additive color model),
* via HSV (Hue, Saturation, Value color modal), via CMY (Cyan, Magenta,
* Yellow substractive color model), or by name.
* Commonly used colors can be dragged into a number of small color wells
* to be used repeatedly; colors dropped into the small color wells are
* automatically saved into the registry for future use.
*/
class FXColorDialog : public FXDialogBox {
public:
  long onChgColor(FXObject*,FXSelector,void* PTR_COLOR);
  long onCmdColor(FXObject*,FXSelector,void* PTR_COLOR);
public:
  enum {
    ID_COLORSELECTOR=FXDialogBox::ID_LAST,
    ID_LAST
    };
public:
  %extend {
    /// Construct color dialog
    FXColorDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbColorDialog(owner,name,opts,x,y,w,h);
      }
    }

  /// Set the color
  void setRGBA(FXColor clr);

  /// Get the color
  FXColor getRGBA() const;

  /// Return true if only opaque colors allowed
  FXbool isOpaqueOnly() const;

  /// Change opaque only mode
  void setOpaqueOnly(FXbool forceopaque);

  /// Destructor
  virtual ~FXColorDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXColorDialog)
DECLARE_FXID_VIRTUALS(FXColorDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXColorDialog)
DECLARE_FXWINDOW_VIRTUALS(FXColorDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXColorDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXColorDialog)

