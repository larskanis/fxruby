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

class FXTable;

// Default cell margin
enum { DEFAULT_MARGIN = 2 };


/// Table options
enum {
  TABLE_COL_SIZABLE     = 0x00100000,   /// Columns are resizable
  TABLE_ROW_SIZABLE     = 0x00200000,   /// Rows are resizable
  TABLE_NO_COLSELECT    = 0x00400000,   /// Disallow column selections
  TABLE_NO_ROWSELECT    = 0x00800000,   /// Disallow row selections
  TABLE_READONLY        = 0x01000000,   /// Table is NOT editable
  TABLE_COL_RENUMBER    = 0x02000000,   /// Renumber columns
  TABLE_ROW_RENUMBER    = 0x04000000    /// Renumber rows
  };


// Position in table
struct FXTablePos {
  FXTablePos();
  FXint  row;
  FXint  col;
  ~FXTablePos();
  };
  

// Range of table cells
struct FXTableRange {
  FXTableRange();
  FXTablePos fm;
  FXTablePos to;
  ~FXTableRange();
  };


/// Item in table
class FXTableItem : public FXObject {
protected:
  FXString    label;
  FXIcon     *icon;
  void       *data;
  FXuint      state;
protected:
  FXTableItem():icon(NULL),data(NULL),state(0){}
  FXint textWidth(const FXTable* table) const;
  FXint textHeight(const FXTable* table) const;
  virtual void draw(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawBorders(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawContent(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawPattern(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
  virtual void drawBackground(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;
protected:
  FXTableItem();
public:
  enum{    
    SELECTED   = 0x00000001,    /// Selected
    FOCUS      = 0x00000002,    /// Focus
    DISABLED   = 0x00000004,    /// Disabled
    DRAGGABLE  = 0x00000008,    /// Draggable
    RESERVED1  = 0x00000010,    /// Reserved
    RESERVED2  = 0x00000020,    /// Reserved
    ICONOWNED  = 0x00000040,    /// Icon owned by table item
    RIGHT      = 0x00002000,    /// Align on right (default)
    LEFT       = 0x00004000,    /// Align on left
    CENTER_X   = 0,             /// Align centered horizontally
    TOP        = 0x00008000,    /// Align on top
    BOTTOM     = 0x00010000,    /// Align on bottom
    CENTER_Y   = 0,             /// Align centered vertically (default)
    BEFORE     = 0x00020000,    /// Icon before the text
    AFTER      = 0x00040000,    /// Icon after the text
    ABOVE      = 0x00080000,    /// Icon above the text
    BELOW      = 0x00100000,    /// Icon below the text
    LBORDER    = 0x00200000,    /// Draw left border
    RBORDER    = 0x00400000,    /// Draw right border
    TBORDER    = 0x00800000,    /// Draw top border
    BBORDER    = 0x01000000     /// Draw bottom border
    };
public:
  %extend {
    // Construct new table item
    FXTableItem(const FXString& text,FXIcon* ic=NULL,void* ITEMDATA=NULL){
      return new FXRbTableItem(text,ic,ITEMDATA);
      }
    }

  %extend {
    // Change item's user data
    void setData(VALUE ptr){
      self->setData(reinterpret_cast<void*>(ptr));
      }

    // Get item's user data
    VALUE getData() const {
      return self->getData() ? reinterpret_cast<VALUE>(self->getData()) : Qnil;
      }
  }
  
  // Return true if item has focus
  FXbool hasFocus() const;
  
  // Return true if item is selected
  FXbool isSelected() const;
  
  // Return true if item is enabled
  FXbool isEnabled() const;
  
  // Return true if item is draggable
  FXbool isDraggable() const;

  // Return item content justification
  FXuint getJustify() const;

  // Return item icon position
  FXuint getIconPosition() const;

  // Return item borders
  FXuint getBorders() const;

  // Return item background stipple
  FXStipplePattern getStipple() const;

  // Destructor
  virtual ~FXTableItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTableItem)
DECLARE_FXTABLEITEM_VIRTUALS(FXTableItem)

// Enforce row numbers that are within bounds 0 <= row < numRows
%typemap(check) FXint TABLE_ROW_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumRows()) {
    rb_raise(rb_eIndexError, "table row out of bounds");
  }
}

// Enforce row numbers that are within bounds 0 <= row <= numRows
%typemap(check) FXint TABLE_ROW_ALL {
  if ($1 < 0 || $1 > arg1->getNumRows()) {
    rb_raise(rb_eIndexError, "table row out of bounds");
  }
}

// Enforce row = 0 or row = 1 only
%typemap(check) FXint ROW_ZERO_OR_ONE {
  if ($1 != 0 && $1 != 1) {
    rb_raise(rb_eIndexError, "table row out of bounds");
  }
}

// Special for removeRows()
%typemap(check) (FXint row,FXint nr) {
  if ($1 < 0 || $1 + $2 > arg1->getNumRows()) {
    rb_raise(rb_eIndexError,"table row out of bounds");
  }
}

// Enforce column numbers that are within bounds 0 <= column < numColumns
%typemap(check) FXint TABLE_COLUMN_INDEX {
  if ($1 < 0 || $1 >= arg1->getNumColumns()) {
    rb_raise(rb_eIndexError, "table column out of bounds");
  }
}

// Enforce column numbers that are within bounds 0 <= column <= numColumns
%typemap(check) FXint TABLE_COLUMN_ALL {
  if ($1 < 0 || $1 > arg1->getNumColumns()) {
    rb_raise(rb_eIndexError, "table column out of bounds");
  }
}

// Enforce column = 0 or column = 1 only
%typemap(check) FXint COLUMN_ZERO_OR_ONE {
  if ($1 != 0 && $1 != 1) {
    rb_raise(rb_eIndexError, "table column out of bounds");
  }
}

// Special for removeColumns()
%typemap(check) (FXint col,FXint nc) {
  if ($1 < 0 || $1 + $2 > arg1->getNumColumns()) {
    rb_raise(rb_eIndexError,"table column out of bounds");
  }
}

%apply FXint TABLE_ROW_INDEX { FXint row, FXint r, FXint startrow, FXint endrow };
%apply FXint TABLE_COLUMN_INDEX { FXint col, FXint c, FXint startcol, FXint endcol };

%rename("editable=")          FXTable::setEditable(FXbool);
%rename("editable?")          FXTable::isEditable() const;
%rename("cornerButton")       FXTable::getCornerButton() const;
%rename("columnRenumbering=") FXTable::setColumnRenumbering(FXbool flag);
%rename("columnRenumbering?") FXTable::getColumnRenumbering() const;
%rename("rowRenumbering=")    FXTable::setRowRenumbering(FXbool flag);
%rename("rowRenumbering?")    FXTable::getRowRenumbering() const;

/**
* The Table widget displays a table of items, each with a text and optional
* icon.  A column Header control provide captions for each column, and a row
* Header control provides captions for each row.  Columns are resizable by
* means of the column Header control if the TABLE_COL_SIZABLE option is passed.
* Likewise, rows in the table are resizable if the TABLE_ROW_SIZABLE option is
* specified.  An entire row (column) can be selected by clicking on the a button
* in the row (column) Header control.  Passing TABLE_NO_COLSELECT disables column
* selection, and passing TABLE_NO_ROWSELECT disables column selection.
* When TABLE_COL_RENUMBER is specified, columns are automatically renumbered when
* columns are added or removed.  Similarly, TABLE_ROW_RENUMBER will cause row numbers
* to be recalculated automatically when rows are added or removed.
* To disable editing of cells in the table, the TABLE_READONLY can be specified.
* Cells in the table may or may not have items in them.  When populating a cell
* for the first time, an item will be automatically created if necessary.  Thus,
* a cell in the table takes no space unless it has actual contents.
* Moreover, a contiguous, rectangular region of cells in the table may refer to
* one single item; in that case, the item will be stretched to cover all the
* cells in the region, and no grid lines will be drawn interior to the spanning
* item.
* The Table widget issues SEL_SELECTED or SEL_DESELECTED when cells are selected
* or deselected, respectively.  The table position affected is passed along as the
* 3rd parameter of these messages.
* Whenever the current (focus) item is changed, a SEL_CHANGED message is sent with
* the new table position as a parameter.
* When items are added to the table, a SEL_INSERTED message is sent, with the table
* range of the newly added cells as the parameter in the message.
* When items are removed from the table, a SEL_DELETED message is sent prior to the
* removal of the items, and the table range of the removed cells is passed as a parameter.
* A SEL_REPLACED message is sent when the contents of a cell are changed, either through
* editing or by other means; the parameter is the range of affected cells.  This message
* is sent prior to the change.
* SEL_CLICKED, SEL_DOUBLECLICKED, and SEL_TRIPLECLICKED messages are sent when a cell
* is clicked, double-clicked, or triple-clicked, respectively.
* A SEL_COMMAND is sent when an enabled item is clicked inside the table.
*/
class FXTable : public FXScrollArea {
public:
  static FXDragType csvType;
  static const FXchar csvTypeName[];
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelectionRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardRequest(FXObject*,FXSelector,void* PTR_EVENT);
  long onAutoScroll(FXObject*,FXSelector,void* PTR_EVENT);
  long onCommand(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onClicked(FXObject*,FXSelector,void* PTR_EVENT);
  long onDoubleClicked(FXObject*,FXSelector,void* PTR_EVENT);
  long onTripleClicked(FXObject*,FXSelector,void* PTR_EVENT);
  long onQueryTip(FXObject*,FXSelector,void* PTR_NULL);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_NULL);
  long onTipTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  
  long onCmdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);

  // Visual characteristics
  long onCmdHorzGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdHorzGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdVertGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdVertGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  
  // Row/Column manipulations
  long onCmdDeleteColumn(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdDeleteColumn(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdDeleteRow(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdDeleteRow(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdInsertColumn(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdInsertColumn(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdInsertRow(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onUpdInsertRow(FXObject*,FXSelector,void* PTR_IGNORE);
  
  // Movement
  long onCmdMoveRight(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMoveLeft(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMoveUp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMoveDown(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMoveHome(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMoveEnd(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMoveTop(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMoveBottom(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMovePageDown(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdMovePageUp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME

  // Mark and extend
  long onCmdMark(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdExtend(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME

  // Changing Selection
  long onUpdSelectCell(FXObject*,FXSelector,void*); // FIXME
  long onCmdSelectCell(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSelectRow(FXObject*,FXSelector,void*); // FIXME
  long onCmdSelectRow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSelectColumn(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSelectColumn(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectRowIndex(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSelectColumnIndex(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDeselectAll(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdDeselectAll(FXObject*,FXSelector,void* PTR_IGNORE);

  // Manipulation Selection
  long onCmdCutSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCopySel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPasteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdHaveSelection(FXObject*,FXSelector,void* PTR_IGNORE);

  // Edit control
  long onCmdStartInput(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdStartInput(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdAcceptInput(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdAcceptInput(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCancelInput(FXObject*,FXSelector,void* PTR_IGNORE);

public:

  enum {
    ID_HORZ_GRID=FXScrollArea::ID_LAST,
    ID_VERT_GRID,
    ID_TOGGLE_EDITABLE,
    ID_DELETE_COLUMN,
    ID_DELETE_ROW,
    ID_INSERT_COLUMN,
    ID_INSERT_ROW,
    ID_SELECT_COLUMN_INDEX,
    ID_SELECT_ROW_INDEX,
    ID_SELECT_COLUMN,
    ID_SELECT_ROW,
    ID_SELECT_CELL,
    ID_SELECT_ALL,
    ID_DESELECT_ALL,
    ID_MOVE_LEFT,
    ID_MOVE_RIGHT,
    ID_MOVE_UP,
    ID_MOVE_DOWN,
    ID_MOVE_HOME,
    ID_MOVE_END,
    ID_MOVE_TOP,
    ID_MOVE_BOTTOM,
    ID_MOVE_PAGEDOWN,
    ID_MOVE_PAGEUP,
    ID_START_INPUT,
    ID_CANCEL_INPUT,
    ID_ACCEPT_INPUT,
    ID_MARK,
    ID_EXTEND,
    ID_CUT_SEL,
    ID_COPY_SEL,
    ID_PASTE_SEL,
    ID_DELETE_SEL,
    ID_LAST
    };

public:
  
  /**
  * Construct a new table.
  * The table is initially empty, and reports a default size based on
  * the scroll areas's scrollbar placement policy.
  */
  %extend {
    FXTable(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_MARGIN,FXint pr=DEFAULT_MARGIN,FXint pt=DEFAULT_MARGIN,FXint pb=DEFAULT_MARGIN){
      return new FXRbTable(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }
  
  /// Return button in the top/left corner
  FXButton* getCornerButton() const;

  /// Return column header control
  FXHeader* getColumnHeader() const;

  /// Return row header control
  FXHeader* getRowHeader() const;

  /// Change number of visible rows
  void setVisibleRows(FXint nvrows);
  
  /// Return number of visible rows
  FXint getVisibleRows() const;
  
  // Change number of visible columns
  void setVisibleColumns(FXint nvcols);
  
  // Return number of visible columns
  FXint getVisibleColumns() const;
 
  /// Return TRUE if table is editable
  FXbool isEditable() const;

  /// Set editable flag
  void setEditable(FXbool edit=true);

  /// Show or hide horizontal grid
  void showHorzGrid(FXbool on=true);

  /// Is horizontal grid shown
  FXbool isHorzGridShown() const;

  /// Show or hide vertical grid
  void showVertGrid(FXbool on=true);
  
  /// Is vertical grid shown
  FXbool isVertGridShown() const;

  /// Get number of rows
  FXint getNumRows() const;

  /// Get number of columns
  FXint getNumColumns() const;

  /// Change top cell margin
  void setMarginTop(FXint pt);

  /// Return top cell margin
  FXint getMarginTop() const;

  /// Change bottom cell margin
  void setMarginBottom(FXint pb);

  /// Return bottom cell margin
  FXint getMarginBottom() const;

  /// Change left cell margin
  void setMarginLeft(FXint pl);

  /// Return left cell margin
  FXint getMarginLeft() const;

  /// Change right cell margin
  void setMarginRight(FXint pr);

  /// Return right cell margin
  FXint getMarginRight() const;

  /**
  * Determine column containing x.
  * Returns -1 if x left of first column, and ncols if x right of last column;
  * otherwise, returns column in table containing x.
  */
  FXint colAtX(FXint x) const;

  /**
  * Determine row containing y.
  * Returns -1 if y above first row, and nrows if y below last row;
  * otherwise, returns row in table containing y.
  */
  FXint rowAtY(FXint y) const;
  
  /// Return the item at the given index
  FXTableItem *getItem(FXint row,FXint col) const;

  %extend {
    /// Replace the item with a [possibly subclassed] item
    void setItem(FXint row,FXint col,FXTableItem* item,FXbool notify=false){
      if(item!=0 && item->isMemberOf(FXMETACLASS(FXRbTableItem))){
        dynamic_cast<FXRbTableItem*>(item)->owned=TRUE;
        }
      self->setItem(row,col,item,notify);
      }
  }

  // Return TRUE if item partially visible
  FXbool isItemVisible(FXint r,FXint c) const;

  /**
  * Change column header height mode to fixed or variable.
  * In variable height mode, the column header will size to
  * fit the contents in it.  In fixed mode, the size is
  * explicitly set using setColumnHeaderHeight().
  * The default is to determine the column header height
  * based on the contents, using the LAYOUT_MIN_HEIGHT option.
  */
  void setColumnHeaderMode(FXuint hint=LAYOUT_FIX_HEIGHT);

  /// Return column header height mode
  FXuint getColumnHeaderMode() const;

  /**
  * Change row header width mode to fixed or variable.
  * In variable width mode, the row header will size to
  * fit the contents in it.  In fixed mode, the size is
  * explicitly set using setRowHeaderWidth().
  */
  void setRowHeaderMode(FXuint hint=LAYOUT_FIX_WIDTH);

  /// Return row header width mode
  FXuint getRowHeaderMode() const;

  /// Set column header font
  void setColumnHeaderFont(FXFont* fnt);

  /// Return column header font
  FXFont* getColumnHeaderFont() const;

  /// Set row header font
  void setRowHeaderFont(FXFont* fnt);

  /// Return row header font
  FXFont* getRowHeaderFont() const;

  /// Change column header height
  void setColumnHeaderHeight(FXint h);

  /// Return column header height
  FXint getColumnHeaderHeight() const;

  /// Change row header width
  void setRowHeaderWidth(FXint w);

  /// Return row header width
  FXint getRowHeaderWidth() const;

  %extend {
    FXint getColumnX(FXint colEdge) const {
      if(colEdge<0 || self->getColumnHeader()->getNumItems()<=colEdge){
        rb_raise(rb_eIndexError,"table column out of bounds");
        }
      return self->getColumnX(colEdge);
      }
  
    /// Change Y coordinate of row r
    FXint getRowY(FXint rowEdge) const {
      if(rowEdge<0 || self->getRowHeader()->getNumItems()<=rowEdge){
        rb_raise(rb_eIndexError,"table row out of bounds");
        }
      return self->getRowY(rowEdge);
      }
  }
  
  /// Get column width
  FXint getColumnWidth(FXint col) const;

  /// Get row height
  FXint getRowHeight(FXint row) const;

  /// Change default column width
  void setDefColumnWidth(FXint cwidth);
  
  /// Get default column width
  FXint getDefColumnWidth() const;

  /// Change default row height
  void setDefRowHeight(FXint rheight);
  
  /// Get default row height
  FXint getDefRowHeight() const;

  /// Return minimum row height
  FXint getMinRowHeight(FXint r) const;

  /// Return minimum column width
  FXint getMinColumnWidth(FXint c) const;

  /// Fit row heights to contents
  void fitRowsToContents(FXint row,FXint nr=1);

  /// Fit column widths to contents
  void fitColumnsToContents(FXint col,FXint nc=1);

  /// Change column header
  void setColumnText(FXint TABLE_COLUMN_INDEX,const FXString& text);

  /// Return text of column header at index
  FXString getColumnText(FXint TABLE_COLUMN_INDEX) const;

  /// Change row header
  void setRowText(FXint TABLE_ROW_INDEX,const FXString& text);

  /// Return text of row header at index
  FXString getRowText(FXint TABLE_ROW_INDEX) const;

  /// Change column header icon
  void setColumnIcon(FXint TABLE_COLUMN_INDEX,FXIcon* icon);

  /// Return icon of column header at index
  FXIcon* getColumnIcon(FXint TABLE_COLUMN_INDEX) const;

  /// Change row header icon
  void setRowIcon(FXint TABLE_ROW_INDEX,FXIcon* icon);

  /// Return icon of row header at index
  FXIcon* getRowIcon(FXint TABLE_ROW_INDEX) const;

  /// Change column header tip text
  void setColumnTipText(FXint index,const FXString& text);

  /// Return tip text of column header at index
  FXString getColumnTipText(FXint index) const;

  /// Change row header tip text
  void setRowTipText(FXint index,const FXString& text);

  /// Return tip text of row header at index
  FXString getRowTipText(FXint index) const;

  /// Change column header icon position, e.g. FXHeaderItem::BEFORE, etc.
  void setColumnIconPosition(FXint TABLE_COLUMN_INDEX,FXuint mode);

  /// Return icon position of column header at index
  FXuint getColumnIconPosition(FXint TABLE_COLUMN_INDEX) const;

  /// Change row header icon position, e.g. FXHeaderItem::BEFORE, etc.
  void setRowIconPosition(FXint TABLE_ROW_INDEX,FXuint mode);

  /// Return icon position of row header at index
  FXuint getRowIconPosition(FXint TABLE_ROW_INDEX) const;

  /// Change column header justify, e.g. FXHeaderItem::RIGHT, etc.
  void setColumnJustify(FXint TABLE_COLUMN_INDEX,FXuint justify);

  /// Return justify of column header at index
  FXuint getColumnJustify(FXint TABLE_COLUMN_INDEX) const;

  /// Change row header justify, e.g. FXHeaderItem::RIGHT, etc.
  void setRowJustify(FXint TABLE_ROW_INDEX,FXuint justify);

  /// Return justify of row header at index
  FXuint getRowJustify(FXint TABLE_ROW_INDEX) const;

  %extend {
    /// Modify cell text
    void setItemText(FXint r,FXint c,const FXString& text,FXbool notify=false){
      FXRbTableItem* item;
      self->setItemText(r,c,text,notify);
      item=dynamic_cast<FXRbTableItem*>(self->getItem(r,c));
      if(item!=0){
        item->owned=TRUE;
        }
      }
  }
  
  // Get cell text
  FXString getItemText(FXint r,FXint c) const;

  %extend {  
    /// Modify cell icon, deleting the old icon if it was owned
    void setItemIcon(FXint r,FXint c,FXIcon* icon,FXbool notify=false){
      FXRbTableItem* item;
      self->setItemIcon(r,c,icon,notify);
      item=dynamic_cast<FXRbTableItem*>(self->getItem(r,c));
      if(item!=0){
        item->owned=TRUE;
        }
      }
  }
  
  // Get the item's icon
  FXIcon* getItemIcon(FXint r,FXint c) const;
  
  %extend {
    /// Modify cell user-data
    void setItemData(FXint r,FXint c,VALUE ptr){
      FXRbTableItem* item;
      self->setItemData(r,c,reinterpret_cast<void*>(ptr));
      item=dynamic_cast<FXRbTableItem*>(self->getItem(r,c));
      if(item!=0){
        item->owned=TRUE;
        }
      }

    /// Get cell user data
    VALUE getItemData(FXint r,FXint c) const {
      void* ptr=self->getItemData(r,c);
      return (ptr!=0) ? reinterpret_cast<VALUE>(ptr) : Qnil;
      }
  }
  
  %extend {
    /// Extract cells from given range as text.
    VALUE extractText(FXint startrow,FXint endrow,FXint startcol,FXint endcol,const FXchar* cs="\t",const FXchar* rs="\n") const {
      FXString str;
      VALUE result;
      if(startrow<0 || startcol<0 || self->getNumRows()<=endrow || self->getNumColumns()<=endcol) rb_raise(rb_eIndexError,"index out of bounds");
      self->extractText(str,startrow,endrow,startcol,endcol,cs,rs);
      result=rb_str_new2(str.text());
      return result;
      }

    /// Overlay text over given cell range
    void overlayText(FXint startrow,FXint endrow,FXint startcol,FXint endcol,VALUE str,const FXchar* cs="\t",const FXchar* rs="\n",FXbool notify=false){
      if(startrow<0 || startcol<0 || self->getNumRows()<=endrow || self->getNumColumns()<=endcol) rb_raise(rb_eIndexError,"index out of bounds");
      const FXchar* text=reinterpret_cast<FXchar*>(StringValuePtr(str));
      FXint size=RSTRING_LEN(str);
      self->overlayText(startrow,endrow,startcol,endcol,text,size,cs,rs,notify);
      }
  }

  %extend {
    /**
    * Determine the number of rows and columns in a block of text
    * where columns are separated by characters from the set cs, and rows
    * are separated by characters from the set rs.
    */
    VALUE countText(const FXString& text,const FXchar* cs="\t,",const FXchar* rs="\n") const {
      FXint nr,nc;
      self->countText(nr,nc,text,cs,rs);
      return rb_ary_new3(2,INT2NUM(nr),INT2NUM(nc));
      }
  }

  /// Return TRUE if its a spanning cell
  FXbool isItemSpanning(FXint r,FXint c) const;

  %extend {
    /// Repaint cells between grid lines sr,er and grid lines sc,ec
    void updateRange(FXint sr,FXint er,FXint sc,FXint ec) const {
      if(sr<0 || sc<0 || self->getNumRows()<=er || self->getNumColumns()<=ec) rb_raise(rb_eIndexError,"index out of bounds");
      self->updateRange(sr,er,sc,ec);
      }
  }

  /// Repaint cell at r,c
  void updateItem(FXint r,FXint c) const;
  
  // Is item enabled?
  FXbool isItemEnabled(FXint r,FXint c) const;

  /**
  * Change item justification.  Horizontal justification is controlled by passing
  * FXTableItem::RIGHT,  FXTableItem::LEFT, or FXTableItem::CENTER_X.
  * Vertical justification is controlled by FXTableItem::TOP, FXTableItem::BOTTOM,
  * or FXTableItem::CENTER_Y.
  * The default is a combination of FXTableItem::RIGHT and FXTableItem::CENTER_Y.
  */
  void setItemJustify(FXint r,FXint c,FXuint justify);
  
  /// Return item justification
  FXuint getItemJustify(FXint r,FXint c) const;
  
  /**
  * Change relative position of icon and text of item.
  * Passing FXTableItem::BEFORE or FXTableItem::AFTER places the icon
  * before or after the text, and passing FXTableItem::ABOVE or
  * FXTableItem::BELOW places it above or below the text, respectively.
  * The default is 0 which places the text on top of the icon.
  */
  void setItemIconPosition(FXint r,FXint c,FXuint mode);
  
  /// Return relative icon and text position
  FXuint getItemIconPosition(FXint r,FXint c) const;
  
  /**
  * Change item borders style.  Borders on each side of the item can be turned
  * controlled individually using FXTableItem::LBORDER, FXTableItem::RBORDER,
  * FXTableItem::TBORDER and FXTableItem::BBORDER.
  */
  void setItemBorders(FXint r,FXint c,FXuint borders);
  
  /// Return item border style
  FXuint getItemBorders(FXint r,FXint c) const;
  
  /// Change item background stipple style
  void setItemStipple(FXint r,FXint c,FXStipplePattern pat);
  
  /// Return item background stipple style
  FXStipplePattern getItemStipple(FXint r,FXint c) const;

  /// Get row number of current item
  FXint getCurrentRow() const;

  /// Get column number of current item
  FXint getCurrentColumn() const;

  /// Is this the current item?
  FXbool isItemCurrent(FXint r,FXint c) const;

  /// Change anchor item
  void setAnchorItem(FXint r,FXint c);

  /// Get row number of anchor item
  FXint getAnchorRow() const;

  /// Get column number of anchor item
  FXint getAnchorColumn() const;

  /// Get selection start row; returns -1 if no selection
  FXint getSelStartRow() const;

  /// Get selection start column; returns -1 if no selection
  FXint getSelStartColumn() const;

  /// Get selection end row; returns -1 if no selection
  FXint getSelEndRow() const;

  /// Get selection end column; returns -1 if no selection
  FXint getSelEndColumn() const;

  /// Is item selected?
  FXbool isItemSelected(FXint r,FXint c) const;
  
  /// Is row of cells selected
  FXbool isRowSelected(FXint r) const;

  /// Is column selected
  FXbool isColumnSelected(FXint c) const;

  /// Is anything selected
  FXbool isAnythingSelected() const;

  /// Change font
  void setFont(FXFont* fnt);
  FXFont* getFont() const;

  /// Obtain colors of various parts
  FXColor getTextColor() const;
  FXColor getBaseColor() const;
  FXColor getHiliteColor() const;
  FXColor getShadowColor() const;
  FXColor getBorderColor() const;
  FXColor getSelBackColor() const;
  FXColor getSelTextColor() const;
  FXColor getGridColor() const;
  FXColor getStippleColor() const;
  FXColor getCellBorderColor() const;

  /// Change colors of various parts
  void setTextColor(FXColor clr);
  void setBaseColor(FXColor clr);
  void setHiliteColor(FXColor clr);
  void setShadowColor(FXColor clr);
  void setBorderColor(FXColor clr);
  void setSelBackColor(FXColor clr);
  void setSelTextColor(FXColor clr);
  void setGridColor(FXColor clr);
  void setStippleColor(FXColor clr);
  void setCellBorderColor(FXColor clr);

  /// Change cell background color for even/odd rows/columns
  void setCellColor(FXint ROW_ZERO_OR_ONE,FXint COLUMN_ZERO_OR_ONE,FXColor clr);

  /// Obtain cell background color for even/odd rows/columns
  FXColor getCellColor(FXint ROW_ZERO_OR_ONE,FXint COLUMN_ZERO_OR_ONE) const;

  /// Change cell border width
  void setCellBorderWidth(FXint borderwidth);

  /// Return cell border width
  FXint getCellBorderWidth() const;

  /// Change table style
  FXuint getTableStyle() const;
  void setTableStyle(FXuint style);
  
  /// Set column renumbering
  void setColumnRenumbering(FXbool flag);

  /// Get column renumbering
  FXbool getColumnRenumbering() const;

  /// Set row renumbering
  void setRowRenumbering(FXbool flag);

  /// Get row renumbering
  FXbool getRowRenumbering() const;

  /// Change help text
  void setHelpText(const FXString& text);
  
  /// Get help text
  const FXString& getHelpText() const;

  /// Destructor
  virtual ~FXTable();
  };

%clear FXint r;
%clear FXint row;
%clear FXint c;
%clear FXint col;

DECLARE_FXOBJECT_VIRTUALS(FXTable)
DECLARE_FXID_VIRTUALS(FXTable)
DECLARE_FXDRAWABLE_VIRTUALS(FXTable)
DECLARE_FXWINDOW_VIRTUALS(FXTable)
DECLARE_FXSCROLLAREA_VIRTUALS(FXTable)
DECLARE_FXTABLE_VIRTUALS(FXTable)

