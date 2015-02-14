/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

struct FXFileAssoc;
class  FXFileDict;
class  FXIcon;


// File List options
enum {
  FILELIST_SHOWHIDDEN   = 0x04000000, /// Show hidden files or directories
  FILELIST_SHOWDIRS     = 0x08000000, /// Show only directories
  FILELIST_SHOWFILES    = 0x10000000, /// Show only files
  FILELIST_SHOWIMAGES   = 0x20000000, /// Show preview of images
  FILELIST_NO_OWN_ASSOC = 0x40000000, /// Do not create associations for files
  FILELIST_NO_PARENT    = 0x80000000  /// Suppress display of '.' and '..'
  };


/// File item
class FXFileItem : public FXIconItem {
public:
  %extend {
    /// Constructor
    FXFileItem(const FXString& text,FXIcon* bi=NULL,FXIcon* mi=NULL,void* ITEMDATA=NULL){
      return new FXRbFileItem(text,bi,mi,ITEMDATA);
      }
    }

  /// Return true if this is a file item
  FXbool isFile() const;

  /// Return true if this is a directory item
  FXbool isDirectory() const;

  /// Return true if this is a share item
  FXbool isShare() const;

  /// Return true if this is an executable item
  FXbool isExecutable() const;

  /// Return true if this is a symbolic link item
  FXbool isSymlink() const;

  /// Return true if this is a character device item
  FXbool isChardev() const;

  /// Return true if this is a block device item
  FXbool isBlockdev() const;

  /// Return true if this is an FIFO item
  FXbool isFifo() const;

  /// Return true if this is a socket
  FXbool isSocket() const;

  /// Return the file-association object for this item
  FXFileAssoc* getAssoc() const;

  /// Return the file size for this item
  FXlong getSize() const;

  /// Return the date for this item
  FXTime getDate() const;

  /// Destructor
  virtual ~FXFileItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFileItem)
DECLARE_FXICONITEM_VIRTUALS(FXFileItem)


// Rename these methods
%rename(getHiddenFilesShown) FXFileList::showHiddenFiles() const;
%rename(setHiddenFilesShown) FXFileList::showHiddenFiles(FXbool showing);

%rename(getOnlyDirectoriesShown) FXFileList::showOnlyDirectories() const;
%rename(setOnlyDirectoriesShown) FXFileList::showOnlyDirectories(FXbool shown);

%rename(getShowImages) FXFileList::showImages() const;
%rename(setShowImages) FXFileList::showImages(FXbool showing);

  /// Return TRUE if showing parent directories
%rename("parentDirsShown?") FXFileList::showParents() const;

/// Show parent directories
%rename("parentDirsShown=") FXFileList::showParents(FXbool shown);

%typemap(check) FXint FILELIST_ITEM_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumItems()) {
    rb_raise(rb_eIndexError, "file list item index out of bounds");
  }
}

%apply FXint FILELIST_ITEM_INDEX { FXint index };

