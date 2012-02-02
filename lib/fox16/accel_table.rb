module Fox
  class FXAccelTable
    alias addAccelOrig addAccel # :nodoc:

    #
    # Add an accelerator to the table. The _hotKey_ is a code returned
    # by the Fox.fxparseAccel method.
    #
    # There are several forms for _addAccel_; the original form (from FOX)
    # takes either three or four arguments. For example, to associate the
    # Ctrl+H keypress with sending the "hide" command to a window, you might
    # use code like this:
    #
    #   hotKey = fxparseAccel("Ctrl+H")
    #   accelTable.addAccel(hotKey, window, FXSEL(SEL_COMMAND, FXWindow::ID_HIDE))
    #
    # If you instead want to trigger the command on the key release (instead of
    # the key press), pass a zero for the third argument and pass the command
    # as the fourth argument:
    #
    #   accelTable.addAccel(hotKey, window, 0, FXSEL(SEL_COMMAND, FXWindow::ID_HIDE))
    #
    # You can even pass in two different messages, corresponding to the key press
    # and key release events for the hot key, although this is less common.
    #
    #   accelTable.addAccel(hotKey, window,
    #     FXSEL(SEL_COMMAND, FXWindow::ID_HIDE),
    #     FXSEL(SEL_COMMAND, FXWindow::ID_SHOW))
    #
    # The problem with this form is that you need to be familiar with the message
    # types and identifiers that different widgets respond to, and this information
    # isn't very well documented. A more straightforward way to use _addAccel_
    # from Ruby code is to instead pass one or more callable objects in as the
    # second and third arguments. For example:
    #
    #   accelTable.addAccel(hotKey, lambda { window.hide })
    #
    # or to trigger the event on the key release event:
    #
    #   accelTable.addAccel(hotKey, nil, lambda { window.hide })
    #
    # Or to handle both the key press and key release events:
    #
    #   accelTable.addAccel(hotKey, lambda { window.hide }, lambda { window.show })
    #
    def addAccel(hotKey, *args)
      tgt, seldn, selup = nil, 0, 0
      if args.length > 0
        if args[0].respond_to? :call
          tgt = FXPseudoTarget.new
          seldn = Fox.FXSEL(SEL_KEYPRESS, 0)
          tgt.pconnect(SEL_KEYPRESS, args[0])
        else
          tgt = args[0]
        end
        if args.length > 1
          if args[1].respond_to? :call
            tgt = tgt || FXPseudoTarget.new
            selup = Fox.FXSEL(SEL_KEYRELEASE, 0)
            tgt.pconnect(SEL_KEYRELEASE, args[1])
          else
            seldn = args[1]
            selup = args[2] if args.length > 2
          end
        end
      end
      # FIXME: The target objects stored in the accelerator table are currently
      # private. Therefore FXRbAccelTable::markfunc() doesn't mark them as used.
      # As a workaround the objects are additionally stored in @targets Hash.
      @targets = {} unless instance_variable_defined?('@targets')
      @targets[hotKey] = tgt
      addAccelOrig(hotKey, tgt, seldn, selup)
    end

    alias removeAccelOrig removeAccel # :nodoc:

    def removeAccel(hotKey)
      @targets = {} unless instance_variable_defined?('@targets')
      @targets.delete(hotKey)
      removeAccelOrig(hotKey)
    end
  end
end
