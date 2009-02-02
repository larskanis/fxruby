public:
  // Overrides the base class version of makeCurrent()
  virtual FXbool makeCurrent();

  // Overrides the base class version of makeNonCurrent()
  virtual FXbool makeNonCurrent();

  // Overrides the base class version of isCurrent()
  virtual FXbool isCurrent() const;

  // Overrides the base class version of swapBuffers()
  virtual void swapBuffers();

