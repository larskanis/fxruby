public:
  // Overrides the base class version of create()
  virtual void create();

  // Overrides the base class version of detach()
  virtual void detach();

  // Overrides the base class version of destroy()
  virtual void destroy();

  // Overrides the base class version of setText()
  virtual void setText(const FXString& txt);

  // Overrides the base class version of setIcon()
  virtual void setIcon(FXIcon* icn,FXbool owned=FALSE);

  // Overrides the base class version of setFocus()
  virtual void setFocus(FXbool focus);

  // Overrides the base class version of setSelected()
  virtual void setSelected(FXbool selected);

  // Overrides the base class version of setEnabled()
  virtual void setEnabled(FXbool enabled);

  // Overrides the base class version of setDraggable()
  virtual void setDraggable(FXbool draggable);

  // Overrides the base class version of getWidth()
  virtual FXint getWidth(const FXList* list) const;

  // Overrides the base class version of getHeight()
  virtual FXint getHeight(const FXList* list) const;
