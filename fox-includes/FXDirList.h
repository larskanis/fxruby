/********************************************************************************
*                                                                               *
*                     D i r e c t o r y   L i s t   W i d g e t                 *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXDirList.h 2195 2005-08-25 12:29:55Z lyle $                         *
********************************************************************************/
#ifndef FXDIRLIST_H
#define FXDIRLIST_H

#ifndef FXTREELIST_H
#include "FXTreeList.h"
#endif

namespace FX {


struct FXFileAssoc;
class  FXFileDict;
class  FXIcon;
class  FXDirList;


/// Directory List options
enum {
  DIRLIST_SHOWFILES     = 0x08000000, /// Show files as well as directories
  DIRLIST_SHOWHIDDEN    = 0x10000000, /// Show hidden files or directories
  DIRLIST_NO_OWN_ASSOC  = 0x20000000  /// Do not create associations for files
  };


/// Directory item
class FXAPI FXDirItem : public FXTreeItem {
  FXDECLARE(FXDirItem)
  friend class FXDirList;
protected:
  FXFileAssoc  *assoc;                // File association
  FXDirItem    *link;                 // Link to next item
  FXDirItem    *list;                 // List of child items
  FXlong        size;                 // File size (if a file)
  FXTime        date;                 // Time of item
private:
  FXDirItem(const FXDirItem&);
  FXDirItem& operator=(const FXDirItem&);
protected:
  FXDirItem():assoc(NULL),link(NULL),list(NULL),size(0L),date(0){}
public:
  enum {
    FOLDER      = 512,          /// Directory item
    EXECUTABLE  = 1024,         /// Executable item
    SYMLINK     = 2048,         /// Symbolic linked item
    CHARDEV     = 4096,         /// Character special item
    BLOCKDEV    = 8192,         /// Block special item
    FIFO        = 16384,        /// FIFO item
    SOCK        = 32768         /// Socket item
    };
public:

  /// Constructor
  FXDirItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL):FXTreeItem(text,oi,ci,ptr),assoc(NULL),link(NULL),list(NULL),size(0),date(0){state=HASITEMS;}

  /// Return true if this is a file item
  FXbool isFile() const { return (state&(FOLDER|BLOCKDEV|CHARDEV|FIFO|SOCK))==0; }

  /// Return true if this is a directory item
  FXbool isDirectory() const { return (state&FOLDER)!=0; }

  /// Return true if this is an executable item
  FXbool isExecutable() const { return (state&EXECUTABLE)!=0; }

  /// Return true if this is a symbolic link item
  FXbool isSymlink() const { return (state&SYMLINK)!=0; }

  /// Return true if this is a character device item
  FXbool isChardev() const { return (state&CHARDEV)!=0; }

  /// Return true if this is a block device item
  FXbool isBlockdev() const { return (state&BLOCKDEV)!=0; }

  /// Return true if this is an FIFO item
  FXbool isFifo() const { return (state&FIFO)!=0; }

  /// Return true if this is a socket
  FXbool isSocket() const { return (state&SOCK)!=0; }

  /// Return the file-association object for this item
  FXFileAssoc* getAssoc() const { return assoc; }

  /// Return the file size for this item
  FXlong getSize() const { return size; }

  /// Return the date for this item
  FXTime getDate() const { return date; }
  };


