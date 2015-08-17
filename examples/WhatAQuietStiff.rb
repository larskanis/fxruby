#!/usr/bin/env ruby

#
# Depends on Kou's RSS Parser module (http://raa.ruby-lang.org/list.rhtml?name=rss).
#
# Potential enhancements:
#
# - preference of whether the pictures are listed latest first, or
#   oldest first.
# - option to always show the latest picture after a refresh
#

require 'fox16'
require 'open-uri'

begin
  require 'rss/parser'
  require 'rss/2.0'
rescue LoadError
  require 'fox16/missingdep'
  MSG = <<EOM
  Sorry, this example depends on the RSS extension. Please
  check the Ruby Application Archives for an appropriate
  download site.
EOM
  missingDependency(MSG)
end

include Fox

class WhatAQuietWindow < FXMainWindow

  RSS_FEED_URL          = "http://whytheluckystiff.net/quiet/quiet.xml"
  DEFAULT_REFRESH_DELAY = 60 # in minutes

  def initialize(app)
    # Invoke base class initialize first
    super(app, "What a Quiet Stiff", :opts => DECOR_ALL, :width => 850, :height => 600, :padLeft => 0, :padRight => 0)

    # Icons for list items
    File.open(File.expand_path("../icons/bluebullet14x14.gif", __FILE__), "rb") do |f|
      bytes = f.read
      @itemIcon = FXGIFIcon.new(getApp(), bytes)
    end
    File.open(File.expand_path("../icons/transpbullet14x14.gif", __FILE__), "rb") do |f|
      bytes = f.read
      @transpIcon = FXGIFIcon.new(getApp(), bytes)
    end

    # Menubar
    menuBar = FXMenuBar.new(self, LAYOUT_SIDE_TOP|LAYOUT_FILL_X)

    # File menu
    fileMenu = FXMenuPane.new(self)
    saveCmd = FXMenuCommand.new(fileMenu, "Save selected image...")
    saveCmd.connect(SEL_COMMAND, method(:onCmdSave))
    saveCmd.connect(SEL_UPDATE, method(:onUpdSave))
    FXMenuCommand.new(fileMenu, "Preferences...").connect(SEL_COMMAND, method(:onCmdPreferences))
    FXMenuCommand.new(fileMenu, "&Quit\tCtrl+Q").connect(SEL_COMMAND, method(:onQuit))
    FXMenuTitle.new(menuBar, "&File", nil, fileMenu)

    # Help menu
    helpMenu = FXMenuPane.new(self)
    FXMenuTitle.new(menuBar, "&Help", nil, helpMenu, LAYOUT_RIGHT)
    aboutCmd = FXMenuCommand.new(helpMenu, "&About...")
    aboutCmd.connect(SEL_COMMAND) do
      FXMessageBox.information(self, MBOX_OK, "About This Program",
        "What a Quiet Stiff\nA Sliding Surface for Found Imagery\nCourtesy of http://whytheluckystiff.net")
    end

    # Respond to window close
    self.connect(SEL_CLOSE, method(:onQuit))

    # Main contents area is split left-to-right.
    splitter = FXSplitter.new(self, LAYOUT_FILL_X|LAYOUT_FILL_Y)

    # Put the list in a sunken frame
    listFrame = FXVerticalFrame.new(splitter,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,
      :padding => 00)

    # List of items appears on the left.
    @itemList = FXList.new(listFrame, :opts => LAYOUT_FILL_X|LAYOUT_FILL_Y)
    @itemList.numVisible = 12
    @itemList.connect(SEL_COMMAND) do |sender, sel, itemIndex|
      @showLinkedImage = false
      getApp().beginWaitCursor do
        setImage(@itemList.getItemData(itemIndex))
        @itemList.setItemIcon(itemIndex, @transpIcon)
      end
    end

    # Sunken border for image widget
    imagebox = FXHorizontalFrame.new(splitter,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,
      :padding => 0)

    # Make image widget
    @imageview = FXImageView.new(imagebox, :opts => LAYOUT_FILL_X|LAYOUT_FILL_Y)
    @imageview.enable
    @imageview.connect(SEL_LEFTBUTTONRELEASE) { toggleImage }

    # Cache previously viewed images in a Hash
    @cache = {}
    @showLinkedImage = false

    # Start out with the current feed's contents.
    refreshList
  end

  # Return true if an item is selected, false otherwise.
  def itemSelected?
    begin
      @itemList.itemSelected?(@itemList.currentItem)
    rescue IndexError
      false
    end
  end

  #
  # Enable or disable the "Save Image" command, depending on
  # whether or not any items are selected.
  #
  def onUpdSave(sender, sel, ptr)
    if itemSelected?
      sender.handle(self, FXSEL(SEL_COMMAND, ID_ENABLE), nil)
    else
      sender.handle(self, FXSEL(SEL_COMMAND, ID_DISABLE), nil)
    end
  end

  # Save the currently selected image to a file.
  def onCmdSave(sender, sel, ptr)
    saveDialog = FXFileDialog.new(self, "Save Image")
    saveDialog.filename = @itemList.getItemText(@itemList.currentItem)
    if saveDialog.execute != 0
      if File.exist? saveDialog.filename
        if MBOX_CLICKED_NO == FXMessageBox.question(self, MBOX_YES_NO,
          "Overwrite Image", "Overwrite existing image?")
          return 1
        end
      end
      getApp().beginWaitCursor do
        FXFileStream.open(saveDialog.filename, FXStreamSave) do |stream|
          @imageview.image.restore
          @imageview.image.savePixels(stream)
        end
      end
    end
  end

  # Display the Preferences dialog box.
  def onCmdPreferences(sender, sel, ptr)
    refreshDelayTarget = FXDataTarget.new(@refreshDelay)

    prefsDialog = FXDialogBox.new(self, "Preferences", :padding => 2)

    buttons = FXHorizontalFrame.new(prefsDialog, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X)
    FXFrame.new(buttons, LAYOUT_FILL_X)
    FXButton.new(buttons, "Cancel", nil, prefsDialog, FXDialogBox::ID_CANCEL,
      LAYOUT_SIDE_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,
      :padLeft => 20, :padRight => 20, :padTop => 4, :padBottom => 4)
    FXButton.new(buttons, "OK", nil, prefsDialog, FXDialogBox::ID_ACCEPT,
      LAYOUT_SIDE_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,
      :padLeft => 30, :padRight => 30, :padTop => 4, :padBottom => 4)

    FXHorizontalSeparator.new(prefsDialog, SEPARATOR_GROOVE|LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X)

    contents = FXMatrix.new(prefsDialog, 2, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FILL_Y)
    FXLabel.new(contents, "Refresh Delay (minutes):", nil, LAYOUT_CENTER_Y)
    FXTextField.new(contents, 5, refreshDelayTarget, FXDataTarget::ID_VALUE,
      LAYOUT_CENTER_Y|FRAME_SUNKEN|FRAME_THICK|JUSTIFY_RIGHT)

    if prefsDialog.execute != 0
      @refreshDelay = refreshDelayTarget.value
    end
  end

  #
  # Given an RSS object, populate the list of images with one
  # per item in the RSS.
  #
  def populateItemList(rss)
    @itemList.clearItems
    liveItems = {}
    rss.items.each do |rssItem|
      srcURL  = getSourceURL(rssItem)
      linkURL = getLinkURL(rssItem)
      itemIcon = (@cache.key?(srcURL) || @cache.key?(linkURL)) ? @transpIcon : @itemIcon
      @itemList.appendItem(rssItem.title, itemIcon, rssItem)
      liveItems[srcURL] = 1 if @cache.key?(srcURL)
      liveItems[linkURL] = 1 if @cache.key?(linkURL)
    end
    @cache.delete_if { |key, value| !liveItems.key?(key) }
  end

  def toggleImage
    @showLinkedImage = !@showLinkedImage
    if itemSelected?
      itemIndex = @itemList.currentItem
      getApp().beginWaitCursor do
        setImage(@itemList.getItemData(itemIndex))
        @itemList.setItemIcon(itemIndex, @transpIcon)
      end
    end
  end

  def setImage(rssItem)
    url = getImageURL(rssItem)
    img = @cache[url]
    if img.nil?
      img = makeImage(url)
      img.create
      @cache[url] = img
    end
    @imageview.image = img
  end

  def getRSSFeed(url)
    rss = nil
    open(url) do |f|
      doc = f.read
      begin
        rss = RSS::Parser.parse(doc)
      rescue RSS::InvalidRSSError
        rss = RSS::Parser.parse(doc, false)
      end
    end
    rss
  end

  # Return the URL listed in the src tag of the description's HTML text.
  def getSourceURL(rssItem)
    rssItem.description =~ /src="(.*?)"/
    return $1
  end

  # Return the URL listed in the href tag of the description's HTML text.
  def getLinkURL(rssItem)
    rssItem.description =~ /href="(.*?)"/
    return $1
  end

  # Return the appropriate URL given the current settings.
  def getImageURL(rssItem)
    @showLinkedImage ? getLinkURL(rssItem) : getSourceURL(rssItem)
  end

  def getImageData(url)
    bytes = nil
    open(url, "rb") do |f|
      bytes = f.read
    end
    bytes
  end

  # This is a little weak...
  def makeImage(url)
    bytes = getImageData(url)
    extension = url.split('.').last.upcase
    case extension
      when "GIF"
        FXGIFImage.new(getApp(), bytes)
      when "JPG"
        FXJPGImage.new(getApp(), bytes)
      when "PNG"
        FXPNGImage.new(getApp(), bytes)
      else
        raise "Unrecognized file extension for: #{url}"
    end
  end

  def resizeItemList
    maxItemSize = 0
    @itemList.each do |listItem|
      itemSize = @itemList.font.getTextWidth(listItem.text)
      maxItemSize = [maxItemSize, itemSize].max
    end
    @itemList.parent.width = maxItemSize
  end

  def refreshList
    # Grab the latest RSS feed
    @rss = getRSSFeed(RSS_FEED_URL)

    # Repopulate the list with this set of items
    populateItemList(@rss)
  end

  def onRefreshList(sender, sel, ptr)
    # Refresh, then re-register the timeout
    getApp().beginWaitCursor { refreshList }
    getApp().addTimeout(1000*60*@refreshDelay, method(:onRefreshList))
  end

  def onQuit(sender, sel, ptr)
    writeRegistry
    getApp().exit(0)
  end

  def readRegistry
    xx = getApp().reg().readIntEntry("SETTINGS", "x", 0)
    yy = getApp().reg().readIntEntry("SETTINGS", "y", 0)
    ww = getApp().reg().readIntEntry("SETTINGS", "width", 850)
    hh = getApp().reg().readIntEntry("SETTINGS", "height", 600)
    @refreshDelay = getApp().reg().readIntEntry("SETTINGS", "refreshDelay", DEFAULT_REFRESH_DELAY)
  end

  def writeRegistry
    getApp().reg().writeIntEntry("SETTINGS", "x", x)
    getApp().reg().writeIntEntry("SETTINGS", "y", y)
    getApp().reg().writeIntEntry("SETTINGS", "width", width)
    getApp().reg().writeIntEntry("SETTINGS", "height", height)
    getApp().reg().writeIntEntry("SETTINGS", "refreshDelay", @refreshDelay)
  end

  def create
    # Do base class create first
    super

    readRegistry

    @itemIcon.create
    @transpIcon.create

    # Make the item list wide enough to show the longest item
    resizeItemList

    # Resize main window
    # Resize main window client area to fit image size
#    resize(@imageview.contentWidth, @imageview.contentHeight)

    # Now show it
    show(PLACEMENT_SCREEN)

    # Start the updates timer
    getApp().addTimeout(1000*60*@refreshDelay, method(:onRefreshList))
  end
end

if __FILE__ == $0
  # Make application
  application = FXApp.new("WhatAQuietWindow", "FXRuby")

  # Make window
  window = WhatAQuietWindow.new(application)

  # Handle interrupts to terminate program gracefully
  application.addSignal("SIGINT", window.method(:onQuit))

  # Create it
  application.create

  # Run
  application.run
end
