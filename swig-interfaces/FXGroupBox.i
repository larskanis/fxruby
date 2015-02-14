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

// Group box options
enum {
  GROUPBOX_TITLE_LEFT   = 0,            /// Title is left-justified
  GROUPBOX_TITLE_CENTER = 0x00040000,	/// Title is centered
  GROUPBOX_TITLE_RIGHT  = 0x00080000,	/// Title is right-justified
  GROUPBOX_NORMAL       = GROUPBOX_TITLE_LEFT
  };


/**
* A group box widget provides a nice raised or sunken border
* around a group of widgets, providing a visual delineation.
* Typically, a title is placed over the border to provide some
* clarification.
* Radio buttons placed inside a group box automatically assume
* mutually exclusive behaviour, i.e. at most one radio button will
* be checked at any one time.
*/
class FXGroupBox : public FXPacker {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:
  %extend {
    /// Construct group box layout manager
    FXGroupBox(FXComposite* p,const FXString& text,FXuint opts=GROUPBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbGroupBox(p,text,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Change group box title text
  void setText(const FXString& text);

  /// Return current groupbox title text
  FXString getText() const;

  /// Change group box style
  void setGroupBoxStyle(FXuint style);

  /// Return current group box style
  FXuint getGroupBoxStyle() const;

  /// Change title font
  void setFont(FXFont* fnt);

  /// Return title font
  FXFont* getFont() const;

  /// Change title text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const;

  /// Destructor
  virtual ~FXGroupBox();
  };


DECLARE_FXOBJECT_VIRTUALS(FXGroupBox)
DECLARE_FXID_VIRTUALS(FXGroupBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXGroupBox)
DECLARE_FXWINDOW_VIRTUALS(FXGroupBox)

