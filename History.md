=== 1.6.39 / 2017-12-26

* Fix FXGLVisual.supported and .supported?
* Add support for RubyInstaller-2.5

=== 1.6.38 / 2017-07-27

* Update dependent libraries for Windows binary gem.
* Replace libjpeg-9b by libjpeg-turbo-1.5.2 on Windows binary gem.
* Fix build with clang on FreeBSD (and possibly other OS). Fixes #41

=== 1.6.37 / 2017-06-24

* Add a 3rd type of FXRbObjects which is used for callbacks. Fixes #39

=== 1.6.36 / 2017-06-04

* Support the fxruby source gem on Windows (only RubyInstaller-2.4).
* Replace our self-made directory search methods by pgk-config.
* Enable the use of Win32 unicode functions. Fixes #30 and #38
* Fix segfault in vsprintf on Windows 10.
* Update support for RubyInstaller-2.4.1-1
* Update to libjpeg-9b
* More automation for gem releases

=== 1.6.35 / 2017-02-15

* Adjust for Ruby-2.4 with unified Integers
* Add support for RubyInstaller-2.4
* Drop support for Ruby-1.8 and 1.9. It may work with them, but is no longer tested.
* Add compat with SWIG-3.0
* Fix an issue with FXApp#removeInput introduced in fxruby-1.6.30.
* Work around missing /usr/lib/libfxscintilla.so file in Ubuntu
* Update dependent gems.
* Update libraries for Windows build.

=== 1.6.34 / 2016-04-26

* Add support for RubyInstaller-2.3
* Avoid RARRAY_PTR() which broke fxruby on ruby-2.3.0.
* Make use of StringValueCStr() where it is suitable.
* Fix initialisation of runOnUiThread event handler, when FXApp is called with a block.
* Disable GVL on RubyInstaller-1.9.3. Fixes #24

=== 1.6.33 / 2015-08-20

* Avoid rb_* calls that are prohibited during GC. Fixes #23
* Use copy'ing getters for FXVec members in FXMat*, FXMaterial and FXLight.
  This fixes the TC_FXMaterial#test_bug test case.
* Fix test suite, so that all tests pass.
* Add a travis-ci test setup and connect it to the github account.

=== 1.6.32 / 2015-08-07

* Avoid call to rb_class2name() during GC. Fixes #21
* Use release mode, unless extconf.rb is called with --enable-debug,
  so that all FXTRACE() and FXASSERT() calls are skiped, per default.
* Remove self made GC detection by ruby's rb_during_gc().
* Fix Windows binary x86-mingw32.gem for Ruby versions < 2.0

=== 1.6.31 / 2015-07-21

* Replace pipe2() by pipe() and fcntl(), because pipe2() is not as portable.
* Add missing include statement. Fixes #20

=== 1.6.30 / 2015-07-07

* Fix crashes in rb_gc_mark(): 0x00000003f54af8 is T_ZOMBIE / T_NONE
* Release Ruby's GVL while calls to FXImage#savePixels, #loadPixels
  and FXApp#run* methods.
* Add a working version for FXApp#addInput event handling on Windows.
  This works for sockets only for now.
* Add FXApp#runOnUiThread and FXId#runOnUiThread .
  This allows to safely execute GUI code from other threads.
* Use rake-compiler-dock for building windows binary gems.

=== 1.6.29 / 2015-02-17

* Add Windows binaries for Ruby-2.1 and 2.2.
* Use shared libs for Windows binary gems to reduce gem size.
* Allow non owned assignment of image data to FXImage derivations
  without copy'ing pixel data.
* Allow retrival of parts of the pixel data.
* Fix namespace specifier for FXRGB in kwargs.rb.
* Change GC'ing of TreeListBox and FXTreeItem. Fixes #10
* Update to swig version 2.0 or newer. Fixes #13

=== 1.6.28 / 2013-07-05

* Fix build for Ruby-2.0.0-p127+
* Update libraries for win32 build: libfox-1.6.49

=== 1.6.27 / 2013-04-05

* Add support for Ruby-2.0.
* Add cross compilation for x64-mingw32 target.

=== 1.6.26 / 2013-02-16

* Mark all text strings retrieved from fox as UTF-8 when running on Ruby 1.9
* Fix loading error on Ruby 1.8.7 by renaming the C++ extension to fox16_c
* Update libraries for windows cross compilation

=== 1.6.25 / 2012-06-17

* Windows: Fix slow loading of fox16.so by using a more recent mingw-w64 compiler
  (reported by Allen Doug and Igor Jorobus)
* Fix two possible segfaults in conjunction with FXSplashWindow (reported by Igor Jorobus)

=== 1.6.24 / 2012-06-06

* Update libraries for win32 build: libz-1.2.7 libpng-1.5.10 libjpeg-8d libtiff-4.0.1 libfox-1.6.45
* Avoid Segfauls in lots of methods when called with nil instead of FXApp, FXComposite or FXWindow objects

=== 1.6.23 / 2012-03-08

* Add YARD documentation support
* Use generated Manifest.txt
* Support for parallel task execution with drake

=== 1.6.22 / 2012-02-21

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

=== 1.6.20 / 2009-03-06

* Integrated the Hoe and rake-compiler extensions into the Rakefile and
  removed redundant tasks.
* Did some work to provide support for MinGW builds.

=== 1.6.19 / 2009-03-06

* Please see http://www.fxruby.org/doc/changes.html
  for a complete list of the changes in this release.
