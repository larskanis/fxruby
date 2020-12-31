## 1.6.44 / 2020-12-31

* Add binary gem support for ruby-3.0. #66
* Drop support for ruby-2.2

## 1.6.43 / 2020-11-27

* Make FXRuby compatible to ruby-3.0
* Migration to the `opengl-bindings` gem.
  The `opengl` gem is deprecated since years and no longer maintained.
  `opengl-bindings` is the announced successor.
* Add an alternative location for API documentation: https://larskanis.github.io/fxruby/
  This is because https://rubydoc.info is too often down.
* Fix Canvas::ImageShape and shape selection. #60
  This changes the position the text of TextShape is printed on the canvas.

## 1.6.42 / 2020-02-01

* Fix a packing issue in 1.6.41: `lib/fox16/input.rb` had owner permission only.

## 1.6.41 / 2020-01-26

* Add support for Ruby-2.7
* Fix build error on FreeBSD. #51
* Fix handling of scroll events to FXText instance.
* Add 8 virtual methods of FXText to be passed through ruby.
* FXText#findText: Return multi entry array only when searching Regex.
* Fix several example apps in example/ dir.
* Update to rake-compiler-dock-1.0 and use parallel cross build.
* Update to libpng-1.6.37, jpeg-turbo-2.0.4, libtiff-4.1.0 on Windows binary gem.

## 1.6.40 / 2018-12-28

* Fix some library classes which failed, when Fox was not included into the global namespace.
* Add new accessor FXImage#dataPtr to access raw image data from FFI, Fiddle or OpenGL.
* Ensure zero terminated strings in values of C-argv.
* Remove various Ruby and C++ warnings.
* Update libfox to 1.6.57.
* Add support for RubyInstaller-2.6
* Set minimum required ruby version to 2.2.

## 1.6.39 / 2017-12-26

* Fix FXGLVisual.supported and .supported?
* Add support for RubyInstaller-2.5

## 1.6.38 / 2017-07-27

* Update dependent libraries for Windows binary gem.
* Replace libjpeg-9b by libjpeg-turbo-1.5.2 on Windows binary gem.
* Fix build with clang on FreeBSD (and possibly other OS). Fixes #41

## 1.6.37 / 2017-06-24

* Add a 3rd type of FXRbObjects which is used for callbacks. Fixes #39

## 1.6.36 / 2017-06-04

* Support the fxruby source gem on Windows (only RubyInstaller-2.4).
* Replace our self-made directory search methods by pgk-config.
* Enable the use of Win32 unicode functions. Fixes #30 and #38
* Fix segfault in vsprintf on Windows 10.
* Update support for RubyInstaller-2.4.1-1
* Update to libjpeg-9b
* More automation for gem releases

## 1.6.35 / 2017-02-15

* Adjust for Ruby-2.4 with unified Integers
* Add support for RubyInstaller-2.4
* Drop support for Ruby-1.8 and 1.9. It may work with them, but is no longer tested.
* Add compat with SWIG-3.0
* Fix an issue with FXApp#removeInput introduced in fxruby-1.6.30.
* Work around missing /usr/lib/libfxscintilla.so file in Ubuntu
* Update dependent gems.
* Update libraries for Windows build.

## 1.6.34 / 2016-04-26

* Add support for RubyInstaller-2.3
* Avoid RARRAY_PTR() which broke fxruby on ruby-2.3.0.
* Make use of StringValueCStr() where it is suitable.
* Fix initialisation of runOnUiThread event handler, when FXApp is called with a block.
* Disable GVL on RubyInstaller-1.9.3. Fixes #24

## 1.6.33 / 2015-08-20

* Avoid rb_* calls that are prohibited during GC. Fixes #23
* Use copy'ing getters for FXVec members in FXMat*, FXMaterial and FXLight.
  This fixes the TC_FXMaterial#test_bug test case.
* Fix test suite, so that all tests pass.
* Add a travis-ci test setup and connect it to the github account.

## 1.6.32 / 2015-08-07

* Avoid call to rb_class2name() during GC. Fixes #21
* Use release mode, unless extconf.rb is called with --enable-debug,
  so that all FXTRACE() and FXASSERT() calls are skiped, per default.
* Remove self made GC detection by ruby's rb_during_gc().
* Fix Windows binary x86-mingw32.gem for Ruby versions < 2.0

## 1.6.31 / 2015-07-21

* Replace pipe2() by pipe() and fcntl(), because pipe2() is not as portable.
* Add missing include statement. Fixes #20

## 1.6.30 / 2015-07-07

* Fix crashes in rb_gc_mark(): 0x00000003f54af8 is T_ZOMBIE / T_NONE
* Release Ruby's GVL while calls to FXImage#savePixels, #loadPixels
  and FXApp#run* methods.
* Add a working version for FXApp#addInput event handling on Windows.
  This works for sockets only for now.
* Add FXApp#runOnUiThread and FXId#runOnUiThread .
  This allows to safely execute GUI code from other threads.
* Use rake-compiler-dock for building windows binary gems.

## 1.6.29 / 2015-02-17

* Add Windows binaries for Ruby-2.1 and 2.2.
* Use shared libs for Windows binary gems to reduce gem size.
* Allow non owned assignment of image data to FXImage derivations
  without copy'ing pixel data.
* Allow retrival of parts of the pixel data.
* Fix namespace specifier for FXRGB in kwargs.rb.
* Change GC'ing of TreeListBox and FXTreeItem. Fixes #10
* Update to swig version 2.0 or newer. Fixes #13

## 1.6.28 / 2013-07-05

* Fix build for Ruby-2.0.0-p127+
* Update libraries for win32 build: libfox-1.6.49

## 1.6.27 / 2013-04-05

* Add support for Ruby-2.0.
* Add cross compilation for x64-mingw32 target.

## 1.6.26 / 2013-02-16

* Mark all text strings retrieved from fox as UTF-8 when running on Ruby 1.9
* Fix loading error on Ruby 1.8.7 by renaming the C++ extension to fox16_c
* Update libraries for windows cross compilation

## 1.6.25 / 2012-06-17

* Windows: Fix slow loading of fox16.so by using a more recent mingw-w64 compiler
  (reported by Allen Doug and Igor Jorobus)
* Fix two possible segfaults in conjunction with FXSplashWindow (reported by Igor Jorobus)

## 1.6.24 / 2012-06-06

* Update libraries for win32 build: libz-1.2.7 libpng-1.5.10 libjpeg-8d libtiff-4.0.1 libfox-1.6.45
* Avoid Segfauls in lots of methods when called with nil instead of FXApp, FXComposite or FXWindow objects

## 1.6.23 / 2012-03-08

* Add YARD documentation support
* Use generated Manifest.txt
* Support for parallel task execution with drake

