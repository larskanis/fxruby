public:
  // Overrides the base class version of show() with placement
  virtual void show(FXuint placement);

  // Overrides the base class version of maximize()
  virtual FXbool maximize(FXbool notify=false);

  // Overrides the base class version of minimize()
  virtual FXbool minimize(FXbool notify=false);

  // Overrides the base class version of restore()
  virtual FXbool restore(FXbool notify=false);

  // Overrides the base class version of close()
  virtual FXbool close(FXbool notify=false);

  // Overrides the base class version of flash()
  virtual void flash(FXbool yes);

  // Overrides the base class version of fullScreen()
  virtual FXbool fullScreen(FXbool notify=false);
  
  // Overrides the base class version of stackingOrder()
  virtual FXbool stackingOrder(FXuint order);
