public:
  // Overrides the base class version of bounds()
  virtual void bounds(FXRangef& box);

  // Overrides the base class version of draw()
  virtual void draw(FXGLViewer* viewer);

  // Overrides the base class version of hit()
  virtual void hit(FXGLViewer* viewer);

  // Overrides the base class version of copy()
  virtual FXGLObject* copy();

  // Overrides the base class version of canDrag()
  virtual FXbool canDrag() const;

  // Overrides the base class version of canDelete()
  virtual FXbool canDelete() const;

  // Overrides the base class version of drag()
  virtual FXbool drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty);

