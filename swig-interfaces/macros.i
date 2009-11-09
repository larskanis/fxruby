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

%define DECLARE_FXAPP_VIRTUALS(klass)
%extend klass {
  /// Create application's windows
  virtual void create();

  /// Destroy application's windows
  virtual void destroy();

  /// Detach application's windows
  virtual void detach();

  /**
   * Initialize application.
   * Parses and removes common command line arguments, reads the registry.
   * Finally, if connect is TRUE, it opens the display.
   */
  virtual void init(VALUE arr,FXbool connect=true);

  /**
   * Exit application.
   * Closes the display and writes the registry.
   */
  virtual void exit(FXint code=0);
  }
%enddef

%define DECLARE_FXBITMAP_VIRTUALS(klass)
%extend klass {
   /**
  * Retrieves pixels from the server-side bitmap.  
  */
  virtual void restore();

  /// Render pixels
  virtual void render();

  /// Release the client-side pixels buffer, freeing it if it was owned.
  virtual void release();

  /// Save pixel data only
  virtual FXbool savePixels(FXStream& store) const;
  
  /// Load pixel data
  virtual FXbool loadPixels(FXStream& store);

  /// Rescale pixels to the specified width and height
  virtual void scale(FXint w,FXint h);

  /// Mirror bitmap horizontally and/or vertically
  virtual void mirror(FXbool horizontal,FXbool vertical);

  /// Rotate bitmap by degrees ccw
  virtual void rotate(FXint degrees);

  /// Crop bitmap to given rectangle
  virtual void crop(FXint x,FXint y,FXint w,FXint h,FXbool color=false);

  /// Fill bitmap with uniform value
  virtual void fill(FXbool color);

  /**
  * Populate the bitmap with new pixel data of the same size; it will assume
  * ownership of the pixel data if image BITMAP_OWNED option is passed.
  * The server-side representation of the image, if it exists, is not updated.
  * This can be done by calling render().
  */
  virtual void setData(FXuchar *pix,FXuint opts=0);

  /**
  * Populate the bitmap with new pixel data of a new size; it will assume ownership
  * of the pixel data if image BITMAP_OWNED option is passed.  The size of the server-
  * side representation of the image, if it exists, is adjusted but the contents are
  * not updated yet. This can be done by calling render().
  */
  virtual void setData(FXuchar *pix,FXuint opts,FXint w,FXint h);
  }
%enddef

%define DECLARE_FXCURSOR_VIRTUALS(klass)
%extend klass {
  /// Save pixel data only
  virtual FXbool savePixels(FXStream& store) const;
  
  /// Load pixel data
  virtual FXbool loadPixels(FXStream& store);
  }
%enddef

