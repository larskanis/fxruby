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

// Tab Book options
enum {
  TABBOOK_TOPTABS    = 0,                                   // Tabs on top (default)
  TABBOOK_BOTTOMTABS = 0x00020000,                          // Tabs on bottom
  TABBOOK_SIDEWAYS   = 0x00040000,                          // Tabs on left
  TABBOOK_LEFTTABS   = TABBOOK_SIDEWAYS|TABBOOK_TOPTABS,    // Tabs on left
  TABBOOK_RIGHTTABS  = TABBOOK_SIDEWAYS|TABBOOK_BOTTOMTABS, // Tabs on right
  TABBOOK_NORMAL     = TABBOOK_TOPTABS
  };


/**
* The tab bar layout manager arranges tab items side by side,
* and raises the active tab item above the neighboring tab items.
* In a the horizontal arrangement, the tab bar can have the tab
* items on the top or on the bottom.  In the vertical arrangement,
* the tabs can be on the left or on the right.
* When one of the tab items is pressed, the tab bar's setCurrent()
* is called with notify=TRUE.  Thus causes the tab bar to send a
* SEL_COMMAND message to its target.
*/
class FXTabBar : public FXPacker {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusNext(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusPrev(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdOpenItem(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetValue(FXObject*,FXSelector,void* PTR_INT);
  long onCmdSetIntValue(FXObject*,FXSelector,void* PTR_PINT);
  long onCmdGetIntValue(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdOpen(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdOpen(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
public:
  enum {
    ID_OPEN_ITEM=FXPacker::ID_LAST,   /// Sent from one of the FXTabItems
    ID_OPEN_FIRST,                    /// Switch to panel ID_OPEN_FIRST+i
    ID_OPEN_SECOND,
    ID_OPEN_THIRD,
    ID_OPEN_FOURTH,
    ID_OPEN_FIFTH,
    ID_OPEN_SIXTH,
    ID_OPEN_SEVENTH,
    ID_OPEN_EIGHTH,
    ID_OPEN_NINETH,
    ID_OPEN_TENTH,
    ID_OPEN_LAST=ID_OPEN_FIRST+100,
    ID_LAST
    };
public:
  /// Construct a tab bar
  %extend {
    FXTabBar(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TABBOOK_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING){
      return new FXRbTabBar(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Return the currently active tab item
  FXint getCurrent() const;

  /// Return tab bar style
  FXuint getTabStyle() const;

  /// Change tab tab style
  void setTabStyle(FXuint style);

  /// Destructor
  virtual ~FXTabBar();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTabBar)
DECLARE_FXID_VIRTUALS(FXTabBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXTabBar)
DECLARE_FXWINDOW_VIRTUALS(FXTabBar)
DECLARE_FXTABBAR_VIRTUALS(FXTabBar)

%{
static swig_type_info *FXTabBar_dynamic_cast(void **ptr) {
    FXTabBar **ppTabBar = reinterpret_cast<FXTabBar **>(ptr);
    FXTabBook *pTabBook=dynamic_cast<FXTabBook*>(*ppTabBar);
    if(pTabBook){
      *ptr=reinterpret_cast<void*>(pTabBook);
      return SWIG_TypeQuery("FXTabBook *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXTabBar, FXTabBar_dynamic_cast);

