public:
  /// Overrides the base class version of enableItem()
  virtual FXbool enableItem(FXint index);

  /// Overrides the base class version of disableItem()
  virtual FXbool disableItem(FXint index);

  /// Overrides the base class version of makeItemVisible()
  virtual void makeItemVisible(FXint index);

  /// Overrides the base class version of getItemAt()
  virtual FXint getItemAt(FXint x,FXint y) const;

  /// Overrides the base class version of selectItem()
  virtual FXbool selectItem(FXint index,FXbool notify=FALSE);

  /// Overrides the base class version of deselectItem()
  virtual FXbool deselectItem(FXint index,FXbool notify=FALSE);

  /// Overrides the base class version of toggleItem()
  virtual FXbool toggleItem(FXint index,FXbool notify=FALSE);

  /// Overrides the base class version of extendSelection()
  virtual FXbool extendSelection(FXint index,FXbool notify=FALSE);

  /// Overrides the base class version of killSelection()
  virtual FXbool killSelection(FXbool notify=FALSE);

  /// Overrides the base class version of setCurrentItem()
  virtual void setCurrentItem(FXint index,FXbool notify=FALSE);
