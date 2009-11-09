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

class FXFileList;
class FXTextField;
class FXCheckButton;
class FXComboBox;
class FXDirBox;
class FXButton;
class FXIcon;
class FXMenuPane;


/// File selection modes
enum {
  SELECTFILE_ANY,             /// A single file, existing or not (to save to)
  SELECTFILE_EXISTING,        /// An existing file (to load)
  SELECTFILE_MULTIPLE,        /// Multiple existing files
  SELECTFILE_MULTIPLE_ALL,    /// Multiple existing files or directories
  SELECTFILE_DIRECTORY        /// Existing directory
  };


// Rename these methods
%rename("associations=")		FXFileSelector::setAssociations(FXFileDict*,FXbool);
%rename("associations")		    FXFileSelector::getAssociations() const;
%rename("draggableFiles=")		FXFileSelector::setDraggableFiles(FXbool);
%rename("draggableFiles?")		FXFileSelector::getDraggableFiles() const;
%rename(setReadOnlyShown)		FXFileSelector::showReadOnly(FXbool show);
%rename(getReadOnlyShown)		FXFileSelector::shownReadOnly() const;
%rename(setAllowPatternEntry)	FXFileSelector::allowPatternEntry(FXbool);
%rename(getAllowPatternEntry)   FXFileSelector::allowPatternEntry() const;
%rename(getShowHiddenFiles)		FXFileSelector::showHiddenFiles() const;
%rename(setShowHiddenFiles)		FXFileSelector::showHiddenFiles(FXbool showing);
%rename(getShowImages)			FXFileSelector::showImages() const;
%rename(setShowImages)			FXFileSelector::showImages(FXbool showing);
%rename("navigationAllowed=")   FXFileSelector::allowNavigation(FXbool navigable);
%rename("navigationAllowed?")   FXFileSelector::allowNavigation() const;
%rename("numPatterns")			FXFileSelector::getNumPatterns() const;

/// File selection widget
class FXFileSelector : public FXPacker {
public:
  long onCmdAccept(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFilter(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdItemDblClicked(FXObject*,FXSelector,void* PTR_INT);
  long onCmdItemSelected(FXObject*,FXSelector,void* PTR_INT);
  long onCmdItemDeselected(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDirTree(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdHome(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdWork(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBookmark(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdVisit(FXObject*,FXSelector,void* PTR_CSTRING);
  long onCmdNew(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdNew(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRename(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCopy(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMove(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLink(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRemove(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSelected(FXObject*,FXSelector,void* PTR_IGNORE);
  long onPopupMenu(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdImageSize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdImageSize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdNavigable(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_FILEFILTER=FXPacker::ID_LAST,
    ID_ACCEPT,
    ID_FILELIST,
    ID_DIRECTORY_UP,
    ID_DIRTREE,
    ID_NORMAL_SIZE,
    ID_MEDIUM_SIZE,
    ID_GIANT_SIZE,
    ID_HOME,
    ID_WORK,
    ID_BOOKMARK,
    ID_BOOKMENU,
    ID_VISIT,
    ID_NEW,
    ID_RENAME,
    ID_COPY,
    ID_MOVE,
    ID_LINK,
    ID_REMOVE,
    ID_LAST
    };
public:
  %extend {
    /// Constructor
    FXFileSelector(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbFileSelector(p,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return a pointer to the "Accept" button
  FXButton *acceptButton() const;

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const;

  /// Change file name
  void setFilename(const FXString& path);

  /// Return file name, if any
  FXString getFilename() const;

  %extend {
    // Return list of selected file names.
    VALUE getFilenames() const {
        VALUE result = rb_ary_new();
        FXString *filenames = self->getFilenames();
        if (filenames) {
            register FXString *p = filenames;
            while ((*p) != FXString::null) {
                rb_ary_push(result, rb_str_new2((*p).text()));
		p++;
            }
	    delete [] filenames;
        }
        return result;
    }
  }

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
  %extend {
    // Takes an array of strings as described above
    void setPatternList(VALUE ary) {
      FXString patterns;
      if(TYPE(ary)==T_STRING){
        patterns=FXString(StringValuePtr(ary));
        }
      else if(TYPE(ary)==T_ARRAY){
        for(long i=0; i<RARRAY_LEN(ary); i++){
          VALUE obj=rb_ary_entry(ary,i);
          Check_Type(obj,T_STRING);
          patterns+=FXString(StringValuePtr(obj))+FXString("\n");
          }
        }
      else{
        rb_raise(rb_eArgError,"expected either a string, or an array of strings, as input");
        }
      self->setPatternList(patterns);
      }

    /// Return list of patterns
    VALUE getPatternList() const {
      FXString pat;
      FXString patterns;
      VALUE ary;
      patterns=self->getPatternList();
      ary=rb_ary_new();
      for(FXint start=0;!(pat=patterns.section('\n',start)).empty();start++){
	rb_ary_push(ary,to_ruby(pat.text()));
        }
      return ary;
    }
  }

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
  void allowPatternEntry(FXbool allow);

  /// Return TRUE if pattern entry is allowed
  FXbool allowPatternEntry() const;

  /// Change directory
  void setDirectory(const FXString& path);

  /// Return directory
  FXString getDirectory() const;

  /**
  * Given filename pattern of the form "GIF Format (*.gif)",
  * returns the pattern only, i.e. "*.gif" in this case.
  * If the parentheses are not found then returns the entire
  * input pattern.
  */
  static FXString patternFromText(const FXString& pattern);

  /**
  * Given a pattern of the form "*.gif,*.GIF", return
  * the first extension of the pattern, i.e. "gif" in this
  * example. Returns empty string if it doesn't work out.
  */
  static FXString extensionFromPattern(const FXString& pattern);

  /// Set the inter-item spacing (in pixels)
  void setItemSpace(FXint s);

  /// Return the inter-item spacing (in pixels)
  FXint getItemSpace() const;

  /// Change file list style
  void setFileBoxStyle(FXuint style);

  /// Return file list style
  FXuint getFileBoxStyle() const;

  /// Change file selection mode
  void setSelectMode(FXuint mode);

  /// Return file selection mode
  FXuint getSelectMode() const;

  /// Change wildcard matching mode
  void setMatchMode(FXuint mode);

  /// Return wildcard matching mode
  FXuint getMatchMode() const;

  /// Return TRUE if showing hidden files
  FXbool showHiddenFiles() const;

  /// Show or hide hidden files
  void showHiddenFiles(FXbool showing);

  /// Return TRUE if image preview on+
  FXbool showImages() const;

  /// Show or hide preview images
  void showImages(FXbool showing);

  /// Return images preview size
  FXint getImageSize() const;

  /// Change images preview size
  void setImageSize(FXint size);

  /// Show readonly button
  void showReadOnly(FXbool show);
  
  /// Return TRUE if readonly is shown
  FXbool shownReadOnly() const;
  
  /// Set initial state of readonly button
  void setReadOnly(FXbool state);

  /// Get readonly state
  FXbool getReadOnly() const;

  /// Allow or disallow navigation
  void allowNavigation(FXbool navigable);
  
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

  /// Destructor
  virtual ~FXFileSelector();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFileSelector)
DECLARE_FXID_VIRTUALS(FXFileSelector)
DECLARE_FXDRAWABLE_VIRTUALS(FXFileSelector)
DECLARE_FXWINDOW_VIRTUALS(FXFileSelector)

