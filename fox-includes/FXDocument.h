/********************************************************************************
*                                                                               *
*                         D o c u m e n t   O b j e c t                         *
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
* $Id: FXDocument.h 2725 2007-11-16 16:57:54Z lyle $                        *
********************************************************************************/
#ifndef FXDOCUMENT_H
#define FXDOCUMENT_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {


// Forward
class FXWindow;


/// Abstract base class for documents
class FXAPI FXDocument : public FXObject {
  FXDECLARE(FXDocument)
private:
  FXString     title;             // Title to appear above windows
  FXString     filename;          // File name to save to
  FXbool       modified;          // Document has been modified
public:
  long onUpdTitle(FXObject*,FXSelector,void*);
  long onUpdFilename(FXObject*,FXSelector,void*);
public:
  enum {
    ID_TITLE=10000,                 // Don't interfere with viewer's message id's
    ID_FILENAME,
    ID_LAST
    };
public:

  /// Constructor
  FXDocument();

  /// Return true if document is modified
  FXbool isModified() const { return modified; }

  /// Set its modified state
  void setModified(FXbool mdfy=true){ modified=mdfy; }

  /// Set document title
  void setTitle(const FXString& name);

  /// Get document title
  const FXString& getTitle() const { return title; }

  /// Set document filename
  void setFilename(const FXString& path);

  /// Get document filename
  const FXString& getFilename() const { return filename; }

  /// Save document to a stream
  virtual void save(FXStream& store) const;

  /// Load document from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXDocument();
  };

}

#endif
