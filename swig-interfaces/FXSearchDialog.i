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


/// Text search dialog
class FXSearchDialog : public FXReplaceDialog {
public:

  /// Construct search dialog box
  %extend {
    FXSearchDialog(FXWindow* owner,const FXString& caption,FXIcon* ic=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbSearchDialog(owner,caption,ic,opts,x,y,w,h);
      }
    }

  /// Destructor
  virtual ~FXSearchDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXSearchDialog)
DECLARE_FXID_VIRTUALS(FXSearchDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXSearchDialog)
DECLARE_FXWINDOW_VIRTUALS(FXSearchDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXSearchDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXSearchDialog)

