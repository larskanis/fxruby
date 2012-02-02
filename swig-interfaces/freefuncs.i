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

/**
 * The default protocol for what happens to objects at garbage-collection
 * time is defined by FXRbObject::freefunc, and it is associated with
 * all of the classes as part of the DO_CLASS_SETUP macro (see exceptions.i).
 */

/**
 * Special cases.
 */

%freefunc FXCursor "FXRbCursor::freefunc";
%freefunc FXCURCursor "FXRbCURCursor::freefunc";
%freefunc FXGIFCursor "FXRbGIFCursor::freefunc";
%freefunc FXGLVisual "FXRbGLVisual::freefunc";
%freefunc FXColorItem "FXRbColorItem::freefunc";
%freefunc FXDirItem "FXRbDirItem::freefunc";
%freefunc FXFileItem "FXRbFileItem::freefunc";
%freefunc FXFoldingItem "FXRbFoldingItem::freefunc";
%freefunc FXFont "FXRbFont::freefunc";
%freefunc FXHeaderItem "FXRbHeaderItem::freefunc";
%freefunc FXIconItem "FXRbIconItem::freefunc";
%freefunc FXListItem "FXRbListItem::freefunc";
%freefunc FXTableItem "FXRbTableItem::freefunc";
%freefunc FXTreeItem "FXRbTreeItem::freefunc";
%freefunc FXVisual "FXRbVisual::freefunc";

/**
 * Other structs and classes not derived from FXObject.
 * Just unregister these.
 */

%freefunc FXChore "FXRbUnregisterRubyObj";
%freefunc FXDC "FXRbUnregisterRubyObj";
%freefunc FXDCPrint "FXRbUnregisterRubyObj";
%freefunc FXEvent "FXRbUnregisterRubyObj";
%freefunc FXExtentd "FXRbUnregisterRubyObj";
%freefunc FXExtentf "FXRbUnregisterRubyObj";
%freefunc FXFileAssoc "FXRbUnregisterRubyObj";
%freefunc FXFileStream "FXRbUnregisterRubyObj";
%freefunc FXFontDesc "FXRbUnregisterRubyObj";
%freefunc FXLight "FXRbUnregisterRubyObj";
%freefunc FXMat3d "FXRbUnregisterRubyObj";
%freefunc FXMat3f "FXRbUnregisterRubyObj";
%freefunc FXMat4d "FXRbUnregisterRubyObj";
%freefunc FXMat4f "FXRbUnregisterRubyObj";
%freefunc FXMaterial "FXRbUnregisterRubyObj";
%freefunc FXMemoryStream "FXRbUnregisterRubyObj";
%freefunc FXPoint "FXRbUnregisterRubyObj";
%freefunc FXPrinter "FXRbUnregisterRubyObj";
%freefunc FXQuatd "FXRbUnregisterRubyObj";
%freefunc FXQuatf "FXRbUnregisterRubyObj";
%freefunc FXRanged "FXRbUnregisterRubyObj";
%freefunc FXRangef "FXRbUnregisterRubyObj";
%freefunc FXRectangle "FXRbUnregisterRubyObj";
%freefunc FXRegion "FXRbUnregisterRubyObj";
%freefunc FXSize "FXRbUnregisterRubyObj";
%freefunc FXSphered "FXRbUnregisterRubyObj";
%freefunc FXSpheref "FXRbUnregisterRubyObj";
%freefunc FXStream "FXRbUnregisterRubyObj";
// %freefunc FXTablePos "FXRbUnregisterRubyObj";
// %freefunc FXTableRange "FXRbUnregisterRubyObj";
%freefunc FXTimer "FXRbUnregisterRubyObj";
%freefunc FXVec2d "FXRbUnregisterRubyObj";
%freefunc FXVec2f "FXRbUnregisterRubyObj";
%freefunc FXVec3d "FXRbUnregisterRubyObj";
%freefunc FXVec3f "FXRbUnregisterRubyObj";
%freefunc FXVec4d "FXRbUnregisterRubyObj";
%freefunc FXVec4f "FXRbUnregisterRubyObj";
%freefunc FXViewport "FXRbUnregisterRubyObj";
%freefunc NotifyHeader "FXRbUnregisterRubyObj";
%freefunc SCNotification "FXRbUnregisterRubyObj";
