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


/// Directory Box
class FXDriveBox : public FXListBox {
public:
  long onListChanged(FXObject*,FXSelector,void* PTR_INT);
  long onListClicked(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:
  %extend {
    /// Constructor
    FXDriveBox(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|LISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbDriveBox(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set current drive
  FXbool setDrive(const FXString& drive);

  /// Return current drive
  FXString getDrive() const;

  /// Change file associations
  void setAssociations(FXFileDict* assoc);

  /// Return file associations
  FXFileDict* getAssociations() const;

  /// Destructor
  virtual ~FXDriveBox();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDriveBox)
DECLARE_FXID_VIRTUALS(FXDriveBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXDriveBox)
DECLARE_FXWINDOW_VIRTUALS(FXDriveBox)
DECLARE_FXLISTBOX_VIRTUALS(FXDriveBox)


