/********************************************************************************
*                                                                               *
*                      P r o g r e s s B a r   W i d g e t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXProgressBar.h 814 2002-07-12 16:34:49Z lyle $                     *
********************************************************************************/
#ifndef FXPROGRESSBAR_H
#define FXPROGRESSBAR_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif

namespace FX {


/// Progress bar styles
enum {
  PROGRESSBAR_HORIZONTAL = 0,             /// Horizontal display
  PROGRESSBAR_VERTICAL   = 0x00008000,    /// Vertical display
  PROGRESSBAR_PERCENTAGE = 0x00010000,    /// Show percentage done
  PROGRESSBAR_DIAL       = 0x00020000,    /// Show as a dial instead of bar
  PROGRESSBAR_NORMAL     = FRAME_SUNKEN|FRAME_THICK
  };


/// Progress bar widget
class FXAPI FXProgressBar : public FXFrame {
  FXDECLARE(FXProgressBar)
protected:
  FXuint   progress;                      // Integer percentage number
  FXuint   total;                         // Amount for completion
  FXint    barsize;                       // Bar size
  FXFont*  font;
  FXColor  barBGColor;
  FXColor  barColor;
  FXColor  textNumColor;
  FXColor  textAltColor;
protected:
  FXProgressBar(){}
  void drawInterior(FXDCWindow& dc);
private:
  FXProgressBar(const FXProgressBar&);
  FXProgressBar &operator=(const FXProgressBar&);
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetIntValue(FXObject*,FXSelector,void*);
  long onCmdGetIntValue(FXObject*,FXSelector,void*);
public:

  /// Construct progress bar
  FXProgressBar(FXComposite* p,FXObject* target=NULL,FXSelector sel=0,FXuint opts=PROGRESSBAR_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Change the amount of progress
  void setProgress(FXuint value);

  /// Get current progress
  FXuint getProgress() const { return progress; }

  /// Set total amount of progress
  void setTotal(FXuint value);

  /// Return total amount of progrss
  FXuint getTotal() const { return total; }

  /// Increment progress by given amount
  void increment(FXuint value);

  /// Hide progress percentage
  void hideNumber();

  /// Show progress percentage
  void showNumber();

  /// Change progress bar width
  void setBarSize(FXint size);

  /// Return progress bar width
  FXint getBarSize() const { return barsize; }

  /// Change backgroundcolor
  void setBarBGColor(FXColor clr);

  /// Return background color
  FXColor getBarBGColor() const { return barBGColor; }

  /// Change bar color
  void setBarColor(FXColor clr);

  /// Return bar color
  FXColor getBarColor() const { return barColor; }

  /// Change text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const { return textNumColor; }

  /// Change alternate text color shown when bar under text
  void setTextAltColor(FXColor clr);

  /// Return alternate text color
  FXColor getTextAltColor() const { return textAltColor; }

  /// Set the text font
  void setFont(FXFont *fnt);

  /// Get the text font
  FXFont* getFont() const { return font; }

  /// Change progress bar style
  void setBarStyle(FXuint style);

  /// Return current progress bar style
  FXuint getBarStyle() const;

  /// Save progress bar to a stream
  virtual void save(FXStream& store) const;

  /// Load progress bar from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXProgressBar();
  };

}

#endif
