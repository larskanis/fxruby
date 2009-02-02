/********************************************************************************
*                                                                               *
*                           W i z a r d   W i d g e t                           *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2003 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXWizard.h 1536 2003-05-14 21:41:00Z lyle $                           *
********************************************************************************/
#ifndef FXWIZARD_H
#define FXWIZARD_H

#ifndef FXDIALOGBOX_H
#include "FXDialogBox.h"
#endif

namespace FX {


class FXImage;
class FXIcon;
class FXImageFrame;
class FXButton;
class FXSwitcher;


/**
* A Wizard widget guides the user through a number of panels
* in a predefined sequence; each step must be completed before
* moving on to the next step.
* For example, a Wizard may be used to install software components,
* and ask various questions at each step in the installation.
*/
class FXAPI FXWizard : public FXDialogBox {
  FXDECLARE(FXWizard)
protected:
  FXHorizontalFrame *buttons;           // Button frame
  FXImageFrame      *sidebar;           // Sidebar comprising image
  FXButton          *advance;           // Advance to next stage
  FXButton          *retreat;           // Retreat to last stage
  FXButton          *finish;            // Finish panel
  FXButton          *cancel;            // Cancel button
  FXSwitcher        *panels;            // Sub panels
  FXIcon            *finishicon;
  FXIcon            *nexticon;
  FXIcon            *backicon;
protected:
  FXWizard(){}
  void construct();
private:
  FXWizard(const FXWizard&);
  FXWizard &operator=(const FXWizard&);
public:
  long onUpdFinish(FXObject*,FXSelector,void*);
  long onCmdNext(FXObject*,FXSelector,void*);
  long onUpdNext(FXObject*,FXSelector,void*);
  long onCmdBack(FXObject*,FXSelector,void*);
  long onUpdBack(FXObject*,FXSelector,void*);
public:
  enum {
    ID_NEXT=FXDialogBox::ID_LAST,
    ID_BACK,
    ID_LAST
    };
public:

  /// Construct free-floating Wizard
  FXWizard(FXApp* a,const FXString& name,FXImage *image,FXuint opts=DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=10,FXint vs=10);

  /// Construct Wizard which will always float over the owner window
  FXWizard(FXWindow* owner,const FXString& name,FXImage *image,FXuint opts=DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=10,FXint vs=10);

  /// Return a pointer to the button frame
  FXHorizontalFrame *buttonFrame() const { return buttons; }

  /// Return a pointer to the "Advance" button
  FXButton *advanceButton() const { return advance; }

  /// Return a pointer to the "Retreat" button
  FXButton *retreatButton() const { return retreat; }

  /// Return a pointer to the "Finish" button
  FXButton *finishButton() const { return finish; }

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const { return cancel; }

  /// Return the container used as parent for the subpanels
  FXSwitcher *getContainer() const { return panels; }

  /// Change the image being displayed
  void setImage(FXImage* img);

  /// Return the current image
  FXImage* getImage() const;

  /// Return number of panels
  FXint getNumPanels() const;

  /// Bring the child window at index to the top
  void setCurrentPanel(FXint index);

  /// Return the index of the child window currently on top
  FXint getCurrentPanel() const;

  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  // Destroy
  virtual ~FXWizard();
  };

}

#endif
