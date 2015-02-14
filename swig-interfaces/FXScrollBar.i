/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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

/// ScrollBar styles
enum {
  SCROLLBAR_VERTICAL   = 0,             /// Vertically oriented
  SCROLLBAR_HORIZONTAL = 0x00020000,    /// Horizontally oriented
  SCROLLBAR_WHEELJUMP  = 0x00040000     /// Mouse wheel jumps instead of sliding smoothly
  };


%rename("barSize")  FXScrollBar::getBarSize() const;
%rename("barSize=") FXScrollBar::setBarSize(FXint);

/**
* The scroll bar is used when a document has a larger content than may be made
* visible.  The range is the total size of the document, the page is the part
* of the document which is visible.  The size of the scrollbar thumb is adjusted
* to give feedback of the relative sizes of each.
* The scroll bar may be manipulated by the left mouse button (normal scrolling), by the
* middle mouse button (same as the left mouse only the scroll position can jump to the
* place where the click is made), or by the right mouse button (vernier- or fine-scrolling).
* Holding down the control key while scrolling with the left or middle mouse button also
* enables vernier-scrolling mode.  The vernier-scrolling mode is very useful for accurate
* positioning in large documents.
* Finally, if the mouse sports a wheel, the scroll bar can be manipulated by means
* of the mouse wheel as well.  Holding down the Control-key during wheel motion
* will cause the scrolling to go faster than normal.
* While moving the scroll bar, a message of type SEL_CHANGED will be sent to the
* target, and the message data will reflect the current position of type FXint.
* At the end of the interaction, the scroll bar will send a message of type
* SEL_COMMAND to notify the target of the final position.
*/
class FXScrollBar : public FXWindow {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onTimeWheel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_IN);
  long onCmdGetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_OUT);
public:
  enum{
    ID_TIMEWHEEL=FXWindow::ID_LAST,
    ID_AUTOSCROLL,
    ID_LAST
    };
public:
  %extend {
    /// Construct scroll bar
    FXScrollBar(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=SCROLLBAR_VERTICAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbScrollBar(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Set content size range
  void setRange(FXint r);

  /// Return content size range
  FXint getRange() const;

  /// Set viewport page size
  void setPage(FXint p);

  /// Return page size
  FXint getPage() const;

  /// Set scroll increment for line
  void setLine(FXint l);

  /// Return line increment
  FXint getLine() const;

  /// Change current scroll position
  void setPosition(FXint p);

  %extend {
    /// Return scroll position
    FXint position() const {
      return self->getPosition();
      }
    }

  /// Change highlight color
  void setHiliteColor(FXColor clr);

  /// Return highlight color
  FXColor getHiliteColor() const;

  /// Change shadow color
  void setShadowColor(FXColor clr);

  /// Return shadow color
  FXColor getShadowColor() const;

  /// Return border color
  FXColor getBorderColor() const;

  /// Change border color
  void setBorderColor(FXColor clr);

  /// Change the scrollbar style
  FXuint getScrollBarStyle() const;

  /// Get the current scrollbar style
  void setScrollBarStyle(FXuint style);

  /// Change the bar size
  void setBarSize(FXint size);

  /// Return the bar size
  FXint getBarSize() const;

  /// Destructor
  virtual ~FXScrollBar();
  };


DECLARE_FXOBJECT_VIRTUALS(FXScrollBar)
DECLARE_FXID_VIRTUALS(FXScrollBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXScrollBar)
DECLARE_FXWINDOW_VIRTUALS(FXScrollBar)


/// Corner between scroll bars
class FXScrollCorner : public FXWindow {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXScrollCorner(FXComposite* p){
      return new FXRbScrollCorner(p);
      }
    }

  /// Destructor
  virtual ~FXScrollCorner();
  };


DECLARE_FXOBJECT_VIRTUALS(FXScrollCorner)
DECLARE_FXID_VIRTUALS(FXScrollCorner)
DECLARE_FXDRAWABLE_VIRTUALS(FXScrollCorner)
DECLARE_FXWINDOW_VIRTUALS(FXScrollCorner)