%define DECLARE_FXDC_VIRTUALS(klass)
%extend klass {
  /// Read back pixel
  virtual FXColor readPixel(FXint x,FXint y);

  /// Draw points
  virtual void drawPoint(FXint x,FXint y);
  virtual void drawPoints(const FXPoint* points,FXuint npoints);
  virtual void drawPointsRel(const FXPoint* points,FXuint npoints);

  /// Draw lines
  virtual void drawLine(FXint x1,FXint y1,FXint x2,FXint y2);
  virtual void drawLines(const FXPoint* points,FXuint npoints);
  virtual void drawLinesRel(const FXPoint* points,FXuint npoints);
  virtual void drawLineSegments(const FXSegment* segments,FXuint nsegments);
  
  /// Draw rectangles
  virtual void drawRectangle(FXint x,FXint y,FXint w,FXint h);
  virtual void drawRectangles(const FXRectangle* rectangles,FXuint nrectangles);

  /// Draw rounded rectangle with ellipse with ew and ellips height eh
  virtual void drawRoundRectangle(FXint x,FXint y,FXint w,FXint h,FXint ew,FXint eh);

  /**
  * Draw arcs.
  * The argument ang1 specifies the start of the arc relative to the 
  * three-o'clock position from the center, in units of degrees*64.
  * The argument ang2 specifies the path and extent of the arc relative 
  * to the start of the arc, in units of degrees*64.
  * The arguments x,y,w,h specify the bounding rectangle.
  */
  virtual void drawArc(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);
  virtual void drawArcs(const FXArc* arcs,FXuint narcs);

  /// Draw ellipse
  virtual void drawEllipse(FXint x,FXint y,FXint w,FXint h);

  /// Filled rectangles
  virtual void fillRectangle(FXint x,FXint y,FXint w,FXint h);
  virtual void fillRectangles(const FXRectangle* rectangles,FXuint nrectangles);

  /// Draw filled rounded rectangle with ellipse with ew and ellips height eh
  virtual void fillRoundRectangle(FXint x,FXint y,FXint w,FXint h,FXint ew,FXint eh);

  /// Draw chords
  virtual void fillChord(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);
  virtual void fillChords(const FXArc* chord,FXuint nchords);

  /// Draw arcs
  virtual void fillArc(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);
  virtual void fillArcs(const FXArc* arcs,FXuint narcs);

  /// Filled polygon
  virtual void fillPolygon(const FXPoint* points,FXuint npoints);
  virtual void fillConcavePolygon(const FXPoint* points,FXuint npoints);
  virtual void fillComplexPolygon(const FXPoint* points,FXuint npoints);

  /// Filled polygon with relative points
  virtual void fillPolygonRel(const FXPoint* points,FXuint npoints);
  virtual void fillConcavePolygonRel(const FXPoint* points,FXuint npoints);
  virtual void fillComplexPolygonRel(const FXPoint* points,FXuint npoints);

  /// Draw hashed box
  virtual void drawHashBox(FXint x,FXint y,FXint w,FXint h,FXint b=1);

  /// Draw focus rectangle
  virtual void drawFocusRectangle(FXint x,FXint y,FXint w,FXint h);
  
  /// Draw area from source
  virtual void drawArea(const FXDrawable* source,FXint sx,FXint sy,FXint sw,FXint sh,FXint dx,FXint dy);

  /// Draw stretched area from source
  virtual void drawArea(const FXDrawable* source,FXint sx,FXint sy,FXint sw,FXint sh,FXint dx,FXint dy,FXint dw,FXint dh);

  /// Draw image 
  virtual void drawImage(const FXImage* image,FXint dx,FXint dy);

  /// Draw bitmap
  virtual void drawBitmap(const FXBitmap* bitmap,FXint dx,FXint dy);
  
  /// Draw icon 
  virtual void drawIcon(const FXIcon* icon,FXint dx,FXint dy);
  virtual void drawIconShaded(const FXIcon* icon,FXint dx,FXint dy);
  virtual void drawIconSunken(const FXIcon* icon,FXint dx,FXint dy);

  /// Draw string
  // virtual void drawText(FXint x,FXint y,const FXString& string);
  virtual void drawText(FXint x,FXint y,const FXchar* string,FXuint length);
  // virtual void drawImageText(FXint x,FXint y,const FXString& string);
  virtual void drawImageText(FXint x,FXint y,const FXchar* string,FXuint length);

  /// Set foreground drawing color
  virtual void setForeground(FXColor clr);
  
  /// Set background drawing color
  virtual void setBackground(FXColor clr);
  
  /**
  * Set dash pattern and dash offset.
  * A dash pattern of [1 2 3 4] is a repeating pattern of 1 foreground pixel, 
  * 2 background pixels, 3 foreground pixels, and 4 background pixels.
  * The offset is where in the pattern the system will start counting.
  * The maximum length of the dash pattern is 32.
  */
  virtual void setDashes(FXuint dashoffset,const FXchar *dashpattern,FXuint dashlength);

  /// Set line width:- 0 means thinnest/fastest possible
  virtual void setLineWidth(FXuint linewidth=0);
  
  /// Set line cap style
  virtual void setLineCap(FXCapStyle capstyle=CAP_BUTT);
  
  /// Set line join style
  virtual void setLineJoin(FXJoinStyle joinstyle=JOIN_MITER);
  
  /// Set line style
  virtual void setLineStyle(FXLineStyle linestyle=LINE_SOLID);
  
  /// Set fill style
  virtual void setFillStyle(FXFillStyle fillstyle=FILL_SOLID);
  
  /// Set fill rule
  virtual void setFillRule(FXFillRule fillrule=RULE_EVEN_ODD);
  
  /// Set rasterop function
  virtual void setFunction(FXFunction func=BLT_SRC);
  
  /// Set the tile image
  virtual void setTile(FXImage* image,FXint dx=0,FXint dy=0);
  
  /// Set the stipple pattern 
  virtual void setStipple(FXBitmap *bitmap,FXint dx=0,FXint dy=0);
  
  /// Set the stipple pattern 
  virtual void setStipple(FXStipplePattern pat,FXint dx=0,FXint dy=0);
  
  /// Set clip region
  virtual void setClipRegion(const FXRegion& region);
  
  /// Set clip rectangle
  virtual void setClipRectangle(FXint x,FXint y,FXint w,FXint h);

  /// Change clip rectangle
  virtual void setClipRectangle(const FXRectangle& rectangle);
  
  /// Clear clipping
  virtual void clearClipRectangle();
  
  /// Set clip mask
  virtual void setClipMask(FXBitmap* bitmap,FXint dx=0,FXint dy=0);
  
  /// Clear clip mask
  virtual void clearClipMask();
  
  /// Set font to draw text with
  virtual void setFont(FXFont *fnt);
  
  /// Clip against child windows
  virtual void clipChildren(FXbool yes);
  }
%enddef

%define DECLARE_FXDIALOGBOX_VIRTUALS(klass)
%extend klass {
  /// Run modal invocation of the dialog
  virtual FXuint execute(FXuint placement=PLACEMENT_CURSOR);
  }
%enddef

%define DECLARE_FXDOCKBAR_VIRTUALS(klass)
%extend klass {
  /**
  * Dock the bar against the given side, after some other widget.
  * However, if after is -1, it will be docked as the innermost bar just before
  * the work-area, while if after is 0, if will be docked as the outermost bar.
  */
  virtual void dock(FXDockSite* docksite,FXWindow* other=NULL,FXbool notify=false);

  /**
  * Dock the bar against the given side, near the given position relative
  * to the toolbar dock's origin.
  */
  virtual void dock(FXDockSite* docksite,FXint localx,FXint localy,FXbool notify=false);

  /**
  * Undock or float the bar.
  * The initial position of the wet dock is a few pixels
  * below and to the right of the original docked position.
  */
  virtual void undock(FXint rootx,FXint rooty,FXbool notify=false);
  }
%enddef

