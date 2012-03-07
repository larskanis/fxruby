module Fox
  #
  # The accelerator table sends a message to a specific
  # target object when the indicated key and modifier combination
  # is pressed.
  #
  class FXAccelTable < FXObject
    #
    # Construct empty accelerator table.
    #
    def initialize # :yields: acceleratorTable
    end

    #
    # Remove an accelerator from the table.
    #
    def removeAccel(hotKey) ; end

    #
    # Return +true+ if accelerator specified.
    # Here, _hotKey_ is a code representing an accelerator key as returned
    # by the Fox.fxparseAccel method. For example,
    #
    #   if accelTable.hasAccel?(fxparseAccel("Ctrl+S"))
    #     ...
    #   end
    #
    def hasAccel?(hotKey) ; end

    #
    # Return the target object of the given accelerator, or +nil+ if
    # the accelerator is not present in this accelerator table.
    # Here, _hotKey_ is a code representing an accelerator key as returned
    # by the Fox.fxparseAccel method. For example,
    #
    #   doc = accelTable.targetofAccel(fxparseAccel("Ctrl+S"))
    #
    def targetOfAccel(hotKey) ; end

    #
    # Remove mapping for specified hot key.
    # Here, _hotKey_ is a code representing an accelerator key as returned
    # by the Fox.fxparseAccel method. For example,
    #
    #   accelTable.removeAccel(fxparseAccel("Ctrl+S"))
    #
    def removeAccel(hotKey) ; end
  end

  #
  # Parse accelerator from string, yielding modifier and
  # key code.  For example, parseAccel("Ctl+Shift+X")
  # yields MKUINT(KEY_X,CONTROLMASK|SHIFTMASK).
  #
  def parseAccel(string); end

  #
  # Unparse hot key comprising modifier and key code back
  # into a string suitable for parsing with {#parseHotKey}.
  #
  def unparseAccel(key); end

  #
  # Parse hot key from string, yielding modifier and
  # key code.  For example, parseHotKey(""Salt && &Pepper!"")
  # yields MKUINT(KEY_p,ALTMASK).
  #
  def parseHotKey(string); end

  #
  # Obtain hot key offset in string, or -1 if not found.
  # For example, findHotKey("Salt && &Pepper!") yields 7.
  # Note that this is the byte-offset, not the character
  # index!
  #
  def findHotKey(string); end

  #
  # Strip hot key combination from the string.
  # For example, stripHotKey("Salt && &Pepper") should
  # yield "Salt & Pepper".
  #
  def stripHotKey(string); end
end
