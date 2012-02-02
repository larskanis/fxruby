module Fox

  class FXApp

    alias addTimeoutOrig	addTimeout # :nodoc:
    alias addDeadlineOrig	addDeadline # :nodoc:
    alias removeTimeoutOrig	removeTimeout # :nodoc:
    alias hasTimeoutOrig?	hasTimeout? # :nodoc:
    alias remainingTimeoutOrig	remainingTimeout # :nodoc:

    #
    # Add a timeout message to be sent to target object in _ms_ milliseconds.
    # By default, the timer fires only once after the interval expires.  The last argument
    # is optional user data which will be passed along as the _ptr_ argument of
    # the message handler. If a timer with the same target and message already exists,
    # it will be rescheduled.
    #
    # There are several forms for #addTimeout; the original form (from FOX)
    # takes three arguments:
    #
    #     timeout = app.addTimeout(delay, tgt, sel)
    #
    # Here, _delay_ is the time interval (in milliseconds) to wait
    # before firing this timeout. The second and third arguments are the
    # target object and message identifier for the message to be sent when
    # this timeout fires.
    #
    # A second form of #addTimeout takes a Method instance as its single argument:
    #
    #     timeout = app.addTimeout(delay, mthd)
    #
    # For this form, the method should have the standard argument list
    # for a FOX message handler. That is, the method should take three
    # arguments, for the message _sender_ (an FXObject), the message _selector_,
    # and the message _data_ (if any).
    #
    # The last form of #addTimeout takes a block:
    #
    #     timeout = app.addTimeout(delay) do |sender, sel, data|
    #         ... handle the timeout ...
    #     end
    #
    # All of these return a reference to an opaque object (actually, a hash) that
    # can be passed to #removeTimeout if it is necessary to remove the timeout
    # before it fires.
    #
    # For the last two forms, you can pass in the optional +:repeat+ parameter to
    # cause the timeout to be re-registered after it fires, e.g.
    #
    #     timeout = app.addTimeout(delay, :repeat => true) do |sender, sel, data|
    #         ... handle the timeout ...
    #         ... re-add the timeout with the same delay ...
    #     end
    #
    def addTimeout(ms, *args, &block)
      params = {}
      params = args.pop if args.last.is_a? Hash
      params[:delay] = ms
      tgt, sel = nil, 0
      if args.length > 0
        if args[0].respond_to? :call
          tgt = params[:target] || FXPseudoTarget.new
          tgt.pconnect(SEL_TIMEOUT, args[0], params)
        else # it's some other kind of object
          tgt = args[0]
          sel = args[1]
        end
      else
        tgt = params[:target] || FXPseudoTarget.new
        tgt.pconnect(SEL_TIMEOUT, block, params)
      end
      ns = 1000*ms # FOX expects timeout value in nanoseconds
      addTimeoutOrig(tgt, sel, ns)
      params[:target] = tgt
      params[:selector] = sel
      params
    end

    #
    # Add deadline timeout message to be sent when the _due_ time is reached. This is the preferred way to schedule regularly
    # occuring events, as the exact time of issue will not suffer increasing errors as with the
    # addTimeout() method. However, it is important to ensure that the due time is sufficiently far
    # into the future, as otherwise the system may be swamped executing nothing but timeout messages.
    #
    # There are several forms for #addDeadline; the original form takes three arguments:
    #
    #     timeout = app.addDeadline(due, tgt, sel)
    #
    # Here, _due_ is the due time (a Time instance) for this timeout. The second and third arguments are the
    # target object and message identifier for the message to be sent when this deadline is reached.
    #
    # A second form of #addDeadline takes a Method instance as its single argument:
    #
    #     timeout = app.addDeadline(due, mthd)
    #
    # For this form, the method should have the standard argument list
    # for a FOX message handler. That is, the method should take three
    # arguments, for the message _sender_ (an FXObject), the message _selector_,
    # and the message _data_ (if any).
    #
    # The last form of #addDeadline takes a block:
    #
    #     timeout = app.addDeadline(due) do |sender, sel, data|
    #         ... handle the timeout ...
    #     end
    #
    # All of these return a reference to an opaque object (actually, a hash) that
    # can be passed to #removeTimeout if it is necessary to remove the timeout
    # before it fires.
    #
    def addDeadline(due, *args, &block)
      raise ArgumentError, "due time should be a Time instance" unless due.is_a? Time
      params = {}
      params = args.pop if args.last.is_a? Hash
      params[:due] = due
      tgt, sel = nil, 0
      if args.length > 0
        if args[0].respond_to? :call
          tgt = params[:target] || FXPseudoTarget.new
          tgt.pconnect(SEL_TIMEOUT, args[0], params)
        else # it's some other kind of object
          tgt = args[0]
          sel = args[1]
        end
      else
        tgt = params[:target] || FXPseudoTarget.new
        tgt.pconnect(SEL_TIMEOUT, block, params)
      end
      addDeadlineOrig(tgt, sel, due.to_f*1000000000) # convert seconds to nanoseconds
      params[:target] = tgt
      params[:selector] = sel
      params
    end

    #
    # Remove timeout previously registered using #addDeadline or #addTimeout; returns +nil+.
    # For an example of how to use #removeTimeout, see the documentation for
    # the #hasTimeout? method.
    #
    def removeTimeout(*args)
      if args.length == 2
        removeTimeoutOrig(args[0], args[1])
      else
        params = args[0]
        removeTimeoutOrig(params[:target], params[:selector])
      end
    end

    #
    # Return +true+ if given timeout has been set, otherwise return +false+.
    #
    # For example, suppose you set up a timeout event to run ten seconds from
    # now:
    #
    #     timeout = app.addTimeout(10*1000, ...)
    #
    # but in the meantime, you decide that you want to cancel it if it hasn't
    # run yet:
    #
    #     if app.hasTimeout?(timeout)
    #       app.removeTimeout(timeout)
    #     end
    #
    def hasTimeout?(*args)
      if args.length == 2
        hasTimeoutOrig?(args[0], args[1])
      else
        hsh = args[0]
        hasTimeoutOrig?(hsh[:target], hsh[:selector])
      end
    end

    #
    # Return the time remaining (in milliseconds) until the given timer fires.
    # If the timer is past due, zero is returned. If there is no such
    # timer, infinity (UINT_MAX) is returned.
    #
    # For example:
    #
    #     timeout = app.addTimeout(ms, ...)
    #     time_left = app.remainingTimeout(timeout)
    #
    def remainingTimeout(*args)
      ns  = nil
      if args.length == 2
        ns = remainingTimeoutOrig(args[0], args[1])
      else
        hsh = args[0]
        ns = remainingTimeoutOrig(hsh[:target], hsh[:selector])
      end
      ms = ns/1000 # FOX returns the time in nanoseconds
    end

  end # class FXApp

end # module Fox