%define DECLARE_FXDOCKSITE_VIRTUALS(klass)
%extend klass {
  /// Resize toolbar
  virtual void resizeToolBar(FXDockBar* bar,FXint barx,FXint bary,FXint barw,FXint barh);

  /**
  * Move tool bar, changing its options to suite the new position.
  * Used by the toolbar dragging to rearrange the toolbars inside the
  * toolbar dock.
  */
  virtual void moveToolBar(FXDockBar* bar,FXint barx,FXint bary);

  /**
  * The dock site is notified that the given bar has been added
  * logically before the other window, and is to placed on a new
  * galley all by itself.  The default implementation adjusts
  * the layout options of the bars accordingly.
  */
  virtual void dockToolBar(FXDockBar* bar,FXWindow* other);

  /**
  * The dock site is informed that the given bar has been docked
  * at the given coordinates.  The default implementation determines
  * where to insert the newly docked bar and adjusts the layout
  * options of the bars accordingly.
  */
  virtual void dockToolBar(FXDockBar* bar,FXint barx,FXint bary);

  /**
  * The dock site is informed that the given bar has been removed.
  * In the default implementation, the dock site fixes the layout
  * options of the remaining bars so they stay in the same place
  * if possible.
  */
  virtual void undockToolBar(FXDockBar* bar);
  }
%enddef

%define DECLARE_FXDRAWABLE_VIRTUALS(klass)
%extend klass {
  /// Resize drawable to the specified width and height 
  virtual void resize(FXint w,FXint h);
  }
%enddef

%define DECLARE_FXFILEDICT_VIRTUALS(klass)
%extend klass {
  virtual FXFileAssoc* findFileBinding(const FXchar* pathname);
  virtual FXFileAssoc* findDirBinding(const FXchar* pathname);
  virtual FXFileAssoc* findExecBinding(const FXchar* pathname);
  }
%enddef

%define DECLARE_FXFOLDINGITEM_VIRTUALS(klass)
%extend klass {
  virtual void setText(const FXString& txt);
  virtual void setOpenIcon(FXIcon* icn,FXbool owned=false);
  virtual void setClosedIcon(FXIcon* icn,FXbool owned=false);
  virtual void setFocus(FXbool focus);
  virtual void setSelected(FXbool selected);
  virtual void setOpened(FXbool opened);
  virtual void setExpanded(FXbool expanded);
  virtual void setEnabled(FXbool enabled);
  virtual void setDraggable(FXbool draggable);
  virtual FXint getWidth(const FXFoldingList* list) const;
  virtual FXint getHeight(const FXFoldingList* list) const;
  virtual void create();
  virtual void detach();
  virtual void destroy();
  }
%enddef

%define DECLARE_FXFOLDINGLIST_VIRTUALS(klass)
%extend klass {
  virtual FXFoldingItem *getItemAt(FXint x,FXint y) const;
  virtual void makeItemVisible(FXFoldingItem* item);

  /// Enable item
  virtual FXbool enableItem(FXFoldingItem* item);

  /// Disable item
  virtual FXbool disableItem(FXFoldingItem* item);

  /// Select item
  virtual FXbool selectItem(FXFoldingItem* item,FXbool notify=false);

  /// Deselect item
  virtual FXbool deselectItem(FXFoldingItem* item,FXbool notify=false);

  /// Toggle item selection
  virtual FXbool toggleItem(FXFoldingItem* item,FXbool notify=false);

  /// Extend selection from anchor item to item
  virtual FXbool extendSelection(FXFoldingItem* item,FXbool notify=false);

  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=false);

  /// Open item
  virtual FXbool openItem(FXFoldingItem* item,FXbool notify=false);

  /// Close item
  virtual FXbool closeItem(FXFoldingItem* item,FXbool notify=false);

  /// Collapse tree
  virtual FXbool collapseTree(FXFoldingItem* tree,FXbool notify=false);

  /// Expand tree
  virtual FXbool expandTree(FXFoldingItem* tree,FXbool notify=false);

  /// Change current item
  virtual void setCurrentItem(FXFoldingItem* item,FXbool notify=false);
  }
%enddef

%define DECLARE_FXFONT_VIRTUALS(klass)
%extend klass {
  /// Change font description
  virtual void setFontDesc(const FXFontDesc& fontdesc);

  /// Set to new angle, in degrees*64 relative to positive x axis
  virtual void setAngle(FXint ang);

  /**
  * Change the font to the specified font description string.
  */
  virtual void setFont(const FXString& string);

  /// Find out if the font is monotype or proportional
  virtual FXbool isFontMono() const;
  
  %extend {
    /// See if font has glyph for ch
    virtual FXbool hasChar(VALUE ch) const {
      if(TYPE(ch)==T_STRING){
        if(RSTRING_LEN(ch)==1){
          return self->hasChar(*(StringValuePtr(ch))); // FIXME: hasChar() expects an FXwchar
	  }
	else{
	  rb_raise(rb_eArgError,"expected a string of length one");
	  }
        }
      else{
        return self->hasChar(NUM2INT(ch)); // FIXME: hasChar() expects an FXwchar
        }
      }
  }

  /// Get first character glyph in font  
  virtual FXwchar getMinChar() const;
  
  /// Get last character glyph in font
  virtual FXwchar getMaxChar() const;

  /// Left bearing
  virtual FXint leftBearing(FXwchar ch) const;
  
  /// Right bearing
  virtual FXint rightBearing(FXwchar ch) const;
  
  /// Width of widest character in font
  virtual FXint getFontWidth() const;
  
  /// Height of highest character in font
  virtual FXint getFontHeight() const;
  
  /// Ascent from baseline
  virtual FXint getFontAscent() const;
  
  /// Descent from baseline
  virtual FXint getFontDescent() const;
  
  /// Get font leading [that is lead-ing as in Pb!]
  virtual FXint getFontLeading() const;
  
  /// Get font line spacing
  virtual FXint getFontSpacing() const;

  /// Calculate width of single wide character in this font
  virtual FXint getCharWidth(const FXwchar ch) const;

   /// Calculate width of given text in this font
   virtual FXint getTextWidth(const FXString& string) const;

   /// Calculate height of given text in this font
   virtual FXint getTextHeight(const FXString& string) const;
}
%enddef

