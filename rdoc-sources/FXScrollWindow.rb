module Fox
  #
  # The ScrollWindow widget manages one single child window and
  # scrolls it when the child is larger than the available area.
  # You can use ScrollWindow when parts of your user interface need to be
  # scrollable, for example when applications may need to run on small screens.
  # ScrollWindow normally contains only one single child window, which could
  # be a VerticalFrame or any other widget.  It will measure this widget using
  # getDefaultWidth() and getDefaultHeight() and place the scrollbars when needed,
  # based on options like  HSCROLLING_ALWAYS, etc., and the options of the child
  # window.
  # ScrollWindow observes some layout hints of its child window: LAYOUT_FIX_WIDTH,
  # LAYOUT_FIX_HEIGHT are observed at all times, while LAYOUT_FILL_X, LAYOUT_LEFT,
  # LAYOUT_RIGHT, LAYOUT_CENTER_X, as well as LAYOUT_FILL_Y, LAYOUT_TOP, LAYOUT_BOTTOM,
  # LAYOUT_CENTER_Y are only observed if the child window size is smaller than the
  # ScrollWindow's viewport size.  If the content size is larger than the viewport size,
  # the content must be scrolled normally.
  # Note that this means that the child window's position is not necessarily equal to
  # the scroll position of the scroll window!
  #
  class FXScrollWindow < FXScrollArea
    #
    # Return an initialized FXScrollWindow instance.
    #
    # ==== Parameters:
    #
    # +p+::	the parent window for this scroll window [FXComposite]
    # +opts+::	the options [Integer]
    # +x+::	initial x-position, when the +LAYOUT_FIX_X+ layout hint is in effect [Integer]
    # +y+::	initial y-position, when the +LAYOUT_FIX_Y+ layout hint is in effect [Integer]
    # +width+::	initial width, when the +LAYOUT_FIX_WIDTH+ layout hint is in effect [Integer]
    # +height+::	initial height, when the +LAYOUT_FIX_HEIGHT+ layout hint is in effect [Integer]
    #
    def initialize(p, opts=0, x=0, y=0, width=0, height=0) # :yields: theScrollWindow
    end
  
    #
    # Return a reference to the contents window (an FXWindow instance).
    #
    def contentWindow; end
  end
end

