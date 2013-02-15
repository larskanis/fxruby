public:
  // Overrides the base class version of restore
  virtual void restore();

  // Overrides the base class version of render()
  virtual void render();

  // Overrides the base class version of release()
  virtual void release();

  // Overrides the base class version of scale()
  virtual void scale(FXint w,FXint h,FXint quality);

  // Overrides the base class version of mirror()
  virtual void mirror(bool horizontal,bool vertical);

  // Overrides the base class version of rotate()
  virtual void rotate(FXint degrees);

  // Overrides the base class version of crop()
  virtual void crop(FXint x,FXint y,FXint w,FXint h,FXColor color=0);

  // Overrides the base class version of fill()
  virtual void fill(FXColor color);

  // Overrides the base class version of fade()
  virtual void fade(FXColor color,FXint factor=255);

  // Overrides the base class version of xshear()
  virtual void xshear(FXint shear,FXColor clr=0);

  // Overrides the base class version of yshear()
  virtual void yshear(FXint shear,FXColor clr=0);

  // Overrides the base class version of hgradient()
  virtual void hgradient(FXColor left,FXColor right);

  // Overrides the base class version of vgradient()
  virtual void vgradient(FXColor top,FXColor bottom);

  // Overrides the base class version of gradient()
  virtual void gradient(FXColor topleft,FXColor topright,FXColor bottomleft,FXColor bottomright);

  // Overrides the base class version of blend()
  virtual void blend(FXColor color);

  // Overrides the base class version of savePixels()
  virtual bool savePixels(FXStream& store) const;

  // Overrides the base class version of loadPixels()
  virtual bool loadPixels(FXStream& store);
