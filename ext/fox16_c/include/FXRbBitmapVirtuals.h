public:
  // Overrides the base class version of restore()
  virtual void restore();

  // Overrides the base class version of render()
  virtual void render();

  // Overrides the base class version of release()
  virtual void release();

  // Overrides the base class version of savePixels()
  virtual bool savePixels(FXStream& store) const;

  // Overrides the base class version of loadPixels()
  virtual bool loadPixels(FXStream& store);

  /// Rescale pixels to the specified width and height
  virtual void scale(FXint w,FXint h);

  /// Mirror bitmap horizontally and/or vertically
  virtual void mirror(FXbool horizontal,FXbool vertical);

  /// Rotate bitmap by degrees ccw
  virtual void rotate(FXint degrees);

  /// Crop bitmap to given rectangle
  virtual void crop(FXint x,FXint y,FXint w,FXint h,FXbool color=0);

  /// Fill bitmap with uniform value
  virtual void fill(FXbool color);

  // Overrides the base class version of setData()
  virtual void setData(FXuchar *pix,FXuint opts=0);

  // Overrides the base class version of setData()
  virtual void setData(FXuchar *pix,FXuint opts,FXint w,FXint h);

