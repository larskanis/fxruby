/********************************************************************************
*                                                                               *
*                        P r i n t   J o b   D i a l o g                        *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2002 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXPrintDialog.h 809 2002-07-11 17:28:15Z lyle $                     *
********************************************************************************/
#ifndef FXPRINTDIALOG_H
#define FXPRINTDIALOG_H

#ifndef FXDIALOGBOX_H
#include "FXDialogBox.h"
#endif

namespace FX {


class FXRadioButton;
class FXComboBox;
class FXListBox;
class FXTextField;
class FXSpinner;
class FXIcon;


/// Printer selection dialog
class FXAPI FXPrintDialog : public FXDialogBox {
  FXDECLARE(FXPrintDialog)
protected:
  FXRadioButton *sendtoprinter;
  FXComboBox    *printername;
  FXRadioButton *sendtofile;
  FXTextField   *filename;
  FXRadioButton *printall;
  FXRadioButton *printeven;
  FXRadioButton *printodd;
  FXRadioButton *printrange;
  FXRadioButton *firstpagefirst;
  FXRadioButton *lastpagefirst;
  FXRadioButton *printincolor;
  FXRadioButton *printinblacknwhite;
  FXRadioButton *orientportrait;
  FXRadioButton *orientlanscape;
  FXListBox     *media;
  FXSpinner     *firstpage;
  FXSpinner     *lastpage;
  FXSpinner     *numberofcopies;
  FXIcon        *landscapeIcon;
  FXIcon        *portraitIcon;
  FXPrinter      printer;
protected:
  FXPrintDialog(){}
private:
  FXPrintDialog(const FXPrintDialog&);
  FXPrintDialog &operator=(const FXPrintDialog&);
public:
  long onCmdToPrinter(FXObject*,FXSelector,void*);
  long onUpdToPrinter(FXObject*,FXSelector,void*);
  long onCmdToFile(FXObject*,FXSelector,void*);
  long onUpdToFile(FXObject*,FXSelector,void*);
  long onCmdBrowse(FXObject*,FXSelector,void*);
  long onUpdBrowse(FXObject*,FXSelector,void*);
  long onCmdProps(FXObject*,FXSelector,void*);
  long onUpdProps(FXObject*,FXSelector,void*);
  long onCmdPortrait(FXObject*,FXSelector,void*);
  long onUpdPortrait(FXObject*,FXSelector,void*);
  long onCmdLandscape(FXObject*,FXSelector,void*);
  long onUpdLandscape(FXObject*,FXSelector,void*);
  long onCmdPages(FXObject*,FXSelector,void*);
  long onUpdPages(FXObject*,FXSelector,void*);
  long onCmdColor(FXObject*,FXSelector,void*);
  long onUpdColor(FXObject*,FXSelector,void*);
  long onCmdGray(FXObject*,FXSelector,void*);
  long onUpdGray(FXObject*,FXSelector,void*);
  long onCmdNumCopies(FXObject*,FXSelector,void*);
  long onUpdNumCopies(FXObject*,FXSelector,void*);
  long onCmdFirstPage(FXObject*,FXSelector,void*);
  long onUpdFirstPage(FXObject*,FXSelector,void*);
  long onCmdLastPage(FXObject*,FXSelector,void*);
  long onUpdLastPage(FXObject*,FXSelector,void*);
  long onCmdCollateNormal(FXObject*,FXSelector,void*);
  long onUpdCollateNormal(FXObject*,FXSelector,void*);
  long onCmdCollateReversed(FXObject*,FXSelector,void*);
  long onUpdCollateReversed(FXObject*,FXSelector,void*);
  long onCmdFileName(FXObject*,FXSelector,void*);
  long onUpdFileName(FXObject*,FXSelector,void*);
  long onCmdPrinterName(FXObject*,FXSelector,void*);
  long onUpdPrinterName(FXObject*,FXSelector,void*);
  long onCmdAccept(FXObject*,FXSelector,void*);
  long onCmdMedia(FXObject*,FXSelector,void*);
  long onUpdMedia(FXObject*,FXSelector,void*);
public:
  enum{
    ID_TO_PRINTER=FXDialogBox::ID_LAST,
    ID_TO_FILE,
    ID_PRINTER_NAME,
    ID_FILE_NAME,
    ID_LANDSCAPE,
    ID_PORTRAIT,
    ID_MEDIA,
    ID_COLLATE_NORMAL,
    ID_COLLATE_REVERSED,
    ID_PAGES_ALL,
    ID_PAGES_EVEN,
    ID_PAGES_ODD,
    ID_PAGES_RANGE,
    ID_PAGES_FIRST,
    ID_PAGES_LAST,
    ID_BROWSE_FILE,
    ID_PROPERTIES,
    ID_COLOR_PRINTER,
    ID_GRAY_PRINTER,
    ID_NUM_COPIES
    };
public:

  /// Construct print dialog
  FXPrintDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Create dialog
  virtual void create();

  /// Set printer info
  void setPrinter(const FXPrinter& pr);

  /// Get printer info
  void getPrinter(FXPrinter& pr);

  /// Save dialog to a stream
  virtual void save(FXStream& store) const;

  /// Load dialog from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXPrintDialog();
  };

}

#endif
