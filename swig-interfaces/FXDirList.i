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


/// Directory List options
enum {
  DIRLIST_SHOWFILES     = 0x08000000, /// Show files as well as directories
  DIRLIST_SHOWHIDDEN    = 0x10000000, /// Show hidden files or directories
  DIRLIST_NO_OWN_ASSOC  = 0x20000000  /// Do not create associations for files
  };


/// Directory item
class FXDirItem : public FXTreeItem {
public:
  enum {
    FOLDER      = 512,                // Directory item
    EXECUTABLE  = 1024,               // Executable item
    SYMLINK     = 2048,               // Symbolic linked item
    CHARDEV     = 4096,               // Character special item
    BLOCKDEV    = 8192,               // Block special item
    FIFO        = 16384,              // FIFO item
    SOCK        = 32768               // Socket item
    };
public:
  %extend {
    /// Constructor
    FXDirItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL){
      return new FXRbDirItem(text,oi,ci,ITEMDATA);
      }
    }

  /// Return true if this is a file item
  FXbool isFile() const;

  /// Return true if this is a directory item
  FXbool isDirectory() const;

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
  virtual ~FXDirItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDirItem)
DECLARE_FXTREEITEM_VIRTUALS(FXDirItem)


// Rename these methods
%rename(getShowFiles) FXDirList::showFiles() const;
%rename(setShowFiles) FXDirList::showFiles(FXbool showing);
%rename(getShowHiddenFiles) FXDirList::showHiddenFiles() const;
%rename(setShowHiddenFiles) FXDirList::showHiddenFiles(FXbool showing);


/**
* A Directory List widget provides a tree-structured view of the file system.
* It automatically updates itself periodically by re-scanning the file system
* for any changes.  As it scans the displayed directories and files, it automatically
* determines the icons to be displayed by consulting the file-associations registry
* settings.  A number of messages can be sent to the Directory List to control the
* filter pattern, sorting order, case sensitivity, and hidden file display mode.
* The Directory list widget supports drags and drops of files.
*/
class FXDirList : public FXTreeList {
public:
  long onRefreshTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onBeginDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onEndDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onDragged(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdToggleHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdShowHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdShowHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHideHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHideHidden(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleFiles(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleFiles(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdShowFiles(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdShowFiles(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHideFiles(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHideFiles(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetPattern(FXObject*,FXSelector,void* PTR_CSTRING);
  long onUpdSetPattern(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSortReverse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortReverse(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdSortCase(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSortCase(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdRefresh(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  static FXint ascending(const FXTreeItem* a,const FXTreeItem* b);
  static FXint descending(const FXTreeItem* a,const FXTreeItem* b);
  static FXint ascendingCase(const FXTreeItem* a,const FXTreeItem* b);
  static FXint descendingCase(const FXTreeItem* a,const FXTreeItem* b);
public:
  enum {
    ID_REFRESHTIMER=FXTreeList::ID_LAST,
    ID_SHOW_FILES,
    ID_HIDE_FILES,
    ID_TOGGLE_FILES,
    ID_SHOW_HIDDEN,
    ID_HIDE_HIDDEN,
    ID_TOGGLE_HIDDEN,
    ID_SET_PATTERN,
    ID_SORT_REVERSE,
    ID_SORT_CASE,
    ID_REFRESH,
    ID_LAST
    };
public:
  %extend {
    /// Construct a directory list
    FXDirList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbDirList(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Scan the directories and update the items if needed, or if force is TRUE
  void scan(FXbool force=TRUE);

  /// Return TRUE if item is a directory
  FXbool isItemDirectory(const FXTreeItem* item) const;

  /// Return TRUE if item is a file
  FXbool isItemFile(const FXTreeItem* item) const;

  /// Return TRUE if item is executable
  FXbool isItemExecutable(const FXTreeItem* item) const;

  /// Set current file
  void setCurrentFile(const FXString& file,FXbool notify=FALSE);

  /// Return current file
  FXString getCurrentFile() const;

  /// Set current directory
  void setDirectory(const FXString& path,FXbool notify=FALSE);

  /// Return current directory
  FXString getDirectory() const;

  /// Return absolute pathname of item
  FXString getItemPathname(const FXTreeItem* item) const;

  /// Return the item from the absolute pathname
  FXTreeItem* getPathnameItem(const FXString& path);

  /// Change wildcard matching pattern
  void setPattern(const FXString& ptrn);

  /// Return wildcard pattern
  FXString getPattern() const;

  /// Return wildcard matching mode
  FXuint getMatchMode() const;

  /// Change wildcard matching mode
  void setMatchMode(FXuint mode);

  /// Return TRUE if showing files as well as directories
  FXbool showFiles() const;

  /// Show or hide normal files
  void showFiles(FXbool showing);

  /// Return TRUE if showing hidden files and directories
  FXbool showHiddenFiles() const;

  /// Show or hide hidden files and directories
  void showHiddenFiles(FXbool showing);

  /// Change file associations
  void setAssociations(FXFileDict* assoc);

  /// Return file associations
  FXFileDict* getAssociations() const;

  /// Destructor
  virtual ~FXDirList();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDirList)
DECLARE_FXID_VIRTUALS(FXDirList)
DECLARE_FXDRAWABLE_VIRTUALS(FXDirList)
DECLARE_FXWINDOW_VIRTUALS(FXDirList)
DECLARE_FXSCROLLAREA_VIRTUALS(FXDirList)
DECLARE_FXTREELIST_VIRTUALS(FXDirList)
