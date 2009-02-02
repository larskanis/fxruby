module Fox
  #
  # A Picker button allows you to identify an arbitrary location on the screen.
  # It generates +SEL_CHANGED+ callbacks while the user is moving the mouse, and
  # a final +SEL_COMMAND+ when a location has been identified. The message data
  # in the callback is a reference to an FXPoint instance which indicates the location,
  # in root-coordinates, of the place where the click took place.
  #
  # === Events
  #
  # The following messages are sent by FXPicker to its target:
  #
  # +SEL_CHANGED+::
  #   sent continuously while the position is changing; the message data is an
  #   FXPoint instance indicating the current root window position of the mouse
  #   pointer.
  # +SEL_COMMAND+::
  #   sent when the left mouse button is clicked the second time (i.e. to
  #   "pick" a position); the message data is an FXPoint instance indicating
  #   the picked position in root window coordinates.
  #
  class FXPicker < FXButton
    #
    # Returns an initialized FXPicker instance.
    #
    # ==== Parameters:
    #
    # +p+::          the parent widget for this picker [FXComposite]
    # +text+::       the text [String]
    # +ic+::         the icon [FXIcon]
    # +target+::     the message target [FXObject]
    # +selector+::   the selector [Integer]
    # +opts+::       options [Integer]
    # +x+::          initial x-position [Integer]
    # +y+::          initial y-position [Integer]
    # +width+::      initial width [Integer]
    # +height+::     initial height [Integer]
    # +padLeft+::    left padding in pixels [Integer]
    # +padRight+::   right padding in pixels [Integer]
    # +padTop+::     top padding in pixels [Integer]
    # +padBottom+::  bottom padding in pixels [Integer]
    #
    def initialize(p, text, ic=nil, target=nil, selector=0, opts=BUTTON_NORMAL, x=0, y=0, width=0, height=0, padLeft=DEFAULT_PAD, padRight=DEFAULT_PAD, padTop=DEFAULT_PAD, padBottom=DEFAULT_PAD) # :yields: thePicker
    end
  end
end

