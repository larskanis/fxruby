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
 * $Id: core.i 2381 2006-04-21 00:28:05Z lyle $
 ***********************************************************************/

%module core

%include common.i

%inline %{
void setIgnoreExceptions(VALUE ignore){
  extern FXbool FXRbCatchExceptions;
  FXRbCatchExceptions=(ignore==Qtrue)? TRUE : FALSE;
  }
%}

%include fxdefs.i

%include FXStream.i
%include FXFileStream.i
%include FXMemoryStream.i

%include FXSize.i
%include FXPoint.i
%include FXRectangle.i
%include FXRegion.i

%include FXObject.i
%include FXAccelTable.i
%include FXApp.i
%include FXDataTarget.i
%include FXDebugTarget.i
%include FXDelegator.i
%include FXTranslator.i

%include FXDict.i
%include FXFileDict.i
%include FXIconDict.i
%include FXStringDict.i
%include FXSettings.i
%include FXRegistry.i

%include FXDocument.i

%include FXRecentFiles.i

%include FXId.i
%include FXCursor.i
%include FXCURCursor.i
%include FXGIFCursor.i
%include FXDrawable.i
%include FXVisual.i
%include FXFont.i

%include FXWindow.i
%include FXFrame.i
%include FXComposite.i
%include FXRootWindow.i
%include FXShell.i
%include FXPopup.i
%include FXTopWindow.i
%include FXMainWindow.i
%include FXSplashWindow.i

