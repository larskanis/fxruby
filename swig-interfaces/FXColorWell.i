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

// Color Well Styles
enum {
  COLORWELL_OPAQUEONLY = 0x00008000,  /// Colors must be opaque
  COLORWELL_SOURCEONLY = 0x00010000,   /// ColorWell is never a target
  COLORWELL_NORMAL     = JUSTIFY_LEFT
  };


/**
* A color well is a widget which controls color settings.
* Colors may be dragged and dropped from one color well to another.
* A double-click inside a color well will bring up the standard
* color dialog panel to edit the color well's color.
* Colors may be also pasted by name using middle-mouse click into/out of
* color wells from/to other selection-capable applications; for example,
* you can highlight the word `red' and paste it into a color well.
*/
class FXColorWell : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onBeginDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onEndDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onDragged(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onClicked(FXObject*,FXSelector,void* PTR_IGNORE);
  long onDoubleClicked(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_COLOR);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdColorWell(FXObject*,FXSelector,void* PTR_COLOR);
  long onChgColorWell(FXObject*,FXSelector,void* PTR_COLOR);
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_COLORDIALOG=FXFrame::ID_LAST,
    ID_LAST
    };
public:
  %extend {
    /// Construct color well with initial color clr
    FXColorWell(FXComposite* p,FXColor clr=0,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=COLORWELL_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbColorWell(p,clr,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set color
  void setRGBA(FXColor clr,FXbool notify=FALSE);

  /// Get color
  FXColor getRGBA() const;

  /// Set status line help text for this color well
  void setHelpText(const FXString& text);

  /// Get status line help text for this color well
  const FXString& getHelpText() const;

  /// Set tool tip message for this color well
  void setTipText(const FXString& text);

  /// Get tool tip message for this color well
  const FXString& getTipText() const;

  /// Return true if only opaque colors allowed
  FXbool isOpaqueOnly() const;

  /// Change opaque only mode
  void setOpaqueOnly(FXbool opaque);

  /// Destructor
  virtual ~FXColorWell();
  };


DECLARE_FXOBJECT_VIRTUALS(FXColorWell)
DECLARE_FXID_VIRTUALS(FXColorWell)
DECLARE_FXDRAWABLE_VIRTUALS(FXColorWell)
DECLARE_FXWINDOW_VIRTUALS(FXColorWell)

