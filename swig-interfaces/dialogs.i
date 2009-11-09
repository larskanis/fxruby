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

/***********************************************************************
 * $Id: dialogs.i 2134 2005-08-14 00:31:17Z lyle $
 ***********************************************************************/

%module dialogs

%include common.i

%import fxdefs.i
%import core.i
%import ui.i
%import layout.i

%include FXDialogBox.i
%include FXDirDialog.i
%include FXFileDialog.i
%include FXColorDialog.i
%include FXFontDialog.i
%include FXReplaceDialog.i
%include FXSearchDialog.i
%include FXInputDialog.i
%include FXPrintDialog.i
%include FXProgressDialog.i
%include FXMessageBox.i
%include FXWizard.i
%include FXChoiceBox.i

