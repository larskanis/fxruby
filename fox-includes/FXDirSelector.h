/********************************************************************************
*                                                                               *
*              D i r e c t o r y   S e l e c t i o n   W i d g e t              *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDirSelector.h 2127 2005-08-07 20:21:35Z lyle $                     *
********************************************************************************/
#ifndef FXDIRSELECTOR_H
#define FXDIRSELECTOR_H

#ifndef FXPACKER_H
#include "FXPacker.h"
#endif

namespace FX {


class FXDirList;
class FXTextField;
class FXButton;


/**
* The Directory Selector widget is the reusable mega-widget component which
* is the core of the Directory Dialog.  The function of the directory selector widget
* is very similar to the file selector widget, except that the directory selector widget
* displays a tree-structured view of the file system, and thereby makes up and down
* navigation through the file system significantly easier.
*/
class FXAPI FXDirSelector : public FXPacker {
  FXDECLARE(FXDirSelector)
protected:
  FXDirList     *dirbox;        // Directory list widget
  FXTextField   *dirname;       // Directory name entry field
  FXButton      *accept;        // Accept button
  FXButton      *cancel;        // Cancel button
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
private:
  FXDirSelector(const FXDirSelector&);
  FXDirSelector &operator=(const FXDirSelector&);
public:
  long onCmdName(FXObject*,FXSelector,void*);
  long onCmdOpened(FXObject*,FXSelector,void*);
  long onCmdHome(FXObject*,FXSelector,void*);
  long onCmdWork(FXObject*,FXSelector,void*);
  long onCmdDirectoryUp(FXObject*,FXSelector,void*);
  long onPopupMenu(FXObject*,FXSelector,void*);
  long onCmdBookmark(FXObject*,FXSelector,void*);
  long onCmdVisit(FXObject*,FXSelector,void*);
  long onCmdNew(FXObject*,FXSelector,void*);
  long onUpdNew(FXObject*,FXSelector,void*);
  long onCmdMove(FXObject*,FXSelector,void*);
  long onCmdCopy(FXObject*,FXSelector,void*);
  long onCmdLink(FXObject*,FXSelector,void*);
  long onCmdDelete(FXObject*,FXSelector,void*);
  long onUpdSelected(FXObject*,FXSelector,void*);
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

  /// Constructor
  FXDirSelector(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Return a pointer to the "Accept" button
  FXButton *acceptButton() const { return accept; }

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const { return cancel; }

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

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXDirSelector();
  };

}

#endif
