protected:
  // Overrides the base class version of draw()
  virtual void draw(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Overrides the base class version of hitItem()
  virtual FXint hitItem(const FXIconList* list,FXint rx,FXint ry,FXint rw=1,FXint rh=1) const;

  // Overrides the base class version of drawBigIcon()
  virtual void drawBigIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Overrides the base class version of drawMiniIcon()
  virtual void drawMiniIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Overrides the base class version of drawDetails()
  virtual void drawDetails(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

public:
  // Publically accessible version of draw()
  void public_draw(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Publically accessible version of hitItem()
  FXint public_hitItem(const FXIconList* list,FXint rx,FXint ry,FXint rw=1,FXint rh=1) const;

  // Publically accessible version of drawBigIcon()
  void public_drawBigIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Publically accessible version of drawMiniIcon()
  void public_drawMiniIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

  // Publically accessible version of drawDetails()
   void public_drawDetails(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const;

public:
  // Overrides the base class version of setText()
  virtual void setText(const FXString& txt);

  // Overrides the base class version of setBigIcon()
  virtual void setBigIcon(FXIcon* icn,FXbool owned=FALSE);

  // Overrides the base class version of setMiniIcon()
  virtual void setMiniIcon(FXIcon* icn,FXbool owned=FALSE);

  // Overrides the base class version of setFocus()
  virtual void setFocus(FXbool focus);

  // Overrides the base class version of setSelected()
  virtual void setSelected(FXbool selected);

  // Overrides the base class version of setEnabled()
  virtual void setEnabled(FXbool enabled);

  // Overrides the base class version of setDraggable()
  virtual void setDraggable(FXbool draggable);

  // Overrides the base class version of getWidth()
  virtual FXint getWidth(const FXIconList* list) const;

  // Overrides the base class version of getHeight()
  virtual FXint getHeight(const FXIconList* list) const;

  // Overrides the base class version of create()
  virtual void create();

  // Overrides the base class version of detach()
  virtual void detach();

  // Overrides the base class version of destroy()
  virtual void destroy();
