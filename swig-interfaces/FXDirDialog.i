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

class FXDirSelector;


// Rename these methods
%rename(getShowFiles) FXDirDialog::showFiles() const;
%rename(setShowFiles) FXDirDialog::showFiles(FXbool showing);
%rename(getShowHiddenFiles) FXDirDialog::showHiddenFiles() const;
%rename(setShowHiddenFiles) FXDirDialog::showHiddenFiles(FXbool showing);


/// Directory selection dialog
class FXDirDialog : public FXDialogBox {
public:
  %extend {
    /// Construct Directory Dialog Box
    FXDirDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=400,FXint h=300){
      return new FXRbDirDialog(owner,name,opts,x,y,w,h);
      }

    /// Construct free-floating Directory Dialog box
    FXDirDialog(FXApp* a,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=400,FXint h=300){
      return new FXRbDirDialog(a,name,opts,x,y,w,h);
      }
    }

  /// Change directory
  void setDirectory(const FXString& path);

  /// Return directory
  FXString getDirectory() const;

  /// Return TRUE if showing files as well as directories
  FXbool showFiles() const;

  /// Show or hide normal files
  void showFiles(FXbool showing);

  /// Return TRUE if showing hidden files
  FXbool showHiddenFiles() const;

  /// Show or hide hidden files
  void showHiddenFiles(FXbool showing);

  /// Return wildcard matching mode
  FXuint getMatchMode() const;

  /// Change wildcard matching mode
  void setMatchMode(FXuint mode);

  /// Change Directory List style
  void setDirBoxStyle(FXuint style);

  /// Return Directory List style
  FXuint getDirBoxStyle() const;

  /// Open directory name
  static FXString getOpenDirectory(FXWindow* owner,const FXString& caption,const FXString& path);

  /// Destructor
  virtual ~FXDirDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDirDialog)
DECLARE_FXID_VIRTUALS(FXDirDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXDirDialog)
DECLARE_FXWINDOW_VIRTUALS(FXDirDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXDirDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXDirDialog)

