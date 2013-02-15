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

/// Text widget options
enum {
  TEXT_READONLY      = 0x00100000,              /// Text is NOT editable
  TEXT_WORDWRAP      = 0x00200000,              /// Wrap at word breaks
  TEXT_OVERSTRIKE    = 0x00400000,              /// Overstrike mode
  TEXT_FIXEDWRAP     = 0x00800000,              /// Fixed wrap columns
  TEXT_NO_TABS       = 0x01000000,              /// Insert spaces for tabs
  TEXT_AUTOINDENT    = 0x02000000,              /// Autoindent
  TEXT_SHOWACTIVE    = 0x04000000,              /// Show active line
  TEXT_AUTOSCROLL    = 0x08000000               /// Logging mode, keeping last line visible
  };


/// Selection modes
enum FXTextSelectionMode {
  SELECT_CHARS,
  SELECT_WORDS,
  SELECT_LINES
  };


/// Highlight style entry
struct FXHiliteStyle {
  %extend {
		FXHiliteStyle(){
			FXHiliteStyle *self = new FXHiliteStyle();
			self->normalForeColor = 0;
			self->normalBackColor = 0;
			self->selectForeColor = 0;
			self->selectBackColor = 0;
			self->hiliteForeColor = 0;
			self->hiliteBackColor = 0;
			self->activeBackColor = 0;
			self->style = 0;
			return self;
			}
    }
  FXColor normalForeColor;            /// Normal text foreground color
  FXColor normalBackColor;            /// Normal text background color
  FXColor selectForeColor;            /// Selected text foreground color
  FXColor selectBackColor;            /// Selected text background color
  FXColor hiliteForeColor;            /// Highlight text foreground color
  FXColor hiliteBackColor;            /// Highlight text background color
  FXColor activeBackColor;            /// Active text background color
  FXuint  style;                      /// Highlight text style
  ~FXHiliteStyle();
  };


/**
* Text mutation callback data passed with the SEL_INSERTED,
* SEL_REPLACED, and SEL_DELETED messages; both old and new
* text is available on behalf of the undo system as well as
* syntax highlighting.
*/
struct FXTextChange {
  FXint   pos;          /// Position in buffer
  FXint   ndel;         /// Number characters deleted at position
  FXint   nins;         /// Number characters inserted at position
  %extend {
    VALUE ins() const {
      return to_ruby(self->ins,self->nins);
      }
    VALUE del() const {
      return to_ruby(self->del,self->ndel);
      }
    }
  };

%rename("overstrike?") FXText::isOverstrike() const;
%rename("overstrike=") FXText::setOverstrike(FXbool);
%rename("numRows")     FXText::getNumRows() const;

