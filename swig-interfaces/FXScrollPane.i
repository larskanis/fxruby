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

class FXArrowButton;

%rename("numVisible=") FXScrollPane::setNumVisible(FXint);
%rename("numVisible")  FXScrollPane::getNumVisible() const;

/**
* A Scroll Pane is a menu pane which provides scrolling of menu entries.
* It is useful when menus are populated programmatically and it is not
* known in advance how many entries will be added.
*/
class FXScrollPane : public FXMenuPane {
public:
  long onCmdIncrement(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDecrement(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    ID_SCROLL_DN=FXMenuPane::ID_LAST,
    ID_SCROLL_UP,
    ID_LAST
    };
public:

  %extend {
    /// Construct menu pane
    FXScrollPane(FXWindow* owner,FXint nvis,FXuint opts=0){
      return new FXRbScrollPane(owner,nvis,opts);
      }
  }

  /// Return number of visible items
  FXint getNumVisible() const;

  /// Change the number of visible items
  void setNumVisible(FXint nvis);

  /// Get index of top most menu item
  FXint getTopItem() const;

  /// Scroll item to top
  void setTopItem(FXint t);

  /// Destroy
  virtual ~FXScrollPane();
  };

DECLARE_FXOBJECT_VIRTUALS(FXScrollPane)
DECLARE_FXID_VIRTUALS(FXScrollPane)
DECLARE_FXDRAWABLE_VIRTUALS(FXScrollPane)
DECLARE_FXWINDOW_VIRTUALS(FXScrollPane)
DECLARE_FXPOPUP_VIRTUALS(FXScrollPane)

