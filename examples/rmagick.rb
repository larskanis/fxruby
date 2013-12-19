require 'fox16'
begin
  require 'RMagick'
rescue LoadError
  warn("LoadError: To execute this app you need to have 'RMagick' gem installed.")
  sleep(5)
  exit(false)
end

include Fox

class RMagickExample < FXMainWindow

  def initialize(app)
    super(app, "RMagick Example", :width => 800, :height => 600)

    # Construct an ImageList
    dippy = Magick::ImageList.new(File.join("icons", "dippy.png"))

    # Manipulate the image
    text = Magick::Draw.new
    text.annotate(dippy, 0, 0, 0, 60, "Dippy Duck") do
      self.gravity = Magick::SouthGravity
      self.pointsize = 24
      self.stroke = 'transparent'
      self.fill = '#0000A9'
      self.font_weight = Magick::BoldWeight
    end

    # Extract image data and use it to construct FXPNGImage
    dippy_image = FXPNGImage.new(app, dippy.to_blob)

    # Display it inside an FXImageFrame
    FXImageFrame.new(self, dippy_image, :opts => LAYOUT_FILL)
  end

  def create
    super
    show(PLACEMENT_SCREEN)
  end

end

if __FILE__ == $0
  FXApp.new("RMagick Example", "FXRuby") do |app|
    RMagickExample.new(app)
    app.create
    app.run
  end
end
