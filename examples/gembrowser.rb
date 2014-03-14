require 'fox16'

include Fox

class GemBrowser

  #
  # A reference to the currently selected Gem specification, or +nil+
  # if none is selected.
  #
  attr_accessor :currentSpec

  def initialize
    @currentSpec = nil
  end

  #
  # Install the Gem described by the named spec file, and return the
  # Specification for this Gem.
  #
  def install(filename)
    Gem::Installer.new(filename).install
    spec = nil
    cache.each do |n, s|
      spec = s if (File.basename(filename, ".gem") == s.full_name)
    end
    spec
  end

  #
  # Uninstall the Gem described by this specification.
  #
  def uninstall(spec)
    Gem::Uninstaller.new(spec.name).uninstall
  end

  # Return an array of the installed specifications.
  def cache
#   Gem.cache
    Gem::SourceIndex.from_installed_gems
  end
end

class GemInfoPanel < FXVerticalFrame

  attr_reader :browser

  def initialize(p, b, opts)
    # Initialize base class
    super(p, opts)

    @browser = b

    self.backColor = FXRGB(255, 255, 255)

    File.open(File.expand_path("../icons/gem_big.png", __FILE__), "rb") do |f|
      @bigIcon = FXPNGIcon.new(getApp(), f.read)
    end

    nameLabel = FXLabel.new(self, "", @bigIcon, JUSTIFY_LEFT|JUSTIFY_TOP|ICON_BEFORE_TEXT|LAYOUT_FILL_X)
    nameLabel.backColor = FXRGB(255, 255, 255)
    nameLabel.connect(SEL_UPDATE) { |nameLabel, sel, ptr|
      if currentSpec
	nameLabel.text = specDescription(currentSpec)
	nameLabel.show
      else
	nameLabel.text = ""
	nameLabel.hide
      end
    }

    summaryText = FXText.new(self, nil, 0, TEXT_READONLY|TEXT_WORDWRAP|LAYOUT_FILL_X|LAYOUT_FILL_Y)
    summaryText.backColor = FXRGB(255, 255, 255)
    summaryText.connect(SEL_UPDATE) { |summaryText, sel, ptr|
      theText = currentSpec ? currentSpec.summary : nil
      summaryText.text = theText unless (summaryText.text == theText)
    }
  end

  #
  # Return a reference to the currently selected Gem specification,
  # or +nil+ if none is selected.
  #
  def currentSpec
    browser.currentSpec
  end

  # Return a multiline string (suitable for use with an FXLabel) describing this spec.
  def specDescription(spec)
    [spec.name, "version #{spec.version}", spec.author, spec.email, spec.homepage].join("\n")
  end

  def create
    super
    @bigIcon.create
  end
end

class GemsPanel < FXVerticalFrame

  attr_reader :browser

  def initialize(p, br, opts)
    # Initialize base class
    super(p, opts)

    # Save a reference to the browser
    @browser = br

    File.open(File.expand_path("../icons/gem_big.png", __FILE__), "rb") do |f|
      @bigIcon = FXPNGIcon.new(getApp(), f.read)
    end
    File.open(File.expand_path("../icons/gem_small.png", __FILE__), "rb") do |f|
      @smallIcon = FXPNGIcon.new(getApp(), f.read)
    end

    @iconList = FXIconList.new(self, nil, 0, LAYOUT_FILL_X|LAYOUT_FILL_Y|ICONLIST_MINI_ICONS|ICONLIST_BROWSESELECT)
    @iconList.connect(SEL_SELECTED) { |sender, sel, ptr|
      browser.currentSpec = itemSpec(ptr)
    }

    # Fill the list with installed specifications.
    browser.cache.each { |name, spec| appendItem(spec) }
    if numItems > 0
      selectItem(0)
      browser.currentSpec = itemSpec(0)
    end
  end

  def appendItem(spec)
    @iconList.appendItem(spec.name, @bigIcon, @smallIcon, spec)
    if numItems == 1
      selectItem(0)
      browser.currentSpec = itemSpec(0)
    end
  end

  def currentItem
    @iconList.currentItem
  end

  #
  # Return the specification associated with the item at _index_, or
  # +nil+ if no such item.
  #
  def itemSpec(index)
    (index >= 0) ? getItem(index).data : nil
  end

  def currentItemSpec
    itemSpec(currentItem)
  end

  def getItem(*args)
    @iconList.getItem(*args)
  end

  def selectItem(index)
    @iconList.selectItem(index, true)
  end

  def numItems
    @iconList.numItems
  end

  def create
    super
    @bigIcon.create
    @smallIcon.create
    self.width = @iconList.font.getTextWidth("MMMMMMMMMMMMM")
  end
