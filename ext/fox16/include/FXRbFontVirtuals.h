public:
  // Overrides the base class version of setFontDesc()
  virtual void setFontDesc(const FXFontDesc& fontdesc);

  // Overrides the base class version of setAngle()
  virtual void setAngle(FXint ang);

  // Overrides the base class version of setFont()
  virtual void setFont(const FXString& string);

  // Overrides the base class version of isFontMono()
  virtual FXbool isFontMono() const;

  // Overrides the base class version of hasChar()
  virtual FXbool hasChar(FXwchar ch) const;

  // Overrides the base class version of getMinChar()
  virtual FXwchar getMinChar() const;

  // Overrides the base class version of getMaxChar()
  virtual FXwchar getMaxChar() const;

  // Overrides the base class version of leftBearing()
  virtual FXint leftBearing(FXwchar ch) const;

  // Overrides the base class version of rightBearing()
  virtual FXint rightBearing(FXwchar ch) const;

  // Overrides the base class version of getFontWidth()
  virtual FXint getFontWidth() const;

  // Overrides the base class version of getFontHeight()
  virtual FXint getFontHeight() const;

  // Overrides the base class version of getFontAscent()
  virtual FXint getFontAscent() const;

  // Overrides the base class version of getFontDescent()
  virtual FXint getFontDescent() const;

  // Overrides the base class version of getFontLeading()
  virtual FXint getFontLeading() const;

  // Overrides the base class version of getFontSpacing()
  virtual FXint getFontSpacing() const;

  // Overrides the base class version of getCharWidth()
  virtual FXint getCharWidth(const FXwchar ch) const;

  // Overrides the base class version of getTextWidth()
  virtual FXint getTextWidth(const FXString& string) const;

  // Overrides the base class version of getTextHeight()
  virtual FXint getTextHeight(const FXString& string) const;

