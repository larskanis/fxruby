protected:
  // Overrides the base class version of draw()
  virtual void draw(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Overrides the base class version of drawBorders()
  virtual void drawBorders(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Overrides the base class version of drawContent()
  virtual void drawContent(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Overrides the base class version of drawPattern()
  virtual void drawPattern(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Overrides the base class version of drawBackground()
  virtual void drawBackground(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

public:
  // Publically accessible version of draw()
  void public_draw(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Publically accessible version of drawBorders()
  void public_drawBorders(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Publically accessible version of drawContent()
  void public_drawContent(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Publically accessible version of drawPattern()
  void public_drawPattern(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Publically accessible version of drawBackground()
  void public_drawBackground(const FXTable* table,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

public:
  // Overrides the base class version of setText()
  virtual void setText(const FXString& txt);

  // Overrides the base class of getText()
  virtual FXString getText() const;

  // Overrides the base class version of setIcon()
  virtual void setIcon(FXIcon* icn,FXbool owned=FALSE);

  // Overrides the base class version of getIcon()
  virtual FXIcon* getIcon() const;

  // Overrides the base class version of setFocus()
  virtual void setFocus(FXbool focus);

  // Overrides the base class version of setSelected()
  virtual void setSelected(FXbool selected);

  // Overrides the base class version of setEnabled()
  virtual void setEnabled(FXbool enabled);

  // Overrides the base class version of setDraggable()
  virtual void setDraggable(FXbool draggable);

  // Overrides the base class version of setJustify()
  virtual void setJustify(FXuint justify=RIGHT|CENTER_Y);

  // Overrides the base class version of setIconPosition()
  virtual void setIconPosition(FXuint mode);

  // Overrides the base class version of setBorders()
  virtual void setBorders(FXuint borders=0);

  // Overrides the base class version of setStipple()
  virtual void setStipple(FXStipplePattern pattern);

  /// Overrides the base class version of getControlFor()
  virtual FXWindow *getControlFor(FXTable* table);

  /// Overrides the base class version of setFromControl()
  virtual void setFromControl(FXWindow *control);

  // Overrides the base class version of getWidth()
  virtual FXint getWidth(const FXTable* table) const;

  // Overrides the base class version of getHeight()
  virtual FXint getHeight(const FXTable* table) const;

  // Overrides the base class version of create()
  virtual void create();

  // Overrides the base class version of detach()
  virtual void detach();

  // Overrides the base class version of destroy()
  virtual void destroy();
