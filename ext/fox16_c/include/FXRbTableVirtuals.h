protected:
  // Overrides the base class versions of these virtual functions
  virtual void drawCell(FXDC& dc,FXint sr,FXint er,FXint sc,FXint ec);
  virtual void drawRange(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  virtual void drawHGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  virtual void drawVGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  virtual void drawContents(FXDC& dc,FXint x,FXint y,FXint w,FXint h);
  virtual FXTableItem* createItem(const FXString& text,FXIcon* icon,void* ptr);

public:
  // Publically accessible versions of those protected functions
  void public_drawCell(FXDC& dc,FXint sr,FXint er,FXint sc,FXint ec);
  void public_drawRange(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  void public_drawHGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  void public_drawVGrid(FXDC& dc,FXint rlo,FXint rhi,FXint clo,FXint chi);
  void public_drawContents(FXDC& dc,FXint x,FXint y,FXint w,FXint h);
  FXTableItem* public_createItem(const FXString& text,FXIcon* icon,void* ptr);

public:
  // Overrides the base class version of setTableSize()
  virtual void setTableSize(FXint nr,FXint nc,FXbool notify=FALSE);

  // Overrides the base class version of insertRows()
  virtual void insertRows(FXint row,FXint nr=1,FXbool notify=FALSE);

  // Overrides the base class version of insertColumns()
  virtual void insertColumns(FXint col,FXint nc=1,FXbool notify=FALSE);

  // Overrides the base class version of removeRows()
  virtual void removeRows(FXint row,FXint nr=1,FXbool notify=FALSE);

  // Overrides the base class version of removeColumns()
  virtual void removeColumns(FXint col,FXint nc=1,FXbool notify=FALSE);

  // Overrides the base class version of extractItem()
  virtual FXTableItem* extractItem(FXint row,FXint col,FXbool notify=FALSE);

  // Overrides the base class version of removeItem()
  virtual void removeItem(FXint row,FXint col,FXbool notify=FALSE);

  // Overrides the base class version of removeRange()
  virtual void removeRange(FXint startrow,FXint startcol,FXint endrow,FXint endcol,FXbool notify=FALSE);

  // Overrides the base class version of clearItems()
  virtual void clearItems(FXbool notify=FALSE);

  // Overrides the base class version of setColumnWidth()
  virtual void setColumnWidth(FXint col,FXint cwidth);

  // Overrides the base class version of setRowHeight()
  virtual void setRowHeight(FXint row,FXint rheight);

  // Overrides the base class version of setCurrentItem()
  virtual void setCurrentItem(FXint r,FXint c,FXbool notify=FALSE);

  /// Select a row
  virtual FXbool selectRow(FXint row,FXbool notify=FALSE);

  /// Select a column
  virtual FXbool selectColumn(FXint col,FXbool notify=FALSE);

  // Overrides the base class version of selectRange()
  virtual FXbool selectRange(FXint sr,FXint er,FXint sc,FXint ec,FXbool notify=FALSE);

  // Overrides the base class version of extendSelection()
  virtual FXbool extendSelection(FXint r,FXint c,FXbool notify=FALSE);

  // Overrides the base class version of killSelection()
  virtual FXbool killSelection(FXbool notify=FALSE);

  // Overrides base class version of startInput()
  virtual void startInput(FXint row,FXint col);

  // Overrides base class version of cancelInput()
  virtual void cancelInput();

  // Overrides base class version of acceptInput()
  virtual void acceptInput(FXbool notify=FALSE);

  // Overrides the base class version of makePositionVisible()
  virtual void makePositionVisible(FXint r,FXint c);

  // Overrides the base class version of enableItem()
  virtual FXbool enableItem(FXint r,FXint c);

  // Overrides the base class version of disableItem()
  virtual FXbool disableItem(FXint r,FXint c);


