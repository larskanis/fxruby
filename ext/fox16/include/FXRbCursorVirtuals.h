public:
  // Overrides the base class version of savePixels()
  virtual bool savePixels(FXStream& store) const;

  // Overrides the base class version of loadPixels()
  virtual bool loadPixels(FXStream& store);
