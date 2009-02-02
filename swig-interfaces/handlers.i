#ifdef IGNORE_MESSAGE_HANDLERS

%ignore onCmdFov(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdAlphaText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onQueryTip(FXObject*,FXSelector,void*);
%ignore onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdClicked(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdCursorWordLeft(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCancel(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdCollateReversed(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdTop(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdBack(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelectionGained(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdBackMaterial(FXObject*,FXSelector,void*);
%ignore onUpdBackColor(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdAmbientColor(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onCmdShiftText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdBottom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdShadeSmooth(FXObject*,FXSelector,void*);
%ignore onUpdFront(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdToggleShown(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelected(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onChgColorWell(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onMotion(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onListClicked(FXObject*,FXSelector,void* PTR_INT);
%ignore onClipboardGained(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdPost(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdMoveTop(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdOpen(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdCMYText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdCollateNormal(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdHeader(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onBeginDragGrip(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
%ignore onCollapsed(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCmdPost(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdList(FXObject*,FXSelector,void* PTR_INT);
%ignore onCmdNew(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdMaximize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetValue(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onCmdSelectAll(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
%ignore onCmdDeleteWord(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorColumn(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdVertGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onFocusIn(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onTripleClicked(FXObject*,FXSelector,void* PTR_GLOBJECT);
%ignore onUpdCloseDocument(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onClosed(FXObject*,FXSelector,void* PTR_DIRITEM);
%ignore onUncheckOther(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSearchSel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdIncrement(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdDockBottom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSelectColumn(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetValue(FXObject*,FXSelector,void* PTR_UINT);
%ignore onUpdShowHidden(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCMYText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelectionRequest(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdUncollapse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdScrollUp(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdTurbo(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdStyleText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelected(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdPrintVector(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdRight(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdShadeSmooth(FXObject*,FXSelector,void*);
%ignore onCmdLassoSelect(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdToggleOverstrike(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDNDLeave(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onTipTimer(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLightSpecular(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onCmdFitView(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onHeaderChanged(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusDown(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdFmTree(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTimeDecPage(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onClicked(FXObject*,FXSelector,void* PTR_GLOBJECT);
%ignore onCmdCopySel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onButtonPress(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onDNDRequest(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdLastPage(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdDockRight(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onMiddleBtnPress(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onUpdTitle(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onButtonPress(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onClicked(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCutSel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdChangeCase(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSearch(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTimeIncLine(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdDir(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorTop(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdMenuRestore(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDrawingStyle(FXObject*,FXSelector,void*);
%ignore onCmdColorWell(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onUpdXYZScale(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLightAmbient(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onUpdRGBText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdHome(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDirTree(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onCmdUpdate(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onDelete(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSortBySize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdate(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdMoveLeft(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdWeight(FXObject*,FXSelector,void* PTR_INT);
%ignore onPaint(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdYes(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdInsertNewline(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onOpenTimer(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdUndock(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdCursorColumn(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusUp(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorHome(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onOpenItem(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTripleClicked(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusNext(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdRGBSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorEnd(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdColor(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onButtonRelease(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdExpand(FXObject*,FXSelector,void*);
%ignore onTimeDecPix(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdRGBText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLandscape(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusPrev(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdScrollDown(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorRight(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFlash(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdDeleteColumn(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onTipShow(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCollapse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUncheck(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdRight(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSize(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdCMYSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onOpened(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCommand(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onMaximize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onLassoed(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdTileVertical(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTimeWheel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdNext(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdArrangeByRows(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdToPrinter(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetStringValue(FXObject*,FXSelector,void* PTR_STRING);
%ignore onCmdPortrait(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdEnable(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdPasteSel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdShowBigIcons(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSetWidth(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCommand(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCmdCursorRow(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdUndock(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMovePageDown(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdRollPitchYaw(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSelected(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onVScrollerChanged(FXObject*,FXSelector,void* PTR_INT);
%ignore onListChanged(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdSortByName(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onFwdToText(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onCmdWork(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdCursorScreenCenter(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onMotion(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onUpdMode(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdMenuMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdHideFiles(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdScalable(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdCursorPageUp(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLighting(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdTileVertical(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onClosed(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCmdMode(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSortReverse(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onCmdGetStringValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onLeave(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdRestore(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdPrintImage(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdWindowSelect(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorParHome(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdUnpost(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDoubleClicked(FXObject*,FXSelector,void* PTR_GLOBJECT);
%ignore onClicked(FXObject*,FXSelector,void* PTR_INT);
%ignore onTimeout(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdChoice(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onOpened(FXObject*,FXSelector,void* PTR_DIRITEM);
%ignore onCmdDeiconify(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdIconify(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdAccel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdArrangeByRows(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdSelectInverse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdRollPitchYaw(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdNumCopies(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDeselected(FXObject*,FXSelector,void* PTR_MDICHILD);
%ignore onUpdDeleteSel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdLightSpecular(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdGetStringValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onClipboardRequest(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onUpdShowBigIcons(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdRestore(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdShowDetails(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdParallel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onEndDragGrip(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onLeftBtnPress(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onReplaceKey(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onHotKeyRelease(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdActivatePrev(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdFileName(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onChanged(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onPick(FXObject*,FXSelector,void* PTR_GLOBJECT); // FIXME
%ignore onCmdLower(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTreeChanged(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCmdEntry(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdClear(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLassoZoom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdAlphaLabel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCollapsed(FXObject*,FXSelector,void* PTR_DIRITEM);
%ignore onCmdSortByTime(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onConfigure(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onBeginDrag(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onUpdSetDirectory(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdZoom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdWindowSelect(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onBeginDrag(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdPerspective(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorScreenBottom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelectionRequest(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdSortByType(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdDump(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdShow(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusOut(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onConfigure(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdItemSelected(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdActivateNext(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdSetPattern(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdButton(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onHScrollerDragged(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdCurrent(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTextChanged(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onCmdSetValue(FXObject*,FXSelector,void* PTR_BOOL);
%ignore onCmdPerspective(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdDockTop(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdInsertTab(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onRightBtnPress(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onCmdReplaceHist(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdHSVSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onPaint(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onClipboardLost(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onVerify(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onCmdDeleteEol(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdXYZDial(FXObject*,FXSelector,void* PTR_INT);
%ignore onCmdBackColor(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onCmdItemDeselected(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCustomWell(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onCmdMoveDown(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdOpenItem(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTimeInc(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSearchHist(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdActivatePrev(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdArrangeByColumns(FXObject*,FXSelector,void* PTR_NULL);
%ignore onMap(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onChgWell(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onPaint(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onCmdAllFonts(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdLock(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdTileHorizontal(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onExpanded(FXObject*,FXSelector,void* PTR_DIRITEM);
%ignore onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdSetDirectory(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onCmdColor(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdAllFonts(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDockTop(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorDown(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdPitch(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdMenuWindow(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMark(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onTimeDecLine(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLock(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdBookmark(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdOpened(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onBlink(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onRefreshTimer(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onRestore(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMaximize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDeleteColumn(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdHeader(FXObject*,FXSelector,void* PTR_UINT);
%ignore onUnknown(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdCursorUp(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDeleteRow(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdDecrement(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdFog(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMoveEnd(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdBackspaceBol(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorPageDown(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdInsertRow(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdAnyFiles(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdBar(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onEndDrag(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdSelectChar(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdDeleteRow(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onTimeoutTicking(FXObject*, FXSelector, void* PTR_IGNORE);
%ignore onScintillaCommand(FXObject*, FXSelector, void* PTR_IGNORE);
%ignore onUpdShowFiles(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdBlockBeg(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onAutoScroll(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCascade(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMedia(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDeselected(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onClicked(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onDNDDrop(FXObject*,FXSelector,void*);
%ignore onCmdTop(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdDockLeft(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSortBySize(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdFov(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDoubleClicked(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdAlphaSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdFirstPage(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdExpand(FXObject*,FXSelector,void*);
%ignore onEndDrag(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onCmdSetRealValue(FXObject*,FXSelector,void* PTR_PDOUBLE);
%ignore onCmdSortByUser(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdShadeOff(FXObject*,FXSelector,void*);
%ignore onUpdZoom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdHideHidden(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdProps(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdIncrement(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDeselected(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdCollateNormal(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onHMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdTileHorizontal(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdSortReverse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onListUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdUnpost(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdDirectoryUp(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdXYZScale(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdWheel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdColor(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onVMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onKeyPress(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onDNDMotion(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onUpdDrawingStyle(FXObject*,FXSelector,void*);
%ignore onUpdXYZDial(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onChanged(FXObject*,FXSelector,void* PTR_GLOBJECT);
%ignore onUpdPitch(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDither(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCloseDocument(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdBackMaterial(FXObject*,FXSelector,void*);
%ignore onCmdSelectRow(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdHorzGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdNew(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCloseAll(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelectionLost(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onDNDEnter(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onChanged(FXObject*,FXSelector,void* PTR_OBJECT);
%ignore onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUncheckRadio(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdAlphaText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCommand(FXObject*,FXSelector,void* PTR_OBJECT);
%ignore onCmdHorzGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onTextButton(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdate(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdColorPick(FXObject*,FXSelector,void* PTR_POINT);
%ignore onCmdShowMiniIcons(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdLastPage(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onSelectionLost(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onChgCustomWell(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onCmdUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onChgEntry(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onClipboardLost(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onCmdFamily(FXObject*,FXSelector,void* PTR_INT);
%ignore onCmdToFile(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdLeft(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdShowMiniIcons(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdDecrement(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdOption(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCommand(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdOption(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onMessage(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onCmdArrangeByColumns(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDNDDrop(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onDoubleClicked(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdMedia(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdRaise(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTipHide(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDockRight(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdScalable(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLeft(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdFmText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdExtend(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdMoveRight(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdLandscape(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetWidth(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onClipboardRequest(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdSelectMatching(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdGotoLine(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTimeIncPix(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onHScrollerChanged(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdHSVText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdAlphaSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSelectBlock(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDragged(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onCmdDir(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdAnyWindows(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onChanged(FXObject*,FXSelector,void* PTR_MDICHILD);
%ignore onUpdProps(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorLeft(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSortByType(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSortReverse(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdGetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_OUT);
%ignore onUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdClose(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdAccept(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdQuit(FXObject*,FXSelector,void* PTR_NULL);
%ignore onUpdToggleOverstrike(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdDither(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdPages(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMovePageUp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdSetValue(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onCmdSortByGroup(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onChgColor(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdShadeOn(FXObject*,FXSelector,void*);
%ignore onAutoScroll(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdHSVText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMark(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorBottom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdPrinterName(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdGetRealValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onCmdValue(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelectionRequest(FXObject*,FXSelector,void* ptr);
%ignore onCmdInsertString(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onTripleClicked(FXObject*,FXSelector,void* PTR_INT);
%ignore onCmdSetIntValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onCmdSortByName(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onRepeat(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdToFile(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetRealRange(FXObject*,FXSelector,void* PTR_DBLRANGE_IN);
%ignore onDraggedGrip(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdSelectLine(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdPortrait(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSelected(FXObject*,FXSelector,void* PTR_MDICHILD);
%ignore onCmdSetPattern(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onUpdHideFiles(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdShadeOff(FXObject*,FXSelector,void*);
%ignore onCmdGetRealRange(FXObject*,FXSelector,void* PTR_DBLRANGE_OUT);
%ignore onRefresh(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTimeIncPage(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSizeText(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdRGBSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorScreenTop(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdBrowse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSortByUser(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUnknown(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdNumCopies(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdFilter(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCommand(FXObject*,FXSelector,void* PTR_INT);
%ignore onEnter(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onPopupMenu(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onTimeDec(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdLighting(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFieldButton(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdPrinterName(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdGetRealValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onClose(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdHideHidden(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdCollapse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdExtend(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdHSVSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUnmap(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdOverstString(FXObject*,FXSelector,void* PTR_CHAR);
%ignore onUpdFile(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdName(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdClose(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdToPrinter(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSortByGroup(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdToggleFiles(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMoveUp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdWindow(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdFrontMaterial(FXObject*,FXSelector,void*);
%ignore onInserted(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdCursorRow(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdInsertColumn(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onUpdPages(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdResetView(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdCascade(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdShadeOn(FXObject*,FXSelector,void*);
%ignore onCmdDockBottom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdGotoMatching(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdFile(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCheck(FXObject*,FXSelector,void* PTR_NULL);
%ignore onCmdToggleFiles(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdShowHidden(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdHide(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdUncollapse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdAll(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onLookupTimer(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdCMYSlider(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdDockLeft(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSelectWord(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorParEnd(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdCloseAllDocuments(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdValue(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdCharset(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onSearchKey(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdLink(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onChanged(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCmdCopy(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMove(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCloseAllDocuments(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdFrontMaterial(FXObject*,FXSelector,void*);
%ignore onCmdSelectCell(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdGray(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdBrowse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onExpanded(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCmdMoveHome(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onLeftBtnRelease(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onUpdCollateReversed(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdFront(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdToggleShown(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdHaveSelection(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onCmdUnpost(FXObject*,FXSelector,void* PTR_OPTION);
%ignore onCmdWell(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCharset(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDisable(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onFocusSelf(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdGray(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDragged(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUpdShowDetails(FXObject*,FXSelector,void* PTR_NULL);
%ignore onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdWheel(FXObject*,FXSelector,void* PTR_FLTARRAY);
%ignore onCmdGetStringValue(FXObject*,FXSelector,void* PTR_STRING);
%ignore onCmdVisit(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onChgColor(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onTreeClicked(FXObject*,FXSelector,void* PTR_TREEITEM);
%ignore onCmdBackspaceWord(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdGotoSelected(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdReplace(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdAmbientColor(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTextCommand(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onUpdFirstPage(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdMenuClose(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdLightDiffuse(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDestroy(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdMoveBottom(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdDelete(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdBottom(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdSortByTime(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onDeleted(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onCmdBlockEnd(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdVertGrid(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
%ignore onVScrollerDragged(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdParallel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdLightDiffuse(FXObject*,FXSelector,void* PTR_COLOR);
%ignore onCmdActivePane(FXObject*,FXSelector,void* PTR_INT);
%ignore onCmdBackspace(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdSetIntRange(FXObject*,FXSelector,void* PTR_INTRANGE_IN);
%ignore onCmdToggleHidden(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDeleteLine(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDNDRequest(FXObject*, FXSelector, void* PTR_EVENT);
%ignore onCmdShowFiles(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdFog(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdBar(FXObject*,FXSelector,void* PTR_FLTARRAY);
%ignore onUpdFileName(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCheck(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdCursorWordRight(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdToggleHidden(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDriveChanged(FXObject*,FXSelector,void* PTR_CSTRING);
%ignore onCmdCancel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDeleteSel(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdDeselectAll(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdOpen(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onUpdLightAmbient(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdActivateNext(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdTurbo(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onTripleClicked(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onCmdStyle(FXObject*,FXSelector,void* PTR_INT);
%ignore onCmdGetIntValue(FXObject*,FXSelector,void* PTR_NULL); // FIXME
%ignore onCmdItemDblClicked(FXObject*,FXSelector,void* PTR_INT);
%ignore onUpdBack(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onCmdToggleEditable(FXObject*,FXSelector,void* PTR_IGNORE);
%ignore onDoubleClicked(FXObject*,FXSelector,void* PTR_EVENT);
%ignore onUncheck(FXObject*,FXSelector,void* PTR_NULL);
%ignore onUpdFilename(FXObject*,FXSelector,void* PTR_IGNORE);

#endif /* IGNORE_MESSAGE_HANDLERS */

