public:
  /// Overrides the base class version of close()
  virtual FXbool close();

  /// Overrides the base class version of flush()
  virtual FXbool flush();

  // Overrides the base class version of position()
  virtual FXbool position(FXlong p,FXWhence whence=FXFromStart);