end

class GemBrowserWindow < FXMainWindow

  attr_reader :browser

  def initialize(anApp)
    # Initialize base class first
    super(anApp, "Gem Browser", nil, nil, DECOR_ALL)

    # Menu bar
    menubar = FXMenuBar.new(self, LAYOUT_SIDE_TOP|LAYOUT_FILL_X)

    # File menu
    filemenu = FXMenuPane.new(self)
    FXMenuTitle.new(menubar, "&File", nil, filemenu)

    installCmd = FXMenuCommand.new(filemenu, "Install a Gem...")
    installCmd.connect(SEL_COMMAND) { install }

    uninstallCmd = FXMenuCommand.new(filemenu, "Uninstall this Gem")
    uninstallCmd.connect(SEL_COMMAND) { uninstall }
    uninstallCmd.connect(SEL_UPDATE) do |sender, sel, ptr|
      spec = browser.currentSpec
      if spec
        sender.text = "Uninstall #{spec.name}"
        sender.enable
      else
        sender.text  = "Uninstall this Gem"
        sender.disable
      end
    end

    FXMenuCommand.new(filemenu, "&Quit\tCtl-Q").connect(SEL_COMMAND) { quit }

    # Main window interior
    contents = FXVerticalFrame.new(self, LAYOUT_FILL_X|LAYOUT_FILL_Y)

    @browser = GemBrowser.new

    # Horizontal splitter with info pane on the left, icon list on the right
    @splitter = FXSplitter.new(contents, LAYOUT_FILL_X|LAYOUT_FILL_Y|SPLITTER_HORIZONTAL|SPLITTER_REVERSED) do |splitter|
      infoPanel = GemInfoPanel.new(splitter, @browser, LAYOUT_FILL_X|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK)
      @gemsPanel = GemsPanel.new(splitter, @browser, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN|FRAME_THICK)
    end

    # Catch these too
    self.connect(SEL_CLOSE) { quit }
    anApp.addSignal("SIGINT") { quit }
  end

  def install
    FXFileDialog.new(self, "Install Gem") { |dlg|
      dlg.directory = @directory unless @directory.empty?
      dlg.patternList = ["Gem Files (*.gem)", "All Files (*)"]
      if dlg.execute != 0
        @directory = dlg.directory
        begin
          spec = browser.install(dlg.filename)
	  @gemsPanel.appendItem(spec)
	rescue => ex
	  FXMessageBox.error(self, MBOX_OK, "Installation Failed", ex.to_s)
	end
      end
    }
  end

  def uninstall
    begin
      browser.uninstall(browser.currentSpec)
    rescue => ex
      FXMessageBox.error(self, MBOX_OK, "Uninstall Failed", ex.to_s)
    end
  end

  def quit
    getApp().reg().writeIntEntry("SETTINGS", "x", x)
    getApp().reg().writeIntEntry("SETTINGS", "y", y)
    getApp().reg().writeIntEntry("SETTINGS", "width", width)
    getApp().reg().writeIntEntry("SETTINGS", "height", height)
    getApp().reg().writeIntEntry("SETTINGS", "listWidth", @splitter.first.next.width)
    getApp().reg().writeStringEntry("SETTINGS", "directory", @directory) if @directory
    getApp().exit(0)
  end

  def create
    # Do base class create
    super

    # Get size, etc. from registry
    xx = getApp().reg().readIntEntry("SETTINGS", "x", 0)
    yy = getApp().reg().readIntEntry("SETTINGS", "y", 0)
    ww = getApp().reg().readIntEntry("SETTINGS", "width", 450)
    hh = getApp().reg().readIntEntry("SETTINGS", "height", 300)
    position(xx, yy, ww, hh)

    # Splitter child sizes
    rightPaneSize = getApp().reg().readIntEntry("SETTINGS", "listWidth", -1)
    if rightPaneSize >= 0
      @splitter.first.next.width = rightPaneSize
    end

    # Last directory for Gem files
    @directory = getApp().reg().readStringEntry("SETTINGS", "directory", "")

    # Show it
    show
  end
end

if __FILE__ == $0
  FXApp.new("GemBrowser", "FXRuby") do |theApp|
    GemBrowserWindow.new(theApp)
    theApp.create
    theApp.run
  end
end

