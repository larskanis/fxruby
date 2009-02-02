protected:
  // Overrides the base class version of drawshape()
  virtual void drawshape(FXGLViewer* viewer);

public:
  // This is the publically accessible version
  void _drawshape(FXGLViewer* viewer);

  // Overrides the base class version of setPosition()
  void setPosition(const FXVec3f& pos);

