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

/// Layout hints for child widgets
enum {
  LAYOUT_NORMAL      = 0,                                   /// Default layout mode
  LAYOUT_SIDE_TOP    = 0,                                   /// Pack on top side (default)
  LAYOUT_SIDE_BOTTOM = 0x00000001,                          /// Pack on bottom side
  LAYOUT_SIDE_LEFT   = 0x00000002,                          /// Pack on left side
  LAYOUT_SIDE_RIGHT  = LAYOUT_SIDE_LEFT|LAYOUT_SIDE_BOTTOM, /// Pack on right side
  LAYOUT_FILL_COLUMN = 0x00000001,                          /// Matrix column is stretchable
  LAYOUT_FILL_ROW    = 0x00000002,                          /// Matrix row is stretchable
  LAYOUT_LEFT        = 0,                                   /// Stick on left (default)
  LAYOUT_RIGHT       = 0x00000004,                          /// Stick on right
  LAYOUT_CENTER_X    = 0x00000008,                          /// Center horizontally
  LAYOUT_FIX_X       = LAYOUT_RIGHT|LAYOUT_CENTER_X,        /// X fixed
  LAYOUT_TOP         = 0,                                   /// Stick on top (default)
  LAYOUT_BOTTOM      = 0x00000010,                          /// Stick on bottom
  LAYOUT_CENTER_Y    = 0x00000020,                          /// Center vertically
  LAYOUT_FIX_Y       = LAYOUT_BOTTOM|LAYOUT_CENTER_Y,       /// Y fixed
  LAYOUT_DOCK_SAME   = 0,                                   /// Dock on same galley if it fits
  LAYOUT_DOCK_NEXT   = 0x00000040,                          /// Dock on next galley
  LAYOUT_RESERVED_1  = 0x00000080,
  LAYOUT_FIX_WIDTH   = 0x00000100,                          /// Width fixed
  LAYOUT_FIX_HEIGHT  = 0x00000200,                          /// height fixed
  LAYOUT_MIN_WIDTH   = 0,                                   /// Minimum width is the default
  LAYOUT_MIN_HEIGHT  = 0,                                   /// Minimum height is the default
  LAYOUT_FILL_X      = 0x00000400,                          /// Stretch or shrink horizontally
  LAYOUT_FILL_Y      = 0x00000800,                          /// Stretch or shrink vertically
  LAYOUT_FILL        = LAYOUT_FILL_X|LAYOUT_FILL_Y,         /// Stretch or shrink in both directions
  LAYOUT_EXPLICIT    = LAYOUT_FIX_X|LAYOUT_FIX_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT   /// Explicit placement
  };


/// Frame border appearance styles (for subclasses)
enum {
  FRAME_NONE   = 0,                                     /// Default is no frame
  FRAME_SUNKEN = 0x00001000,                            /// Sunken border
  FRAME_RAISED = 0x00002000,                            /// Raised border
  FRAME_THICK  = 0x00004000,                            /// Thick border
  FRAME_GROOVE = FRAME_THICK,                           /// A groove or etched-in border
  FRAME_RIDGE  = FRAME_THICK|FRAME_RAISED|FRAME_SUNKEN, /// A ridge or embossed border
  FRAME_LINE   = FRAME_RAISED|FRAME_SUNKEN,             /// Simple line border
  FRAME_NORMAL = FRAME_SUNKEN|FRAME_THICK               /// Regular raised/thick border
  };


/// Packing style (for packers)
enum {
  PACK_NORMAL         = 0,              /// Default is each its own size
  PACK_UNIFORM_HEIGHT = 0x00008000,     /// Uniform height
  PACK_UNIFORM_WIDTH  = 0x00010000      /// Uniform width
  };

class FXCursor;
class FXAccelTable;
class FXComposite;


%typemap(check) FXint CHILD_WINDOW_INDEX {
  if ($1 < 0 || $1 >= arg1->numChildren()) {
    rb_raise(rb_eIndexError, "child window index out of bounds");
  }
}

%apply FXint CHILD_WINDOW_INDEX { FXint index };

%rename("windowCount") FXWindow::getWindowCount() const;
%rename("before?") FXWindow::before(const FXWindow *a,const FXWindow* b);
%rename("before?") FXWindow::before(const FXWindow* b);
%rename("after?") FXWindow::after(const FXWindow *a,const FXWindow* b);
%rename("after?") FXWindow::after(const FXWindow* b);
%rename("composeContext") FXWindow::getComposeContext() const;
%rename("inFocusChain?") FXWindow::inFocusChain() const;