/**
* The text widget supports editing of multiple lines of text.
* An optional style table can provide text coloring based on
* the contents of an optional parallel style buffer, which is
* maintained as text is edited.  In a typical scenario, the
* contents of the style buffer is either directly written when
* the text is added to the widget, or is continually modified
* by editing the text via syntax-based highlighting engine which
* colors the text based on syntactical patterns.
*/
class FXText : public FXScrollArea {
public:
  enum {
    STYLE_UNDERLINE = 0x0001,   /// Underline text
    STYLE_STRIKEOUT = 0x0002,   /// Strike out text
    STYLE_BOLD      = 0x0004    /// Bold text
    };
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onBeginDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onEndDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onDragged(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onBlink(FXObject*,FXSelector,void* PTR_IGNORE);
  long onFlash(FXObject*,FXSelector,void* PTR_IGNORE);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_EVENT);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);

  // Control commands
  long onCmdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleOverstrike(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleOverstrike(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorRow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCursorRow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorColumn(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCursorColumn(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHaveSelection(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdSearch(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdReplace(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSearchNext(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSearchSel(FXObject*,FXSelector,void* PTR_IGNORE);

  // Cursor movement
  long onCmdCursorTop(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorBottom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorHome(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorEnd(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorDown(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordStart(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorWordEnd(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorPageDown(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorPageUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorScreenTop(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorScreenBottom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorScreenCenter(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorParHome(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCursorParEnd(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBlockBeg(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBlockEnd(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdGotoMatching(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdGotoSelected(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdGotoLine(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdScrollUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdScrollDown(FXObject*,FXSelector,void* PTR_IGNORE);

  // Mark and extend
  long onCmdMark(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdExtend(FXObject*,FXSelector,void* PTR_IGNORE);

  // Inserting
  long onCmdOverstString(FXObject*,FXSelector,void* PTR_CHAR);
  long onCmdInsertString(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdInsertNewline(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdInsertTab(FXObject*,FXSelector,void* PTR_IGNORE);

  // Manipulation Selection
  long onCmdCutSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCopySel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPasteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdChangeCase(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdShiftText(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPasteMiddle(FXObject*,FXSelector,void* PTR_IGNORE);

  // Changing Selection
  long onCmdSelectChar(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectWord(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectLine(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectMatching(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectBlock(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeselectAll(FXObject*,FXSelector,void* PTR_IGNORE);

  // Deletion
  long onCmdBackspace(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBackspaceWord(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBackspaceBol(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDelete(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteWord(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteEol(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteLine(FXObject*,FXSelector,void* PTR_IGNORE);

public:
  static const FXchar textDelimiters[];

public:

  enum {
    ID_CURSOR_TOP=FXScrollArea::ID_LAST,
    ID_CURSOR_BOTTOM,
    ID_CURSOR_HOME,
    ID_CURSOR_END,
    ID_CURSOR_RIGHT,
    ID_CURSOR_LEFT,
    ID_CURSOR_UP,
    ID_CURSOR_DOWN,
    ID_CURSOR_WORD_LEFT,
    ID_CURSOR_WORD_RIGHT,
    ID_CURSOR_WORD_START,
    ID_CURSOR_WORD_END,
    ID_CURSOR_PAGEDOWN,
    ID_CURSOR_PAGEUP,
    ID_CURSOR_SCRNTOP,
    ID_CURSOR_SCRNBTM,
    ID_CURSOR_SCRNCTR,
    ID_CURSOR_PAR_HOME,
    ID_CURSOR_PAR_END,
    ID_SCROLL_UP,
    ID_SCROLL_DOWN,
    ID_MARK,
    ID_EXTEND,
    ID_OVERST_STRING,
    ID_INSERT_STRING,
    ID_INSERT_NEWLINE,
    ID_INSERT_TAB,
    ID_CUT_SEL,
    ID_COPY_SEL,
    ID_DELETE_SEL,
    ID_PASTE_SEL,
    ID_PASTE_MIDDLE,
    ID_SELECT_CHAR,
    ID_SELECT_WORD,
    ID_SELECT_LINE,
    ID_SELECT_ALL,
    ID_SELECT_MATCHING,
    ID_SELECT_BRACE,
    ID_SELECT_BRACK,
    ID_SELECT_PAREN,
    ID_SELECT_ANG,
    ID_DESELECT_ALL,
    ID_BACKSPACE,
    ID_BACKSPACE_WORD,
    ID_BACKSPACE_BOL,
    ID_DELETE,
    ID_DELETE_WORD,
    ID_DELETE_EOL,
    ID_DELETE_ALL,
    ID_DELETE_LINE,
    ID_TOGGLE_EDITABLE,
    ID_TOGGLE_OVERSTRIKE,
    ID_CURSOR_ROW,
    ID_CURSOR_COLUMN,
    ID_CLEAN_INDENT,
    ID_SHIFT_LEFT,
    ID_SHIFT_RIGHT,
    ID_SHIFT_TABLEFT,
    ID_SHIFT_TABRIGHT,
    ID_UPPER_CASE,
    ID_LOWER_CASE,
    ID_GOTO_MATCHING,
    ID_GOTO_SELECTED,
    ID_GOTO_LINE,
    ID_SEARCH_FORW_SEL,
    ID_SEARCH_BACK_SEL,
    ID_SEARCH_FORW,
    ID_SEARCH_BACK,
    ID_SEARCH,
    ID_REPLACE,
    ID_LEFT_BRACE,
    ID_LEFT_BRACK,
    ID_LEFT_PAREN,
    ID_LEFT_ANG,
    ID_RIGHT_BRACE,
    ID_RIGHT_BRACK,
    ID_RIGHT_PAREN,
    ID_RIGHT_ANG,
    ID_BLINK,
    ID_FLASH,
    ID_LAST
    };
public:

  /// Construct multi-line text widget
  %extend {
    FXText(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2){
      return new FXRbText(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Change top margin
  void setMarginTop(FXint pt);

  /// Return top margin
  FXint getMarginTop() const;

  /// Change bottom margin
  void setMarginBottom(FXint pb);

  /// Return bottom margin
  FXint getMarginBottom() const;

  /// Change left margin
  void setMarginLeft(FXint pl);

  /// Return left margin
  FXint getMarginLeft() const;

  /// Change right margin
  void setMarginRight(FXint pr);

  /// Return right margin
  FXint getMarginRight() const;

  /// Return wrap columns
  FXint getWrapColumns() const;

  /// Set wrap columns
  void setWrapColumns(FXint cols);

  /// Return tab columns
  FXint getTabColumns() const;

  /// Change tab columns
  void setTabColumns(FXint cols);

  /// Return number of columns used for line numbers
  FXint getBarColumns() const;

  /// Change number of columns used for line numbers
  void setBarColumns(FXint cols);

  /// Return TRUE if text was modified
  FXbool isModified() const;

  /// Set modified flag
  void setModified(FXbool mod=TRUE);

  /// Set editable flag
  void setEditable(FXbool edit=TRUE);

  /// Return TRUE if text is editable
  FXbool isEditable() const;

  /// Set overstrike mode
  void setOverstrike(FXbool over=TRUE);

  /// Return TRUE if overstrike mode in effect
  FXbool isOverstrike() const;

  /// Set styled text mode
  void setStyled(FXbool styled=TRUE);

  /// Return TRUE if style buffer
  FXbool isStyled() const;

  /// Change delimiters of words
  void setDelimiters(const FXchar* delims=textDelimiters);

  /// Return word delimiters
  const FXchar* getDelimiters() const;

  /// Change text font
  void setFont(FXFont* fnt);

  /// Return text font
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

  /// Change highlighted text color
  void setHiliteTextColor(FXColor clr);

  /// Return highlighted text color
  FXColor getHiliteTextColor() const;

  /// Change highlighted background color
  void setHiliteBackColor(FXColor clr);

  /// Return highlighted background color
  FXColor getHiliteBackColor() const;

  /// Change active background color
  void setActiveBackColor(FXColor clr);

  /// Return active background color
  FXColor getActiveBackColor() const;

  /// Change cursor color
  void setCursorColor(FXColor clr);

  /// Return cursor color
  FXColor getCursorColor() const;

  /// Change line number color
  void setNumberColor(FXColor clr);

  /// Return line number color
  FXColor getNumberColor() const;

  /// Change bar color
  void setBarColor(FXColor clr);

  /// Return bar color
  FXColor getBarColor() const;

  /// Set help text
  void setHelpText(const FXString& text);

  /// Return help text
  FXString getHelpText() const;

  /// Set the tool tip message for this text field
  void setTipText(const FXString& text);

  /// Get the tool tip message for this text field
  FXString getTipText() const;

  /// Get character at position in text buffer
  FXint getByte(FXint pos) const;

  /// Get wide character at position pos
  FXwchar getChar(FXint pos) const;

  /// Get length of wide character at position pos
  FXint getCharLen(FXint pos) const;

  /// Get style at position in style buffer
  FXint getStyle(FXint pos) const;

  %extend {

    // Extract n bytes of text from position pos
    VALUE extractText(FXint pos,FXint n) const {
      VALUE str;
      FXString buffer;
      self->extractText(buffer,pos,n);
      str=to_ruby(buffer.text(),n);
      return str;
      }

    /// Extract n bytes of style info from position pos
    VALUE extractStyle(FXint pos,FXint n) const {
      FXString style;
      VALUE str=Qnil;
      if(self->isStyled()){
        self->extractStyle(style,pos,n);
        str=to_ruby(style.text(),n);
        }
      return str;
      }

  } // end %extend

  /// Return text in the widget
  FXString getText() const;

  /// Return length of buffer
  FXint getLength() const;

  /// Return number of rows in buffer
  FXint getNumRows() const;

  /// Shift block of lines from position start up to end by given amount
  FXint shiftText(FXint start,FXint end,FXint amount,FXbool notify=FALSE);

  %extend {
    /**
    * Search for string in text buffer, returning the extent of
    * the string in beg and end.  The search starts from the given
    * starting position, scans forward (SEARCH_FORWARD) or backward
    * (SEARCH_BACKWARD), and wraps around if SEARCH_WRAP has been
    * specified.  The search type is either a plain search (SEARCH_EXACT),
    * case insensitive search (SEARCH_IGNORECASE), or regular expression
    * search (SEARCH_REGEX).
    * For regular expression searches, capturing parentheses are used if
    * npar is greater than 1; in this case, the number of entries in the
    * beg[], end[] arrays must be npar also.  If either beg or end or
    * both are NULL, internal arrays are used.
    * [This API is still subject to change!!]
    */
    VALUE findText(const FXString& string,FXint start=0,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP|SEARCH_EXACT){
      FXint* beg;
      FXint* end;
      VALUE ary=Qnil;
			FXint ngroups=string.contains('(')+1;  // FIXME: is this right?
      if(!FXMALLOC(&beg,FXint,ngroups)){
        return Qnil;
				}
      if(!FXMALLOC(&end,FXint,ngroups)){
        FXFREE(&beg);
				return Qnil;
				}
      if(self->findText(string,beg,end,start,flags,ngroups)){
        ary=rb_ary_new();
				rb_ary_push(ary,FXRbMakeArray(beg,ngroups));
				rb_ary_push(ary,FXRbMakeArray(end,ngroups));
        }
      FXFREE(&beg);
      FXFREE(&end);
      return ary;
      }
  }

  /// Return TRUE if position pos is selected
  FXbool isPosSelected(FXint pos) const;

  /// Return TRUE if position is fully visible
  FXbool isPosVisible(FXint pos) const;

  /// Return text position at given visible x,y coordinate
  FXint getPosAt(FXint x,FXint y) const;

  /// Count number of rows; start should be on a row start
  FXint countRows(FXint start,FXint end) const;

  /// Count number of columns; start should be on a row start
  FXint countCols(FXint start,FXint end) const;

  /// Count number of newlines
  FXint countLines(FXint start,FXint end) const;

  /// Return position of begin of line containing position pos
  FXint lineStart(FXint pos) const;

  /// Return position of end of line containing position pos
  FXint lineEnd(FXint pos) const;

  /// Return start of next line
  FXint nextLine(FXint pos,FXint nl=1) const;

  /// Return start of previous line
  FXint prevLine(FXint pos,FXint nl=1) const;

  /// Return row start
  FXint rowStart(FXint pos) const;

  /// Return row end
  FXint rowEnd(FXint pos) const;

  /// Return start of next row
  FXint nextRow(FXint pos,FXint nr=1) const;

  /// Return start of previous row
  FXint prevRow(FXint pos,FXint nr=1) const;

  /// Return end of previous word
  FXint leftWord(FXint pos) const;

  /// Return begin of next word
  FXint rightWord(FXint pos) const;

  /// Return begin of word
  FXint wordStart(FXint pos) const;

  /// Return end of word
  FXint wordEnd(FXint pos) const;

  /// Return validated utf8 character start position
  FXint validPos(FXint pos) const;

  /// Retreat to the previous valid utf8 character start
  FXint dec(FXint pos) const;

  /// Advance to the next valid utf8 character start
  FXint inc(FXint pos) const;

  /// Make line containing pos the top line
  void setTopLine(FXint pos);

  /// Return position of top line
  FXint getTopLine() const;

  /// Make line containing pos the bottom line
  void setBottomLine(FXint pos);

  /// Return the position of the bottom line
  FXint getBottomLine() const;

  /// Make line containing pos the center line
  void setCenterLine(FXint pos);

  /// Set the anchor position
  void setAnchorPos(FXint pos);

  /// Return the anchor position
  FXint getAnchorPos() const;

  /// Set cursor row
  void setCursorRow(FXint row,FXbool notify=FALSE);

  /// Return cursor row, i.e. indent position
  FXint getCursorRow() const;

  /// Set cursor column
  void setCursorColumn(FXint col,FXbool notify=FALSE);

  /// Return cursor column
  FXint getCursorColumn() const;

  /// Return the cursor position
  FXint getCursorPos() const;

  /// Return selstartpos
  FXint getSelStartPos() const;

  /// Return selendpos
  FXint getSelEndPos() const;

  /// Select all text
  FXbool selectAll(FXbool notify=FALSE);

  /// Select len characters starting at given position pos
  FXbool setSelection(FXint pos,FXint len,FXbool notify=FALSE);

  /// Highlight len characters starting at given position pos
  FXbool setHighlight(FXint start,FXint len);

  /// Unhighlight the text
  FXbool killHighlight();

  /// Scroll text to make the given position visible
  void makePositionVisible(FXint pos);

  /// Change text widget style
  void setTextStyle(FXuint style);

  /// Return text widget style
  FXuint getTextStyle() const;

  /// Change number of visible rows
  void setVisibleRows(FXint rows);

  /// Return number of visible rows
  FXint getVisibleRows() const;

  /// Change number of visible columns
  void setVisibleColumns(FXint cols);

  /// Return number of visible columns
  FXint getVisibleColumns() const;

  /**
  * Change brace and parenthesis match highlighting time, in ms.
  * A match highlight time of 0 disables brace matching.
  */
  void setHiliteMatchTime(FXuint t);

  /**
  * Return brace and parenthesis match highlighting time, in ms.
  */
  FXuint getHiliteMatchTime() const;

  %extend {
    /// Set highlight styles
    void setHiliteStyles(VALUE styles){
      if(self->isMemberOf(FXMETACLASS(FXRbText))){
        FXRbText *text=dynamic_cast<FXRbText*>(self);
	FXASSERT(text);
        Check_Type(styles,T_ARRAY);
	if(text->numStyles>0){
	  delete [] text->styles;
	  text->numStyles=0;
	  }
	text->numStyles=RARRAY_LEN(styles);
	if(text->numStyles>0){
          text->styles=new FXHiliteStyle[text->numStyles];
          for (long i=0; i<text->numStyles; i++){
            FXHiliteStyle* ptr;
	    SWIG_ConvertPtr(rb_ary_entry(styles,i),(void **)&ptr,SWIGTYPE_p_FXHiliteStyle,1);
            text->styles[i]=*ptr;
            }
	  self->setHiliteStyles(text->styles);
	  }
	}
      else{
        rb_notimplement();
        }
      }

    /// Get highlight styles
    VALUE getHiliteStyles() const {
      if(self->isMemberOf(FXMETACLASS(FXRbText))){
        const FXRbText* text=dynamic_cast<const FXRbText*>(self);
	FXASSERT(text);
        VALUE ary=rb_ary_new();
        for(FXint i=0; i<text->numStyles; i++){
	  rb_ary_push(ary,FXRbGetRubyObj(&(text->styles[i]),"FXHiliteStyle *"));
	  }
	return ary;
	}
      else{
        rb_notimplement();
	return Qnil; // not reached
        }
      }
  }

  /// Destructor
  virtual ~FXText();
  };


DECLARE_FXOBJECT_VIRTUALS(FXText)
DECLARE_FXID_VIRTUALS(FXText)
DECLARE_FXDRAWABLE_VIRTUALS(FXText)
DECLARE_FXWINDOW_VIRTUALS(FXText)
DECLARE_FXSCROLLAREA_VIRTUALS(FXText)
DECLARE_FXTEXT_VIRTUALS(FXText)

