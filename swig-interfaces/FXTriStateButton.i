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
/**
* The tri-state button provides a three-state button, which toggles between the
* on and the off state each time it is pressed; programmatically, it may also be
* switched into the MAYBE state.  The MAYBE state is useful to signify an unknown
* state in the application data.
* Like the toggle button, it sends a SEL_COMMAND to its target, with the
* message data set to the current state of the toggle button, of the type FXbool.
*/
class FXTriStateButton : public FXToggleButton {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onUnknown(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
public:

  %extend {
    /// Construct tri-state toggle button with three text labels, and three icons, one for each state
    FXTriStateButton(FXComposite* p,const FXString& text1,const FXString& text2,const FXString& text3,FXIcon* icon1=NULL,FXIcon* icon2=NULL,FXIcon* icon3=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TOGGLEBUTTON_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbTriStateButton(p,text1,text2,text3,icon1,icon2,icon3,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
    }
  }

  /// Change maybe text shown when toggled
  void setMaybeText(const FXString& text);

  /// Return maybe text
  FXString getMaybeText() const;

  /// Change maybe icon shown when toggled
  void setMaybeIcon(FXIcon* ic);

  /// Return maybe icon
  FXIcon* getMaybeIcon() const;

  /// Change maybe help text shown when toggled
  void setMaybeHelpText(const FXString& text);

  /// Return maybe help text
  FXString getMaybeHelpText() const;

  /// Change maybe tip text shown when toggled
  void setMaybeTipText(const FXString& text);

  /// Return maybe tip text
  FXString getMaybeTipText() const;

  /// Destructor
  virtual ~FXTriStateButton();
  };

DECLARE_FXOBJECT_VIRTUALS(FXToggleButton)
DECLARE_FXID_VIRTUALS(FXToggleButton)
DECLARE_FXDRAWABLE_VIRTUALS(FXToggleButton)
DECLARE_FXWINDOW_VIRTUALS(FXToggleButton)

