/********************************************************************************
*                                                                               *
*                           C o l o r   D i a l o g                             *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXColorDialog.h 2127 2005-08-07 20:21:35Z lyle $                     *
********************************************************************************/
#ifndef FXCOLORDIALOG_H
#define FXCOLORDIALOG_H

#ifndef FXDIALOGBOX_H
#include "FXDialogBox.h"
#endif

namespace FX {


class FXColorSelector;


/**
* The Color dialog is a standard dialog panel used to edit colors.
* Colors can be edited via RGB (Red, Green, Blue additive color model),
* via HSV (Hue, Saturation, Value color modal), via CMY (Cyan, Magenta,
* Yellow subtractive color model), or by name.
* Commonly used colors can be dragged into a number of small color wells
* to be used repeatedly; colors dropped into the small color wells are
* automatically saved into the registry for future use.
*/
class FXAPI FXColorDialog : public FXDialogBox {
  FXDECLARE(FXColorDialog)
protected:
  FXColorSelector *colorbox;
protected:
  FXColorDialog(){}
private:
  FXColorDialog(const FXColorDialog&);
  FXColorDialog &operator=(const FXColorDialog&);
public:
  long onChgColor(FXObject*,FXSelector,void*);
  long onCmdColor(FXObject*,FXSelector,void*);
public:
  enum {
    ID_COLORSELECTOR=FXDialogBox::ID_LAST,
    ID_LAST
    };
public:

  /// Construct color dialog
  FXColorDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Set the color
  void setRGBA(FXColor clr);

  /// Get the color
  FXColor getRGBA() const;

  /// Return true if only opaque colors allowed
  FXbool isOpaqueOnly() const;

  /// Change opaque only mode
  void setOpaqueOnly(FXbool forceopaque);

  /// Save dialog to a stream
  virtual void save(FXStream& store) const;

  /// Load dialog from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXColorDialog();
  };

}

#endif
