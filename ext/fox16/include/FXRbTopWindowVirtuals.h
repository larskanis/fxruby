public:
  // Overrides the base class version of show() with placement
  virtual void show(FXuint placement);

  // Overrides the base class version of maximize()
  virtual FXbool maximize(FXbool notify=FALSE);

  // Overrides the base class version of minimize()
  virtual FXbool minimize(FXbool notify=FALSE);

  // Overrides the base class version of restore()
  virtual FXbool restore(FXbool notify=FALSE);

  // Overrides the base class version of close()
  virtual FXbool close(FXbool notify=FALSE);
