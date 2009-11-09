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

/// Splitter options
enum {
  SPLITTER_HORIZONTAL = 0,                  /// Split horizontally
  SPLITTER_VERTICAL   = 0x00008000,         /// Split vertically
  SPLITTER_REVERSED   = 0x00010000,         /// Reverse-anchored
  SPLITTER_TRACKING   = 0x00020000,         /// Track continuous during split
  SPLITTER_NORMAL     = SPLITTER_HORIZONTAL
  };

%typemap(check) FXint SPLITTER_PANEL_INDEX {
  if ($1 < 0 || $1 >= arg1->numChildren()) {
    rb_raise(rb_eIndexError, "splitter panel index out of bounds");
  }
}

%apply FXint SPLITTER_PANEL_INDEX { FXint index };

/**
* Splitter window is used to interactively repartition
* two or more subpanels.
* Space may be subdivided horizontally (SPLITTER_HORIZONTAL, which
* the default) or vertically (SPLITTER_VERTICAL option).
* When the splitter is itself resized, the right-most (bottom-most)
* child window will be resized unless the splitter window is reversed;
* if the splitter is reversed, the left-most (top-most) child window
* will be resized instead.
* The splitter widget sends a SEL_CHANGED to its target
* during the resizing of the panels; at the end of the resize interaction,
* it sends a SEL_COMMAND to signify that the resize operation is complete.
* Normally, children are resizable from 0 upwards; however, if the child
* in a horizontally oriented splitter has LAYOUT_FILL_X in combination with 
* LAYOUT_FIX_WIDTH, it will not be made smaller than its default width,
* except when the child is the last visible widget (or first when the option
* SPLITTER_REVERSED has been passed to the splitter).
* In a vertically oriented splitter, children with LAYOUT_FILL_Y and 
* LAYOUT_FIX_HEIGHT behave analogously.
*/
class FXSplitter : public FXComposite {
protected:
  FXSplitter();
  void adjustHLayout();
  void adjustVLayout();
  void moveHSplit(FXint amount);
  void moveVSplit(FXint amount);
  void drawHSplit(FXint pos);
  void drawVSplit(FXint pos);
  FXWindow* findHSplit(FXint pos);
  FXWindow* findVSplit(FXint pos);
public:
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusNext(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusPrev(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
public:
  
  %extend {
    /// Construct new splitter widget
    FXSplitter(FXComposite* p,FXuint opts=SPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbSplitter(p,opts,x,y,w,h);
      }

    /// Construct new splitter widget, which will notify target about size changes
    FXSplitter(FXComposite* p,FXObject* tgt,FXSelector sel,FXuint opts=SPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbSplitter(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return size of the panel at index
  FXint getSplit(FXint index) const;

  /// Change the size of panel at the given index
  void setSplit(FXint index,FXint size);

  /// Change splitter style
  void setSplitterStyle(FXuint style);
  
  /// Return current splitter style
  FXuint getSplitterStyle() const;
  
  /// Change splitter bar size
  void setBarSize(FXint bs);
  
  /// Return current bar size
  FXint getBarSize() const;

  /// Destroy splitter
  virtual ~FXSplitter();
  };

%clear FXint index;

DECLARE_FXOBJECT_VIRTUALS(FXSplitter)
DECLARE_FXID_VIRTUALS(FXSplitter)
DECLARE_FXDRAWABLE_VIRTUALS(FXSplitter)
DECLARE_FXWINDOW_VIRTUALS(FXSplitter)

