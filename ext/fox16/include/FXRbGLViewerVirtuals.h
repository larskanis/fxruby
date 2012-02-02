public:
  // Overrides the base class version of select()
  virtual FXGLObject** select(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of pick()
  virtual FXGLObject* pick(FXint x,FXint y);

  // Overrides the base class version of setBounds()
  virtual FXbool setBounds(const FXRangef& box);