## 1.6.22 / 2012-02-21

* Allow better access to raw pixel data of FXImage and derivatives
* Build Windows binary gem per cross compiler on Linux
* Add support for Rubinius (currently requires rubinius from git)
* Add alias FXApp#modalWindow, as described in rdoc
* Add quality parameter to FXJPGImage and FXJPGIcon
* Fix invalid memory access in final GC call when using FXMenuCommand with acckey
* Fix double referenced foxObj when borrowed object registration is triggered from C++
* Fix Segfault while GC'ing FXWindows
* Fix 'object allocation not allowed while garbage collection' bug
* Fix clipboard handling on windows
* Add missing namespace qualifier to FXSEL in FXAccelTable
* Fix GC bug in FXAccelTable
* Fix double free in FXMemoryStream#giveBuffer
* Fix invalid memory access in typemap to zero terminated FXchar* (such as fillItems methods)
* Fix FXApp#addInput for Ruby 1.9 on Linux
* Fix "ruby_code case not handled: Regexp" issue with newer rubygems

## Changes For Version 1.6.20 (November 09, 2009)

* Integrated the Hoe and rake-compiler extensions into the Rakefile and
  removed redundant tasks.
* Did some work to provide support for MinGW builds.
* The previous release of FXRuby couldn't be built from source against Ruby 1.9.1 final
  due to a change in some of the file-related utility libraries
  (see RubyForge Bug #23786). This problem has been corrected.


## Changes For Version 1.6.19 (March 6, 2009)

* The previous release of FXRuby couldn't be built from source against Ruby 1.9.1 final
  due to a change in some of the file-related utility libraries
  (see RubyForge Bug #23786). This problem has been corrected.
* The previous release of FXRuby couldn't be built from source against Ruby versions 1.8.5 or
  earlier (see RubyForge Bug #23967). This problem has been corrected.
* A change in the return value for Ruby's `instance_variables` method broke
  some of the code related to message handling in FXRuby (see RubyForge
  Bug #23787). This problem has been corrected.
* The `addAccel` method for the `FXAccelTable` class
  now accepts lambda functions (or any other objects that respond to `call`). See
  the API documentation
  for `FXAccelTable` for examples of how this works.


## Changes For Version 1.6.18 (December 29, 2008)

* Some users were having trouble building FXRuby on 64-bit operating systems
  (see RubyForge Bug #23375). This problem has been corrected.


## Changes For Version 1.6.17 (December 24, 2008)

* The Ruby interpreter was generating a large number of warning messages about redefined methods
  in the `kwargs.rb` library
  (see RubyForge
  Bug #19231 and elsewhere). This problem has been corrected.

* Due to recent changes in Ruby's garbage collection algorithm, FXRuby applications could under some circumstances
  crash for large numbers of table items
  (see RubyForge bugs ).
  This bug has been fixed.

* The documentation for the `FXTable` class referred to the non-existent `setColumnX`
  and `setRowY` instance methods
  (see RubyForge
  Bug #21987). These entries have been removed from the documentation.

* A number of instance methods for the `FXTable` class could crash an application if they
  were passed out-of-bounds index arguments
  (see RubyForge
  Bug #21987). These methods now raise `IndexError` when they're passed out-of-bounds
  indexes.

* Due to a change in the URL scheme for the Dilbert web site, the `dilbert.rb` example
  program was no longer working properly
  (see RubyForge
  Bug #21538). This has been fixed.

* The `lower` method for the `FXRangef` was returning
  ´self´ instead of an `FXVec3f` instance for the range's low
  bound
  (see RubyForge
  Bug #22488). This has been fixed.

* Made a number of minor fixes for compatibility with Ruby 1.9.1.


## Changes For Version 1.6.16 (July 3, 2008)

* Historically, if you called `create` on a
  window before its parent window was created, your application would
  crash (see RubyForge
  Bug #20702 and elsewhere). Now, the code should raise a
  ´RuntimeError´ with a message indicating the
  problem.

* The message data that the `FXPicker` widget
  sends along with its ´SEL_CHANGED´ and
  ´SEL_COMMAND´ messages wasn't being handled
  properly, and as a result, applications using this widget could crash
  (see RubyForge
  Bug #20780). This problem has been fixed.


## Changes For Version 1.6.15 (June 4, 2008)

* FXRuby applications could crash (with a segmentation fault) if
  ´nil´ was passed in as the first argument to
  `FXDialogBox.new` or
  `FXMainWindow.new` (see RubyForge
  Bug #14642). These methods now raise an
  ´ArgumentError´ if ´nil´ is
  passed as the first argument.

* You should only ever construct one `FXApp`
  object per application, but there was no protection against doing so
  in the code (see RubyForge
  Bug #16275). Now, `FXApp.new` will
  raise a `RuntimeException` if an
  `FXApp` object already exists.

* The `babelfish.rb` example program, which
  previously depended on an external web service to perform translation
  between languages, was broken since that web service no longer exists
  (see RubyForge
  Bug #16962). The example has now been updated to use Dr. Nic's
  Tranexp library instead.

* The value of the ´MBOX_SAVE_CANCEL_DONTSAVE´
  option (for the `FXMessageBox` class) wasn't
  wrapped properly and was unusable (see RubyForge
  Bug #17094). There was also no constant corresponding to the
  ´MBOX_CLICKED_DONTSAVE´ return value. Both of these
  problems have been fixed.

* The fields for new `FXHiliteStyle` objects
  were uninitialized and as a result sometimes gave unpredictable
  results (see RubyForge
  Bug #19637). This has been fixed.

* The `columnHeaderFont` and
  `rowHeaderFont` attributes for
  `FXTable` weren't implemented properly (see
  RubyForge
  Bug #20142). This has been fixed.

* Ruby 1.8.7 adds a new `first` method to
  the `Enumerable` module, and this conflicts with
  the existing `first` method defined in the
  `FXWindow` base class for a number of FXRuby
  classes which mix in `Enumerable` (see RubyForge
  Bug #20418). This problem has been resolved.

* Due to a bug in the `extconf.rb` script, the
  build was failing for Ruby 1.9.0 (see RubyForge
  Bug #20426). This has been fixed.


## Changes For Version 1.6.14 (March 29, 2008)

* Updated the documentation for the `FXImage`
  class to indicate which methods call `render`
  after they're finished, and which ones do not.

* Corrected a little typo in the
  `gembrowser.rb` example program.

* Updated the `dilbert.rb` example program to
  use the more popular-and-likely-to-be-installed Hpricot HTML
  parser library instead of Rubyful Soup.

* Re-added the documentation for the
  ´TOGGLEBUTTON_KEEPSTATE´ option, which had
  mysteriously disappeared (see RubyForge
  Bug #2286).

* Made a number of minor fixes to support building FXRuby against
  Ruby 1.9.

* Added a binary gem for OS X. This works with the Ruby that's
  included with OS X (Leopard).

* The binary gem for Windows was built with FOX version 1.6.32 and
  FXScintilla version 1.71.


## Changes For Version 1.6.13 (November 9, 2007)

* Calls to the `extractText` method for the
  `FXTable` class were causing various
  memory-related errors on certain platforms (see RubyForge
  Bug #15444). This problem has been fixed.

* The binary gem for Windows was built with FOX version 1.6.28 and
  FXScintilla version 1.71.

## Changes For Version 1.6.12 (October 19, 2007)

* The API documentation for `FXMDIClient`
  referred to the non-existent instance method
  `activeChild=` (see RubyForge
  Bug #10259). This method has been added.

* The API documentation for `FXMDIClient`
  also referred to the non-existent instance methods
  `getMDIChildFirst` and
  `getMDIChildLast`. These entries have been
  removed.

* The API documentation for `FXMDIChild`
  referred to non-existent instance methods
  `getMDINext` and
  `getMDIPrev` (see RubyForge
  Bug #10436). The documentation has been corrected.

* Added the ´:repeat´ parameter for the
  `addChore` and
  `addTimeout` methods. See the documentation for
  more details, and `gltest.rb` for an example of its
  use.

* Corrected a number of minor typos in the API
  documentation.

* Corrected a typo in the `imageviewer.rb`
  example.

* Modified the `inputs.rb` example program to
  use `Pipe.read_nonblock()` instead of
  `Pipe.read()`.

* Fixed a bug in the implementation of the
  `findText` method for the
  `FXText` class, when used with the
  ´SEARCH_REGEX´ option.

* The binary gem for Windows was built with FOX version 1.6.28 and
  FXScintilla version 1.71.


## Changes For Version 1.6.11 (April 18, 2007)

* Added `editable` as an alias for
  `FXTextField#editable?`.

* Added `each_child_recursive` instance
  method for the `FXWindow` class. This method
  performs a depth-first traversal of the widget tree starting at the
  receiver window.

* Corrected some errors in the keyword arguments support for the
  `FXVec2d`, `FXVec2f`,
  `FXVec3d`, `FVec3f`,
  `FXVec4d` and `FXVec4f`
  classes.

* Corrected an error in the keyword arguments support for the
  `FXIconDict` class.

* Modified the gem specification so that the RDoc generated during
  a gem install is consistent with that generated by other methods (see
  RubyForge
  Bug #10035).

* Changes to the `iterators` library in version
  1.6.6 introduced a bug in the `each` method for
  the `FXFoldingList`,
  `FXTreeList` and
  `FXTreeListBox` classes (see RubyForge
  Bug #10175). This problem has been fixed.

* Applied submitted patches for building FXRuby against Ruby 1.9
  (see RubyForge
  Bug #10181). Please note that building FXRuby against the Ruby
  1.9 code base is still officially unsupported; however, I'm glad to
  accept patches that will help make this possible.

* The binary gem for Windows was built with FOX version 1.6.25 and
  FXScintilla version 1.71.


## Changes For Version 1.6.9 (April 8, 2007)

* A bug was discovered in the keyword arguments library support
  for the `FXMenuBar` class (see RubyForge
  Bug #9927). This problem has been fixed.

* The binary gem for Windows was built with FOX version 1.6.25 and
  FXScintilla version 1.71.


## Changes For Version 1.6.8 (April 5, 2007)

* Due to an internal bookkeeping error, applications like the
  `glviewer.rb` example program which create multiple
  `FXGLViewer` instances could cause an assertion
  to fail. When this assertion fails on Windows, the program simply
  crashes (see RubyForge
  Bug #9775). This problem has been fixed.

* The keyword arguments library, introduced in version 1.6.5, is
  now included automatically when you load FXRuby; it is no longer
  necessary to explicitly require it.

* The binary gem for Windows was built with FOX version 1.6.25 and
  FXScintilla version 1.71.


## Changes For Version 1.6.7 (March 31, 2007)

* The binary gem for Windows was built with FOX version 1.6.25 and
  FXScintilla version 1.71.


## Changes For Version 1.6.6 (February 10, 2007)

* Somewhere along the way, the RAA browser example program got
  broken due to changes in the SOAP interface to RAA (see RubyForge
  Bug #7977). This has been fixed.

* Some debugging code that was meant to detect errors in FXRuby
  message data conversion was inadvertently causing some user
  applications to crash when running under Windows (see RubyForge
  Bug #8049). This debugging code has been changed to avoid the
  problem.

* Modified the implementations of the each iterator methods for
  `FXFoldingList`,
  `FXFoldingItem`,
  `FXTreeItem`, `FXTreeList`
  and `FXTreeListBox` (see RubyForge
  Bug #8090). The new implementation is a bit more robust in
  terms of modifications (such as deletion) of the iterated-over
  elements.

* A bug in the new keyword arguments library (introduced in
  version 1.6.5) caused the `initialize` method
  for the `FXDCWindow` class to do the wrong thing
  (see RubyForge
  Bug #8441). This has been corrected.

* A different bug in the keyword arguments library caused the
  `initialize` method for the
  `FXFont` class to do the wrong thing (see RubyForge
  Bug #8517). This also has been corrected.

* Yet another bug in the keyword arguments library broke the part
  of the code that used to yield ´self´ to an
  optional block attached to the call to `new`
  (see RubyForge
  Bug #8518). This has been corrected.

* Most of the FXRuby example programs have been updated to use the
  keyword arguments library.

* Added a new "virtual" keyword argument
  ´:padding´ that can be used in place of (or in
  addition to) the ´:padLeft´,
  ´:padRight´, ´:padTop´ and
  ´:padBottom´ arguments for a constructor. When a
  ´:padding´ value is passed in to the arguments
  hash, that value will be used for any of the four regular padding
  values that aren't otherwise specified. See the example programs for,
  you know, examples.

* The binary gem for Windows was built with FOX version 1.6.20 and
  FXScintilla version 1.71.


## Changes For Version 1.6.5 (January 20, 2007)

* Clicking outside of the visible cells for an
  `FXTable` when there was no current selection
  caused the code to raise an exception (see RubyForge
  Bug #5907). This problem has been fixed.

* The `hasTimeout?` method for the
  `FXApp` class was implemented incorrectly (see
  RubyForge
  Bug #7564). This problem has been fixed.

* The `FXFoldingList` and
  `FXFoldingItem` classes did not have each
  iterator methods like most of the other list-based widgets (see RubyForge
  Patch #7978). These have been added.

* The API documentation for `FXMDIClient`
  claimed that `FXScrollArea` was its base class
  (see RubyForge
  Bug #7979). This has been corrected; the base class for
  `FXMDIClient` is
  `FXComposite`.

* There was a small typo in the documentation for the
  `FXFoldingList` class options (see RubyForge
  Bug #7981). This has been fixed.

* Added preliminary support for keyword-style arguments, as
  described in the "Differences Between
  FOX and FXRuby" section of the FXRuby User's Guide.

* The binary gem for Windows was built with FOX version 1.6.20 and
  FXScintilla version 1.71.


## Changes For Version 1.6.4 (November 30, 2006)

* A change made in Ruby 1.8.5 for cyclic requires led to a problem
  that caused the Ruby interpreter to emit a large number of warnings
  (see RubyForge
  Bug #5633). This problem has been fixed.

* The binary gem for Windows was built with FOX version 1.6.16 and
  FXScintilla version 1.71.


## Changes For Version 1.6.3 (October 27, 2006)

* Widgets of some classes (namely
  `FXTopWindow` and
  `FXMDIChild`) weren't properly sending a
  ´SEL_CLOSE´ message to their message targets (see
  RubyForge
  Bug #5498). Thanks to a change in FOX version 1.6.16, this
  problem has been fixed.

* The `getControlFor` method for the
  `FXComboTableItem` class was coded incorrectly
  (see RubyForge
  Bug #5906). This has been fixed.

* There was a minor typo in the API documentation for the
  `FXTriStateButton` class (see RubyForge Bug #5962). This has been fixed.

* The `each_row` and
  `each_column` iterator methods for the
  `FXTable` class were incorrectly coded (see
  RubyForge
  Bug #6036). This has been fixed.

* The `new` class methods for
  `FXColorItem`, `FXDirItem`,
  `FXFileItem`,
  `FXFoldingItem`,
  `FXHeaderItem`,
  `FXIconItem`, `FXListItem`
  and `FXTreeItem` were all raising exceptions when
  a non-´nil´ value was passed in for the last
  argument (see RubyForge
  Bug #6197). A similar problem was present for various instance
  methods in the `FXColorList`,
  `FXListBox` and
  `FXMDIClient` classes. These problems have been
  fixed.

* A few problems were discovered for the
  `inputs.rb` example program (see RubyForge
  Bug #6209). These problems have been fixed.

* Several instance methods for the `FXTable`
  class were not actually present under their documented names (see
  RubyForge
  Bug #6211). This has been fixed.

* The build script was not compatible with changes made in the
  recently-released FXScintilla 1.71 (see RubyForge
  Bug #6313). This has been fixed.

* The binary gem for Windows was built with FOX version 1.6.16 and
  FXScintilla version 1.71.


## Changes For Version 1.6.2 (September 13, 2006)

* The `expandTree()` and
  `collapseTree()` methods for the
  `FXFoldingList` class were incorrectly identified
  as `expandFolding()` and
  `collapseFolding()` in the API documentation
  (see RubyForge
  Bug #5354). This has been fixed.

* The `FXDockTitle` class was not supported
  (see RubyForge
  Bug #5632). This has been fixed.

* The API documentation for the `FXGLCanvas`
  class claimed it had a `shared?` method, but it
  didn't (see RubyForge
  Bug #5591). Now it does.

* The `FXGradientBar` class was not supported
  (see RubyForge
  Bug #5746). This has been fixed.

* The binary gem for Windows was built with FOX version 1.6.14 and
  FXScintilla version 1.67 (from CVS).


## Changes For Version 1.4.7 (September 13, 2006)

* The `children` instance method for the
  `FXWindow` class always returned an array of
  `FXWindow` instances, even if the actual types
  should have been instances of subclasses of
  `FXWindow` (see RubyForge
  Bug #4342). This has been fixed.

* The `dilbert.rb` example program was broken
  due to a change in the Dilbert.com web site structure (see RubyForge
  Bug #4597). This has been fixed.

* The `expandTree()` and
  `collapseTree()` methods for the
  `FXFoldingList` class were incorrectly identified
  as `expandFolding()` and
  `collapseFolding()` in the API documentation
  (see RubyForge
  Bug #5354). This has been fixed.

* The `FXDockTitle` class was not supported
  (see RubyForge
  Bug #5632). This has been fixed.

* The API documentation for the `FXGLCanvas`
  class claimed it had a `shared?` method, but it
  didn't (see RubyForge
  Bug #5591). Now it does.

* The `FXGradientBar` class was not supported
  (see RubyForge
  Bug #5746). This has been fixed.

* The binary gem for Windows was built with FOX version 1.4.34 and
  FXScintilla version 1.63.


## Changes For Version 1.6.1 (July 21, 2006)

* The message data sent along for the
  ´SEL_INSERTED´, ´SEL_DELETED´
  and ´SEL_REPLACED´ messages from an a
  `FXText` widget to its target was not being
  converted properly (see RubyForge
  Bug #4666). This has been fixed.

* The code related to the localization of application messages in
  FOX wasn't implemented properly in FXRuby, and as a result,
  constructing certain dialogs (like the color dialog) could cause a
  program to crash (see RubyForge
  Bug #5000). This has been fixed.

* The "Stop Spin" button in the gltest.rb example program didn't
  stop the cubes from spinning after either the "Spin Timer" or "Spin
  Chore" option was selected (see RubyForge
  Bug #5001). This was actually a symptom of a larger problem,
  that FXRuby wasn't properly handling timers and chores. These problems
  have been fixed.

* Setting the current item for an
  `FXComboBox` to -1 (to indicate that there's no
  current item) would cause FXRuby to erroneously raise an
  `IndexError` (see RubyForge
  Bug #5007). This has been fixed.

* The documentation for the `reparent`
  instance method for the `FXWindow` class was
  incorrect (see RubyForge
  Bug #5035). This has been fixed.

* The `textedit.rb` example program was not up
  to date with some of the changes for FOX 1.6. This example has been
  updated.

* The new `font` method for the
  `FXFont` class was not documented. This has been
  fixed.

* The `dilbert.rb` example program has been
  modified to use the RubyfulSoup HTML library instead of the
  html-parser library.

* As discussed in various forums (see for example [this
  post](http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-talk/182827), the `autorequire` directive for
  RubyGems specifications is now deprecated. As a result, this has been
  removed from the FXRuby gem specification. This change will break any
  code that was using a statement like:´require_gem 'fxruby'´as
  the sole means for loading FXRuby. Such programs should instead
  use:´require 'fox16'´which will work
  for either gem based or non-gem based installations.

* The binary gem for Windows was built with FOX version 1.6.8 and
  FXScintilla version 1.67 (from CVS).


## Changes For Version 1.6.0 (May 29, 2006)

* This is the first release of FXRuby compatible with FOX version
  1.6. One of the most signficant changes for FOX 1.6 has been the
  addition of Unicode support; all FOX widgets and internal string
  processing routines are now Unicode aware. For a comprehensive
  overview of the changes made to FOX since version 1.4 (including those
  made in the FOX 1.5 development series), please refer to the
  [News archives](http://www.fox-toolkit.com/news.html) at
  the FOX web site.

* Added the `allowSide`,
  `disallowSide` and
  `allowedSide?` methods for the
  `FXDockBar` class, as complements to the
  `allowedSides` accessor methods (see RubyForge
  Feature Request #2307).

* Added the `visible=` and
  `visible?` accessor methods for the
  `FXWindow` class, as complements to the
  `show`, `hide` and
  `shown?` methods (see RubyForge
  Feature Request #3579).

* The `browser.rb` example was making use of a
  deprecated API (see RubyForge
  Bug #4325). This has been fixed.

* The `children` instance method for the
  `FXWindow` class always returned an array of
  `FXWindow` instances, even if the actual types
  should have been instances of subclasses of
  `FXWindow` (see RubyForge
  Bug #4342). This has been fixed.

* The `dilbert.rb` example program was broken
  due to a change in the Dilbert.com web site structure (see RubyForge
  Bug #4597). This has been fixed.

* The binary gem for Windows was built with FOX version 1.6.5 and
  FXScintilla version 1.67 (from CVS).


## Changes For Version 1.4.6 (April 26, 2006)

* FXRuby would not compile properly on some x86-64 systems (see
  RubyForge
  Bug #3729). This error has been corrected. Thanks to Javier
  Goizueta for initially reporting this problem, and especially to
  Tobias Peters for providing a patch.

* The `FXIconDict` widget was accidentally
  "lost" in the transition between FXRuby versions 1.2 and 1.4 (see
  RubyForge
  Bug #4117). This error has been corrected. Thanks to Manfred
  Usselmann for reporting this problem.

* The `FXSwitcher` widget was not sending the
  appropriate message data to its message target for the
  ´SEL_COMMAND´ message type (see RubyForge
  Bug #4157). This error has been corrected. Thanks to Manfred
  Usselmann for reporting this problem.

* The `FXSeparator` class wasn't implemented
  properly (see RubyForge
  Bug #4158). This error has been corrected. Thanks to Gerard
  Menochet for reporting this problem.

* The `findItemByData` method was
  implemented incorrectly for the `FXComboBox`,
  `FXFoldingList`,
  `FXIconList`, `FXList` and
  `FXListBox` classes (see RubyForge
  Bug #4172). This error has been corrected. Thanks to Gerard
  Menochet for reporting this problem.

* The `FXListBox` widget was not sending the
  appropriate message data to its message target for the
  ´SEL_COMMAND´ message type (see RubyForge
  Bug #4255). This error has been corrected. Thanks to Gerard
  Menochet for reporting this problem.

* The binary gem for Windows was built with FOX version 1.4.29 and
  FXScintilla version 1.63.


## Changes For Version 1.4.5 (April 10, 2006)

* The `FXTextField` class was not properly
  responding to the ´ID_INSERT_STRING´ command (see
  RubyForge
  Bug #3320). This error has been corrected. Thanks to Uwe Hartl
  for reporting this problem.

* The `text` and
  `getText` methods for the
  `FXMenuCaption` class were returning
  ´nil´ instead of the actual value (see RubyForge
  Bug #3458). This error has been corrected. Thanks to Meinrad
  Recheis (Henon) for reporting this problem.

* The API documentation for the `FXMDIChild`
  class erroneously listed ´SEL_CLOSEALL´ as one of
  the message types that an MDI child window might send to its message
  target (see RubyForge
  Bug #3508). This error has been corrected. Thanks to Meinrad
  Recheis (Henon) for reporting this problem.

* Calling the `selectRange` method for
  class `FXTable` would cause a fatal error instead
  of merely raising an `IndexError` exception (see
  RubyForge
  Bug #3615). This error has been corrected. Thanks to Meinrad
  Recheis (Henon) for reporting this problem.

* Due to an error in the SWIG interface files, the
  `FXChoiceBox` class was basically unusable (see
  RubyForge
  Bug #3676). This error has been corrected. Thanks to Uwe Hartl
  for reporting this problem.

* The API documentation for the
  `FXRealSlider` and
  `FXRealSpinner` classes erroneously claimed that
  the message data for the ´SEL_COMMAND´ and
  ´SEL_CHANGED´ messages sent by these widgets to
  their targets were integers (see RubyForge
  Bug #3749). Along the same lines, the message data for those
  widgets wasn't being converted correctly (see RubyForge
  Bug #3750). Both of these errors have been corrected. Thanks
  to Meinrad Recheis (Henon) for reporting these problems.

* The API documentation for the Fox module incorrectly listed the
  names of the `FXSELTYPE` and
  `FXSELID` methods as
  `SELTYPE` and `SELID`
  (see RubyForge
  Bug #3940). This error has been corrected. Thanks to Joel
  VanderWerf for reporting this problem.

* The `FXTableItem` constructor was supposed
  to (optionally) accept a reference to an arbitrary Ruby object as its
  third argument, but this wasn't working properly (see RubyForge
  Bug #4005). This error has been corrected. Thanks to Mark
  Volkman for reporting this problem.

* The binary gem for Windows was built with FOX version 1.4.29 and
  FXScintilla version 1.63.


## Changes For Version 1.4.4 (January 21, 2006)

* The build instructions for Unix platforms had not been updated
  recently and as such contained some errors (see RubyForge
  Bug #3014). These errors have been corrected. Thanks to Dave
  Burns for reporting this problem.

* The `extendSelection` method for the
  `FXTable` class was raising an exception if an
  out of bounds row or column index was passed in (see RubyForge
  Bug #3050). This has been changed so that
  `extendSelection` instead returns false for out
  of bounds arguments. Thanks to Leonid Moiseichuk for reporting this
  problem.

* The `each_child` iterator method for the
  `FXWindow` class would fail if the child window
  was destroyed in the block (see RubyForge
  Bug #3134). Thanks to Liam Irish for reporting this problem
  and providing a patch.

* The message data for the ´SEL_REPLACED´
  message sent by the `FXTable` class to its target
  was not being handled properly (see RubyForge
  Bug #3244). There were also problems with the message data for
  the ´SEL_SELECTED´ and
  ´SEL_DESELECTED´ messages. Furthermore, the
  ´SEL_REPLACED´ message was not documented in the
  RDoc documentation for the `FXTable` class. All
  of these problems have been corrected. Thanks to _blackdog for
  reporting this problem.

* The binary gem for Windows was built with FOX version 1.4.29 and
  FXScintilla version 1.63.


## Changes For Version 1.4.3 (November 7, 2005)

* The ´TOGGLEBUTTON_KEEPSTATE´ option for the
  `FXToggleButton` class was not documented (see
  RubyForge
  Bug #2286). This oversight has been corrected. Thanks to Tim
  Smith for reporting this problem.

* The `scintilla.rb` library file was not up to
  date with the latest FXScintilla release, and as a result it was
  missing some methods (see RubyForge
  Bug #2479). This oversight has been corrected. Thanks to Maxim
  Kulkin for reporting this problem.

* Due to changes in the APIs for timers and chores, the mechanisms
  for removing chores and timeouts were broken (see RubyForge
  Bug #2563). This bug has been fixed. Thanks to "moinker" for
  reporting this problem.

* An error in the test setup caused all of the tests for the
  `FXList` class to fail (see RubyForge
  Bug #2564). This bug has been fixed. Thanks to Peter for
  reporting this problem.

* Due to a bug in the test suite runner script, not all test cases
  were being exercised (see RubyForge
  Bug #2565). This bug has been fixed.

* Calling the `getPixel` method for the
  `FXImage` class when the client-side pixel buffer
  for the image has already been released would cause a program to crash
  (see RubyForge
  Bug #2611). Now, `getPixel` will raise
  an exception if it's called after the pixel buffer has been released.
  The documentation for `getPixel` has been
  updated accordingly. Thanks to Gonzalo Garramuno for reporting this
  problem.

* The `makePositionVisible` method for the
  `FXTable` class was raising an exception when
  passed out-of-bounds values for the row or column index (see RubyForge
  Bug #2660). This could happen, for example, if you were to
  click in a table area outside of the regular cells (which indirectly
  triggers a call to `makePositionVisible`). This
  was actually inconsistent with standard FOX behavior, which simply
  ignores out of bounds values for that method's arguments. This bug has
  been fixed, and the documentation for
  `makePositionVisible` has been updated
  accordingly. Thanks to Ralf Jonas for reporting this problem.

* The binary gem for Windows was built with FOX version 1.4.21 and
  FXScintilla version 1.63.


## Changes For Version 1.4.2 (August 22, 2005)

* Due to a bug in the implementation, the
  `checked?` method for the
  `FXCheckButton` class always returned
  ´false´ (see RubyForge
  Bug #1852). This bug has been fixed. Thanks to Meinrad Recheis
  for reporting this problem.

* The API documentation for the `FXTable`
  class listed several obsolete attributes (see RubyForge
  Bug #1928). Those errors have been corrected. Thanks to Pavel
  Sokolov for reporting these problems.

* There were a number of bugs in the
  `textedit.rb` example program (see RubyForge
  Bug #1979), and those bugs have been fixed. Thanks to Claude
  Marinier for reporting these problems.

* The API documentation for the `FXTreeList`
  class' `new` method still showed the number of
  visible items (´nvis´) as its second argument
  (see RubyForge
  Bug #2171). This problem has been corrected. Thanks to Bill
  Atkins for reporting this problem.

* The API documentation for the `FXTopWindow`
  class had a number of errors (see RubyForge
  Bug #2269). This problem has been corrected.

* The API documentation for the `FXTreeList`
  class still listed the obsolete `reparentItem`
  method (see RubyForge
  Bug #2270). This problem has been corrected. Thanks to Jacob
  Hansen for reporting this problem.

* Due to a bug in how the SWIG typemaps for the
  ´FXlong´ type were defined, some methods for the
  `FXFileStream` class were broken (see RubyForge
  Bug #2275). This problem has been corrected. Thanks to Gonzalo
  Garramuno for reporting this problem.

* Merged in all of the fixes for FXRuby 1.2.6.

* The binary gem for Windows was built with FOX version 1.4.17 and
  FXScintilla version 1.63.


## Changes For Version 1.4.1 (August 20, 2005)

* This is the second release of FXRuby which is compatible with
  FOX 1.4, and as such should be considered an "unstable" release. For a
  history of the changes made during the FOX 1.3 and 1.4 development,
  see the [News](http://www.fox-toolkit.com/news.html)
  page at the FOX Web site.

* The unit tests (in the `tests` subdirectory)
  had not been updated to require the ´fox14´
  feature, and were still looking at ´fox12´. This
  has been corrected.

* A number of minor problems were corrected for the Windows build
  of FXRuby.

* The binary gem for Windows was built with FOX version 1.4.17 and
  FXScintilla version 1.63.


## Changes For Version 1.4.0 (August 19, 2005)

* This is the first release of FXRuby which is compatible with FOX
  1.4, and as such should be considered an "unstable" release. For a
  history of the changes made during the FOX 1.3 and 1.4 development,
  see the [News](http://www.fox-toolkit.com/news.html)
  page at the FOX Web site.


## Changes For Version 1.2.6 (April 15, 2005)

* Some additional problems related to calling the
  `setTableSize` method for an
  `FXTable` were discovered (see RubyForge
  Bug #1597). This problem has been corrected. Thanks to Joel
  VanderWerf for reporting this problem.

* The `iconlist.rb` example program had a
  "Sort" pulldown menu filled with a number of commands that didn't
  really do anything, including sorting the items (see RubyForge
  Bug #1654). This pulldown menu has been removed from that
  example.

* The API documentation for the `FXDC` class
  erroneously referred to the `font` attribute as
  `textFont` (see RubyForge
  Bug #1667). This problem has been corrected. Thanks to Meinrad
  Recheis for reporting this problem.

* The `checked?`,
  `unchecked?` and
  `maybe?` methods for the
  `FXMenuCheck` class were missing (see RubyForge
  Bug #1677). This problem has been corrected. Thanks to Oliver
  Smith for reporting this problem.

* The API documentation for the
  `FXScrollArea` class incorrectly spelled the
  names of the `horizontalScrollBar` and
  `verticalScrollBar` methods as
  `horizontalScrollbar` and
  `verticalScrollbar` (see RubyForge
  Bug #1678). The documentation has been corrected. Thanks to
  Jannis Pohlmann for reporting this mistake.

* Some code in the `groupbox.rb` example
  program was calling the `getRootWindow` method,
  but that method has been renamed to `getRoot`
  (see RubyForge
  Bug #1692). This problem has been corrected. Thanks to
  Jaroslav Stika for reporting this problem.

* The `hasChar?` method for the
  `FXFont` class was spelled without a trailing
  question mark, but it seems more Ruby-like that it should, so we've
  added an alias for that (see RubyForge
  Bug #1714). This method also now accepts a string of size 1
  (i.e. a single character) as its input, as an alternative to an
  ordinal value. Thanks to Meinrad Recheis for these suggestions.

* The API documentation for the `FXImage`
  class mistakenly listed ´IMAGE_ALPHA´ as a valid
  image rendering hint, but this flag is no longer needed since FOX
  images now always contain an alpha channel (see RubyForge
  Bug #1715). The documentation has been corrected. Thanks to
  Meinrad Recheis for reporting this mistake.

* Due to an error in the SWIG interface files, the
  `data` method for the
  `FXSettings` class was not being wrapped
  properly. As a result, this method was unavailable and in turn led to
  other dependent methods (like `each_section`)
  to be unavailable as well (see RubyForge
  Bug #1771). This error has been corrected. Thanks to Jannis
  Pohlmann for reporting this problem.

* The binary gem for Windows was built with FOX version 1.2.16 and
  FXScintilla version 1.62.


## Changes For Version 1.2.5 (March 1, 2005)

* The change made for FXRuby version 1.2.4 regarding garbage
  collection for table items corrected only one of the problems
  described in RubyForge
  Bug #1445; There was still a problem related to the
  "destructive" effects of the `setTableSize`
  method for the `FXTable` class. This problem has
  now been corrected as well. Thanks to David Peoples, Jamey Cribbs and
  Joel VanderWerf for their assistance in helping me to track down this
  problem.

* The `extractText` and
  `overlayText` methods for the
  `FXTable` class were implemented incorrectly and
  weren't listed in the API documentation. These problems have been
  corrected.

* The checks for out-of-bounds indices in the
  `getColumnX`,
  `setColumnX`, `getRowY`,
  `setRowY` and
  `updateRange` methods for the
  `FXTable` class were incorrect. These have been
  fixed.

* The `setTableSize` method for the
  `FXTable` class now raises
  `ArgError` if either the number of rows or
  columns passed in as arguments is less than zero.

* A typo in one of the source files was causing the build to fail
  when compiled against Ruby versions 1.8.1 or earlier (see RubyForge
  Bug #1551). This error has been corrected. Thanks to Alex
  McGuire for reporting this problem.

* The `selectItem` method for the
  `FXTable` class was removed in FOX 1.2, so we've
  added a convenience method for this that just calls the
  `selectRange` method under the hood (see RubyForge
  Bug #1562). Thanks to Joel VanderWerf for this
  suggestion.

* The binary gem for Windows was built with FOX version 1.2.13 and
  FXScintilla version 1.62.


## Changes For Version 1.2.4 (February 23, 2005)

* Due to a change in some of the internal Ruby C APIs, a
  compile-time error for FXRuby was introduced in some of the Ruby 1.8.2
  preview releases (see RubyForge
  Bug #1039). One should not see any compile-time errors when
  compiling FXRuby (versions 1.2.3 or later) against the Ruby 1.8.2
  final release, but I've neverthless made a change to how those
  internal APIs are used, to avoid any potential problems. Thanks to the
  many users who pointed out this problem.

* Joel VanderWerf suggested some enhancements to the
  `image.rb` example program in order to improve its
  startup time (see RubyForge
  Bug #1281). Those changes have been incorporated. Thanks to
  Joel for this suggestion.

* One change for the `FXImage` class between
  FOX versions 1.0 and 1.2 is the nature of the pixel buffer that's
  passed to the `FXImage` constructor. Previously,
  this pixel buffer was expected to be a string of bytes; now it's
  expected to be an array of ´FXColor´ values. This
  modification was not implemented correctly for FXRuby versions 1.2.3
  and earlier (see RubyForge
  Bug #1427). This bug has been corrected, and the example
  program (`image.rb`) and test cases have been
  updated as well. Thanks to Oliver Smith and others for reporting this
  problem.

* A couple of different problems, reported by Patrick Fernie and
  David Peoples, exposed a flaw in how FXRuby manages the links between
  FOX objects and their Ruby peers when the FOX objects are destroyed
  (see RubyForge
  Bug #1445). Without going into all the gory details, let's
  just say that since we have no explicit control over when Ruby's
  garbage collector decides to "collect" those Ruby peers that point to
  C++ objects that have been destroyed, we need to take steps to
  neutralize those Ruby peer objects so that they can't cause your
  application to crash in the meantime; I've implemented a fix to take
  care of this situation. Thanks to Patrick and David for reporting
  these problems.

* The API documentation for FXRuby 1.2 still contained references
  to the old "spellings" of the `fxparseAccel`
  and `fxparseHotKey` method names, which were
  all lowercase (i.e. `fxparseaccel` and
  `fxparsehotkey`). (see RubyForge
  Bug #1470). These errors have been corrected.

* Added the `FXScrollArea#scrollCorner`
  method, which returns a reference to the scroll corner for any window
  derived from `FXScrollArea` (see RubyForge
  Feature Request #1226). Thanks to Brian Sheehan for this
  suggestion.

* Added the `FXMemoryBuffer#to_a` method,
  which is just an alias for the `data` accessor
  method that returns a copy of the data buffer as an array (see RubyForge
  Feature Request #1295). Thanks to Meinrad Recheis for this
  suggestion.

* Added the `appendRows` and
  `appendColumns` methods to the
  `FXTable` class (see RubyForge
  Feature Request #1295). Thanks to Brett Hallett for this
  suggestion.

* The binary gem for Windows was built with FOX version 1.2.13 and
  FXScintilla version 1.62.


## Changes For Version 1.2.3 (January 22, 2005)

* Since group boxes containing radio buttons no longer enforce the
  radio behavior of radio buttons (i.e. keeping only one radio button
  selected at a time), some of the example programs were no longer
  working as desired (see RubyForge
  Bug #751 and RubyForge
  Bug #1280). This problem has been corrected. Thanks to Yuri
  Leikind and Barry DeZonia for reporting this problem.

* Bob Sidebotham reported a little typo in the
  `table.rb` example program (see RubyForge
  Bug #990). This has been corrected.

* The API documentation for `FXList` did not
  reflect the changes for FOX 1.2; the
  `retrieveItem()` has been renamed to
  `getItem()` and
  `insertItem()` has been renamed to
  `setItem()` (see RubyForge
  Bug #1037 and RubyForge
  Bug #1257). This has been corrected. Thanks to Remy Drouilhet
  and Stephan Kamper for reporting this problem.

* The Windows installer was missing some of the documentation
  files (see RubyForge
  Bug #1139). This has been corrected. Thanks to Curt Hibbs and
  Mark Smith for reporting this problem.

* The `browser.rb` example program was broken
  (see RubyForge
  Bug #1146). This has been corrected. Thanks to Stefan Lang for
  reporting this problem.

* The attribute setter for
  `FXHeaderItem#justification` was defined
  incorrectly (see RubyForge
  Bug #1276). This has been corrected. Thanks to Joel VanderWerf
  for reporting this problem (and providing a patch to fix it).

* The `filenames` alias for the
  `FXFileDialog#getFilenames()` instance method
  was missing (see RubyForge
  Bug #1277). This error has been corrected. Thanks to Barry
  DeZonia for reporting this problem.

* The API documentation for the
  `FXFileDialog` class methods
  `getOpenFilenames()`,
  `getOpenDirectory()`,
  `getOpenFilename()` and
  `getSaveFilename()` was extremely inadequate
  (see RubyForge
  Bug #1279). This documentation has been improved. Thanks to
  Barry DeZonia for reporting this problem.

* Brett Hallett contributed a Ruby port of the "ratio" example
  program from the regular FOX distribution, for demonstrating the use
  of the new `FXSpring` layout manager (see RubyForge
  Bug #1282). Many thanks to Brett for this addition!

* Joel VanderWerf contributed code to simplify how programs
  interact with modal and non-modal dialog boxes (see RubyForge
  Bug #1283). See the API documentation for the new
  `FXDialogBox#execute_modal` and
  `FXDialogBox#execute_nonmodal` methods for
  examples of their use.

* The attribute setters for
  `FXRealSpinner#selBackColor` and
  `FXSpinner#selBackColor` were defined
  incorrectly (see RubyForge
  Bug #1297). These have been corrected. Thanks to Meinrad
  Recheis for reporting this problem.

* The `tooltipPause` attribute reader for
  the `FXApp` class was missing (see RubyForge
  Patch #1306). Thanks to Joel VanderWerf for reporting this
  omission and providing a patch to fix it.

* The API documentation for the
  `FXToolBarTab` class was missing (see RubyForge
  Bug #1322). Thanks to Joel VanderWerf for reporting this
  omission.

* The attribute accessors for
  `FXText#visibleRows` and
  `FXText#visibleColumns` were defined and
  documented incorrectly (see RubyForge
  Bug #1325). These have been corrected. Thanks to Karl El-Koura
  for reporting this problem.

* The binary gem for Windows was built with FOX version 1.2.13 and
  FXScintilla version 1.62.


## Changes For Version 1.2.2 (October 1, 2004)

* In order to avoid versioning problems when dealing with a mix of
  applications based on either FXRuby 1.0 or 1.2, the feature name for
  FXRuby has been changed from "fox" to "fox12". For most application
  developers, this means that you will need to modify the source code
  for applications targeted at FXRuby 1.2 to begin with the line
  ´require 'fox12'´Note that no
  changes should be required for legacy applications targeted at FXRuby
  1.0.

* Made a number of updates to the documentation, to reflect API
  changes for FXRuby 1.2.

* The binary gem for Windows was built with FOX version 1.2.9 and
  FXScintilla version 1.61.


## Changes For Version 1.2a2 (July 10, 2004)

* This is the second "alpha" release of FXRuby 1.2. This release
  should be compatible with any FOX library version 1.2; it is not
  compatible with any previous FOX library versions. As this is an alpha
  release, users should expect a certain amount of instability, bugs,
  etc.

* For this release, all of the FOX 1.2 classes are available with
  the exception of the `FXBitmapView` class. There
  is a small problem with how the `FXBitmapView`
  class is declared in the FOX 1.2 header files, and I'm trying to
  decide how best to resolve that problem. The goal is to have this
  problem resolved by the next alpha release of FXRuby.

* For this release, all of the RDoc-based online documentation has
  been brought up to date with the new APIs.

* Portions of the FXRuby User's Guide were still out of date with
  respect to the new APIs (see SourceForge Bug #988623). This has been fixed.

* The `mditest.rb` example program was not up
  to date with the new APIs. This has been fixed.

* The `glviewer.rb` example program was not up
  to date with the new APIs (see SourceForge Bug #986479). This has been fixed. Thanks to Remy Drouilhet
  for reporting this problem and suggesting the fixes.

* The `FXGLGroup#bounds` method was defined
  incorrectly (see SourceForge Bug #986476). This has been fixed. Thanks to Remy Drouilhet
  for reporting this problem and suggesting the fix.

* The `scintilla-test.rb` example program was
  not up to date with the new APIs (see SourceForge Bug #986172). This has been fixed. Thanks to Peter Watkins for
  reporting this problem and submitting a corrected version of the
  program.

* There was a small typo in the table.rb example program (see
  SourceForge Bug #988152). This has been fixed. Thanks to Jamey Cribbs for
  reporting this problem and suggesting the fix.

* Due to an oversight on my part, one of the overloaded
  constructors for the `FXRegion` class wasn't
  wrapped properly (see SourceForge Bug #986181). This has been fixed. Thanks to Bil Bas for
  reporting this problem.

* Removed some obsolete aliases for the old leading and trailing
  rows and columns for the `FXTable` class (see
  SourceForge Bug #988038). Thanks to Yuri Leikind for reporting this
  problem.

* Added `FXTable` instance methods
  `horizontalGridShown=()` and
  `verticalGridShown=()` to complement the
  already available `horizontalGridShown?` and
  `verticalGridShown?` methods.

* The binary gem for the 1.2a1 release on Windows didn't have PNG
  or JPEG image support built-in (see SourceForge Bug #986180). This has been fixed. Thanks to Bil Bas for
  reporting this problem.

* The binary gem for Windows was built with FOX version 1.2.7 and
  FXScintilla version 1.61.


## Changes For Version 1.2a1 (June 28, 2004)

* This is the first "alpha" release of FXRuby 1.2. This release
  should be compatible with any FOX library version 1.2; it is not
  compatible with any previous FOX library versions. As this is an alpha
  release, users should expect a certain amount of instability, bugs,
  etc.
  The intent of this first alpha release is twofold. The primary
  intent is allow application developers who have current projects based
  on FXRuby 1.0 to begin the process of updating their applications for
  compatibility with FXRuby 1.2. For this release, all of the classes
  that existed in FXRuby 1.0 have been updated for compatibility with
  FOX 1.2, and so developers should at least be able to begin to "port"
  their applications forward now. Note that there have been a number of
  changes for FOX 1.2 and FXRuby 1.2, both in terms of API changes and
  less obvious "behavioral" changes. For a detailed summary of these
  changes, please see "What's New in FOX 1.2" (also available as a PDF).
  Note that few, if any, of the new classes introduced in FOX 1.2 are
  available in this first alpha release of FXRuby 1.2. Support for those
  new classes should come along quickly in subsequent alpha releases of
  FXRuby 1.2.
  The secondary intent of this first alpha release is to introduce
  the new RubyGems-based packaging
  of FXRuby and to begin to work out the inevitable kinks in that
  system.

* The binary gem for Windows was built with FOX version 1.2.4 and
  FXScintilla version 1.57.

