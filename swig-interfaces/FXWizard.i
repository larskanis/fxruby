/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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

/**
* A Wizard widget guides the user through a number of panels
* in a predefined sequence; each step must be completed before
* moving on to the next step.
* For example, a Wizard may be used to install software components,
* and ask various questions at each step in the installation.
*/
class FXWizard : public FXDialogBox {
public:
  long onUpdFinish(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdNext(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdNext(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBack(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdBack(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_NEXT=FXDialogBox::ID_LAST,
    ID_BACK,
    ID_LAST
    };
public:
  %extend {
    /// Construct free-floating Wizard
    FXWizard(FXApp* a,const FXString& name,FXImage *image,FXuint opts=DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=10,FXint vs=10){
      return new FXRbWizard(a,name,image,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }

    /// Construct Wizard which will always float over the owner window
    FXWizard(FXWindow* owner,const FXString& name,FXImage *image,FXuint opts=DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=10,FXint pr=10,FXint pt=10,FXint pb=10,FXint hs=10,FXint vs=10){
      return new FXRbWizard(owner,name,image,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Return a pointer to the button frame
  FXHorizontalFrame *buttonFrame() const;

  /// Return a pointer to the "Advance" button
  FXButton *advanceButton() const;

  /// Return a pointer to the "Retreat" button
  FXButton *retreatButton() const;

  /// Return a pointer to the "Finish" button
  FXButton *finishButton() const;

  /// Return a pointer to the "Cancel" button
  FXButton *cancelButton() const;

  /// Return the container used as parent for the subpanels
  FXSwitcher *getContainer() const;

  /// Change the image being displayed
  void setImage(FXImage* img);

  /// Return the current image
  FXImage* getImage() const;

  /// Return number of panels
  FXint getNumPanels() const;

  %extend {
    /// Bring the child window at index to the top
    void setCurrentPanel(FXint index) {
      if(0<=index && index<self->getNumPanels()){
        self->setCurrentPanel(index);
        }
      else{
        rb_raise(rb_eIndexError,"panel index %d out of bounds",index);
        }
      }
  }

  /// Return the index of the child window currently on top
  FXint getCurrentPanel() const;

  // Destroy
  virtual ~FXWizard();
  };


DECLARE_FXOBJECT_VIRTUALS(FXWizard)
DECLARE_FXID_VIRTUALS(FXWizard)
DECLARE_FXDRAWABLE_VIRTUALS(FXWizard)
DECLARE_FXWINDOW_VIRTUALS(FXWizard)
DECLARE_FXTOPWINDOW_VIRTUALS(FXWizard)
DECLARE_FXDIALOGBOX_VIRTUALS(FXWizard)
