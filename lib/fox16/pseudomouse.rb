module Fox
  #
  # Based on a suggestion from Hugh Sasse on the fxruby-users mailing list,
  # an FXPseudoMouse object provides a simple means to operate widgets
  # programmatically, to aid test driven design. An FXPseudoMouse instance
  # can be pointed at an FXObject and will manage the sending of events to
  # it.
  #
  class FXPseudoMouse < FXObject

    attr_accessor :target

    def initialize(tgt=nil)
      @target = tgt
    end
    
    def doMotion
      unless @target.nil?
        evt = FXEvent.new
        evt.type = Fox::SEL_MOTION
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_MOTION), evt)
      end
    end

    def doMouseWheel
      unless @target.nil?
        evt = FXEvent.new
        evt.type = Fox::SEL_MOUSEWHEEL
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_MOUSEWHEEL), evt)
      end
    end

    def doLeftButtonPress
      unless @target.nil?
        evt = FXEvent.new
        evt.type = Fox::SEL_LEFTBUTTONPRESS
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_LEFTBUTTONPRESS), evt)
      end
    end

    def doLeftButtonRelease
      unless @target.nil?
       evt = FXEvent.new
        evt.type = Fox::SEL_LEFTBUTTONRELEASE
       @target.handle(self, Fox.MKUINT(0, Fox::SEL_LEFTBUTTONRELEASE), evt)
      end
    end

    def doMiddleButtonPress
      unless @target.nil?
        evt = FXEvent.new
        evt.type = Fox::SEL_MIDDLEBUTTONPRESS
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_MIDDLEBUTTONPRESS), evt)
      end
    end

    def doMiddleButtonRelease
      unless @target.nil?
        evt = FXEvent.new
        evt.type = Fox::SEL_MIDDLEBUTTONRELEASE
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_MIDDLEBUTTONRELEASE), evt)
      end
    end

    def doRightButtonPress
      unless @target.nil?
        evt = FXEvent.new
        evt.type = Fox::SEL_RIGHTBUTTONPRESS
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_RIGHTBUTTONPRESS), evt)
      end
    end

    def doRightButtonRelease
      unless @target.nil?
        evt = FXEvent.new
        evt.type = Fox::SEL_RIGHTBUTTONRELEASE
        @target.handle(self, Fox.MKUINT(0, Fox::SEL_RIGHTBUTTONRELEASE), evt)
      end
    end
  end
end

