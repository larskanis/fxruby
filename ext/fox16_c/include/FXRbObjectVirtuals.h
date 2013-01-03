public:
  // Overrides the base class version of onDefault()
  // virtual long onDefault(FXObject* sender,FXSelector sel,void* ptr);

  // Overrides the base class version of save()
  virtual void save(FXStream& store) const;

  // Overrides the base class version of load()
  virtual void load(FXStream& store);
