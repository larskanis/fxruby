/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

%rename("caption=")      FXDockTitle::setCaption(const FXString&);
%rename("caption")       FXDockTitle::getCaption() const;
%rename("font=")         FXDockTitle::setFont(FXFont*);
%rename("font")          FXDockTitle::getFont() const;
%rename("captionColor=") FXDockTitle::setCaptionColor(FXColor);
%rename("captionColor")  FXDockTitle::getCaptionColor() const;
%rename("justify=")      FXDockTitle::setJustify(FXuint);
%rename("justify")       FXDockTitle::getJustify() const;

/**
* A dock title is used to move its container, a dock bar.
* The dock title is also used simultaneously to provide a
* caption above the dock bar.
*/
class FXDockTitle : public FXDockHandler {
protected:
  FXString  caption;            // Caption text
  FXFont   *font;               // Caption font
  FXColor   captionColor;       // Caption color
protected:
  FXDockTitle();
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdSetStringValue(FXObject*,FXSelector,void*); // FIXME
  long onCmdGetStringValue(FXObject*,FXSelector,void*); // FIXME
public:

  %extend {
    /// Construct dock bar title widget
    FXDockTitle(FXComposite* p,const FXString& text,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL|JUSTIFY_CENTER_X|JUSTIFY_CENTER_Y,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0){
      return new FXRbDockTitle(p,text,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
  }
  
  /// Set the caption for the grip
  void setCaption(const FXString& text);

  /// Get the caption for the grip
  FXString getCaption() const;

  /// Set caption font
  void setFont(FXFont *fnt);

  /// Get caption font
  FXFont* getFont() const;

  /// Get the current caption color
  FXColor getCaptionColor() const;

  /// Set the current caption color
  void setCaptionColor(FXColor clr);

  /// Set the current justification mode.
  void setJustify(FXuint mode);

  /// Get the current justification mode.
  FXuint getJustify() const;

  /// Destroy
  virtual ~FXDockTitle();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDockTitle)
DECLARE_FXID_VIRTUALS(FXDockTitle)
DECLARE_FXDRAWABLE_VIRTUALS(FXDockTitle)
DECLARE_FXWINDOW_VIRTUALS(FXDockTitle)

