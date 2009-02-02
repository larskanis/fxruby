/********************************************************************************
*                                                                               *
*                G r o u p  B o x   W i n d o w   W i d g e t                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGroupBox.h 2232 2005-11-09 03:18:19Z lyle $                        *
********************************************************************************/
#ifndef FXGROUPBOX_H
#define FXGROUPBOX_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


// Group box options
enum {
  GROUPBOX_TITLE_LEFT   = 0,	        /// Title is left-justified
  GROUPBOX_TITLE_CENTER = 0x00020000,	/// Title is centered
  GROUPBOX_TITLE_RIGHT  = 0x00040000,	/// Title is right-justified
  GROUPBOX_NORMAL       = GROUPBOX_TITLE_LEFT
  };



/**
* A group box widget provides a nice raised or sunken border
* around a group of widgets, providing a visual delineation.
* Typically, a title is placed over the border to provide some
* clarification.
*/
class FXAPI FXGroupBox : public FXPacker {
  FXDECLARE(FXGroupBox)
protected:
  FXString  label;
  FXFont   *font;
  FXColor   textColor;
protected:
  FXGroupBox();
private:
  FXGroupBox(const FXGroupBox&);
  FXGroupBox &operator=(const FXGroupBox&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
public:

  /// Construct group box layout manager
  FXGroupBox(FXComposite* p,const FXString& text,FXuint opts=GROUPBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Perform layout
  virtual void layout();

  /// Enable the window
  virtual void enable();

  /// Disable the window
  virtual void disable();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Change group box title text
  void setText(const FXString& text);

  /// Return current groupbox title text
  FXString getText() const { return label; }

  /// Change group box style
  void setGroupBoxStyle(FXuint style);

  /// Return current group box style
  FXuint getGroupBoxStyle() const;

  /// Change title font
  void setFont(FXFont* fnt);

  /// Return title font
  FXFont* getFont() const { return font; }

  /// Change title text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const { return textColor; }

  /// Save to a stream
  virtual void save(FXStream& store) const;

  /// Load from a stream
  virtual void load(FXStream& store);
  };

}

#endif
