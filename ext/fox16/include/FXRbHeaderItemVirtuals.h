public:
  // Overrides the base class version of setText()
  virtual void setText(const FXString& text);

  // Overrides the base class version of setIcon()
  virtual void setIcon(FXIcon* icn);

  // Overrides the base class version of getWidth()
  virtual FXint getWidth(const FXHeader* header) const;

  // Overrides the base class version of getHeight()
  virtual FXint getHeight(const FXHeader* header) const;

  // Overrides the base class version of create()
  virtual void create();

  // Overrides the base class version of detach()
  virtual void detach();

  // Overrides the base class version of destroy()
  virtual void destroy();

