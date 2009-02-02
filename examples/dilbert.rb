#!/usr/bin/env ruby

require 'fox16'
require 'fox16/kwargs'
require 'open-uri'
begin
  require 'rubyful_soup'
rescue LoadError
  require 'fox16/missingdep'
  MSG = <<EOM
  Sorry, this example depends on the RubyfulSoup extension. Please
  check the Ruby Application Archives for an appropriate
  download site.
EOM
  missingDependency(MSG)
end

include Fox

class DailyDilbert < FXMainWindow

 include Responder

  def initialize(app)
    # Invoke base class initialize first
    super(app, "Daily Dilbert Viewer", :opts => DECOR_ALL, :width => 850, :height => 600, :padLeft => 0, :padRight => 0)

    # Sunken border for image widget
    imagebox = FXHorizontalFrame.new(self,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y)
  
    # Make image widget
    @imageview = FXImageView.new(imagebox,
      :opts => LAYOUT_FILL_X|LAYOUT_FILL_Y|HSCROLLER_NEVER|VSCROLLER_NEVER)
      
    # Construct a GIF image and store it in the image viewer
    @imageview.image = FXGIFImage.new(getApp(), image_data)

    # Resize main window client area to fit image size
    resize(@imageview.contentWidth, @imageview.contentHeight)
  end
  
  def image_data
    src = open("http://www.dilbert.com/").read
    soup = BeautifulSoup.new(src)
    url = soup.find('img', { :attrs => { 'alt' => /Today's Comic/ } })
    open("http://www.dilbert.com" + url['src'], "rb").read
  end
  
  def create
    super
    show(PLACEMENT_SCREEN)
  end
end

if __FILE__ == $0
  # Make application
  application = FXApp.new("DailyDilbert", "FoxTest")

  # Make window
  window = DailyDilbert.new(application)

  # Create it
  application.create

  # Run
  application.run
end
