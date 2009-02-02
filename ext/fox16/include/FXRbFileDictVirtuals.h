public:
  // Overrides the base class version of findFileBinding()
  virtual FXFileAssoc* findFileBinding(const FXchar* pathname);

  // Overrides the base class version of findDirBinding()
  virtual FXFileAssoc* findDirBinding(const FXchar* pathname);

  // Overrides the base class version of findExecBinding()
  virtual FXFileAssoc* findExecBinding(const FXchar* pathname);
