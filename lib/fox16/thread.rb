require 'thread'

module Fox

  class FXApp

    alias initialize_before_thread initialize # :nodoc:

    def initialize(*args, &block)
      initialize_before_thread(*args)
      event_handler_setup
      block.call(self) if block_given?
    end

    def runOnUiThread(&block)
      @event_handler_events << block
      @event_handler_pwr.write 'e'
    end

    private

    def event_handler_setup
      if RUBY_PLATFORM =~ /mingw|mswin/i
        require 'socket'
        gs = TCPServer.open('localhost', 0)
        prd = TCPSocket.open('localhost', gs.addr[1])
        pwr = gs.accept
        gs.close
      else
        prd, pwr = IO.pipe
      end
      self.addInput(prd, Fox::INPUT_READ){ event_handler_pull(prd) }
      @event_handler_pwr = pwr
      @event_handler_events = Queue.new
    end

    def event_handler_pull(prd)
      prd.read(1)
      while !@event_handler_events.empty?
        ev = @event_handler_events.shift
        ev.call
      end
    end

  end # class FXApp

  class FXId
    def runOnUiThread(&block)
      app.runOnUiThread(&block)
    end
  end
end # module Fox