/**
* A Directory List widget provides a tree-structured view of the file system.
* It automatically updates itself periodically by re-scanning the file system
* for any changes.  As it scans the displayed directories and files, it automatically
* determines the icons to be displayed by consulting the file-associations registry
* settings.  A number of messages can be sent to the Directory List to control the
* filter pattern, sorting order, case sensitivity, and hidden file display mode.
* The Directory list widget supports drags and drops of files.
*/
class FXAPI FXDirList : public FXTreeList {
  FXDECLARE(FXDirList)
protected:
  FXFileDict   *associations;         // Association table
  FXDirItem    *list;                 // Root item list
  FXString      dropdirectory;        // Drop directory
  FXDragAction  dropaction;           // Drop action
  FXString      dragfiles;            // Dragged files
  FXString      pattern;              // Pattern of file names
  FXuint        matchmode;            // File wildcard match mode
  FXuint        counter;              // Refresh counter
  FXIcon       *open_folder;          // Open folder icon
  FXIcon       *closed_folder;        // Closed folder icon
  FXIcon       *mini_doc;             // Document icon
  FXIcon       *mini_app;             // Application icon
  FXIcon       *cdromicon;
  FXIcon       *harddiskicon;
  FXIcon       *networkicon;
  FXIcon       *floppyicon;
  FXIcon       *zipdiskicon;
protected:
  FXDirList();
  void listRootItems();
  void listChildItems(FXDirItem *par);
  virtual FXTreeItem* createItem(const FXString& text,FXIcon* oi,FXIcon* ci,void* ptr);
private:
  FXDirList(const FXDirList&);
  FXDirList &operator=(const FXDirList&);
public:
  long onRefreshTimer(FXObject*,FXSelector,void*);
  long onBeginDrag(FXObject*,FXSelector,void*);
  long onEndDrag(FXObject*,FXSelector,void*);
  long onDragged(FXObject*,FXSelector,void*);
  long onDNDEnter(FXObject*,FXSelector,void*);
  long onDNDLeave(FXObject*,FXSelector,void*);
  long onDNDMotion(FXObject*,FXSelector,void*);
  long onDNDDrop(FXObject*,FXSelector,void*);
  long onDNDRequest(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
  long onCmdToggleHidden(FXObject*,FXSelector,void*);
  long onUpdToggleHidden(FXObject*,FXSelector,void*);
  long onCmdShowHidden(FXObject*,FXSelector,void*);
  long onUpdShowHidden(FXObject*,FXSelector,void*);
  long onCmdHideHidden(FXObject*,FXSelector,void*);
  long onUpdHideHidden(FXObject*,FXSelector,void*);
  long onCmdToggleFiles(FXObject*,FXSelector,void*);
  long onUpdToggleFiles(FXObject*,FXSelector,void*);
  long onCmdShowFiles(FXObject*,FXSelector,void*);
  long onUpdShowFiles(FXObject*,FXSelector,void*);
  long onCmdHideFiles(FXObject*,FXSelector,void*);
  long onUpdHideFiles(FXObject*,FXSelector,void*);
  long onCmdSetPattern(FXObject*,FXSelector,void*);
  long onUpdSetPattern(FXObject*,FXSelector,void*);
  long onCmdSortReverse(FXObject*,FXSelector,void*);
  long onUpdSortReverse(FXObject*,FXSelector,void*);
  long onCmdSortCase(FXObject*,FXSelector,void*);
  long onUpdSortCase(FXObject*,FXSelector,void*);
  long onCmdRefresh(FXObject*,FXSelector,void*);
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

  /// Construct a directory list
  FXDirList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Scan the directories and update the items if needed, or if force is TRUE
  void scan(FXbool force=TRUE);

  /// Return TRUE if item is a directory
  FXbool isItemDirectory(const FXTreeItem* item) const;

  /// Return TRUE if item is a file
  FXbool isItemFile(const FXTreeItem* item) const;

  /// Return TRUE if item is executable
  FXbool isItemExecutable(const FXTreeItem* item) const;

  /// Collapse tree
  virtual FXbool collapseTree(FXTreeItem* tree,FXbool notify=FALSE);

  /// Expand tree
  virtual FXbool expandTree(FXTreeItem* tree,FXbool notify=FALSE);

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
  FXString getPattern() const { return pattern; }

  /// Return wildcard matching mode
  FXuint getMatchMode() const { return matchmode; }

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
  FXFileDict* getAssociations() const { return associations; }

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXDirList();
  };

}

#endif
