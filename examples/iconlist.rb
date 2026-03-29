require 'fox16'
require 'uri'

include Fox

class IconListWindow < FXMainWindow

  # Load the named PNG icon from a file
  def loadIcon(filename)
    filename = File.expand_path("../icons/#{filename}", __FILE__)
    File.open(filename, "rb") do |f|
      FXPNGIcon.new(getApp(), f.read)
    end
  end

  # Main window constructor
  def initialize(app)
    # Initialize base class first
    super(app, "Icon List Test", :opts => DECOR_ALL, :width => 800, :height => 600)

    # Menu bar
    menubar = FXMenuBar.new(self, LAYOUT_SIDE_TOP|LAYOUT_FILL_X)

    # File menu
    filemenu = FXMenuPane.new(self)
    FXMenuCommand.new(filemenu, "&Quit\tCtl-Q", nil, getApp(), FXApp::ID_QUIT)
    FXMenuTitle.new(menubar, "&File", nil, filemenu)

    # Status bar
    status = FXStatusBar.new(self, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER)

    # Main window interior
    group = FXVerticalFrame.new(self, LAYOUT_FILL_X|LAYOUT_FILL_Y,
      :padLeft => 0, :padRight => 0, :padTop => 0, :padBottom => 0)

    # Files
    FXLabel.new(group, "Icon List Widget", nil, LAYOUT_TOP|LAYOUT_FILL_X|FRAME_SUNKEN)
    subgroup = FXVerticalFrame.new(group, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,
      :padLeft => 0, :padRight => 0, :padTop => 0, :padBottom => 0)

    # Icon list on the right
    iconlist = FXIconList.new(subgroup, :opts => LAYOUT_FILL_X|LAYOUT_FILL_Y|ICONLIST_BIG_ICONS|ICONLIST_EXTENDEDSELECT)

    iconlist.appendHeader("Name", nil, 200)
    iconlist.appendHeader("Type", nil, 100)
    iconlist.appendHeader("Size", nil, 60)
    iconlist.appendHeader("Modified Date", nil, 150)
    iconlist.appendHeader("User", nil, 50)
    iconlist.appendHeader("Group", nil, 50)

    @big_folder = loadIcon("bigfolder.png")
    @mini_folder = loadIcon("minifolder.png")

    iconlist.appendItem("Really BIG and wide item to test\tDocument\t10000\tJune 13, 1999\tUser\tSoftware", @big_folder, @mini_folder)
    1.upto(400) do |i|
      iconlist.appendItem("Filename_#{i}\tDocument\t10000\tJune 13, 1999\tUser\tSoftware", @big_folder, @mini_folder)
    end
    iconlist.currentItem = iconlist.numItems - 1
    @iconlist = iconlist

    FXMenuPane.new(self) do |menuPane|
      paste_icon = loadIcon("paste.png")
      FXMenuCommand.new(menuPane, "&Insert from clipboard\tCtrl-V", paste_icon) do |mc|
        mc.connect(SEL_COMMAND) { insert_from_clipboard }
      end
      FXMenuTitle.new(menubar, "&Edit", nil, menuPane)
    end

    # Arrange menu
    FXMenuPane.new(self) do |menuPane|
      FXMenuCommand.new(menuPane, "&Details", nil, iconlist, FXIconList::ID_SHOW_DETAILS)
      FXMenuCommand.new(menuPane, "&Small Icons", nil, iconlist, FXIconList::ID_SHOW_MINI_ICONS)
      FXMenuCommand.new(menuPane, "&Big Icons", nil, iconlist, FXIconList::ID_SHOW_BIG_ICONS)
      FXMenuCommand.new(menuPane, "&Rows", nil, iconlist, FXIconList::ID_ARRANGE_BY_ROWS)
      FXMenuCommand.new(menuPane, "&Columns", nil, iconlist, FXIconList::ID_ARRANGE_BY_COLUMNS)
      FXMenuTitle.new(menubar, "&Arrange", nil, menuPane)
    end
    # Let's see a tooltip
    FXToolTip.new(getApp())

    # Register the drag types for copy files from the clipboard
    @dragtype_urilist = app.registerDragType("text/uri-list")
    @dragtype_filename = app.registerDragType("FileNameW")
    @dragtype_filegroup = app.registerDragType("FileGroupDescriptorW")

  end

  # Overrides base class version
  def create
    super
    show(PLACEMENT_SCREEN)
  end

  def get_clipboard_files
    # Show the avaliable clipboard formats:
    puts "Avaliable clipboard formats:"
    type_ids = inquireDNDTypes(FROM_CLIPBOARD)
    pp type_ids.map{|id| [id, app.getDragTypeName(id), getDNDData(FROM_CLIPBOARD, id)] }

    # Process copied files with standard uri list (on Linux)
    paths = getDNDData(FROM_CLIPBOARD, @dragtype_urilist)
    if paths
      files = paths.each_line.map do |file|
        # file.chomp.sub(%r{^file://}, "")
        URI.decode_uri_component(URI(file.chomp).path)
      end
      return files
    end

    # Process copied data from Windows Explorer
    # This works for files only, but not for directories.
    path = getDNDData(FROM_CLIPBOARD, @dragtype_filename)
    filesdata = getDNDData(FROM_CLIPBOARD, @dragtype_filegroup)
    if path && filesdata
      path = path.encode("UTF-8", "UTF-16LE").rstrip("\0")
      path = File.dirname(path)
      cnt, rest = filesdata.unpack("Ia*")
      files = cnt.times.map do
        # Unpack the FILEGROUPDESCRIPTORW struct
        #  DWORD    dwFlags;
        #  CLSID    clsid;
        #  SIZEL    sizel;
        #  POINTL   pointl;
        #  DWORD    dwFileAttributes;
        #  FILETIME ftCreationTime;
        #  FILETIME ftLastAccessTime;
        #  FILETIME ftLastWriteTime;
        #  DWORD    nFileSizeHigh;
        #  DWORD    nFileSizeLow;
        #  CHAR     cFileName[MAX_PATH];
        dwFlags, clsid, sizel, pointl, dwFileAttributes,
            ftCreationTime, ftLastAccessTime, ftLastAccessTime,
            nFileSizeHigh, nFileSizeLow, cFileName, rest =
            rest.unpack("La16a8a8La8a8a8LLa520a*")
        fname = cFileName.encode("UTF-8", "UTF-16LE").rstrip("\0")
        File.join(path, fname)
      end
      return files
    end
  end

  def insert_from_clipboard
    files = get_clipboard_files

    files&.each do |file|
      ftype = File.ftype(file)
      fsize = File.size(file)
      mtime = File.mtime(file)
      @iconlist.prependItem([file, ftype, fsize, mtime].join("\t"), @big_folder, @mini_folder)
    end
  end
end

if __FILE__ == $0
  FXApp.new("IconList", "FXRuby") do |theApp|
    IconListWindow.new(theApp)
    theApp.create
    theApp.run
  end
end

