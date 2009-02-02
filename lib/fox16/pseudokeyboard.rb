module Fox
  #
  # Based on a suggestion from Hugh Sasse on the fxruby-users mailing list,
  # an FXPseudoKeyboard object provides a simple means to operate widgets
  # programmatically, to aid test driven design. An FXPseudoKeyboard instance
  # can be pointed at an FXObject and will manage the sending of events to
  # it.
  #
  class FXPseudoKeyboard

    attr_accessor :target

    def initialize(tgt=nil)
      @target = tgt
    end
    
    def doKeyPress
      unless @target.nil?
        evt = FXEvent.new
	evt.type = Fox::SEL_KEYPRESS
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_KEYPRESS), evt)
      end
    end

    def doKeyRelease
      unless @target.nil?
        evt = FXEvent.new
	evt.type = Fox::SEL_KEYRELEASE
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_KEYRELEASE), evt)
      end
    end
  end
end

