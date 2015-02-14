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

class FXShutter;
class FXScrollWindow;


/**
* A Shutter Item is a panel which is embedded inside a Shutter Widget.
* It can contain other user interface widgets which can be added under
* the content widget.  The content widget is itself embedded in a scroll
* window to allow unlimited room for all the contents.
*/
class FXShutterItem : public FXVerticalFrame {
public:
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdButton(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_SHUTTERITEM_BUTTON=FXVerticalFrame::ID_LAST,
    ID_LAST
    };
public:
  /// Constructor
  %extend {
    FXShutterItem(FXShutter* p,const FXString& text=FXString::null,FXIcon* icon=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbShutterItem(p,text,icon,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Return a pointer to the button for this item
  FXButton* getButton() const;

  /// Return a pointer to the contents for this item
  FXVerticalFrame* getContent() const;

  /// Set the status line help text for this item
  void setHelpText(const FXString& text);

  /// Get the status line help text for this item
  FXString getHelpText() const;

  /// Set the tool tip message for this item
  void setTipText(const FXString& text);

  /// Get the tool tip message for this item
  FXString getTipText() const;

  /// Destructor
  virtual ~FXShutterItem();
  };


DECLARE_FXOBJECT_VIRTUALS(FXShutterItem)
DECLARE_FXID_VIRTUALS(FXShutterItem)
DECLARE_FXDRAWABLE_VIRTUALS(FXShutterItem)
DECLARE_FXWINDOW_VIRTUALS(FXShutterItem)



/**
* The Shutter widget provides a set of foldable sub panels.  Each subpanel
* consists of a Shutter Item which contains a button and some contents.
* A sub panel can be unfolded by pressing on that panel's button.
*/
class FXShutter : public FXVerticalFrame {
public:
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onTimeout(FXObject*,FXSelector,void* PTR_IGNORE);
  long onOpenItem(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdOpen(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdOpen(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:
  enum{
    ID_SHUTTER_TIMEOUT=FXVerticalFrame::ID_LAST,
    ID_OPEN_SHUTTERITEM,
    ID_OPEN_FIRST,
    ID_OPEN_LAST=ID_OPEN_FIRST+1000,
    ID_LAST
    };
public:
  /// Constructor
  %extend {
    FXShutter(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbShutter(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Return the index of the currently displayed item
  FXint getCurrent() const;

  /// Destructor
  virtual ~FXShutter();
  };


DECLARE_FXOBJECT_VIRTUALS(FXShutter)
DECLARE_FXID_VIRTUALS(FXShutter)
DECLARE_FXDRAWABLE_VIRTUALS(FXShutter)
DECLARE_FXWINDOW_VIRTUALS(FXShutter)
DECLARE_FXSHUTTER_VIRTUALS(FXShutter)

