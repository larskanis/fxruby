/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

class FXRadioButton;
class FXComboBox;
class FXListBox;
class FXTextField;
class FXSpinner;
class FXIcon;


/// Printer selection dialog
class FXPrintDialog : public FXDialogBox {
public:
  long onCmdToPrinter(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToPrinter(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdToFile(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdToFile(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBrowse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdBrowse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdProps(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdProps(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPortrait(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdPortrait(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLandscape(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdLandscape(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPages(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdPages(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdColor(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdColor(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdGray(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdGray(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdNumCopies(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdNumCopies(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFirstPage(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdFirstPage(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLastPage(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdLastPage(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCollateNormal(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCollateNormal(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCollateReversed(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCollateReversed(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFileName(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdFileName(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPrinterName(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdPrinterName(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdAccept(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMedia(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMedia(FXObject*,FXSelector,void* PTR_IGNORE);
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
  /// Constructor
  %extend {
    FXPrintDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbPrintDialog(owner,name,opts,x,y,w,h);
      }
    }

  // Set the printer description
  void setPrinter(const FXPrinter& pr);

  %extend {
    // Returns information about the selected printer
    FXPrinter getPrinter() {
	FXPrinter pr;
	self->getPrinter(pr);
	return pr;
    }
  }

  /// Destructor
  virtual ~FXPrintDialog();
  };


DECLARE_FXOBJECT_VIRTUALS(FXPrintDialog)
DECLARE_FXID_VIRTUALS(FXPrintDialog)
DECLARE_FXDRAWABLE_VIRTUALS(FXPrintDialog)
DECLARE_FXWINDOW_VIRTUALS(FXPrintDialog)
DECLARE_FXTOPWINDOW_VIRTUALS(FXPrintDialog)
DECLARE_FXDIALOGBOX_VIRTUALS(FXPrintDialog)

