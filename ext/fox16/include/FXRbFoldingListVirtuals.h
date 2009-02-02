public:
  // Overrides the base class version of getItemAt()
  virtual FXFoldingItem *getItemAt(FXint x,FXint y) const;

  // Overrides the base class version of makeItemVisible()
  virtual void makeItemVisible(FXFoldingItem* item);

  /// Overrides the base class version of enableItem()
  virtual FXbool enableItem(FXFoldingItem* item);

  /// Overrides the base class version of disableItem()
  virtual FXbool disableItem(FXFoldingItem* item);

  /// Overrides the base class version of selectItem()
  virtual FXbool selectItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Overrides the base class version of deselectItem()
  virtual FXbool deselectItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Overrides the base class version of toggleItem()
  virtual FXbool toggleItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Extend selection from anchor item to item
  virtual FXbool extendSelection(FXFoldingItem* item,FXbool notify=FALSE);

  /// Deselect all items
  virtual FXbool killSelection(FXbool notify=FALSE);

  /// Open item
  virtual FXbool openItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Close item
  virtual FXbool closeItem(FXFoldingItem* item,FXbool notify=FALSE);

  /// Collapse tree
  virtual FXbool collapseTree(FXFoldingItem* tree,FXbool notify=FALSE);

  /// Expand tree
  virtual FXbool expandTree(FXFoldingItem* tree,FXbool notify=FALSE);

  /// Change current item
  virtual void setCurrentItem(FXFoldingItem* item,FXbool notify=FALSE);

