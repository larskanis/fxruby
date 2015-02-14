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

// Arrow style options
enum {
  ARROW_NONE     = 0,		// No arrow
  ARROW_UP       = 0x00080000,	// Arrow points up
  ARROW_DOWN     = 0x00100000,	// Arrow points down
  ARROW_LEFT     = 0x00200000,	// Arrow points left
  ARROW_RIGHT    = 0x00400000,	// Arrow points right
  ARROW_AUTO     = 0x00800000,  // Automatically fire when hovering mouse over button
  ARROW_REPEAT   = 0x01000000,	// Button repeats if held down
  ARROW_AUTOGRAY = 0x02000000,	// Automatically gray out when not updated
  ARROW_AUTOHIDE = 0x04000000,	// Automatically hide when not updated
  ARROW_TOOLBAR  = 0x08000000,	// Button is toolbar-style
  ARROW_NORMAL   = FRAME_RAISED|FRAME_THICK|ARROW_UP
  };


/// Button with an arrow
class FXArrowButton : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_NULL);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onRepeat(FXObject*,FXSelector,void* PTR_NULL);
  long onAuto(FXObject*,FXSelector,void* PTR_IGNORE);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_REPEAT=FXFrame::ID_LAST,
    ID_AUTO,
    ID_LAST
    };
public:
  %extend {
    /// Construct arrow button
    FXArrowButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=ARROW_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbArrowButton(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set the button state (where TRUE means the button is down)
  void setState(FXbool s);

  /// Get the button state (where TRUE means the button is down)
  FXbool getState() const;

  /// Set status line help text for this arrow button
  void setHelpText(const FXString& text);

  /// Get status line help text for this arrow button
  const FXString& getHelpText() const;

  /// Set tool tip message for this arrow button
  void setTipText(const FXString& text);

  /// Get tool tip message for this arrow button
  const FXString& getTipText() const;

  /// Set the arrow style flags
  void setArrowStyle(FXuint style);

  /// Get the arrow style flags
  FXuint getArrowStyle() const;

  /// Set the default arrow size
  void setArrowSize(FXint size);

  /// Get the default arrow size
  FXint getArrowSize() const;

  /// Set the current justification mode.
  void setJustify(FXuint mode);

  /// Get the current justification mode.
  FXuint getJustify() const;

  /// Get the fill color for the arrow
  FXColor getArrowColor() const;

  /// Set the fill color for the arrow
  void setArrowColor(FXColor clr);

  /// Destructor
  virtual ~FXArrowButton();
  };


DECLARE_FXOBJECT_VIRTUALS(FXArrowButton)
DECLARE_FXID_VIRTUALS(FXArrowButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXArrowButton)
DECLARE_FXWINDOW_VIRTUALS(FXArrowButton)

