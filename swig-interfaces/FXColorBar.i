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

/// Color bar orientation
enum {
  COLORBAR_HORIZONTAL = 0,            /// Color bar shown horizontally
  COLORBAR_VERTICAL   = 0x00008000    /// Color bar shown vertically
  };


class FXImage;


/**
* A color bar is a widget which controls the brightness (value) of a
* color by means of the hue, saturation, value specification system.
*/
class FXColorBar : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  %extend {
    /// Construct color well with initial color clr
    FXColorBar(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbColorBar(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
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

  /// Change the color bar style
  FXuint getBarStyle() const;

  /// Get the color bar style
  void setBarStyle(FXuint style);

  /// Set status line help text for this color bar
  void setHelpText(const FXString& text);

  /// Get status line help text for this color bar
  const FXString& getHelpText() const;

  /// Set tool tip message for this color bar
  void setTipText(const FXString& text);

  /// Get tool tip message for this color bar
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXColorBar();
  };


DECLARE_FXOBJECT_VIRTUALS(FXColorBar)
DECLARE_FXID_VIRTUALS(FXColorBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXColorBar)
DECLARE_FXWINDOW_VIRTUALS(FXColorBar)