%define DECLARE_FXGLCANVAS_VIRTUALS(klass)
%extend klass {
  /// Make OpenGL context current prior to performing OpenGL commands
  virtual FXbool makeCurrent();
  
  /// Make OpenGL context non current
  virtual FXbool makeNonCurrent();

  /// Return TRUE if context is current
  virtual FXbool isCurrent() const;

  /// Swap front and back buffer
  virtual void swapBuffers();
  }
%enddef

%define DECLARE_FXGLOBJECT_VIRTUALS(klass)
%extend klass {
  /// Clone this object
  virtual FXGLObject* copy();

  /// Called by the viewer to get bounds for this object
  virtual FXRangef bounds();

  /// Draw this object in a viewer
  virtual void draw(FXGLViewer* viewer);

  /// Draw this object for hit-testing purposes
  virtual void hit(FXGLViewer* viewer);

  /// Return true if this object can be dragged around
  virtual FXbool canDrag() const;

  /// Return true if this object can be deleted from the scene
  virtual FXbool canDelete() const;

  /// Drag this object from one position to another
  virtual FXbool drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty);
  }
%enddef

%define DECLARE_FXGLSHAPE_VIRTUALS(klass)
%extend klass {  
  // Draw shape into viewer
  virtual void drawshape(FXGLViewer*);
  
  // Set the position
  virtual void setPosition(const FXVec3f& pos);
  }
%enddef

%define DECLARE_FXGLVIEWER_VIRTUALS(klass)
%extend klass {
  /// Return a NULL-terminated list of all objects in the given rectangle, or NULL
  virtual FXGLObject** select(FXint x,FXint y,FXint w,FXint h);

  /// Perform a pick operation, returning the object at the given x,y position, or NULL
  virtual FXGLObject* pick(FXint x,FXint y);

  /// Change the model bounding box; this adjusts the viewer
  virtual FXbool setBounds(const FXRangef& box);
  }
%enddef

%define DECLARE_FXHEADERITEM_VIRTUALS(klass)
%extend klass {
  virtual void setText(const FXString& txt);
  virtual void setIcon(FXIcon *ic);
  virtual FXint getWidth(const FXHeader* header) const;
  virtual FXint getHeight(const FXHeader* header) const;
  virtual void create();
  virtual void detach();
  virtual void destroy();
  }
%enddef

