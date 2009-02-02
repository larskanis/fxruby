/********************************************************************************
*                                                                               *
*                       S t a t u s B a r   W i d g e t                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2003 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXStatusBar.h 1536 2003-05-14 21:41:00Z lyle $                        *
********************************************************************************/
#ifndef FXSTATUSBAR_H
#define FXSTATUSBAR_H

#ifndef FXHORIZONTALFRAME_H
#include "FXHorizontalFrame.h"
#endif

namespace FX {


/// StatusBar options
enum {
  STATUSBAR_WITH_DRAGCORNER = 0x00020000    /// Causes the DragCorner to be shown
  };


class FXDragCorner;
class FXStatusLine;


/// Status bar
class FXAPI FXStatusBar : public FXHorizontalFrame {
  FXDECLARE(FXStatusBar)
protected:
  FXDragCorner *corner;
  FXStatusLine *status;
protected:
  FXStatusBar(){}
private:
  FXStatusBar(const FXStatusBar&);
  FXStatusBar& operator=(const FXStatusBar&);
public:

  /// Construct status bar with or without a drag corner
  FXStatusBar(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2,FXint hs=4,FXint vs=0);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /// Show or hide the drag corner
  void setCornerStyle(FXbool withcorner=TRUE);

  /// Return TRUE if drag corner shown
  FXbool getCornerStyle() const;

  /// Acess the status line widget
  FXStatusLine *getStatusLine() const { return status; }

  /// Access the drag corner widget
  FXDragCorner *getDragCorner() const { return corner; }

  /// Save status bar to a stream
  virtual void save(FXStream& store) const;

  /// Load status bar from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXStatusBar();
  };

}

#endif
