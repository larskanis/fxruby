public:
  /// Overrides the base class version of close()
  virtual bool close();

  /// Overrides the base class version of flush()
  virtual bool flush();

  // Overrides the base class version of position()
  virtual bool position(FXlong p,FXWhence whence=FXFromStart);
