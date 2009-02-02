/********************************************************************************
*                                                                               *
*                        D r i v e   B o x   W i d g e t                        *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2004 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDriveBox.h 1889 2004-05-26 03:13:01Z lyle $                        *
********************************************************************************/
#ifndef FXDRIVEBOX_H
#define FXDRIVEBOX_H

#ifndef FXLISTBOX_H
#include "FXListBox.h"
#endif

namespace FX {


class FXIcon;
class FXFileDict;

/// Drive Box options
enum {
  DRIVEBOX_NO_OWN_ASSOC = 0x00020000    /// Do not create associations for files
  };


/// Directory Box
class FXAPI FXDriveBox : public FXListBox {
  FXDECLARE(FXDriveBox)
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
  FXDriveBox(){}
  void listDrives();
private:
  FXDriveBox(const FXDriveBox&);
  FXDriveBox &operator=(const FXDriveBox&);
public:
  long onListChanged(FXObject*,FXSelector,void*);
  long onListClicked(FXObject*,FXSelector,void*);
  long onCmdSetValue(FXObject*,FXSelector,void*);
  long onCmdSetStringValue(FXObject*,FXSelector,void*);
  long onCmdGetStringValue(FXObject*,FXSelector,void*);
public:

  /// Constructor
  FXDriveBox(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|LISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

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

  /// Set current drive
  FXbool setDrive(const FXString& drive);

  /// Return current drive
  FXString getDrive() const;

  /// Change file associations
  void setAssociations(FXFileDict* assoc);

  /// Return file associations
  FXFileDict* getAssociations() const { return associations; }

  /// Destructor
  virtual ~FXDriveBox();
  };

}

#endif
