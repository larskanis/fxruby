module Fox
  #
  # A text field is a single-line text entry widget.
  # The text field widget supports clipboard for cut-and-paste
  # operations.
  # The text field also sends SEL_COMMAND when the focus moves to another control.
  # TEXTFIELD_ENTER_ONLY can be passed to suppress this feature. Typically, this
  # flag is used in dialogs that close when ENTER is hit in a text field.
  #
  # === Events
  #
  # The following messages are sent from FXTextField to its target:
  #
  # +SEL_COMMAND+::		sent when the user presses the *Enter* key or tabs out of the text field; the message data is a String containing the text.
  # +SEL_CHANGED+::		sent when the text changes; the message data is a String containing the text.
  # +SEL_VERIFY+::		sent when the user attempts to enter new text in the text field; the message data is a String containing the proposed new text.
  # +SEL_KEYPRESS+::		sent when a key goes down; the message data is an FXEvent instance.
  # +SEL_KEYRELEASE+::		sent when a key goes up; the message data is an FXEvent instance.
  # +SEL_LEFTBUTTONPRESS+::	sent when the left mouse button goes down; the message data is an FXEvent instance.
  # +SEL_LEFTBUTTONRELEASE+::	sent when the left mouse button goes up; the message data is an FXEvent instance.
  # +SEL_MIDDLEBUTTONPRESS+::	sent when the middle mouse button goes down; the message data is an FXEvent instance.
  # +SEL_MIDDLEBUTTONRELEASE+::	sent when the middle mouse button goes up; the message data is an FXEvent instance.
  #
  # === Textfield styles
  #
  # +TEXTFIELD_PASSWD+::      Password mode
  # +TEXTFIELD_INTEGER+::     Integer mode
  # +TEXTFIELD_REAL+::        Real mode
  # +TEXTFIELD_READONLY+::    NOT editable
  # +TEXTFIELD_ENTER_ONLY+::  Only callback when enter hit
  # +TEXTFIELD_LIMITED+::     Limit entry to given number of columns
  # +TEXTFIELD_OVERSTRIKE+::  Overstrike mode
  # +TEXTFIELD_NORMAL+::      <tt>FRAME_SUNKEN|FRAME_THICK</tt>
  #
  # === Message identifiers
  #
  # +ID_CURSOR_HOME+::
  # +ID_CURSOR_END+::
  # +ID_CURSOR_RIGHT+::
  # +ID_CURSOR_LEFT+::
  # +ID_MARK+::
  # +ID_EXTEND+::
  # +ID_SELECT_ALL+::
  # +ID_DESELECT_ALL+::
  # +ID_CUT_SEL+::
  # +ID_COPY_SEL+::
  # +ID_PASTE_SEL+::
  # +ID_DELETE_SEL+::
  # +ID_OVERST_STRING+::
  # +ID_INSERT_STRING+::
  # +ID_BACKSPACE+::
  # +ID_DELETE+::
  # +ID_TOGGLE_EDITABLE+::
  # +ID_TOGGLE_OVERSTRIKE+::
  # +ID_BLINK+::
  #
  class FXTextField < FXFrame

    # Text field editability [Boolean]
    attr_writer		:editable

    # Cursor position [Integer]
    attr_accessor	:cursorPos

    # Anchor position [Integer]
    attr_accessor	:anchorPos

    # Text [String]
    attr_accessor	:text

    # Selected text [String]
    attr_accessor	:selectedText

    # Text font [FXFont]
    attr_accessor	:font

    # Text color [FXColor]
    attr_accessor	:textColor

    # Background color for selected text [FXColor]
    attr_accessor	:selBackColor

    # Foreground color for selected text [FXColor]
    attr_accessor	:selTextColor

    # Default width of this text field, in terms of a number of columns times the width of the numeral '8' [Integer]
    attr_accessor	:numColumns

    # Text justification mode, a combination of horizontal justification (JUSTIFY_LEFT, JUSTIFY_RIGHT, or JUSTIFY_CENTER_X), and vertical justification (JUSTIFY_TOP, JUSTIFY_BOTTOM, JUSTIFY_CENTER_Y) [Integer]
    attr_accessor	:justify

    # Status line help text [String]
    attr_accessor	:helpText

    # Tool tip message [String]
    attr_accessor	:tipText

    # Text style [Integer]
    attr_accessor	:textStyle

    #
    # Return an initialized FXTextField instance.
    # It should be wide enough to display _ncols_ columns.
    #
    # ==== Parameters:
    #
    # +p+::	the parent window for this text field [FXComposite]
    # +ncols+::	number of visible items [Integer]
    # +target+::	the message target, if any, for this text field [FXObject]
    # +selector+::	the message identifier for this text field [Integer]
    # +opts+::	text field options [Integer]
    # +x+::	initial x-position [Integer]
    # +y+::	initial y-position [Integer]
    # +width+::	initial width [Integer]
    # +height+::	initial height [Integer]
    # +padLeft+::	internal padding on the left side, in pixels [Integer]
    # +padRight+::	internal padding on the right side, in pixels [Integer]
    # +padTop+::	internal padding on the top side, in pixels [Integer]
    # +padBottom+::	internal padding on the bottom side, in pixels [Integer]
    #
    def initialize(p, ncols, target=nil, selector=0, opts=TEXTFIELD_NORMAL, x=0, y=0, width=0, height=0, padLeft=DEFAULT_PAD, padRight=DEFAULT_PAD, padTop=DEFAULT_PAD, padBottom=DEFAULT_PAD) # :yields: theTextField
    end

    #
    # Set the text for this field to _text_.
    # If _notify_ is +true+, a +SEL_COMMAND+ message is sent to the text field's target after the text is changed.
    #
    def setText(text, notify=false); end

    #
    # Replace range of bytes with text.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is replaced.
    #
    def replaceText(pos, m, text, notify=false); end

    #
    # Append _text_ to the end of the text buffer.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is appended.
    #
    def appendText(text, notify=false); end

    #
    # Insert _text_ at position _pos_.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is inserted.
    #
    def insertText(pos, text, notify=false); end

    #
    # Remove _m_ characters starting at position _pos_.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is removed.
    #
    def removeText(pos, m, notify=false); end

    # Select all text
    def selectAll(); end

    # Select _len_ characters starting at given position _pos_.
    def setSelection(pos, len) ; end

    # Extend the selection from the anchor to the given position _pos_.
    def extendSelection(pos) ; end

    #
    # Copy the primary selection to the clipboard, using the stringType, textType, utf8Type and utf16Type drag types.
    # Returns +false+ if there is no text selected, or if the text field can't acquire the clipboard; otherwise
    # returns +true+.
    #
    def copySelection(); end

    #
    # Copy the selected text to the clipboard and then delete it.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is removed.
    # Returns +false+ if there is no text selected, or if the text field can't acquire the clipboard; otherwise
    # returns +true+.
    #
    def cutSelection(notify=false); end

    #
    # Delete the selected text (without first copying it to the clipboard).
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is removed.
    # Returns +false+ if there is no text selected, otherwise returns +true+.
    #
    def deleteSelection(notify=false); end

    #
    # Replace the currently selected text with _text_.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is replaced.
    # Returns +false+ if there is no text selected, otherwise returns +true+.
    #
    def replaceSelection(text, notify=false); end

    #
    # Paste the selected text (the primary selection) into the text field.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is replaced.
    # Returns +false+ if we can't get the primary selection in a suitable text format, otherwise returns +true+.
    #
    def pasteSelection(notify=false); end

    #
    # Paste the clipboard contents into the text field.
    # If _notify_ is +true+, a +SEL_CHANGED+ message is sent to the text field's target after the text is replaced.
    # Returns +false+ if we can't get the clipboard contents in a suitable text format, otherwise returns +true+.
    #
    def pasteClipboard(notify=false); end

    # Unselect the text
    def killSelection() ; end

    # Return +true+ if position _pos_ is selected.
    def posSelected?(pos) ; end

    # Return +true+ if position _pos_ is fully visible.
    def posVisible?(pos) ; end

    # Scroll text to make the given position _pos_ visible.
    def makePositionVisible(pos) ; end

    # Return +true+ if text field may be edited
    def editable?() ; end

    # Set overstrike mode to +true+ or +false+.
    def overstrike=(os); end

    # Return +true+ if overstrike mode is set.
    def overstrike?; end
  end
end
