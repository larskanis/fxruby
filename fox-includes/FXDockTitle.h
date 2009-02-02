/********************************************************************************
*                                                                               *
*                         D o c k T i t l e   W i d g e t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXDockTitle.h 2129 2005-08-07 20:24:37Z lyle $                        *
********************************************************************************/
#ifndef FXDOCKTITLE_H
#define FXDOCKTITLE_H

#ifndef FXDOCKHANDLER_H
#include "FXDockHandler.h"
#endif

namespace FX {


/**
* A dock title is used to move its container, a dock bar.
* The dock title is also used simultaneously to provide a
* caption above the dock bar.
*/
class FXAPI FXDockTitle : public FXDockHandler {
  FXDECLARE(FXDockTitle)
protected:
  FXString  caption;            // Caption text
  FXFont   *font;               // Caption font
  FXColor   captionColor;       // Caption color
protected:
  FXDockTitle();
private:
  FXDockTitle(const FXDockTitle&);
  FXDockTitle& operator=(const FXDockTitle&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
public:

  /// Construct dock bar title widget
  FXDockTitle(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL|JUSTIFY_CENTER_X|JUSTIFY_CENTER_Y,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Set the caption for the grip
  void setCaption(const FXString& text);

  /// Get the caption for the grip
  FXString getCaption() const { return caption; }

  /// Set caption font
  void setFont(FXFont *fnt);

  /// Get caption font
  FXFont* getFont() const { return font; }

  /// Get the current caption color
  FXColor getCaptionColor() const { return captionColor; }

  /// Set the current caption color
  void setCaptionColor(FXColor clr);

  /// Set the current justification mode.
  void setJustify(FXuint mode);

  /// Get the current justification mode.
  FXuint getJustify() const;

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXDockTitle();
  };

}

#endif
