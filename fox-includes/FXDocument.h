/********************************************************************************
*                                                                               *
*                         D o c u m e n t   O b j e c t                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXDocument.h 2127 2005-08-07 20:21:35Z lyle $                        *
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
  void setModified(FXbool mdfy=TRUE){ modified=mdfy; }

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
