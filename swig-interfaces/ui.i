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
 * $Id: ui.i 2479 2006-09-08 23:20:52Z lyle $
 ***********************************************************************/

%module ui

%include common.i

%import fxdefs.i

%import core.i
%import layout.i
%import framesmodule.i

%include FX7Segment.i
%include FXSpinner.i
%include FXRealSpinner.i
%include FXCanvas.i
%include FXToolTip.i
%include FXDockBar.i
%include FXToolBar.i
%include FXTabBar.i
%include FXTabBook.i
%include FXScrollBar.i
%include FXComboBox.i
%include FXListBox.i
%include FXTreeListBox.i
%include FXImageView.i
// %include FXBitmapView.i
%include FXDragCorner.i
%include FXDirBox.i
%include FXDriveBox.i
%include FXDirSelector.i
%include FXFileSelector.i
%include FXColorSelector.i
%include FXFontSelector.i
%include FXDockHandler.i
%include FXDockTitle.i
%include FXToolBarGrip.i
%include FXToolBarShell.i
%include FXRulerView.i
