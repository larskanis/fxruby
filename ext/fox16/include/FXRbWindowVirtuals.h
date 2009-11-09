public:
  // Overrides base class version of layout()
  virtual void layout();

  // Overrides base class version of getDefaultWidth()
  virtual FXint getDefaultWidth();

  // Overrides base class version of getDefaultHeight()
  virtual FXint getDefaultHeight();

  // Overrides base class version of getWidthForHeight()
  virtual FXint getWidthForHeight(FXint givenheight);

  // Overrides base class version of getHeightForWidth()
  virtual FXint getHeightForWidth(FXint givenwidth);

  // Overrides the base class version of canFocus()
  virtual bool canFocus() const;

  // Overrides the base class version of setFocus()
  virtual void setFocus();

  // Overrides the base class version of killFocus()
  virtual void killFocus();

  // Overrides the base class version of changeFocus()
  virtual void changeFocus(FXWindow *child);

  // Overrides the base class version of setDefault()
  virtual void setDefault(FXbool enable);

  // Overrides the base class version of enable()
  virtual void enable();

  // Overrides the base class version of disable()
  virtual void disable();

  // Overrides the base class version of raise()
  virtual void raise();

  // Overrides the base class version of lower()
  virtual void lower();

  // Overrides the base class version of move()
  virtual void move(FXint x,FXint y);

  // Overrides the base class version of position()
  virtual void position(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of recalc()
  virtual void recalc();

  // Overrides the base class version of reparent()
  virtual void reparent(FXWindow* father,FXWindow* other=NULL);

  // Overrides the base class version of show()
  virtual void show();

  // Overrides the base class version of hide()
  virtual void hide();

  // Overrides the base class version of isComposite()
  virtual bool isComposite() const;

  // Overrides the base class version of contains()
  virtual bool contains(FXint parentx,FXint parenty) const;

  // Overrides the base class version of doesSaveUnder()
  virtual bool doesSaveUnder() const;

  // Overrides the base class version of setBackColor()
  virtual void setBackColor(FXColor clr);

  // Overrides the base class version of tr()
  virtual const FXchar* tr(const FXchar* message,const FXchar* hint=NULL) const;

  /// Overrides the base class version of dropEnable()
  virtual void dropEnable();

  /// Overrides the base class version of dropDisable()
  virtual void dropDisable();

  /// Overrides the base class version of setShape()
  virtual void setShape(const FXRegion& region);

  /// Overrides the base class version of setShape()
  virtual void setShape(FXBitmap* bitmap);

  /// Overrides the base class version of setShape()
  virtual void setShape(FXIcon* icon);

  /// Overrides the base class version of clearShape()
  virtual void clearShape();

