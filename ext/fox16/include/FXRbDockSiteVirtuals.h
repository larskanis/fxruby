public:
  // Overrides the base class version of resizeToolBar()
  virtual void resizeToolBar(FXDockBar* bar,FXint barx,FXint bary,FXint barw,FXint barh);

  // Overrides the base class version of moveToolBar()
  virtual void moveToolBar(FXDockBar* bar,FXint barx,FXint bary);

  // Overrides the base class version of dockToolBar()
  virtual void dockToolBar(FXDockBar* bar,FXWindow* other);

  // Overrides the base class version of dockToolBar()
  virtual void dockToolBar(FXDockBar* bar,FXint barx,FXint bary);

  // Overrides the base class version of undockToolBar()
  virtual void undockToolBar(FXDockBar* bar);

