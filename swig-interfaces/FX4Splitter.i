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

// Splitter options
enum {
  FOURSPLITTER_TRACKING = 0x00008000,	// Track continuously during split
  FOURSPLITTER_NORMAL   = 0
  };


/**
* The Four-way splitter is a layout manager which manages
* four children like four panes in a window.
* You can use a four-way splitter for example in a CAD program
* where you may want to maintain three orthographic views, and
* one oblique view of a model.
* The four-way splitter allows interactive repartitioning of the
* panes by means of moving the central splitter bars.
* When the four-way splitter is itself resized, each child is
* proportionally resized, maintaining the same split-percentage.
*/
class FX4Splitter : public FXComposite {
protected:
  FX4Splitter();
  FXuchar getMode(FXint x,FXint y);
  void moveSplit(FXint x,FXint y);
  void drawSplit(FXint x,FXint y);
  void adjustLayout();
public:
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdExpand(FXObject*,FXSelector,void*);
  long onUpdExpand(FXObject*,FXSelector,void*);
public:
  enum {
    ExpandNone        = 0,                                  /// None expanded
    ExpandTopLeft     = 1,                                  /// Expand top left child
    ExpandTopRight    = 2,                                  /// Expand top right child
    ExpandBottomLeft  = 4,                                  /// Expand bottom left child
    ExpandBottomRight = 8,                                  /// Expand bottom right child
    ExpandTop         = ExpandTopLeft|ExpandTopRight,       /// Expand top children
    ExpandBottom      = ExpandBottomLeft|ExpandBottomRight, /// Expand bottom children
    ExpandLeft        = ExpandTopLeft|ExpandBottomLeft,     /// Expand left children
    ExpandRight       = ExpandTopRight|ExpandBottomRight,   /// Expand right children
    ExpandAll         = ExpandLeft|ExpandRight              /// Expand all children
    };
public:
  enum {
    ID_EXPAND_NONE=FXComposite::ID_LAST+ExpandNone,
    ID_EXPAND_TOP=ID_EXPAND_NONE+ExpandTop,
    ID_EXPAND_BOTTOM=ID_EXPAND_NONE+ExpandBottom,
    ID_EXPAND_LEFT=ID_EXPAND_NONE+ExpandLeft,
    ID_EXPAND_RIGHT=ID_EXPAND_NONE+ExpandRight,
    ID_EXPAND_TOPLEFT=ID_EXPAND_NONE+ExpandTopLeft,
    ID_EXPAND_TOPRIGHT=ID_EXPAND_NONE+ExpandTopRight,
    ID_EXPAND_BOTTOMLEFT=ID_EXPAND_NONE+ExpandBottomLeft,
    ID_EXPAND_BOTTOMRIGHT=ID_EXPAND_NONE+ExpandBottomRight,
    ID_EXPAND_ALL=ID_EXPAND_NONE+ExpandAll,
    ID_LAST
    };
public:

  %extend {
    /// Create 4-way splitter, initially shown as four unexpanded panes
    FX4Splitter(FXComposite* p,FXuint opts=FOURSPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRb4Splitter(p,opts,x,y,w,h);
      }
  
    /// Create 4-way splitter, initially shown as four unexpanded panes; notifies target about size changes
    FX4Splitter(FXComposite* p,FXObject* tgt,FXSelector sel,FXuint opts=FOURSPLITTER_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRb4Splitter(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Get top left child, if any
  FXWindow *getTopLeft() const;

  /// Get top right child, if any
  FXWindow *getTopRight() const;

  /// Get bottom left child, if any
  FXWindow *getBottomLeft() const;

  /// Get bottom right child, if any
  FXWindow *getBottomRight() const;

  /// Get horizontal split fraction
  FXint getHSplit() const;

  /// Get vertical split fraction
  FXint getVSplit() const;

  /// Change horizontal split fraction
  void setHSplit(FXint s);

  /// Change vertical split fraction
  void setVSplit(FXint s);

  /// Return current splitter style
  FXuint getSplitterStyle() const;
  
  /// Change splitter style
  void setSplitterStyle(FXuint style);
  
  /// Change splitter bar width
  void setBarSize(FXint bs);
  
  /// Get splitter bar width
  FXint getBarSize() const;

  /// Change set of expanded children
  void setExpanded(FXuint set=FX4Splitter::ExpandAll);

  /// Get expanded child, or -1 if not expanded
  FXuint getExpanded() const;
  
  /// Destructor
  virtual ~FX4Splitter();
  };

DECLARE_FXOBJECT_VIRTUALS(FX4Splitter)
DECLARE_FXID_VIRTUALS(FX4Splitter)
DECLARE_FXDRAWABLE_VIRTUALS(FX4Splitter)
DECLARE_FXWINDOW_VIRTUALS(FX4Splitter)

