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

// Forward
class FXWindow;


/// Abstract base class for documents
class FXDocument : public FXObject {
public:
  long onUpdTitle(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdFilename(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_TITLE=10000,                 // Don't interfere with viewer's message id's
    ID_FILENAME,
    ID_LAST
    };
public:
  %extend {
    /// Constructor
    FXDocument(){
      return new FXRbDocument();
      }
    }

  /// Return true if document is modified
  FXbool isModified() const;

  /// Set its modified state
  void setModified(FXbool mdfy=TRUE);

  /// Set document title
  void setTitle(const FXString& name);

  /// Get document title
  const FXString& getTitle() const;

  /// Set document filename
  void setFilename(const FXString& path);

  /// Get document filename
  const FXString& getFilename() const;

  /// Destructor
  virtual ~FXDocument();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDocument)

