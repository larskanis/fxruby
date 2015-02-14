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

class FXPopup;


%rename("selBackColor=") FXOption::setSelBackColor(FXColor);
%rename("selBackColor")  FXOption::getSelBackColor() const;
%rename("selTextColor=") FXOption::setSelTextColor(FXColor);
%rename("selTextColor")  FXOption::getSelTextColor() const;

/// Option Menu Button
class FXOption : public FXLabel {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onHotKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Constructor
    FXOption(FXComposite* p,const FXString& text,FXIcon* ic=NULL,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=JUSTIFY_NORMAL|ICON_BEFORE_TEXT,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbOption(p,text,ic,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Return the selection background color
  void setSelBackColor(FXColor clr);

  /// Return the selection background color
  FXColor getSelBackColor() const;

  /// Return the selection text color
  void setSelTextColor(FXColor clr);

  /// Return the selection text color
  FXColor getSelTextColor() const;

  /// Destructor
  virtual ~FXOption();
  };


DECLARE_FXOBJECT_VIRTUALS(FXOption)
DECLARE_FXID_VIRTUALS(FXOption)
DECLARE_FXDRAWABLE_VIRTUALS(FXOption)
DECLARE_FXWINDOW_VIRTUALS(FXOption)


/// Option Menu
class FXOptionMenu : public FXLabel {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdPost(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdUnpost(FXObject*,FXSelector,void* PTR_OPTION);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:
  %extend {
    /// Constructor
    FXOptionMenu(FXComposite* p,FXPopup* pup=NULL,FXuint opts=JUSTIFY_NORMAL|ICON_BEFORE_TEXT,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbOptionMenu(p,pup,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Set the current option
  void setCurrent(FXOption *win,FXbool notify=FALSE);

  /// Return the current option
  FXOption* getCurrent() const;

  /// Set the current option number
  void setCurrentNo(FXint no,FXbool notify=FALSE);

  /// Get the current option number
  FXint getCurrentNo() const;

  /// Get number of options
  FXint getNumOptions() const;

  /// Set the pane which will be popped up
  void setMenu(FXPopup *pup);

  /// Return the pane which is popped up
  FXPopup* getMenu() const;

  /// Return TRUE if popped up
  FXbool isPopped() const;

  /// Destructor
  virtual ~FXOptionMenu();
  };


DECLARE_FXOBJECT_VIRTUALS(FXOptionMenu)
DECLARE_FXID_VIRTUALS(FXOptionMenu)
DECLARE_FXDRAWABLE_VIRTUALS(FXOptionMenu)
DECLARE_FXWINDOW_VIRTUALS(FXOptionMenu)

