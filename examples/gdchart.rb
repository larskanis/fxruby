require 'fox16'
require 'tempfile'
begin
  require 'GDChart'
rescue LoadError
  require 'fox16/missingdep'
  MSG = <<EOM
  Sorry, this example depends on the GDChart extension. Please
  check the Ruby Application Archives for an appropriate
  download site.
EOM
  missingDependency(MSG)
end

include Fox

class GDChartViewer < FXMainWindow
  def initialize(app)
    # Invoke base class initialize first
    super(app, "GDChart Viewer", :opts => DECOR_ALL, :width => 850, :height => 600)

    # Sunken border for image widget
    imagebox = FXHorizontalFrame.new(self,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y)

    # Make image widget
    @imageview = FXImageView.new(imagebox,
      :opts => LAYOUT_FILL_X|LAYOUT_FILL_Y|HSCROLLER_NEVER|VSCROLLER_NEVER)

    # Construct a PNG image and store it in the image viewer
    @imageview.image = createChart

    # Resize main window client area to fit image size
    resize(@imageview.contentWidth, @imageview.contentHeight)
  end

  def createChart
    # Create a simple chart
    GDChart.title = "A Chart"
    GDChart.xtitle = "X-axis"
    GDChart.ytitle = "Y-axis"
    data = [1, 2, 3, 4, 5, 6]
    labels = ["label 1", "label 2", "label 3", "label 4", "label 5", "label 6"]

    # Write chart data out as GIF to a temporary file
    File.open('gdchart.gif', 'w') do |f|
      GDChart.out_graph(200, 200, f, GDChart::LINE, labels.length, labels, 1, data)
    end

    # Reopen it and construct image
    img = nil
    File.open('gdchart.gif', 'rb') do |f|
      img = FXGIFIcon.new(getApp(), f.read)
    end
    img
  end

  def create
    super
    show(PLACEMENT_SCREEN)
  end
end

if __FILE__ == $0
  # Make application
  application = FXApp.new("GDChart Viewer", "FoxTest")

  # Make window
  window = GDChartViewer.new(application)

  # Create it
  application.create

  # Run
  application.run
end
