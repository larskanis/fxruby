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

%rename("hue=")       FXColorRing::setHue(FXfloat);
%rename("hue")        FXColorRing::getHue() const;
%rename("sat=")       FXColorRing::setSat(FXfloat);
%rename("sat")        FXColorRing::getSat() const;
%rename("val=")       FXColorRing::setVal(FXfloat);
%rename("val")        FXColorRing::getVal() const;
%rename("ringWidth=") FXColorRing::setRingWidth(FXint);
%rename("ringWidth")  FXColorRing::getRingWidth() const;
%rename("helpText=")  FXColorRing::setHelpText(const FXString&);
%rename("helpText")   FXColorRing::getHelpText() const;
%rename("tipText=")   FXColorRing::setTipText(const FXString&);
%rename("tipText")    FXColorRing::getTipText() const;

/**
* A Color Ring widget provides an intuitive way to specify a color.
* The outer ring of the widget is rotated to control the hue of the color
* being specified, while the inner triangle varies the color saturation
* and the brightness of the color.  The color saturation axis of the
* triangle goes from a fully saturated "pure" color to "pastel" color;
* the brightness goes from black to a bright color.
*/
class FXColorRing : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_NULL);
  long onQueryTip(FXObject*,FXSelector,void* PTR_NULL);
public:

  %extend {
    /// Construct color ring with initial color clr
    FXColorRing(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbColorRing(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
  }

  /// Change hue
  void setHue(FXfloat h);

  /// Return hue
  FXfloat getHue() const;

  /// Change saturation
  void setSat(FXfloat s);

  /// Return saturation
  FXfloat getSat() const;

  /// Change value
  void setVal(FXfloat v);

  /// Return value
  FXfloat getVal() const;

  /// Set hue, saturation, value
  void setHueSatVal(FXfloat h,FXfloat s,FXfloat v);

  /// Change width of hue ring
  void setRingWidth(FXint rw);

  /// Return width of hue ring
  FXint getRingWidth() const;

  /// Set status line help text for this color well
  void setHelpText(const FXString& text);

  /// Get status line help text for this color well
  const FXString& getHelpText() const;

  /// Set tool tip message for this color well
  void setTipText(const FXString& text);

  /// Get tool tip message for this color well
  const FXString& getTipText() const;

 /// Destructor
  virtual ~FXColorRing();
  };