%define DECLARE_FXICONITEM_VIRTUALS(klass)
%extend klass {
  virtual void draw(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual FXint hitItem(const FXIconList* list,FXint rx,FXint ry,FXint rw=1,FXint rh=1) const;
  virtual void drawBigIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawMiniIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawDetails(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void setText(const FXString& text);
  virtual void setBigIcon(FXIcon* icn,FXbool owned=false);
  virtual void setMiniIcon(FXIcon* icn,FXbool owned=false);
  virtual void setFocus(FXbool focus);
  virtual void setSelected(FXbool selected);
  virtual void setEnabled(FXbool enabled);
  virtual void setDraggable(FXbool draggable);
  virtual FXint getWidth(const FXIconList* list) const;
  virtual FXint getHeight(const FXIconList* list) const;
  virtual void create();
  virtual void detach();
  virtual void destroy();
  }
%enddef

%define DECLARE_FXICONLIST_VIRTUALS(klass)
%extend klass {
  /// Select item at index
  virtual FXbool selectItem(FXint index,FXbool notify=false);
  
  /// Deselect item at index
  virtual FXbool deselectItem(FXint index,FXbool notify=false);
  
  /// Toggle item at index
  virtual FXbool toggleItem(FXint index,FXbool notify=false);

  /// Select items in rectangle
  virtual FXbool selectInRectangle(FXint x,FXint y,FXint w,FXint h,FXbool notify=false);

  /// Extend selection from anchor index to index
  virtual FXbool extendSelection(FXint index,FXbool notify=false);

  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=false);

  /// Change current item index
  virtual void setCurrentItem(FXint index,FXbool notify=false);

  /// Return index of item at x,y, or -1 if none
  virtual FXint getItemAt(FXint x,FXint y) const;

  /// Scroll to make item at index visible
  virtual void makeItemVisible(FXint index);  

  /// Enable item at index
  virtual FXbool enableItem(FXint index);
  
  /// Disable item at index
  virtual FXbool disableItem(FXint index);
  }
%enddef

%define DECLARE_FXICONSOURCE_VIRTUALS(klass)
%extend klass {
  /**
  * Load an icon from the file filename. By default, the file extension is
  * stripped and used as the icon type; if an explicit icon type is forced,
  * then that type is used and the extension is ignored.
  * For example, loadIcon("icon","gif") will try to load a CompuServe GIF
  * file, since the filename does not give any clue as to the type of the
  * icon.
  */
  virtual FXIcon *loadIconFile(const FXString& filename,const FXString& type=FXString::null) const;

  /**
  * Load an icon of a given type (e.g. "gif") from reswrapped data.
  * Returns NULL if there's some error loading the icon.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the icon format if the parameter is omitted].
  */
  virtual FXIcon *loadIconData(const void *pixels,const FXString& type=FXString::null) const;

  /**
  * Load an icon of a given type (e.g. "gif") from an already open stream.
  * Returns NULL if there's some error loading the icon.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the icon format if the parameter is omitted].
  */
  virtual FXIcon *loadIconStream(FXStream& store,const FXString& type=FXString::null) const;

  /**
  * Load an image from the file filename. By default, the file extension is
  * stripped and used as the image type; if an explicit image type is forced,
  * then that type is used and the extension is ignored.
  * For example, loadImage("image","gif") will try to load a CompuServe GIF
  * file, since the filename does not give any clue as to the type of the
  * image.
  */
  virtual FXImage *loadImageFile(const FXString& filename,const FXString& type=FXString::null) const;

  /**
  * Load an image of a given type (e.g. "gif") from reswrapped data.
  * Returns NULL if there's some error loading the icon.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the icon format if the parameter is omitted].
  */
  virtual FXImage *loadImageData(const void *pixels,const FXString& type=FXString::null) const;
  
  /**
  * Load an image of a given type (e.g. "gif") from an already open stream.
  * Returns NULL if there's some error loading the image.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the image format if the parameter is omitted].
  */
  virtual FXImage *loadImageStream(FXStream& store,const FXString& type=FXString::null) const;

  /// Load icon and scale it such that its dimensions does not exceed given size
  virtual FXIcon *loadScaledIconFile(const FXString& filename,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load icon and scale it such that its dimensions does not exceed given size
  virtual FXIcon *loadScaledIconData(const void *pixels,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load icon and scale it such that its dimensions does not exceed given size
  virtual FXIcon *loadScaledIconStream(FXStream& store,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load image and scale it such that its dimensions does not exceed given size
  virtual FXImage *loadScaledImageFile(const FXString& filename,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load image and scale it such that its dimensions does not exceed given size
  virtual FXImage *loadScaledImageData(const void *pixels,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load image and scale it such that its dimensions does not exceed given size
  virtual FXImage *loadScaledImageStream(FXStream& store,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;
  }
%enddef

%define DECLARE_FXID_VIRTUALS(klass)
%extend klass {
  virtual void create();
  virtual void detach();
  virtual void destroy();
  }
%enddef

%define DECLARE_FXIMAGE_VIRTUALS(klass)
%extend klass {
  /**
  * Retrieves pixels from the server-side image.  For example, to make
  * screen snapshots, or to retrieve an image after it has been drawn
  * into by various means.
  */
  virtual void restore();

  /**
  * Render the server-side representation of the image from client-side
  * pixels.  Normally, IMAGE_DITHER is used which causes the server-side
  * representation to be rendered using a 16x16 ordered dither if necessary;
  * however if IMAGE_NEAREST is used a faster (but uglier-looking), nearest
  * neighbor algorithm is used.  
  */
  virtual void render();

   /**
   * Release the client-side pixels buffer, free it if it was owned.
   * If it is not owned, the image just forgets about the buffer.
   */
  virtual void release();
  
  /**
  * Rescale pixels image to the specified width and height; this calls 
  * resize() to adjust the client and server side representations.
  */
  virtual void scale(FXint w,FXint h,FXint quality=0);
  
  /// Mirror image horizontally and/or vertically
  virtual void mirror(bool horizontal,bool vertical);

  /**
  * Rotate image by degrees ccw; this calls resize() to adjust the client 
  * and server side representations if necessary.
  */
  virtual void rotate(FXint degrees);

  /**
  * Crop image to given rectangle; this calls resize() to adjust the client 
  * and server side representations.
  */
  virtual void crop(FXint x,FXint y,FXint w,FXint h,FXColor color=false);

  /// Fill image with uniform color
  virtual void fill(FXColor color);

  /// Fade image to uniform color
  virtual void fade(FXColor color,FXint factor=255);

  /**
  * Shear image horizontally; the number of pixels is equal to the
  * shear parameter times 256.  The area outside the image is filled
  * with transparent black, unless another color is specified.
  */
  virtual void xshear(FXint shear,FXColor clr=0);

  /**
  * Shear image vertically; the number of pixels is equal to the
  * shear parameter times 256.  The area outside the image is filled
  * with transparent black, unless another color is specified.
  */
  virtual void yshear(FXint shear,FXColor clr=0);

  /// Fill horizontal gradient
  virtual void hgradient(FXColor left,FXColor right);

  /// Fill vertical gradient
  virtual void vgradient(FXColor top,FXColor bottom);

  /// Fill with gradient
  virtual void gradient(FXColor topleft,FXColor topright,FXColor bottomleft,FXColor bottomright);

  /// Blend image over uniform color
  virtual void blend(FXColor color);

  virtual FXbool savePixels(FXStream& store) const;
  virtual FXbool loadPixels(FXStream& store);
  }
%enddef

%define DECLARE_FXLISTITEM_VIRTUALS(klass)
%extend klass {
  virtual void setText(const FXString& txt);
  virtual void setIcon(FXIcon* icn,FXbool owned=false);
  virtual void setFocus(FXbool focus);
  virtual void setSelected(FXbool selected);
  virtual void setEnabled(FXbool enabled);
  virtual void setDraggable(FXbool draggable);
  virtual FXint getWidth(const FXList* list) const;
  virtual FXint getHeight(const FXList* list) const;
  virtual void create();
  virtual void detach();
  virtual void destroy();
  }
%enddef

%define DECLARE_FXLIST_VIRTUALS(klass)
%extend klass {
  /// Enable item
  virtual FXbool enableItem(FXint index);
  
  /// Disable item
  virtual FXbool disableItem(FXint index);
  
  /// Scroll to bring item into view
  virtual void makeItemVisible(FXint index);
  
  /// Return index of item at x,y, if any
  virtual FXint getItemAt(FXint x,FXint y) const;
  
  /// Select item
  virtual FXbool selectItem(FXint index,FXbool notify=false);
  
  /// Deselect item
  virtual FXbool deselectItem(FXint index,FXbool notify=false);
  
  /// Toggle item selection state
  virtual FXbool toggleItem(FXint index,FXbool notify=false);

  /// Extend selection from anchor item to index
  virtual FXbool extendSelection(FXint index,FXbool notify=false);
  
  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=false);

  /// Change current item
  virtual void setCurrentItem(FXint index,FXbool notify=false);
  }
%enddef

%define DECLARE_FXLISTBOX_VIRTUALS(klass)
%extend klass {
  /// Set the current item (index is zero-based)
  virtual void setCurrentItem(FXint index,FXbool notify=false);
}
%enddef

%define DECLARE_FXMDICHILD_VIRTUALS(klass)
%extend klass {
  virtual FXbool minimize(FXbool notify=false);
  virtual FXbool maximize(FXbool notify=false);
  virtual FXbool restore(FXbool notify=false);
  virtual FXbool close(FXbool notify=false);
  }
%enddef

%define DECLARE_FXMDICLIENT_VIRTUALS(klass)
%extend klass {
  /// Set active MDI Child
  virtual FXbool setActiveChild(FXMDIChild* child=NULL,FXbool notify=true);

  // Cascade windows
  virtual void cascade(FXbool notify=false);

  // Layout horizontally
  virtual void horizontal(FXbool notify=false);

  // Layout vertically
  virtual void vertical(FXbool notify=false);
  }
%enddef

%define DECLARE_FXOBJECT_VIRTUALS(klass)
%extend klass {
  /// Save object to stream
  virtual void save(FXStream& store) const;

  /// Load object from stream
  virtual void load(FXStream& store);
  }
%enddef

%define DECLARE_FXPOPUP_VIRTUALS(klass)
%extend klass {
  virtual void popup(FXWindow* grabto,FXint x,FXint y,FXint w=0,FXint h=0);
  virtual void popdown();
  }
%enddef

%define DECLARE_FXREALSPINNER_VIRTUALS(klass)
%extend klass {
  virtual void setValue(FXdouble value,FXbool notify=false);
  }
%enddef

%define DECLARE_FXSCROLLAREA_VIRTUALS(klass)
%rename("visibleX")			klass::getVisibleX() const;
%rename("visibleY")			klass::getVisibleY() const;
%rename("visibleWidth")		klass::getVisibleWidth() const;
%rename("visibleHeight")	klass::getVisibleHeight() const;
%extend klass {
	// Return content area width
  virtual FXint getContentHeight();

  // Return content area height
  virtual FXint getContentWidth();

  /// Return visible scroll-area x position
  virtual FXint getVisibleX() const;

  /// Return visible scroll-area y position
  virtual FXint getVisibleY() const;

  /// Return visible scroll-area width
  virtual FXint getVisibleWidth() const;

  /// Return visible scroll-area height
  virtual FXint getVisibleHeight() const;
}
%enddef

%define DECLARE_FXSPINNER_VIRTUALS(klass)
%extend klass {
  virtual void setValue(FXint value,FXbool notify=false);
  }
%enddef

%define DECLARE_FXSHUTTER_VIRTUALS(klass)
%extend klass {
  virtual void setCurrent(FXint panel,FXbool notify=false);
  }
%enddef

%define DECLARE_FXSTREAM_VIRTUALS(klass)
%rename("setPosition") klass::position(FXlong offset,FXWhence whence);
%extend klass {
  virtual FXbool close();
  virtual FXbool flush();
  virtual FXbool position(FXlong offset,FXWhence whence=FXFromStart);
  }
%enddef

%define DECLARE_FXTABBAR_VIRTUALS(klass)
%extend klass {
  virtual void setCurrent(FXint panel,FXbool notify=false);
  }
%enddef

%define DECLARE_FXTABLEITEM_VIRTUALS(klass)
%extend klass {
  virtual void draw(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawBorders(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawContent(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawPattern(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawBackground(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  
  // Change item's text label
  virtual void setText(const FXString& txt);
  
  // Return item's text label
  virtual FXString getText() const;

  /// Change item's icon, deleting the old icon if it was owned
  virtual void setIcon(FXIcon* icn,FXbool owned=false);

  /// Return item's icon
  virtual FXIcon* getIcon() const;

  // Make item draw as focused
  virtual void setFocus(FXbool focus);

  // Select item
  virtual void setSelected(FXbool selected);
  
  // Enable or disable item
  virtual void setEnabled(FXbool enabled);
  
  // Make item draggable
  virtual void setDraggable(FXbool draggable);

  /// Change item content justification
  virtual void setJustify(FXuint justify=RIGHT|CENTER_Y);

  /// Change item icon position
  virtual void setIconPosition(FXuint mode);

  /// Change item borders
  virtual void setBorders(FXuint borders=0);

  /// Change item background stipple
  virtual void setStipple(FXStipplePattern pattern);

  /// Create input control for editing this item
  virtual FXWindow *getControlFor(FXTable* table);

  /// Set value from input control
  virtual void setFromControl(FXWindow *control);

  // Return width of item
  virtual FXint getWidth(const FXTable* table) const;
  
  // Return height of item
  virtual FXint getHeight(const FXTable* table) const;
  
  // Create server-side resources
  virtual void create();
  
  // Detach server-side resources
  virtual void detach();
  
  // Destroy server-side resources
  virtual void destroy();
  }
%enddef

%define DECLARE_FXTABLE_VIRTUALS(klass)
%extend klass {
  virtual void drawCell(FXDC& dc,FXint sr,FXint er,FXint sc,FXint ec);
  virtual void drawRange(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  virtual void drawHGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  virtual void drawVGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  virtual void drawContents(FXDC& dc,FXint x,FXint y,FXint w,FXint h);
  virtual FXTableItem* createItem(const FXString& text,FXIcon* icon,void* ptr);
  
  /// Set the table size to nr rows and nc columns; all existing items will be removed
  virtual void setTableSize(FXint nr,FXint nc,FXbool notify=false);

  /// Insert new row
  virtual void insertRows(FXint TABLE_ROW_ALL,FXint nr=1,FXbool notify=false);

  /// Insert new column
  virtual void insertColumns(FXint TABLE_COLUMN_ALL,FXint nc=1,FXbool notify=false);

  /// Remove rows of cells
  virtual void removeRows(FXint row,FXint nr=1,FXbool notify=false);

  /// Remove column of cells
  virtual void removeColumns(FXint col,FXint nc=1,FXbool notify=false);

  /// Extract item from table
  virtual FXTableItem* extractItem(FXint row,FXint col,FXbool notify=false);

  /// Clear single cell
  virtual void removeItem(FXint row,FXint col,FXbool notify=false);

  /// Clear all cells in the given range
  virtual void removeRange(FXint startrow,FXint endrow,FXint startcol,FXint endcol,FXbool notify=false);

  /// Remove all items from table
  virtual void clearItems(FXbool notify=false);

  /// Change column width
  virtual void setColumnWidth(FXint col,FXint cwidth);

  /// Change row height
  virtual void setRowHeight(FXint row,FXint rheight);

  /// Change current item
  virtual void setCurrentItem(FXint row_unchecked,FXint col_unchecked,FXbool notify=false);

  /// Select a row
  virtual FXbool selectRow(FXint row,FXbool notify=false);

  /// Select a column
  virtual FXbool selectColumn(FXint col,FXbool notify=false);

  /// Select range
  virtual FXbool selectRange(FXint startrow,FXint endrow,FXint startcol,FXint endcol,FXbool notify=false);

  /// Extend selection
  virtual FXbool extendSelection(FXint row_unchecked,FXint col_unchecked,FXbool notify=false);

  /// Kill selection
  virtual FXbool killSelection(FXbool notify=false);
  
  /**
  * Start input mode for the cell at the given position.
  * An input control is created which is used to edit the cell;
  * it is filled by the original item's contents if the cell contained
  * an item.  You can enter input mode also by sending the table an
  * ID_START_INPUT message.
  * Return true if editing of the cell has been started.
  */
  virtual FXbool startInput(FXint row_unchecked,FXint col_unchecked);

  /**
  * Cancel input mode.  The input control is immediately deleted
  * and the cell will retain its old value.  You can also cancel
  * input mode by sending the table an ID_CANCEL_INPUT message.
  * Return true if editing of the cell has been cancelled.
  */
  virtual FXbool cancelInput();

  /**
  * End input mode and accept the new value from the control.
  * The item in the cell will be set to the value from the control,
  * and the control will be deleted.  If TRUE is passed, a SEL_REPLACED
  * callback will be generated to signify to the target that this call
  * has a new value.  You can also accept the input by sending the table
  * an ID_ACCEPT_INPUT message.
  * Return true if the new value of the cell has been accepted.
  */
  virtual FXbool acceptInput(FXbool notify=false);

  /// Scroll to make cell at r,c fully visible
  virtual void makePositionVisible(FXint row_unchecked,FXint col_unchecked);
  
  /// Enable item
  virtual FXbool enableItem(FXint r,FXint c);

  /// Disable item
  virtual FXbool disableItem(FXint r,FXint c);
  }
%enddef

%define DECLARE_FXTEXT_VIRTUALS(klass)
%extend klass {
  virtual void setCursorPos(FXint pos,FXbool notify=false);

  /// Replace m bytes at pos by n characters
  virtual void replaceText(FXint pos,FXint m,const FXString& text,FXbool notify=false);

  /// Replace m bytes at pos by n characters
  virtual void replaceStyledText(FXint pos,FXint m,const FXString& text,FXint style=0,FXbool notify=false);

  /// Append n bytes of text at the end of the buffer
  virtual void appendText(const FXString& text,FXbool notify=false);

  /// Append n bytes of text at the end of the buffer
  virtual void appendStyledText(const FXString& text,FXint style=0,FXbool notify=false);

  /// Insert n bytes of text at position pos into the buffer
  virtual void insertText(FXint pos,const FXString& text,FXbool notify=false);

  /// Insert n bytes of text at position pos into the buffer
  virtual void insertStyledText(FXint pos,const FXString& text,FXint style=0,FXbool notify=false);

  /// Remove n bytes of text at position pos from the buffer
  virtual void removeText(FXint pos,FXint n,FXbool notify=false);

  /// Change style of text range
  virtual void changeStyle(FXint pos,FXint n,FXint style);
 
  /// Change style of text range from style-array
  virtual void changeStyle(FXint pos,const FXString& style);

  /// Change the text in the buffer to new text
  virtual void setText(const FXString& text,FXbool notify=false);
 
  /// Change the text in the buffer to new text
  virtual void setStyledText(const FXString& text,FXint style=0,FXbool notify=false);
  }
%enddef

%define DECLARE_FXTOPWINDOW_VIRTUALS(klass)
%extend klass {
  virtual void show(FXuint placement);
  virtual FXbool maximize(FXbool notify=false);
  virtual FXbool minimize(FXbool notify=false);
  virtual FXbool restore(FXbool notify=false);
  
  /**
  * Close the window, return TRUE if actually closed.  If notify=TRUE, the target
  * will receive a SEL_CLOSE message to determine if it is OK to close the window.
  * If the target ignores the SEL_CLOSE message or returns 0, the window will
  * be closed, and subsequently deleted.  When the last main window has been
  * closed, the application will receive an ID_QUIT message and will be closed.
  */
  virtual FXbool close(FXbool notify=false);

  // Flash the window to get the user's attention
  virtual void flash(FXbool yes);

  // Make window full screen, return true if success
  virtual FXbool fullScreen(FXbool notify=false);
  
  // Special stacking order level
  virtual FXbool stackingOrder(FXuint order);
  }
%enddef

%define DECLARE_FXTRANSLATOR_VIRTUALS(klass)
%extend klass {
  /// Translate a string
  virtual const FXchar* tr(const FXchar* context,const FXchar* message,const FXchar* hint=NULL,FXint count=-1) const;
}
%enddef

%define DECLARE_FXTREEITEM_VIRTUALS(klass)
%extend klass {
  // Change item label
  virtual void setText(const FXString& txt);
  
  // Change open icon, deleting the old one if it was owned
  virtual void setOpenIcon(FXIcon* icn,FXbool owned=false);
  
  // Change closed icon, deleting the old one if it was owned
  virtual void setClosedIcon(FXIcon* icn,FXbool owned=false);
  virtual void setFocus(FXbool focus);
  virtual void setSelected(FXbool selected);
  virtual void setOpened(FXbool opened);
  virtual void setExpanded(FXbool expanded);
  virtual void setEnabled(FXbool enabled);
  virtual void setDraggable(FXbool draggable);
  virtual FXint getWidth(const FXTreeList* list) const;
  virtual FXint getHeight(const FXTreeList* list) const;
  virtual void create();
  virtual void detach();
  virtual void destroy();
  }
%enddef

%define DECLARE_FXTREELIST_VIRTUALS(klass)
%extend klass {
  /// Select item
  virtual FXbool selectItem(FXTreeItem* item,FXbool notify=false);

  /// Deselect item
  virtual FXbool deselectItem(FXTreeItem* item,FXbool notify=false);

  /// Toggle item selection
  virtual FXbool toggleItem(FXTreeItem* item,FXbool notify=false);

  /// Extend selection from anchor item to item
  virtual FXbool extendSelection(FXTreeItem* item,FXbool notify=false);
  
  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=false);

  /// Open item
  virtual FXbool openItem(FXTreeItem* item,FXbool notify=false);

  /// Close item
  virtual FXbool closeItem(FXTreeItem* item,FXbool notify=false);

  /// Collapse tree
  virtual FXbool collapseTree(FXTreeItem* tree,FXbool notify=false);

  /// Expand tree 
  virtual FXbool expandTree(FXTreeItem* tree,FXbool notify=false);

  /// Change current item
  virtual void setCurrentItem(FXTreeItem* item,FXbool notify=false);

  /// Get item at x,y, if any
  virtual FXTreeItem* getItemAt(FXint x,FXint y) const;

  /// Scroll to make item visible
  virtual void makeItemVisible(FXTreeItem* item);

  /// Enable item
  virtual FXbool enableItem(FXTreeItem* item);

  /// Disable item
  virtual FXbool disableItem(FXTreeItem* item);
  }
%enddef

%define DECLARE_FXTREELISTBOX_VIRTUALS(klass)
%extend klass {
  /// Change current item
  virtual void setCurrentItem(FXTreeItem* item,FXbool notify=false);
  }
%enddef

%define DECLARE_FXWINDOW_VIRTUALS(klass)
%rename("raiseWindow") klass::raise();
%extend klass {
  virtual FXint getDefaultWidth();
  virtual FXint getDefaultHeight();
  virtual FXint getWidthForHeight(FXint givenheight);
  virtual FXint getHeightForWidth(FXint givenwidth);
  virtual FXbool canFocus() const;
  virtual void setFocus();
  virtual void killFocus();

  /// Notification that focus moved to new child
  virtual void changeFocus(FXWindow *child);

  virtual void setDefault(FXuchar flag=TRUE);
  virtual void enable();
  virtual void disable();
  virtual void raise();
  virtual void lower();

  /**
  * Move the window immediately, in the parent's coordinate system.
  * Update the server representation as well if the window is realized.
  * Perform layout of the children when necessary.
  */
  virtual void move(FXint x,FXint y);

  /**
  * Move and resize the window immediately, in the parent's coordinate system.
  * Update the server representation as well if the window is realized.
  * Perform layout of the children when necessary.
  */
  virtual void position(FXint x,FXint y,FXint w,FXint h);

  virtual void layout();
  virtual void recalc();
  virtual void reparent(FXWindow* father,FXWindow* other);
  virtual void show();
  virtual void hide();
  virtual FXbool isComposite() const;
  virtual FXbool contains(FXint parentx,FXint parenty) const;
  virtual FXbool doesSaveUnder() const;
  virtual void setBackColor(FXColor clr);

  /**
  * Translate message for localization; using the current FXTranslator,
  * an attempt is made to translate the given message into the current
  * language.  An optional hint may be passed to break any ties in case
  * more than one tranlation is possible for the given message text.
  * In addition, the name of the widget is passed as context name so
  * that translations for a single dialog may be grouped together.
  */
  virtual const FXchar* tr(const FXchar* message,const FXchar* hint=NULL,FXint count=-1) const;

  /// Enable this window to receive drops 
  virtual void dropEnable();

  /// Disable this window from receiving drops
  virtual void dropDisable();

  /// Set window shape by means of region
  virtual void setShape(const FXRegion& region);

  /// Set window shape by means of bitmap
  virtual void setShape(FXBitmap* bitmap);

  /// Set window shape by means of icon
  virtual void setShape(FXIcon* icon);

  /// Clear window shape
  virtual void clearShape();
  }
%enddef

