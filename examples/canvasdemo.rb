require 'fox16'
require 'fox16/canvas'

include Fox
include Canvas

class CanvasDemo < FXMainWindow
  def initialize(app)
    # Initialize base class first
    super(app, "Canvas Demo", nil, nil, DECOR_ALL, 0, 0, 800, 600)

    # Menu bar
    menu_bar = FXMenuBar.new(self, LAYOUT_SIDE_TOP|LAYOUT_FILL_X)

    # File menu
    file_menu = FXMenuPane.new(self)
    FXMenuCommand.new(file_menu, "&New...")
    FXMenuCommand.new(file_menu, "&Open...")
    FXMenuCommand.new(file_menu, "&Close")
    FXMenuCommand.new(file_menu, "&Save")
    FXMenuCommand.new(file_menu, "Save &As...")
    FXMenuSeparator.new(file_menu)
    FXMenuCommand.new(file_menu, "&Print...")
    FXMenuCommand.new(file_menu, "Print &Setup...")
    FXMenuCommand.new(file_menu, "Print Pre&view")
    FXMenuSeparator.new(file_menu)
    FXMenuCommand.new(file_menu, "E&xit", nil, app, FXApp::ID_QUIT)

    # Edit menu
    edit_menu = FXMenuPane.new(self)
    FXMenuCommand.new(edit_menu, "&Undo")
    FXMenuCommand.new(edit_menu, "&Redo")
    FXMenuSeparator.new(edit_menu)
    FXMenuCommand.new(edit_menu, "&Cut")
    FXMenuSeparator.new(edit_menu)
    FXMenuCommand.new(edit_menu, "Change &background color")
    FXMenuCommand.new(edit_menu, "Edit &label")

    # Recently used files
    @mru_files = FXRecentFiles.new

    # Help menu
    help_menu = FXMenuPane.new(self)
    aboutBox = FXMenuCommand.new(help_menu, "&About...")
    aboutBox.connect(SEL_COMMAND) do |sender, sel, ptr|
      FXMessageBox.information(self, MBOX_OK, "About Canvas",
        "Canvas Demo\nTo draw a shape, select a shape on the toolbar and left-click on the canvas.\nTo draw a line, right-drag between shapes.")
    end

    # Attach menus to menu bar titles
    FXMenuTitle.new(menu_bar, "&File", nil, file_menu)
    FXMenuTitle.new(menu_bar, "&Edit", nil, edit_menu)
    FXMenuTitle.new(menu_bar, "&Help", nil, help_menu)

    # Status bar
    FXStatusBar.new(self,
      LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER)

    # Shapes canvas fills the remainder
    frame = FXHorizontalFrame.new(self,
      LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN|FRAME_THICK,
      0, 0, 0, 0, 0, 0, 0, 0)
    canvas = ShapeCanvas.new(frame, nil, 0, LAYOUT_FILL_X|LAYOUT_FILL_Y)
    canvas.scene = get_scene(canvas)
  end

  def get_scene(canvas)
    scene = ShapeGroup.new
    scene.addShape(CircleShape.new(5, 5, 10))
    scene.addShape(CircleShape.new(50, 50, 20))
    scene.addShape(LineShape.new(10, 10, 70, 70))
    scene.addShape(RectangleShape.new(90, 90, 30, 40))
    scene.addShape(TextShape.new(60, 60, 30, 40, "Hello!"))
    scene
  end

  def create
    super
    show(PLACEMENT_SCREEN)
  end
end

if __FILE__ == $0
  app = FXApp.new("CanvasDemo", "FXRuby")
  CanvasDemo.new(app)
  app.create
  app.run
end
