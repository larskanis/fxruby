public:
  // Overrides the base class version of readPixel()
  virtual FXColor readPixel(FXint x,FXint y);

  // Overrides the base class version of drawPoint()
  virtual void drawPoint(FXint x,FXint y);

  // Overrides the base class version of drawPoints()
  virtual void drawPoints(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of drawPointsRel()
  virtual void drawPointsRel(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of drawLine()
  virtual void drawLine(FXint x1,FXint y1,FXint x2,FXint y2);

  // Overrides the base class version of drawLines()
  virtual void drawLines(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of drawLinesRel()
  virtual void drawLinesRel(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of drawLineSegments()
  virtual void drawLineSegments(const FXSegment* segments,FXuint nsegments);

  // Overrides the base class version of drawRectangle()
  virtual void drawRectangle(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of drawRectangles()
  virtual void drawRectangles(const FXRectangle* rectangles,FXuint nrectangles);

  /// Overrides the base class version of drawRoundRectangle()
  virtual void drawRoundRectangle(FXint x,FXint y,FXint w,FXint h,FXint ew,FXint eh);

  // Overrides the base class version of drawArc()
  virtual void drawArc(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);

  // Overrides the base class version of drawArcs()
  virtual void drawArcs(const FXArc* arcs,FXuint narcs);

  /// Overrides the base class version of drawEllipse()
  virtual void drawEllipse(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of fillRectangle()
  virtual void fillRectangle(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of fillRectangles()
  virtual void fillRectangles(const FXRectangle* rectangles,FXuint nrectangles);

  /// Overrides the base class version of fillRoundRectangle()
  virtual void fillRoundRectangle(FXint x,FXint y,FXint w,FXint h,FXint ew,FXint eh);

  // Overrides the base class version of fillChord()
  virtual void fillChord(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);

  // Overrides the base class version of fillChords()
  virtual void fillChords(const FXArc* chords,FXuint nchords);

  // Overrides the base class version of fillArc()
  virtual void fillArc(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2);

  // Overrides the base class version of fillArcs()
  virtual void fillArcs(const FXArc* arcs,FXuint narcs);

  /// Overrides the base class version of fillEllipse()
  virtual void fillEllipse(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of fillPolygon()
  virtual void fillPolygon(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of fillConcavePolygon()
  virtual void fillConcavePolygon(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of fillComplexPolygon()
  virtual void fillComplexPolygon(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of fillPolygonRel()
  virtual void fillPolygonRel(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of fillConcavePolygonRel()
  virtual void fillConcavePolygonRel(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of fillComplexPolygonRel()
  virtual void fillComplexPolygonRel(const FXPoint* points,FXuint npoints);

  // Overrides the base class version of drawHashBox()
  virtual void drawHashBox(FXint x,FXint y,FXint w,FXint h,FXint b=1);

  // Overrides the base class version of drawFocusRectangle()
  virtual void drawFocusRectangle(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of drawArea()
  virtual void drawArea(const FXDrawable* source,FXint sx,FXint sy,FXint sw,FXint sh,FXint dx,FXint dy);

  // Overrides the base class version of drawArea()
  virtual void drawArea(const FXDrawable* source,FXint sx,FXint sy,FXint sw,FXint sh,FXint dx,FXint dy,FXint dw,FXint dh);

  // Overrides the base class version of drawImage()
  virtual void drawImage(const FXImage* image,FXint dx,FXint dy);

  // Overrides the base class version of drawBitmap()
  virtual void drawBitmap(const FXBitmap* bitmap,FXint dx,FXint dy);

  // Overrides the base class version of drawIcon()
  virtual void drawIcon(const FXIcon* icon,FXint dx,FXint dy);

  // Overrides the base class version of drawIconShaded()
  virtual void drawIconShaded(const FXIcon* icon,FXint dx,FXint dy);

  // Overrides the base class version of drawIconSunken()
  virtual void drawIconSunken(const FXIcon* icon,FXint dx,FXint dy);

  // Overrides the base class version of drawText()
  virtual void drawText(FXint x,FXint y,const FXString& string);

  // Overrides the base class version of drawText()
  virtual void drawText(FXint x,FXint y,const FXchar* string,FXuint length);

  // Overrides the base class version of drawImageText()
  virtual void drawImageText(FXint x,FXint y,const FXString& string);

  // Overrides the base class version of drawImageText()
  virtual void drawImageText(FXint x,FXint y,const FXchar* string,FXuint length);

  // Overrides the base class version of setForeground()
  virtual void setForeground(FXColor clr);

  // Overrides the base class version of setBackground()
  virtual void setBackground(FXColor clr);

  // Overrides the base class version of setDashes()
  virtual void setDashes(FXuint dashoffset,const FXchar *dashpattern,FXuint dashlength);

  // Overrides the base class version of setLineWidth()
  virtual void setLineWidth(FXuint linewidth=0);

  // Overrides the base class version of setLineCap()
  virtual void setLineCap(FXCapStyle capstyle=CAP_BUTT);

  // Overrides the base class version of setLineJoin()
  virtual void setLineJoin(FXJoinStyle joinstyle=JOIN_MITER);

  // Overrides the base class version of setLineStyle()
  virtual void setLineStyle(FXLineStyle linestyle=LINE_SOLID);

  // Overrides the base class version of setFillStyle()
  virtual void setFillStyle(FXFillStyle fillstyle=FILL_SOLID);

  // Overrides the base class version of setFillRule()
  virtual void setFillRule(FXFillRule fillrule=RULE_EVEN_ODD);

  // Overrides the base class version of setFunction()
  virtual void setFunction(FXFunction func=BLT_SRC);

  // Overrides the base class version of setTile()
  virtual void setTile(FXImage* image,FXint dx=0,FXint dy=0);

  // Overrides the base class version of setStipple()
  virtual void setStipple(FXBitmap *bitmap,FXint dx=0,FXint dy=0);

  // Overrides the base class version of setStipple()
  virtual void setStipple(FXStipplePattern pat,FXint dx=0,FXint dy=0);

  // Overrides the base class version of setClipRegion()
  virtual void setClipRegion(const FXRegion& region);

  // Overrides the base class version of setClipRectangle()
  virtual void setClipRectangle(FXint x,FXint y,FXint w,FXint h);

  // Overrides the base class version of setClipRectangle()
  virtual void setClipRectangle(const FXRectangle& rectangle);

  // Overrides the base class version of clearClipRectangle()
  virtual void clearClipRectangle();

  // Overrides the base class version of setClipMask()
  virtual void setClipMask(FXBitmap* bitmap,FXint dx=0,FXint dy=0);

  // Overrides the base class version of clearClipMask()
  virtual void clearClipMask();

  // Overrides the base class version of setFont()
  virtual void setFont(FXFont *fnt);

  // Overrides the base class version of clipChildren()
  virtual void clipChildren(FXbool yes);

