public:
  // Overrides the base class version of loadIconFile()
  virtual FXIcon *loadIconFile(const FXString& filename,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadIconData()
  virtual FXIcon *loadIconData(const void *pixels,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadIconStream()
  virtual FXIcon *loadIconStream(FXStream& store,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadImageFile()
  virtual FXImage *loadImageFile(const FXString& filename,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadImageData()
  virtual FXImage *loadImageData(const void *pixels,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadImageStream()
  virtual FXImage *loadImageStream(FXStream& store,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadScaledIconFile()
  virtual FXIcon *loadScaledIconFile(const FXString& filename,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadScaledIconData()
  virtual FXIcon *loadScaledIconData(const void *pixels,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadScaledIconStream()
  virtual FXIcon *loadScaledIconStream(FXStream& store,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadScaledImageFile()
  virtual FXImage *loadScaledImageFile(const FXString& filename,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadScaledImageData()
  virtual FXImage *loadScaledImageData(const void *pixels,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  // Overrides the base class version of loadScaledImageStream()
  virtual FXImage *loadScaledImageStream(FXStream& store,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

