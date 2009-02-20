module Fox
  class FXAccelTable
    alias addAccelOrig addAccel # :nodoc:
    
    #
    # Add an accelerator to the table. The _hotKey_ is a code returned
    # by the Fox.fxparseAccel method. For example, to associate the
    # Ctrl+S keypress with sending a "save" command to a document, you
    # might use code like this:
    #
    #   hotKey = fxparseAccel("Ctrl+S")
    #   accelTable.addAccel(hotKey, doc, FXSEL(SEL_COMMAND, MyDocument::ID_SAVE))
    #
    # A more straightforward way is to pass one or more callable objects in:
    #
    #   accelTable.addAccel(hotKey, lambda { doc.save })
    #
    # or to trigger the event on the key "up" event,
    #
    #   accelTable.addAccel(hotKey, nil, lambda { doc.save })
    #
    def addAccel(hotKey, *args)
      tgt, seldn, selup = nil, 0, 0
      if args.length > 0
        if args[0].respond_to? :call
          tgt = FXPseudoTarget.new
          seldn = FXSEL(SEL_KEYPRESS, 0)
          tgt.pconnect(SEL_KEYPRESS, args[0])
        else
          tgt = args[0]
        end
        if args.length > 1
          if args[1].respond_to? :call
            tgt = tgt || FXPseudoTarget.new
            selup = FXSEL(SEL_KEYRELEASE, 0)
            tgt.pconnect(SEL_KEYRELEASE, args[1])
          else
            seldn = args[1]
            selup = args[2] if args.length > 2
          end
        end
      end
      addAccelOrig(hotKey, tgt, seldn, selup)
    end
  end
end