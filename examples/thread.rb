#!/usr/bin/env ruby

require 'fox16'

class ThreadedWindow < Fox::FXMainWindow
  include Fox

  def initialize(app)
    # Call the base class initializer first
    super(app, "Threaded Widget Test", :opts => DECOR_ALL, width: 200, height: 500)

    @vframe = FXVerticalFrame.new(self,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL, :padding => 0) do |frame|
      FXButton.new(frame, "Click to add", opts: FRAME_RAISED|FRAME_THICK|LAYOUT_FILL_X) do |button|
        button.connect(SEL_COMMAND, method(:on_button_clicked))
      end
    end
  end

  def on_button_clicked(sender, sel, ptr)
    FXHorizontalFrame.new(@vframe,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL, :padding => 10) do |frame|

      label = FXLabel.new frame, "..."

      Thread.new do
        50.times do |seconds|
          runOnUiThread do
            label.text = "#{(50 - seconds)/10.0} seconds to remove"
          end
          sleep 0.1
        end

        runOnUiThread do
          @vframe.removeChild(frame)
          @vframe.create; @vframe.show; @vframe.recalc
        end
      end
    end
    @vframe.create; @vframe.show; @vframe.recalc
  end

  # Create and show this window
  def create
    super
    show(PLACEMENT_SCREEN)
  end
end

if __FILE__ == $0
  application = Fox::FXApp.new("ThreadApp", "FoxTest")
  ThreadedWindow.new(application)
  application.create
  application.run
end
