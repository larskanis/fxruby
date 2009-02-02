/********************************************************************************
*                                                                               *
*                    D i r e c t o r y   B o x   W i d g e t                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDirBox.h 2127 2005-08-07 20:21:35Z lyle $                          *
********************************************************************************/
#ifndef FXDIRBOX_H
#define FXDIRBOX_H

#ifndef FXTREELISTBOX_H
#include "FXTreeListBox.h"
#endif

namespace FX {


class FXIcon;
class FXFileDict;

/// Directory Box options
enum {
  DIRBOX_NO_OWN_ASSOC = 0x00020000      /// Do not create associations for files
  };


/**
* A Directory Box widget allows the user to select parts of a file path.
* First, it is filled with a string comprising a file path, like "/a/b/c".
* Then, the user can select "/a/b/c", "/a/b", "/a", and "/" from the drop-down
* list.  The entries in the drop-down list are automatically provided with icons
* by consulting the file-associations registry settings.
* The Directory Box sends SEL_CHANGED and SEL_COMMAND messages, with the string
* containing the full path to the selected item.
*/
class FXAPI FXDirBox : public FXTreeListBox {
  FXDECLARE(FXDirBox)
protected:
  FXFileDict *associations;     // Association table
  FXIcon     *foldericon;       // Folder icons
  FXIcon     *cdromicon;        // CDROM icon
  FXIcon     *harddiskicon;     // Hard disk icon
  FXIcon     *netdriveicon;     // Networked drive icon
  FXIcon     *floppyicon;       // Floppy icon
  FXIcon     *nethoodicon;      // Network neighborhood icon
  FXIcon     *zipdiskicon;      // Zip drive icon
protected:
  FXDirBox(){}
  FXString getItemPathname(FXTreeItem *item) const;
  FXTreeItem* getPathnameItem(const FXString& path);
private:
  FXDirBox(const FXDirBox&);
  FXDirBox &operator=(const FXDirBox&);
public:
  long onTreeChanged(FXObject*,FXSelector,void*);
  long onTreeClicked(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
public:

  /// Construct a Directory Box
  FXDirBox(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|TREELISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Detach server-side resources
  virtual void detach();

  /// Destroy server-side resources
  virtual void destroy();

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Set current directory
  void setDirectory(const FXString& pathname);

  /// Return current directory
  FXString getDirectory() const;

  /// Change file associations used to look up icons
  void setAssociations(FXFileDict* assoc);

  /// Return file associations
  FXFileDict* getAssociations() const { return associations; }

  /// Destructor
  virtual ~FXDirBox();
  };

}

#endif
