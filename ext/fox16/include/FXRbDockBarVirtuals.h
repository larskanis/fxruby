public:
  // Overrides the base class version of dock()
  virtual void dock(FXDockSite* docksite,FXWindow* before=NULL,FXbool notify=FALSE);

  // Overrides the base class version of dock()
  virtual void dock(FXDockSite* docksite,FXint localx,FXint localy,FXbool notify);

  // Overrides the base class version of undock()
  virtual void undock(FXint rootx,FXint rooty,FXbool notify=FALSE);

