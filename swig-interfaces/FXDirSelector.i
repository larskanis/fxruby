/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

class FXDirList;
class FXTextField;
class FXButton;
class FXDriveBox;


// Rename these methods
%rename(getShowFiles) FXDirSelector::showFiles() const;
%rename(setShowFiles) FXDirSelector::showFiles(FXbool showing);
%rename(getShowHiddenFiles) FXDirSelector::showHiddenFiles() const;
%rename(setShowHiddenFiles) FXDirSelector::showHiddenFiles(FXbool showing);


/// Directory selection widget
class FXDirSelector : public FXPacker {
protected:
  FXDirList     *dirbox;          // Directory list widget
  FXDriveBox    *drivebox;        // Drive selection widget
  FXTextField   *dirname;         // Directory name entry field
  FXButton      *accept;          // Accept button
  FXButton      *cancel;          // Cancel button
  FXIcon        *updiricon;     // Up directory icon
  FXIcon        *homeicon;      // Go home icon
  FXIcon        *workicon;      // Go home icon
  FXIcon        *markicon;      // Book mark icon
  FXIcon        *clearicon;     // Book clear icon
  FXIcon        *newicon;       // New directory icon
  FXIcon        *deleteicon;    // Delete file icon
  FXIcon        *moveicon;      // Rename file icon
  FXIcon        *copyicon;      // Copy file icon
  FXIcon        *linkicon;      // Link file icon
  FXRecentFiles  mrufiles;      // Recently visited places
protected:
  FXDirSelector(){}
public:
  long onCmdName(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdOpened(FXObject*,FXSelector,void* PTR_TREEITEM);
  long onCmdHome(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdWork(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onPopupMenu(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdBookmark(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdVisit(FXObject*,FXSelector,void*); // FIXME
  long onCmdNew(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdNew(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMove(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCopy(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLink(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDelete(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSelected(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_DIRNAME=FXPacker::ID_LAST,
    ID_DIRLIST,
    ID_HOME,
    ID_WORK,
    ID_DIRECTORY_UP,
    ID_BOOKMARK,
    ID_VISIT,
    ID_NEW,
    ID_DELETE,
    ID_MOVE,
    ID_COPY,
    ID_LINK,
    ID_LAST
    };
public:
  %extend {
    /// Constructor
    FXDirSelector(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbDirSelector(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return a pointer to the "Accept" button
  FXButton *acceptButton() const;

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const;
  
  /// Change directory
  void setDirectory(const FXString& path);
  
  /// Return directory
  FXString getDirectory() const;

  /// Return TRUE if showing files as well as directories
  FXbool showFiles() const;

  /// Show or hide normal files
  void showFiles(FXbool showing);

  /// Return TRUE if showing hidden directories
  FXbool showHiddenFiles() const;

  /// Show or hide hidden directories
  void showHiddenFiles(FXbool showing);

  /// Return wildcard matching mode
  FXuint getMatchMode() const;

  /// Change wildcard matching mode
  void setMatchMode(FXuint mode);

  /// Change Directory List style
  void setDirBoxStyle(FXuint style);

  /// Return Directory List style
  FXuint getDirBoxStyle() const;

  /// Destructor
  virtual ~FXDirSelector();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDirSelector)
DECLARE_FXID_VIRTUALS(FXDirSelector)
DECLARE_FXDRAWABLE_VIRTUALS(FXDirSelector)
DECLARE_FXWINDOW_VIRTUALS(FXDirSelector)

