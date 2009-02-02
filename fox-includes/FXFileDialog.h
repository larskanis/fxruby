/********************************************************************************
*                                                                               *
*                   F i l e   S e l e c t i o n   D i a l o g                   *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXFileDialog.h 2741 2007-11-16 21:42:00Z lyle $                      *
********************************************************************************/
#ifndef FXFILEDIALOG_H
#define FXFILEDIALOG_H

#ifndef FXDIALOGBOX_H
#include "FXDialogBox.h"
#endif

namespace FX {


class FXFileDict;
class FXFileSelector;


/// File selection dialog
class FXAPI FXFileDialog : public FXDialogBox {
  FXDECLARE(FXFileDialog)
protected:
  FXFileSelector *filebox;
protected:
  FXFileDialog(){}
  void initdialog();
private:
  FXFileDialog(const FXFileDialog&);
  FXFileDialog &operator=(const FXFileDialog&);
public:

  /// Construct file dialog box
  FXFileDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=500,FXint h=300);

  /// Construct free-floating file dialog box
  FXFileDialog(FXApp* a,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=500,FXint h=300);

  /// Hide this window
  virtual void hide();

  /// Change file name
  void setFilename(const FXString& path);

  /// Return file name, if any
  FXString getFilename() const;

  /// Return empty-string terminated list of selected file names, or NULL if none selected
  FXString* getFilenames() const;

  /// Change file pattern
  void setPattern(const FXString& ptrn);

  /// Return file pattern
  FXString getPattern() const;

  /**
  * Change the list of file patterns shown in the file dialog.
  * Each pattern comprises an optional name, followed by a pattern in
  * parentheses.  The patterns are separated by newlines.
  * For example,
  *
  *  "*\n*.cpp,*.cc\n*.hpp,*.hh,*.h"
  *
  * and
  *
  *  "All Files (*)\nC++ Sources (*.cpp,*.cc)\nC++ Headers (*.hpp,*.hh,*.h)"
  *
  * will set the same three patterns, but the former shows no pattern names.
  */
  void setPatternList(const FXString& patterns);

  /// Return list of patterns
  FXString getPatternList() const;

  /**
  * After setting the list of patterns, this call will
  * initially select pattern n as the active one.
  */
  void setCurrentPattern(FXint n);

  /// Return current pattern number
  FXint getCurrentPattern() const;

  /// Get pattern text for given pattern number
  FXString getPatternText(FXint patno) const;

  /// Change pattern text for pattern number
  void setPatternText(FXint patno,const FXString& text);

  /// Return number of patterns
  FXint getNumPatterns() const;

  /// Allow pattern entry
  void allowPatternEntry(FXbool flag);

  /// Return true if pattern entry is allowed
  FXbool allowPatternEntry() const;

  /// Change directory
  void setDirectory(const FXString& path);

  /// Return directory
  FXString getDirectory() const;

  /// Set the inter-item spacing (in pixels)
  void setItemSpace(FXint s);

  /// Return the inter-item spacing (in pixels)
  FXint getItemSpace() const;

  /// Change file selection mode
  void setSelectMode(FXuint mode);

  /// Return file selection mode
  FXuint getSelectMode() const;

  /// Change wildcard matching mode
  void setMatchMode(FXuint mode);

  /// Return wildcard matching mode
  FXuint getMatchMode() const;

  /// Return true if showing hidden files
  FXbool showHiddenFiles() const;

  /// Show or hide hidden files
  void showHiddenFiles(FXbool flag);

  /// Return true if image preview on
  FXbool showImages() const;

  /// Show or hide preview images
  void showImages(FXbool flag);

  /// Return images preview size
  FXint getImageSize() const;

  /// Change images preview size
  void setImageSize(FXint size);

  /// Show readonly button
  void showReadOnly(FXbool flag);

  /// Return true if readonly is shown
  FXbool shownReadOnly() const;

  /// Set initial state of readonly button
  void setReadOnly(FXbool flag);

  /// Get readonly state
  FXbool getReadOnly() const;

  /// Change File List style
  void setFileBoxStyle(FXuint style);

  /// Return File List style
  FXuint getFileBoxStyle() const;

  /// Allow or disallow navigation
  void allowNavigation(FXbool flag);

  /// Is navigation allowed?
  FXbool allowNavigation() const;

  /// Set draggable files
  void setDraggableFiles(FXbool flag);

  /// Are draggable files
  FXbool getDraggableFiles() const;

  /// Change file associations; delete old ones if owned
  void setAssociations(FXFileDict* assoc,FXbool owned=false);

  /// Return file associations
  FXFileDict* getAssociations() const;

  /// Open existing filename
  static FXString getOpenFilename(FXWindow* owner,const FXString& caption,const FXString& path,const FXString& patterns="*",FXint initial=0);

  /// Open multiple existing files
  static FXString* getOpenFilenames(FXWindow* owner,const FXString& caption,const FXString& path,const FXString& patterns="*",FXint initial=0);

  /// Save to filename
  static FXString getSaveFilename(FXWindow* owner,const FXString& caption,const FXString& path,const FXString& patterns="*",FXint initial=0);

  /// Open directory name
  static FXString getOpenDirectory(FXWindow* owner,const FXString& caption,const FXString& path);

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXFileDialog();
  };

}

#endif
