/********************************************************************************
*                                                                               *
*                        F o n t   S e l e c t i o n   B o x                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXFontSelector.h 809 2002-07-11 17:28:15Z lyle $                    *
********************************************************************************/
#ifndef FXFONTSELECTOR_H
#define FXFONTSELECTOR_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


class FXTextField;
class FXList;
class FXComboBox;
class FXLabel;
class FXButton;
class FXCheckButton;
class FXFont;


/// Font selection widget
class FXAPI FXFontSelector : public FXPacker {
  FXDECLARE(FXFontSelector)
protected:
  FXTextField   *family;
  FXList        *familylist;
  FXTextField   *weight;
  FXList        *weightlist;
  FXTextField   *style;
  FXList        *stylelist;
  FXTextField   *size;
  FXList        *sizelist;
  FXComboBox    *charset;
  FXComboBox    *setwidth;
  FXComboBox    *pitch;
  FXCheckButton *scalable;
  FXCheckButton *allfonts;
  FXButton      *accept;
  FXButton      *cancel;
  FXLabel       *preview;
  FXFont        *previewfont;
  FXFontDesc     selected;
protected:
  FXFontSelector(){}
  void listFontFaces();
  void listWeights();
  void listSlants();
  void listFontSizes();
  void previewFont();
private:
  FXFontSelector(const FXFontSelector&);
  FXFontSelector &operator=(const FXFontSelector&);
public:
  long onCmdFamily(FXObject*,FXSelector,void*);
  long onCmdWeight(FXObject*,FXSelector,void*);
  long onCmdStyle(FXObject*,FXSelector,void*);
  long onCmdStyleText(FXObject*,FXSelector,void*);
  long onCmdSize(FXObject*,FXSelector,void*);
  long onCmdSizeText(FXObject*,FXSelector,void*);
  long onCmdCharset(FXObject*,FXSelector,void*);
  long onUpdCharset(FXObject*,FXSelector,void*);
  long onCmdSetWidth(FXObject*,FXSelector,void*);
  long onUpdSetWidth(FXObject*,FXSelector,void*);
  long onCmdPitch(FXObject*,FXSelector,void*);
  long onUpdPitch(FXObject*,FXSelector,void*);
  long onCmdScalable(FXObject*,FXSelector,void*);
  long onUpdScalable(FXObject*,FXSelector,void*);
  long onCmdAllFonts(FXObject*,FXSelector,void*);
  long onUpdAllFonts(FXObject*,FXSelector,void*);
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

  /// Constructor
  FXFontSelector(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create server-side resources
  virtual void create();

  /// Return a pointer to the "Accept" button
  FXButton *acceptButton() const { return accept; }

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const { return cancel; }

  /// Set font selection
  void setFontSelection(const FXFontDesc& fontdesc);

  /// Get font selection
  void getFontSelection(FXFontDesc& fontdesc) const;

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXFontSelector();
  };

}

#endif