/**
* A File List widget provides an icon rich view of the file system.
* It automatically updates itself periodically by re-scanning the file system
* for any changes.  As it scans the displayed directory, it automatically
* determines the icons to be displayed by consulting the file associations registry
* settings.  A number of messages can be sent to the File List to control the
* filter pattern, sort category, sorting order, case sensitivity, and hidden file
* display mode.
* The File list widget supports drags and drops of files.
*/
class FXFileList : public FXIconList {
public:
  long onOpenTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onRefreshTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onBeginDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onEndDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onDragged(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortByName(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortByName(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortByType(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortByType(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortBySize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortBySize(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortByTime(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortByTime(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortByUser(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortByUser(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortByGroup(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortByGroup(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortReverse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortReverse(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSortCase(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortCase(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdSetPattern(FXObject*,FXSelector,void* PTR_CSTRING);
  long onUpdSetPattern(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetDirectory(FXObject*,FXSelector,void* PTR_CSTRING);
  long onUpdSetDirectory(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdShowHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdShowHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHideHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHideHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleImages(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleImages(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHeader(FXObject*,FXSelector,void* PTR_UINT);
  long onUpdHeader(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRefresh(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  static FXint ascending(const FXIconItem* a,const FXIconItem* b);
  static FXint descending(const FXIconItem* a,const FXIconItem* b);
  static FXint ascendingCase(const FXIconItem* a,const FXIconItem* b);
  static FXint descendingCase(const FXIconItem* a,const FXIconItem* b);
  static FXint ascendingType(const FXIconItem* a,const FXIconItem* b);
  static FXint descendingType(const FXIconItem* a,const FXIconItem* b);
  static FXint ascendingSize(const FXIconItem* a,const FXIconItem* b);
  static FXint descendingSize(const FXIconItem* a,const FXIconItem* b);
  static FXint ascendingTime(const FXIconItem* a,const FXIconItem* b);
  static FXint descendingTime(const FXIconItem* a,const FXIconItem* b);
  static FXint ascendingUser(const FXIconItem* a,const FXIconItem* b);
  static FXint descendingUser(const FXIconItem* a,const FXIconItem* b);
  static FXint ascendingGroup(const FXIconItem* a,const FXIconItem* b);
  static FXint descendingGroup(const FXIconItem* a,const FXIconItem* b);
public:
  enum {
    ID_REFRESHTIMER=FXIconList::ID_LAST,
    ID_OPENTIMER,
    ID_SORT_BY_NAME,    /// Sort by name
    ID_SORT_BY_TYPE,    /// Sort by type
    ID_SORT_BY_SIZE,    /// Sort by size
    ID_SORT_BY_TIME,    /// Sort by access time
    ID_SORT_BY_USER,    /// Sort by owner name
    ID_SORT_BY_GROUP,   /// Sort by group name
    ID_SORT_REVERSE,    /// Reverse sort order
    ID_SORT_CASE,       /// Toggle sort case sensitivity
    ID_DIRECTORY_UP,    /// Move up one directory
    ID_SET_PATTERN,     /// Set match pattern
    ID_SET_DIRECTORY,   /// Set directory
    ID_SHOW_HIDDEN,     /// Show hidden files
    ID_HIDE_HIDDEN,     /// Hide hidden files
    ID_TOGGLE_HIDDEN,   /// Toggle display of hidden files
    ID_TOGGLE_IMAGES,   /// Toggle display of images
    ID_REFRESH,         /// Refresh immediately
    ID_LAST
    };
public:
  %extend {
    /// Construct a file list
    FXFileList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbFileList(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Scan the current directory and update the items if needed, or if force is TRUE
  void scan(FXbool force=TRUE);

  /// Set current file
  void setCurrentFile(const FXString& file,FXbool notify=FALSE);

  /// Return current file
  FXString getCurrentFile() const;

  /// Set current directory
  void setDirectory(const FXString& path);

  /// Return current directory
  FXString getDirectory() const;

  /// Change wildcard matching pattern
  void setPattern(const FXString& ptrn);

  /// Return wildcard pattern
  FXString getPattern() const;

  /// Return TRUE if item is a directory
  FXbool isItemDirectory(FXint index) const;

  /// Return TRUE if item is a directory
  FXbool isItemShare(FXint index) const;

  /// Return TRUE if item is a file
  FXbool isItemFile(FXint index) const;

  /// Return TRUE if item is executable
  FXbool isItemExecutable(FXint index) const;

  /// Return name of item at index
  FXString getItemFilename(FXint index) const;

  /// Return full pathname of item at index
  FXString getItemPathname(FXint index) const;

  /// Return file association of item
  FXFileAssoc* getItemAssoc(FXint index) const;

  /// Return wildcard matching mode
  FXuint getMatchMode() const;

  /// Change wildcard matching mode
  void setMatchMode(FXuint mode);

  /// Return TRUE if showing hidden files
  FXbool showHiddenFiles() const;

  /// Show or hide hidden files
  void showHiddenFiles(FXbool showing);

  /// Return TRUE if showing directories only
  FXbool showOnlyDirectories() const;

  /// Show directories only
  void showOnlyDirectories(FXbool shown);

  /// Return TRUE if showing files only
  FXbool showOnlyFiles() const;

  /// Show files only
  void showOnlyFiles(FXbool shown);

  /// Return TRUE if image preview on
  FXbool showImages() const;

  /// Show or hide preview images
  void showImages(FXbool showing);

  /// Return images preview size
  FXint getImageSize() const;

  /// Change images preview size
  void setImageSize(FXint size);

  /// Return TRUE if showing parent directories
  FXbool showParents() const;

  /// Show parent directories
  void showParents(FXbool shown);

  /// Change file associations
  void setAssociations(FXFileDict* assoc);

  /// Return file associations
  FXFileDict* getAssociations() const;

  /// Destructor
  virtual ~FXFileList();
  };

%clear FXint index;

DECLARE_FXOBJECT_VIRTUALS(FXFileList)
DECLARE_FXID_VIRTUALS(FXFileList)
DECLARE_FXDRAWABLE_VIRTUALS(FXFileList)
DECLARE_FXWINDOW_VIRTUALS(FXFileList)
DECLARE_FXSCROLLAREA_VIRTUALS(FXFileList)
DECLARE_FXICONLIST_VIRTUALS(FXFileList)
