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

%rename("app") FXRecentFiles::getApp() const;

/**
* The Recent files manages a most recently used (MRU) file list by
* means of the standard system registry.
*/
class FXRecentFiles : public FXObject {
public:
  long onCmdClear(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFile(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdFile(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdAnyFiles(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_CLEAR,
    ID_ANYFILES,
    ID_FILE_1,
    ID_FILE_2,
    ID_FILE_3,
    ID_FILE_4,
    ID_FILE_5,
    ID_FILE_6,
    ID_FILE_7,
    ID_FILE_8,
    ID_FILE_9,
    ID_FILE_10,
    ID_LAST
    };
public:
  %extend {
    /// Make new recent files group, using global application instance
    FXRecentFiles(){ return new FXRbRecentFiles(); }

    /// Make new recent files group with default groupname
    FXRecentFiles(FXApp* a){ return new FXRbRecentFiles(a); }

    /// Make new recent files group with groupname gp
    FXRecentFiles(FXApp* a,const FXString& gp,FXObject *tgt=NULL,FXSelector sel=0){
      return new FXRbRecentFiles(a,gp,tgt,sel);
      }
    }

  /// Get application
  FXApp* getApp() const;

  /// Change number of files we're tracking
  void setMaxFiles(FXint mx);

  /// Return the maximum number of files being tracked
  FXint getMaxFiles() const;

  /// Set group name
  void setGroupName(const FXString& name);

  /// Return group name
  FXString getGroupName() const;

  /// Change the target
  void setTarget(FXObject *t);

  /// Get the target
  FXObject *getTarget() const;

  /// Change the message
  void setSelector(FXSelector sel);

  /// Return the message id
  FXSelector getSelector() const;

  /// Obtain the filename at index
  FXString getFile(FXint index) const;

  /// Change the filename at index
  void setFile(FXint index,const FXString& filename);

  /// Append a file
  void appendFile(const FXString& filename);

  /// Remove a file
  void removeFile(const FXString& filename);

  /// Clear the list of files
  void clear();

  /// Destructor
  virtual ~FXRecentFiles();
  };


DECLARE_FXOBJECT_VIRTUALS(FXRecentFiles)

