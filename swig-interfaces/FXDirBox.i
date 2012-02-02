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


/// Directory Box options
enum {
  DIRBOX_NO_OWN_ASSOC = 0x00020000      /// Do not create associations for files
  };


/// Directory Box
class FXDirBox : public FXTreeListBox {
public:
  long onTreeChanged(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onTreeClicked(FXObject*,FXSelector,void* PTR_NULL); // FIXME
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetStringValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
public:
  %extend {
    /// Constructor
    FXDirBox(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|TREELISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbDirBox(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set current directory
  void setDirectory(const FXString& pathname);

  /// Return current directory
  FXString getDirectory() const;

  /// Change file associations
  void setAssociations(FXFileDict* assoc);

  /// Return file associations
  FXFileDict* getAssociations() const;

  /// Destructor
  virtual ~FXDirBox();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDirBox)
DECLARE_FXID_VIRTUALS(FXDirBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXDirBox)
DECLARE_FXWINDOW_VIRTUALS(FXDirBox)
DECLARE_FXTREELISTBOX_VIRTUALS(FXDirBox)

