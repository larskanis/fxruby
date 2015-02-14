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

/// ToolBar Tab styles
enum {
  TOOLBARTAB_HORIZONTAL = 0,              /// Default is for horizontal toolbar
  TOOLBARTAB_VERTICAL   = 0x00008000      /// For vertical toolbar
  };

/**
 * A toolbar tab is used to collapse or uncollapse a sibling
 * widget.  The sibling affected is the widget immediately following
 * the toolbar tab or, if the toolbar tab is the last widget in the list,
 * the widget immediately preceding the toolbar tab.
 */

class FXToolBarTab : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_NULL);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdCollapse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCollapse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdUncollapse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdUncollapse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryTip(FXObject*,FXSelector,void* PTR_EVENT);
public:
  enum {
    ID_COLLAPSE=FXFrame::ID_LAST,
    ID_UNCOLLAPSE,
    ID_LAST
    };
public:
  %extend {
   /// Construct toolbar tab
   FXToolBarTab(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
     return new FXRbToolBarTab(p,tgt,sel,opts,x,y,w,h);
     }
   }

  /// Collapse or uncollapse the toolbar
  void collapse(FXbool fold,FXbool notify=FALSE);

  /// Return true if the toolbar is collapsed
  FXbool isCollapsed() const;

  /// Change the tab style
  void setTabStyle(FXuint style);

  /// Get current tab style
  FXuint getTabStyle() const;

  /// Get the active color
  FXColor getActiveColor() const;

  /// Set the active color
  void setActiveColor(FXColor clr);

  /// Set the tool tip message for the toolbar tab
  void setTipText(const FXString& text);

  /// Get the tool tip message for the toolbar tab
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXToolBarTab();
  };


DECLARE_FXOBJECT_VIRTUALS(FXToolBarTab)
DECLARE_FXID_VIRTUALS(FXToolBarTab)
DECLARE_FXDRAWABLE_VIRTUALS(FXToolBarTab)
DECLARE_FXWINDOW_VIRTUALS(FXToolBarTab)

