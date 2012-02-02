public:
  // Overrides the base class version of setCursorPos()
  virtual void setCursorPos(FXint pos,FXbool notify=FALSE);

  // Overrides the base class version of extendSelection()
  virtual FXbool extendSelection(FXint pos,FXTextSelectionMode mode=SELECT_CHARS,FXbool notify=FALSE);

  // Overrides the base class version of killSelection()
  virtual FXbool killSelection(FXbool notify=FALSE);

  /// Overrides the base class versions of replaceText()
  virtual void replaceText(FXint pos,FXint m,const FXchar *text,FXint n,FXbool notify=FALSE);
  virtual void replaceText(FXint pos,FXint m,const FXString& text,FXbool notify=FALSE);

  /// Overrides the base class versions of replaceStyledText()
  virtual void replaceStyledText(FXint pos,FXint m,const FXchar *text,FXint n,FXint style=0,FXbool notify=FALSE);
  virtual void replaceStyledText(FXint pos,FXint m,const FXString& text,FXint style=0,FXbool notify=FALSE);

  /// Overrides the base class versions of appendText()
  virtual void appendText(const FXchar *text,FXint n,FXbool notify=FALSE);
  virtual void appendText(const FXString& text,FXbool notify=FALSE);

  /// Overrides the base class versions of appendStyledText()
  virtual void appendStyledText(const FXchar *text,FXint n,FXint style=0,FXbool notify=FALSE);
  virtual void appendStyledText(const FXString& text,FXint style=0,FXbool notify=FALSE);

  /// Overrides the base class versions of insertText()
  virtual void insertText(FXint pos,const FXchar *text,FXint n,FXbool notify=FALSE);
  virtual void insertText(FXint pos,const FXString& text,FXbool notify=FALSE);

  /// Overrides the base class versions of insertStyledText()
  virtual void insertStyledText(FXint pos,const FXchar *text,FXint n,FXint style=0,FXbool notify=FALSE);
  virtual void insertStyledText(FXint pos,const FXString& text,FXint style=0,FXbool notify=FALSE);

  /// Overrides the base class version of removeText()
  virtual void removeText(FXint pos,FXint n,FXbool notify=FALSE);

  /// Overrides the base class version of changeStyle()
  virtual void changeStyle(FXint pos,FXint n,FXint style);

  /// Overrides the base class versions of changeStyle()
  virtual void changeStyle(FXint pos,const FXchar* style,FXint n);
  virtual void changeStyle(FXint pos,const FXString& style);

  /// Overrides the base class versions of setText()
  virtual void setText(const FXchar* text,FXint n,FXbool notify=FALSE);
  virtual void setText(const FXString& text,FXbool notify=FALSE);

  /// Overrides the base class versions of setStyledText()
  virtual void setStyledText(const FXchar* text,FXint n,FXint style=0,FXbool notify=FALSE);
  virtual void setStyledText(const FXString& text,FXint style=0,FXbool notify=FALSE);

