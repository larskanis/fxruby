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

/// Textfield styles
enum {
  TEXTFIELD_PASSWD     = 0x00080000,    /// Password mode
  TEXTFIELD_INTEGER    = 0x00100000,    /// Integer mode
  TEXTFIELD_REAL       = 0x00200000,    /// Real mode
  TEXTFIELD_READONLY   = 0x00400000,    /// NOT editable
  TEXTFIELD_ENTER_ONLY = 0x00800000,    /// Only callback when enter hit
  TEXTFIELD_LIMITED    = 0x01000000,    /// Limit entry to given number of columns
  TEXTFIELD_OVERSTRIKE = 0x02000000,    /// Overstrike mode
  TEXTFIELD_AUTOGRAY   = 0x04000000,    /// Automatically gray out text field when not updated
  TEXTFIELD_AUTOHIDE   = 0x08000000,    /// Automatically hide text field when not updated
  TEXTFIELD_NORMAL     = FRAME_SUNKEN|FRAME_THICK
  };

%rename("overstrike=") FXTextField::setOverstrike(FXbool);
%rename("overstrike?") FXTextField::isOverstrike() const;

/**
* A Text field is a single-line text entry widget.
* The text field widget supports clipboard for cut-and-paste
* operations.
* The text field also sends SEL_COMMAND when the focus moves to another control.
* TEXTFIELD_ENTER_ONLY can be passed to suppress this feature. Typically, this
* flag is used in dialogs that close when ENTER is hit in a text field.
*/
class FXTextField : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onVerify(FXObject*,FXSelector,void* PTR_CSTRING);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionRequest(FXObject*,FXSelector,void* ptr);
  long onClipboardLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onBlink(FXObject*,FXSelector,void* PTR_IGNORE);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdSetRealValue(FXObject*,FXSelector,void* PTR_PDOUBLE);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdGetRealValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdCursorHome(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorEnd(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordStart(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordEnd(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMark(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdExtend(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeselectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCutSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCopySel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPasteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPasteMiddle(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdOverstString(FXObject*,FXSelector,void* PTR_CHAR);
  long onCmdInsertString(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdBackspace(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDelete(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleOverstrike(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleOverstrike(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHaveSelection(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:

  /// Default text delimiters
  static const FXchar textDelimiters[];

public:

  enum{
    ID_CURSOR_HOME=FXFrame::ID_LAST,
    ID_CURSOR_END,
    ID_CURSOR_RIGHT,
    ID_CURSOR_LEFT,
    ID_CURSOR_WORD_LEFT,
    ID_CURSOR_WORD_RIGHT,
    ID_CURSOR_WORD_START,
    ID_CURSOR_WORD_END,
    ID_MARK,
    ID_EXTEND,
    ID_SELECT_ALL,
    ID_DESELECT_ALL,
    ID_CUT_SEL,
    ID_COPY_SEL,
    ID_PASTE_SEL,
    ID_DELETE_SEL,
    ID_DELETE_ALL,
    ID_OVERST_STRING,
    ID_INSERT_STRING,
    ID_BACKSPACE,
    ID_DELETE,
    ID_TOGGLE_EDITABLE,
    ID_TOGGLE_OVERSTRIKE,
    ID_BLINK,
    ID_LAST
    };
public:

  /// Construct text field wide enough to display ncols columns
  %extend {
    FXTextField(FXComposite* p,FXint ncols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TEXTFIELD_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbTextField(p,ncols,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change text field editability
  void setEditable(FXbool edit=TRUE);

  /// Return TRUE if text field may be edited
  FXbool isEditable() const;

  /// Set overstrike mode
  void setOverstrike(FXbool over=TRUE);

  /// Return TRUE if overstrike mode in effect
  FXbool isOverstrike() const;

  /// Set cursor position
  void setCursorPos(FXint pos);

  /// Return cursor position
  FXint getCursorPos() const;

  /// Change anchor position
  void setAnchorPos(FXint pos);

  /// Return anchor position
  FXint getAnchorPos() const;

  /// Set the text for this label
  void setText(const FXString& text,FXbool notify=FALSE);

  /// Get the text for this label
  FXString getText() const;

  /// Set the text font
  void setFont(FXFont* fnt);

  /// Get the text font
  FXFont* getFont() const;

  /// Change text color
  void setTextColor(FXColor clr);

  /// Return text color
  FXColor getTextColor() const;

  /// Change selected background color
  void setSelBackColor(FXColor clr);

  /// Return selected background color
  FXColor getSelBackColor() const;

  /// Change selected text color
  void setSelTextColor(FXColor clr);

  /// Return selected text color
  FXColor getSelTextColor() const;

  /// Changes the cursor color
  void setCursorColor(FXColor clr);

  /// Return the cursor color
  FXColor getCursorColor() const;

  /**
   * Change the default width of the text field in terms of a number
   * of columns times the width of the numeral '8'.
   */
  void setNumColumns(FXint cols);

  /// Return number of columns
  FXint getNumColumns() const;

  /**
   * Change text justification mode. The justify mode is a combination of
   * horizontal justification (JUSTIFY_LEFT, JUSTIFY_RIGHT, or JUSTIFY_CENTER_X),
   * and vertical justification (JUSTIFY_TOP, JUSTIFY_BOTTOM, JUSTIFY_CENTER_Y).
   * Note that JUSTIFY_CENTER_X can not be set from the constructor since by
   * default text fields are left-justified.
   */
  void setJustify(FXuint mode);

  /// Return text justification mode
  FXuint getJustify() const;

  /// Change word delimiters
  void setDelimiters(const FXchar* delims=textDelimiters);

  /// Return word delimiters
  const FXchar* getDelimiters() const;

  /// Set the status line help text for this label
  void setHelpText(const FXString& text);

  /// Get the status line help text for this label
  const FXString& getHelpText() const;

  /// Set the tool tip message for this text field
  void setTipText(const FXString& text);

  /// Get the tool tip message for this text field
  const FXString& getTipText() const;

  /// Change text style
  void setTextStyle(FXuint style);

  /// Return text style
  FXuint getTextStyle() const;

  /// Select all text
  FXbool selectAll();

  /// Select len characters starting at given position pos
  FXbool setSelection(FXint pos,FXint len);

  /// Extend the selection from the anchor to the given position
  FXbool extendSelection(FXint pos);

  /// Unselect the text
  FXbool killSelection();

  /// Return TRUE if position pos is selected
  FXbool isPosSelected(FXint pos) const;

  /// Return TRUE if position is fully visible
  FXbool isPosVisible(FXint pos) const;

  /// Scroll text to make the given position visible
  void makePositionVisible(FXint pos);

  /// Destructor
  virtual ~FXTextField();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTextField)
DECLARE_FXID_VIRTUALS(FXTextField)
DECLARE_FXDRAWABLE_VIRTUALS(FXTextField)
DECLARE_FXWINDOW_VIRTUALS(FXTextField)

