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
 * $Id: labelmodule.i 1933 2004-07-06 00:16:31Z lyle $
 ***********************************************************************/

%module label

%include common.i

%import fxdefs.i

// %import core.i
// %import layout.i
%import framesmodule.i

%include FXLabel.i
%include FXButton.i
%include FXCheckButton.i
%include FXMenuButton.i
%include FXOptionMenu.i
%include FXRadioButton.i
%include FXTabItem.i
%include FXToggleButton.i
%include FXTriStateButton.i

%include FXPicker.i
