public:
  // Overrides the base class version of setActiveChild()
  virtual FXbool setActiveChild(FXMDIChild* child=NULL,FXbool notify=FALSE);

  // Overrides the base class version of cascade()
  virtual void cascade(FXbool notify=FALSE);

  // Overrides the base class version of horizontal()
  virtual void horizontal(FXbool notify=FALSE);

  // Overrides the base class version of vertical()
  virtual void vertical(FXbool notify=FALSE);
