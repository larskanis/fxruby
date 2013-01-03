public:
  // Overrides the base class version of create()
  virtual void create();

  // Overrides the base class version of detach()
  virtual void detach();

  // Overrides the base class version of destroy()
  virtual void destroy();

  // Overrides the base class version of init()
  virtual void init(int& argc, char** argv,bool connect=true);

  // Overrides the base class version of exit()
  virtual void exit(FXint code=0);
