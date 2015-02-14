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

class FXFileSelector;

%rename(setAllowPatternEntry) FXFileDialog::allowPatternEntry(FXbool);
%rename(getAllowPatternEntry) FXFileDialog::allowPatternEntry() const;

%rename(getShowHiddenFiles) FXFileDialog::showHiddenFiles() const;
%rename(setShowHiddenFiles) FXFileDialog::showHiddenFiles(FXbool showing);

%rename(getShowImages) FXFileDialog::showImages() const;
%rename(setShowImages) FXFileDialog::showImages(FXbool showing);

%rename("numPatterns") FXFileDialog::getNumPatterns() const;

%rename("navigationAllowed=") FXFileDialog::allowNavigation(FXbool navigable);
%rename("navigationAllowed?") FXFileDialog::allowNavigation() const;

/// File selection dialog
class FXFileDialog : public FXDialogBox {
public:
  %extend {
    /// Construct file dialog box
    FXFileDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=500,FXint h=300){
      return new FXRbFileDialog(owner,name,opts,x,y,w,h);
      }

    /// Construct free-floating file dialog box
    FXFileDialog(FXApp* a,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=500,FXint h=300){
      return new FXRbFileDialog(a,name,opts,x,y,w,h);
      }
    }

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
                rb_ary_push(result, to_ruby(*p));
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

  /// Return TRUE if showing hidden files
  FXbool showHiddenFiles() const;

  /// Show or hide hidden files
  void showHiddenFiles(FXbool showing);

  /// Return TRUE if image preview on
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

  /// Change File List style
  void setFileBoxStyle(FXuint style);

  /// Return File List style
  FXuint getFileBoxStyle() const;

  /// Allow or disallow navigation
  void allowNavigation(FXbool navigable);

  /// Is navigation allowed?
  FXbool allowNavigation() const;

  /// Open existing filename
  static FXString getOpenFilename(FXWindow* owner,const FXString& caption,const FXString& path,const FXString& patterns="*",FXint initial=0);

  %extend {
    // Open multiple existing files
    static VALUE getOpenFilenames(FXWindow* owner,
                                  const FXString& caption,
                                  const FXString& path,
                                  const FXString& patterns = "*",
                                  FXint initial = 0) {
        VALUE result = rb_ary_new();
        FXString *filenames = FXFileDialog::getOpenFilenames(owner, caption,
          path, patterns, initial);
        if (filenames) {
            register FXString *p = filenames;
            while ((*p) != FXString::null) {
                rb_ary_push(result, to_ruby(*p));
                p++;
            }
            delete [] filenames;
        }
        return result;
    }
  }

  /// Save to filename
  static FXString getSaveFilename(FXWindow* owner,const FXString& caption,const FXString& path,const FXString& patterns="*",FXint initial=0);

  /// Open directory name
  static FXString getOpenDirectory(FXWindow* owner,const FXString& caption,const FXString& path);

  /// Destructor
  virtual ~FXFileDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFileDialog)
DECLARE_FXID_VIRTUALS(FXFileDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXFileDialog)
DECLARE_FXWINDOW_VIRTUALS(FXFileDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXFileDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXFileDialog)

