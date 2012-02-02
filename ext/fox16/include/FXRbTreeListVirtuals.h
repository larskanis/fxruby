public:
  // Overrides the base class version of selectItem()
  virtual FXbool selectItem(FXTreeItem* item,FXbool notify=FALSE);

  // Overrides the base class version of deselectItem()
  virtual FXbool deselectItem(FXTreeItem* item,FXbool notify=FALSE);

  // Overrides the base class version of toggleItem()
  virtual FXbool toggleItem(FXTreeItem* item,FXbool notify=FALSE);

  // Overrides the base class version of extendSelection()
  virtual FXbool extendSelection(FXTreeItem* item,FXbool notify=FALSE);

  // Overrides the base class version of killSelection()
  virtual FXbool killSelection(FXbool notify=FALSE);

  // Overrides the base class version of openItem()
  virtual FXbool openItem(FXTreeItem* item,FXbool notify=FALSE);

  // Overrides the base class version of closeItem()
  virtual FXbool closeItem(FXTreeItem* item,FXbool notify=FALSE);

  // Overrides the base class version of collapseTree()
  virtual FXbool collapseTree(FXTreeItem* tree,FXbool notify=FALSE);

  // Overrides the base class version of expandTree()
  virtual FXbool expandTree(FXTreeItem* tree,FXbool notify=FALSE);

  // Overrides the base class version of setCurrentItem()
  virtual void setCurrentItem(FXTreeItem* item,FXbool notify=FALSE);

  // Overrides the base class version of getItemAt()
  virtual FXTreeItem* getItemAt(FXint x,FXint y) const;

  // Overrides the base class version of makeItemVisible()
  virtual void makeItemVisible(FXTreeItem* item);

  // Overrides the base class version of enableItem()
  virtual FXbool enableItem(FXTreeItem* item);

  // Overrides the base class version of disableItem()
  virtual FXbool disableItem(FXTreeItem* item);
