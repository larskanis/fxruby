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
* The tab book layout manager arranges pairs of children;
* the even numbered children (0,2,4,...) are usually tab items,
* and are placed on the top.  The odd numbered children are
* usually layout managers, and are placed below; all the odd
* numbered children are placed on top of each other, similar
* to the switcher widget.  When the user presses one of the
* tab items, the tab item is raised above the neighboring tabs,
* and the corresponding panel is raised to the top.
* Thus, a tab book can be used to present many GUI controls
* in a small space by placing several panels on top of each
* other and using tab items to select the desired panel.
* When one of the tab items is pressed, the tab book's setCurrent()
* is called with notify=TRUE.  Thus causes the tab book to send a
* SEL_COMMAND message to its target.
*/
class FXTabBook : public FXTabBar {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusNext(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusPrev(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdOpenItem(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  /// Construct tab book
  %extend {
    FXTabBook(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TABBOOK_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING){
      return new FXRbTabBook(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Destructor
  virtual ~FXTabBook();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTabBook)
DECLARE_FXID_VIRTUALS(FXTabBook)
DECLARE_FXDRAWABLE_VIRTUALS(FXTabBook)
DECLARE_FXWINDOW_VIRTUALS(FXTabBook)
DECLARE_FXTABBAR_VIRTUALS(FXTabBook)

