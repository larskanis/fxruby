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

/// Progress bar styles
enum {
  PROGRESSBAR_HORIZONTAL = 0,             /// Horizontal display
  PROGRESSBAR_VERTICAL   = 0x00008000,    /// Vertical display
  PROGRESSBAR_PERCENTAGE = 0x00010000,    /// Show percentage done
  PROGRESSBAR_DIAL       = 0x00020000,    /// Show as a dial instead of bar
  PROGRESSBAR_NORMAL     = FRAME_SUNKEN|FRAME_THICK
  };


/// Progress bar widget
class FXProgressBar : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_UINT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:

  /// Construct progress bar
  %extend {
    FXProgressBar(FXComposite* p,FXObject* target=NULL,FXSelector sel=0,FXuint opts=PROGRESSBAR_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbProgressBar(p,target,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change the amount of progress
  void setProgress(FXuint value);

  /// Get current progress
  FXuint getProgress() const;

  /// Set total amount of progress
  void setTotal(FXuint value);

  /// Return total amount of progrss
  FXuint getTotal() const;

  /// Increment progress by given amount
  void increment(FXuint value);

  /// Hide progress percentage
  void hideNumber();

  /// Show progress percentage
  void showNumber();

  /// Change progress bar width
  void setBarSize(FXint size);

  /// Return progress bar width
  FXint getBarSize() const;

  /// Change backgroundcolor
  void setBarBGColor(FXColor clr);

  /// Return background color
  FXColor getBarBGColor() const;

  /// Change bar color
  void setBarColor(FXColor clr);

  /// Return bar color
  FXColor getBarColor() const;

  /// Change text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const;

  /// Change alternate text color shown when bar under text
  void setTextAltColor(FXColor clr);

  /// Return alternate text color
  FXColor getTextAltColor() const;

  /// Set the text font
  void setFont(FXFont *fnt);

  /// Get the text font
  FXFont* getFont() const;

  /// Change progress bar style
  void setBarStyle(FXuint style);

  /// Return current progress bar style
  FXuint getBarStyle() const;

  /// Destructor
  virtual ~FXProgressBar();
  };


DECLARE_FXOBJECT_VIRTUALS(FXProgressBar)
DECLARE_FXID_VIRTUALS(FXProgressBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXProgressBar)
DECLARE_FXWINDOW_VIRTUALS(FXProgressBar)

