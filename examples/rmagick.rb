require 'fox16'
begin
  require 'rmagick'
rescue LoadError
  warn("LoadError: To execute this app you need to have 'rmagick' gem installed.")
  sleep(5)
  exit(false)
end

include Fox

class RMagickExample < FXMainWindow

  def initialize(app)
    super(app, "RMagick Example", :width => 800, :height => 600)

    # Construct an ImageList
    dippy = Magick::ImageList.new(File.expand_path("icons/dippy.png", __dir__))

    # Manipulate the image
    text = Magick::Draw.new
    text.annotate(dippy, 0, 0, 0, 60, "Dippy Duck") do |a|
      a.gravity = Magick::SouthGravity
      a.pointsize = 24
      a.stroke = 'transparent'
      a.fill = '#80C0A9'
      a.font_weight = Magick::BoldWeight
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