%alias FXWindow::shown() const "visible?";

%ignore FXWindow::setDNDData(FXDNDOrigin origin,FXDragType type,const FXString& string) const;
%ignore FXWindow::getDNDData(FXDNDOrigin origin,FXDragType type,FXString& string) const;

/// Base class for all windows
class FXWindow : public FXDrawable {
public:

  // Common DND types
  static FXDragType octetType;          // Raw octet stream
  static FXDragType deleteType;         // Delete request
  static FXDragType textType;           // Ascii text request
  static FXDragType utf8Type;           // UTF-8 text request
  static FXDragType utf16Type;          // UTF-16 text request
  static FXDragType colorType;          // Color
  static FXDragType urilistType;        // URI List
  static const FXDragType stringType;   // Clipboard text type (pre-registered)
  static const FXDragType imageType;    // Clipboard image type (pre-registered)

public:

  // Message handlers
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onMap(FXObject*,FXSelector,void* PTR_EVENT);
  long onUnmap(FXObject*,FXSelector,void* PTR_EVENT);
  long onConfigure(FXObject*,FXSelector,void* PTR_EVENT);
  long onUpdate(FXObject*,FXSelector,void* PTR_NULL);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onBeginDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onEndDrag(FXObject*,FXSelector,void* PTR_EVENT);
  long onDragged(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onDestroy(FXObject*,FXSelector,void* PTR_IGNORE);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_IGNORE);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_EVENT); // FIXME
  long onQueryTip(FXObject*,FXSelector,void* PTR_EVENT); // FIXME
  long onCmdShow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdHide(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleShown(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleShown(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRaise(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLower(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdEnable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDisable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleEnabled(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToggleEnabled(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdYes(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDelete(FXObject*,FXSelector,void* PTR_IGNORE);

public:

  // Message ID's common to most Windows
  enum {
    ID_NONE,
    ID_HIDE,            // ID_HIDE+FALSE
    ID_SHOW,            // ID_HIDE+TRUE
    ID_TOGGLESHOWN,
    ID_LOWER,
    ID_RAISE,
    ID_DELETE,
    ID_DISABLE,         // ID_DISABLE+FALSE
    ID_ENABLE,          // ID_DISABLE+TRUE
    ID_TOGGLEENABLED,
    ID_UNCHECK,         // ID_UNCHECK+FALSE
    ID_CHECK,           // ID_UNCHECK+TRUE
    ID_UNKNOWN,         // ID_UNCHECK+MAYBE
    ID_UPDATE,
    ID_AUTOSCROLL,
    ID_TIPTIMER,
    ID_HSCROLLED,
    ID_VSCROLLED,
    ID_SETVALUE,
    ID_SETINTVALUE,
    ID_SETREALVALUE,
    ID_SETSTRINGVALUE,
    ID_SETICONVALUE,
    ID_SETINTRANGE,
    ID_SETREALRANGE,
    ID_GETINTVALUE,
    ID_GETREALVALUE,
    ID_GETSTRINGVALUE,
    ID_GETICONVALUE,
    ID_GETINTRANGE,
    ID_GETREALRANGE,
    ID_SETHELPSTRING,
    ID_GETHELPSTRING,
    ID_SETTIPSTRING,
    ID_GETTIPSTRING,
    ID_QUERY_MENU,
    ID_HOTKEY,
    ID_ACCEL,
    ID_UNPOST,
    ID_POST,
    ID_MDI_TILEHORIZONTAL,
    ID_MDI_TILEVERTICAL,
    ID_MDI_CASCADE,
    ID_MDI_MAXIMIZE,
    ID_MDI_MINIMIZE,
    ID_MDI_RESTORE,
    ID_MDI_CLOSE,
    ID_MDI_WINDOW,
    ID_MDI_MENUWINDOW,
    ID_MDI_MENUMINIMIZE,
    ID_MDI_MENURESTORE,
    ID_MDI_MENUCLOSE,
    ID_MDI_NEXT,
    ID_MDI_PREV,
    ID_LAST
    };

public:

  // Common DND type names
  %extend {
    static VALUE octetTypeName() {
      return to_ruby(FXWindow::octetTypeName);
    }

    static VALUE deleteTypeName() {
      return to_ruby(FXWindow::deleteTypeName);
    }

    static VALUE textTypeName() {
      return to_ruby(FXWindow::textTypeName);
    }

    static VALUE colorTypeName() {
      return to_ruby(FXWindow::colorTypeName);
    }

    static VALUE urilistTypeName() {
      return to_ruby(FXWindow::urilistTypeName);
    }

    static VALUE utf8TypeName() {
      return to_ruby(FXWindow::utf8TypeName);
    }

    static VALUE utf16TypeName() {
      return to_ruby(FXWindow::utf16TypeName);
    }
  }

public:

  /// Constructor
  %extend {
    // Construct as a child of some other window
    FXWindow(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbWindow(p,opts,x,y,w,h);
      }

    // Shell window constructor
    FXWindow(FXApp* a,FXVisual *vis){
      return new FXRbWindow(a,vis);
      }

    // Construct owned window
    FXWindow(FXApp* a,FXWindow* own,FXuint opts,FXint x,FXint y,FXint w,FXint h){
      return new FXRbWindow(a,own,opts,x,y,w,h);
      }
    }

  /// Return a pointer to the parent window
  FXWindow* getParent() const;

  /// Return a pointer to the owner window
  FXWindow* getOwner() const;

  /// Return a pointer to the shell window
  FXWindow* getShell() const;

  /// Return a pointer to the root window
  FXWindow* getRoot() const;

  /// Return a pointer to the next (sibling) window, if any
  FXWindow* getNext() const;

  /// Return a pointer to the previous (sibling) window , if any
  FXWindow* getPrev() const;

  /// Return a pointer to this window's first child window , if any
  FXWindow* getFirst() const;

  /// Return a pointer to this window's last child window, if any
  FXWindow* getLast() const;

  /// Return a pointer to the currently focused child window
  FXWindow* getFocus() const;

  /// Change window key
  void setKey(FXuint k);

  /// Return window key
  FXuint getKey() const;

  /// Set the message target object for this window
  void setTarget(FXObject *t);

  /// Get the message target object for this window, if any
  FXObject* getTarget() const;

  /// Set the message identifier for this window
  void setSelector(FXSelector sel);

  /// Get the message identifier for this window
  FXSelector getSelector() const;

  /// Get this window's x-coordinate, in the parent's coordinate system
  FXint getX() const;

  /// Get this window's y-coordinate, in the parent's coordinate system
  FXint getY() const;

  /// Set this window's x-coordinate, in the parent's coordinate system
  void setX(FXint x);

  /// Set this window's y-coordinate, in the parent's coordinate system
  void setY(FXint y);

  /**
  * Set the window width; and flag the widget as being in need of
  * layout by its parent.  This does not immediately update the server-
  * side representation of the widget.
  */
  void setWidth(FXint w);

  /**
  * Set the window height; and flag the widget as being in need of
  * layout by its parent.  This does not immediately update the server-
  * side representation of the widget.
  */
  void setHeight(FXint h);

  /// Set layout hints for this window
  void setLayoutHints(FXuint lout);

  /// Get layout hints for this window
  FXuint getLayoutHints() const;

  /// Return a pointer to the accelerator table
  FXAccelTable* getAccelTable() const;

  /// Set the accelerator table
  void setAccelTable(FXAccelTable* acceltable);

  /// Add a hot key
  void addHotKey(FXHotKey code);

  /// Remove a hot key
  void remHotKey(FXHotKey code);

  /// Change help tag for this widget
  void setHelpTag(const FXString& text);

  /// Get the help tag for this widget
  const FXString& getHelpTag() const;

  /// Return true if window is a shell window
  bool isShell() const;

  /// Return true if specified window is owned by this window
  bool isOwnerOf(const FXWindow* window) const;

  /// Return true if specified window is ancestor of this window.
  bool isChildOf(const FXWindow* window) const;

  /// Return true if this window contains child in its subtree.
  bool containsChild(const FXWindow* child) const;

  /// Return the child window at specified coordinates
  FXWindow* getChildAt(FXint x,FXint y) const;

  /// Return the number of child windows for this window
  FXint numChildren() const;

  /**
  * Return the index (starting from zero) of the specified child window,
  * or -1 if the window is not a child or NULL
  */
  FXint indexOfChild(const FXWindow *window) const;

  %extend {
    // Remove specified child window
    FXbool removeChild(FXWindow* child){
      if(self->containsChild(child)){
        delete child;
        return TRUE;
        }
      else{
        return FALSE;
        }
      }
  }

  /**
  * Return the child window at specified index,
  * or NULL if the index is negative or out of range
  */
  FXWindow* childAtIndex(FXint index) const;

  /// Return the common ancestor of window a and window b
  static FXWindow* commonAncestor(FXWindow* a,FXWindow* b);

  /// Return TRUE if sibling a <= sibling b in list
  static bool before(const FXWindow *a,const FXWindow* b);

  /// Return TRUE if sibling a >= sibling b in list
  static bool after(const FXWindow *a,const FXWindow* b);

  %extend {
    bool before(const FXWindow *other) const { return FXWindow::before(self, other); }
    bool after(const FXWindow *other) const { return FXWindow::after(self, other); }
  }

  /// Return compose context
  FXComposeContext* getComposeContext() const;

  /// Create compose context
  void createComposeContext();

  /// Destroy compose context
  void destroyComposeContext();

  /// Set the default cursor for this window
  void setDefaultCursor(FXCursor* cur);

  /// Return the default cursor for this window
  FXCursor* getDefaultCursor() const;

  /// Set the drag cursor for this window
  void setDragCursor(FXCursor* cur);

  /// Return the drag cursor for this window
  FXCursor* getDragCursor() const;

  %extend {
    /// Return the cursor position and mouse button-state
    VALUE getCursorPosition() const {
      FXint x, y;
      FXuint buttons;
      self->getCursorPosition(x, y, buttons);
      VALUE arr = rb_ary_new();
      rb_ary_push(arr, INT2NUM(x));
      rb_ary_push(arr, INT2NUM(y));
      rb_ary_push(arr, UINT2NUM(buttons));
      return arr;
    }
  }

  /// Warp the cursor to the new position
  FXint setCursorPosition(FXint x,FXint y);

  /// Return true if this window is able to receive mouse and keyboard events
  bool isEnabled() const;

  /// Return true if the window is active
  bool isActive() const;

  /// Return true if this window has the focus
  bool hasFocus() const;

  /// Return true if this window is in focus chain
  bool inFocusChain() const;

  /// Return true if this is the default window
  bool isDefault() const;

  /// Make this window the initial default window
  void setInitial(bool enable=true);

  /// Return true if this is the initial default window
  bool isInitial() const;

  /// Generate a SEL_UPDATE message for the window and its children
  void forceRefresh();

  /// Scroll rectangle x,y,w,h by a shift of dx,dy
  void scroll(FXint x,FXint y,FXint w,FXint h,FXint dx,FXint dy) const;

  /// Mark the specified rectangle to be repainted later
  void update(FXint x,FXint y,FXint w,FXint h) const;

  /// Mark the entire window to be repainted later
  void update() const;

  /// Process any outstanding repaint messages immediately, for the given rectangle
  void repaint(FXint x,FXint y,FXint w,FXint h) const;

  /// If marked but not yet painted, paint the window now
  void repaint() const;

  /**
  * Grab the mouse to this window; future mouse events will be
  * reported to this window even while the cursor goes outside of this window
  */
  void grab();

  /// Release the mouse grab
  void ungrab();

  /// Return true if the window has been grabbed
  bool grabbed() const;

  /// Grab keyboard device
  void grabKeyboard();

  /// Ungrab keyboard device
  void ungrabKeyboard();

  /// Return true if active grab is in effect
  bool grabbedKeyboard() const;

  /// Return true if the window is shown
  bool shown() const;

  /// Return true if the window is under the cursor
  bool underCursor() const;

  /// Return true if this window owns the primary selection
  bool hasSelection() const;

  %extend {
    /// Try to acquire the primary selection, given a list of drag types
    bool acquireSelection(VALUE typesArray){
      Check_Type(typesArray,T_ARRAY);
      FXDragType *types=0;
      FXuint numtypes=RARRAY_LEN(typesArray);
      if(numtypes>0){
        types=new FXDragType[numtypes];
        for(FXuint i=0;i<numtypes;i++){
          types[i]=(FXDragType) NUM2UINT(rb_ary_entry(typesArray,i));
          }
      }
      bool result=self->acquireSelection(types,numtypes);
      delete [] types;
      return result;
      }
  }

  /// Release the primary selection
  bool releaseSelection();

  /// Return true if this window owns the clipboard
  bool hasClipboard() const;

  %extend {
    /// Try to acquire the clipboard, given a list of drag types
    bool acquireClipboard(VALUE typesArray){
      Check_Type(typesArray,T_ARRAY);
      FXDragType *types=0;
      FXuint numtypes=RARRAY_LEN(typesArray);
      if(numtypes>0){
        types=new FXDragType[numtypes];
        for(FXuint i=0;i<numtypes;i++){
          types[i]=(FXDragType) NUM2UINT(rb_ary_entry(typesArray,i));
          }
      }
      bool result=self->acquireClipboard(types,numtypes);
      delete [] types;
      return result;
      }
  }

  /// Release the clipboard
  bool releaseClipboard();

  /// Return true if this window is able to receive drops
  bool isDropEnabled() const;

  /// Return true if a drag operaion has been initiated from this window
  bool isDragging() const;

  %extend {
    /// Initiate a drag operation with a list of previously registered drag types
    bool beginDrag(VALUE typesArray){
      Check_Type(typesArray,T_ARRAY);
      FXDragType *types=0;
      FXuint numtypes=RARRAY_LEN(typesArray);
      if(numtypes>0){
        types=new FXDragType[numtypes];
        for(FXuint i=0;i<numtypes;i++){
          types[i]=(FXDragType) NUM2UINT(rb_ary_entry(typesArray,i));
          }
      }
      bool result=self->beginDrag(types,numtypes);
      delete [] types;
      return result;
      }
  }

  /**
  * When dragging, inform the drop-target of the new position and
  * the drag action
  */
  bool handleDrag(FXint x,FXint y,FXDragAction action=DRAG_COPY);

  /// Terminate the drag operation with or without actually dropping the data
  FXDragAction endDrag(bool drop=true);

  /// Return true if this window is the target of a drop
  bool isDropTarget() const;

  /**
  * When being dragged over, indicate that no further SEL_DND_MOTION messages
  * are required while the cursor is inside the given rectangle
  */
  void setDragRectangle(FXint x,FXint y,FXint w,FXint h,bool wantupdates=true) const;

  /**
  * When being dragged over, indicate we want to receive SEL_DND_MOTION messages
  * every time the cursor moves
  */
  void clearDragRectangle() const;

  /// When being dragged over, indicate acceptance or rejection of the dragged data
  void acceptDrop(FXDragAction action=DRAG_ACCEPT) const;

  /// The target accepted our drop
  FXDragAction didAccept() const;

  /**
  * Sent by the drop target in response to SEL_DND_DROP.  The drag action
  * should be the same as the action the drop target reported to the drag
  * source in reponse to the SEL_DND_MOTION message.
  * This function notifies the drag source that its part of the drop transaction
  * is finished, and that it is free to release any resources involved in the
  * drag operation.
  * Calling dropFinished() is advisable in cases where the drop target needs
  * to perform complex processing on the data received from the drag source,
  * prior to returning from the SEL_DND_DROP message handler.
  */
  void dropFinished(FXDragAction action=DRAG_REJECT) const;

  %extend {
    // When being dragged over, inquire the drag types which are being offered
    VALUE inquireDNDTypes(FXDNDOrigin origin) const {
      FXDragType* types;
      FXuint numtypes;
      VALUE arr = rb_ary_new();
      if (self->inquireDNDTypes(origin, types, numtypes)) {
        for (FXuint i = 0; i < numtypes; i++)
          rb_ary_push(arr, to_ruby(types[i]));
        FXFREE(&types);
      }
      return arr;
    }
  }

  /// When being dragged over, return true if we are offered the given drag type
  bool offeredDNDType(FXDNDOrigin origin,FXDragType type) const;

  /// When being dragged over, return the drag action
  FXDragAction inquireDNDAction() const;

  %extend {
    // Set DND data; ownership is transferred to the system
    void setDNDData(FXDNDOrigin origin, FXDragType type, VALUE str) const {
      Check_Type(str, T_STRING);
      FXuchar* data;
      FXuint size = RSTRING_LEN(str);
      if (FXMALLOC(&data, FXuchar, size)) {
        memcpy((void *) data, (void *) RSTRING_PTR(str), size);
        self->setDNDData(origin, type, data, size);
      } else {
        rb_raise(rb_eNoMemError, "couldn't copy drag-and-drop data");
      }
    }

    // Get DND data; the caller becomes the owner of the array.
    VALUE getDNDData(FXDNDOrigin origin, FXDragType type) const {
      FXuchar* data;
      FXuint size;
      VALUE result = Qnil;
      if (self->getDNDData(origin, type, data, size)) {
        result = rb_str_new((const FXchar *) data, size);
        FXFREE(&data);
      }
      return result;
    }
  }

  /**
  * Set DND data from string value.
  */
  bool setDNDData(FXDNDOrigin origin,FXDragType type,const FXString& string) const;

  /**
  * Get DND data into string value.
  */
  bool getDNDData(FXDNDOrigin origin,FXDragType type,FXString& string) const;

  %extend {
    // Translate coordinates from fromwindow's coordinate space
    // to this window's coordinate space
    VALUE translateCoordinatesFrom(const FXWindow* fromwindow,
                                   FXint fromx, FXint fromy) const {
      FXint tox, toy;
      self->translateCoordinatesFrom(tox, toy, fromwindow, fromx, fromy);
      VALUE result = rb_ary_new();
      rb_ary_push(result, INT2NUM(tox));
      rb_ary_push(result, INT2NUM(toy));
      return result;
    }

    // Translate coordinates from this window's coordinate space
    // to towindow's coordinate space
    VALUE translateCoordinatesTo(const FXWindow* towindow,
                                 FXint fromx, FXint fromy) const {
      FXint tox, toy;
      self->translateCoordinatesTo(tox, toy, towindow, fromx, fromy);
      VALUE result = rb_ary_new();
      rb_ary_push(result, INT2NUM(tox));
      rb_ary_push(result, INT2NUM(toy));
      return result;
    }
  }

  /// Get background color
  FXColor getBackColor() const;

  /// Destroy window
  virtual ~FXWindow();
  };

%clear FXint index;

DECLARE_FXOBJECT_VIRTUALS(FXWindow)
DECLARE_FXID_VIRTUALS(FXWindow)
DECLARE_FXDRAWABLE_VIRTUALS(FXWindow)
DECLARE_FXWINDOW_VIRTUALS(FXWindow)

%{
static swig_type_info *FXWindow_dynamic_cast(void **ptr) {
    FXWindow **ppWindow = reinterpret_cast<FXWindow **>(ptr);
    FXCanvas *pCanvas=dynamic_cast<FXCanvas*>(*ppWindow);
    if(pCanvas){
      *ptr=reinterpret_cast<void*>(pCanvas);
      return SWIG_TypeQuery("FXCanvas *");
      }
    FXComposite *pComposite=dynamic_cast<FXComposite*>(*ppWindow);
    if(pComposite){
      *ptr=reinterpret_cast<void*>(pComposite);
      return SWIG_TypeQuery("FXComposite *");
      }
    FXDragCorner *pDragCorner=dynamic_cast<FXDragCorner*>(*ppWindow);
    if(pDragCorner){
      *ptr=reinterpret_cast<void*>(pDragCorner);
      return SWIG_TypeQuery("FXDragCorner *");
      }
    FXFrame *pFrame=dynamic_cast<FXFrame*>(*ppWindow);
    if(pFrame){
      *ptr=reinterpret_cast<void*>(pFrame);
      return SWIG_TypeQuery("FXFrame *");
      }
    FXMenuCaption *pMenuCaption=dynamic_cast<FXMenuCaption*>(*ppWindow);
    if(pMenuCaption){
      *ptr=reinterpret_cast<void*>(pMenuCaption);
      return SWIG_TypeQuery("FXMenuCaption *");
      }
    FXMenuSeparator *pMenuSeparator=dynamic_cast<FXMenuSeparator*>(*ppWindow);
    if(pMenuSeparator){
      *ptr=reinterpret_cast<void*>(pMenuSeparator);
      return SWIG_TypeQuery("FXMenuSeparator *");
      }
    FXScrollBar *pScrollBar=dynamic_cast<FXScrollBar*>(*ppWindow);
    if(pScrollBar){
      *ptr=reinterpret_cast<void*>(pScrollBar);
      return SWIG_TypeQuery("FXScrollBar *");
      }
    FXScrollCorner *pScrollCorner=dynamic_cast<FXScrollCorner*>(*ppWindow);
    if(pScrollCorner){
      *ptr=reinterpret_cast<void*>(pScrollCorner);
      return SWIG_TypeQuery("FXScrollCorner *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXWindow, FXWindow_dynamic_cast);

